// SPDX-License-Identifier: GPL-2.0-or-later


#define INCL_PM
#define INCL_DOS
#define INCL_VIO
#define INCL_AVIO

#include "max.h"
#include "mcp.h"
#include "pmdebug.h"
#include "pos2.h"
#include "sm.h"
#include "smrc.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

int AvioPrintf(LINEINFO *pli, char *format, ...);
extern HPIPE hp;
extern char szViewClass[];

static void near AvioCls(HVPS hvps, int attr)
{
    byte cell[2];

    cell[0] = ' ';
    cell[1] = (byte)attr;

    VioScrollDn(0, 0, VIO_HEIGHT - 1, VIO_WIDTH - 1, VIO_HEIGHT, &cell, hvps);
}

static void near loc_putc(LINEINFO *pli, int ch)
{
    byte b = ch;

    if (ch == 8)
    {
        if (pli->usCurCol)
            pli->usCurCol--;

        return;
    }
    else if (ch == 13)
    {
        pli->usCurCol = 0;
        return;
    }

    if (ch == 10)
        pli->usCurRow++;
    else
    {
        VioWrtCharStrAtt(&b, 1, pli->usCurRow, pli->usCurCol++, &pli->avp.curattr, pli->hvps);
    }

    if (pli->usCurCol == VIO_WIDTH)
    {
        pli->usCurCol = 0;
        pli->usCurRow++;
    }

    if (pli->usCurRow >= VIO_HEIGHT)
    {
        byte cell[2];

        cell[0] = ' ';
        cell[1] = pli->avp.curattr;

        VioScrollUp(0, 0, VIO_HEIGHT - 1, VIO_WIDTH - 1, 1, &cell, pli->hvps);
        pli->usCurRow--;
    }
}


            if (pli->avp.last_cc == -1)
            {
                pli->avp.save_cx = pli->usCurRow + 1;
                pli->avp.last_cc = pli->usCurCol + 1;
            }

            for (pli->avp.x = 0; pli->avp.x < (word)(9 - (pli->avp.last_cc % 8)); pli->avp.x++)
            {
                loc_putc(pli, ' ');
            }

            pli->avp.last_cc = -1;
            break;

        case 10:
            pli->usCurCol = 0;

            if (++pli->usCurRow >= VIO_HEIGHT)
            {
                byte cell[2];

                cell[0] = ' ';
                cell[1] = pli->avp.curattr;

                VioScrollUp(0, 0, VIO_HEIGHT - 1, VIO_WIDTH - 1, 1, &cell, pli->hvps);
                pli->usCurRow--;
            }
            break;

        case 12:
            break;

        default:
            loc_putc(pli, ch);
            break;
        }
    }
    else
        switch (pli->avp.state)
        {
        case 0:
            switch (ch)
            {
                pli->avp.state = 8;
                break;

                pli->avp.state = 12;
                break;

                break;

            {
                pli->avp.curattr = (char)ch;
                pli->avp.state = -1;
            }
            else
                pli->avp.state = 2;
            break;

            pli->avp.save_cx = (unsigned char)ch;
            pli->avp.state = 10;
            break;

            pli->avp.save_cx = (unsigned char)ch;
            pli->avp.state = 13;
            break;

            pli->avp.y = pli->usCurRow + 1;
            pli->avp.z = pli->usCurCol + 1;
            pli->avp.a = pli->avp.save_cx;
            pli->avp.state = -1;

            AvioPrintf(pli, "\x16\x01%c", pli->avp.a);

            for (pli->avp.x = 0; pli->avp.x < pli->avp.s2; pli->avp.x++)
                AvioPrintf(pli, "\x16\x08%c%c\x19 %c", pli->avp.y + pli->avp.x, pli->avp.z,
                           (char)ch + 1);

            AvioPrintf(pli, "\x16\x08%c%c", pli->avp.y, pli->avp.z);
            break;

            pli->avp.s2 = ch;
            pli->avp.state = 17;
            break;

            pli->avp.y = pli->usCurRow + 1;
            pli->avp.z = pli->usCurCol + 1;
            pli->avp.a = pli->avp.save_cx;
            pli->avp.state = -1;

            AvioPrintf(pli, "\x16\x01%c", pli->avp.a);

            for (pli->avp.x = 0; pli->avp.x < pli->avp.s3; pli->avp.x++)
                AvioPrintf(pli, "\x16\x08%c%c\x19%c%c", pli->avp.y + pli->avp.x, pli->avp.z,
                           pli->avp.s2, ch + 1);

            AvioPrintf(pli, "\x16\x08%c%c", pli->avp.y, pli->avp.z);
            break;

        {
            word x;
            byte c;
            int uch;

            c = (byte)pli->avp.save_cx;

            uch = (byte)ch;

            for (x = 0; x < uch; x++)
                loc_putc(pli, c);

            pli->avp.state = -1;
        }
        break;

        case 30:
            pli->avp.save_cx = (unsigned char)ch;
            pli->avp.x = 0;
            pli->avp.state = 31;
            break;

        case 31:
            if (pli->avp.x < 24 && pli->avp.x < pli->avp.save_cx)
                pli->avp.str2[pli->avp.x++] = (char)ch;
            else
            {
                word y;

                pli->avp.str2[pli->avp.x] = '\0';
                pli->avp.state = -1;

                pli->avp.uch = (byte)ch;

                for (y = 0; y < pli->avp.uch; y++)
                    AvioPrintf(pli, "%s", pli->avp.str2);
            }
            break;

        default:
            pli->avp.state = -1;
            break;
        }
}

