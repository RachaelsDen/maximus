// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: t_add.c,v 1.2 2003/06/11 14:03:06 wesgarland Exp $";
#pragma on(unreferenced)

#include "trackp.h"

#ifdef MAX_TRACKER

char accomment_colon[] = "ACCOMMENT:";
extern char szTrk[];


        WhiteN();
        InputGetsL(szOwner, PATHLEN - 1, which_owner);

        if (!*szOwner)
            return FALSE;
        else if (eqstri(szOwner, qmark))
            TrackValidOwner(t, szOwner, to, TRUE);
        else if (TrackValidOwner(t, szOwner, to, FALSE))
            return TRUE;
        else
        {

            if (!PrivOK(PRM(track_privmod), FALSE))
            {
                Printf(trk_owner_not_accept, szOwner);
                Press_ENTER();
                continue;
            }

            sprintf(prompt, trk_ask_owner_quest, szOwner);

            if (GetListAnswer(yCN, NULL, useyforyes, 0, prompt) != 'Y')
                continue;

            sprintf(prompt, trk_enter_4char, szOwner);

            Input(to, INPUT_LB_LINE, 0, 4, prompt);

            if (!*to)
                continue;

            if (!TrkSetOwner(t, to, szOwner))
            {
                strcpy(szOwner, qmark);
                logit(log_err_setting_owner, to, szOwner);
            }

            Printf(trk_added_owner_as, szOwner, to);
            return TRUE;
        }
    }
}


int TrackInsertTracking(HAREA ha, dword msgnum, XMSG *pxmsg, int modify_actrack, int add_act,
                        char *actrack, int modify_audit, char *audit, int modify_comment,
                        char *comment)
{
    XMSG xmsg;
    char *txt, *ctrl;
    dword txt_len, ctrl_len;
    HMSG hm;
    int rc = FALSE;
    int len_audit = modify_audit ? strlen(audit) + 30 : 0;
    int len_comment = modify_comment && comment ? strlen(comment) : 0;


    MsgReadMsg(hm, pxmsg, 0L, 0L, NULL, 0L, NULL);


    txt_len = MsgGetTextLen(hm) + len_audit + 10;
    ctrl_len = MsgGetCtrlLen(hm) + (actrack ? strlen(actrack) : 0) + len_comment + 10;


            MsgReadMsg(hm, pxmsg, 0L, (size_t)txt_len, txt, (size_t)ctrl_len, ctrl);


            p = MsgGetCtrlToken(ctrl, actrack_colon);

            if (modify_actrack)
            {
                if (add_act && p)
                {
                    Puts(trk_msg_already_in_db);

                    MsgFreeCtrlToken(p);
                    free(ctrl);
                    free(txt);
                    return FALSE;
                }

                if (!add_act && !p)
                {
                    Puts(trk_msg_not_in_db);
                    free(ctrl);
                    free(txt);
                    return FALSE;
                }
            }

            if (modify_actrack)
            {
                if (add_act)
                {

                    strcpy(actrack, p + 9);
                    MsgRemoveToken(ctrl, actrack_colon);
                }
            }

            MsgFreeCtrlToken(p);


            if (modify_audit)
            {
                Add_Trailing(txt, '\r');
                sprintf(txt + strlen(txt), "\x01%s\r", audit);
            }


            rc = TRUE;
            free(ctrl);
        }

        free(txt);
    }

    MsgCloseMsg(hm);
    return rc;
}


    memset(&tmn, 0, sizeof tmn);

    strcpy(tmn.szTrackID, actrack);
    strcpy(tmn.to, to);
    strcpy(tmn.tl.szArea, name);
    tmn.tl.uid = uid;
    tmn.ts = TS_NEW;
    tmn.tp = TP_NORMAL;
    tmn.scDateWritten.msg_st = pxmsg->date_written;


        if (!*tmn.to)
            TrackValidOwner(t, pxmsg->to, tmn.to, FALSE);

        if ((rc = TrkAddMsg(t, &tmn)) != 0)
            logit(log_tracking, name, uid, actrack);
        else
        {
            logit(log_track_cantadd1, name, uid);
            logit(log_track_cantadd2);
        }

        TrackRelease(t);
    }

    return rc;
}


int TrackInsertMessage(HAREA ha, dword msgnum, TRK_OWNER to, char *out_actkludge)
{
    char inserted_audit[PATHLEN];
    char actrack[PATHLEN];
    XMSG xmsg;
    SCOMBO sc;
    int rc = FALSE;

    Get_Dos_Date(&sc);


    if (TrackInsertTracking(ha, msgnum, &xmsg, TRUE, TRUE, actrack, TRUE, inserted_audit, FALSE,
                            NULL))
    {
        rc = TrackInsertDB(actrack + 10, MAS(mah, name), to, MsgMsgnToUid(ha, msgnum), &xmsg);
    }


int TrackNeedToAdd(PMAH pmah, XMSG *pxmsg)
{
    TRK t;
    char *szTag;
    char szOwner[TRK_ASCII_OWNER_SIZE];
    int rc = TRUE;


    if (IsUserExcluded(pxmsg->from))
        return FALSE;

    if ((t = TrackGet()) == NULL)
        return FALSE;


void TrackAddMessage(PMAH pmah, XMSG *msg, char *kludges, HAREA ha)
{
    char *actrack = MsgGetCtrlToken(kludges, actrack_colon);


    if (!actrack || (pmah->ma.attribs & MA_AUDIT) == 0)
        return;

    TrackInsertDB(actrack + 9, PMAS(pmah, name), blank_str, MsgMsgnToUid(ha, MsgGetHighMsg(ha)),
                  msg);

    MsgFreeCtrlToken(actrack);
}


int TrackNeedToInsertRemoteMsg(PMAH pmah, XMSG *pxmsg, char *kludges)
{
    char *p;


    if (kludges && (p = MsgGetCtrlToken(kludges, actrack_colon)) != NULL)
    {
        MsgFreeCtrlToken(p);
        return FALSE;
    }

