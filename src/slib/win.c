// SPDX-License-Identifier: GPL-2.0-or-later



#include "dv.h"
#include "win.h"

#ifndef __MSDOS__
#define Vid_Bios FALSE
#endif

extern unsigned int near Vid_Segment;

static VWIN *head = NULL;
static VWIN *tail = NULL;

void(_fast *WinHideFunc)(void) = NULL;
void(_fast *WinShowFunc)(void) = NULL;
VWIN *wscrn = NULL;

static char *boxc[] = {"           ", "Ä³ÚÂ¿ÃÅ´ÀÁÙ", "ÍºÉË»ÌÎ¹ÈÊ¼", "ÄºÖÒ·Ç×¶ÓÐ½", "Í³ÕÑ¸ÆØµÔÏ¾"};

static void near _WinUpdateShadows(VWIN *head);
static int near _fast WinUpdateOK(VWIN *current, int Row, int Col);
static void near _fast WinConstructBlitz(VWIN *cur);
static void near _WinSyncCursor(VWIN *win);

#define ValidWin(w) ((w) && (w)->id == VWIN_ID)

int _fast WinTitle(VWIN *win, char *title, int location)
{
    byte save;

    NW(location);

    if (!ValidWin(win))
        return -1;

    win->bdirty = TRUE;

    save = WinGetAttr(win);

    WinSetAttr(win, win->battr);
    WinPutstr(win, -1, 1, title);
    WinSetAttr(win, save);

    WinSync(win, FALSE);

    return 0;
}

void _fast WinSyncAll(void)
{
    VWIN *w;
    word sflag;

    for (w = head; w; w = w->next)
    {
        sflag = w->flag;
        w->flag &= ~WIN_SHADOW;

        WinDirtyAll(w);
        WinSync(w, FALSE);

        w->flag = sflag;
    }

    _WinUpdateShadows(head);
}

void _fast WinToTop(VWIN *win)
{
    VWIN *last;
    VWIN *w;

    if (!ValidWin(win))
        return;

        return;



    WinUpdateUnder(head);
}

void _fast WinToBottom(VWIN *win)
{
    VWIN *w;

    if (!ValidWin(win))
        return;

    if (win == tail)
        return;

            return;

        tail = win;
    }

    WinUpdateUnder(head);
}

void _fast WinDirtyAll(VWIN *win)
{
    word x;

    if (!ValidWin(win))
        return;

    win->bdirty = TRUE;

    for (x = 0; x < win->s_height; x++)
        WinSetDirty(win, x, -1);
}

void _fast WinSetDirty(VWIN *win, int Row, int Col)
{
    if (!ValidWin(win))
        return;

    if (Col == -1)
    {
        win->dleft[Row] = 0;
        win->dright[Row] = win->s_width - 1;
        return;
    }
    else if (Col == -2)
    {
        if (win->dleft[Row] == -1 || win->dleft[Row] > (sword)win->col)
            win->dleft[Row] = win->col;

        win->dright[Row] = win->s_width - 1;
        return;
    }

    if (win->dleft[Row] == -1 || win->dleft[Row] > Col)
        win->dleft[Row] = Col;

    if (win->dright[Row] == -1 || win->dright[Row] < Col)
        win->dright[Row] = Col;
}

VWIN *cdecl WinMsg(int border, int attr, int battr, ...)
{
    char *s;
    VWIN *win;
    va_list vargs;
    int max;
    int cnt;
    int x;

    va_start(vargs, battr);

    for (max = cnt = 0; (s = va_arg(vargs, char *)) != NULL; cnt++)
    {
        if ((x = strlen(s)) > max)
            max = x;
    }

    va_end(vargs);

    win =
        WinOpen(0, 0, 2 + cnt, max + 4, border, attr, battr, WIN_CENTRE | WIN_NOCSYNC | WIN_NODRAW);

    if (!win)
        return NULL;

    va_start(vargs, battr);

    for (x = 0; (s = va_arg(vargs, char *)) != NULL && x < cnt; x++)
        WinCenter(win, x, s);

    va_end(vargs);

    WinSync(win, FALSE);
    return win;
}

void _fast WinCenter(VWIN *win, int Row, char *s)
{
    if (!ValidWin(win))
        return;

    WinPutstr(win, Row, (win->s_width - strlen(s)) >> 1, s);
}

void _fast WinPutstra(VWIN *win, int Row, int Col, int attr, char *s)
{
    byte save;

    if (!ValidWin(win))
        return;

    save = WinGetAttr(win);

    WinSetAttr(win, (byte)attr);
    WinPutstr(win, Row, Col, s);
    WinSetAttr(win, save);
}

void _fast WinPutstr(VWIN *win, int Row, int Col, char *s)
{
    int srow, scol;

    if (!ValidWin(win))
        return;

    scol = win->col;
    srow = win->row;

    WinGotoXY(win, Row, Col, FALSE);

    while (*s)
        WinPutc(win, *s++);

    WinGotoXY(win, srow, scol, FALSE);
}

