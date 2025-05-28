// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mh_tty.c,v 1.1.1.1 2002/10/01 17:52:33 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_bor

#include "mh_tty.h"
#include "display.h"
#include "keys.h"
#include "max_msg.h"
#include "node.h"
#include "prog.h"
#include <ctype.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *msgname;

int GetTTYHeader(XMSG *msg, PMAH pmah, char *mname, long mn, long highmsg)
{
    int ret, i;

#define TTYQS 6

    static int(near * TTYMsgEntryPtr[TTYQS])(PMAH pmah, XMSG * msg) = {
#define NUM_TTY_HEADFUNCS 5

        TTYGetPrivate, TTYGetNetmailAddress, TTYGetToField,
        TTYGetSubject, TTYGetFrom,           TTYGetAttach};

    NW(mn);
    NW(highmsg);

    msgname = mname;

    DisplayEmptyHeader(pmah);


    for (i = 0, ret = 0; i < TTYQS && ret == 0; i++)
        ret = (*TTYMsgEntryPtr[i])(pmah, msg);

    return ret;
}

int near TTYGetPrivate(PMAH pmah, XMSG *msg)
{
    char temp[PATHLEN];
    byte ch;
    ;

    sprintf(temp, "%sWHY_PVT", PRM(misc_path));

    if ((pmah->ma.attribs & (MA_PUB | MA_PVT)) == (MA_PUB | MA_PVT))
    {
        if (msg->attr & MSGPRIVATE)
            ch = GetYnhAnswer(temp, apvt, 0);
        else
            ch = GetyNhAnswer(temp, apvt, 0);

        if (ch == YES)
            msg->attr |= MSGPRIVATE;
        else
            msg->attr &= ~MSGPRIVATE;

        Putc('\n');
    }

    Clear_KBuffer();

    return 0;
}

int near TTYGetNetmailAddress(PMAH pmah, XMSG *msg)
{
    NETADDR *d;
    NFIND *nf;
    int len;

    d = &msg->dest;

    if (!(pmah->ma.attribs & MA_NET))
        return 0;


        if (!*netnode || !isareply)
        {
            WhiteN();

        }


        if (*netnode && (netnode[len = strlen(netnode) - 1] == '/' || netnode[len] == '#'))
        {

            if (len > 1)
            {

        if (!*netnode)
        {
            strcpy(netnode, Address(&msg->dest));
            fUsedDefault = TRUE;
        }


        strcpy(netnode, Address(d));


            Printf("%0.34s, %0.20s\n\n", nf->found.name, nf->found.city);
            NodeFindClose(nf);

            break;
        }
        else
        {

            if (GEPriv(usr.priv, prm.unlisted_priv))
                break;
            else
            {

                if (fUsedDefault)
                    return -1;

                *netnode = '\0';
            }
        }

    if (!isareply)
    {
        strcpy(oldto, msg->to);
        *msg->to = '\0';
    }

    while (isblstr(msg->to))
    {
        if ((prm.flags & FLAG_no_ulist) == 0 && (pmah->ma.attribs & MA_NET) == 0)

        if (*oldto && !isareply)
            Printf(keep_to, oldto);


        InputGetsNH(msg->to, min(34, (TermWidth() - current_col) + 1), NULL);

        if (*msg->to == '\0' && *oldto && !isareply)
        {
            strcpy(msg->to, oldto);
            break;
        }


        if (eqstr(msg->to, qmark))
        {
            char temp[PATHLEN];


            sprintf(temp, "%suserlist", PRM(misc_path));
            if (Display_File(DISPLAY_NONE, NULL, temp) != 0 && !(prm.flags & FLAG_no_ulist))
            {
                Putc('\n');
                UserList();
                Putc('\n');
            }
            *msg->to = '\0';
            continue;
        }

        if (isblstr(msg->to))
            return -1;


        if ((pmah->ma.attribs & MA_NET) == 0 && eqstri(msg->to, sysop_txt))
        {
            Printf(mroute_sysop, PRM(sysop));
            strcpy(msg->to, PRM(sysop));
        }
        else
        {

            if (*msg->to && (pmah->ma.attribs & (MA_NET | MA_SHARED)) == 0 &&
                (msg->attr & MSGPRIVATE) && !IsInUserList(msg->to, TRUE))
            {

                *msg->to = '\0';
                Puts(userdoesntexist);
                Putc('\n');
            }

    return 0;
}

int near TTYGetSubject(PMAH pmah, XMSG *msg)
{
    char *rdbox, temp[PATHLEN];


    for (i = 1; i < 16; i++)
    {
        if (GEPriv(usr.priv, prm.msg_assume[i]) ||
            (GEPriv(usr.priv, prm.msg_ask[i]) && GetyNAnswer(s_ret(n_msg_attr0 + i), 0) == YES))
        {
            msg->attr |= (1 << i);
        }
        else
            msg->attr &= ~(1 << i);
    }

    msg->attr |= MSGLOCAL;
}

static void near DisplayEmptyHeader(PMAH pmah)
{

    if (usr.bits2 & BITS2_CLS)
        Puts(CLS);
    else if (usr.video)
    {
        Puts(avt_home);

        Printf("\x16\x19\x03"
               "\n" CLEOL "%c",
               TermLength() - !!(prm.flags & FLAG_statusline));
    }

    Puts("\x16\x08\x03\x01" CYAN);

    else if (pmah->ma.attribs & MA_PVT)

    if (pmah->ma.attribs & MA_ECHO)
    Printf(this_area, msgname);
}

int near TTYGetAttach(PMAH pmah, XMSG *msg)
{
    if (!(msg->attr & MSGFILE) && AllowAttribute(pmah, MSGKEY_LATTACH) &&
        (pmah->ma.attribs & MA_ATTACH) && GetyNAnswer(msg_with_attach, 0) == YES)
    {
        msg->attr |= MSGFILE;
    }

    return 0;
}
