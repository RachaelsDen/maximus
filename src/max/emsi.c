// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: emsi.c,v 1.1.1.1 2002/10/01 17:50:54 sdudley Exp $";
#pragma on(unreferenced)


#ifdef EMSI

#include "emsi.h"
#include "crc.h"
#include "emsip.h"
#include "mm.h"
#include "modem.h"
#include <stdarg.h>
#include <string.h>

static char location[] = "Kingston, Ontario";
static byte emsi_buf[EMSI_MAX + 20];
static char *emsi_max = emsi_buf + EMSI_MAX;
static word emsi_len;
static char px[] = "%x";
static char plx[] = "%lx";

unsigned fGotICI, fAbort, fEMSI;


word EmsiCheck(int ch)
{
    struct _eft *ep;
    char frame[5];

    if (fAbort || !EmsiGotInit(ch))
        return FALSE;


    for (ep = eft; *ep->type; ep++)
        if (!*ep->type || strncmp(ep->type, frame, 3) == 0)
        {
            if (!EmsiCrcOK(ep->crc_len) || !(*ep->handler)())
                EmsiTxFrame(EMSI_NAK);

            break;
        }

    return TRUE;
}


    if ((char)ch != emsi_seq[estate])
    {
        estate = 0;
        return FALSE;
    }


static word near EmsiGetHeader(char *frame)
{
    long t;
    char *fp;


    for (fp = frame; !timeup(t) && fp < frame + 3;)
        if (Mdm_keyp())
            *fp++ = Mdm_getcw() & 0x7f;

    *fp = '\0';

    strcpy(emsi_buf, emsi_seq);
    strcat(emsi_buf, frame);

    logit("^EmsiGetHeader - Got %s", frame);


static word near EmsiReadLine(void)
{
    long t;
    char *p;

    logit("^EmsiReadLine");


    crc16 = 0;


    crc32 = 0xffffffffLu;

    for (s = emsi_buf + 2, e = s + len; s < e; s++)
        crc32 = crc32fn(*s, crc32);

    logit("@EmsiCalcCrc32 - %08lx", crc32);
    return crc32;
}


    if (len == 16)
    {
        e -= 4;

        logit("@EmsiCrcOK16 - ASCII CRC=%s", e);

        if (sscanf(e, px, &crc16) != 1)
            return FALSE;
    }
    else
    {
        e -= 8;

        logit("@EmsiCrcOK32 - ASCII CRC=%s", e);

        if (sscanf(e, plx, &crc32) != 1)
            return FALSE;
    }


static word near EmsiFtACK(void)
{
    logit("^EmsiFtACK");

    if (!fGotICI)
        return TRUE;

    return TRUE;
}

    return TRUE;
}


    if (fGotICI || fLoggedOn)
        return TRUE;


    if (sscanf(buf, px, &len) != 1)
        return FALSE;

    if (len > emsi_len - 4)
        len = emsi_len - 4;


            EmsiTxFrame(EMSI_IIR);
            fAbort = TRUE;
            return TRUE;
        }

    logit("^EmsiFtICI - Name: %s", eclr.ec_name);
    logit("^EmsiFtICI - Alias: %s", eclr.ec_alias);
    logit("^EmsiFtICI - City: %s", eclr.ec_city);
    logit("^EmsiFtICI - Phdata: %s", eclr.ec_phdata);
    logit("^EmsiFtICI - Phvoice: %s", eclr.ec_phvoice);
    logit("^EmsiFtICI - Pwd: %s", eclr.ec_pwd);
    logit("^EmsiFtICI - Dob: %s", eclr.ec_dob);
    logit("^EmsiFtICI - Crt: %s", eclr.ec_crt);
    logit("^EmsiFtICI - Proto: %s", eclr.ec_proto);
    logit("^EmsiFtICI - Cap: %s", eclr.ec_cap);
    logit("^EmsiFtICI - Req: %s", eclr.ec_req);
    logit("^EmsiFtICI - Sw: %s", eclr.ec_sw);
    logit("^EmsiFtICI - Xlat: %s", eclr.ec_xlat);

    fGotICI = TRUE;


        EmsiTxFrame(EMSI_ISI);

        t1 = timerset(2000);

    GetNext:

        switch (frame = EmsiPollFrame(t1))
        {
        case EMSI_ACK:
            logit("^EmsiFtICI-ISI: Got ACK");
            fEMSI = TRUE;
            break;

        case EMSI_NAK:
            logit("^EmsiFtICI-ISI: Got NAK");

    if (!tries)
    {
        EmsiTxFrame(EMSI_IIR);
        fAbort = TRUE;
    }

    return TRUE;
}


static word near EmsiPollFrame(long t)
{
    struct _eft *ep;
    char frame[5];

    logit("^EmsiPollFrame");


    if (!EmsiGetHeader(frame) || !EmsiReadLine())
    {
        logit("^EmsiPollFrame - NAK");
        EmsiTxFrame(EMSI_NAK);
        return EMSI_BAD;
    }

    logit("^EmsiPollFrame - Got `%s'", emsi_buf);


static word near EmsiFtBAD(void)
{
    logit("^EmsiFtBAD");
    return TRUE;
}


    if (*p++ != '{')
        return FALSE;


        if (*p == '\\')
        {

    if (*p != '}')
        while (p < omax - 1 && *p != '}')
            p++;

    *o = '\0';
    *buf = p + 1;
}


void EmsiTxFrame(word ft)
{
    char buf[30];
    struct _eft *ep;
    word crc16;
    long crc32;

    logit("@EmsiTxFrame1");


    if (!ep->ft)
        return;


    logit("@EmsiTxFrame2 - Send %s", ep->type);

    if (ep->bldfunc)
        (*ep->bldfunc)();

    logit("@EmsiTxFrame3");


static word near EmsiTxBytes(char *buf, word len)
{
    long txtimer;
    int got;
    char *s;

    if (local)
        return TRUE;

    txtimer = timerset(3000);

    logit("@EmsiTxBytes");

    for (s = buf; (got = mdm_blockwrite(len, s)) < len;)
    {
        if (!carrier() || timeup(txtimer))
        {
            logit("^EmsiTxBytes - Timeout");
            return FALSE;
        }

        s += got;
        len -= got;

        if (len > 100)
            Giveaway_Slice();
    }

    return TRUE;
}


    va_start(var_args, fmt);
    vsprintf(string, fmt, var_args);
    va_end(var_args);


    for (p = string; *p; p++)
    {
        if (*p == '\\' || *p == '{' || *p == '}' || *p < ' ' || *p >= 0x7f)
        {

static void near EmsiBldISI(void)
{
    char buf[20];
    char *lp;

    EmsiBldA1("Maximus - Copyright " THIS_YEAR " by Scott J. Dudley.  All rights reserved.");


    sprintf(buf, "%04X", strlen(emsi_buf) - 14);
    memmove(lp, buf, 4);
}



