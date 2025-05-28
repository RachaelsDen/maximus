// SPDX-License-Identifier: GPL-2.0-or-later


#include "compiler.h"
#include <stdlib.h>

void NoMem();

#if !SLOPPY_ALIGNMENT_OKAY

#if defined(NEED_MEMALIGN)

    aligned = memalign(alignment, size);
    if (!aligned)
        NoMem();
    memcpy(aligned, unaligned, size);

    return aligned;
}

void _unaligndup_free(void *unaligned, void *aligned, size_t size)
{
    if (unaligned == aligned)

    if (alignedStaticRAM == NULL)
    {
        alignedStaticRAM = realloc(alignedStaticRAM, size);
        alignedSize = size;
    }

    if (alignedStaticRAM == NULL)
        NoMem();

    memcpy(alignedStaticRAM, unaligned, size);
    return alignedStaticRAM;
}

void _unalign(void *unaligned, void *aligned, size_t size)
{
    if (unaligned != aligned)
        memcpy(unaligned, aligned, size);

    return;
}

