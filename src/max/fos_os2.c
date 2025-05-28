// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: fos_os2.c,v 1.3 2003/06/06 01:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#include <conio.h>
#include <dos.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(UNIX)
#include "mm.h"
#include "modem.h"
#include "prog.h"
#endif

#if defined(OS_2) || defined(NT)
#ifdef OS_2
#define INCL_DOS
#define INCL_VIO
#define INCL_NOPM
#include "pos2.h"
#endif

#include "mm.h"
#include "modem.h"
#include "prog.h"
#endif

#if defined(OS_2) || defined(NT) || defined(UNIX)
static int fossil_installed = FALSE;

int mdm_ggetcw(void)
{
    ComRxWait(hcModem, -1L);
    return ComGetc(hcModem);
}

  void fossil_gotoxy(char row,char col)
  {
      VioSetCurPos((word)row, (word)col, 0);
  }
#endif


int mdm_avail() { return !local && ComInCount(hcModem); }

int mdm_baud(int bod)
{
    static struct
    {
        int bodmask;
        long baudrate;
    } * pb, bodcvt[] = {{BAUD300, 300L},
                        {BAUD600, 600L},
                        {BAUD1200, 1200L},
                        {BAUD2400, 2400L},
                        {BAUD4800, 4800L},
                        {BAUD9600, 9600L},
                        {BAUD19200, 19200L},
                        {BAUD38400, 38400L},
                        {BAUD57600, 57600L},
                        {BAUD115200, 115200L},
                        {0, 0}};

    USHORT rc;
    long b;

    if (steady_baud)
        bod = steady_baud;

#if (COMMAPI_VER > 1)
    if (ComIsAModem(hcModem))
    {
#endif
        for (pb = bodcvt; pb->baudrate; pb++)
        {
            if (pb->bodmask == bod)
            {
                b = pb->baudrate;
                break;
            }
        }


    if (b == 115200L)
        rc = 0;
    else
        rc = ComSetBaudRate(hcModem, b, 'N', 8, 1);
#endif

    if (rc)
        logit("!SYS%04u:  ComSetBaudRate(%ld)", rc, b);

    return (0);
}

int mdm_blockwrite(int max_chars, char *offset)
{
    max_chars = min(ComOutSpace(hcModem), max_chars);

    if (!max_chars)
        return 0;

#if defined(NT) || defined(UNIX)
    return (ComWrite(hcModem, offset, max_chars) ? max_chars : 0);
#else
    return (ComWrite(hcModem, offset, max_chars) ? 0 : max_chars);
#endif
}


void mdm_break(unsigned int hsecs)
{
    com_break(TRUE);

#ifdef NT
    Sleep(hsecs * 10L);
#else
    DosSleep(hsecs * 10L);
#endif

    com_break(FALSE);
}

int mdm_ctrlc(char mask)
{
    int c;

    extern char local;


    if (loc_peek() == 3)
    {

    if (local)
        return brk_trapped;

    if (!mask)
        return 0;

    c = ComPeek(hcModem);

    return (c == 3 || c == 11);
}

{
    port = prt;

    if (local)
        return INIT_OK;

    if (Cominit(prt) != 0x1954)
        return INIT_NOFOSSIL;

    if (waitforcaller)

    return INIT_OK;
}


