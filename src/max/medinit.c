// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: medinit.c,v 1.1.1.1 2002/10/01 17:52:18 sdudley Exp $";
#pragma on(unreferenced)

#ifdef OS_2

#include <stdio.h>
#include <string.h>
#define INCL_NOPM
#define INCL_DOS
#define INCL_VIO
#include "compiler.h"
#include "ffind.h"
#include "modem.h"
#include "snserver.h"
#include "typedefs.h"
#include <os2.h>

extern void near _loadds StackOvl(int err);

#endif
}

#ifndef __FLAT__
int pascal far ZeroDiv(void)
{
    char *msg = "\r\nDivide by zero\r\n";
    char far *null = 0L;
    VioWrtTTY(msg, strlen(msg), 0);
}
#pragma check_stack()
#endif

static void _loadds near textify(void);

void pascal far _loadds CleanUp(USHORT flag)
{
    HFILE hand;
    char *msg;
    char str[200];
#ifdef __FLAT__
    ULONG bytes;
#else
    USHORT bytes;
#endif

    setvbuf(stdout, NULL, _IONBF, 0);
    hand = ComGetFH(hcModem);
    if (hand == -1)
        hand = 0;
    if (!ComIsOnline(hcModem))
        hand = 0;
    switch (flag)
    {
        msg = "due to a hardware error";
        break;
        msg = "because of an exception trap";
        break;
    default:
        msg = "for unknown reasons";
        break;
    }
    sprintf(str, "\n[0m[1mThe BBS has ended %s.\r\n", msg);
    printf(str);
    if (hand)
        DosWrite(hand, str, strlen(str), &bytes);
    if (flag != TC_EXIT)
    {
        sprintf(str, "Please wait while an attempt is made to record this bad news...\r\n[0m");
        printf(str);
        if (hand)
        {
            DosWrite(hand, str, strlen(str), &bytes);
            DosBufReset(hand);
        }
        LogWrite("!!!! Uh oh.\n");
        textify();
    buf[viomi.col] = 0;
    blanklines = 0;
    for (row = 0; row < viomi.row; row++)
    {
        VioReadCharStr(buf, &viomi.col, row, 0, 0);
        for (col = viomi.col - 1; col >= 0; col--)
        }
        else
        {
            buf[col + 1] = 0;
            while (blanklines)
            {
                LogWrite("! CRASH ³\n");
#ifdef MAXSNOOP
                SnWrite("! CRASH ³\n");
#endif
                blanklines--;
            }
            sprintf(str, "! CRASH ³%s\n", buf);
            LogWrite(str);
#ifdef MAXSNOOP
            SnWrite(str);
#endif
        }
    }
}

