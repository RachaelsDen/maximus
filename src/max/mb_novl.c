// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mb_novl.c,v 1.1.1.1 2002/10/01 17:52:12 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_m_browse

#include "dr.h"
#include "m_browse.h"
#include "max_msg.h"
#include "prog.h"
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <share.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int idling;
int last_title;
struct _lrptr *lrptr;

static int near Browse_Scan_This_Area(BROWSE *b, PMAH pmah, BARINFO *pbi);


void Lmsg_Set(BROWSE *b, long msgn)
{
    struct _lrptr *lp;


    if (lp == NULL)
    {
#ifdef MIKE_GOVE
        logit("@Lmsg_Set - Area %s added to lrptr list", b->path);
#endif

        if ((lp = malloc(sizeof(struct _lrptr))) == NULL)
            return;

        memset(lp, '\0', sizeof(struct _lrptr));

        lp->next = lrptr;
        lp->type = mah.ma.type;
        lrptr = lp;
    }
#ifdef MIKE_GOVE
    else
    {
        logit("@Lmsg_Set - Area %s already in lrptr list", b->path);
    }
#endif

    if (lp->path == NULL)
        lp->path = strdup(b->path);

#ifdef MIKE_GOVE
    logit("@Lmsg_Set - Set pointer to %ld", msgn);
#endif
    lp->msgn = msgn;
}

void Lmsg_Update(BROWSE *b)
{
    int using_sq;
    HAREA lsq;
    struct _lrptr *lp;

    NW(b);

#ifdef MIKE_GOVE
    logit("@Lmsg_Update");
#endif


        if (eqstri(lp->path, MAS(mah, path)) && sq)
        {
            using_sq = TRUE;
            lsq = sq;
        }
        else
        {
            using_sq = FALSE;

            if ((lsq = MsgOpenArea(lp->path, MSGAREA_NORMAL, lp->type)) == NULL)
                continue;
        }


    Lmsg_Free();
}

int OkToFixLastread(BROWSE *b)
{
    return ((b->bflag & (BROWSE_NEW | BROWSE_ALL | BROWSE_FROM)) && b->first->txt == NULL &&
            b->first->next == NULL && b->first->attr == 0L &&
            (b->first->flag & (SF_NOT_ATTR | SF_HAS_ATTR)) == 0);
}

static char whirlygig[] = "|/-\\";
static int whirly = FALSE;

int List_Idle(BROWSE *b)
{
    static int gig = 0;
    static int ctr = 0;

    NW(b);


    if ((b->bflag & BROWSE_ACUR) == 0)
    {
        Rev_Up();
        Printf(srchng, (colour % 7) + 9, aname);
        last_title = TRUE;
        vbuf_flush();
    }

    Mdm_check();

    if (halt())
        return -1;

    return 0;
}

        Puts("\r" CLEOL);
    else if (!hasRIP())
    {

        for (x = strlen(srchng) + 11; x--;)
            Putc(' ');

        Putc('\r');
    }

    whirly = FALSE;
}


    if ((b->bflag & BROWSE_QWK) == 0)
        logit(log_start_browse);

    if ((*b->Begin_Ptr)(b) == -1)
        return -1;

    ret = 0;
    stop = FALSE;


            if ((rc = (*b->Status_Ptr)(b, MAS(ma, name), colour++)) == -1)
            {
                ret = -1;
                stop = TRUE;
                break;
            }



    if ((*b->End_Ptr)(b) == -1)
    {
        ret = -1;
        stop = TRUE;
    }

    if (b->matched == 0 && !stop)
    {
        if ((b->bflag & (BROWSE_READ | BROWSE_EXACT)) == (BROWSE_READ | BROWSE_EXACT))
            Display_File(0, NULL, PRM(nomail));
        else
        {
            Puts(br_notfound);
            vbuf_flush();
        }
    }

    Lmsg_Free();

    return ret;
}

#ifdef __MSC__
#pragma optimize("", on)
#endif

static int near Browse_Scan_This_Area(BROWSE *b, PMAH pmah, BARINFO *pbi)
{
        }


            if (wc_len && strnicmp(PMAS(pmah, name), b->wildcard, wc_len) != 0)
                return FALSE;
        }
        else if (b->bflag & BROWSE_AWLD)
        {
            if (!BrowseWCMatch(b->wildcard, PMAS(pmah, name)))
                return FALSE;
        }
        else if (b->bflag & BROWSE_ALNT)
        {
            if (pmah->ma.attribs & (MA_ECHO | MA_CONF))
                return FALSE;
        }
    }


    return (ValidMsgArea(NULL, pmah, VA_NOVAL | VA_PWD | VA_EXTONLY, pbi));
}

int Match_All(BROWSE *b) { return (CanSeeMsg(&b->msg)); }

int List_End(BROWSE *b)
{
    NW(b);

    if (last_title)
        Puts(space_over);

    Rev_Up();

    return 0;
}
