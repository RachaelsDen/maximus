// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_heap.c,v 1.1.1.1 2002/10/01 17:57:45 sdudley Exp $";
#pragma on(unreferenced)

#define SILT
#define NOVARS
#define NOINIT
#define NO_MSGH_DEF

#include "s_heap.h"
#include "max.h"
#include "prog.h"
#include "silt.h"
#include <stdlib.h>
#include <string.h>

void HeapAdd(PHEAP ph, zstr *pzstr, char *txt)
{
    if (ph->end - ph->heap + strlen(txt) >= ph->size)
    {
        printf("\n\aError!  Internal SILT heap is full!  (No more than %d bytes allowed.)\n",
               ph->size);
        exit(1);
    }


void HeapNew(PHEAP ph, int size)
{
    ph->size = size;

    if ((ph->heap = malloc(size)) == NULL)
        NoMem();

    *ph->heap = 0;
    ph->end = ph->heap + 1;
}

void HeapDelete(PHEAP ph)
{
    free(ph->heap);
    ph->heap = ph->end = NULL;
}
