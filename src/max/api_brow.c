// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: api_brow.c,v 1.2 2003/06/04 23:09:26 wesgarland Exp $";
#pragma on(unreferenced)

#define NO_MSGH_DEF

#include "alc.h"
#include "api_brop.h"
#include "api_sq.h"
#include "m_browse.h"
#include "max_area.h"
#include "mm.h"
#include "msgapi.h"
#include "old_msg.h"
#include "prog.h"
#include "scanbld.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

sword EXPENTRY MsgBrowseArea(BROWSE *b)
{
    SEARCH *s;
    int bcsf_ret;
    int ret;
    int x;


    if ((b->bflag & BROWSE_NEW) && (b->bflag & BROWSE_EXACT) && b->first->where == WHERE_TO)
    {

        for (s = b->first; s; s = s->next)
            if (b->first->where != WHERE_TO || (b->first->flag & SF_OR) == 0)
                break;

        if (s == NULL)
        {
            bcsf_ret = BrowseCheckScanFile(b);

            if (bcsf_ret <= 0)
                return bcsf_ret;

    for (ret = 0, b->msgn = b->bdata + 1; b->msgn <= MsgHighMsg(b->sq); b->msgn++)
    {
        if ((x = Browse_Scan_Message(b)) == -1)
        {

            ret = 0;
            break;
        }
    }

    return ret;
}

static int near BrowseCheckScanFile(BROWSE *b)
{
    SBREC *psh;
    SQIDX *siptr = NULL;
    NETADDR newdest;

    char temp[PATHLEN];
    char *block = NULL;

    UMSGID low_uid = 0L;
    int recsize, blsiz, got, in;
    int ret, sfd;


    if (b->bflag & BROWSE_NEW)
        low_uid = MsgMsgnToUid(b->sq, b->bdata);

    ret = 0;

    if (b->type == MSGTYPE_SDM)
    {
        sprintf(temp, scanfile_name, b->path);
        recsize = sizeof(SBREC);
        blsiz = SCAN_BLOCK_SBREC;
    }
    else if (b->type == MSGTYPE_SQUISH)
    {
#ifndef UNIX
        sprintf(temp, "%s.SQI", b->path);
#else
        sprintf(temp, "%s.sqi", b->path);
#endif

        recsize = sizeof(SQIDX);
        blsiz = SCAN_BLOCK_SQUISH;
    }
    else
        return 1;

    if (!block)
        return 1;


    if (b->type == MSGTYPE_SDM)
        lseek(sfd, sizeof(SBHDR), SEEK_SET);

    newdest = prm.address[0];

    while ((got = read(sfd, block, blsiz * recsize)) >= recsize)
    {
        got /= recsize;

        for (in = 0; in < got; in++)
        {
            b->msg.dest = newdest;

            if (b->type == MSGTYPE_SDM)
            {

                psh = (SBREC *)block + in;

                strcpy((char *)b->msg.to, (char *)psh->to);
                b->msg.attr = (long)psh->attr;

                if ((b->bflag & BROWSE_NEW) && (UMSGID)psh->msgnum < low_uid)
                    continue;
            }
            else if (b->type == MSGTYPE_SQUISH)
            {
                siptr = (SQIDX *)(block + (sizeof(SQIDX) * in));

                *(dword *)b->msg.to = siptr->hash;
                b->msg.attr = (siptr->hash & 0x80000000Lu) ? MSGREAD : 0;
                b->bflag |= BROWSE_HASH;

                if ((b->bflag & BROWSE_NEW) && siptr->umsgid < low_uid)
                    continue;
            }

            *b->msg.from = '\0';
            *b->msg.subj = '\0';


            if (BrowseMatchMessage(b, NULL, FALSE))
            {
                b->bflag &= ~BROWSE_HASH;

                b->msgn = MsgUidToMsgn(
                    b->sq, (b->type == MSGTYPE_SQUISH) ? siptr->umsgid : psh->msgnum, UID_EXACT);


    curtl = MsgGetTextLen(m);

#if defined(__MSDOS__) || defined(OS_2)


    curtl = (word)curtl;
#endif

    if (b->bflag & BROWSE_GETTXT)
        if (curtl <= 0L || (msgtxt = (char *)malloc((word)curtl + 10)) == NULL)
            b->bflag &= ~BROWSE_GETTXT;

    if ((b->bflag & BROWSE_GETTXT) == 0)
        curtl = 0L;

#ifdef OS_2

    if (MsgReadMsg(m, &b->msg, 0L, curtl, msgtxt == NULL ? (byte far *)NULL : (byte far *)msgtxt,
                   0L, NULL) == -1)
#else
    if (MsgReadMsg(m, &b->msg, 0L, curtl, msgtxt, 0L, NULL) == -1)
#endif
    {
        if (msgapierr == MERR_NOMEM)
            ret = -1;
    }
    else
    {
        if (msgtxt)
            msgtxt[(unsigned)curtl] = '\0';

        if (BrowseMatchMessage(b, msgtxt, TRUE))
        {
            b->matched++;
            b->m = m;

            if (b->Display_Ptr == NULL || (x = (*b->Display_Ptr)(b)) == -1)
                ret = -1;
            else if (x == 3)
                ret = 3;

            m = b->m;
        }
        else if (b->Idle_Ptr && (*b->Idle_Ptr)(b) == -1)
            ret = -1;
    }

    if (msgtxt)
        free(msgtxt);

    if (m)
        MsgCloseMsg(m);

    b->bflag = bfsave;

    return ret;
}

int near StringMatchInStr(char *msg, char *search)
{
    char *p;
    char *orig;

    p = stristr(msg, search);

    if (p == NULL)
        return FALSE;

    orig = stristr(msg, " * Origin:");

    if (orig && orig < p)
        return FALSE;
    else
        return (p != NULL);
}

int near HashMatchEqual(char *msg, char *search)
{
    return ((*(dword *)msg & 0x7fffffffLu) == SquishHash((byte *)search));
}

int near StringMatchEqual(char *msg, char *search) { return (eqstri(msg, search)); }

static int near BrowseMatchMessage(BROWSE *b, char *msgtxt, word checkaddr)
{
    typedef int(near * eq_func)(char *msg, char *search);
    eq_func equal;
    SEARCH *s;
    int doit = FALSE;
    int match;

    if (b->bflag & BROWSE_HASH)
        equal = HashMatchEqual;
    else if (b->bflag & BROWSE_EXACT)
        equal = StringMatchEqual;
    else
        equal = StringMatchInStr;


    for (s = b->first; s; s = s->next)
    {
        match = FALSE;

        if (s->txt && *s->txt)
        {
            if (s->where & WHERE_TO)
                if ((*equal)((char *)b->msg.to, s->txt))
                {

                    if ((mah.ma.attribs & MA_NET) == 0 || (b->bflag & BROWSE_EXACT) == 0 ||
                        !checkaddr || MsgToUs(&b->msg.dest))
                    {
                        match = TRUE;
                    }
                }

            if (s->where & WHERE_FROM)
                if ((*equal)((char *)b->msg.from, s->txt))
                    match = TRUE;

            if (s->where & WHERE_SUBJ)
                if ((*equal)((char *)b->msg.subj, s->txt))
                    match = TRUE;

            if ((s->where & WHERE_BODY) && (b->bflag & BROWSE_GETTXT) && msgtxt)
                if ((*equal)(msgtxt, s->txt))
                    match = TRUE;
        }

        if ((s->where & WHERE_ALL) == 0)
            match = TRUE;


        if (s->flag & SF_OR)
        {
            if (match && !doit)
                doit = TRUE;
        }
        else if (s->flag & SF_AND)
        {
            if (match && doit)
                doit = TRUE;
            else
                doit = FALSE;
        }
    }

    return doit && b->Match_Ptr && (*b->Match_Ptr)(b);
}
