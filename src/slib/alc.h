// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __ALC_H_DEFINED
#define __ALC_H_DEFINED

#include "compiler.h"

#if defined(_lint) || defined(__MSC__) || defined(__WATCOMC__) || defined(__IBMC__) ||             \
    defined(__TOPAZ__)
#include <malloc.h>

#ifdef __FARDATA__


unsigned long cdecl coreleft(void);
#else
unsigned cdecl coreleft(void);
#endif

#elif defined(__TURBOC__)
#include <alloc.h>
#else
#include <string.h>
#endif

#ifdef __TURBOC__
#define halloc(x, y) ((char far *)farmalloc(x * y))
#define hfree(p) farfree(p)
#endif

