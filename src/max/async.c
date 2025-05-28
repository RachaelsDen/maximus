// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: async.c,v 1.1.1.1 2002/10/01 17:50:45 sdudley Exp $";
#pragma on(unreferenced)

#ifdef OS_2

#define MAX_INCL_COMMS
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INCL_NOPM
#define INCL_DOS
#define INCL_DOSERRORS
#define INCL_DOSDEVIOCTL
#include "pos2.h"
#undef CONTROL
#include "comm.h"
#include "mm.h"


int GetConnectionType(void)
{
    HFILE hf;
    int rc;

    typedef struct
    {
        USHORT cbSize;
        BYTE bStatus;
    } VMPORTDATA;

    VMPORTDATA vpd = {sizeof(VMPORTDATA), 0};

    if (local)
        return CTYPE_LOCAL;

#ifdef __FLAT__
    {
        ULONG dlen, plen;

        hf = ComGetFH(hcModem);

        plen = 0;
        dlen = sizeof vpd;

        rc = DosDevIOCtl(hf, IOCTL_ASYNC, 0xe8, NULL, 0L, &plen, &vpd, sizeof vpd, &dlen);
    }
#else
    hf = ComGetFH(hcModem);

    rc = DosDevIOCtl2(&vpd, sizeof vpd, (PVOID)0, 0, 0xe8, IOCTL_ASYNC, hf);
#endif

    return rc ? CTYPE_ASYNC : (int)vpd.bStatus;
}

void com_DTR_on(void)
{
    DCBINFO sDCB;
    USHORT rc;

    if (!(rc = ComGetDCB(hcModem, &sDCB)))
    {
        ComSetDCB(hcModem, &sDCB);
    }
    else
        logit("!SYS%04u: ComGetDCB()", rc);
}

void com_XON_disable(void)
{
    DCBINFO sDCB;
    USHORT rc;

    if (!(rc = ComGetDCB(hcModem, &sDCB)))
    {
void com_break(int on)
{
    OS2UINT cmd;
    OS2UINT comerr;
    OS2UINT rc;
    HFILE hf;

    cmd = on ? ASYNC_SETBREAKON : ASYNC_SETBREAKOFF;
    hf = ComGetFH(hcModem);

    if (hf)
    {
#ifdef __FLAT__
        ULONG dlen, plen;

        plen = 0;
        dlen = sizeof(comerr);

        rc = DosDevIOCtl(hf, IOCTL_ASYNC, cmd, NULL, 0L, &plen, &comerr, sizeof(comerr), &dlen);
#else
        rc = DosDevIOCtl(&comerr, 0L, cmd, IOCTL_ASYNC, hf);
#endif

        if (rc)
            logit("!SYS%04u: ASYNC_SETBREAK", rc);
    }
}

static void near ShowMdmSettings(void)
{
#if 1
    return;
#else
    DCBINFO dcb;
    char *On = "On";
    char *Off = "Off";
    char *dtr;
    char *rts;
    char *buffer;
    int Rx = 0, Tx;

    if (!ComGetDCB(hcModem, &dcb))
    {
        logit(" Modem: TO=%s,XON(Rx)=%s,XON(Tx)=%s",
              (dcb.fbTimeout & MODE_NO_WRITE_TIMEOUT) ? On : Off,
              (dcb.fbFlowReplace & MODE_AUTO_RECEIVE) ? On : Off,
              (dcb.fbFlowReplace & MODE_AUTO_TRANSMIT) ? On : Off);
        logit(" Modem: IDSR=%s,ODSR=%s,OCTS=%s",
              (dcb.fbCtlHndShake & MODE_DSR_SENSITIVITY) ? On : Off,
              (dcb.fbCtlHndShake & MODE_DSR_HANDSHAKE) ? On : Off,
              (dcb.fbCtlHndShake & MODE_CTS_HANDSHAKE) ? On : Off);
        switch (dcb.fbCtlHndShake & (MODE_DTR_CONTROL | MODE_DTR_HANDSHAKE))
        {
        case 0:
            dtr = Off;
            break;
        case MODE_DTR_CONTROL:
            dtr = On;
            break;
        case MODE_DTR_HANDSHAKE:
            dtr = "IHS";
    }
#endif
}

int Cominit(int port)
{
    char tmp[20];
    USHORT rc;
    HFILE hf;

    if (hcModem)
    {
        ComResume(hcModem);
        return 0x1954;
    }

    if (port_is_device)
    {
        sprintf(tmp, "com%1u", port + 1);
        rc = ComOpen(tmp, &hcModem, 8200, 8200);
    }
    else
    {
        sprintf(tmp, "handle %d", port + 1);
        hf = (HFILE)port + 1;
        rc = ComHRegister(hf, &hcModem, 8200, 8200);
    }

    if (rc)
    {
        logit("!SYS%04u:  Cannot open com port (%s)", rc, tmp);
        return 0;
    }

    DosSetPrty(PRTYS_THREAD, PRTYC_NOCHANGE, 2, 0);
    ShowMdmSettings();

    return 0x1954;
}

