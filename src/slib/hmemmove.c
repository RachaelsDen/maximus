// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <stdio.h>

#ifdef OS_2
#define INCL_DOS
#include "pos2.h"
#endif


void _fast h_memmove(void huge *vto, void huge *vfrom, long size)
{
    char huge *to = vto;
    char huge *from = vfrom;

    while (size > 0)
    {
        unsigned long ulMaxTo = 65536L - (word)(char near *)to;
        unsigned long ulMaxFrom = 65536L - (word)(char near *)from;
        unsigned long ulTransfer = (unsigned long)size;

        if (!ulMaxTo || !ulMaxFrom)
        {
#ifdef OS_2
            DosBeep(500, 100);
            DosBeep(2500, 100);
            DosBeep(2000, 100);
            DosBeep(2000, 100);
            DosBeep(2000, 100);
#endif
            return;
        }

        ulTransfer = min(ulTransfer, ulMaxTo);
        ulTransfer = min(ulTransfer, ulMaxFrom);

        f_memmove(to, from, (word)ulTransfer);

        to += ulTransfer;
        from += ulTransfer;
        size -= ulTransfer;
    }
}

#endif
