// SPDX-License-Identifier: GPL-2.0-or-later


#define INCL_PM
#define INCL_GPI
#define INCL_DOS
#define INCL_VIO
#define INCL_AVIO

#include "max.h"
#include "mcp.h"
#include "pmdebug.h"
#include "pos2.h"
#include "sm.h"
#include "smrc.h"
#include <process.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern HWND hwndClient;
extern HPIPE hp;

#define DbgPrintf !!Error !!


int CALLBACK RcIoMonitorDump(SMDISPATCH *psd)
{
    USHORT usHeight, usWidth, usSize;
    char *newdump;

    DbgPrintfp("Got RcIoMonitorDump");


    DbgPrintfp("Got ping for %d", *psd->pb);

    WinPostMsg(hwndClient, SM_PING, MPFROMSHORT(*psd->pb), MPFROMLONG(time(NULL)));

    return 0;
}

int CALLBACK RcOverview(SMDISPATCH *psd)
{
    struct _cstat *pcs, *newpcs;

    DbgPrintfp("Got RcOverview");

    pcs = (struct _cstat *)(psd->pb + 1);

    if ((newpcs = malloc(sizeof *newpcs)) != NULL)
    {
        memmove(newpcs, pcs, sizeof *pcs);

        DbgPrintfp("Setting status for node %d", *psd->pb);

        WinPostMsg(hwndClient, SM_SETSTATUS, MPFROMSHORT(*psd->pb), MPFROMP(newpcs));
    }

    return 0;
}

    USHORT rc;

    DbgPrintfp("Connecting to pipe '%s'", szPipe);


        if (rc)
        {
            WinPostMsg(hwndClient, SM_PIPEWAIT, MPFROMLONG(1L), 0L);
            DosSleep(30000L);
        }
    } while (rc);


    sd.pb = pcBuf + sizeof(USHORT);


TID StartMonitor(char *szPipeRoot)
{
    char *szPipe;
    char *pcStack;

