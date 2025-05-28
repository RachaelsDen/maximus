// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_read.c,v 1.1.1.1 2002/10/01 17:52:48 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS
#define MAX_LANG_m_browse

#include "m_full.h"
#include "m_readp.h"
#include "max_msg.h"
#include "node.h"
#include "prog.h"
#include "trackm.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void near Clear_To_Screen_End();
static int near Msg_Read_RepOrig(int orig);
static int near Msg_Get_Msgs(int dir, dword startmsg, int nonstop, int exact, int show_err);
static int near MoreYnns_Read(int inbrowse);
static void near Display_Addr(char *orig_or_dest, char *type, word *msgoffset, NETADDR *addr);

struct _show_kludges
{
    char *paged;
    int msgoffset;
    int pause;
    char *nonstop;
};

static void near GotoCleos(int msgoffset)
{
    if (usr.bits2 & BITS2_CLS)
    {
        Goto(msgoffset, 1);
        Clear_To_Screen_End();
    }
}

static int near DoTheMoreThing(char *nonstop, char *paged, int msgoffset, int inbrowse)
{
    int ch;

    Puts(CYAN CLEOL);

    if ((ch = MoreYnns_Read(inbrowse)) == YES)
    {
        *paged = TRUE;
        GotoCleos(msgoffset);
    }
    else if (ch == M_NONSTOP)
        *nonstop = TRUE;
        {
            next_menu_char = ch;
            display_line = (usr.video || !(usr.bits2 & BITS2_CLS)) ? 1 : msgoffset;
        }
        return FALSE;
    }

    if (*nonstop || usr.video == GRAPH_TTY || !(usr.bits2 & BITS2_CLS))
        display_line = display_col = 1;

    return TRUE;
}


int ShowKludgeLines(char *ctrl, int (*showfunc)(char *, void *, int), void *args, int inbrowse)
{
    char *kp, *end, *new;
    int rc;

    if (!GEPriv(usr.priv, prm.ctla_priv))
        return 0;

    for (kp = ctrl; kp && *kp == '\x01';)
    {
        end = strchr(++kp, '\x01');

        if (!end)
            end = kp + strlen(kp);

        if (end == kp)
        {
            if (*end == 0)
                break;
            else
                continue;
        }


        if ((new = malloc((end - kp) + 10)) == NULL)
            return 0;

        memmove(new, kp, end - kp);
        new[(end - kp)] = '\0';

        rc = (*showfunc)(new, args, inbrowse);

        free(new);

        if (rc != 0)
            return rc;

        kp += end - kp;
    }

    return 0;
}

