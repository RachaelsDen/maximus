// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_create.c,v 1.1.1.1 2002/10/01 17:52:39 sdudley Exp $";
#pragma on(unreferenced)


#include "max_edit.h"
#include "max_msg.h"
#include "prog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Goodbye_Comment(void)
{
    extern int linenum;
    int aborted, rc;
    char *where;
    XMSG msg;


    Blank_Msg(&msg);
    *netnode = *orig_msgid = 0;

    strcpy(msg.from, usrname);


    Parse_Outside_Cmd(comment_fr, msg.subj);


    if (usr.bits2 & BITS2_BORED)
        Printf(inrefto, msg.subj);

    rc = Editor(&msg, NULL, 0L, NULL, NULL);


        if ((last_maxed ? num_lines : linenum) == 1 && screen[1] && screen[1][1] == '\0')
        {
            Free_All();
            aborted = TRUE;
        }
        else
        {

            strcpy(msg.to, PRM(sysop));
            aborted = SaveMsg(&msg, NULL, FALSE, 0, FALSE, &mah, where, sq, NULL, NULL, TRUE);
        }
    }

    if (aborted)
        Puts(msg_aborted);

    PopMsgArea();
    ForceGetMsgArea();

    return !aborted;
}
