// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_change.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)


#include "max_msg.h"
#include "node.h"
#include "prog.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int Msg_Change_Err(void);

int Msg_Change(void)
{
    char *ctrl_buf = NULL;
    unsigned ctrl_len;
    NETADDR *dest;
    HMSG msgh = NULL;
    NFIND *nf;

    XMSG msg;

    long lmsg;
    long hwm;

    word aborted;
    word charge_user;
    sword res;
    word cost;

    lmsg = *linebuf ? atol(linebuf) : last_msg;
    *linebuf = '\0';
    *orig_msgid = '\0';

    if ((msgh = MsgOpenMsg(sq, MOPEN_READ, lmsg)) == NULL ||
        MsgReadMsg(msgh, &msg, 0L, 0L, NULL, 0L, NULL) == (unsigned long)-1L ||
        !(eqstri(msg.from, usr.name) || eqstri(msg.from, usr.alias) || mailflag(CFLAGM_ATTRANY)))
    {
        aborted = Msg_Change_Err();
        goto Done;
    }


            RemoveFromCtrl(ctrl_buf, "MSGID:");
            RemoveFromCtrl(ctrl_buf, "INTL");
            Strip_Trailing(ctrl_buf, '\x01');
        }
    }


    hwm = MsgGetHighWater(sq);


        if (!mailflag(CFLAGM_ATTRANY) || GetyNAnswer(change_any, 0) != YES)
        {
            aborted = TRUE;
            goto Done;
        }
    }


    if (lmsg <= hwm)
        MsgSetHighWater(sq, lmsg - 1);


    msg.attr &= ~(MSGREAD | MSGSENT | MSGSCANNED);
    msg.attr |= MSGLOCAL;

    Add_Message_Date(&msg);

    dest = &msg.dest;

    if (mah.ma.attribs & MA_NET)
        strcpy(netnode, Address(dest));
    else
        *netnode = '\0';

    if (GetMsgAttr(&msg, &mah, usr.msg, lmsg, -1L) == -1)
    {
        aborted = TRUE;
        goto Done;
    }

    isareply = FALSE;
    isachange = TRUE;

    res = Editor(&msg, msgh, lmsg, ctrl_buf, NULL);

    isachange = FALSE;

    MsgCloseMsg(msgh);
    msgh = NULL;

    if (res == ABORT)
    {
        aborted = TRUE;
        goto Done;
    }

    if (res == LOCAL_EDIT)
        aborted = FALSE;
    else
        aborted = SaveMsg(&msg, NULL, FALSE, lmsg, TRUE, &mah, usr.msg, sq, ctrl_buf, NULL, FALSE);


    if (!charge_user && !aborted && (mah.ma.attribs & MA_NET))
    {
        if ((nf = NodeFindOpen(dest)) != NULL)
        {
            cost = nf->found.cost;

            if (cost)
            {
                Printf(balance_adjusted, cost);

                if (usr.debit >= cost)
                    usr.debit -= cost;
                else
                    usr.debit = 0;
            }

            NodeFindClose(nf);
        }
    }

Done:

    if (ctrl_buf)
        free(ctrl_buf);

    if (msgh)
        MsgCloseMsg(msgh);

    if (aborted)
        Puts(msg_aborted);

    return (aborted ? -1 : 0);
}

static int Msg_Change_Err(void)
{
    Display_File(0, NULL, "%sCHG_NO", PRM(misc_path));
    return TRUE;
}
