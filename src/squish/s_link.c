// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_link.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#define NOVARS

#include "s_link.h"
#include "alc.h"
#include "dr.h"
#include "max.h"
#include "msgapi.h"
#include "prog.h"
#include "squish.h"
#include <ctype.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

static char *etn = NULL;

void Link_Messages(char *etname)
{
    etn = etname;

    S_LogMsg("#Linking messages");

    (void)printf("Linking areas:\n\n");
    Do_Echotoss(etname, Link_Area, TRUE, NULL);
    (void)printf("\n");
}

static void Link_Area(struct _cfgarea *ar, HAREA opensq)
{
    HAREA sq;

    NW(opensq);
    NW(config);


static void near LinkGetMsgid(char *s, dword *hash, dword *stamp)
{
    char *p;

    if ((p = strrchr(s, ' ')) != NULL)
        if (sscanf(p + 1, "%8" INT32_FORMAT "x", stamp) == 1)
            *hash = SquishHash(s + 7);
}


    mn = (ar->type & MSGTYPE_SDM) ? 2L : 1L;
    max = MsgHighMsg(sq);

    if (config.flag2 & FLAG2_LMSGID)
        ctrl_buf = malloc(MAX_CTRL_LINK);
    else
        ctrl_buf = NULL;

    for (nl = 0; mn <= max; mn++)
    {
        if ((mh = MsgOpenMsg(sq, MOPEN_READ, mn)) == NULL)
            continue;

        if (MsgReadMsg(mh, &msg, 0L, 0L, NULL, MAX_CTRL_LINK, ctrl_buf) == (dword)-1)
        {
            (void)MsgCloseMsg(mh);
            continue;
        }

        link[nl] = malloc(sizeof(struct _link));


        if (ctrl_buf && (s = MsgGetCtrlToken(ctrl_buf, "MSGID")) != NULL)
        {
            LinkGetMsgid(s, &link[nl]->msgid_hash, &link[nl]->msgid_stamp);
            MsgFreeCtrlToken(s);
        }

        if (ctrl_buf && (s = MsgGetCtrlToken(ctrl_buf, "REPLY")) != NULL)
        {
            LinkGetMsgid(s, &link[nl]->reply_hash, &link[nl]->reply_stamp);
            MsgFreeCtrlToken(s);
        }

        link[nl++]->delta = FALSE;

        if ((nl % 25) == 0 && (config.flag2 & FLAG2_QUIET) == 0)
            (void)printf("\b\b\b\b\b%" SIZET_FORMAT, nl);

        (void)MsgCloseMsg(mh);
    }

    if (ctrl_buf)
        free(ctrl_buf);

    return nl;
}


static void near LinkMsgid(HAREA sq, long nl, struct _link **link)
{
    UMSGID new_down, new_up;
    size_t lnk;
    int up;
    int i;

    qsort(link, (size_t)nl, sizeof(struct _link *), msgidcomp);

    if (!nl)
        return;

    for (lnk = 0; lnk < nl; lnk++)
    {

        if ((up = (int)msgidsearch(link, nl, link[lnk])) == -1)
            continue;


        for (i = 0; i < MAX_REPLY; i++)
            if (link[up]->downs[i] == new_down)
                break;


            for (i = 0; i < MAX_REPLY; i++)
                if (!link[up]->downs[i])
                {
                    link[up]->downs[i] = new_down;
                    break;
                }
        }
    }
}


            memmove(msg.replies, link[lnk]->downs, sizeof(UMSGID) * MAX_REPLY);

            if (config.flag2 & FLAG2_LMSGID)
            {
                int i;


static void near LinkIt(HAREA sq, struct _cfgarea *ar)
{
    struct _link **link;
    long nl;

    (void)printf("Linking area %-40s", ar->name);

    link = malloc((size_t)MsgNumMsg(sq) * sizeof(struct _link *));

    if (!link)
    {
        S_LogMsg("!Not enough memory to link area %s", ar->name);
        return;
    }

    (void)memset(link, '\0', (size_t)MsgNumMsg(sq) * sizeof(struct _link *));

    if ((config.flag2 & FLAG2_QUIET) == 0)
        (void)printf(" - Read -----");

    nl = LinkReadArea(sq, ar, link);

    if ((config.flag2 & FLAG2_QUIET) == 0)
        (void)printf("\b\b\b\b\b\b\b\b\b\bSort      ");

    if (nl)
    {
        if (config.flag2 & FLAG2_LMSGID)
            LinkMsgid(sq, nl, link);
        else
            LinkSubject(sq, nl, link);
    }

    if ((config.flag2 & FLAG2_QUIET) == 0)
        (void)printf("\b\b\b\b\b\b\b\b\b\bLink -----");

    LinkUpdateMsgs(sq, link, nl);
    free(link);

    (void)printf("\n");
}

static int _stdc msgcomp(const void *i1, const void *i2)
{
    struct _link **l1, **l2;
    char *subj1;
    char *subj2;
    int eq;

    l1 = (struct _link **)i1;
    l2 = (struct _link **)i2;

    subj1 = (*l1)->subj;
    subj2 = (*l2)->subj;

    if (toupper(subj1[0]) == 'R' && toupper(subj1[1]) == 'E' && subj1[2] == ':')
        subj1 += 4;

    if (toupper(subj2[0]) == 'R' && toupper(subj2[1]) == 'E' && subj2[2] == ':')
        subj2 += 4;

    eq = stricmp(subj1, subj2);

    if (eq)
        return eq;
    else
        return ((int)((*l1)->mnum - (*l2)->mnum));
}


static int _stdc umsgidcomp(const void *i1, const void *i2)
{
    long eq;

    eq = *(dword *)i1 - *(dword *)i2;

    return eq == 0 ? 0 : eq > 0 ? 1 : -1;
}

