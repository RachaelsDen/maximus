// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: t_report.c,v 1.1.1.1 2002/10/01 17:53:16 sdudley Exp $";
#pragma on(unreferenced)

#define MAX_LANG_max_init
#define MAX_LANG_max_main
#include "trackp.h"

#ifdef MAX_TRACKER

#include "api_brow.h"
#include "m_browse.h"
#include "qwk.h"

extern char szTrk[];


    if (!prep->uiArea)
    {
        *prep->szWildcard = 0;

        do
        {
            ch = toupper(KeyGetRNP(trk_rep_txt));
        } while (!strchr(szAreaKeys, ch) && ch && ch != 13);

        if (ch == szAreaKeys[0])
            prep->uiArea = RF_AREA_CUR;
        else if (ch == szAreaKeys[1])
            prep->uiArea = RF_AREA_TAG;
        else if (ch == szAreaKeys[2])
            prep->uiArea = RF_AREA_GRP;
        else if (ch == szAreaKeys[3])
            prep->uiArea = RF_AREA_WLD;
        else if (ch == szAreaKeys[4] || ch == 0 || ch == 13)
            prep->uiArea = RF_AREA_ALL;
        else
            return FALSE;
    }

    if (prep->uiArea == RF_AREA_WLD && !*prep->szWildcard)
    {
        WhiteN();
        InputGetsL(prep->szWildcard, PATHLEN - 1, trk_rep_get_areaname);

        if (!*prep->szWildcard)
            return FALSE;
    }

    return TRUE;
}


    if (prep->fStatus)
        return TRUE;

    WhiteN();
    InputGetsL(szInput, PATHLEN - 1, trk_rep_stat_txt);
    strupr(szInput);

    prep->fStatus = 0;

    if (!*szInput)
    {
        prep->fStatus = SF_NEW | SF_OPEN | SF_WORKING;
        return TRUE;
    }


