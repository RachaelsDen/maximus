// SPDX-License-Identifier: GPL-2.0-or-later


#include "wincomm.h"
#include "prog.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _REENTRANT
#error not yet: needs more work (statics)
#endif

static struct _DCB static_DCB;
static int static_hFile = -1;
static struct _COMMTIMEOUTS static_CT;

BOOL SetCommState(int hFile, LPDCB lpDCB)
{
    lpDCB->DCBlength = sizeof(*lpDCB);
    lpDCB->fNull = FALSE;
    lpDCB->fAbortOnError = FALSE;

    if ((static_hFile == hFile) || (static_hFile == -1))
    {
        static_hFile = hFile;
        static_DCB = *lpDCB;
        return TRUE;
    }

    return FALSE;
}

BOOL GetCommState(int hFile, LPDCB lpDCB)
{
    if (static_hFile == hFile)
    {
        *lpDCB = static_DCB;
        return TRUE;
    }

    return FALSE;
}

BOOL SetCommMask(int hFile, DWORD dwEvtMask) { return TRUE; }

BOOL SetCommTimeouts(OSCOMMHANDLE hFile, LPCOMMTIMEOUTS lpCommTimeouts)
{
    if ((static_hFile == hFile) || (static_hFile == -1))
    {
        static_hFile = hFile;
        static_CT = *lpCommTimeouts;
        return TRUE;
    }

    return FALSE;
}

