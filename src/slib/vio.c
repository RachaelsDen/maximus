// SPDX-License-Identifier: GPL-2.0-or-later



#if defined(OS_2)

#include <string.h>
#define INCL_NOPM
#define INCL_VIO
#define INCL_DOS
#include "compiler.h"
#include "dv.h"
#include "modem.h"
#include "typedefs.h"
#include <assert.h>
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>

static BYTE Vcurattr = 7;
static USHORT Vnumcols;
static USHORT Vnumrows;
static USHORT curRow, curCol;

#define lastRow (Vnumrows - 1)
#define lastCol (Vnumcols - 1)

void _stdc Vidfcur(void);

static PBYTE lvb = 0L;
static USHORT lvbLen;
static int isHidden = FALSE;

#pragma check_stack(off)

word _fast VidOpen(int has_snow, int desqview, int dec_rows)
{
    VIOMODEINFO viomi;

    NW(has_snow);
    if (dec_rows)
    {
        Vnumrows--;

        while (curRow >= Vnumrows)
        {
            VioScrollUp(0, 0, 0xFFFF, 0xFFFF, 1, " \x7", 0);
            curRow--;
        }
    }
#endif

    if (!lvb)
    {
#ifdef __FLAT__
        ULONG ul;

        VioGetBuf((PULONG)&ul, &lvbLen, 0);
        lvb = (PBYTE)thunk16to32(ul);
#else
        VioGetBuf((PULONG)&lvb, &lvbLen, 0);
#endif
    }

    return (1);
}

int _fast VidClose(void)
{
    lvb = NULL;
    return (0);
}

int _fast VidGotoXY(int Col, int Row, int sync)
{
    if (isHidden)
    {
        VIOCURSORINFO vct;

        VioGetCurType(&vct, 0);
        vct.attr = 0;
        isHidden = FALSE;
        VioSetCurType(&vct, 0);
    }
    curRow = min((USHORT)Row - 1, lastRow);
    curCol = min((USHORT)Col - 1, lastCol);
    if (sync)
        VioSetCurPos(curRow, curCol, 0);
    return (0);
}

void _stdc Vidfcur(void) { VioSetCurPos(curRow, curCol, 0); }

void _fast VidCls(char Attribute)
{
    BYTE cell[2];
    curRow = curCol = 0;
    cell[0] = ' ';
    cell[1] = Attribute;
    VioScrollUp(0, 0, -1, -1, -1, cell, 0);
    Vidfcur();
}

void _fast VidSetAttr(char Attribute) { Vcurattr = Attribute; }

void _fast VidGetXY(int *Col, int *Row)
{
    *Col = curCol + 1;
    *Row = curRow + 1;
}

int _fast VidWhereX(void) { return curCol + 1; }

int _fast VidWhereY(void) { return curRow + 1; }

void pascal VidCleol(void)
{
    BYTE cell[2];
    cell[0] = ' ';
    cell[1] = Vcurattr;

    if (curRow < Vnumrows && curCol < Vnumcols)
        VioWrtNCell(cell, Vnumcols - curCol, curRow, curCol, 0);
}

int _fast VidNumRows(void) { return Vnumrows; }
int _fast VidNumCols(void) { return Vnumcols; }

char _fast VidGetAttr(void) { return Vcurattr; }

void cdecl VidPutch(int Row, int Col, char Char, char Attr)
{
    VioWrtCharStrAtt(&Char, sizeof(Char), Row, Col, &Attr, 0);
}

int cdecl VidGetch(int Row, int Col)
{
    BYTE b;
#if 0
      USHORT l = sizeof(b);
      VioReadCharStr(&b, &l, Row, Col, 0);
#else
    b = lvb[(Row * Vnumcols + Col) * 2];
#endif
    return (int)b;
}

void _fast VidBios(int use_bios) { use_bios = use_bios; }

void _fast VidHideCursor(void)
{
    VIOCURSORINFO vct;

    VioGetCurType(&vct, 0);
    isHidden = TRUE;
    vct.attr = 0xffff;
    VioSetCurType(&vct, 0);
}


