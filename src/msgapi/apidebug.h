// SPDX-License-Identifier: GPL-2.0-or-later



#if 0

#ifdef palloc
#undef palloc
#endif

#ifdef pfree
#undef pfree
#endif

#define palloc(p) dmalloc(p)
#define pfree(p) dfree(p)

#include "dmalloc.h"

#endif
