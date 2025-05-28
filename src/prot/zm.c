// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: zm.c,v 1.2 2003/06/05 01:16:01 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_protocols
#define INCL_DOSDEVIOCTL
#include "keys.h"
#include "pdata.h"
#include "zmodem.h"
#include "zsjd.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifdef DEBUGZ
#if defined(OS_2)

    return bStatus;
}

#define ZmUpdCrc(cp, crc) (crctab[((crc >> 8) & 255)] ^ (crc << 8) ^ cp)

#define ZRWINDOW 1400



#ifdef DEBUGZ
static int Verbose = 4;
#endif

static char *frametypes[] = {

int ZmInitStatics(void)
{
    int ok = TRUE;


    Attn = malloc(ZATTNLEN + 1);
    linbuf = malloc(HOWMANY);
    szTxBuf = malloc(MAX_TXBUF);


void ZmDeinitStatics(void)
{

int ZmQueryLocalAbort(void)
{

int ZmDoLocalAbort(void)
{
    if (!ZmQueryLocalAbort())
        return FALSE;

    if (carrier())
        canit();

    return TRUE;
}


        if (!carrier() || ZmQueryLocalAbort())
            break;
    }

    szTxPtr = szTxBuf;
    iTxBufLeft = MAX_TXBUF;
}


void flushmo(void)
{

    while (!out_empty() && carrier() && !ZmQueryLocalAbort())
    {
        if (!t)
            t = timerset(10000);

        if (timeup(t))
        {
            t = timerset(10000);
#ifdef DEBUGZ
            dlogit(("!Timeout in flushmo - s=%x", zmdm_status()));
#endif
            Mdm_Flow(FLOW_OFF);
            Mdm_Flow(FLOW_NO_CCK);
        }

        Giveaway_Slice();
    }
}


#if 0
void
zmdm_pputcw(int c)
{

static void near zperr(char *s, ...)
{
    char out[PATHLEN * 2];
    va_list va;

    sprintf(out, log_retry_num, ++z_errors);

    va_start(va, s);
    vsprintf(out + strlen(out), s, va);
    va_end(va);

    logit(out);
}


    ZmStatHdr(TRUE, type, frametypes[type + FTOFFSET], rclhdr(hdr));

    zmdm_pputcw(ZBIN32);
    zsendline(type);

    crc = 0xffffffffL;
    crc = UPDC32(type, crc);

    for (n = 4; --n >= 0; ++hdr)
    {
        crc = UPDC32((0xff & *hdr), crc);
        zsendline(*hdr);
    }

    crc = ~crc;

    for (n = 4; --n >= 0;)
    {
        zsendline((int)crc);
        crc >>= 8;
    }
}


        ZmStatHdr(TRUE, type, frametypes[type + FTOFFSET], rclhdr(hdr));

        zmdm_pputcw(ZBIN);
        zsendline(type);
        crc = ZmUpdCrc(type, 0);

        for (n = 4; --n >= 0; ++hdr)
        {
            zsendline(*hdr);
            crc = ZmUpdCrc((0xff & *hdr), crc);
        }
        crc = ZmUpdCrc(0, ZmUpdCrc(0, crc));
        zsendline(crc >> 8);
        zsendline(crc);
    }

    if (type != ZDATA)
        flushmo();
}


void zshhdr(int type, char *hdr)
{
    int n;
    unsigned short crc;


    zmdm_pputcw(015);
    zmdm_pputcw(0x8a);


    if (type != ZFIN && type != ZACK)
    {
        zmdm_pputcw(0x11);
    }

    flushmo();
}


void zsdata(unsigned char *buf, int length, int frameend)
{
    unsigned short crc;

#ifdef DEBUGZ
    dlogit(("@zsdata: %d %s", length, Zendnames[frameend - ZCRCE & 3]));
#endif

    if (Crc32t)
        zsda32(buf, length, frameend);
    else
    {
        crc = 0;

        for (; --length >= 0; ++buf)
        {
            zsendline(*buf);
            crc = ZmUpdCrc((0xff & *buf), crc);
        }

        zmdm_pputcw(ZDLE);
        zmdm_pputcw(frameend);

        crc = ZmUpdCrc(frameend, crc);
        crc = ZmUpdCrc(0, ZmUpdCrc(0, crc));

        zsendline(crc >> 8);
        zsendline(crc);
    }

    if (frameend == ZCRCW)
    {
        zmdm_pputcw(XON);
        flushmo();
    }
}


