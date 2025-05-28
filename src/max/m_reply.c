// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_reply.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)


#include "m_reply.h"
#include "max_msg.h"
#include "prog.h"
#include "trackm.h"
#include <ctype.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

};

static int near readmsgline(struct _mline *pml)
{
    char *bptr;
    int i;

    if (pml->pos)
    {
        memmove(pml->buf, pml->buf + pml->pos, pml->chars - pml->pos + 1);
        pml->chars -= pml->pos;
        pml->pos = 0;
    }

    bptr = pml->buf;
    for (;;)
    {


        while (*(byte *)bptr == (byte)'\x8d' || *bptr == '\x0a')
            ++bptr;


            pml->pos = pml->chars = 0;
        }

        i = (int)Read_Chars(pml->hmsg, pml->buf + pml->chars, MSGBUFLEN - pml->chars);
        if (i == 0)
            break;

        pml->buf[pml->chars += i] = '\0';
    }

    return pml->pos = bptr - pml->buf;
}

static int near Reply_Get_Area(struct _replyp *r, char *areaname)
{
    int gotarea;
    char temp[PATHLEN];
    BARINFO bi;

    strcpy(temp, areaname);

    gotarea = (*temp != 0);
    for (;;)
    {
        if (!gotarea)
        {
            RipClear();

            WhiteN();
            InputGets(temp, where_to_reply);
        }
        gotarea = FALSE;

        if (*temp == '?')
            ListMsgAreas(NULL, FALSE, FALSE);
        else if (!*temp || *temp == '=')
            return 1;
        else
        {
            MAH ma;
            HAREA tosq;

            memset(&ma, 0, sizeof ma);

            SetAreaName(r->toareaname, temp);
            if (eqstri(r->toareaname, usr.msg))
                return 1;


            CopyMsgArea(&mah, &ma);
            sq = tosq;
            DisposeMah(&ma);
            return 0;
        }
    }
}

int Msg_ReplyArea(char *areaname)
{
    char *ctrl, *p;

    long ctlen;
    int aborted, editrc, rc, i;
    int isnet, wasecho, wasnet;
    HMSG omsgh;
    XMSG omsg, nmsg;

    struct _replyp rp;

    memset(&rp, 0, sizeof rp);

    if ((omsgh = MsgOpenMsg(sq, MOPEN_READ, last_msg)) == NULL ||
        MsgReadMsg(omsgh, &omsg, 0L, 0L, NULL, 0L, NULL) == -1 || !CanSeeMsg(&omsg))
    {
        if (omsgh)
            MsgCloseMsg(omsgh);

        return (Msg_Enter());
    }

    rp.original = MsgMsgnToUid(sq, last_msg);


    wasecho = !!(mah.ma.attribs & MA_ECHO);
    wasnet = !!(mah.ma.attribs & MA_NET);


    *orig_msgid = '\0';

    ctlen = MsgGetCtrlLen(omsgh);
    ctrl = NULL;

    if (ctlen)
    {
        if ((ctrl = malloc((int)ctlen + 1)) == NULL)
            ctlen = 0;
        else
        {
            MsgReadMsg(omsgh, NULL, 0L, 0L, NULL, ctlen, ctrl);
            ctrl[(size_t)ctlen] = '\0';

            if ((p = MsgGetCtrlToken(ctrl, "MSGID")) != NULL)
            {

    CopyMsgArea(&rp.fromarea, &mah);
    rp.fromsq = sq;

    if (!areaname)
    {
        isnet = !!(mah.ma.attribs & MA_NET);
        strcpy(rp.toareaname, MAS(mah, name));
    }
    else
    {

        int got;


        got = Reply_Get_Area(&rp, areaname);

        if (got != 0)
        {
            else

            memset(&omsg.orig, 0, sizeof omsg.orig);


            if (*orig_msgid)
                ParseNNN(orig_msgid, &omsg.orig, FALSE);


                    m.hmsg = omsgh;
                    m.buf[m.chars = m.pos = 0] = '\0';

                    while (readmsgline(&m))
                    {


                            char *p;

                            p = strrchr(m.buf, '(');
                            if (p != NULL)
                            {
                                while (*++p && !isdigit(*p))
                                    ;
                                if (*p)
                                {

                            m.buf[m.pos] = ch;
                        }
                    }
                    free(m.buf);
                }
            }
        }
    }

    MsgCloseMsg(omsgh);


    if (omsg.attr & MSGPRIVATE || (areaname && isnet))
        nmsg.attr |= MSGPRIVATE;


    strcpy(nmsg.to, omsg.from);


    nmsg.dest = omsg.orig;


    isareply = TRUE;
    isachange = FALSE;

    rc = 0;

    if (GetMsgAttr(&nmsg, &mah, usr.msg, 0L, -1L) == -1)
        aborted = TRUE;
    else
    {
        editrc = Editor(&nmsg, NULL, 0L, NULL, &rp);

        isareply = FALSE;

        if (editrc == ABORT)
            aborted = TRUE;
        else
        {
            if (editrc == LOCAL_EDIT)
                aborted = FALSE;
            else
                aborted = SaveMsg(&nmsg, NULL, FALSE, 0L, FALSE, &mah, rp.toareaname, sq, NULL,
                                  rp.fromareaname, FALSE);


            omsgh = NULL;

            if (!areaname && !aborted &&
                (omsgh = MsgOpenMsg(rp.fromsq, MOPEN_RW,
                                    MsgUidToMsgn(rp.fromsq, rp.original, UID_EXACT))) != NULL &&
                MsgReadMsg(omsgh, &omsg, 0L, 0L, NULL, 0L, NULL) != -1)
            {

            TrackAfterReply(ctrl, last_msg, rp.fromsq);
#endif
        }
    }

    if (aborted)
    {
        Puts(msg_aborted);
        rc = -1;
    }

    if (ctrl)
        free(ctrl);

    if (areaname)
    {
        CopyMsgArea(&mah, &rp.fromarea);
        MsgCloseArea(sq);
        last_msg = MsgUidToMsgn(rp.fromsq, rp.original, UID_PREV);
    }

    DisposeMah(&rp.fromarea);
    sq = rp.fromsq;

    isareply = FALSE;

    return rc;
}
