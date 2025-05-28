// SPDX-License-Identifier: GPL-2.0-or-later


#define INCL_PM
#define INCL_GPI
#define INCL_DOS

#include "sm.h"
#include "ezfont.h"
#include "max.h"
#include "mcp.h"
#include "msg.h"
#include "pmdebug.h"
#include "pos2.h"
#include "prmapi.h"
#include "smrc.h"
#include <process.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



static HWND near InitListbox(HWND hwnd, LINEINFO *li)
{
    HWND hwndList;
    int i;

    hwndList = WinCreateWindow(hwnd, WC_LISTBOX, "", LS_NOADJUSTPOS | LS_OWNERDRAW, 0, 0, 0, 0,
                               hwnd, HWND_TOP, ID_LISTBOX, NULL, NULL);


        WinSendMsg(hwndList, LM_INSERTITEM, MPFROMSHORT(i), MPFROMP("-foo-"));


static void near UpdateListbox(HWND hwndList, int iNode)
{

static int near DrawItem(MPARAM mp2, FONTMETRICS *pfm, LINEINFO *liInfo)
{
    char text[120];
    POWNERITEM poi;
    POINTL ptl;


    ptl.x = poi->rclItem.xLeft;
    ptl.y = poi->rclItem.yBottom + pfm->lMaxDescender;

    WinFillRect(poi->hps, &poi->rclItem, poi->fsState ? CLR_BLACK : SYSCLR_ENTRYFIELD);
    // GpiQueryBackColor(poi->hps));


    if (fPipeBusy || liInfo[poi->idItem].fOnline == 0)
    {
        strcpy(text, "(off-line)");
        GpiCharStringAt(poi->hps, &ptl, strlen(text), text);
    }
    else
    {
        time_t *ptt;
        struct tm *ptm;

        strcpy(text, liInfo[poi->idItem].pcs->username);
        GpiCharStringAt(poi->hps, &ptl, strlen(text), text);
        ptl.x += pfm->lAveCharWidth * LB_COL2;

        strcpy(text, liInfo[poi->idItem].pcs->status);
        GpiCharStringAt(poi->hps, &ptl, strlen(text), text);
        ptl.x += pfm->lAveCharWidth * LB_COL3;

        ptt = (time_t *)&liInfo[poi->idItem].lPingTime;

        if (!*ptt)
            strcpy(text, "(none)");
        else
        {
            ptm = localtime(ptt);

            sprintf(text, "%02d:%02d:%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
        }

        GpiCharStringAt(poi->hps, &ptl, strlen(text), text);
    }

    poi->fsStateOld = poi->fsState = 0;

    return TRUE;
}


    hps = WinGetPS(hwnd);
    GpiQueryFontMetrics(hps, sizeof(FONTMETRICS), pfm);
    WinReleasePS(hps);

    return InitListbox(hwnd, liInfo);
}


    ptl.x = pfm->lAveCharWidth + WinQuerySysValue(HWND_DESKTOP, SV_CXDLGFRAME);
    ptl.y = cyClient - pfm->lMaxAscender;
    GpiMove(hps, &ptl);


static void near SetStatusText(LINEINFO *pli, char *txt)
{

    if (pli->pcs)
        strcpy(pli->pcs->status, txt);
}


static void near MainButton2(HWND hwnd, HWND hwndList, HWND hwndMenu, LINEINFO *liInfo, MPARAM mp1,
                             FONTMETRICS *pfm)
{
    USHORT usTop = SHORT1FROMMR(WinSendMsg(hwndList, LM_QUERYTOPINDEX, 0, 0));
    USHORT usId;
    SWP swp;

    WinQueryWindowPos(hwndList, &swp);

    usId = usTop + (long)(swp.y + swp.cy - (long)SHORT2FROMMP(mp1)) /
                       (long)(pfm->lMaxAscender + pfm->lMaxDescender);
    WinSendMsg(hwndList, LM_SELECTITEM, MPFROMSHORT(usId), MPFROMSHORT(1));


    WinSendMsg(hwndMenu, MM_SETITEMATTR, MPFROM2SHORT(IDM_START, TRUE),
               MPFROM2SHORT(MIA_DISABLED, liInfo[usId].fOnline == 1 ? MIA_DISABLED : 0));


    WinSendMsg(hwndMenu, MM_SETITEMATTR, MPFROM2SHORT(IDM_VIEW, TRUE),
               MPFROM2SHORT(MIA_DISABLED, liInfo[usId].fOnline == 1 ? 0 : MIA_DISABLED));


    WinSendMsg(hwndMenu, MM_SETITEMATTR, MPFROM2SHORT(IDM_MESSAGE, TRUE),
               MPFROM2SHORT(MIA_DISABLED, liInfo[usId].fOnline == 1 ? 0 : MIA_DISABLED));


void MainMenuStart(HWND hwnd, HWND hwndList, LINEINFO *pli, USHORT usId)
{
    NW(hwnd);


    UpdateListbox(hwndList, usId);
}


    if (pli[usId].fOnline != 1)
    {
        WinAlarm(HWND_DESKTOP, WA_ERROR);
        return;
    }

    sprintf(szPrompt, "Warning!  Task %d will be stopped!", pli[usId].tid);

    if (WinMessageBox(HWND_DESKTOP, hwnd, szPrompt, "Kill Task", 0,
                      MB_OKCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_APPLMODAL |
                          MB_MOVEABLE) == MBID_OK)
    {
        McpSendMsg(hp, CLMSG_HAPPY_DAGGER, &pli[usId].tid, 1);
        SetStatusText(pli + usId, szTermTxt);
        UpdateListbox(hwndList, usId);
    }
}

void MainMenuLog(HWND hwnd, HWND hwndList, LINEINFO *pli, USHORT usId)
{
    NW(hwnd);
    NW(hwndList);
    NW(pli);
    NW(usId);
}


void MainMenuGStop(HWND hwnd, HWND hwndList, LINEINFO *pli, USHORT usId)
{
    int i;

    NW(hwnd);
    NW(hwndList);
    NW(usId);

    if (WinMessageBox(HWND_DESKTOP, hwnd, "Warning!  All tasks will be stopped!", "Kill All Tasks",
                      0,
                      MB_OKCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_APPLMODAL |
                          MB_MOVEABLE) == MBID_OK)
    {
        for (i = 0; i < iMaxLines; i++)
            if (pli[i].fOnline != 0)
            {
                McpSendMsg(hp, CLMSG_HAPPY_DAGGER, &pli[i].tid, 1);
                SetStatusText(pli + i, szTermTxt);
                UpdateListbox(hwndList, i);
                DosSleep(1);
            }
    }
}


    usId = SHORT1FROMMP(WinSendMsg(hwndList, LM_QUERYSELECTION, MPFROMSHORT(LIT_FIRST), 0));


    for (i = 0; i < sizeof(cmdtable) / sizeof(*cmdtable); i++)
        if (usCmd == cmdtable[i].usCmd)
        {
            (*cmdtable[i].pfn)(hwnd, hwndList, liInfo, usId);
            break;
        }
}


        memset(liInfo, 0, iMaxLines * sizeof(LINEINFO));
        hwndList = MainCreate(hwnd, &fm, liInfo);
        hwndMenu = WinLoadMenu(HWND_OBJECT, 0, ID_POPUP);
        liInfo->hwndMain = hwnd;
        break;

    case WM_SIZE:

        if (hwndList)
            WinSetWindowPos(hwndList, (HWND)0, 0, 0, cxClient,
                            cyClient - fm.lMaxAscender - fm.lMaxDescender, SWP_SIZE | SWP_MOVE);

        WinShowWindow(hwndList, TRUE);
        break;


        WinQueryWindowPos(hwndFrame, &swp);

        if ((fp = fopen("sm.ini", "w")) != NULL)
        {
            fprintf(fp, "%ld %ld %ld %ld\n", swp.x, swp.y, swp.cx, swp.cy);
            fclose(fp);
        }

        WinDestroyWindow(hwndList);
        free(liInfo);
        break;
    }

    case WM_COMMAND:
        if (SHORT1FROMMP(mp2) == CMDSRC_MENU)
            MainMenu(hwnd, SHORT1FROMMP(mp1), liInfo, hwndList);
        break;

    case WM_BUTTON2DOWN:

    case WM_MEASUREITEM:
        return MRFROMSHORT(fm.lMaxAscender + fm.lMaxDescender);

    case SM_PIPEWAIT:
        fPipeBusy = LONGFROMMP(mp1);
        break;


        if (i == 0 || i > iMaxLines)
            break;


        if (liInfo[i].pcs)
            free(liInfo[i].pcs);

        liInfo[i].pcs = PVOIDFROMMP(mp2);


        if (fOnlineOld && !liInfo[i].fOnline)
            if (liInfo[i].hwndClient)
                WinDestroyWindow(liInfo[i].hwndFrame);


    case SM_PING:
        i = (int)(byte)SHORT1FROMMP(mp1);

        if (i == 0 || i > iMaxLines)
            break;

        i--;

        liInfo[i].lPingTime = LONGFROMMP(mp2);
        UpdateListbox(hwndList, i);
        break;


        i = (int)(byte)SHORT1FROMMP(mp1);

        if (i == 0 || i > iMaxLines)
            break;

        i--;