void pascal VidScroll(char Direction, char NumOfLines, char Attribute, char LeftCol, char TopRow,
                      char RightCol, char BotRow)
{
    char bCell[2];

    bCell[0] = ' ';
    bCell[1] = Attribute;

    if (Direction == SCROLL_up)
        VioScrollUp(TopRow, LeftCol, BotRow, RightCol, NumOfLines, bCell, 0);
    else
        VioScrollDn(TopRow, LeftCol, BotRow, RightCol, NumOfLines, bCell, 0);
}

#elif defined(NT)

#include "compiler.h"
#include "dv.h"
#include "modem.h"
#include "typedefs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static BYTE Vcurattr = 7;
static USHORT Vnumcols;
static USHORT Vnumrows;
static USHORT curRow, curCol;

#define lastRow (Vnumrows - 1)
#define lastCol (Vnumcols - 1)

void _stdc Vidfcur(void);

static int isHidden = FALSE;
HANDLE hStdout;

#pragma check_stack(off)

word _fast VidOpen(int has_snow, int desqview, int dec_rows)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    NW(has_snow);
    NW(desqview);
    NW(dec_rows);

    fflush(stdout);

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &csbi);

    Vnumcols = csbi.dwSize.X;
    Vnumrows = csbi.dwSize.Y;

    curCol = csbi.dwCursorPosition.X;
    curRow = csbi.dwCursorPosition.Y;

    return 1;
}

int _fast VidClose(void) { return (0); }

int _fast VidGotoXY(int Col, int Row, int sync)
{
    if (isHidden)
    {
        CONSOLE_CURSOR_INFO cci;

        GetConsoleCursorInfo(hStdout, &cci);
        cci.bVisible = TRUE;
        SetConsoleCursorInfo(hStdout, &cci);
        isHidden = FALSE;
    }

    curRow = min((USHORT)Row - 1, lastRow);
    curCol = min((USHORT)Col - 1, lastCol);

    if (sync)
    {
        COORD c;

        c.Y = curRow;
        c.X = curCol;

        SetConsoleCursorPosition(hStdout, c);
    }

    return (0);
}

void _stdc Vidfcur(void)
{
    COORD c;

    c.Y = curRow;
    c.X = curCol;

    SetConsoleCursorPosition(hStdout, c);
}

void _fast VidCls(char Attribute)
{
    SMALL_RECT sr;
    CHAR_INFO ci;
    COORD c;

    ci.Char.AsciiChar = ' ';
    ci.Attributes = Attribute;

    sr.Left = 0;
    sr.Top = 0;
    sr.Bottom = lastRow;
    sr.Right = lastCol;

    c.X = Vnumcols;
    c.Y = Vnumrows;

    ScrollConsoleScreenBuffer(hStdout, &sr, NULL, c, &ci);
}

void _fast VidSetAttr(char Attribute) { Vcurattr = Attribute; }

void _fast VidGetXY(int *Col, int *Row)
{
    *Col = curCol + 1;
    *Row = curRow + 1;
}

int _fast VidWhereX(void) { return curCol + 1; }

int _fast VidWhereY(void) { return curRow + 1; }

void pascal VidCleol(void)
{
    SMALL_RECT sr;
    CHAR_INFO ci;
    COORD c;

    ci.Char.AsciiChar = ' ';
    ci.Attributes = Vcurattr;

    sr.Left = curCol;
    sr.Top = curRow;
    sr.Bottom = curRow;
    sr.Right = lastCol;

    c.X = Vnumcols;
    c.Y = Vnumrows;

    if (curRow < Vnumrows && curCol < Vnumcols)
        ScrollConsoleScreenBuffer(hStdout, &sr, NULL, c, &ci);
}

int _fast VidNumRows(void) { return Vnumrows; }
int _fast VidNumCols(void) { return Vnumcols; }

char _fast VidGetAttr(void) { return Vcurattr; }

