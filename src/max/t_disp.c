// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: t_disp.c,v 1.1.1.1 2002/10/01 17:53:13 sdudley Exp $";
#pragma on(unreferenced)

#define MAX_LANG_m_area
#include "trackp.h"

#ifdef MAX_TRACKER

extern char szTrk[];


static void near TrackDisplayStatus(TRK_MSG_NDX *ptmn, int update_status)
{
    TRK t;
    char szOwner[PATHLEN];

    if ((t = TrackGet()) == NULL)
        return;

    if (!TrkGetOwner(t, ptmn->to, szOwner))
        strcpy(szOwner, ptmn->to);

    Printf(trk_msg_info, " " + !(usr.bits & BITS_FSR), TrkGetStatus(t, ptmn),
           TrkGetPriority(t, ptmn), szOwner, " " + !(usr.bits & BITS_FSR));


    if (update_status)
        TrackOwnerReadMsg(t, ptmn);

    TrackRelease(t);
}


    if (TrackNeedToInsertRemoteMsg(pmah, pxmsg, kludges))
    {
        char add_kludge[PATHLEN];
        new_kludges = malloc((kludges ? strlen(kludges) : 0) + PATHLEN);

        if (!new_kludges)
            logit(log_trk_kludges);


            kludges = new_kludges;
        }
    }

    if (TrackAreWeOwner(kludges, &tmn, &update_status))
    {
        Goto(row, col);
        Puts(colour);

        TrackDisplayStatus(&tmn, update_status);
        Puts(msg_text_col);
        Putc('\n');
    }

