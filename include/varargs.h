/* Copyright (C) 2000 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#ifndef __dj_include_vararg_h_
#define __dj_include_vararg_h_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __dj_ENFORCE_ANSI_FREESTANDING

#ifdef __dj_include_stdarg_h_
#error varargs.h and stdarg.h are mutually exclusive
#endif

#include <sys/djtypes.h>

__DJ_va_list
#undef __DJ_va_list
#define __DJ_va_list

/* For GCC 2.96 or later we use its builtin va_list */
#if ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 96)) || (__GNUC__ >= 3)

#define va_alist     __builtin_va_alist
#define va_dcl int __builtin_va_alist __attribute__((__mode__(__word__))); ...
#define va_start(ap) __builtin_varargs_start((ap))
#define va_end       __builtin_va_end
#define va_arg       __builtin_va_arg


#else /* #if ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 96)) || (__GNUC__ >= 3) */

#define va_alist __dj_last_arg

#define va_dcl int __dj_last_arg;

#define __dj_va_rounded_size(T)  \
  (((sizeof (T) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#define va_arg(ap, T) \
    (ap = (va_list) ((char *) (ap) + __dj_va_rounded_size (T)),	\
     *((T *) (void *) ((char *) (ap) - __dj_va_rounded_size (T))))

#define va_end(ap)

#define va_start(ap)  (ap=(char *)(&__dj_last_arg))

#endif /* #if ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 96)) || (__GNUC__ >= 3) */
  
#ifndef __STRICT_ANSI__

#ifndef _POSIX_SOURCE

#endif /* !_POSIX_SOURCE */
#endif /* !__STRICT_ANSI__ */
#endif /* !__dj_ENFORCE_ANSI_FREESTANDING */

#ifndef __dj_ENFORCE_FUNCTION_CALLS
#endif /* !__dj_ENFORCE_FUNCTION_CALLS */

#ifdef __cplusplus
}
#endif

#endif /* !__dj_include_varargs_h_ */