void cdecl VidPutch(int Row, int Col, char Char, char Attr)
{
    CHAR_INFO ci;
    COORD c, origc;
    SMALL_RECT sr;

    ci.Char.AsciiChar = Char;
    ci.Attributes = Attr;

    c.X = c.Y = 1;
    origc.X = origc.Y = 0;

    sr.Top = sr.Bottom = Row;
    sr.Left = sr.Right = Col;

    WriteConsoleOutput(hStdout, &ci, c, origc, &sr);
}

int cdecl VidGetch(int Row, int Col)
{
    CHAR_INFO ci;
    COORD c, destc;
    SMALL_RECT sr;

    c.X = c.Y = 1;
    destc.X = destc.Y = 0;

    sr.Top = sr.Bottom = Row;
    sr.Left = sr.Right = Col;

    ReadConsoleOutput(hStdout, &ci, c, destc, &sr);

    return (ci.Char.AsciiChar | (ci.Attributes << 8));
}

void _fast VidBios(int use_bios) { NW(use_bios); }

void _fast VidHideCursor(void)
{
    CONSOLE_CURSOR_INFO cci;

    if (!isHidden)
    {
        GetConsoleCursorInfo(hStdout, &cci);
        cci.bVisible = FALSE;
        SetConsoleCursorInfo(hStdout, &cci);
        isHidden = TRUE;
    }
}

#define MAX_COL 160

static CHAR_INFO aci[MAX_COL];


    if (num_col > MAX_COL)
        num_col = MAX_COL;

    --from;
    --pci;

    do
    {
        (++pci)->Char.AsciiChar = *++from;
        pci->Attributes = *++from;
    } while (--num_col);

    WriteConsoleOutput(hStdout, aci, c, origc, &sr);
}


#include "compiler.h"
#include "dv.h"
#include "modem.h"
#include "typedefs.h"
#include "viocurses.h"
#include <assert.h>
#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static BYTE Vcurattr = 7;
static USHORT Vnumcols;
static USHORT Vnumrows;
static USHORT curRow, curCol;

#define lastRow (Vnumrows - 1)
#define lastCol (Vnumcols - 1)

void setsize()
{
    if (!stdscr)
    {
        Vnumcols = atoi(getenv("COLS") ?: "80");
        Vnumrows = atoi(getenv("ROWS") ?: "25");
    }
    else
    {
        getmaxyx(stdscr, Vnumrows, Vnumcols);
        getyx(stdscr, curRow, curCol);
        setscrreg(0, lastRow);
    }
}

void resize(int sig)
{
    if (stdscr)
    {

#if 0
#endif

    return 1;
}

int VidClose(void)
{
    if (stdscr)
{

    chtype chbuf[num_col];
    int i;
    int ch, attr;
    unsigned char *start;
#ifdef MANUAL_SCROLL
    int newlineCount = 0;
#endif

    start = (unsigned char *)(from_ofs + (win_start_col * 2));

    for (i = 0; i < num_col; i++)
    {
#ifdef BIG_ENDIAN
        attr = start[i * 2];
        ch = start[(i * 2) + 1];
#else
        ch = start[i * 2];
        attr = start[(i * 2) + 1];
#endif

#ifdef MANUAL_SCROLL
        if (ch == '\n')
            newlineCount++;
#endif
        chbuf[i] = ch | (attr & FOREGROUND_INTENSITY ? A_NORMAL : A_DIM);
    }

#ifdef DEBUG_WINBLITZ
    {
        char buf[num_col + 1];

        for (i = 0; i < num_col; i++)
            buf[i] = ((start[i * 2] == '\n') ? ' ' : start[i * 2]);

        buf[i] = (char)0;
    }
#endif

#ifdef MANUAL_SCROLL

        scrl(newlineCount);
        if (newlineCount < this_row)
            this_row -= newlineCount;
        else
            this_row = 0;
    }
#endif

    if (stdscr)
    {
        move(this_row, start_col);
        addchnstr(chbuf, num_col);
        refresh();
    }

    return;
}

#endif

void pascal VidSyncDVWithForce(int fForce)
{
#ifndef UNIX
    // not implemented
    NW(fForce);
#else
    if (stdscr)
        refresh();
#endif
}

void pascal VidSyncDV(void)
{
    if (stdscr)
        refresh();
}
