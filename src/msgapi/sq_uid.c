// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sq_uid.c,v 1.1.1.1 2002/10/01 17:54:33 sdudley Exp $";
#pragma on(unreferenced)

#define MSGAPI_HANDLERS
#define MSGAPI_NO_OLD_TYPES

#include "api_sq.h"
#include "apidebug.h"
#include "msgapi.h"
#include "prog.h"
#include <stddef.h>
#include <string.h>


UMSGID MAPIENTRY SquishGetNextUid(HAREA ha) { return Sqd->uidNext; }


UMSGID MAPIENTRY SquishMsgnToUid(HAREA ha, dword dwMsg)
{
    SQIDX sqi;

    if (MsgInvalidHarea(ha))
        return (UMSGID)0L;


dword MAPIENTRY SquishUidToMsgn(HAREA ha, UMSGID uid, word wType)
{
    SQIDX sqi;
    dword rc = 0;
    sdword stLow, stHigh, stTry;
    dword dwMax;

    if (MsgInvalidHarea(ha))
        return (UMSGID)0L;


    if (!_SquishBeginBuffer(Sqd->hix))
        return (dword)0;


    (void)memset(&sqi, 0, sizeof sqi);


        if (!SidxGet(Sqd->hix, (dword)stTry, &sqi))
            break;

        if (sqi.umsgid == uid)
        {
            rc = (dword)stTry;
            break;
        }
        else if (uid > sqi.umsgid)
            stLow = stTry + 1;
        else
            stHigh = stTry - 1;
    }


    if (!_SquishEndBuffer(Sqd->hix))
        rc = (dword)0;

    return rc;
}