static int near zdlread(void)
{
    int c;
#ifdef DEBUGZ
    static long lInvoke = 0L;

    lInvoke++;
#endif

again:


static int near zrdat32(char *buf, int length)
{
    int c;
    long crc;
    char *end;
    int d;

    crc = 0xFFFFFFFFL;
    Rxcount = 0;
    end = buf + length;

    while (buf <= end)
    {
        if ((c = zdlread()) & ~0xff)
        {
        crcfoo:

            switch (c)
            {
            case GOTCRCE:
            case GOTCRCG:
            case GOTCRCQ:
            case GOTCRCW:
                d = c;
                c &= 0xff;

                crc = UPDC32(c, crc);

                if ((c = zdlread()) & ~0xff)
                    goto crcfoo;

                crc = UPDC32(c, crc);

                if ((c = zdlread()) & ~0xff)
                    goto crcfoo;

                crc = UPDC32(c, crc);

                if ((c = zdlread()) & ~0xff)
                    goto crcfoo;

                crc = UPDC32(c, crc);

                if ((c = zdlread()) & ~0xff)
                    goto crcfoo;

                crc = UPDC32(c, crc);

                if (crc != 0xDEBB20E3)
                {
                    zperr(bad_crc_at, Rxbytes);
                    return ERROR;
                }

                Rxcount = length - (end - buf);

#ifdef DEBUGZ
                dlogit(("@zrdat32: %d %s", Rxcount, Zendnames[d - GOTCRCE & 3]));
#endif
                return d;

            case GOTCAN:
                zperr(sender_cancelled);
                return ZCAN;

            case TIMEOUT:
                zperr(transfer_timeout);
                return c;

            default:
                zperr(bad_data_subpkt);
                return c;
            }
        }

        *buf++ = c;
        crc = UPDC32(c, crc);
    }

    zperr(data_subpkt_long);
    return ERROR;
}


int zrdata(char *buf, int length)
{
    int c;
    unsigned short crc;
    char *end;
    int d;

    if (Rxframeind == ZBIN32)
        return zrdat32(buf, length);

    crc = Rxcount = 0;
    end = buf + length;

    while (buf <= end)
    {
        if ((c = zdlread()) & ~0xff)
        {
        crcfoo:

            switch (c)
            {
            case GOTCRCE:
            case GOTCRCG:
            case GOTCRCQ:
            case GOTCRCW:
                crc = ZmUpdCrc((d = c) & 0xff, crc);

                if ((c = zdlread()) & ~0xff)
                    goto crcfoo;

                crc = ZmUpdCrc(c, crc);

                if ((c = zdlread()) & ~0xff)
                    goto crcfoo;

                crc = ZmUpdCrc(c, crc);

                if (crc & 0xFFFF)
                {
                    zperr(bad_crc_at, Rxbytes);
                    return ERROR;
                }

                Rxcount = length - (end - buf);

#ifdef DEBUGZ
                dlogit(("@zrdata: %d  %s", Rxcount, Zendnames[d - GOTCRCE & 3]));
#endif
                return d;

            case GOTCAN:
                zperr(sender_cancelled);
                return ZCAN;

            case TIMEOUT:
                zperr(transfer_timeout);
                return c;

            default:
                zperr(bad_data_subpkt);
                return c;
            }
        }

        *buf++ = c;
        crc = ZmUpdCrc(c, crc);
    }

    zperr(data_subpkt_long);
    return ERROR;
}

#endif

    for (n = 4; --n >= 0; ++hdr)
    {
        if ((c = zdlread()) & ~0xff)
            return c;

        crc = UPDC32(c, crc);
        *hdr = c;

#ifdef DEBUGZ
#endif
    }

    if (crc != 0xDEBB20E3)
    {
        zperr(bad_crc_hdr);
        return ERROR;
    }

    return Rxtype;
}


static int near noxrd7(void)
{
    int c;

    for (;;)
    {
        if ((c = readline(Rxtimeout)) < 0)
            return c;

        switch (c &= 0x7f)
        {
        case XON:
        case XOFF:
            continue;

        default:
            if (Zctlesc && !(c & 0x60))
                continue;

        case '\r':
        case '\n':
        case ZDLE:
            return c;
        }
    }
}


