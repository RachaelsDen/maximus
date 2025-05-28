// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __BTYPE_H_DEFINED
#define __BTYPE_H_DEFINED

#include "compiler.h"

// Insertion modes
#define IF_DUPE    0x0001 // Allow duplicate keys
#define IF_REPLACE 0x0002 // Replace existing key
#define IF_NORM    0x0004 // Insert only if new (default)

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

// Define API calling conventions
#ifndef BAPIENTRY
#define BAPIENTRY
#endif

#ifndef BEXPENTRY
#define BEXPENTRY
#endif

#define OS2FAR  // Obsolete; kept for compatibility

// Key comparison function pointer
typedef int (*keycomp_t)(void *a1, void *a2);

#endif /* __BTYPE_H_DEFINED */

