// SPDX-License-Identifier: GPL-2.0-or-later


#include "crc.h"
#include "prog.h"
#include <stdlib.h>

word _fast crc16fn(word ch, word crc)
{
    word i;

    for (i = 8, ch <<= 8; i--; ch <<= 1)
        crc = (crc << 1) ^ (((ch ^ crc) & 0x8000u) ? CRC16CCITT : 0);

    return crc;
}

word *_fast mkcrc16tab(void)
{
    word *tab;
    word i;

    if ((tab = malloc(sizeof(word) * 256)) == NULL)
        return NULL;

    for (i = 0; i < 256; i++)
        tab[i] = crc16fn(i, 0);

    return tab;
}
