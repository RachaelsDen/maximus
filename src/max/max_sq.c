// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_sq.c,v 1.1.1.1 2002/10/01 17:52:03 sdudley Exp $";
#pragma on(unreferenced)

#include "alc.h"
#include "max_msg.h"
#include "prog.h"
#include <string.h>

LLPUSH lam = NULL, laf = NULL;

void EnterFileAreaBarricade(void)
{
    if (!eqstri(CurrentMenuName(), FAS(fah, barricademenu)))
        return;

    if (mah.heap && !eqstri(CurrentMenuName(), MAS(mah, barricademenu)))
        ExitMsgAreaBarricade();

    if (fah.bi.use_barpriv)
    {

        usr.priv = fah.bi.priv;
        usr.xkeys |= fah.bi.keys;
    }
    else
    {
        laf->biOldPriv.use_barpriv = FALSE;
    }
}

void ExitFileAreaBarricade(void)
{

        if (!locked)
        {
            usr.priv = laf->biOldPriv.priv;
            usr.xkeys = laf->biOldPriv.keys;
        }

        laf->biOldPriv.use_barpriv = FALSE;
    }
}

void EnterMsgAreaBarricade(void)
{
    if (!eqstri(CurrentMenuName(), MAS(mah, barricademenu)))
        return;

    if (fah.heap && !eqstri(CurrentMenuName(), FAS(fah, barricademenu)))
        ExitFileAreaBarricade();

    if (mah.bi.use_barpriv)
    {

        usr.priv = mah.bi.priv;
        usr.xkeys |= mah.bi.keys;
    }
    else
    {
        lam->biOldPriv.use_barpriv = FALSE;
    }
}

void ExitMsgAreaBarricade(void)
{
    if (lam && lam->biOldPriv.use_barpriv)
    {

    ExitMsgAreaBarricade();

    if (sq)
    {

int PushMsgAreaSt(PMAH pmah, BARINFO *pbi)
{
    LLPUSH llp;


        ExitMsgArea();
    }


int PushMsgArea(char *name, BARINFO *pbi)
{
    MAH ma;
    int rc;

    memset(&ma, 0, sizeof ma);

    if (!ReadMsgArea(ham, name, &ma))
        return FALSE;

    rc = PushMsgAreaSt(&ma, pbi);
    DisposeMah(&ma);
    return rc;
}


int PopPushMsgArea(char *name, BARINFO *pbi)
{
    MAH ma;
    int rc;

    memset(&ma, 0, sizeof ma);

    if (!ReadMsgArea(ham, name, &ma))
        return FALSE;

    rc = PopPushMsgAreaSt(&ma, pbi);
    DisposeMah(&ma);

    return rc;
}


    ExitMsgArea();


    if (!lam)
        return FALSE;


int PushFileAreaSt(PFAH pfah, BARINFO *pbi)
{
    LLPUSH llp;


        ExitFileArea();
    }


int PushFileArea(char *name, BARINFO *pbi)
{
    FAH fa;
    int rc;

    memset(&fa, 0, sizeof fa);

    if (!ReadFileArea(haf, name, &fa))
        return FALSE;

    rc = PushFileAreaSt(&fa, pbi);
    DisposeFah(&fa);
    return rc;
}


int PopFileArea(void)
{
    LLPUSH lp;

    if (!laf)
        return FALSE;


    lp = laf;
    laf = laf->next;

    DisposeFah(&lp->ah.fah);
    free(lp);

    if (!laf)
        return FALSE;


HAREA MaxOpenArea(MAH *pmah)
{
    return (MsgOpenArea(MAS(*pmah, path), MSGAREA_CRIFNEC,
                        pmah->ma.type | ((pmah->ma.type & MA_ECHO) ? MSGTYPE_ECHO : 0)));
}
