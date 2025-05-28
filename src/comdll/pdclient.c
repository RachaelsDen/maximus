// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: pdclient.c,v 1.1.1.1 2002/10/01 17:49:35 sdudley Exp $";
#pragma on(unreferenced)

#include "pdclient.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

static HANDLE hp;
static HANDLE hmx;

BOOL PDInit(char *pipe)
{
    if (!WaitNamedPipe(pipe, NMPWAIT_WAIT_FOREVER))
    {
        printf("WaitNamedPipe returned %d\n", GetLastError());
        return FALSE;
    }

    if ((hmx = CreateMutex(NULL, FALSE, NULL)) == INVALID_HANDLE_VALUE)
    {
        printf("Couldn't create mutex semaphore!\n");
        exit(1);
    }

    if ((hp = CreateFile(pipe, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL)) ==
        INVALID_HANDLE_VALUE)
    {
        printf("CreateFile returned %d\n", GetLastError());
        return FALSE;
    }

    return TRUE;
}

int PDWrite(char *s)
{
    DWORD sent;
    int rc;

    if ((rc = WaitForSingleObject(hmx, INFINITE)) != 0)
        printf("WaitForSingleObject rc=%d, err=%d\n", rc, GetLastError());

