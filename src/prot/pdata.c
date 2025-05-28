// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: pdata.c,v 1.1.1.1 2002/10/01 17:54:39 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS

#ifdef OS_2
#include <os2.h>
#endif

#define MAX_LANG_protocols
#define MAX_LANG_f_area
#include "mm.h"
#include "pdata.h"
#include "pdatap.h"
#include "prog.h"
#include "xmodem.h"
#include "zsjd.h"
#include <conio.h>
#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void ThruStart(void)
{
    lTimeStart = time(NULL);
    lStartOffset = 0L;
}


void ThruSetStartOffset(long lStartOfs) { lStartOffset = lStartOfs; }

void ThruLog(long lTotalBytes)
{
    long lTimeElapsed;
    long lBytesSent;
    long lCPS;

        p = fname;
        while (*p && *p != '.')
            if (!*p)
            {
                *p = suffix[n];
                *(++p) = '\0';
            }
            else
                p++;

        {
            p = fname + strlen(fname) - 1;
            for (n = 3; n--;)
            {
                if (!isdigit(*p))
                    *p = '0';
                if (++(*p) <= '9')
                    break;
                else
                    *p-- = '0';


unsigned XferWinOpen(sword protocol, unsigned doing_dl)
{
    char temp[PATHLEN], temp2[PATHLEN];

    if (displaymode != VIDEO_IBM)
        gwXfer = NULL;
    else
    {
        gwXfer = WinOpen(-1, -1, 9, 67, BORDER_SINGLE, CWHITE | _BLUE, CYELLOW | _BLUE,
                         WIN_CENTRE | WIN_NOCSYNC | WFLAG_NOCUR);

        WinCls(gwXfer, CWHITE | _BLUE);
    }


void XferWinNewFile(char *filename, long size)
{

    WinGotoXY(gwXfer, 3, 19, FALSE);

    if (size == -1L)
        WinPuts(gwXfer, unknown);
    else
        WinPrintf(gwXfer, "%-8ld", size);
}


static void near XferWinShowRates(long size, long sent, long elapsed, word protocol)
{
    long xtime;


    if (size != -1L)
    {
        WinGotoXY(gwXfer, 3, 51, FALSE);

        xtime = (size - sent < 0) ? 0 : XferTime(protocol, size - sent);
        WinPrintf(gwXfer, "%10lu:%02u", xtime / 60L, (unsigned)(xtime % 60L));


static void near XferWinSpace(int row, int col, int n_spaces)
{
    WinGotoXY(gwXfer, 0, 1, FALSE);

    while (n_spaces--)
        WinPutch(gwXfer, row, col++, ' ', CWHITE | _BLUE);
}


static int XferWinDoSync(void)
{
    static long lSyncTime = -1L;
    long lNow;


void XmStatus(unsigned flag, unsigned do_crc, long sent, time_t start, sword protocol, long size,
              long last_ack, unsigned n_err, long block)
{
    if (gwXfer)
    {
        int fDoSync = XferWinDoSync();

        if (fDoSync)
        {
            WinPutstr(gwXfer, 2, 19, do_crc ? win_crc16 : win_checksum);


        if (flag != XS_SENT && flag != XS_RECV)
        {
            WinCleol(gwXfer, 6, 19, CWHITE | _BLUE);


void ZmStatInit(void)
{
    tZmodemStart = time(NULL);
    ulZmSize = 0L;
    XferWinClear();
    Lputc('\n');
    WinSync(gwXfer, FALSE);
}


    if (iHdr == ZDATA)
        return;

    WinCleol(gwXfer, 6, 19, CWHITE | _BLUE);
    WinGotoXY(gwXfer, 6, 19, FALSE);

    WinSync(gwXfer, FALSE);
}

void ZmStatFile(char *szPath, unsigned long ulSize, unsigned fCrc32)
{
    tZmodemStart = time(NULL);
    ThruStart();


    WinGotoXY(gwXfer, 2, 51, FALSE);

    XferWinShowRates(ulZmSize, ulPos, time(NULL) - tZmodemStart, PROTOCOL_ZMODEM);

    if (XferWinDoSync())
        WinSync(gwXfer, FALSE);
}


void ZmStatus(unsigned crc32, unsigned block_size, long size, long sent, time_t start, char *status)
{
  char temp[PATHLEN];
  time_t now;
  long xtime;

  if (gwXfer)
  {
    sprintf(temp, crc32 ? win_crc32_size : win_crc16_size, block_size);
    WinPutstr(gwXfer, 2, 19, temp);

    WinGotoXY(gwXfer, 3, 19, FALSE);
    WinPrintf(gwXfer, pl, size);

    WinGotoXY(gwXfer, 4, 19, FALSE);
    WinPrintf(gwXfer, "%-10ld", sent);

    WinGotoXY(gwXfer, 2, 51, FALSE);

    now=time(NULL);

    if (now != start)
      WinPrintf(gwXfer, win_cps, sent / (long)(now-start));

    WinGotoXY(gwXfer, 3, 51, FALSE);
    xtime=XferTime(PROTOCOL_ZMODEM, size-sent);
    WinPrintf(gwXfer, win_time, xtime / 60L, (unsigned)(xtime % 60L));

    WinGotoXY(gwXfer, 4, 51, FALSE);
    xtime=time(NULL)-start;
    WinPrintf(gwXfer, win_time, xtime / 60L, (unsigned)(xtime % 60L));


int mdm_getct(unsigned timeout)
{
    long t1 = timerset(timeout);
    int ch;

    while (!timeup(t1))
    {
        if ((ch = mdm_getc()) != -1)
            return ch;
        else if (!carrier())
            break;
        else
            Giveaway_Slice();
    }

    return -1;
}


    mdm_dump(DUMP_OUTPUT);


    for (i = 0; i < 16; i++)
    {
        mdm_pputcw('\x08');
        mdm_pputcw(' ');
        mdm_pputcw('\x08');
    }
}
