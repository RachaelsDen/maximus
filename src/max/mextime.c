// SPDX-License-Identifier: GPL-2.0-or-later


#include "mexall.h"

#ifdef MEX


word EXPENTRY intrin_timestamp(void)
{
    MA ma;
    struct mex_stamp *pms;
    SCOMBO sc;
    word rc;


    Get_Dos_Date(&sc);
    StampToMexStamp(&sc, pms);

    regs_2[0] = 0;
    return rc;
}


word EXPENTRY intrin_stamp_to_long(void)
{
    MA ma;
    struct mex_stamp *pms;
    word rc;
    SCOMBO sc;
    struct tm t;

    MexArgBegin(&ma);
    pms = MexArgGetRef(&ma);
    rc = MexArgEnd(&ma);

    MexStampToStamp(pms, &sc);
    DosDate_to_TmDate(&sc, &t);

    regs_4[0] = mktime(&t);
    return rc;
}


word EXPENTRY intrin_long_to_stamp(void)
{
    MA ma;
    word rc;
    struct tm *ptm;
    struct mex_stamp *pms;
    SCOMBO sc;
    time_t l;

    MexArgBegin(&ma);
    l = MexArgGetDword(&ma);
    pms = MexArgGetRef(&ma);
    rc = MexArgEnd(&ma);

    ptm = localtime(&l);
    TmDate_to_DosDate(ptm, &sc);
    StampToMexStamp(&sc, pms);

    return rc;
}


    MexArgBegin(&ma);
    pms = MexArgGetRef(&ma);
    rc = MexArgEnd(&ma);


word EXPENTRY intrin_timeleft(void)
{
    regs_4[0] = timeleft();
    return 0;
}


word EXPENTRY intrin_timeadjustsoft(void)
{
    MA ma;
    word was_added, added, was_xp_mins;
    long lDelta;

    MexArgBegin(&ma);
    lDelta = MexArgGetDword(&ma);


    regs_4[0] = Add_To_Time(lDelta);


    return MexArgEnd(&ma);
}


    regs_4[0] = (timeoff += lDelta);
    return MexArgEnd(&ma);
}

