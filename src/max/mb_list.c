// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mb_list.c,v 1.1.1.1 2002/10/01 17:52:10 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_m_browse

#include "m_browse.h"
#include "max_msg.h"
#include "prog.h"
#include <stdlib.h>
#include <string.h>

extern int last_title;
extern int idling;

int List_Begin(BROWSE *b)
{
    NW(b);

    Puts(br_list_head1);
    Puts(br_list_head2);

    return 0;
}

int List_Display(BROWSE *b)
{


    return 0;
}

int List_After(BROWSE *b)
{
    NW(b);
    return 0;
}
