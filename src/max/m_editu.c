// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_editu.c,v 1.1.1.1 2002/10/01 17:52:39 sdudley Exp $";
#pragma on(unreferenced)

#include "max_msg.h"
#include "prog.h"

int Msg_Edit_User(void)
{
    HMSG mh;
    XMSG msg;

    if ((mh = MsgOpenMsg(sq, MOPEN_READ, last_msg)) == NULL ||
        MsgReadMsg(mh, &msg, 0L, 0L, NULL, 0L, NULL) == -1)
    {
        if (mh)
            MsgCloseMsg(mh);

        return -1;
    }

    MsgCloseMsg(mh);

    User_Edit(msg.from);
    return 0;
}
