// SPDX-License-Identifier: GPL-2.0-or-later



#include "dv.h"
#include "prog.h"

#ifdef __MSDOS__

void cdecl VidPuts(char *Text)
{
    while (*Text)
        VidPutc(*Text++);
}

