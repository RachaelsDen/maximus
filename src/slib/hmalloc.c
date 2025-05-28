// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"

#if defined(OS_2) && !defined(__FLAT__)

#define INCL_DOSMEMMGR
#include "pos2.h"

void huge *_fast h_malloc(long size)
{
    SEL sel;
    unsigned usSeg;
    unsigned usOfs;

    usSeg = (unsigned)(size / 65536L);
    usOfs = (unsigned)(size % 65536L);

    if (DosAllocHuge(usSeg, usOfs, &sel, 19, SEG_NONSHARED) != 0)
        return NULL;

    return MAKEP(sel, 0);
}

void _fast h_free(void huge *p) { DosFreeSeg(SELECTOROF(p)); }

void huge *_fast h_realloc(void huge *p, long newsize)
{
    SEL sel = SELECTOROF(p);

    if (DosReallocHuge((unsigned)(newsize / 65536L), (unsigned)(newsize % 65536L), sel) != 0)
    {
        return NULL;
    }

    return MAKEP(sel, 0);
}

#else

#include "alc.h"
#include "prog.h"
#include <stdlib.h>

void huge *_fast h_malloc(long size) { return farmalloc((size_t)size); }

void _fast h_free(void huge *p) { farfree((void *)p); }

void huge *_fast h_realloc(void huge *p, long newsize)
{
    return farrealloc((void *)p, (size_t)newsize);
}

#endif
