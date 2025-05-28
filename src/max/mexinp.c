// SPDX-License-Identifier: GPL-2.0-or-later


#include "mexall.h"
#include "modem.h"

#ifdef MEX


    MexArgGetRefString(&ma, &ia, &wLen);
    wType = MexArgGetWord(&ma);
    wCh = MexArgGetByte(&ma);
    wMax = MexArgGetWord(&ma);
    pszPrompt = MexArgGetString(&ma, FALSE);


    if ((s = malloc(wMax + 1)) != NULL)
    {
        Input(s, wType, wCh, wMax, *pszPrompt ? pszPrompt : NULL);
        wRetVal = strlen(s);


        MexStoreByteStringAt(MexIaddrToVM(&ia), s, wRetVal);
        free(s);
    }

    regs_2[0] = wRetVal;

    if (pszPrompt)
        free(pszPrompt);

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_input_ch(void)
{
    MA ma;
    word wType;
    char *pszOptions;

    MexArgBegin(&ma);


    regs_2[0] = Input_Char(wType, *pszOptions ? pszOptions : NULL);

    free(pszOptions);

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_input_list(void)
{
    MA ma;
    char *pszList;
    word wType;
    char *pszHelpFile;
    char *pszInvalidResponse;
    char *pszPrompt;

    MexArgBegin(&ma);


    regs_2[0] =
        GetListAnswer(pszList, pszHelpFile, pszInvalidResponse, wType, percent_s, pszPrompt);

    free(pszPrompt);
    free(pszInvalidResponse);
    free(pszHelpFile);
    free(pszList);

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_getch(void)
{
    vbuf_flush();
    regs_1[0] = (byte)Mdm_getcw();
    return 0;
}


word EXPENTRY intrin_localkey(void)
{
    regs_1[0] = (byte)Mdm_WasLocalKey();
    return 0;
}

word EXPENTRY intrin_keyboard(void)
{
    MA ma;

    MexArgBegin(&ma);
    regs_2[0] = SetLocalKeystate(MexArgGetWord(&ma));
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_iskeyboard(void)
{
    regs_2[0] = LocalKeystate();
    return 0;
}

word EXPENTRY intrin_time_check(void)
{
    MA ma;

    MexArgBegin(&ma);
    regs_2[0] = !!do_timecheck;
    do_timecheck = !!MexArgGetWord(&ma);
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_dcd_check(void)
{
    MA ma;

    MexArgBegin(&ma);
    regs_2[0] = !(no_dcd_check);
    no_dcd_check = !MexArgGetWord(&ma);
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_carrier(void)
{
    regs_2[0] = local || real_carrier();
    return 0;
}


word EXPENTRY intrin_reset_more(void)
{
    MA ma;
    byte *pbNonStop;

    MexArgBegin(&ma);
    pbNonStop = MexArgGetRef(&ma);

    display_line = display_col = 1;
    *pbNonStop = FALSE;

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_do_more(void)
{
    MA ma;
    byte *pbNonStop;
    char *colour;

    MexArgBegin(&ma);

    pbNonStop = MexArgGetRef(&ma);
    colour = MexArgGetString(&ma, FALSE);

