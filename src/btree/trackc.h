// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __TRACKC_H_DEFINED
#define __TRACKC_H_DEFINED

#include "btype.h"

#ifdef __cplusplus
#include "dbase.h"
#else
#include "dbasec.h"
#endif

#include "trackcom.h"

#if 0
#define OS2FAR far
#else
#ifdef OS2FAR
#undef OS2FAR
#endif

#define OS2FAR
#endif

#ifdef __cplusplus
class TRACKER;
typedef TRACKER OS2FAR *TRK;

extern "C"
{
#else
typedef char OS2FAR *TRK;
#endif
    TRK BAPIENTRY TrkOpen(char *szFile, unsigned fNewFile);
    void BAPIENTRY TrkClose(TRK t);

    int BAPIENTRY TrkAddMsg(TRK t, TRK_MSG_NDX OS2FAR *ptmn);
    char *BAPIENTRY TrkGetStatus(TRK t, TRK_MSG_NDX OS2FAR *ptmn);
    char *BAPIENTRY TrkGetPriority(TRK t, TRK_MSG_NDX OS2FAR *ptmn);
    char *BAPIENTRY TrkGetAreaOwner(TRK t, char *szArea);
    int BAPIENTRY TrkLookupMsg(TRK t, char OS2FAR *szTrackID, char OS2FAR *szOwner,
                               char OS2FAR *szLocation, PALIST OS2FAR *ppl,
                               TRK_MSG_NDX OS2FAR *ptmn);
    int BAPIENTRY TrkLookupMsgI(TRK t, char OS2FAR *szTrackID, char OS2FAR *szOwner,
                                char OS2FAR *szLocation, PALIST OS2FAR *ppl,
                                TRK_MSG_NDX OS2FAR *ptmn, unsigned uiIdx);
    int BAPIENTRY TrkSetOwner(TRK t, TRK_OWNER OS2FAR to, char OS2FAR *szOwner);
    int BAPIENTRY TrkGetOwner(TRK t, TRK_OWNER OS2FAR to, char OS2FAR *szOwner);
    int BAPIENTRY TrkSetDefaultOwner(TRK t, char OS2FAR *szArea, TRK_OWNER OS2FAR to);
    int BAPIENTRY TrkGetDefaultOwner(TRK t, char OS2FAR *szArea, TRK_OWNER OS2FAR to);
    int BAPIENTRY TrkUpdateMsg(TRK t, TRK_MSG_NDX *ptmnOld, TRK_MSG_NDX *ptmnNew);
    int BAPIENTRY TrkDeleteMsg(TRK t, TRK_MSG_NDX *ptmn);

    BTREE *BAPIENTRY TrkGetOwnerBtree(TRK t);
    BTREE *BAPIENTRY TrkGetAreaBtree(TRK t);
    DBASE *BAPIENTRY TrkGetMsgDbase(TRK t);

#ifdef __cplusplus
};
#endif

#endif // __TRACKC_H_DEFINED