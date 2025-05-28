// SPDX-License-Identifier: GPL-2.0-or-later


#define DEBUG

#include <fcntl.h>
#include <io.h>

#ifdef PM

#include "tui.h"
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#include "pmdebug.h"
#endif

HAB hab;
HWND hwndFrame, hwndClient;
HMQ hmq;
static char szClientClass[] = "ClientClass";
static MRESULT EXPENTRY ClientProc(HWND hwnd, MSGDEF msg, MPARAM mp1, MPARAM mp2);
static MRESULT EXPENTRY DlgProc(HWND hwnd, MSGDEF msg, MPARAM mp1, MPARAM mp2);


void TuiPmInit(void)
{
    SWP swp;
    LONG cx, cy;
    static ULONG flFrameFlags =
        FCF_SIZEBORDER | FCF_TITLEBAR | FCF_SYSMENU | FCF_MINMAX | FCF_TASKLIST;

    hab = WinInitialize(0);
    hmq = WinCreateMsgQueue(hab, 0);

    WinRegisterClass(hab, szClientClass, (PFNWP)ClientProc, (ULONG)CS_SIZEREDRAW, 0);

    hwndFrame =
        WinCreateStdWindow(HWND_DESKTOP, (ULONG)0, (PULONG)&flFrameFlags, (PSZ)szClientClass,
                           (PSZ)NULL, (ULONG)0L, (HMODULE)0, (USHORT)ID_RESOURCE, &hwndClient);

#ifdef DEBUG
    DbgBegin(HWND_DESKTOP, hab, 200);
#endif


void TuiPmTerm(void)
{
#ifdef DEBUG
    DbgEnd();
#endif

    if (hwndFrame)
    {
        WinDestroyWindow(hwndFrame);
        hwndFrame = 0;
    }

    if (hmq)
    {
        WinDestroyMsgQueue(hmq);
        hmq = 0;
    }

    if (hab)
    {
        WinTerminate(hab);
        hab = 0;
    }
}

static char *near _TuiPmConstructMenu(HVMENU vmenu, char *template, USHORT id, USHORT usMul)
{
    MENUTEMPLATE *pmt;
    MTI *pmti;
    BOOL fSubMenu;
    char *p;
    USHORT i;

    pmt = (MENUTEMPLATE *)template;

    pmt->cb = sizeof(MENUTEMPLATE);
    pmt->version = 0;
    pmt->codepage = 437;
    pmt->iInputSize = 0;
    pmt->cMti = 0;

    pmti = (MTI *)(pmt + 1);
    p = (char *)pmti;

    for (i = 0; i < vmenu->num_opt; i++)
    {
        fSubMenu = (vmenu->opt[i].menu && (vmenu->opt[i].menu->type & MENU_DIALOG) == 0);

        pmti->afStyle = MIS_TEXT | (fSubMenu ? MIS_SUBMENU : 0);

static int near TuiPmCreateDlg(HVMENU hd)
{
    HWND hwndDlg;
    char *template, *txt;
    DLGTEMPLATE *pdt;
    DLGTITEM *pdi;
    USHORT cxDlg, cyDlg;
    USHORT cDlgt;
    SHORT i;

    template = malloc(20000);
    pdt = (DLGTEMPLATE *)template;



    for (i = 0, cDlgt = 0; i < (SHORT)hd->num_opt; i++, cDlgt++)
        if (hd->opt[i].regist == DlgStrReg)
            cDlgt++;

    pdi = (DLGTITEM *)((char *)pdt + DLT_SIZE);

    txt = (char *)pdi + (cDlgt + 1) * sizeof(DLGTITEM);

    pdi->fsItemStatus = 0;
    pdi->cChildren = cDlgt;
    pdi->cchClassName = 0;
    pdi->offClassName = 1;
    pdi->cchText = 0;
    pdi->offText = (char *)txt - (char *)pdt;
    *txt++ = '\0';

    pdi++;

    for (i = 0; i < (SHORT)hd->num_opt; i++, pdi++)
    {
        char *oname;

        pdi->fsItemStatus = 0;
        pdi->cChildren = 0;

        pdi->cchClassName = 0;

        if ((oname = strchr(hd->opt[i].name, ';')) != NULL)
            oname++;
        else
            oname = hd->opt[i].name;

        pdi->cchText = oname ? strlen(oname) : 0;
        pdi->offText = (char *)txt - (char *)pdt;


        pdi->id = i + 3;
        pdi->offPresParams = -1;
        pdi->offCtlData = -1;

        if (hd->opt[i].regist == DlgStrReg)
        {


            pdi[1] = *pdi;
            pdi++;


            pdi->cx = atoi(hd->opt[i].name) * 9 / 2;


            pdi->cchText = 0;
            pdi->offText = (char *)txt - (char *)pdt;
            *txt++ = '\0';

        {
            pdi->offClassName = 5;
            pdi->flStyle = WS_VISIBLE | SS_TEXT;
        }

    }

    pdt->cbTemplate = (char *)txt - (char *)pdt;

    hwndDlg = WinCreateDlg(HWND_DESKTOP, hwndClient, DlgProc, pdt, NULL);
    WinProcessDlg(hwndDlg);
    WinDestroyWindow(hwndDlg);

    free(template);

    return 0;
}

static int near TuiPmClientSelect(USHORT id)
{
    USHORT ix1, ix2, ix3;
    HVMENU hd;



    if (ghvm->opt[ix1].menu->type & MENU_DIALOG)
        hd = ghvm->opt[ix1].menu;
    else if (ghvm->opt[ix1].menu->opt[ix2].menu->type & MENU_DIALOG)
        hd = ghvm->opt[ix1].menu->opt[ix2].menu;
    else
        hd = ghvm->opt[ix1].menu->opt[ix2].menu->opt[ix3].menu;

    return TuiPmCreateDlg(hd);
}

static MRESULT EXPENTRY ClientProc(HWND hwnd, MSGDEF msg, MPARAM mp1, MPARAM mp2)
{
