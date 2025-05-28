// SPDX-License-Identifier: GPL-2.0-or-later



#include "dv.h"
#include "prog.h"
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __MSDOS__
#if defined(__TURBOC__) && !defined(__TOPAZ__)


extern byte VidHook;

void thisfunc(void);
void thatfunc(void);

void thisfunc(void)
{
    VidHook = 1;
    thatfunc();
}

void thatfunc(void) { thisfunc(); }

#endif




word _fast VidOpen(int has_snow, int desqview, int dec_rows)
{
    int x, y;

    if (Vid_Open)
        return 0;

    Vid_Open = TRUE;

    Vid_MonoCard = (VidGetMode() == 7);
    Vid_NumCols = NUM_COLS;
    Vid_NumRows = _VidGetNumRows();
    Vid_TotChars = Vid_NumCols * Vid_NumRows;
    Vid_Segment = VidGetBuffer(Vid_MonoCard);

    DesqView = (char)desqview;

    if (desqview)
        Start_Shadow();

#ifdef __FLAT__
    Vid_Display = (char *)((unsigned long)VidGetBuffer(Vid_MonoCard) << 4);
#else
    Vid_Display = MK_FP(VidGetBuffer(Vid_MonoCard), 0);
#endif

    Vid_StatusPort = (Vid_MonoCard ? 0x3BA : 0x3DA);
    Vid_HaveSnow = has_snow;

    if (VidGetBPage() != 0)
        VidSetPage(0);

    Vid_Page = 0;

    VidSetAttr(7);

    _VidGetXYB(&Vid_Col, &Vid_Row);

    if ((First_RowTable = RowTable = (int *)malloc(Vid_NumRows * sizeof(int))) == NULL)
    {
        Vid_Open = FALSE;
        return -1;
    }

    for (x = 0, y = PAGE_OFS; x < Vid_NumRows; x++)
    {
        RowTable[x] = y;
        y += Vid_NumCols * 2;
    }