int zgethdr(char *hdr, int eflag)
{
    int c, cancount;
    long n;


    switch (c = readline(Rxtimeout))
    {
    case RCDO:
    case TIMEOUT:
        goto fifi;

    case CAN:
    gotcan:
        if (--cancount <= 0)
        {
            c = ZCAN;
            goto fifi;
        }

        switch (c = readline(1))
        {
        case TIMEOUT:
            goto again;

    default:
    agn2:
        if (--n == 0)
        {
            zperr(garbage_count_exceeded);
            return (ERROR);
        }

        if (eflag && ((c &= 0x7f) & 0x60))

#ifdef UNIX
        fflush(stderr);
#endif

        goto startover;

        break;

        break;
    }

    switch (c = noxrd7())
    {
    case RCDO:
    case TIMEOUT:
        goto fifi;

    case ZBIN:
        Rxframeind = ZBIN;
        Crc32 = FALSE;
        c = zrbhdr(hdr);
        break;

    case ZBIN32:
        Crc32 = Rxframeind = ZBIN32;
        c = zrbhdr32(hdr);
        break;

    case ZHEX:
        Rxframeind = ZHEX;
        Crc32 = FALSE;
        c = zrhhdr(hdr);
        break;

    case CAN:
        goto gotcan;

    default:
        goto agn2;
    }

    Rxpos = hdr[ZP3] & 0xff;
    Rxpos = (Rxpos << 8) + (hdr[ZP2] & 0xff);
    Rxpos = (Rxpos << 8) + (hdr[ZP1] & 0xff);
    Rxpos = (Rxpos << 8) + (hdr[ZP0] & 0xff);

fifi:


    case ZNAK:
    case ZCAN:
    case ERROR:
    case TIMEOUT:
    case RCDO:
#ifdef DEBUGZ
        dlogit(("@zgethdr got %s", frametypes[c + FTOFFSET]));
#endif

static int near zrbhdr(char *hdr)
{
    int c, n;
    unsigned short crc;

    if ((c = zdlread()) & ~0xff)
        return c;

    Rxtype = c;
    crc = ZmUpdCrc(c, 0);

    for (n = 4; --n >= 0; ++hdr)
    {
        if ((c = zdlread()) & ~0xff)
            return c;

        crc = ZmUpdCrc(c, crc);
        *hdr = c;
    }

    if ((c = zdlread()) & ~0xff)
        return c;

    crc = ZmUpdCrc(c, crc);

    if ((c = zdlread()) & ~0xff)
        return c;

    crc = ZmUpdCrc(c, crc);

    if (crc & 0xFFFF)
    {
        zperr(bad_crc_hdr);
        return ERROR;
    }

    return Rxtype;
}


static int near zgethex(void)
{
    int c;

    c = zgeth1();

    if (Verbose > 8)
        dlogit(("@zgethex: %02X", c));

    return c;
}
#else
#define zgethex() zgeth1()
#endif


        switch (c = readline(1))
        {
        case 0x0a:

static void near zsendline(int c)
{


        case 0x10:
        case 0x11:
        case 0x13:
        case 0x90:
        case 0x91:
        case 0x93:
            zmdm_pputcw(ZDLE);
            c ^= 0x40;

        sendit:
            zmdm_pputcw(lastsent = c);
            break;

        default:
            if (Zctlesc && !(c & 0x60))
            {
                zmdm_pputcw(ZDLE);
                c ^= 0x40;
            }
            zmdm_pputcw(lastsent = c);
        }
    }
}


long rclhdr(char *hdr)
{
    long l;

    l = (hdr[ZP3] & 0xff);
    l = (l << 8) | (hdr[ZP2] & 0xff);
    l = (l << 8) | (hdr[ZP1] & 0xff);
    l = (l << 8) | (hdr[ZP0] & 0xff);
    return l;
}


void zmputs(char *s)
{
    int c;

    while (*s)
    {
        switch (c = *s++)
        {
        case '\336':
            Delay(100);
            continue;

        case '\335':
            sendbrk();
            continue;

        default:
            zmdm_pputcw(c);
        }
    }
}


    mode(1);
    dumpmo();
    Delay(50);
    mode(2);


    flushmo();


int readline(int timeout)
{

    return (*cdq++ & 0xff);
}


void purgeline(void)
{
    Lleft = 0;
    mdm_dump(DUMP_INPUT);
}

