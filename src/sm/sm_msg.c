// SPDX-License-Identifier: GPL-2.0-or-later


#define INCL_PM
#define INCL_DOS

#include "max.h"
#include "mcp.h"
#include "msg.h"
#include "pos2.h"
#include "sm.h"
#include "smrc.h"
#include <stdlib.h>
#include <string.h>

#define MAX_MAXMSG_LEN (PATHLEN - sizeof(struct _cdat) - 2)

extern HPIPE hp;


        WinSendDlgItemMsg(hwnd, IDD_MSG_ENTRY, EM_SETTEXTLIMIT, MPFROMSHORT(MAX_MAXMSG_LEN), 0);
        break;

    case WM_COMMAND:

            switch (SHORT1FROMMP(mp1))
            {
            case IDD_MSG_SEND:

static int near MessageSendOne(byte tid, char *szMsg)
{
    struct _cdat *pcd;
    OS2UINT rc;

    if ((pcd = malloc(sizeof(*pcd) + strlen(szMsg) + 1)) == NULL)
        return FALSE;


    strcpy((char *)(pcd + 1), szMsg);


void MainMenuMessage(HWND hwnd, HWND hwndList, LINEINFO *pli, USHORT usId)
{
    char szMsg[PATHLEN];

    NW(pli);
    NW(usId);


            sprintf(szMsg, "Message sent to node %d", pli[usId].tid);

            WinMessageBox(HWND_DESKTOP, hwnd, szMsg, "", 0, MB_OK | MB_ICONASTERISK);
        }
    }
}

void MainMenuGMessage(HWND hwnd, HWND hwndList, LINEINFO *pli, USHORT usId)
{
    extern int iMaxLines;
    char szMsg[PATHLEN];
    int i;

    NW(usId);


        sprintf(szMsg, "Message sent to all nodes");

        WinMessageBox(HWND_DESKTOP, hwnd, szMsg, "", 0, MB_OK | MB_ICONASTERISK);
    }
}
