/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <libc/stubs.h>
#include <process.h>

extern char **environ;

int spawnl(int mode, const char *path, const char *argv0, ...)
{
  return spawnve(mode, path, (char * const *)&argv0, environ);
}
