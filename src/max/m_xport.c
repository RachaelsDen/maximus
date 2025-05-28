// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_xport.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)


#include "max_msg.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef UNIX
#include <errno.h>
#endif

void Msg_Xport(void)
{
    FILE *out;
    HMSG hmsg;
    XMSG msg;
    word n;

    dword msgnum;

    char temp[PATHLEN];

    RipClear();

    if (!GetMsgNum(xport_which, &msgnum))
        return;

    if ((hmsg = MsgOpenMsg(sq, MOPEN_READ, msgnum)) == NULL ||
        MsgReadMsg(hmsg, &msg, 0L, 0L, NULL, 0L, NULL) == -1 || !CanSeeMsg(&msg))
    {
        if (hmsg)
            MsgCloseMsg(hmsg);

        return;
    }

    InputGets(temp, xport_where);

    if (!*temp || (out = shfopen(temp, fopen_append, O_WRONLY | O_APPEND | O_NOINHERIT)) == NULL)
    {
        if (*temp)
            Printf(cantopen + 1, temp, errno);

        MsgCloseMsg(hmsg);
        return;
    }

    Puts(xporting);


    MsgBodyToFile(hmsg, out, FALSE, FALSE, blank_str, MRL_QEXP);

