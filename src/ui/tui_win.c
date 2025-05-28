// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include "tui.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void _stdc WinErr(char *format, ...)
{
    char out[120];
    va_list var_args;
    VWIN *win;

    va_start(var_args, format);
    vsprintf(out, format, var_args);
    va_end(var_args);

    if ((win = WinOpen(0, 0, 3, strlen(out) + 4, BORDER_DOUBLE, col(CWHITE | _RED),
                       col(CYELLOW | _RED), WIN_CENTRE | WIN_NOCSYNC)) == NULL)
        return;

    WinPutc(win, ' ');
    WinPuts(win, out);
    WinSync(win, TRUE);
    kgetch();
    MouseFlush();
    WinClose(win);
}


static word near InfMaxWid(char *txt)
{
    word wid = 0, cwid = 0;

    while (*txt)
        if (*txt++ == '\n')
        {
            if (cwid > wid)
                wid = cwid;

            cwid = 0;
        }
        else
            cwid++;

    return (cwid > wid ? cwid : wid);
}

static char *yn_text = NULL;


word _stdc WinGetYN(char *fmt, ...)
{
    char *out;
    va_list var_args;
    HVMENU hAsk;
    HVOPT o;
    word maxwid;
    word maxlines;

    if ((out = malloc(strlen(fmt) + 240)) == NULL)
        return 0;

    va_start(var_args, fmt);
    vsprintf(out, fmt, var_args);
    va_end(var_args);

    maxwid = InfMaxWid(out) + 3;
    maxlines = InfMaxLines(out);

    yn_text = out;

    dlg_getyn->start_x = dlg_getyn->start_y = -1;

    dlg_getyn->sizex = max(maxwid, 10);
    dlg_getyn->sizey = 8 + maxlines;

    o = dlg_getyn->opt;
    o->cx = dlg_getyn->sizex / 2 - 11;
    o->cy = dlg_getyn->sizey - 6;
    o++;
    o->cx = dlg_getyn->sizex / 2 + 1;
    o->cy = dlg_getyn->sizey - 6;

    hAsk = TuiRegisterMenu(dlg_getyn);
    TuiExecMenu(hAsk);
    TuiDestroyMenu(hAsk);

    free(out);

    return (dlg_ok == 1);
}

static char *inf_text = NULL;

MenuFunction(ShowInfText)
{
    WinGotoXY(opt->parent->win, 1, 0, FALSE);

    WinPuts(opt->parent->win, inf_text);
    return 0;
}

STD_DIALOG(dlg_inf, -1, -1, BORDER_SINGLE, MENU_NHOT, 60, 16)
DLG_BUF("1 ; ~OK ", 24, 10, &dlg_ok, ShowInfText)
END_MENU

