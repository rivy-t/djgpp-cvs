/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#define USE_ESI
#define USE_EDI
#include <libc/asmdefs.h>

	FUNC(__movedataw)	/* src_sel, src_ofs, dest_sel, dest_ofs, len */
	ENTER

	pushw	%ds
	pushw	%es

	movl	ARG1,%eax
	movw	%ax,%ds
	movl	ARG2,%esi

	movl	ARG3,%eax
	movw	%ax,%es
	movl	ARG4,%edi

	movl	ARG5,%ecx
	cld
	rep
	movsw

	popw	%es
	popw	%ds

	LEAVE
