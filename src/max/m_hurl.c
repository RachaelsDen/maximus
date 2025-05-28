// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_hurl.c,v 1.1.1.1 2002/10/01 17:52:43 sdudley Exp $";
#pragma on(unreferenced)


#include "max_msg.h"
#include "prog.h"
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HURL 4096

static sword near DoTheHurlThing(HMSG omh, dword msgnum, byte *aname)
{
    BARINFO bi;
    HMSG nmh;
    HAREA nma;
    dword dwCtrlLen;
    char *szCtrl = NULL;

    XMSG msg;
    MAH to_mah = {0};
    long bytes;

    char input[PATHLEN];
    char *msgb;

    sword hurl_to_same;
    long got;

    if (MsgReadMsg(omh, &msg, 0L, 0L, NULL, 0L, NULL) == -1 || !CanKillMsg(&msg))
        return -1;

    do
    {
        InputGets(input, which_area);

        if (eqstri(input, qmark))
            ListMsgAreas(NULL, FALSE, FALSE);
    } while (eqstri(input, qmark));

    if (!*input)
        return -1;

    SetAreaName(aname, input);

    if (!ReadMsgArea(ham, aname, &to_mah) || !ValidMsgArea(NULL, &to_mah, VA_VAL | VA_PWD, &bi))
    {
        Puts(areadoesntexist);
        return -1;
    }

    if (AreaIsReadOnly(&to_mah))
    {
        DisposeMah(&to_mah);
        return -1;
    }


            msg.replyto = 0L;
            memset(msg.replies, '\0', sizeof(UMSGID) * MAX_REPLY);


            if ((dwCtrlLen = MsgGetCtrlLen(omh)) != 0)
            {
                if ((szCtrl = malloc((size_t)dwCtrlLen)) == NULL)
                    dwCtrlLen = 0;
                else
                    MsgReadMsg(omh, NULL, 0L, 0L, NULL, dwCtrlLen, szCtrl);
            }


            if (szCtrl)
                free(szCtrl);


    last = MsgMsgnToUid(sq, last_msg);

    if (MsgKillMsg(sq, MsgUidToMsgn(sq, uid, UID_EXACT)) != 0)
    {
        Puts(cantkill);
        return;
    }

    if ((newlast = MsgUidToMsgn(sq, last, UID_PREV)) != 0)
        last_msg = newlast;


    if (*MAS(mah, echo_tag))
        AddToEchoToss(MAS(mah, echo_tag));

    logit(log_hurl, MAS(mah, name), UIDnum(msgnum), aname);
    return;
}
