// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_kill.c,v 1.1.1.1 2002/10/01 17:52:44 sdudley Exp $";
#pragma on(unreferenced)


#include "max_msg.h"
#include "prog.h"
#include "trackm.h"
#include <io.h>
#include <mem.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void near cantkillit(void)
{
    Puts(cantkill);
    Press_ENTER();
}

void Msg_Kill(long n)
{
    HMSG msgh;

    char *ctrl;
    size_t ctrl_len;

    XMSG msg;
    char temp[PATHLEN];

    UMSGID saveid, uidnum;
    long msgnum;
    long save_mn;

    if (n != -1)
        msgnum = n;
    else
    {
        RipClear();

        WhiteN();

        InputGets(temp, kill_which);

        if (eqstri(temp, eq))
            msgnum = last_msg;
        else
        {
            msgnum = atol(temp);


    TrackKillMsg(ctrl);

#endif


    saveid = MsgMsgnToUid(sq, last_msg);
    save_mn = last_msg;


    last_msg = MsgUidToMsgn(sq, saveid, UID_PREV);


    if (last_msg > MsgHighMsg(sq))
        last_msg = MsgHighMsg(sq);

    logit(log_kill, uidnum, usr.msg);
    Printf(kill_done, uidnum);
}