static int near Ask_KillMsg(XMSG *msg)
{
    int x;

    if ((msg->attr & MSGPRIVATE) == 0 || *linebuf)
        return FALSE;

    switch (prm.auto_kill)
    {
        WhiteN();
        x = (GetyNAnswer(del_msg, CINPUT_MSGREAD | CINPUT_NOLF) == YES);
        Putc('\n');
        return x;


int Ask_KillAttach(void)
{
    int rc;

    if (*linebuf)
        return FALSE;

    switch (prm.kill_attach)
    {
        WhiteN();

        if (!GEPriv(usr.priv, prm.kill_attach_priv))
            rc = TRUE;
        else
        {
            rc = (GetYnAnswer(del_attach, CINPUT_MSGREAD | CINPUT_NOLF) == YES);
            Putc('\n');
        }

        return rc;


static int near Ask_DownloadAttach(void)
{
    int rc = FALSE;

    if (!*linebuf)
    {
        WhiteN();
        Putc('\n');
        rc = (GetYnAnswer(dload_attach, CINPUT_MSGREAD | CINPUT_NOLF) != NO);
        Putc('\n');
    }

    return rc;
}

static void near Clear_To_Screen_End()
{
#if 0
  if (usr.video)
  {

    if ((usr.bits & BITS_FSR) && usr.video)
        return;

    if (msg->replyto || msg->replies[0])
        Putc('\r');

    if (msg->replyto)
    {
        otlong =
            (prm.flags2 & FLAG2_UMSGID) ? msg->replyto : MsgUidToMsgn(sq, msg->replyto, UID_EXACT);

        if (otlong)
        {
            Printf(this_reply, otlong);

            if (!msg->replies[0])
                Puts(endofline);
        }
    }

    if (msg->replies[0])
    {
        tlong = (prm.flags2 & FLAG2_UMSGID) ? msg->replies[0]
                                            : MsgUidToMsgn(sq, msg->replies[0], UID_EXACT);

        if (tlong)
        {
            if (msg->replyto && otlong)
                Puts(dot_spsp);
            else
                Putc('\n');

            Printf(see_also, tlong);

            for (i = 1; i < MAX_REPLY && msg->replies[i]; i++)
            {
                tlong = (prm.flags2 & FLAG2_UMSGID) ? msg->replies[i]
                                                    : MsgUidToMsgn(sq, msg->replies[i], UID_EXACT);

                if (tlong)
                    Printf("%s %ld", (i == MAX_REPLY - 1 || !msg->replies[i + 1]) ? and : comma,
                           tlong);
            }

            Puts(endofline);
        }
    }
}

static int near ShowMessageHeader(XMSG *msg, word *msgoffset, long mn)
{
    byte string[PATHLEN];
    long amask;
    long acomp;
    int i;


    sprintf(string, mfrom, msg_from_col, msg_from_txt_col, Strip_Ansi(msg->from, NULL, 0L),
            msg_attr_col);


    if (mah.ma.attribs & MA_SHARED)
        amask &= ~MSGKILL;


    Printf(mto, msg_to_col, msg_to_txt_col, Strip_Ansi(msg->to, NULL, 0L), msg_date_col, UIDnum(mn),
           MsgDate(msg, string));

    if (halt())
        return -1;

    Display_Addr(dest_addr, net_dest, msgoffset, &msg->dest);


    if (got == MAX_MSGDISPLAY)
        last = got - 1;
    else
        last = got;


    if (this < got - 5 || (lt[last] & MSGLINE_END) == 0)
        return FALSE;

    for (i = this; i < got; i++)
    {
        if (*outline[i] || ((lt[i] & MSGLINE_SEENBY) && GEPriv(usr.priv, prm.seenby_priv)) ||
            ((lt[i] & MSGLINE_KLUDGE) && GEPriv(usr.priv, prm.ctla_priv)))
        {
            return FALSE;
        }
    }

    return TRUE;
}

static int near CanShowLine(char linetype)
{
    if (linetype & MSGLINE_KLUDGE)
    {
        if (!GEPriv(usr.priv, prm.ctla_priv))
            return FALSE;
        else
            Puts(msg_kludge_col);
    }
    else if (linetype & MSGLINE_SEENBY)
    {
        if (!GEPriv(usr.priv, prm.seenby_priv))
            return FALSE;
    }
    else if (linetype & MSGLINE_QUOTE)
        Puts(msg_quote_col);
    else
        Puts(msg_text_col);

    return TRUE;
}

static int near ShowMessageLines(int got, byte *outline[], byte lt[], char *paged, word msgoffset,
                                 int pause, char *nonstop, int inbrowse)
{
    int this;

    for (this = 0; this < got; this ++)
    {

            ShowMessageHeader(msg, NULL, msgnum);
            Puts(CLEOS);

            no_remote_output = was_no_output;
        }

#ifdef MAX_TRACKER
        track_ofs = 3;
        track_col = fsr_border_col;
#endif
    }
    else
    {
        if (ShowMessageHeader(msg, &msgoffset, msgnum) == -1)
            return -1;

#ifdef MAX_TRACKER
        track_ofs = 1;
        track_col = WHITE;
#endif
    }

#ifdef MAX_TRACKER
    TrackShowInfo(sq, &mah, msg, msgnum, ctrl, msgoffset - 1, track_ofs, track_col);
#endif

    logit(log_read_msg, msgnum, areano);


    if ((n_ol = Alloc_Outline(ol)) < 1)
        return -2;


            if (kret == -1)
                return -1;
            else
                return 0;
        }
    }

    Dealloc_Outline(ol);

    if (display_line >= (byte)(TermLength() - 1) && pause && !nonstop)
    {
        if (!DoTheMoreThing(&nonstop, &paged, msgoffset, inbrowse))
            return -1;
    }
    else
        Clear_To_Screen_End();

    if ((msg->replies[0] || msg->replyto) && display_line >= TermLength() - 3)
    {
        if ((usr.bits2 & BITS2_CLS) && pause)
            Goto(TermLength(), 1);

        if (pause && !nonstop)
            DoTheMoreThing(&nonstop, &paged, msgoffset, inbrowse);
    }

    if (!*linebuf)
        Show_Replies(msg);

    {
        if (display_line < (byte)(TermLength() - 1))
            Putc('\n');

        if ((usr.bits2 & BITS2_CLS) && pause && !hasRIP())
            Goto(TermLength() - 1, 1);

        if (pause)
            DoTheMoreThing(&nonstop, &paged, msgoffset, inbrowse);
    }

    return 0;
}

static void near Display_Addr(char *orig_or_dest, char *type, word *msgoffset, NETADDR *addr)
{
    NFIND *nf;

    if (!(mah.ma.attribs & MA_NET))
        return;

    if (MsgToUs(addr))
        return;

    if ((nf = NodeFindOpen(addr)) != NULL)
    {
        Printf(addrfmt, msg_addr_col, orig_or_dest, msg_locus_col, nf->found.name, Address(addr),
               nf->found.city);

        NodeFindClose(nf);
    }
    else
        Printf(unlisted_system, type, Address(addr));

    if (msgoffset)
        (*msgoffset)++;
}

int Msg_Current(void) { return Msg_Get_Msgs(DIRECTION_NEXT, last_msg, FALSE, TRUE, TRUE); }

int Msg_Next(long startmsg)
{
    return Msg_Get_Msgs(direction = DIRECTION_NEXT, startmsg + 1, FALSE, FALSE, TRUE);
}

int Msg_Previous(long startmsg)
{
    return Msg_Get_Msgs(direction = DIRECTION_PREVIOUS, startmsg ? startmsg - 1 : 0xffffffffLu,
                        FALSE, FALSE, TRUE);
}

int Msg_Nonstop(void)
{
    Puts(CLS);
    Printf(message_name, msgar_name, usr.msg, MAS(mah, descript));
    Putc('\n');

    while (Msg_Get_Msgs(direction, last_msg + (direction == DIRECTION_NEXT ? 1 : -1), TRUE, FALSE,
                        FALSE) == 0)
    {
        Puts(n_n);

        if (Mdm_flush_ck() || brk_trapped || mdm_halt())
        {
            brk_trapped = 0;
            mdm_dump(DUMP_ALL);
            ResetAttr();
            return -1;
        }
    }

    return 0;
}

static int near Msg_Get_Msgs(int dir, dword startmsg, int nonstop, int exact, int show_err)
{
    HMSG msgh;
    char *ctrl;
    XMSG msg;
    long clen;
    int ret;


                if (ret == -1)
                {
                    if (ctrl)
                        free(ctrl);

                    return -2;
                }

                if (!nonstop)
                {
                    int isnetmsg = !!(mah.ma.attribs & MA_NET);

                    if (MsgToThisUser(msg.to) && Msg_UnreceivedAttach(&msg, ctrl, isnetmsg))
                    {
                        if (Ask_DownloadAttach())
                            Msg_AttachDownload(&msg, ctrl, isnetmsg);
                        if (Ask_KillAttach())
                            Msg_AttachKill(&msg, ctrl, isnetmsg);
                    }

                    if ((msg.attr & MSGREAD) &&
                        (MsgToThisUser(msg.to) || MsgToThisUser(msg.from)) && Ask_KillMsg(&msg))
                        Msg_Kill(last_msg);
                }

                if (ctrl)
                    free(ctrl);

                return 0;
            }

            MsgCloseMsg(msgh);
        }

        return -1;


    mdm_dump(DUMP_INPUT);

    return -1;
}

