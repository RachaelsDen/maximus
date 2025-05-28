// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_for.c,v 1.2 2003/06/11 14:03:06 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_main

#include "m_for.h"
#include "max_msg.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int near Fwd_Get_Parms(struct _fwdp *fp);
static int near Read_Bomb_File(XMSG *msg);
static int _stdc near mprintf(HMSG sq, char *fmt, ...);
static int near mputs(HMSG sq, char *txt, int len);

static int near Read_Bomb_File(XMSG *msg)
{
    char temp[PATHLEN];
    char word[PATHLEN];
    int wn;

    static FILE *bombfile = NULL;

    if (bombfile == NULL)
    {
        Putc('\n');

        InputGets(temp, get_route_file);

        if (!*temp)
            return FALSE;

        if ((bombfile = shfopen(temp, fopen_read, O_RDONLY)) == NULL)
        {
            Printf(iseenoxhere, temp);
            return FALSE;
        }
    }

    while (fgets(temp, PATHLEN - 1, bombfile))
    {
        Trim_Line(temp);

        if (!*temp)
            continue;

        *netnode = '\0';
        *msg->to = '\0';

        getword(temp, word, cmd_delim, wn = 1);

        while (*word)
        {
            if (!*msg->to)
            {
                strcpy(msg->to, fancier_str(Strip_Underscore(word)));

                if (mah.ma.attribs & MA_NET)
                    Get_FidoList_Name(msg, netnode, PRM(fidouser));
            }
            else if (isdigit(*word))
            {
                strcpy(netnode, word);

                MaxParseNN(netnode, &msg->dest);

                strcpy(netnode, Address(&msg->dest));
            }
            else if (*word == '-')
            {
                word[1] = (char)toupper(word[1]);

                switch (word[1])
                {
                case 'C':
                    msg->attr |= MSGCRASH;
                    break;
                case 'D':
                    msg->attr |= (MSGCRASH | MSGHOLD);
                    break;
                case 'H':
                    msg->attr |= MSGHOLD;
                    break;
                case 'N':
                    break;
                default:
                    Printf(huh, word);
                    break;
                }
            }
            else
                Printf(huh, word);

            getword(temp, word, cmd_delim, ++wn);
        }


    if (f->bomb && !(GEPriv(realpriv(), prm.msg_fromfile) && local))
    {
        Puts(you_dont_have_access);
        return -1;
    }

    if (eqstri(p, eq))
        f->msgnum = last_msg;
    else
    {
        f->msgnum = atol(temp);


    f->original = MsgMsgnToUid(sq, f->msgnum);

    if (f->msgnum == 0)
        return -1;

    return 0;
}

static int near Fwd_Get_Area(struct _fwdp *f)
{
    char temp[PATHLEN];
    BARINFO bi;

    do
    {
        InputGets(temp, where_to_fwd);

        switch (*temp)
        {
        case '?':
            ListMsgAreas(NULL, FALSE, FALSE);
            break;

        default:
            SetAreaName(f->toname, temp);

            if (eqstri(f->toname, usr.msg))
            {
            case '\0':
            case '=':
                CopyMsgArea(&f->toar, &mah);
                strcpy(f->toname, usr.msg);
                f->tosq = sq;
                break;
            }

            memset(&f->toar, 0, sizeof f->toar);

            if (!ReadMsgArea(ham, f->toname, &f->toar) ||
                !ValidMsgArea(NULL, &f->toar, VA_VAL | VA_PWD, &bi) ||
                (f->tosq = MaxOpenArea(&f->toar)) == NULL)
            {
                AreaError(msgapierr);

                if (f->toar.heap)
                    DisposeMah(&f->toar);

                return -1;
            }
            break;
        }
    } while (*temp == '?');

    return 0;
}

static void near Fwd_Header(struct _fwdp *f, HMSG th)
{

    if (!eqstri(f->fmsg.from, f->tmsg.from))
        mprintf(th, orig_from, f->fmsg.from, Address(&f->fmsg.orig));

    mprintf(th, orig_to, f->fmsg.to, Address(&f->fmsg.dest));


        if (got > strlen(buf))
        {
            got = strlen(buf) + 1;
            breakout = TRUE;
        }


        buf[FWDBUFSIZE] = '\0';

        if ((f->toar.ma.attribs & MA_SHARED) == 0)
            mputs(th, buf, got);
        else
        {
            p = buf;

            for (p = buf; (p = stristr(p, "---")) != NULL && p < buf + FWDBUFSIZE - FWD_OVERLAP;
                 p = found + 1)
            {
                found = p;


                if ((p = strchr(p, '\r')) == NULL)
                    continue;

                while (*p == '\r' || *p == '\n' || *p == '\x8d')
                    p++;

                if (p[0] == ' ' && p[2] == ' ' && p[3] == 'O' && p[4] == 'r' && p[5] == 'i' &&
                    p[6] == 'g' && p[7] == 'i' && p[8] == 'n' && p[9] == ':')
                {
                    mputs(th, buf, found - 1 - buf);
                    return;
                }

    }
}

static void near Forward_Add_Trailer(struct _fwdp *f, HMSG th)
{
    char temp[MAX_OTEAR_LEN];

    if (f->toar.ma.attribs & MA_ECHO)
    {
        GenerateOriginLine(temp, &f->toar);
        mputs(th, temp, strlen(temp));
    }
}

static void near Forward_One(struct _fwdp *f, struct _fwdp *fp)
{
    UMSGID to_id;
    static SCOMBO last_fwd;
    SCOMBO now;
    HMSG th;
    char *buf;
    byte *kludge;
    int zero;

    Get_Dos_Date(&now);


    kludge = GenerateMessageKludges(&f->tmsg, &mah, NULL);

    MsgWriteMsg(th, FALSE, &f->tmsg, NULL, 0L, MsgGetTextLen(f->fh) + FWD_SAFE,
                kludge ? strlen(kludge) + 1 : 0L, kludge);

    Fwd_Header(f, th);
    Forward_Body(f, th, buf);
    Forward_Add_Trailer(f, th);


    zero = 0;
    MsgWriteMsg(th, TRUE, NULL, (char *)&zero, 1L, 0L, 0L, NULL);

    free(buf);
    MsgCloseMsg(th);

    to_id = UIDnum(MsgHighMsg(f->tosq));
    logit(log_fwd, f->tmsg.to, f->toname, to_id);

    if (!f->bomb && !fp)
        Puts("\n\n");

    Printf(fwd_to, f->tmsg.to, Address(&f->tmsg.dest), to_id);

    vbuf_flush();
}

static void near Fwd_Message(struct _fwdp *f, struct _fwdp *fp)
{
    if (!fp)
    {
        Blank_Msg(&f->tmsg);

    if (f->kill)
        MsgKillMsg(sq, MsgUidToMsgn(sq, f->original, UID_EXACT));
}

void Msg_Forward(struct _fwdp *fp)
{
    struct _fwdp *fwdp;
    UMSGID uid;
    dword mn;


    if (fp)
        fwdp = fp;
    else
    {
        if ((fwdp = malloc(sizeof(struct _fwdp))) == NULL)
            return;

        memset(fwdp, 0, sizeof *fwdp);
    }


    if ((fp || Fwd_Get_Parms(fwdp) == 0) && Fwd_MsgIsOkay(fwdp) == 0 &&
        (fp || Fwd_Get_Area(fwdp) == 0))
    {
        if (!AreaIsReadOnly(&fwdp->toar))
        {

        if (fwdp->tosq && fwdp->tosq != sq)
            MsgCloseArea(fwdp->tosq);

        FwdCleanup(fwdp);
    }

    DisposeMah(&fwdp->toar);

