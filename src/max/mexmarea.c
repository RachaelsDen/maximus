// SPDX-License-Identifier: GPL-2.0-or-later


#include "max_msg.h"
#include "mexall.h"

#ifdef MEX

static void near msgareaexport(struct mex_marea *pma, PMAH mas)
{
    MexKillStructString(mex_marea, pma, name);
    MexKillStructString(mex_marea, pma, descript);
    MexKillStructString(mex_marea, pma, path);
    MexKillStructString(mex_marea, pma, tag);
    MexKillStructString(mex_marea, pma, attach_path);
    MexKillStructString(mex_marea, pma, barricade);
    StoreString(MexPtrToVM(pma), struct mex_marea, name, PMAS(mas, name));
    StoreString(MexPtrToVM(pma), struct mex_marea, descript, PMAS(mas, descript));
    StoreString(MexPtrToVM(pma), struct mex_marea, path, PMAS(mas, path));
    StoreString(MexPtrToVM(pma), struct mex_marea, tag, PMAS(mas, echo_tag));
    StoreString(MexPtrToVM(pma), struct mex_marea, attach_path, PMAS(mas, attachpath));
    StoreString(MexPtrToVM(pma), struct mex_marea, barricade, PMAS(mas, barricade));
    pma->division = (mas->ma.attribs & MA_DIVBEGIN) ? 1 : (mas->ma.attribs & MA_DIVEND) ? 2 : 0;
    pma->type = mas->ma.type;
    pma->attribs = mas->ma.attribs;
}

static word near findmsgarea(struct mex_marea *pma, int direction)
{
    MAH ma;

    memset(&ma, 0, sizeof ma);
    ma.ma.cbPrior = pmisThis->cbPriorMsg;

    while ((direction ? AreaFileFindNext : AreaFileFindPrior)(pmisThis->hafMsg, &ma, FALSE) == 0)
    {
        pmisThis->cbPriorMsg = ma.ma.cbPrior;

        if (!(ma.ma.attribs & MA_HIDDN) && PrivOK(MAS(ma, acs), TRUE))
        {
            msgareaexport(pma, &ma);
            DisposeMah(&ma);
            return TRUE;
        }
    }
    AreaFileFindClose(pmisThis->hafMsg);
    pmisThis->hafMsg = 0;
    DisposeMah(&ma);
    return FALSE;
}

word EXPENTRY intrin_msgareafindfirst(void)
{
    MA ma;
    struct mex_marea *pma;
    char *psz;
    int flags;

    if (pmisThis->hafMsg)
    {
        AreaFileFindClose(pmisThis->hafMsg);
        pmisThis->hafMsg = 0;
    }

    pmisThis->cbPriorMsg = 0;
    MexArgBegin(&ma);
    pma = MexArgGetRef(&ma);
    psz = MexArgGetString(&ma, FALSE);
    flags = MexArgGetWord(&ma);
    pmisThis->hafMsg = AreaFileFindOpen(ham, (psz && *psz) ? psz : NULL, flags);
    if (pmisThis->hafMsg == NULL)
        regs_2[0] = FALSE;
    else
    {
        if ((regs_2[0] = findmsgarea(pma, TRUE)) != 0)
        {
            AreaFileFindChange(pmisThis->hafMsg, NULL, flags);
        }
    }
    if (psz)
        free(psz);
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_msgareafindnext(void)
{
    MA ma;
    struct mex_marea *pma;

    MexArgBegin(&ma);
    pma = MexArgGetRef(&ma);
    if (!pmisThis->hafMsg)
        regs_2[0] = FALSE;
    else
        regs_2[0] = findmsgarea(pma, TRUE);
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_msgareafindprev(void)
{
    MA ma;
    struct mex_marea *pma;

    MexArgBegin(&ma);
    pma = MexArgGetRef(&ma);
    if (!pmisThis->hafMsg)
        regs_2[0] = FALSE;
    else
        regs_2[0] = findmsgarea(pma, FALSE);
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_msgareafindclose(void)
{
    if (pmisThis->hafMsg)
    {
        AreaFileFindClose(pmisThis->hafMsg);
        pmisThis->hafMsg = 0;
    }
    return regs_2[0] = 0;
}

word EXPENTRY intrin_msg_area(void)
{
    Msg_Area();
    if (mah.heap)
    {
        msgareaexport(MexDSEG(pmisThis->vmaMarea), &mah);
        SetAreaName(usr.msg, MAS(mah, name));
        MexKillStructString(mex_usr, pmisThis->pmu, msg);
        StoreString(MexPtrToVM(pmisThis->pmu), struct mex_usr, msg, MAS(mah, name));
        if (!sq)
            memset(pmisThis->pmm, 0, sizeof *pmisThis->pmm);
        else
        {
            pmisThis->set_current = pmisThis->pmm->current = UIDnum(last_msg);
            pmisThis->pmm->num = MsgGetNumMsg(sq);
            pmisThis->pmm->high = UIDnum(MsgGetHighMsg(sq));
        }
    }
    return 0;
}

word EXPENTRY intrin_msgareaselect(void)
{
    MA ma;
    MAH mymah;
    char *psz;
    BARINFO bi;

    memset(&mymah, 0, sizeof mymah);

    if (pmisThis->hafMsg)
    {
        AreaFileFindClose(pmisThis->hafMsg);
        pmisThis->hafMsg = 0;
    }
    MexArgBegin(&ma);
    psz = MexArgGetString(&ma, FALSE);
    regs_2[0] = FALSE;
    if (psz && *psz)
    {
        char temp[MAX_ALEN];

        strcpy(temp, psz);
        pmisThis->hafMsg = AreaFileFindOpen(ham, temp, 0);
        if (pmisThis->hafMsg == NULL)
            regs_2[0] = FALSE;
        else
        {
            int rc = AreaFileFindNext(pmisThis->hafMsg, &mymah, FALSE);
            if (rc != 0)
            {
                char *p;

                strcpy(temp, usr.msg);
                p = strrchr(temp, '.');
                if (p)
                {
                    strcpy(p + 1, psz);
                    AreaFileFindReset(pmisThis->hafMsg);
                    AreaFileFindChange(pmisThis->hafMsg, temp, 0);
                    rc = AreaFileFindNext(pmisThis->hafMsg, &mymah, FALSE);
                }
            }
            if (rc == 0 && !(mymah.ma.attribs & MA_HIDDN) &&
                ValidMsgArea(NULL, &mymah, VA_VAL | VA_PWD | VA_EXTONLY, &bi) &&
                PopPushMsgAreaSt(&mymah, &bi))
            {
                SetAreaName(usr.msg, MAS(mymah, name));
                msgareaexport(MexDSEG(pmisThis->vmaMarea), &mymah);
                regs_2[0] = TRUE;
                MexKillStructString(mex_usr, pmisThis->pmu, msg);
                StoreString(MexPtrToVM(pmisThis->pmu), struct mex_usr, msg, MAS(mymah, name));
                if (!sq)
                    memset(pmisThis->pmm, 0, sizeof *pmisThis->pmm);
                else
                {
                    pmisThis->set_current = pmisThis->pmm->current = UIDnum(last_msg);
                    pmisThis->pmm->num = MsgGetNumMsg(sq);
                    pmisThis->pmm->high = UIDnum(MsgGetHighMsg(sq));
                }
            }
            AreaFileFindClose(pmisThis->hafMsg);
            pmisThis->hafMsg = 0;
            DisposeMah(&mymah);
        }
    }
    if (psz)
        free(psz);
    return MexArgEnd(&ma);
}

