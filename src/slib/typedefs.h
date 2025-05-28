// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef _TYPEDEFS_H
#define _TYPEDEFS_H
#include <sys/types.h>

#define INT8 char
#define INT16 short
#define INT32 int
#define INT64 long long

#define INT16_FORMAT "hi"
#define INT32_FORMAT "i"
#define INT64_FORMAT "lli"

#define UINT16_FORMAT "hu"
#define UINT32_FORMAT "u"
#define UINT64_FORMAT "llu"

#define UINT16_XFORMAT "hx"
#define UINT32_XFORMAT "x"
#define UINT64_XFORMAT "llx"

#define SIZET_FORMAT "lu"
#define POINTER_FORMAT "p"

#include <sys/types.h>

#if defined(LINUX) || defined(SOLARIS)
#define HAVE_ULONG
#define HAVE_USHORT
#endif

typedef signed INT64 int64;
typedef signed INT32 int32;
typedef signed INT16 int16;
typedef signed INT8 int8;
typedef unsigned INT64 uint64;
typedef unsigned INT32 uint32;
typedef unsigned INT16 uint16;
typedef unsigned INT8 uint8;

#if defined(SYSV)
#include <stddef.h>
#endif

#if (!defined(__FreeBSD__) && !defined(LINUX) && !defined(_PTRDIFF_T)) || defined(NEED_PTRDIFF_T)
#if defined(__PTRDIFF_TYPE__)
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#else
#ifndef HAVE_USHORT
typedef unsigned short ushort;
#endif

#ifndef HAVE_ULONG
typedef unsigned long ulong;
#endif

typedef signed short sshort;
typedef signed long slong;
typedef unsigned int bit;

#include "hntypes.h"
