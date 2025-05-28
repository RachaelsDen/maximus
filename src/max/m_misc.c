// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_misc.c,v 1.1.1.1 2002/10/01 17:52:46 sdudley Exp $";
#pragma on(unreferenced)

#include "max_msg.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


void Msg_Unreceive(dword last_msg, HMSG hm)
{
    HMSG hmsg;
    XMSG msg;

    if (hm)
        hmsg = hm;
    else if ((hmsg = MsgOpenMsg(sq, MOPEN_RW, last_msg)) == NULL)
    {
        Puts(msgnotavail);
        return;
    }

    if (MsgReadMsg(hmsg, &msg, 0L, 0L, NULL, 0L, NULL) == 0)
    {
        if (!CanSeeMsg(&msg))
        {
            Puts(msgnotavail);
            MsgCloseMsg(hmsg);
            return;
        }

        msg.attr &= ~MSGREAD;
        MsgWriteMsg(hmsg, TRUE, &msg, NULL, 0L, 0L, 0L, NULL);
    }

    if (!hm)
        MsgCloseMsg(hmsg);

    Puts(WHITE);
    Puts(done_ex);
}
