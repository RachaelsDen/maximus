// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: t_qwk.c,v 1.1.1.1 2002/10/01 17:53:15 sdudley Exp $";
#pragma on(unreferenced)

#include "api_brow.h"
#include "qwk.h"
#include "trackp.h"

#ifdef MAX_TRACKER

extern char szTrk[];
static char szLeftAry[] = "[{";
static char szRightAry[] = "]}";


void TrackAddQWKFirst(TRK_MSG_NDX *ptmn, int *pdo_we_own, char *blpos, char *ctrl)
{
    int real_owner;
    TRK t;

    if (!ctrl)
        return;


    if (TrackAreWeOwner(ctrl, ptmn, &real_owner))
    {
        *pdo_we_own = TRUE;


        sprintf(blpos,
                "^!> ACTrack: %s" QWK_EOL_STR
                "^!> Status: %c %c New; %c %c Open; %c %c Working; %c %c Closed" QWK_EOL_STR
                    QWK_EOL_STR,
                ptmn->szTrackID, szLeftAry[ptmn->ts == TS_NEW], szRightAry[ptmn->ts == TS_NEW],
                szLeftAry[ptmn->ts == TS_OPEN], szRightAry[ptmn->ts == TS_OPEN],
                szLeftAry[ptmn->ts == TS_WORKING], szRightAry[ptmn->ts == TS_WORKING],
                szLeftAry[ptmn->ts == TS_CLOSED], szRightAry[ptmn->ts == TS_CLOSED]);
    }
}

void TrackAddQWKTail(TRK_MSG_NDX *ptmn, char *blpos, char *ctrl)
{
    extern char accomment_colon[];
    char *comment = NULL;

    if (ctrl)
        comment = MsgGetCtrlToken(ctrl, accomment_colon);

    sprintf(
        blpos,
        QWK_EOL_STR
        "^!> Owner: %s" QWK_EOL_STR
        "^!> Prty: %c %c Notify; %c %c Low; %c %c Normal; %c %c Urgent; %c %c Critical" QWK_EOL_STR
        "^!> Comment: [%-62.62s]" QWK_EOL_STR "^!> Discard reply text [ ]" QWK_EOL_STR,
        ptmn->to, szLeftAry[ptmn->tp == TP_NOTIFY], szRightAry[ptmn->tp == TP_NOTIFY],
        szLeftAry[ptmn->tp == TP_LOW], szRightAry[ptmn->tp == TP_LOW],
        szLeftAry[ptmn->tp == TP_NORMAL], szRightAry[ptmn->tp == TP_NORMAL],
        szLeftAry[ptmn->tp == TP_URGENT], szRightAry[ptmn->tp == TP_URGENT],
        szLeftAry[ptmn->tp == TP_CRIT], szRightAry[ptmn->tp == TP_CRIT],
        comment ? comment + 11 : blank_str);

    if (comment)
        MsgFreeCtrlToken(comment);
}


    if ((t = TrackGet()) == NULL)
        return;

    if (strncmp(actinfo + 4, "ACTrack: ", 9) == 0)
    {
        strncpy(acbuf, actinfo + 13, 16);
        acbuf[16] = 0;

        Printf(trk_got_actrack, acbuf);

        {
            if (!TrkLookupMsg(t, acbuf, NULL, NULL, NULL, &pqti->tmn))
            {
                Printf(trk_err_msg_notfound, acbuf);

                *pqti->tmn.szTrackID = 0;
            }
        }
    }
    else
    {
        if (!*pqti->tmn.szTrackID)
        {
            Puts(trk_err_uploading);
        }
        else if (strncmp(actinfo + 4, "Status: ", 8) == 0)
        {
            TRK_STATUS tsOld = pqti->tmn.ts;


            while (acbuf[len = strlen(acbuf) - 1] == ' ')
                acbuf[len] = 0;


            if (actinfo[12] == 'x' || actinfo[12] == 'X')
                pqti->tmn.tp = TP_NOTIFY;
            else if (actinfo[24] == 'x' || actinfo[24] == 'X')
                pqti->tmn.tp = TP_LOW;
            else if (actinfo[33] == 'x' || actinfo[33] == 'X')
                pqti->tmn.tp = TP_NORMAL;
            else if (actinfo[45] == 'x' || actinfo[45] == 'X')
                pqti->tmn.tp = TP_URGENT;
            else if (actinfo[57] == 'x' || actinfo[57] == 'X')
                pqti->tmn.tp = TP_CRIT;

            if (pqti->tmn.tp != tpOld)
                Printf(trk_new_priority, TrkGetPriority(t, &pqti->tmn));
        }
        else if (strncmp(actinfo + 4, "Discard ", 8) == 0)
        {


            if (actinfo[24] == 'x' || actinfo[24] == 'X')
                pqti->kill_after = TRUE;
        }
        else
        {
            Printf(trk_bad_cmd, end - actinfo, end - actinfo, actinfo);
        }
    }

    TrackRelease(t);
    return;
}


    if (!*pqti->tmn.szTrackID)
        return FALSE;

    if (!TrackAreWeOwnerOfActrack(pqti->tmn.szTrackID, NULL, NULL))
    {
        Puts(trk_admin_noaccess);
        return FALSE;
    }

    if ((t = TrackGet()) == NULL)
        return FALSE;

    if (!TrkLookupMsg(t, pqti->tmn.szTrackID, NULL, NULL, NULL, &tmnOld))
        Printf(trk_bad_old_id, pqti->tmn.szTrackID);

    if (!TrkUpdateMsg(t, &tmnOld, &pqti->tmn))
        Printf(trk_err_updating_db, pqti->tmn.szTrackID);
    else
        Printf(trk_info_updated, pqti->tmn.szTrackID);

