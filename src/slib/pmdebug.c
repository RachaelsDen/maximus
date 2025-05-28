// SPDX-License-Identifier: GPL-2.0-or-later



#define INCL_WIN
#define INCL_DOS

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    WinShowWindow(hwndDbgFrame, TRUE);

                    cx / 2, cy / 4,
                    SWP_ACTIVATE | SWP_SIZE | SWP_MOVE | (fMinimize ? SWP_MINIMIZE : 0));
}

void DbgEnd(void)
{
    if (!fBegan)
        return;

    fBegan = FALSE;
    WinDestroyWindow(hwndDbgFrame);
    hwndDbgList = (HWND)0;
}

static MRESULT EXPENTRY DebugProc(HWND hwnd, MSGDEF msg, MPARAM mp1, MPARAM mp2)
{
    RECTL rcl;
    HPS hps;

    switch (msg)
    {
    case WM_CREATE:

        hwndDbgList = WinCreateWindow(
            hwnd, WC_LISTBOX, "lb", WS_VISIBLE | LS_NOADJUSTPOS | LS_HORZSCROLL, 0, 0,
            (SHORT)rcl.xRight, (SHORT)rcl.yTop, hwnd, HWND_TOP, LB_ID, NULL, NULL);

        WinShowWindow(hwndDbgList, TRUE);
        break;

    case WM_SIZE:
        WinDestroyWindow(hwndDbgFrame);
        return 0;
    }

    return WinDefWindowProc(hwnd, msg, mp1, mp2);
}

void DbgPrint(char *txt)
{
    if (!hwndDbgList)
        return;

    WinSendMsg(hwndDbgList, LM_INSERTITEM, MPFROMSHORT(LIT_END), MPFROMP(txt));

    if (++cItem >= cMaxItem)
    {
        WinSendMsg(hwndDbgList, LM_DELETEITEM, MPFROMSHORT(0), 0);
        cItem--;
    }


    WinPostMsg(hwndDbgList, LM_SELECTITEM, MPFROMSHORT(cItem - 1), MPFROMSHORT(TRUE));
}

void _stdc DbgPrintfp(char *format, ...)
{
    va_list var_args;
    static char string[512];

    va_start(var_args, format);
    vsprintf(string, format, var_args);
    va_end(var_args);

    DbgPrintp(string);
}