static int near RepGetPriority(TRK t, PREP prep)
{
    char *szPriKeys = trk_rep_pri_keys;
    char szInput[PATHLEN], *p;

    NW(t);


static int near RepGetOwner(TRK t, PREP prep)
{
    char szOwner[PATHLEN];


    if (*prep->to)
        return TRUE;


    if (!PrivOK(PRM(track_privview), FALSE))
    {
        prep->fOnlyOurs = TRUE;
        *prep->to = 0;
        return TRUE;
    }


static int near RepMatchArea(PREP prep, TRK_MSG_NDX *ptmn)
{
    char szGrp[PATHLEN];
    int uiGrpLen;

    MessageSection(ptmn->tl.szArea, szGrp);
    uiGrpLen = strlen(szGrp);

    return (prep->uiArea == RF_AREA_CUR && eqstri(ptmn->tl.szArea, usr.msg)) ||
           (prep->uiArea == RF_AREA_TAG && TagQueryTagList(&mtm, ptmn->tl.szArea)) ||
           (prep->uiArea == RF_AREA_GRP &&
            (!uiGrpLen || strncmp(ptmn->tl.szArea, szGrp, uiGrpLen) == 0)) ||
           (prep->uiArea == RF_AREA_WLD && BrowseWCMatch(prep->szWildcard, ptmn->tl.szArea)) ||
           (prep->uiArea == RF_AREA_ALL);
}


static int near RepMatchPriority(PREP prep, TRK_MSG_NDX *ptmn)
{
    return (ptmn->tp == TP_NOTIFY && (prep->fPriority & PF_NOTIFY)) ||
           (ptmn->tp == TP_LOW && (prep->fPriority & PF_LOW)) ||
           (ptmn->tp == TP_NORMAL && (prep->fPriority & PF_NORMAL)) ||
           (ptmn->tp == TP_URGENT && (prep->fPriority & PF_URGENT)) ||
           (ptmn->tp == TP_CRIT && (prep->fPriority & PF_CRIT));
}


    if (prep->fOnlyOurs)
    {
        TRKLIST ptl;


static int near RepGetDownload(TRK t, PREP prep)
{
    NW(t);

    if (!prep->fDoQWK)
    {
        WhiteN();

        if (GetyNAnswer(trk_rep_dl_related_qwk, 0) == YES)
            prep->fDoQWK = QF_DO_PACK;
        else
            prep->fDoQWK = QF_DONT_PACK;
    }

    return TRUE;
}


static int near EntryTooOld(SCOMBO *pscMsg)
{
#define NUM_DAYS 7

    SCOMBO scNow;
    struct tm tmMsg, tmNow;
    time_t tNow, tMsg;

    Get_Dos_Date(&scNow);
    DosDate_to_TmDate(&scNow, &tmNow);
    DosDate_to_TmDate(pscMsg, &tmMsg);

    tNow = mktime(&tmNow);
    tMsg = mktime(&tmMsg);


static unsigned near RepShow(TRK t, TRK_MSG_NDX *ptmn, FILE *fp, int *piFirst, char *pcNonstop)
{
    char buf[PATHLEN];
    char line[PATHLEN];


    sprintf(buf, trk_rep_msgnum, ptmn->tl.szArea,
            (prm.flags2 & FLAG2_UMSGID) ? ptmn->tl.uid : MsgUidToMsgn(sq, ptmn->tl.uid, UID_EXACT));


    sprintf(line, trk_rep_fmt, ptmn->szTrackID, (ptmn->scDateWritten.msg_st.date.yr + 80) % 100,
            ptmn->scDateWritten.msg_st.date.mo, ptmn->scDateWritten.msg_st.date.da,
            EntryTooOld((SCOMBO *)&ptmn->scDateWritten) ? '*' : ' ', ptmn->to,
            TrkGetPriority(t, ptmn), TrkGetStatus(t, ptmn), buf);


static BROWSE *RepConstructBrowse(PREP prep, char *nonstop)
{
    BROWSE *b;

    if ((b = malloc(sizeof(*b))) == NULL)
    {
        logit(mem_none);
        return NULL;
    }

    memset(b, 0, sizeof *b);


    if (QWK_Begin(b) == -1)
    {
        free(b);
        return NULL;
    }


static unsigned near RepNewArea(PREP prep, TRK_MSG_NDX *ptmn, BROWSE *b)
{
    BARINFO bi;

    if (!prep->fFirstArea)
        if (QWK_After(b) == -1)
            return FALSE;


static unsigned near RepQWKPack(PREP prep, TRK_MSG_NDX *ptmn, BROWSE *b)
{
    unsigned rc;


    b->sq = sq;
    b->type = mah.ma.type;
    b->path = MAS(mah, path);


    if (!b->bdata)
        return TRUE;

    rc = FALSE;


static unsigned near RepFinishBrowse(PREP prep, BROWSE *b)
{
    unsigned rc;

    if (!prep->fFirstArea)
        QWK_After(b);

    rc = QWK_End(b) != -1;
    free(b);

    return rc;
}


static int near RepDoLookup(TRK t, PREP prep, FILE *fp)
{
    BROWSE *b;
    PALIST *ppl;
    TRK_MSG_NDX tmn;
    char nonstop = FALSE;
    unsigned rc = TRUE;
    int first = TRUE;
    int fDidPush = FALSE;

    if (prep->fDoQWK == QF_DO_PACK)
    {

        if (PushMsgArea(usr.msg, 0))
            fDidPush = TRUE;
    }

    ppl = PalistNew();

    WhiteN();
    display_line = 1;

    while (TrkLookupMsgI(t, NULL, NULL, NULL, ppl, &tmn, prep->fDoQWK == QF_DO_PACK ? 2 : 0))
    {

    PalistDelete(ppl);


static int near TrackMenuReportInternal(TRK t, PREP prep, FILE *fp)
{
    static int doing_report = FALSE;
    unsigned rc;


    if (!RepGetArea(t, prep))
        return FALSE;

    if (!RepGetStatus(t, prep))
        return FALSE;

    if (!RepGetPriority(t, prep))
        return FALSE;

    if (!RepGetOwner(t, prep))
        return FALSE;

    if (!RepGetDownload(t, prep))
        return FALSE;


int TrackReportOurMessages(char *qwk_path)
{
    char fname[PATHLEN];
    int rc = FALSE;
    FILE *fp;
    TRK t;


        sprintf(fname, trk_rep_qwk_bulletin, qwk_path);

        if ((fp = fopen(fname, fopen_write)) == NULL)
            cant_open(fname);
        else
        {
            Puts(trk_rep_generating);
            vbuf_flush();
            rc = TrackMenuReportInternal(t, &rep, fp);
            fclose(fp);

            if (rc)
                Putc('\n');
            else
            {
                Printf(trk_rep_gen_err);
                unlink(fname);
            }
        }

        TrackRelease(t);
    }

    return rc;
}

