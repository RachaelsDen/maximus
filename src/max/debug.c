// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: debug.c,v 1.1.1.1 2002/10/01 17:50:46 sdudley Exp $";
#pragma on(unreferenced)

#include "mm.h"
#include "prog.h"


#ifdef __TURBOC__
void pascal far Swap_Log(byte ovlno, word out)
{
    NW(ovlno);
    NW(out);

#ifdef TEST_VER
    if (debug_ovl)
        logit(">@%s: %02x", (out ? "Out" : "In"), ovlno);
#endif
}

#endif