void AvioPuts(LINEINFO *pli, char *psz)
{
    while (*psz)
        AvioPutc(pli, *psz++);
}

int AvioPrintf(LINEINFO *pli, char *format, ...)
{
    va_list var_args;
    int x;

    char string[MAX_PRINTF];

    if (strlen(format) >= MAX_PRINTF)
        return -1;

    va_start(var_args, format);
    x = vsprintf(string, format, var_args);
    va_end(var_args);

    AvioPuts(pli, string);
    return x;
}


    if (cbGot)
        while (--cbGot)
            AvioPutc(pli, *++pb);

    VioSetCurPos(pli->usCurRow, pli->usCurCol, pli->hvps);
    //  WinInvalidateRect(hwnd, NULL, FALSE);
}

    pdh = (VIO_DUMP_HDR *)pb;
    usHeight = pdh->bHeight;
    usWidth = pdh->bWidth;
    pli->usCurRow = pdh->bCurRow;
    pli->usCurCol = pdh->bCurCol;
    pli->avp.curattr = pdh->bCurAttr;

    pb = (char *)(pdh + 1);


    VioSetCurPos(pli->usCurRow, pli->usCurCol, pli->hvps);


MRESULT EXPENTRY ViewProc(HWND hwnd, MSGDEF msg, MPARAM mp1, MPARAM mp2)
{
    LINEINFO *pli;
    HPS hps;

    switch (msg)
    {
    case WM_CREATE:
    {
        HWND hwndSys;
        HWND hwndFrame;


        WinSendMsg(hwndSys, MM_DELETEITEM, MPFROM2SHORT(SC_MAXIMIZE, TRUE), MPFROMLONG(0));

        WinSendMsg(hwndSys, MM_DELETEITEM, MPFROM2SHORT(SC_SIZE, TRUE), MPFROMLONG(0));

        WinSendMsg(hwndSys, MM_DELETEITEM, MPFROM2SHORT(SC_RESTORE, TRUE), MPFROMLONG(0));
        break;
    }

    case WM_PAINT:
        pli = WinQueryWindowPtr(hwnd, 0);
        hps = WinBeginPaint(hwnd, 0, NULL);
        VioShowPS(VIO_HEIGHT, VIO_WIDTH, 0, pli->hvps);
        WinEndPaint(hps);
        break;

    case WM_SIZE:
        return WinDefAVioWindowProc(hwnd, msg, (ULONG)mp1, (ULONG)mp2);

    case WM_CLOSE:
        WinDestroyWindow(WinQWindow(hwnd, QW_PARENT));
        return 0;

    case SM_VIO:

        ViewVioDump(hwnd, (LINEINFO *)WinQueryWindowPtr(hwnd, 0), PVOIDFROMMP(mp2));

        free(PVOIDFROMMP(mp2));
        break;

    case WM_CHAR:
#if 0
        pli = WinQueryWindowPtr(hwnd, 0);


        VioAssociate(NULL, pli->hvps);
        VioDestroyPS(pli->hvps);


        WinSetWindowPtr(pli->hwndClient, 0, pli);


        AvioCls(pli->hvps, 0x07);


        VioGetDeviceCellSize((PSHORT)&pli->usCellHeight, (PSHORT)&pli->usCellWidth, pli->hvps);


        WinSetWindowPos(pli->hwndFrame, HWND_TOP, 0, 0, rcl.xRight - rcl.xLeft,
                        rcl.yTop - rcl.yBottom, SWP_SIZE | SWP_SHOW | SWP_ZORDER);


        McpSendMsg(hp, CLMSG_BEGINMONITOR, &pli->tid, 1);
    }
    else
    {

        WinSetWindowPos(pli->hwndFrame, HWND_TOP, 0, 0, 0, 0, SWP_ZORDER | SWP_SHOW);
    }

