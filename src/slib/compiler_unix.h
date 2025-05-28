// SPDX-License-Identifier: GPL-2.0-or-later




#ifndef __COMPILER_UNIX_H_DEFINED
#define __COMPILER_UNIX_H_DEFINED


#ifndef UNIX
#error Wrong header file, or no -DUNIX!
#endif

#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif

#include "compat.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define __POSIX__
#define __FARCODE__
#define __FARDATA__
#define __LARGE__
#define __FLAT__
#define EXPENTRY

#define _stdc
#define _vstdc
#define _intr
#define _intcast
#define _veccast
#define _fast
#define _loadds

#define pascal
#define cdecl
#define far
#define near
#define huge

#define NW(var) (void)var

#if defined(__GNUC__) && (__GNUC__ > 2) && (__GNU_MINOR__ > 0)
#define __dll_initialize(...) dll_initialize(__VA_ARGS__) __attribute__((constructor)) __
#define __dll_terminate(...) dll_terminate(__VA_ARGS__) __attribute__((destructor)) __
#else
#define __dll_initialize _init
#define __dll_terminate _fini
#endif


#define mkdir(a) mkdir(a, 0777)
