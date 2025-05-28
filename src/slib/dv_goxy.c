// SPDX-License-Identifier: GPL-2.0-or-later



#include "dv.h"
#include "prog.h"

#ifdef __MSDOS__

int _fast VidGotoXY(int Col, int Row, int do_sync)
{
    Col--;
    Row--;

    if (!do_sync || (Col >= 0 && Col < Vid_NumCols && Row >= 0 && Row < Vid_NumRows))
    {
        Vid_Col = Col;
        Vid_Row = Row;

        if (do_sync)
            VidSyncCur();

        return 0;
    }
    else
        return -1;
}

