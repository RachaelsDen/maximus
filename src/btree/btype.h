// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __BTYPE_H_DEFINED
#define __BTYPE_H_DEFINED

#include "compiler.h"


// Actions for inserting a key that already exists.  The default
// action taken by insert() is to do nothing and return an error
// code.

#define IF_DUPE                                                                                    \
    0x0001 // If key of this name already
           // exists, insert a second using
           // the same key
#define IF_REPLACE                                                                                 \
    0x0002             // If key of this name already
                       // exists, replace it.
#define IF_NORM 0x0004 // Only insert new keys (default)

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#ifdef BEXPENTRY
#undef BEXPENTRY
#endif

#if defined(OS_2)
#ifdef __WATCOMC__
#ifdef __FLAT__
#define BEXPENTRY _System
#else
#define BEXPENTRY far pascal
#endif
#else
#ifdef __FLAT__
#define BEXPENTRY _System
#else
#ifdef __WATCOMC__
#define BEXPENTRY far pascal __loadds
#else
#define BEXPENTRY far pascal _loadds
#endif
#endif
#endif
#elif defined(NT)
#define BEXPENTRY NTstdcall
#else
#define BEXPENTRY
#endif

#ifdef __FLAT__
#ifndef BAPIENTRY
#if defined(OS_2)
#define BAPIENTRY _System
#elif defined(NT)
#define BAPIENTRY NTstdcall
#else
#define BAPIENTRY
#endif
#endif

#define OS2FAR
#else
#ifndef BAPIENTRY
#define BAPIENTRY BEXPENTRY
#endif

#ifdef OS_2
#define OS2FAR far
#else
#define OS2FAR
#endif
#endif


#ifdef __MSC__
typedef int(_stdc OS2FAR *keycomp_t)(void OS2FAR *a1, void OS2FAR *a2);
#else
typedef int(OS2FAR *_stdc keycomp_t)(void OS2FAR *a1, void OS2FAR *a2);
#endif

