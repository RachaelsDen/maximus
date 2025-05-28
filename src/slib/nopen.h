// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __NOPEN_H_DEFINED
#define __NOPEN_H_DEFINED

#include "prog.h"
#include "uni.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef __TURBOC__
#undef sopen
int _stdc sopen(const char *name, int mode, int shacc, ...);
#endif

int _stdc nsopen(const char *name, int mode, int shacc, ...);
int _stdc nopen(const char *name, int mode, ...);
int _stdc nread(int fd, char *buf, unsigned len);
int _stdc nwrite(int fd, char *buf, unsigned len);
long _stdc nlseek(int fd, long ofs, int pos);
long _stdc ntell(int fd);
int _stdc nclose(int fd);
int _stdc ndup(int fd);
int _stdc ndup2(int fd1, int fd2);

