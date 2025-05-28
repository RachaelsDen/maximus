// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: api_sdm.c,v 1.3 2003/06/11 14:03:06 wesgarland Exp $";
#pragma on(unreferenced)

#define MSGAPI_HANDLERS
#define MSGAPI_NO_OLD_TYPES

#include "api_sdm.h"
#include "alc.h"
#include "api_sdmp.h"
#include "apidebug.h"
#include "dr.h"
#include "max.h"
#include "msgapi.h"
#include "old_msg.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SDM_BLOCK 256
#define Mhd ((struct _sdmdata *)(mh->apidata))
#define MsghMhd ((struct _sdmdata *)(((HMSG)msgh)->ha->apidata))

static byte *hwm_from = "-=|ÿSquishMailÿ|=-";

// extern void far pascal DosSleep(dword);

HAREA MSGAPI SdmOpenArea(byte OS2FAR *name, word mode, word type)
{
    HAREA mh;
#ifdef __TURBOC__

            (void)strcpy(msg.from, hwm_from);
            (void)strcpy(msg.to, msg.from);
            (void)strcpy(msg.subj, "High wadda' mark");


        if (mn == (unsigned)-1)
        {
            msgapierr = MERR_NOENT;
            return NULL;
        }
    }
    else if (msgnum == MSGNUM_NEXT)
    {
        for (mn = 0; mn < (unsigned)mh->num_msg; mn++)
            if (Mhd->msgnum[mn] > (unsigned)mh->cur_msg)
            {
                msgnum = mh->cur_msg = (dword)Mhd->msgnum[mn];
                break;
            }


        for (mn = 0; mn < (unsigned)mh->num_msg; mn++)
            if (msgnum == Mhd->msgnum[mn])
                break;

        if (mn == (unsigned)mh->num_msg)
        {
            msgapierr = MERR_NOENT;
            return NULL;
        }
    }

    if (mode == MOPEN_CREATE)
    {

            if (!mh->locked)
            {

                    if (Mhd->msgnum && Mhd->msgnum_len)
                        pfree(Mhd->msgnum);

                    if (!_SdmRescanArea(mh))
                        return NULL;
                }
            }

            msgnum = ++mh->high_msg;


            if (mh->isecho && msgnum == 1)
                msgnum = mh->high_msg = 2;
        }
        else
        {

    if ((handle = sopen(msgname, filemode | O_BINARY | O_NOINHERIT, SH_DENYNONE,
                        S_IREAD | S_IWRITE)) == -1)
    {
        if (filemode & O_CREAT)
            msgapierr = MERR_BADF;
        else
            msgapierr = MERR_NOENT;

        _nopen_cheat = FALSE;
        return NULL;
    }

    _nopen_cheat = FALSE;

    mh->cur_msg = msgnum;

    if ((msgh = palloc(sizeof(*msgh))) == NULL)
    {
        (void)close(handle);
        msgapierr = MERR_NOMEM;
        return NULL;
    }

    (void)memset(msgh, '\0', sizeof(*msgh));
    msgh->fd = handle;

    if (mode == MOPEN_CREATE)
    {
        if (mh->num_msg + 1 >= Mhd->msgnum_len)
        {
            Mhd->msgnum = repalloc(Mhd->msgnum, (Mhd->msgnum_len += SDM_BLOCK) * sizeof(unsigned));

            if (!Mhd->msgnum)
            {
                pfree(msgh);
                (void)close(handle);
                msgapierr = MERR_NOMEM;
                return NULL;
            }
        }

            Mhd->msgnum[(size_t)(mh->num_msg++)] = (unsigned)msgnum;
        else
        {
            for (mn = 0; mn < (unsigned)mh->num_msg; mn++)
                if (Mhd->msgnum[mn] >= (unsigned)msgnum)
                    break;


            if (Mhd->msgnum[mn] == (unsigned)msgnum)
                ;
            else
            {

                (void)memmove(Mhd->msgnum + mn + 1, Mhd->msgnum + mn,
                              (size_t)((int)mh->num_msg - (int)mn) * sizeof(unsigned));

                Mhd->msgnum[mn] = (unsigned)msgnum;
                mh->num_msg++;
            }
        }
    }

    msgh->cur_pos = 0L;

    if (mode == MOPEN_CREATE)
        msgh->msg_len = 0;
    else
        msgh->msg_len = (dword)-1;

    msgh->ha = mh;
    msgh->id = MSGH_ID;
    msgh->ctrl = NULL;
    msgh->clen = -1;
    msgh->zplen = 0;

    msgapierr = MERR_NONE;


    if (msgh->ctrl == NULL && ((msg || ctxt || text) || !(msg || ctxt || text)))
        need_ctrl = TRUE;
    else
        need_ctrl = FALSE;

    realbytes = bytes;
    NW(realbytes);


    if (need_ctrl && (text == NULL || bytes < MAX_SDM_CLEN))
    {
        if ((text = fake_msgbuf = palloc(MAX_SDM_CLEN + 1)) == NULL)
        {
            msgapierr = MERR_NOMEM;
            return (dword)-1;
        }

        text[MAX_SDM_CLEN] = '\0';
        bytes = MAX_SDM_CLEN;
    }


        if (!msg || msgh->msgtxt_start != 0)
        {
            (void)lseek(msgh->fd,
                        (long)sizeof(struct _omsg) + (long)msgh->msgtxt_start + (long)offset,
                        SEEK_SET);

            msgh->cur_pos = offset;
        }

        got = farread(msgh->fd, text, (unsigned)bytes);


        if (got > 0 && !fake_msgbuf)
            msgh->cur_pos += (unsigned)got;
    }
    else
        got = 0;


            (void)memmove(text, newtext, (size_t)(bytes - (dword)(newtext - text)));

            got -= (int)(msgh->clen - 1u);
        }
    }


    if (ctxt && msgh->ctrl)
        (void)memmove(ctxt, msgh->ctrl, min(strlen(msgh->ctrl) + 1, (size_t)clen));

    if (fake_msgbuf)
    {
        pfree(fake_msgbuf);
        got = 0;
    }

    msgapierr = MERR_NONE;
    return (dword)got;
}

