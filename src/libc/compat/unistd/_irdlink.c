/* Copyright (C) 2000 DJ Delorie, see COPYING.DJ for details */

#include <libc/stubs.h>
#include <libc/symlink.h>
#include <sys/fsext.h>
#include <dir.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "xsymlink.h"

int __internal_readlink(const char * __path, int __fhandle, char * __buf, 
                        size_t __max)
{
   ssize_t       bytes_read         = 0;
   char          buf[_SYMLINK_FILE_LEN];
   char        * data_buf;
   int           fd;
   int           ret;
   off_t         old_pos = 0;
   long          file_size;

   /* Reject NULL and impossible arg combinations */
   if (!__buf || (__path && __fhandle))
   {
      errno = EINVAL;
      return -1;
   }

   /* Provide ability to hook symlink support */
   if (__path)
   {
      if (__FSEXT_call_open_handlers(__FSEXT_readlink, &ret, &__path))
         return ret;
   }
   else if (__fhandle)
   {
      __FSEXT_Function *func = __FSEXT_get_function(__fhandle);
      if (func)
      {
         int rv;
         if (func(__FSEXT_readlink, &rv, &__path))
            return rv;
      }
   }
   else
   {
      /* What the ?.. */
      errno = EINVAL;
      return -1;
   }


   /* Get file size */

   if (__fhandle)
      file_size = filelength(__fhandle);
   else
   {
      /* We will check if file exists by the way */
      struct ffblk  file_info;
      if (findfirst(__path, &file_info, 0))
      {
         errno = ENOENT;
         return -1;
      }
      file_size = file_info.ff_fsize;
   }

   /* Is symlink file size a fixed magic value? */
   if (file_size != _SYMLINK_FILE_LEN)
   {
      errno = EINVAL; /* Sad but true */
      return -1;
   }

   /* Now we check for special DJGPP symlink format */

   /* If we have file handle */
   if (__fhandle)
   {
      /* Remember old file pos */
      old_pos = tell(__fhandle);
      if (old_pos == -1)
         return -1;
      lseek(__fhandle, 0, SEEK_SET);
      fd = __fhandle;
   }
   else
   {
      fd = _open(__path, O_RDONLY);
      if (fd < 0)
      {
         /* Retry with DENY-NONE share bit set. It might help in some cases
          * when symlink file is opened by another program. We don't try with
          * DENY-NONE set in the first _open() call, because it might fail under
          * some circumstances. For details, see Ralf Brown's Interrupt List,
          * description of INT 0x21, function 0x3D.
          */
         fd = _open(__path, O_RDONLY | SH_DENYNO);
         if (fd < 0)
            return -1; /* errno from _open() call */
      } 
   }

   bytes_read = read(fd, &buf, _SYMLINK_FILE_LEN);

   if (__fhandle)
      lseek(__fhandle, old_pos, SEEK_SET);
   else
      _close(fd);

   if (bytes_read == -1)
      return -1; /* Return errno set by _read() (_close() in worse case) */
      
   /* Check for symlink file header */
   if (strncmp(buf, _SYMLINK_PREFIX, _SYMLINK_PREFIX_LEN))
   {
      close(fd);
      errno = EINVAL;
      return -1;
   }
   
   data_buf = buf + _SYMLINK_PREFIX_LEN;
   bytes_read = strchr(data_buf, '\n') - data_buf;
   bytes_read = ((unsigned)bytes_read > __max) ? __max : bytes_read;
   memcpy(__buf, data_buf, bytes_read);
   return bytes_read;
}
