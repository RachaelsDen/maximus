// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include "tui.h"
#include <dos.h>

#ifdef __MSDOS__


    CallMouse(&ax, button, col, row);

    *col >>= 3;
    *row >>= 3;
}

void _fast MouseSetPos(word col, word row)
{
    word ax = 4;
    word c = col, r = row;

    if (!has_mouse)
        return;

    c <<= 3;
    r <<= 3;

    CallMouse(&ax, NULL, &c, &r);
}

void _fast MouseGetPress(word button, word *state, word *count, word *col, word *row)
{
    word ax = 5;
    word bx = button;

    if (!has_mouse)
        return;

    CallMouse(&ax, &bx, col, row);
    *state = ax;
    *count = bx;

    *col >>= 3;
    *row >>= 3;
}

void _fast MouseGetRelease(word button, word *state, word *count, word *col, word *row)
{
    word ax = 6;
    word bx = button;

    if (!has_mouse)
        return;

    CallMouse(&ax, &bx, col, row);

    *state = ax;
    *count = bx;

    *col >>= 3;
    *row >>= 3;
}

void _fast MouseSetRange(word col, word row, word n_col, word n_row)
{
    word ax;
    word cx, dx;

    if (!has_mouse)
        return;

    ax = 7;
    cx = col;
    dx = col + n_col - 1;

    cx <<= 3;
    dx <<= 3;

    CallMouse(&ax, NULL, &cx, &dx);

    ax = 8;
    cx = row;
    dx = row + n_row - 1;

    cx <<= 3;
    dx <<= 3;

    CallMouse(&ax, NULL, &cx, &dx);
}

void _fast MouseSetSoftCursor(word scrmask, word curmask)
{
    word ax, bx, cx, dx;

    if (!has_mouse)
        return;

    ax = 0x0a;
    bx = 0;
    cx = scrmask;
    dx = curmask;

    CallMouse(&ax, &bx, &cx, &dx);
}

void _fast MouseClose(void)
{
    if (!has_mouse)
        return;

    MouseHide();
    has_mouse = FALSE;
}

void _fast MouseFlush(void) {}

#ifdef NEVER

void _fast MouseSetMickey(word xmickey, word ymickey)
{
    word ax = 0x0f;
    word cx = xmickey;
    word dx = ymickey;

    CallMouse(&ax, NULL, &cx, &dx);
}

#define EVT_MOVE 0x01
#define EVT_PLEFT 0x02
#define EVT_RLEFT 0x04
#define EVT_PRIGHT 0x08
#define EVT_RRIGHT 0x10
#define EVT_PMIDDLE 0x20
#define EVT_RMIDDLE 0x40

void _fast MouseSetEvent(word evtmask, void(far *evtproc)(void))
{
    union REGS r;
    struct SREGS sr;

    if (!has_mouse)
        return;

    sr.es = FP_SEG(evtproc);
    r.x.ax = 0x0c;
    r.x.cx = evtmask;
    r.x.dx = FP_OFF(evtproc);

    int86x(0x33, &r, &r, &sr);
}

