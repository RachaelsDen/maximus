// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sq_kill.c,v 1.1.1.1 2002/10/01 17:54:31 sdudley Exp $";
#pragma on(unreferenced)

#define MSGAPI_HANDLERS
#define MSGAPI_NO_OLD_TYPES

#include "api_sq.h"
#include "apidebug.h"
#include "msgapi.h"
#include "prog.h"
#include <assert.h>


static sword _SquishKill(HAREA ha, dword dwMsg, SQHDR *psqh, FOFS fo)
{
    assert(Sqd->fHaveExclusive);


    if (!_SquishRemoveIndexEntry(Sqd->hix, dwMsg, NULL, psqh, TRUE))
        return FALSE;


sword MAPIENTRY SquishKillMsg(HAREA ha, dword dwMsg)
{
    SQHDR sqh;
    sword rc;
    FOFS fo;


    if (dwMsg == 0 || dwMsg > ha->num_msg)
    {
        msgapierr = MERR_NOENT;
        return -1;
    }


    if (!_SquishReadHdr(ha, fo, &sqh))
        return -1;


    rc = _SquishKill(ha, dwMsg, &sqh, fo);

