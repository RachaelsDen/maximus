// SPDX-License-Identifier: GPL-2.0-or-later



#include "dv.h"
#include "prog.h"

#ifdef __MSDOS__

void _fast VidGetXY(int *Col, int *Row)
{
    *Col = Vid_Col + 1;
    *Row = Vid_Row + 1;
}