static void near AddTitle(HWND hwndFrame)
{
    SWCNTRL swctl;

    WinSetWindowText(hwndFrame, szTitle);

    memset(&swctl, '\0', sizeof swctl);


    WinQueryWindowProcess(hwndFrame, &swctl.idProcess, NULL);
    WinAddSwitchEntry(&swctl);
    WinShowWindow(hwndFrame, TRUE);
}


    static ULONG flFrameFlags = FCF_TITLEBAR | FCF_SYSMENU | FCF_SIZEBORDER | FCF_MINMAX |

    if ((fp = fopen("sm.ini", "r")) != NULL)
    {
        char temp[64];

        if (fgets(temp, sizeof temp, fp))
        {
            if (sscanf(temp, "%ld %ld %ld %ld", &swp.x, &swp.y, &swp.cx, &swp.cy) == 4)
            {
                fSetPosn = TRUE;
            }
        }

        fclose(fp);
    }


    WinRegisterClass(hab, szViewClass, (PFNWP)ViewProc, (ULONG)CS_SIZEREDRAW, sizeof(LINEINFO *));


    if (!fSetPosn)
        WinQueryWindowPos(hwndFrame, &swp);

    swp.hwnd = hwndFrame;
    swp.hwndInsertBehind = HWND_TOP;

    if (!fSetPosn)
    {

        swp.cx = LB_SUM * fm.lAveCharWidth + WinQuerySysValue(HWND_DESKTOP, SV_CXVSCROLL) +
                 WinQuerySysValue(HWND_DESKTOP, SV_CXBORDER) * 2 + 4;

        swp.cy = (iMaxLines + 1) * (fm.lMaxAscender + fm.lMaxDescender) +
                 WinQuerySysValue(HWND_DESKTOP, SV_CYTITLEBAR) +
                 WinQuerySysValue(HWND_DESKTOP, SV_CYBORDER) * 2 +
                 WinQuerySysValue(HWND_DESKTOP, SV_CYMENU) + 16;
    }

