/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2000 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/*
 * tminit.c - initializer and main part of termios emulation.
 *   designed for DJGPP by Daisuke Aoyama <jack@st.rim.or.jp>
 *   special thanks to Ryo Shimizu
 */

#include <libc/stubs.h>
#include <go32.h>
#include <io.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <libc/file.h>
#include <libc/ttyprvt.h>
#include <libc/farptrgs.h>
#include <libc/getdinfo.h>

#define NPAR 16

struct screen_info
{
  unsigned char init_attrib;
  unsigned char attrib;
  unsigned char max_row;
  unsigned char active_page;
  unsigned short max_col;
  unsigned long video_buffer;
};

/* Console command parser */

enum cmd_parser_states { need_esc = 0, have_esc, have_lbracket,
                         have_arg, have_cmd};

static enum cmd_parser_states cmd_state;

static struct screen_info screen;

/* static functions */
static ssize_t __libc_termios_write (int handle, const void *buffer, size_t count, ssize_t *rv);
static ssize_t __libc_termios_write_cooked_tty (int handle, const void *buffer, size_t count);
static ssize_t __libc_termios_write_raw_tty (int handle, const void *buffer, size_t count);
static size_t parse_console_command(const unsigned char *buf, size_t count);
static void execute_console_command(const unsigned char cmd, unsigned char argc, unsigned int args[NPAR]);

/* direct I/O functions */
static inline void __direct_output (unsigned char ch);
static inline void __direct_outputs (const unsigned char *s);

/* Cursor motion functions.  */
static void set_cursor(unsigned char col, unsigned char row);
static void move_cursor(int x_delta, int y_delta);
static void get_cursor(unsigned char *col, unsigned char *row);

/* Initialize the screen portion of termios.  */
void __libc_termios_init_write(void)
{
  __dpmi_regs r;

  /* set special hooks */
  __libc_write_termios_hook = __libc_termios_write;
  _farsetsel(_dos_ds);

  screen.active_page = _farnspeekb(0x462);
  screen.max_row = _farnspeekb(0x484);
  screen.max_col = _farnspeekb(0x44a) - 1;
  screen.video_buffer = 0xb800 * 16;

  r.h.ah = 0x08;
  r.h.bh = screen.active_page;
  __dpmi_int(0x10, &r);

  screen.init_attrib = r.h.ah;
  screen.attrib = r.h.ah;
}

/******************************************************************************/
/* direct I/O function (inlined) **********************************************/

static inline void
__direct_output (unsigned char ch)
{
  __dpmi_regs r;

  if (ch == 0xff)
    return;

  r.h.al = ch;
  __dpmi_int (0x29, &r);
}

static inline void
__direct_outputs (const unsigned char *s)
{
  while (*s)
    __direct_output (*s++);
}

/******************************************************************************/
/* special write function *****************************************************/

static ssize_t
__libc_termios_write (int handle, const void *buffer, size_t count, ssize_t *rv)
{
  short devmod;

  /* check handle whether valid or not */
  devmod = _get_dev_info (handle);
  if (devmod == -1)
    {
      *rv = -1;
      return 1;
    }

  /* special case */
  if (count == 0)
    {
      *rv = 0;
      return 1;
    }

  /* console only... */
  if ((devmod & _DEV_CDEV) && (devmod & (_DEV_STDIN|_DEV_STDOUT)))
    {
      /* character device */
      if ((devmod & _DEV_RAW) && (__file_handle_modes[handle] & O_BINARY))
	*rv = __libc_termios_write_raw_tty (handle, buffer, count);
      else
	*rv = __libc_termios_write_cooked_tty (handle, buffer, count);
      return 1;
    }

  return 0;
}

