// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_fins.c,v 1.1.1.1 2002/10/01 17:51:38 sdudley Exp $";
#pragma on(unreferenced)

#define MAX_LANG_max_init
#define MAX_LANG_max_chat
#define MAX_INCL_COMMS

#include "mm.h"
#include "prog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Fossil_Install(int fInitVideo)
{
    if (mdm_init(local ? 0xff : port) == INIT_nofossil)
    {
        if (local)
            return;
        else
        {
            logit(log_no_fossil);
            quit(ERROR_NOFOSSIL);
        }
    }

    fossil_initd = TRUE;

    Mdm_Flow_On();

    if (fInitVideo)
    {
        if (!no_video)
#ifdef TTYVIDEO
            if (displaymode == VIDEO_IBM)
#endif
                WinSyncAll();
    }
}
