// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mexint.c,v 1.1.1.1 2002/10/01 17:52:25 sdudley Exp $";
#pragma on(unreferenced)


#include "mexall.h"

#ifdef MEX


    MexArgBegin(&ma);
    pmcs = MexArgGetRef(&ma);
    rc = MexArgEnd(&ma);


    pmcs->avail = cs.avail;

    MexKillStructString(mex_cstat, pmcs, username);
    StoreString(MexPtrToVM(pmcs), struct mex_cstat, username, cs.username);

    MexKillStructString(mex_cstat, pmcs, status);
    StoreString(MexPtrToVM(pmcs), struct mex_cstat, status, cs.status);

    regs_2[0] = TRUE;
    return rc;
}


word EXPENTRY intrin_ProtocolNumberToName(void)
{
    MA ma;
    char temp[PATHLEN];
    sbyte pnum;

    MexArgBegin(&ma);
    pnum = MexArgGetByte(&ma);

    if (pnum == PROTOCOL_NONE)
        strcpy(temp, proto_none);
    else
        Protocol_Name(pnum, temp);

    MexReturnString(temp);

    return MexArgEnd(&ma);
}


    ar = UserAri(cnum);
    strcpy(temp, (ar && cnum && cnum <= MAX_ARI) ? ar->arcname : proto_none);

    MexReturnString(temp);

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_prm_string(void)
{
    MA ma;
    OFS *pofs;
    int stringnum;

    MexArgBegin(&ma);
    stringnum = MexArgGetWord(&ma);

#define PRM_NUM_STRINGS                                                                            \
    (offsetof(struct m_pointers, PRM_HEAP_END) - offsetof(struct m_pointers, PRM_HEAP_START))

    pofs = &prm.PRM_HEAP_START;

    if (stringnum < PRM_NUM_STRINGS)
        MexReturnString(offsets + pofs[stringnum]);
    else
        MexReturnString("");

    return MexArgEnd(&ma);
}

