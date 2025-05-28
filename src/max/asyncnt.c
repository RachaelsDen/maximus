// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: asyncnt.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)

#if defined(NT) || defined(UNIX)

#include "mm.h"
#include "modem.h"
#include "ntcomm.h"
#include "prog.h"
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void cdecl logit(char *fmt, ...);


int GetConnectionType(void) { return CTYPE_ASYNC; }

void com_DTR_on(void)
{
    DCB dcb;

    GetCommState(ComGetHandle(hcModem), &dcb);
    dcb.fDtrControl = 1;
    SetCommState(ComGetHandle(hcModem), &dcb);
}

void com_DTR_off(void)
{
    DCB dcb;

    GetCommState(ComGetHandle(hcModem), &dcb);
    dcb.fDtrControl = 0;
    SetCommState(ComGetHandle(hcModem), &dcb);
}

void com_HHS_enable(int mask)
{
    DCB dcb;

    GetCommState(ComGetHandle(hcModem), &dcb);

    if (mask & FLOW_CTS)
    {
        dcb.fOutxCtsFlow = TRUE;
            rc = !ComOpen(tmp, &hcModem, 8200, 8200);
        }
        else
        {
            sprintf(tmp, "handle %d", port + 1);

            hf = (HFILE)port +
