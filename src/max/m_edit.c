// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_edit.c,v 1.1.1.1 2002/10/01 17:52:39 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_bor

#include "max_edit.h"
#include "max_msg.h"
#include "prog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


        if (linenum && screen[linenum - 1])
            free(screen[linenum - 1]);

        return -1;
    }

    screen[linenum][0] = HARD_CR;
    screen[linenum][1] = '\0';

    num_lines++;

    return 0;
}


void Free_All(void)
{
    int i;

    for (i = num_lines; i >= 1; i--)
        Free_Line(i);

    if (screen[max_lines] && max_lines > 0)
    {
        Free_Line(max_lines);
        screen[max_lines] = NULL;
    }
}


void Parse_Initials(char *msgfrom, char *initials)
{
    char *p, *s;
    char os[36];
    word quota;

    strncpy(os, msgfrom, 35);
    msgfrom[35] = '\0';


word QuoteThisLine(char *txt)
{
    char *pointy_thing;

    pointy_thing = strchr(txt, '>');

    return (*txt != '\0' && (!pointy_thing || pointy_thing >= txt + 5) &&
            !eqstri(txt, end_widget2));
}
