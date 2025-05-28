// SPDX-License-Identifier: GPL-2.0-or-later


#if defined(OS_2)

#include "dv.h"
#include "prog.h"
#include "tui_mous.h"
#include <stdio.h>
#include <stdlib.h>

#define INCL_MOU
#define INCL_NOPM
#define INCL_DOS
#include "pos2.h"

    }
    else
    {
        *button = b;
        *col = c;
        *row = r;
    }
}

void _fast MouseSetPos(word col, word row)
{
    PTRLOC pl;
    if (!has_mouse)
        return;
    pl.col = col;
    pl.row = row;
    // MouSetPtrPos(&pl, hm);
}

void _fast MouseSetRange(word col, word row, word n_col, word n_row)
{
    NW(col);
    NW(row);
    NW(n_col);
    NW(n_row);

    return;
}

void _fast MouseSetSoftCursor(word scrmask, word curmask)
{
    NW(scrmask);
    NW(curmask);
}

void _fast MouseClose(void)
{
    if (!has_mouse)
        return;

    MouseHide();
    has_mouse = FALSE;
    MouClose(hm);
}

void _fast MouseFlush(void)
{
    if (has_mouse)
    {
        MouFlushQue(hm);
    }
}

#elif defined(NT)

#include "dv.h"
#include "prog.h"
#include "tui_mous.h"
#include <stdio.h>
#include <stdlib.h>

word has_mouse = FALSE;

sword _fast MouseOpen(void) { return FALSE; }

void _fast MouseShow(void) {}

void _fast MouseHide(void) {}

void _fast MouseStatus(word *button, word *col, word *row) {}

void _fast MouseSetPos(word col, word row) {}

void _fast MouseSetRange(word col, word row, word n_col, word n_row) {}

void _fast MouseSetSoftCursor(word scrmask, word curmask) {}

void _fast MouseClose(void) {}

void _fast MouseFlush(void) {}
#endif