static ssize_t
__libc_termios_write_cooked_tty (int handle, const void *buffer, size_t count)
{
  ssize_t bytes;

  /* output process if need */
  if (__libc_tty_p->t_oflag & OPOST)
    {
      const unsigned char *rp;
      unsigned char ch;
      ssize_t n;

      rp = buffer;
      n = count;
      while (n > 0)
	{
	  /* get character */
          ch = *rp;

          /* Handle console commands */
	  if (ch == '\e' || cmd_state != need_esc)
          {
            size_t delta;
            delta = parse_console_command(rp, n);

            /* Skip past what was parsed.  */
            n -= delta;
            rp += delta;
            continue;
          }

	  ++rp;
          --n;

	  /* NOTE: multibyte character don't contain control character */
	  /* map NL to CRNL */
	  if (ch == '\n' && (__libc_tty_p->t_oflag & ONLCR))
	    __direct_output ('\r');
	  /* map CR to NL */
	  else if (ch == '\r' && (__libc_tty_p->t_oflag & OCRNL))
	    ch = '\n';
	  /* produce spaces until the next TAB stop */
	  else if (ch == '\t')
	    {
	      int col, max_col;

	      _farsetsel (_dos_ds);
	      /* current column (cursor position) on the active page */
	      col = _farnspeekw (0x450 + _farnspeekb (0x462)) & 0xff;
	      /* the number of displayed character columns */
	      max_col = _farnspeekw (0x44a);

	      for (__direct_output (' '), col += 1; col % 8; col++)
		{
		  if (col >= max_col - 1)
		    col = -1;
		  __direct_output (' ');
		}
	      continue;
	    }

	  __direct_output (ch);
	}

      /* don't count CR */
      bytes = count;
    }
  else
    {
      /* output with no effect */
      bytes = __libc_termios_write_raw_tty (handle, buffer, count);
    }

  return bytes;
}

static ssize_t
__libc_termios_write_raw_tty (int handle, const void *buffer, size_t count)
{
  const unsigned char *rp;
  ssize_t n;
  unsigned char ch;

  rp = buffer;
  n = count;
  while (--n >= 0)
  {
    ch = *rp++;
    __direct_output(ch);
  }

  return count;
}


static inline int
is_command_char(unsigned char ch)
{
  return isalpha(ch) || ch == '@';
}

static size_t
parse_console_command(const unsigned char *buf, size_t count)
{
  static unsigned int args[NPAR];
  static unsigned char arg_count;
  static unsigned char ignore_cmd;

  const unsigned char *ptr = buf;
  const unsigned char *ptr_end = buf + count;

  while (ptr < ptr_end)
  {
    switch (cmd_state)
    {
      case need_esc:
        /* Find an escape or bail out.  */
        if (*ptr != '\e')
          return (ptr - buf);
        ++ptr;
        cmd_state = have_esc;
        if (ptr >= ptr_end)
          break;

      case have_esc:
        /* Find a left bracket or bail out.  */
        if (*ptr != '[')
          return (ptr - buf);

        cmd_state = have_lbracket;
        ++ptr;
        if (ptr == ptr_end)
          break;

      case have_lbracket:
        /* After the left bracket, either an argument
           or the command follows.  */
        arg_count = NPAR;
        arg_count = 0;
        args[0] = 0;
        if (isdigit(*ptr))
        {
          cmd_state = have_arg;
        }
        else if (*ptr == '[')
        {
          /* Ignore function keys. */
          ignore_cmd = 1;
          ++ptr;
          break;
        }
        else
        {
          cmd_state = have_cmd;
          break;
        }

      case have_arg:
      {
        /* Parse the argument.  Quit when there are no more digits.  */
        if (isdigit(*ptr))
        {
          do
          {
            args[arg_count] *= 10;
            args[arg_count] += *ptr - '0';
            ++ptr;
          } while (ptr < ptr_end && isdigit(*ptr));
          break;
        }
        else if (*ptr == ';')
        {
          /* Argument separator.  */
          ++arg_count;
          if (arg_count < NPAR)
            args[arg_count] = 0;
          ++ptr;
          break;
        }
        else
        {
          /* End of the current argument.
             Assume the command has been reached.  */
          cmd_state = have_cmd;
          ++arg_count;
        }
      }
      case have_cmd:
      {
        /* Execute the command.  */
        if (is_command_char(*ptr) && !ignore_cmd)
          execute_console_command(*ptr, arg_count, args);

        /* Reset the parse state.  */
        cmd_state = need_esc;
        ignore_cmd = 0;
        ++ptr;
        return ptr - buf;
      }
    }
  }
  return ptr - buf;
}

