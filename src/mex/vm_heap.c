// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: vm_heap.c,v 1.2 2003/06/05 01:10:36 wesgarland Exp $";
#pragma on(unreferenced)

#define COMPILING_MEX_VM

#include "prog.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hpinit(void)
{
    pdshDheap = (struct _dsheap *)(pbDs + vmh.lGlobSize + vmh.lStackSize);
#ifdef HEAP_SIGNATURE
    pdshDheap->sig = DSHEAP_SIG;
#endif
    pdshDheap->size = vmh.lHeapSize - sizeof(struct _dsheap);
    pdshDheap->next = END_HEAP;
    pdshDheap->free = TRUE;
    pdshDheap->rsvd = 0;
}

VMADDR hpalloc(word len)
{
    struct _dsheap *dh, *fp, *new;
    VMADDR size;

#ifdef HEAP_PROBLEMS
    debheap = 1;
    if (len >= 6000)
    {
        printf("asdf\n");
    }

    if (hpcheck() != 0)
    {
        printf(__FUNCTION__ " bar\n");
    }
#endif

    for (dh = pdshDheap; dh; dh = (struct _dsheap *)(pbDs + dh->next))
    {

            if (dh->size < len)
            {
                size = dh->size;
                fp = dh;

                if (dh->next == END_HEAP)
                    break;


                while (fp && fp->next != END_HEAP && ((struct _dsheap *)(pbDs + fp->next))->free &&
                       size < len)
                {
                    fp = (struct _dsheap *)(pbDs + fp->next);


                    size += fp->size + sizeof(struct _dsheap);
                }


            if (dh->size >= len + sizeof(struct _dsheap) + 8)
            {

                new = (struct _dsheap *)((byte *)dh + sizeof(struct _dsheap) + len);


#ifdef DEBUGVM
            if (debheap)
                printf("%08lx - hpalloc(%d) from %lx\n", (long)((byte *)(dh + 1) - pbDs), len,
                       (long)vaIp);
#endif

            return ((byte *)(dh + 1) - pbDs);
        }

        if (dh->next == END_HEAP)
            break;
    }

    return END_HEAP;
}

void hpfree(VMADDR ofs)
{
    struct _dsheap *dh;

#ifdef HEAP_PROBLEMS
    if (hpcheck() != 0)
    {
        printf(__FUNCTION__ " foo\n");
    }
#endif

    dh = (struct _dsheap *)(pbDs + ofs) - 1;

    if (dh->free || dh->size == 0
#ifdef HEAP_SIGNATURE
        || dh->sig != DSHEAP_SIG
#endif
    )
        vm_err("Invalid hpfree(%08lx)", ofs);

    dh->free = TRUE;

#ifdef DEBUGVM
    if (debheap)
        printf("%08lx - hpfree() from %" UINT32_XFORMAT ")\n", ofs, (long)vaIp);
#endif
}

#ifdef HEAP_PROBLEMS

int hpcheck(void)
{
    struct _dsheap *dh;

    for (dh = pdshDheap; dh; dh = (struct _dsheap *)(pbDs + dh->next))
    {
