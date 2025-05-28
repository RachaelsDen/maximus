// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_isval.c,v 1.1.1.1 2002/10/01 17:51:05 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_main
#include "max_file.h"
#include "prog.h"
#include <string.h>

static int near _ValidFileArea(PFAH pfah, unsigned flags, BARINFO *pbi)
{
    char *bar;

    if ((flags & VA_OVRPRIV) == 0 && !PrivOK(PFAS(pfah, acs), TRUE))
        return FALSE;


    if (pfah)
        fa = *pfah;
    else if (!ReadFileArea(haf, name, &fa))
        return FALSE;

    rc = _ValidFileArea(&fa, flags, pbi);

    if (!pfah)
        DisposeFah(&fa);

    return rc;
}

void ForceGetFileArea(void)
{
    BARINFO bi;

        while (!ValidFileArea(usr.files, NULL, VA_VAL | (first ? VA_PWD : 0), &bi) || bad)
        {
            first = FALSE;
            Puts(inval_cur_file);
            File_Area();
