// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: t_kill.c,v 1.1.1.1 2002/10/01 17:53:13 sdudley Exp $";
#pragma on(unreferenced)

#include "trackp.h"

#ifdef MAX_TRACKER

extern char szTrk[];


int TrackKillMsg(char *ctrl)
{
    char *actrack = MsgGetCtrlToken(ctrl, actrack_colon);
    TRK t;

    if (!actrack)
        return FALSE;

    if ((t = TrackGet()) != NULL)
    {
        TRK_MSG_NDX tmn;

        if (TrkLookupMsg(t, actrack + 9, NULL, NULL, NULL, &tmn))
        {
            if (!TrkDeleteMsg(t, &tmn))
                Printf(trk_err_removing, tmn.szTrackID);
        }

        TrackRelease(t);
    }

    MsgFreeCtrlToken(actrack);
    return TRUE;
}

