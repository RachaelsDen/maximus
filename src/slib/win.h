// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __WIN_H_DEFINED
#define __WIN_H_DEFINED

#include "dv.h"
#include "typedefs.h"

#define VWIN_ID 0x4e495756L


#define SHADOW_NONE 0xff

#define BORDER_NONE 0
#define BORDER_SINGLE 1
#define BORDER_DOUBLE 2
#define BORDER_HSVD 3
#define BORDER_HDVS 4

#define TITLE_LEFT 0
#define TITLE_MIDDLE 1
#define TITLE_RIGHT 2


    byte far **rowtable;
    byte far **orig_rt;

    sword *dleft;
    sword *orig_dl;

    sword *dright;
    sword *orig_dr;

    byte *blitz;
    byte *orig_blitz;

    char far *buf;

    sword row;
    sword col;
    byte attr;
    byte battr;
    word border;
    word bdirty;

    word s_col;
    word s_row;
    word b_col;
    word b_row;
    word s_width;
    word s_height;
    word b_width;
    word b_height;

    sbyte avtstate;
    byte rsvd1;
    byte lockback;
    byte shadattr;
    word flag;
} VWIN;

typedef struct _pickopt
{
    char *name;
    int value;
} PLIST;

#define PICK_UP -1
#define PICK_DOWN -2
#define PICK_SELECT -3
#define PICK_ABORT -4

typedef struct _vpicklist
{
    VWIN *win;

    int row;
    int col;

    int height;
    int width;

    PLIST *items;

    int it_current;
    int it_last;
    int it_top;

    int col_item;
    int col_select;

} VPICK;

#define WinOfs(win, row, col) ((word far *)(win->rowtable[(row)] + ((col) << 1)))
#define WinGetAttr(win) (win->attr)

void _fast WinPutch(VWIN *win, int Col, int Row, byte Char, byte Attr);
void _fast WinVline(VWIN *win, int scol, int srow, int erow, int border, byte attr);
void _fast WinHline(VWIN *win, int scol, int srow, int ecol, int border, byte attr);
void _fast WinBox(VWIN *win, int scol, int srow, int ecol, int erow, int border, byte attr);
void _fast WinGotoXY(VWIN *win, int row, int col, int do_sync);
void _fast WinCls(VWIN *win, byte attr);
void _fast WinSync(VWIN *win, int sync_cursor);
VWIN *_fast WinOpen(int col, int row, int width, int height, int border, int attr, int battr,
                    int flag);
void _fast WinClose(VWIN *win);
void _fast WinScrl(VWIN *win, int dir, int srow, int erow, int attr);
void _fast WinPutc(VWIN *win, byte Char);
void _fast WinCleol(VWIN *win, int Col, int Row, byte Attr);
void _fast WinPuts(VWIN *win, char *s);
void _fast WinDirtyAll(VWIN *win);
void _fast WinSetDirty(VWIN *win, int Row, int Col);
void _fast WinUpdateUnder(VWIN *w);
void _fast WinApiOpen(int save);
void _fast WinApiClose(void);
void _fast WinSetAttr(VWIN *win, byte Attr);
int _fast WinWhereX(VWIN *win);
int _fast WinWhereY(VWIN *win);
VWIN *cdecl WinMsg(int border, int attr, int battr, ...);
void _fast WinCenter(VWIN *win, int Row, char *s);
void _fast WinPutstr(VWIN *win, int Row, int Col, char *s);
void _fast WinToTop(VWIN *win);
void _fast WinToBottom(VWIN *win);
void _fast WinPutsA(VWIN *win, char *s);
void _fast WinPutcA(VWIN *win, byte ch);
void _fast WinSyncAll(void);
int _fast WinTitle(VWIN *win, char *title, int location);
void _fast WinPutstra(VWIN *win, int Row, int Col, int attr, char *s);
VPICK *_fast WinCreatePickList(VWIN *win, int row, int col, int height, int col_item,
                               int col_select, PLIST *picklist, int it_current);
int _fast WinPickAction(VPICK *vp, int action);
int _fast WinClosePickList(VPICK *vp);
void pascal _WinBlitz(word start_col, word num_col, char far *from_ofs, sword win_start_col,
                      word this_row);
void _fast WinCursorHide(VWIN *win);
void _fast WinCursorShow(VWIN *win);
void _fast WinShadow(VWIN *win, byte attr);
void _stdc WinPrintf(VWIN *win, char *format, ...);

#define WinGetRow(win) WinWhereX(win)
#define WinGetCol(win) WinWhereY(win)
#define WinGetNumRows(win) ((win)->s_height)
#define WinGetNumCols(win) ((win)->s_width)

extern VWIN *wscrn;

#endif
