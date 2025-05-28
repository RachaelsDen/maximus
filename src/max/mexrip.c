// SPDX-License-Identifier: GPL-2.0-or-later


#include "mexall.h"

#ifdef MEX


word EXPENTRY intrin_term_length(void)
{
    regs_2[0] = TermLength();
    ;
    return 0;
}


word EXPENTRY intrin_screen_width(void)
{
    regs_2[0] = VidNumCols();
    return 0;
}

word EXPENTRY intrin_set_textsize(void)
{
    MA ma;
    int cols, rows;

    MexArgBegin(&ma);
    cols = MexArgGetWord(&ma);
    rows = MexArgGetWord(&ma);
    SetTermSize(cols, rows);

    return MexArgEnd(&ma);
}

word EXPENTRY intrin_rip_send(void)
{
    MA ma;
    char *pszFile;
    int fDisplay;

    MexArgBegin(&ma);
    pszFile = MexArgGetString(&ma, FALSE);
    fDisplay = MexArgGetWord(&ma);
    if (!pszFile)
        regs_2[0] = 0;
    else
    {
        regs_2[0] = RIP_SendFile(pszFile, fDisplay);
        free(pszFile);
    }
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_rip_hasfile(void)
{
    MA ma;
    char *pszFile;
    long *lfilesize;

    MexArgBegin(&ma);
    pszFile = MexArgGetString(&ma, FALSE);
    lfilesize = MexArgGetRef(&ma);
    if (!pszFile)
        regs_2[0] = 0;
    else
    {
        regs_2[0] = RIP_HasFile(pszFile, lfilesize);
        free(pszFile);
    }
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_ansi_detect(void)
{
    regs_2[0] = autodetect_ansi();
    return 0;
}

word EXPENTRY intrin_rip_detect(void)
{
    regs_2[0] = autodetect_rip();
    return 0;
}