#ifdef __FLAT__
    swp.fl = SWP_SIZE | SWP_SHOW | SWP_MOVE | SWP_ZORDER;
#else
    swp.fs = SWP_SIZE | SWP_SHOW | SWP_MOVE | SWP_ZORDER;
#endif

    WinSetMultWindowPos(hab, &swp, 1);
}

char *GetMax(int argc, char **argv)
{
    char *pszMaximus = NULL;

    (void)argc;


            if (**argv == '-' && (*argv)[1] == 'p')
            {
                pszMaximus = *argv + 2;
                break;
            }

            argv++;
        }
    }


int main(int argc, char *argv[])
{
    char *pszMax;

    hab = WinInitialize(0);
    hmq = WinCreateMsgQueue(hab, 0);

    if ((pszMax = GetMax(argc, argv)) != NULL)
    {
        if (ReadPrm(pszMax))
        {
            CreateStdWindow();


            StartMonitor(argc >= 2 ? argv[1] : "\\pipe\\maximus\\mcp");


            while (WinGetMsg(hab, &qmsg, (HWND)0, 0, 0))
                WinDispatchMsg(hab, &qmsg);

            DbgEnd();
            WinDestroyWindow(hwndFrame);
        }
    }

    WinDestroyMsgQueue(hmq);
    WinTerminate(hab);

    return 0;
}
