// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_full.c,v 1.2 2003/06/04 23:31:28 wesgarland Exp $";
#pragma on(unreferenced)

#include "m_full.h"
#include "max_msg.h"
#include "prog.h"
#include <stdio.h>
#include <string.h>

static char *near Show_Attributes(long attr, char *str);
static void near DisplayMessageFrom(XMSG *msg);
static void near DisplayMessageTo(XMSG *msg);

void DrawReaderScreen(MAH *pmah, int inbrowse)
{
    Printf(inbrowse ? browse_rbox_top : reader_box_top, PMAS(pmah, name), PMAS(pmah, descript),
           TermWidth() - strlen(MAS(*pmah, descript)) - strlen(MAS(*pmah, name)) - 5);
    Printf(reader_box_mid, (prm.flags2 & FLAG2_UMSGID) ? reader_box_highest : reader_box_of);
    Printf(reader_box_from);
    Printf(reader_box_to);
    Printf(reader_box_subj);
    Printf(reader_box_bottom, TermWidth());
}

void DisplayMessageHeader(XMSG *msg, word *msgoffset, long msgnum, long highmsg, MAH *pmah)
{
    DisplayMessageNumber(msg, msgnum, highmsg);
    DisplayMessageAttributes(msg, pmah);
    DisplayMessageFrom(msg);
    DisplayMessageTo(msg);
    DisplayMessageSubj(msg, pmah);
    Puts(reader_msg_init);

    if (msgoffset)
        *msgoffset = (hasRIP()) ? 1 : 7;
}

void DisplayMessageNumber(XMSG *msg, long msgnum, long highmsg)
{
    int i;
    long tlong;
    char tmp[64];

    Printf(rbox_msgn, UIDnum(msgnum ? msgnum : MsgGetHighMsg(sq)) + !msgnum);
    Printf(rbox_high, UIDnum(highmsg));

    i = 0;
    if (msg->replyto)
    {
        tlong =
            (prm.flags2 & FLAG2_UMSGID) ? msg->replyto : MsgUidToMsgn(sq, msg->replyto, UID_EXACT);

        if (tlong)
            i += sprintf(tmp, rbox_replyto, tlong);
    }

    if (msg->replies[0])
    {
        tlong = (prm.flags2 & FLAG2_UMSGID) ? msg->replies[0]
                                            : MsgUidToMsgn(sq, msg->replies[0], UID_EXACT);

        if (tlong)
            i += sprintf(tmp + i, rbox_replies, tlong);
    }

    if (i)
        Printf(rbox_links, tmp);
}

void DisplayMessageAttributes(XMSG *msg, MAH *pmah)
{
    char temp[PATHLEN];
    long amask;


    if (pmah->ma.attribs & MA_SHARED)
        amask &= ~MSGKILL;

    Printf(rbox_attrs, Show_Attributes(msg->attr & amask, temp));
}

static char *near Show_Attributes(long attr, char *str)
{
    int i;
    long acomp;


static void near DisplayMessageFrom(XMSG *msg)
{
    DisplayShowName(rbox_sho_fname, msg->from);
    DisplayShowDate(rbox_sho_fdate, (union stamp_combo *)&msg->date_written);
    DisplayShowAddress(rbox_sho_faddr, &msg->orig, &mah);
}

static void near DisplayMessageTo(XMSG *msg)
{
    DisplayShowName(rbox_sho_tname, msg->to);
    DisplayShowDate(rbox_sho_tdate, (union stamp_combo *)&msg->date_arrived);
    DisplayShowAddress(rbox_sho_taddr, &msg->dest, &mah);
}

void DisplayShowName(char *sho_name, char *who) { Printf(sho_name, Strip_Ansi(who, NULL, 0L)); }

void DisplayShowDate(char *sho_date, union stamp_combo *sc)
{
    char temp[PATHLEN];

    Printf(sho_date, MsgDte(sc, temp));
}

void DisplayShowAddress(char *sho_addr, NETADDR *n, MAH *pmah)
{
    Printf(sho_addr, (pmah->ma.attribs & MA_NET) ? (char *)Address(n) : (char *)blank_str);
}

void DisplayMessageSubj(XMSG *msg, PMAH pmah)
{
