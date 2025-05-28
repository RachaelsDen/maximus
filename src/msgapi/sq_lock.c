// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sq_lock.c,v 1.1.1.1 2002/10/01 17:54:31 sdudley Exp $";
#pragma on(unreferenced)

#define MSGAPI_HANDLERS
#define MSGAPI_NO_OLD_TYPES

#include "api_sq.h"
#include "apidebug.h"
#include "msgapi.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>


static unsigned near _SquishLockBase(HAREA ha)
{
    int iMaxTry = SQUISH_LOCK_RETRY;


    while (iMaxTry && mi.haveshare)
    {
        if (lock(Sqd->sfd, 0L, 1L) == 0)
            break;


    if (!iMaxTry)
    {
        msgapierr = MERR_SHARE;
        Sqd->fHaveExclusive = 0;
        return FALSE;
    }

    return TRUE;
}


    if (--Sqd->fLocked)
        return TRUE;


unsigned _SquishExclusiveBegin(HAREA ha)
{
    SQBASE sqb;


    if (!_SquishLockBase(ha))
        return FALSE;


unsigned _SquishExclusiveEnd(HAREA ha)
{
    SQBASE sqb;
    unsigned rc;

    if (!Sqd->fHaveExclusive)
    {
        msgapierr = MERR_NOLOCK;
        return FALSE;
    }


    if (!_SquishUnlockBase(ha))
        rc = FALSE;

    Sqd->fHaveExclusive = FALSE;

    return rc;
}


    if (Sqd->fLockFunc++ != 0)
        return 0;


    if (!_SquishBeginBuffer(Sqd->hix))
    {
        (void)_SquishUnlockBase(ha);
        return -1;
    }

    return 0;
}