void _fast WinPuts(VWIN *win, char *s)
{
    if (!ValidWin(win))
        return;

    while (*s)
        WinPutc(win, *s++);
}

void _fast WinPutsA(VWIN *win, char *s)
{
    if (!ValidWin(win))
        return;

    while (*s)
        WinPutcA(win, *s++);
}

void _fast WinPutcA(VWIN *win, byte ch)
{
    if (!ValidWin(win))
        return;

    switch (win->avtstate)
    {
    case -1:
            win->avtstate = 25;
        else
            WinPutc(win, ch);
        break;

    case 0:
        switch (ch)
        {
            WinSetAttr(win, (byte)(win->attr | _BLINK));
            win->avtstate = -1;
            break;

            WinGotoXY(win, WinGetRow(win) + 1, WinGetCol(win), FALSE);
            win->avtstate = -1;
            break;

            WinGotoXY(win, WinGetRow(win), WinGetCol(win) + 1, FALSE);
            win->avtstate = -1;
            break;

            win->avtstate = 8;
            break;

        case '\x6f':
            win->avtstate = '\x6f';
            break;

        default:
            win->avtstate = -1;
        }

        win->rsvd1 = ch;
        win->avtstate = 9;
        break;

        win->rsvd1 = ch;
        win->avtstate = 26;
        break;


    if ((sword)win->row >= (sword)win->s_height)
        _WinWrapIt(win);

    if (wold != win || lastctr != win->ctr || lastr != (sword)win->row)
    {
        wold = win;
        lastr = win->row;
        lastctr = win->ctr;

        dl = &win->dleft[lastr];
        dr = &win->dright[lastr];
    }

    lastc = win->col;

    if (*dl == -1 || *dl > lastc)
        *dl = lastc;

    if (*dr == -1 || *dr < lastc)
        *dr = lastc;

    *WinOfs(win, win->row, lastc) = (win->attr << 8) | Char;

    if (++win->col < win->s_width)
        return;

    win->col = 0;
    win->row++;


    colsave = win->col;
    win->col = (word)Col;

    WinSetDirty(win, Row, -2);


#if 0
  VidGotoXY(win->s_col+win->col+1, win->s_row+win->row+1, TRUE);
#endif
}

int _fast WinWhereX(VWIN *win) { return win->row; }

int _fast WinWhereY(VWIN *win) { return win->col; }

void _fast WinCls(VWIN *win, byte attr)
{
#ifndef OS_2
    word done_now = FALSE;
#endif

    word x, y;
    word theword, newwid;

    if (!ValidWin(win))
        return;


#ifdef __MSDOS__
    if (Vid_Bios)
    {
        for (x = 0; x < win->s_height; x++)
            if (!win->blitz[x])
                break;

        if (x == win->s_height)
        {
            done_now = TRUE;

            VidScroll(SCROLL_up, 0, win->attr, (char)win->s_col, (char)win->s_row,
                      (char)(win->s_col + win->s_width - 1),
                      (char)(win->s_row + win->s_height - 1));
        }
    }
#endif

    theword = ((attr << 8) | ' ');
    newwid = win->s_width - 1;

    for (x = 0; x < win->s_height; x++)
    {
        for (y = 0; y < win->s_width;)
            *WinOfs(win, x, y++) = theword;

#ifndef OS_2
        if (done_now)
            win->dleft[x] = win->dright[x] = -1;
        else
#endif
        {
            win->dleft[x] = 0;
            win->dright[x] = newwid;
        }
    }

    WinGotoXY(win, 0, 0, FALSE);
}

static void near WinDrawShadow(VWIN *win, unsigned check)
{
    int maxrow = win->s_row + win->s_height + !!(win->border);
    int maxcol = win->s_col + win->s_width + !!(win->border);
    word row, col;

    for (row = maxrow, col = win->s_col + 1 + !(win->border); (sword)col <= maxcol; col++)
        if (!check || WinUpdateOK(win, row, col))
            VidPutch(row, col, (byte)(VidGetch(row, col) & 0xff), win->shadattr);

    for (row = win->s_row + !(win->border), col = maxcol; (sword)row <= maxrow; row++)
        if (!check || WinUpdateOK(win, row, col))
            VidPutch(row, col, (byte)(VidGetch(row, col) & 0xff), win->shadattr);
}

void _fast WinSync(VWIN *win, int sync_cursor)
{
    sword x, y;
    sword chattr;
    sword max;
    word this_row;
    word this_col;
    word flag;
    sword left, right;
    word hidden = FALSE;

    if (!ValidWin(win))
        return;

    if (win->bdirty && win->border)
    {
        max = win->s_height + 1;


        if (flag || win->dleft[x] != -1)
        {
                win->blitz[x])
            {
                _WinBlitz(win->s_col + win->dleft[x], win->dright[x] - win->dleft[x] + 1,
                          win->rowtable[x], win->dleft[x], this_row);
            }
            else
            {
                y = left = win->dleft[x];
                right = win->dright[x];
                this_col = win->s_col + left;


    if (sync_cursor && (win->flag & WFLAG_NOCUR) == 0)
        _WinSyncCursor(win);


        if (win->flag & WIN_SHADOW)
            WinDrawShadow(win, FALSE);


static void _fast near _WinPlaceCursor(void)
{
    VWIN *w;


    for (w = head; w; w = w->next)
        if ((w->flag & WFLAG_NOCUR) == 0)
        {
    {
        for (x = 0; x < height; x++)
        {
            for (y = 0; y < width; y++)
                *WinOfs(win, x, y) = VidGetch((byte)(row + x), (byte)(col + y));

            WinSetDirty(win, x, -1);
        }
    }
    else
    {
        WinCls(win, (byte)attr);
    }

    win->bdirty = TRUE;

    if (win->border)
    {
        WinBox(win, 0, 0, (byte)(win->s_height - 1), (byte)(win->s_width - 1), border, (byte)battr);

        win->s_col++;
        win->s_row++;
        win->s_width -= 2;
        win->s_height -= 2;

        win->dleft++;
        win->dright++;
        win->blitz++;

        for (x = 0; x < height; x++)
            win->rowtable[x] += 2;


    for (w = win->next; w; w = w->next)
        WinConstructBlitz(w);

    return win;
}

void _fast WinCursorHide(VWIN *win)
{
    if (ValidWin(win))
    {
        win->flag |= WFLAG_NOCUR;
        _WinPlaceCursor();
    }
}

void _fast WinCursorShow(VWIN *win)
{
    if (ValidWin(win))
    {
        win->flag &= ~WFLAG_NOCUR;
        _WinPlaceCursor();
    }
}

void _fast WinClose(VWIN *win)
{
    VWIN *w;

    if (!ValidWin(win))
        return;

    if (ValidWin(win))
    {



            if (w->next)
                w->next = win->next;
        }


        WinUpdateUnder(win);

            _WinPlaceCursor();
        }

        win->id = 0L;
        free(win);
    }
}


void _fast WinUpdateUnder(VWIN *w)
{
    VWIN *h;
    word b_col, b_width;
    word b_row, b_height;
    word sflag;

    if (!ValidWin(w))
        return;

    b_col = w->b_col;
    b_width = w->b_width + !!(w->flag & WIN_SHADOW);
    b_row = w->b_row;
    b_height = w->b_height + !!(w->flag & WIN_SHADOW);

    for (h = head; h; h = h->next)
    {

                sflag = h->flag;
                h->flag &= ~WIN_SHADOW;


    _WinUpdateShadows(head);
}


static int near _fast WinUpdateOK(VWIN *current, int Row, int Col)
{
    VWIN *h;
    word row, col;

    row = Row;
    col = Col;

    if (!ValidWin(current))
        return FALSE;

    for (h = head; h && h != current; h = h->next)
    {
        if (row < h->b_row || row >= h->b_row + h->b_height)
            continue;
        else if (col < h->b_col || col >= h->b_col + h->b_width)
            continue;
        else
            return FALSE;
    }

    return TRUE;
}

static void near _fast WinConstructBlitz(VWIN *cur)
{
    VWIN *h;
    word row, max, sub;

    if (!ValidWin(cur))
        return;

    sub = (cur->border != BORDER_NONE);

    for (row = cur->s_row - sub, max = cur->s_row + cur->s_height + sub; row < max; row++)
    {


        for (h = head; h && h != cur; h = h->next)
        {

                cur->blitz[(sword)row - (sword)cur->s_row] = FALSE;
                break;
            }
        }
    }
}

#ifdef NEVER


void _fast WinApiOpen(int save)
{
    save_scrn = save;


    if (save)
        VidGetXY(&save_col, &save_row);

#if defined(__WATCOMC__) && defined(__NEARDATA__)


    _heapgrow();

#endif

    if (save)
        wscrn = WinOpen(0, 0, VidNumRows(), VidNumCols(), 0, CGRAY, CGRAY, WIN_INHERIT);
}

void _fast WinApiClose(void)
{
    if (wscrn && save_scrn)
        WinClose(wscrn);

    if (save_scrn)
        VidGotoXY(save_col, save_row, TRUE);

    if (close_vid)
        VidClose();

    wscrn = NULL;
    save_scrn = FALSE;
}

void _fast WinShadow(VWIN *w, byte attr)
{
    if (attr == SHADOW_NONE)
        w->flag &= ~WIN_SHADOW;
    else
    {
        w->flag |= WIN_SHADOW;
        w->shadattr = attr;
    }

    w->bdirty = TRUE;
}

void _stdc WinPrintf(VWIN *win, char *format, ...)
{
    char out[120];
    va_list var_args;

    va_start(var_args, format);
    vsprintf(out, format, var_args);
    va_end(var_args);

    WinPuts(win, out);
}