#define GET_ARG(I, DEFVAL) ((argc > I) ? (args[I]) : (DEFVAL))

static void
execute_console_command(const unsigned char cmd, unsigned char argc,
                        unsigned int args[NPAR])
{
  unsigned char row, col;

  switch (cmd)
  {
    /* CUU: Cursor up.  */
    case 'A':
      move_cursor(0, -GET_ARG(0, 1));
      break;

    /* CUD: Cursor down.  */
    case 'B':
      move_cursor(0, GET_ARG(0, 1));
      break;

    /* CUF: Cursor right.  */
    case 'C':
      move_cursor(GET_ARG(0, 1), 0);
      break;

    /* CUB: Cursor Left.  */
    case 'D':
      move_cursor(-GET_ARG(0, 1), 0);
      break;

    /* CHA: Cursor to column.  */
    case 'G':
      get_cursor(&row, &col);
      set_cursor(GET_ARG(0, 1) - 1, row);
      break;

    /* CUP, HVP: Cursor to row and column.  */
    case 'H':
    case 'f':
      set_cursor(GET_ARG(0, 1) - 1, GET_ARG(1, 1) - 1);
      break;

    /* VPA: Cursor to row.  */
    case 'd':
      get_cursor(&col, &row);
      set_cursor(col, GET_ARG(0, 1) - 1);
      break;

    /* CHT: Cursor to next tab stop.  */
    case 'I':
      get_cursor(&col, &row);
      set_cursor(col / 8 * 8 + GET_ARG(0, 1) * 8, row);
      break;

    /* CBT: Cursor to previous tab stop.  */
    case 'Z':
      get_cursor(&col, &row);
      if (col > 0 && GET_ARG(0, 1) > 0)
        set_cursor((col - 1) / 8 * 8 - (GET_ARG(0, 1) - 1) * 8, row);
      break;

    /* Unrecognized command. Do nothing.  */
    default:
      break;
  }
}

static void
get_cursor(unsigned char *col, unsigned char *row)
{
  unsigned short rowcol;

  rowcol = _farnspeekw(0x450 + screen.active_page);
  *row = rowcol >> 8;
  *col = rowcol & 0xff;
}

static void
set_cursor(unsigned char col, unsigned char row)
{
  __dpmi_regs r;

  _farsetsel(_dos_ds);

  if (row > screen.max_row)
    row = screen.max_row;

  if (col > screen.max_col)
    col = screen.max_col;

  r.h.ah = 2;
  r.h.bh = screen.active_page;
  r.h.dh = row;
  r.h.dl = col;
  __dpmi_int(0x10, &r);
}

static void
move_cursor(int x_delta, int y_delta)
{
  unsigned char row, col;
  unsigned short rowcol;
  __dpmi_regs r;

  rowcol = _farpeekw(_dos_ds, 0x450 + screen.active_page);
  row = rowcol >> 8;
  col = rowcol & 0xff;

  if ((int)row + y_delta < 0)
    row = 0;
  else if (row + y_delta > screen.max_row)
    row = screen.max_row;

  if ((int)col + x_delta < 0)
    col = 0;
  else if (col + x_delta > screen.max_col)
    col = screen.max_col;

  r.h.ah = 2;
  r.h.bh = screen.active_page;
  r.h.dh = row + y_delta;
  r.h.dl = col + x_delta;
  __dpmi_int(0x10, &r);
}