int Msg_Read_Reply(void) { return (Msg_Read_RepOrig(FALSE)); }

int Msg_Read_Original(void) { return (Msg_Read_RepOrig(TRUE)); }

static int near Msg_Read_RepOrig(int orig)
{
    HMSG msgh;
    XMSG msg;
    long thismsg;

    if ((msgh = MsgOpenMsg(sq, MOPEN_READ, last_msg)) == NULL)
    {
        Puts(msgnotavail);
        return -1;
    }

    MsgReadMsg(msgh, &msg, 0L, 0L, NULL, 0L, NULL);
    MsgCloseMsg(msgh);

    thismsg = MsgUidToMsgn(sq, orig ? msg.replyto : msg.replies[0], UID_EXACT);

    if (thismsg == 0L || Msg_Get_Msgs(DIRECTION_NEXT, thismsg, FALSE, TRUE, FALSE) == -1)
    {
        Puts(msgnotavail);
        return -1;
    }

    return 0;
}

int Msg_Read_Individual(int ch)
{
    char temp[PATHLEN];

    int msgnum;

    if (!isdigit(ch))
        ch = '0';

    if ((usr.bits & BITS_HOTKEYS) && !*linebuf)
    {

    if (prm.flags2 & FLAG2_UMSGID)
        msgnum = MsgUidToMsgn(sq, msgnum, UID_NEXT);

    if (msgnum && Msg_Get_Msgs(direction, msgnum, FALSE, FALSE, FALSE) == 0)
        return 0;

    Puts(msgnotavail);
    return -1;
}

static int near MoreYnns_Read(int inbrowse)
{
    int c;

    c = GetListAnswer(Yne, NULL, useyforyesns,
                      inbrowse ? CINPUT_NOLF
                               : (CINPUT_NOLF | CINPUT_MSGREAD | CINPUT_ANY | CINPUT_SCAN),
                      inbrowse ? browse_more_prompt : reader_more_prompt);

    if (usr.video == GRAPH_TTY)
        Puts(moreynns_blank);
    else
        Puts(inbrowse ? browse_more_blank : reader_more_blank);

    return c;
}