static sword MAPIENTRY SdmWriteMsg(HMSG msgh, word append, PXMSG msg, byte *text, dword textlen,
                                   dword totlen, dword clen, byte *ctxt)
{
    struct _omsg fmsg;
    byte *s;

    NW(totlen);

    if (clen == 0L || ctxt == NULL)
    {
        ctxt = NULL;
        clen = 0L;
    }

    if (InvalidMsgh(msgh))
        return -1;

    (void)lseek(msgh->fd, 0L, SEEK_SET);

    if (msg)
    {
        Convert_Xmsg_To_Fmsg(msg, &fmsg);

        if (farwrite(msgh->fd, (char *)&fmsg, sizeof(struct _omsg)) != (int)sizeof(struct _omsg))
        {
            msgapierr = MERR_NODS;
            return -1;
        }

        if (!append && msgh->clen <= 0 && msgh->zplen == 0)
        {
            statfd = msgh->fd;
            msgh->zplen = (word)WriteZPInfo(msg, WriteToFd, NULL);
        }
    }

    if (clen && ctxt)
    {

        if (!msg)
            (void)lseek(msgh->fd, (long)sizeof(struct _omsg) + (long)msgh->zplen, SEEK_SET);

        s = CvtCtrlToKludge(ctxt);

        if (s)
        {
            unsigned sl_s = (unsigned)strlen(s);
            int ret;

            ret = farwrite(msgh->fd, s, sl_s);
            MsgFreeCtrlToken(s);

            if (ret != (int)sl_s)
            {
                msgapierr = MERR_NODS;
                return -1;
            }
        }
    }

    if (append)
        (void)lseek(msgh->fd, 0L, SEEK_END);

    if (text)
        if (farwrite(msgh->fd, text, (unsigned)textlen) != (int)textlen)
        {
            msgapierr = MERR_NODS;
            return -1;
        }

    msgapierr = MERR_NONE;
    return 0;
}

static sword MAPIENTRY SdmKillMsg(HAREA mh, dword msgnum)
{
    dword hwm;
    byte temp[PATHLEN];
    unsigned mn;

    if (InvalidMh(mh))
        return -1;


    if (mn == (unsigned)mh->num_msg)
    {
        msgapierr = MERR_NOENT;
        return -1;
    }

    (void)sprintf(temp, sd_msg, Mhd->base, (unsigned)msgnum);

    if (unlink(temp) == -1)
    {
        msgapierr = MERR_NOENT;
        return -1;
    }

    mh->num_msg--;


    hwm = SdmGetHighWater(mh);


    if (mh->high_water != (dword)-1L)
        return (mh->high_water);

    if ((msgh = SdmOpenMsg(mh, MOPEN_READ, 1L)) == NULL)
        return 0L;

    if (SdmReadMsg(msgh, &msg, 0L, 0L, NULL, 0L, NULL) == (dword)-1 || !eqstr(msg.from, hwm_from))
    {
        mh->high_water = 0L;
    }
    else
        mh->high_water = (dword)msg.replyto;

    (void)SdmCloseMsg(msgh);

    return (mh->high_water);
}

static sword MAPIENTRY SdmSetHighWater(HAREA mh, dword hwm)
{
    if (InvalidMh(mh))
        return -1;


    if (hwm != mh->high_water)
        Mhd->hwm_chgd = TRUE;

    mh->high_water = hwm;
    return 0;
}

