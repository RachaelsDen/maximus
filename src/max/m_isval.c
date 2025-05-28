// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_isval.c,v 1.1.1.1 2002/10/01 17:52:44 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_main
#include "max_msg.h"
#include "prog.h"
#include <string.h>

static int near _ValidMsgArea(PMAH pmah, unsigned flags, BARINFO *pbi)
{
    char *bar;

    if ((flags & VA_OVRPRIV) == 0 && !PrivOK(PMAS(pmah, acs), TRUE))
        return FALSE;


    if (pmah)
        ma = *pmah;
    else if (!ReadMsgArea(ham, name, &ma))
        return FALSE;

    rc = _ValidMsgArea(&ma, flags, pbi);

    if (!pmah)
        DisposeMah(&ma);

    return rc;
}

void ForceGetMsgArea(void)
{
    BARINFO bi;

        first = TRUE;

        while (!ValidMsgArea(usr.msg, NULL, VA_VAL | (first ? VA_PWD : 0), &bi) || bad)
        {
            first = FALSE;
            Puts(inval_cur_msg);
            Msg_Area();
