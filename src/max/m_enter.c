// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_enter.c,v 1.1.1.1 2002/10/01 17:52:39 sdudley Exp $";
#pragma on(unreferenced)


#include "max_msg.h"
#include "prog.h"

int Msg_Enter(void)
{
    int aborted, rc;
    XMSG msg;

    isareply = isachange = FALSE;

    Blank_Msg(&msg);
    *netnode = *orig_msgid = '\0';

    if (GetMsgAttr(&msg, &mah, usr.msg, 0L, -1L) == -1)
        aborted = TRUE;
    else if ((rc = Editor(&msg, NULL, 0L, NULL, NULL)) == ABORT)
        aborted = TRUE;
    else if (rc == LOCAL_EDIT)
        aborted = FALSE;
    else
        aborted = SaveMsg(&msg, NULL, FALSE, 0L, FALSE, &mah, usr.msg, sq, NULL, NULL, FALSE);

    if (aborted)
    {
        Puts(msg_aborted);
        return -1;
    }

    return 0;
}
