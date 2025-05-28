// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_scan.c,v 1.1.1.1 2002/10/01 17:52:50 sdudley Exp $";
#pragma on(unreferenced)


#include "max_msg.h"
#include "prog.h"
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Msg_Scan(char *menuname)
{
    SEARCH first;

    RipClear();

    Init_Search(&first);
    first.txt = strdup(usr.name);
    first.attr = MSGREAD;
    first.flag = SF_NOT_ATTR | SF_OR;
    first.where = WHERE_TO;

    Msg_Browse(BROWSE_AALL | BROWSE_NEW | BROWSE_EXACT | BROWSE_LIST, &first, menuname);
}

int Msg_List(char *menuname)
{
    RipClear();

    Msg_Browse(BROWSE_ACUR | BROWSE_FROM | BROWSE_LIST, NULL, menuname);
    return 0;
}
