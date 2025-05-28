// SPDX-License-Identifier: GPL-2.0-or-later
#ifndef __COMPILER_H_DEFINED
#define __COMPILER_H_DEFINED

// If the build system didn't define platform macros, fall back on auto-detect
#if !defined(UNIX) && (defined(__unix__) || defined(__unix) || defined(unix))
#define UNIX 1
#endif

#if !defined(LINUX) && defined(__linux__)
#define LINUX 1
#endif

// Compiler detection (modern builds are assumed to use GCC or Clang)
#if defined(__GNUC__) || defined(__clang__)
# define _stdc
# define _vstdc
# define _intr
# define _intcast
# define _veccast
# define _fast
# define _loadds
# define pascal
# define cdecl
# define far
# define near
# define NW(var) (void)(var)
#else
# error Unsupported compiler! Please use GCC or Clang.
#endif

#ifndef __TYPEDEFS_H_DEFINED
#include "typedefs.h"
#endif

#include "compiler_align.h"

#endif // __COMPILER_H_DEFINED