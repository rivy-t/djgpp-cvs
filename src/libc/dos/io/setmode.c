/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <libc/stubs.h>
#include <sys/exceptn.h>
#include <dpmi.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>

#include <libc/dosio.h>

void (*__setmode_stdio_hook)(int fd, int mode); /* BSS to zero */

int
setmode(int handle, int mode)
{
  __dpmi_regs regs;
  int oldmode, newmode;

  regs.x.ax = 0x4400;
  regs.x.bx = handle;
  regs.x.dx = 0;		/* Clear upper e-word for return */
  __dpmi_int(0x21, &regs);
  if (regs.x.flags & 1)
  {
    errno = __doserr_to_errno(regs.x.ax);
    return -1;
  }
  oldmode = newmode = regs.x.dx;

  if (mode & O_BINARY)
    newmode |= 0x20;
  else
    newmode &= ~0x20;

  if (oldmode & 0x80)	/* Only for character dev */
  {
    regs.x.ax = 0x4401;
    regs.x.bx = handle;
    regs.x.dx = newmode & 0xff;   		/* Force upper byte zero */
    __dpmi_int(0x21, &regs);
    if (regs.x.flags & 1)
    {
      errno = __doserr_to_errno(regs.x.ax);
      return -1;
    }
    if (handle == 0)
      __djgpp_set_ctrl_c(!(mode & O_BINARY));
  }

  oldmode = __file_handle_modes[handle] & (O_BINARY|O_TEXT);
  __file_handle_modes[handle] &= ~(O_BINARY|O_TEXT);
  __file_handle_modes[handle] |= (mode & (O_BINARY|O_TEXT));

  return oldmode;
}
