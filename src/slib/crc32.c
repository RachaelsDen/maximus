// SPDX-License-Identifier: GPL-2.0-or-later


#include "crc.h"
#include "prog.h"
#include <stdlib.h>

dword _fast crc32fn(word ch, dword crc)
{
    dword dwch = (dword)ch;
    word i;

    for (i = 8; i--; dwch >>= 1)
        crc = (crc >> 1) ^ (((dwch ^ crc) & 1) ? CRC32POLY : 0);

    return crc;
}

dword *_fast mkcrc32tab(void)
{
    dword *tab;
    word i;

    if ((tab = malloc(sizeof(dword) * 256)) == NULL)
        return NULL;

    for (i = 0; i < 256; i++)
        tab[i] = crc32fn(i, 0L);

    return tab;
}
