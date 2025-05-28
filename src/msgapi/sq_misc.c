// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sq_misc.c,v 1.2 2003/06/05 22:54:50 wesgarland Exp $";
#pragma on(unreferenced)

#define MSGAPI_HANDLERS
#define MSGAPI_NO_OLD_TYPES

#include "api_sq.h"
#include "apidebug.h"
#include "msgapi.h"
#include "prog.h"
#include <ctype.h>
#include <stdio.h>


dword MAPIENTRY SquishGetCurPos(HMSG hmsg)
{
    if (MsgInvalidHmsg(hmsg) || !_SquishReadMode(hmsg))
        return (dword)-1;

    return hmsg->cur_pos;
}


dword MAPIENTRY SquishGetCtrlLen(HMSG hmsg)
{
    if (MsgInvalidHmsg(hmsg) || !_SquishReadMode(hmsg))
        return (dword)-1L;

    return hmsg->sqhRead.clen;
}


sword MAPIENTRY SquishSetHighWater(HAREA ha, dword dwMsg)
{
    if (MsgInvalidHarea(ha))
        return -1;


void MAPIENTRY SquishSetMaxMsg(HAREA ha, dword dwMaxMsgs, dword dwSkipMsgs, dword dwMaxDays)
{
    if (MsgInvalidHarea(ha))
        return;


dword MAPIENTRY SquishHash(byte OS2FAR *f)
{
    dword hash = 0, g;
    char *p;

    for (p = f; *p; p++)
    {
        hash = (hash << 4) + (dword)tolower(*p);

        if ((g = (hash & 0xf0000000L)) != 0L)
        {
            hash |= g >> 24;
            hash |= g;
        }
    }

