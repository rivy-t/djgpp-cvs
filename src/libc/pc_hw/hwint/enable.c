/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <dos.h>
#include <dpmi.h>

int
enable(void)
{
  /* return __dpmi_get_and_enable_virtual_interrupt_state(); */
  int rv;
  asm volatile ("pushf; popl %0" : "=g" (rv));
  rv = (rv>>9) & 1;
  asm("sti");
  return rv;
}
