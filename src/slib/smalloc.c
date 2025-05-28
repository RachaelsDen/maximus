// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <stdlib.h>
#include <string.h>

void *_fast smalloc(unsigned size)
{
    void *mem;

    if ((mem = (void *)malloc(size)) == NULL)
        NoMem();

    memset(mem, '\0', size);
    return mem;
}

char *_fast sstrdup(char *s)
{
    char *p;

    if ((p = strdup(s)) == NULL)
        NoMem();

    return p;
}
