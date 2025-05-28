// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __S_HEAP_H_INCLUDED
#define __S_HEAP_H_INCLUDED

typedef struct
{
    int size;
    char *heap;
    char *end;
} HEAP, *PHEAP;

void HeapAdd(PHEAP ph, zstr *pzstr, char *txt);
void HeapNew(PHEAP ph, int size);
void HeapDelete(PHEAP ph);

