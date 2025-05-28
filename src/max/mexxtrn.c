// SPDX-License-Identifier: GPL-2.0-or-later


#include "mexall.h"

#ifdef MEX


word EXPENTRY intrin_menu_cmd(void)
{
    MA ma;
    int iOpt;
    char *szArgs;

    MexArgBegin(&ma);


    if ((szArgs = MexArgGetString(&ma, FALSE)) != NULL)
    {
        MexImportData(pmisThis);
        BbsRunOpt(iOpt, szArgs);
        MexExportData(pmisThis);

        free(szArgs);
    }

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_shell(void)
{
    MA ma;
    IADDR where;
    char *s, *cap;
    int method, out_method;
    word wLen;

    MexArgBegin(&ma);
    method = MexArgGetWord(&ma);
    s = MexArgGetNonRefString(&ma, &where, &wLen);


    if ((cap = malloc(wLen + 1)) != NULL)
    {
        memmove(cap, s, wLen);
        cap[wLen] = 0;

        MexImportUser(pmisThis->pmu, &usr);

