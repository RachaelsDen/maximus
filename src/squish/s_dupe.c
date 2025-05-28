// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_dupe.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#include "s_dupe.h"
#include "crc.h"
#include "dr.h"
#include "prog.h"
#include "squish.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef UNIX
#include <errno.h>
#endif

static int dfile = -1;
static DUPEHEAD dh = {0};

static int have_last_dupe = FALSE;
static DUPEID lastdupe;

static char dupefile_sdm[] = "%s" PATH_DELIMS "dupefile.dat";
static char dupefile_sq[] = "%s.sqb";
static char msgid_str[] = "MSGID";


static int near VerifyMsgid(HAREA sq, dword msgn, dword msgid_hash, dword msgid_serial)
{
    dword ctlen;
    char *ctrl;
    HMSG hmsg;
    int rc = FALSE;

    if ((hmsg = MsgOpenMsg(sq, MOPEN_READ, msgn)) == NULL)
        return FALSE;

    ctlen = MsgGetCtrlLen(hmsg);

    if ((ctrl = malloc((size_t)ctlen + 5)) != NULL)
    {
        char *kludge;

        MsgReadMsg(hmsg, NULL, 0L, 0L, NULL, ctlen, ctrl);

        if ((kludge = MsgGetCtrlToken(ctrl, msgid_str)) != NULL)
        {
            dword msg_hash, msg_serial;

            MashMsgid(kludge + 7, &msg_hash, &msg_serial);
            MsgFreeCtrlToken(kludge);

            rc = (msg_hash == msgid_hash && msg_serial == msgid_serial);
        }

        free(ctrl);
    }

    MsgCloseMsg(hmsg);
    return rc;
}


dword FindUpdateMessage(HAREA sq, struct _cfgarea *ar, dword msgid_hash, dword msgid_serial,
                        dword **ppmsgid_hash, dword **ppmsgid_serial)
{
    DUPEID far *dptr, far *dend;
    DUPEID far *dupelist;

    if (config.has_dlist != ar || !config.dupe_msgs)
    {
        S_LogMsg("!Internal error - config.has_dlist != ar!");
        return 0L;
    }

    dupelist = (DUPEID far *)((DUPEHEAD far *)dupebuf + 1);

    for (dptr = dupelist, dend = dptr + dh.num_dupe; dptr < dend; dptr++)
    {
        if (msgid_hash == dptr->msgid_hash && msgid_serial == dptr->msgid_serial && dptr->umsgid)
        {
            dword msgn = MsgUidToMsgn(sq, dptr->umsgid, UID_EXACT);

            if (VerifyMsgid(sq, msgn, msgid_hash, msgid_serial))
            {
                *ppmsgid_hash = &dptr->msgid_hash;
                *ppmsgid_serial = &dptr->msgid_serial;
                return msgn;
            }
        }
    }

    return 0L;
}


static dword near crc2word(char *str, dword crc)
{
    unsigned spaces;
    char *p;

    for (p = str, spaces = 0; *p; p++)
    {
        if (*p == ' ' && ++spaces == 2)
            break;
        else if (((byte)*p & (byte)0x80u) || (byte)*p <= (byte)' ')
            break;
        else
            crc = xcrc32(tolower(*p), crc);
    }

    return crc;
}


static void near WriteDupeList(void)
{
    char fname[PATHLEN];
    struct _cfgarea *pa;
    int size;


    dh.sig = DUPEHEAD_SIG;
    *(DUPEHEAD *)dupebuf = dh;

    size = config.dupe_msgs * sizeof(DUPEID) + sizeof(DUPEHEAD);

    MakeDupeFileName(fname, pa);

    if (dfile == -1 && (dfile = shopen(fname, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY)) == -1)
    {

        if ((pa->type & MSGTYPE_SDM) && !direxist(pa->path))
            mkdir(pa->path);

        if ((dfile = shopen(fname, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY)) == -1)
            S_LogMsg("!Error creating dupe file for %s! (%d)", pa->path, errno);
    }

    if (dfile != -1)
    {
        if (farwrite(dfile, (char far *)dupebuf, size) != (int)size)
            S_LogMsg("!Error writing to dupe file for %s!", pa->path);

        (void)close(dfile);
    }

    dfile = -1;

    farfree(dupebuf);
    dupebuf = NULL;
    config.has_dlist = NULL;
    have_last_dupe = FALSE;
}


    if (dupebuf == NULL)
    {

    MakeDupeFileName(fname, ar);

    config.has_dlist = ar;

    if ((dfile = shopen(fname, O_RDWR | O_BINARY | O_NOINHERIT)) == -1)
    {
        (void)memset(dupebuf, '\0', size);
        return TRUE;
    }

    if (farread(dfile, (char far *)dupebuf, size) != (int)size)
    {

void DupeFlushBuffer(void)
{
    if (!config.dupe_msgs)
        return;

    WriteDupeList();
    dupebuf = NULL;
}


    pid->crc = crc2word(msg->from, pid->crc);
    pid->crc = crc2word(msg->to, pid->crc);


    while (temp[0] == 'r' && temp[1] == 'e' && temp[2] == ':' && temp[3] == ' ')
        (void)memmove(temp, temp + 4, strlen(temp + 4) + 1);

    for (p = temp; *p; p++)
        if (*p != ' ')
            pid->crc = xcrc32(*p, pid->crc);


    if (msg->date_written.date.yr == 0)
        pid->date = crcstr((dword)0xffffffffLu, msg->__ftsc_date);
    else
    {
        char *date = msg->__ftsc_date;
        int ch;

        pid->date = *(dword *)(char *)&msg->date_written;


void GetDidMsgid(DUPEID *pid, char *ctrl)
{
    char *msgid = MsgGetCtrlToken(ctrl, msgid_str);


int IsADupe(struct _cfgarea *ar, XMSG *msg, char *ctrl, dword uid)
{
    DUPEID far *dupelist;
    DUPEID did, far *dptr, far *dend;
    int fCheckHeader;
    int fCheckMsgid;

    if (!ar || !config.dupe_msgs)
        return FALSE;


    GetDidHeader(&did, msg);
    GetDidMsgid(&did, ctrl);


    if (dh.high_dupe == config.dupe_msgs)
        dh.high_dupe = 0;


        if ((fCheckHeader && did.crc == dptr->crc && did.date == dptr->date) ||
            (fCheckMsgid && did.msgid_hash && did.msgid_hash == dptr->msgid_hash &&
             did.msgid_serial == dptr->msgid_serial))
        {
            return TRUE;
        }
    }

    lastdupe = dupelist[dh.high_dupe];
    have_last_dupe = TRUE;

    dupelist[dh.high_dupe] = did;

    if (++dh.high_dupe > dh.num_dupe)
        dh.num_dupe = dh.high_dupe;

    return FALSE;
}
