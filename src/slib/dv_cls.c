// SPDX-License-Identifier: GPL-2.0-or-later



#include "dv.h"
#include "prog.h"

#ifdef __MSDOS__

void _fast VidCls(char Attribute)
{
    VidScroll(SCROLL_up, 0, Attribute, 0, 0, (char)(Vid_NumCols - 1), (char)(Vid_NumRows - 1));
    VidGotoXY(1, 1, TRUE);
}

