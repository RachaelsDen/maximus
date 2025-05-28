// SPDX-License-Identifier: GPL-2.0-or-later



#include "dv.h"
#include "prog.h"
#include <dos.h>

#ifdef __MSDOS__

void far pascal RegScrollUp(int *col, int *row)
{
    NW(col);
    RegScroll(1);

    *row = Vid_NumRows - 1;
}

void _fast RegScroll(int lines)
{
    union REGS r;

