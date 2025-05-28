// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sz.c,v 1.1.1.1 2002/10/01 17:54:43 sdudley Exp $";
#pragma on(unreferenced)

#include "pdata.h"
#include "zmodem.h"
#include "zsjd.h"
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static FILE *in;
static int Rxflags;
static long bytcnt;

int ZmSzInitStatics(void)
{
    txbuf = malloc(1024);

    return !!txbuf;
}


static void near saybibi(void)
{
    for (;;)
    {

        switch (zgethdr(Rxhdr, 0))
        {
        case ZFIN:
            zmdm_pputcw('O');
            zmdm_pputcw('O');
            flushmo();

        case ZCAN:
        case TIMEOUT:
            return;
        }
    }
}


static int near sendzsinit(void)
{
    int c;
    static char Myattn[] = "";

    if (!Zctlesc || (Rxflags & TESCCTL))
        return OK;

    z_errors = 0;

    for (;;)
    {

static int near getzrxinit(void)
{
    int ch, n;

    dlogit(("@In Getzrxinit"));

    for (n = 10; --n >= 0;)
    {
            stohdr(Rxpos);
            zshhdr(ZACK, Txhdr);
            continue;




            if (blklen < 1024)

static int near getinsync(int flag)
{
    int c;

    dlogit(("@Entering getinsync"));

    for (;;)
    {

            dlogit(("@getinsync seeking to offset %ld", Rxpos));

            if (fseek(in, Rxpos, SEEK_SET))
                return ERROR;

            Eofseen = 0;
            bytcnt = Lrxpos = Txpos = Rxpos;

            if (Lastsync == Rxpos)
            {
                if (++Beenhereb4 > 4)
                    if (blklen > 32)
                        blklen /= 2;
            }

            Lastsync = Rxpos;
            return c;

        case ZACK:
            Lrxpos = Rxpos;

            if (flag || Txpos == Rxpos)
                return ZACK;
            continue;

        case ZRINIT:
        case ZSKIP:
            fclose(in);
            return c;

        case ERROR:
        default:
            zsbhdr(ZNAK, Txhdr);
            continue;
        }
    }
}


    Lrxpos = 0;
    junkcount = 0;
    Beenhereb4 = FALSE;


    while (rdchk() && carrier() && !ZmQueryLocalAbort())
    {
        switch (readline(1))
        {
        case CAN:
        case ZPAD:
            c = getinsync(1);
            dlogit(("@readchk gotack"));
            goto gotack;


    newcnt = Rxbuflen;
    Txwcnt = 0;
    stohdr(Txpos);
    zsbhdr(ZDATA, Txhdr);

    do
    {
        n = zfilbuf();

        if (Eofseen)
            e = ZCRCE;
        else if (junkcount > 3)
            e = ZCRCW;
        else if (bytcnt == Lastsync)
            e = ZCRCW;
        else if (Rxbuflen && (newcnt -= n) <= 0)
            e = ZCRCW;
        else if (Txwindow && (Txwcnt += n) >= Txwspac)
        {
            Txwcnt = 0;
            e = ZCRCQ;
        }
        else
            e = ZCRCG;


        if (Txpos + n >= zfilesize - 1)
            zslugbait = TRUE;

                dlogit(("@test2 done flushmo"));

            case XOFF | 0x80:
                readline(100);

            default:
                ++junkcount;
            }
        }

        if (Txwindow)
        {
            while ((tcount = Txpos - Lrxpos) >= Txwindow)
            {
                dlogit(("@%ld window >= %u", tcount, Txwindow));

                if (e != ZCRCQ)
                    zsdata(txbuf, 0, e = ZCRCQ);

                c = getinsync(1);

                if (c != ZACK)
                {
                    mdm_fflush();
                    zsdata(txbuf, 0, ZCRCE);
                    goto gotack;
                }
            }

            dlogit(("@window = %ld", tcount));
        }
    } while (!Eofseen);

    for (;;)
    {

static int near zsendfile(char *buf, int blen)
{
    int c;
    unsigned long crc;

    dlogit(("@Entering ZSendFile"));

    for (;;)
    {

        if (ZmDoLocalAbort())
            return ERROR;

        dlogit(("@ZSendFile calling zgethdr"));
        c = zgethdr(Rxhdr, 1);
        dlogit(("@ZSendFile got zgethdr=%d", c));

        switch (c)
        {
        case ZRINIT:
            while ((c = readline(50)) > 0)
                if (c == ZPAD)
                {
                    goto again;
                }
            fseek(in, 0L, SEEK_SET);

            stohdr(crc);
            zsbhdr(ZCRC, Txhdr);
            goto again;

        case ZSKIP:
            dlogit(("@ZSendFile got zskip"));
            fclose(in);
            return c;

        case ZRPOS:
            dlogit(("@ZSendFile got ZRPOS"));


            if (Rxpos && fseek(in, Rxpos, SEEK_SET))
                return ERROR;


static int near wctxpn(char *name, unsigned long ulFiles, unsigned long ulBytes)
{
    char *p, *q;
    struct stat f;

    q = NULL;

    strcpy(txbuf, No_Path(name));
    q = txbuf + strlen(txbuf) + 1;

    p = q;

    while (q < (txbuf + 1024))
        *q++ = 0;

    if (*name && fstat(fileno(in), &f) != -1)
        sprintf(p, "%lu %lo %o 0 %lu %lu", f.st_size, f.st_mtime, f.st_mode, ulFiles, ulBytes);

        txbuf[127] = (f.st_size + 127) >> 7;
        txbuf[126] = (f.st_size + 127) >> 15;
    }


    return zsendfile(txbuf, 1 + strlen(p) + (p - txbuf));
}


static int near wcs(char *oname, unsigned long ulFiles, unsigned long ulBytes)
{
    int c;
    struct stat f;
    char name[PATHLEN];

    strcpy(name, oname);

    if ((in = shfopen(oname, fopen_readb, O_RDONLY | O_BINARY)) == NULL)
    {
        ++errcnt;

    fstat(fileno(in), &f);

    c = f.st_mode & S_IFMT;

    if (c == S_IFDIR)
    {
        fclose(in);
        return ERROR;
    }

    switch (wctxpn(name, ulFiles, ulBytes))
    {
    case ERROR:
        return ERROR;

    case ZSKIP:
        return ZSKIP;
    }

    return OK;
}


static int ZmInitSession(void)
{
    long lSendTimer;

    zmputs("rz\r");

    Rxtimeout = 600;
    Rxbuflen = 16384;
    Tframlen = 0;
    Rxflags = 0;
    errcnt = 0;
    blklen = 128;
    Wantfcs32 = TRUE;
    Zctlesc = FALSE;
    last = 0;
    z_errors = 0;


        lSendTimer = timerset(800);
        stohdr(0L);
        zshhdr(ZRQINIT, Txhdr);

        do
        {
                break;
            }

            last = ch;
        } while (!timeup(lSendTimer));
    } while (--iSendTries);

    return TIMEOUT;
}


int ZmodemSendFile(char *szName, int fInit, unsigned long ulFiles, unsigned long ulBytes)
{
    int rc;

    fSending = TRUE;


    zslugbait = FALSE;

    if (!szName)
    {
        if (fInit)
        {
            ZmStatInit();
            ZmVarsInit();
            mode(1);
            return ZmInitSession();
        }
        else
        {
            saybibi();
            mode(0);
            return OK;
        }
    }

    bytcnt = -1;

    rc = wcs(szName, ulFiles, ulBytes);

