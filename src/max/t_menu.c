// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: t_menu.c,v 1.1.1.1 2002/10/01 17:53:14 sdudley Exp $";
#pragma on(unreferenced)

#include "trackp.h"

static void near TrackMenuInsert(void);

#ifdef MAX_TRACKER

extern char szTrk[];


        TrackMakeACAUDIT(comment, trk_msg_audit_str, ptmn->to, usrname);

        TrackInsertTracking(sq, msgnum, NULL, FALSE, FALSE, NULL, TRUE, comment, FALSE, NULL);
    }
}


static void near TrackModStatus(TRK t, TRK_MSG_NDX *ptmn, dword msgnum, HAREA ha)
{
    TRK_MSG_NDX tmnNew = *ptmn;
    char prompt[PATHLEN];
    char *szDefault = trk_status_def;
    char *szStatusKeys = trk_status_keys;
    int ch;

    sprintf(prompt, trk_status_txt, ptmn->ts == TS_NEW ? szDefault : blank_str,
            ptmn->ts == TS_OPEN ? szDefault : blank_str,
            ptmn->ts == TS_WORKING ? szDefault : blank_str,
            ptmn->ts == TS_CLOSED ? szDefault : blank_str);


    if (ch == szStatusKeys[0])
        tmnNew.ts = TS_NEW;
    else if (ch == szStatusKeys[1])
        tmnNew.ts = TS_OPEN;
    else if (ch == szStatusKeys[2])
        tmnNew.ts = TS_WORKING;
    else if (ch == szStatusKeys[3])
        tmnNew.ts = TS_CLOSED;
    else
        return;

    if (!TrkUpdateMsg(t, ptmn, &tmnNew))
        Printf(trk_err_upd_db);
    else
    {
        char comment[PATHLEN];
        ptmn->ts = tmnNew.ts;


static void near TrackModPriority(TRK t, TRK_MSG_NDX *ptmn, dword msgnum)
{
    TRK_MSG_NDX tmnNew = *ptmn;
    char *szPriorityKeys = trk_pri_keys;
    int ch;

    do
    {
        WhiteN();
        ch = toupper(KeyGetRNP(trk_pri_txt));
    } while (!strchr(szPriorityKeys, ch) && ch != 13 && ch != 0);

    if (ch == szPriorityKeys[0])
        tmnNew.tp = TP_NOTIFY;
    else if (ch == szPriorityKeys[1])
        tmnNew.tp = TP_LOW;
    else if (ch == szPriorityKeys[2])
        tmnNew.tp = TP_NORMAL;
    else if (ch == szPriorityKeys[3])
        tmnNew.tp = TP_URGENT;
    else if (ch == szPriorityKeys[4])
        tmnNew.tp = TP_CRIT;

    if (!TrkUpdateMsg(t, ptmn, &tmnNew))
        Printf(trk_err_upd_db);
    else
    {
        char comment[PATHLEN];

        ptmn->tp = tmnNew.tp;


static void near TrackMenuModify(void)
{
    char *mod_keys = trk_mod_keys;
    HMSG hmsg;
    dword msgnum;
    int ch;
    TRK t;

    if (!GetMsgNum(modify_which, &msgnum))
        return;

    if ((t = TrackGet()) == NULL)
        return;

    do
    {
        ch = 0;

        if ((hmsg = MsgOpenMsg(sq, MOPEN_READ, msgnum)) != NULL)
        {
            long clen = MsgGetCtrlLen(hmsg);
            char *kludges;
            TRK_MSG_NDX tmn;
            char *actrack;

            if ((kludges = malloc((size_t)clen)) != NULL)
                MsgReadMsg(hmsg, NULL, 0L, 0L, NULL, (size_t)clen, kludges);

            MsgCloseMsg(hmsg);

            if (kludges)
            {
                if ((actrack = MsgGetCtrlToken(kludges, actrack_colon)) == NULL ||
                    !TrkLookupMsg(t, actrack + 9, NULL, NULL, NULL, &tmn))
                {
                    Printf(trk_no_actrack_for_msg);
                }
                else
                {
                    TRK_MSG_NDX tmnTemp;

                    if (!TrackAreWeOwner(kludges, &tmnTemp, NULL))
                    {
                        Printf(trk_not_owner);
                        Press_ENTER();
                    }
                    else
                    {
                        do
                        {
                            extern char accomment_colon[];
                            char szOwner[PATHLEN];
                            char *szComment;

                            if (!TrkGetOwner(t, tmn.to, szOwner))
                                strcpy(szOwner, tmn.to);

                            WhiteN();

                            Printf(trk_msg_stat_owner, szOwner);
                            Printf(trk_msg_stat_status, TrkGetStatus(t, &tmn));
                            Printf(trk_msg_stat_pri, TrkGetPriority(t, &tmn));

                            if ((szComment = MsgGetCtrlToken(kludges, accomment_colon)) != NULL)
                                Printf(trk_msg_stat_cmt, szComment + 11);

                            Putc('\n');

                            do
                            {
                                ch = toupper(KeyGetRNP(trk_mod_txt));
                            } while (!strchr(mod_keys, ch) && ch != 13 && ch != 0);

                            if (ch == mod_keys[0])
                                TrackModOwner(t, &tmn, msgnum);
                            else if (ch == mod_keys[1])
                                TrackModStatus(t, &tmn, msgnum, sq);
                            else if (ch == mod_keys[2])
                                TrackModPriority(t, &tmn, msgnum);
                            else if (ch == mod_keys[3])
                                TrackModComment(t, &tmn, msgnum, szComment ? szComment + 11 : NULL);

                            if (szComment)
                                MsgFreeCtrlToken(szComment);

    } while (ch == mod_keys[3]);

    TrackRelease(t);
}


    if (!GetMsgNum(remove_which, &msgnum))
        return;

    TrackMakeACAUDIT(comment, trk_rem_cmt, usrname);

    if (!TrackInsertTracking(sq, msgnum, NULL, TRUE, FALSE, actrack, TRUE, comment, FALSE, NULL))
    {
        Printf(trk_rem_err, msgnum);
    }
    else
    {
        TRK t;

        if ((t = TrackGet()) != NULL)
        {
            TRK_MSG_NDX tmn;

            if (TrkLookupMsg(t, actrack, NULL, NULL, NULL, &tmn))
            {
                if (TrkDeleteMsg(t, &tmn))
                    Printf(trk_rem_done, msgnum);
                else
                    Printf(trk_rem_err, msgnum);
            }

            TrackRelease(t);
        }
    }
}


static void near TrackAdminOwnerAssign(TRK t)
{
    TRK_OWNER_NDX ton;


    WhiteN();
    Input(ton.to, INPUT_LB_LINE, 0, 4, trk_new_alias);

    if (!*ton.to)
        return;

    if (TrkSetOwner(t, ton.to, ton.szOwner))
        Printf(trk_set_alias, ton.to, ton.szOwner);
    else
        Printf(trk_err_alias, ton.to);

    return;
}


static void near TrackAdminOwnerDelete(TRK t)
{
    TRK_OWNER to;

    do
    {
        WhiteN();
        InputGetsL(to, sizeof(to) - 1, trk_remalias_which);

        if (eqstri(to, qmark))
            TrackAdminOwnerList(t);
    } while (eqstri(to, qmark));

    if (TrkSetOwner(t, to, NULL))
        Printf(trk_remalias_done, to);
    else
        Printf(trk_remalias_err, to);
}


static void near TrackAdminAreaAssign(TRK t)
{
    TRK_AREA_NDX tan;


    if (TrackAskOwner(t, tan.to))
    {
        if (TrkSetDefaultOwner(t, tan.szArea, tan.to))
        {
            Printf(trk_owner_assgn_done, tan.to, tan.szArea);
        }
        else
        {
            Printf(trk_owner_assgn_err, tan.szArea);
        }
    }

    return;
}


static void near TrackAdminAreaList(TRK t)
{
    TRK_AREA_NDX *ptan;
    PALIST *ppl;
    BTREE *pbt;

    pbt = TrkGetAreaBtree(t);

    ppl = PalistNew();

    Puts(trk_owner_lnk_head);

    while ((ptan = BtLookup(pbt, NULL, ppl)) != NULL)
        Printf(trk_owner_lnk_fmt, ptan->to, ptan->szArea);

    PalistDelete(ppl);
}


static void near TrackMenuAdmin(void)
{
    char *admin_keys = trk_admin_keys;

    int ch;

    if (!PrivOK(PRM(track_privmod), FALSE))
    {
        Puts(trk_admin_noaccess);
        Press_ENTER();
        return;
    }

    do
    {
        WhiteN();

        ch = toupper(KeyGetRNP(trk_admin_txt));

        if (!ch || ch == 13)
            return;
    } while (!strchr(admin_keys, ch));

    if (ch == admin_keys[0])
        TrackAdminOwner();
    else if (ch == admin_keys[1])
        TrackAdminArea();
    else if (ch == admin_keys[2])
        TrackAdminRemove();
}


static void near TrackMenuInsert(void)
{
    TRK t;
    TRK_OWNER to;
    dword msgnum;


    if (!GetTrkList() && !PrivOK(PRM(track_privmod), FALSE))
    {
        Printf(trk_admin_noaccess);
        Press_ENTER();
        return;
    }


    if ((t = TrackGet()) != NULL)
    {
        int rc = TrackAskOwner(t, to);
        TrackRelease(t);

        if (rc)
            Printf(TrackInsertMessage(sq, msgnum, to, NULL) ? trk_ins_ok : trk_ins_err,
                   MAS(mah, name), UIDnum(msgnum));
    }
}


    if (TrackAreWeOwner(kludges, &tmn, &real_owner) && real_owner)
    {
        TRK t = TrackGet();

        if (t)
        {
            TrackModStatus(t, &tmn, msgnum, ha);
            TrackRelease(t);
        }
    }

    return TRUE;
}

