// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: me_misc.c,v 1.2 2003/06/05 23:26:49 wesgarland Exp $";
#pragma on(unreferenced)


#include "m_for.h"
#include "max_edit.h"
#include "max_msg.h"
#include "node.h"
#include "prog.h"
#include "trackm.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KLUDGE_LEN 512

static int near Handle_Matrix_Charges(NETADDR *dest, int total);


word WroteMessage(PMAH pmah, XMSG *msg, char *kludges, HAREA ha, int chg)
{
    word ok = TRUE;


        if (!ok)
            Puts(ncredit);
    }
    else if (pmah->ma.attribs & MA_ECHO)
        written_echomail = TRUE;
    else if (pmah->ma.attribs & MA_CONF)
        written_conf = TRUE;
    else
        written_local = TRUE;


    if (!chg)
        TrackAddMessage(pmah, msg, kludges, ha);
#endif

    ci_posted();
    usr.msgs_posted++;
    bstats.msgs_written++;

    return ok;
}

void GenerateOriginLine(char *text, PMAH pmah)
{
            us_short, tear_ver,

            pmah->ma.seenby.net, pmah->ma.seenby.node);
}

static int near Handle_Matrix_Charges(NETADDR *dest, int total)
{
    NFIND *nf;
    word cost;

    if ((nf = NodeFindOpen(dest)) == NULL)
    {
    {
        if (total)
        {
            Puts(ms_1);
            Printf(ms_2, usr.credit);
            Printf(ms_3, usr.debit);
            Printf(ms_4, cost);
        }

        usr.debit += cost;

        if (usr.debit > usr.credit && !mailflag(CFLAGM_ATTRANY))
        {
            usr.debit -= cost;
            return -1;
        }

        if (total)
        {
            Printf(ms_5, usr.credit - usr.debit);

            logit(log_charge, cost);

            if (usr.credit - usr.debit < 100)
                logit(log_bal, usr.credit - usr.debit);
        }
    }

    return 0;
}


char *GenerateMessageKludges(XMSG *msg, PMAH pmah, char *ctrl_buf)
{
    char temp[PATHLEN];
    char *kludge, *kend;


    if (!InCtrlBuf(kludge, actrack_colon) && TrackNeedToAdd(pmah, msg))
    {
        GenerateActrack(msg, kend);
        kend += strlen(kend);
    }
#endif


    if (pmah->ma.primary.point)
        sprintf(temp, ".%u", pmah->ma.primary.point);
    else
        *temp = '\0';


    if (!eqstri(msg->from, usr.name) && !mailflag(CFLAGM_NOREALNM) &&
        !(pmah->ma.attribs & MA_NORNK) && !InCtrlBuf(kludge, "REALNAME:"))
    {
        sprintf(kend, "\x01REALNAME: %s", usr.name);
        kend += strlen(kend);
    }


        sprintf(kend,
                "\x01"
                "INTL %u:%u/%u %u:%u/%u",
                msg->dest.zone, msg->dest.net, msg->dest.node, msg->orig.zone, msg->orig.net,
                msg->orig.node);


        msg->dest.node = msg->dest.zone;
        msg->dest.net = msg->orig.zone;
        msg->dest.zone = msg->orig.zone;
        msg->dest.point = 0;
    }


    return kludge;
}

void AddToEchoToss(char *tag)
{
    char temp[PATHLEN];
    int found = FALSE;
    FILE *fptr;

    if ((prm.flags & FLAG_log_echo) == 0)
        return;

    if (strchr(PRM(echotoss_name), '%'))
        Parse_Outside_Cmd(PRM(echotoss_name), temp);
    else
        strcpy(temp, PRM(echotoss_name));

    if ((fptr = shfopen(temp, fopen_writep, O_CREAT | O_RDWR | O_NOINHERIT)) == NULL)
    {
        cant_open(temp);
        return;
    }

    while (fgets(temp, PATHLEN, fptr))
    {
        Strip_Trailing(temp, '\n');
        Strip_Trailing(temp, ' ');

        if (eqstri(temp, tag))
        {
            found = TRUE;
            break;
        }
    }

    if (!found)
    {
        fseek(fptr, 0L, SEEK_END);
        fprintf(fptr, "%s\n", strupr(tag));
    }

    fclose(fptr);
}