static dword MAPIENTRY SdmGetTextLen(HMSG msgh)
{
    dword pos;
    dword end;


    if (msgh->clen == (sdword)-1 && _Grab_Clen(msgh) == -1)
        return 0L;
    else if ((dword)msgh->msg_len > (dword)msgh->msgtxt_start)
        return (dword)(msgh->msg_len - msgh->msgtxt_start);
    else
        return 0L;
}

static dword MAPIENTRY SdmGetCtrlLen(HMSG msgh)
{

static sword near _SdmRescanArea(HAREA mh)
{
    FFIND *ff;
    byte temp[PATHLEN];
    unsigned mn, thismsg;

    mh->num_msg = 0;

    if ((Mhd->msgnum = palloc(SDM_BLOCK * sizeof(unsigned))) == NULL)
    {
        msgapierr = MERR_NOMEM;
        return FALSE;
    }

    Mhd->msgnum_len = SDM_BLOCK;

    (void)sprintf(temp, "%s*.msg", Mhd->base);

    if ((ff = FindOpen(temp, 0)) != 0)
    {
        mn = 0;

        do
        {

        qksort((int *)Mhd->msgnum, (unsigned)mh->num_msg);
    }

    return TRUE;
}

static void MSGAPI Init_Xmsg(PXMSG msg) { (void)memset(msg, '\0', XMSG_SIZE); }

static void MSGAPI Convert_Fmsg_To_Xmsg(struct _omsg *fmsg, PXMSG msg, word def_zone)
{
    NETADDR *orig, *dest;

    Init_Xmsg(msg);

    orig = &msg->orig;
    dest = &msg->dest;

    fmsg->to[sizeof(fmsg->to) - 1] = '\0';
    fmsg->from[sizeof(fmsg->from) - 1] = '\0';
    fmsg->subj[sizeof(fmsg->subj) - 1] = '\0';
    fmsg->date[sizeof(fmsg->date) - 1] = '\0';

    (void)strcpy(msg->from, fmsg->from);
    (void)strcpy(msg->to, fmsg->to);
    (void)strcpy(msg->subj, fmsg->subj);

    orig->zone = dest->zone = def_zone;
    orig->point = dest->point = 0;

    orig->net = (word)fmsg->orig_net;
    orig->node = (word)fmsg->orig;

    dest->net = (word)fmsg->dest_net;
    dest->node = (word)fmsg->dest;

    Get_Binary_Date(&msg->date_written, &fmsg->date_written, fmsg->date);
    Get_Binary_Date(&msg->date_arrived, &fmsg->date_arrived, fmsg->date);

    (void)strcpy(msg->__ftsc_date, fmsg->date);

    msg->utc_ofs = 0;

    msg->replyto = fmsg->reply;
    msg->replies[0] = fmsg->up;
    msg->attr = (dword)fmsg->attr;



    if (orig->point)
    {
        fmsg->times = orig->point;
        fmsg->cost = ~fmsg->times;
    }
}

int MAPIENTRY WriteZPInfo(PXMSG msg, void(MAPIENTRY *wfunc)(byte OS2FAR *str), byte OS2FAR *kludges)
{
    byte temp[PATHLEN];
    byte *null = "";
    int bytes = 0;

    if (!kludges)
        kludges = null;

    if ((msg->dest.zone != mi.def_zone || msg->orig.zone != mi.def_zone) &&
        !stristr(kludges, "\x01INTL"))
    {
        (void)sprintf(temp, "\x01INTL %u:%u/%u %u:%u/%u\r", (unsigned)msg->dest.zone,
                      (unsigned)msg->dest.net, (unsigned)msg->dest.node, (unsigned)msg->orig.zone,
                      (unsigned)msg->orig.net, (unsigned)msg->orig.node);

        (*wfunc)(temp);
        bytes += (int)strlen(temp);
    }

    if (msg->orig.point && !strstr(kludges, "\x01"
                                            "FMPT"))
    {
        (void)sprintf(temp,
                      "\x01"
                      "FMPT %u\r",
                      (unsigned)msg->orig.point);
        (*wfunc)(temp);
        bytes += (int)strlen(temp);
    }

    if (msg->dest.point && !strstr(kludges, "\x01"
                                            "TOPT"))
    {
        (void)sprintf(temp,
                      "\x01"
                      "TOPT %u\r",
                      (unsigned)msg->dest.point);
        (*wfunc)(temp);
        bytes += (int)strlen(temp);
    }

    return bytes;
}

static void MAPIENTRY WriteToFd(byte OS2FAR *str) { (void)farwrite(statfd, str, strlen(str)); }

static void near Get_Binary_Date(union _stampu *todate, union _stampu *fromdate, byte *asciidate)
{
#ifdef HCC

    ASCII_Date_To_Binary(asciidate, (union stamp_combo *)todate);
#else
    if (fromdate->date.da == 0 || fromdate->date.da > 31 || fromdate->date.yr < 7 ||
        fromdate->time.hh > 23 || fromdate->time.mm > 59 ||
