// SPDX-License-Identifier: GPL-2.0-or-later


#include "mexall.h"

#ifdef MEX

#ifndef INTERNAL_LANGUAGES


word EXPENTRY intrin_lang_heap_string(void)
{
    MA ma;
    char *psz;
    int stringnum;

    MexArgBegin(&ma);
    psz = MexArgGetString(&ma, TRUE);
    stringnum = MexArgGetWord(&ma);
    if (!psz)
        MexReturnString("");
    else
    {
        MexReturnString(s_reth(psz, stringnum));
        free(psz);
    }

    return MexArgEnd(&ma);
}

