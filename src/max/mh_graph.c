// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mh_graph.c,v 1.1.1.1 2002/10/01 17:52:32 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_bor

#include "mh_graph.h"
#include "display.h"
#include "keys.h"
#include "m_full.h"
#include "max_msg.h"
#include "node.h"
#include "prog.h"
#include <ctype.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GotoLocAttr() Puts(reader_pos_attr)
#define GotoLocFrom() Puts(reader_pos_from)
#define GotoAddrFrom() Printf(reader_pos_from_addr)
#define GotoLocTo() Puts(reader_pos_to)
#define GotoAddrTo() Printf(reader_pos_to_addr)
#define GotoLocSubj() Puts(reader_pos_subj)
#define GotoLocSubjField() Puts(reader_pos_subj_field)

static int item = 0;
static int inc = FALSE;
static int goitem = 0;
static long this_msgnum = 0L;
static long high_msg = 0L;

int GetGraphicsHeader(XMSG *msg, PMAH pmah, char *mname, long mn, long highmsg)
{
    int ret = 0;

    static int(near * MsgEntryFtab[GRAPHICS_ENTRY_FUNCS])(PMAH pmah, XMSG *) = {
        GetAttributes, GetFrom, GetFromAddr, GetToField, GetToAddr, GetSubject,
    };

    NW(mname);

    this_msgnum = mn;
    high_msg = (highmsg == -1L) ? MsgGetHighMsg(sq) : highmsg;

    RedrawAll(pmah, msg, TRUE);


    inc = TRUE;

    goitem = (pmah->ma.attribs & MA_ANON) ? ITEM_FROM : ITEM_TO;

    if (*msg->to)
    {
        item = (goitem == ITEM_FROM ? ITEM_FROM : ITEM_SUBJ);
    }
    else if ((pmah->ma.attribs & (MA_PVT | MA_PUB)) != (MA_PVT | MA_PUB) &&
             (pmah->ma.attribs & MA_ATTACH) == 0)
    {
        item = goitem;
    }
    else
    {
        item = ITEM_ATTR;
    }


    if (ret != -1 && (usr.bits2 & BITS2_CLS) && !(usr.bits & BITS_FSR))
        RedrawAll(pmah, msg, FALSE);


    if ((pmah->ma.attribs & (MA_PUB | MA_PVT)) != (MA_PUB | MA_PVT))
    {
        for (i = 0; i < 16; i++)
            if (GEPriv(usr.priv, prm.msg_ask[i]) || mailflag(CFLAGM_ATTRANY))
                break;

        if ((((pmah->ma.attribs & MA_NET) == 0 && !mailflag(CFLAGM_ATTRANY)) || i == 16) &&
            !AllowAttribute(pmah, MSGKEY_LATTACH))
        {
            item = goitem;
            inc = TRUE;
            ret = 0;
            goto DoRet;
        }
    }

    if (usr.help != EXPERT)
    {
        GotoLocText();

            ch = (byte)msgattr_keys[0];

        default:


                        if ((pmah->ma.attribs & MA_ATTACH) && (msg->attr & MSGFILE))
                            *msg->subj = 0;


            if ((pmah->ma.attribs & MA_NET) == 0 && (ch == (byte)msgattr_keys[4]) &&
                AllowAttribute(pmah, MSGKEY_LATTACH))
            {
                msg->attr ^= MSGFILE;
                DisplayMessageAttributes(msg, pmah);
                GotoLocAttr();
                vbuf_flush();
            }
            break;
        }
    }

    item = goitem;
    inc = TRUE;

DoRet:

    DisplayMessageAttributes(msg, pmah);
    GotoLocText();
    Puts(fsr_msginfo_col);

    return ret;
}

int near GetFrom(PMAH pmah, XMSG *msg)
{
    if (!(pmah->ma.attribs & MA_ANON) && !mailflag(CFLAGM_ATTRANY))
    {
        if (inc)
            item++;
        else
            item--;

        return 0;
    }

    Puts(fsr_msginfo_col);
    GotoLocFrom();
    if (GetItemString(msg->from, 29))
        return -1;

    if (strpbrk(msg->from, "@!") == NULL || strchr(msg->from, ' '))
        fancier_str(msg->from);

    DisplayShowName(rbox_sho_fname, msg->from);

    return 0;
}

int near GetFromAddr(PMAH pmah, XMSG *msg)
{
    char tempaddr[30];
    NETADDR *o;

    if (!(pmah->ma.attribs & MA_ANON) && !mailflag(CFLAGM_ATTRANY))
    {
        if (inc)
            item++;
        else
            item--;

        return 0;
    }

    o = &msg->orig;

    GotoAddrFrom();
    Puts(fsr_addr_col);
    Puts(CLEOL);

    strcpy(tempaddr, Address(o));

    if (GetItemString(tempaddr, 24))
        return -1;

    if (*tempaddr == '\0')
        strcpy(tempaddr, Address(&prm.address[0]));

    MaxParseNN(tempaddr, o);
    DisplayShowAddress(rbox_sho_faddr, o, pmah);
    return 0;
}

int near GetToField(PMAH pmah, XMSG *msg)
{
    int ret = 0;
    char first_name[PATHLEN];
    char last_name[PATHLEN];
    NETADDR *d;

    d = &msg->dest;

    if (usr.help != EXPERT && !(prm.flags & FLAG_no_ulist) &&
        (pmah->ma.attribs & (MA_NET | MA_SHARED)) == 0)
    {
        GotoLocText();
        Puts(gmsg_l2p5);
    }

    Puts(fsr_msginfo_col);

    strcpy(first_name, msg->to);

    GotoLocTo();
    if (GetItemString(msg->to, 29))
    {
        ret = -1;
        goto DoRet;
    }


        if (!eqstri(last_name, msg->to))
            DisplayShowName(rbox_sho_tname, msg->to);
    }

    if (eqstri(msg->to, sysop_txt) && (pmah->ma.attribs & MA_NET) == 0)
    {
        strcpy(msg->to, PRM(sysop));
        DisplayShowName(rbox_sho_tname, msg->to);
    }
    else
    {

        if (eqstr(msg->to, qmark))
        {
            char temp[PATHLEN];


            sprintf(temp, "%suserlist", PRM(misc_path));
            if (Display_File(DISPLAY_NONE, NULL, temp) != 0 && !(prm.flags & FLAG_no_ulist))
            {


                Puts(CLS);


                if (UserList() != -1)
                {
                    Puts(WHITE);
                    Press_ENTER();
                }
            }

            *msg->to = '\0';

            RedrawAll(pmah, msg, FALSE);
            item = ITEM_TO;
            ret = 0;
            goto DoRet;
        }


    return ret;
}

static void near DisplayShowDest(NETADDR *d)
{
    NFIND *nf;

    if (!*netnode)
        return;

    if ((nf = NodeFindOpen(d)) != NULL)
    {
        Printf(fsr_dest, nf->found.name, nf->found.city);
        NodeFindClose(nf);
    }
    else
    {
        Puts(fsr_unlisted_node);
    }
}

int near GetSubject(PMAH pmah, XMSG *msg)
{
    NW(pmah);

    if ((pmah->ma.attribs & (MA_NET | MA_ATTACH)) == (MA_NET | MA_ATTACH) &&
        (msg->attr & MSGFILE) && AllowAttribute(pmah, MSGKEY_LATTACH))
    {
        if (inc)
            item++;
        else
            item--;
        return 0;
    }

    Puts(fsr_msginfo_col);

    GotoLocSubj();
    if (GetItemString(msg->subj, sizeof(msg->subj) - 2))
        return -1;

    DisplayMessageSubj(msg, pmah);
    return 0;
}

int near GetItemString(char *str, int max)
{
    switch (mdm_getspnc(str, max))
    {
    case -1:
        item = -1;
        return TRUE;

    case MSGENTER_UP:
        item--;
        inc = FALSE;
        break;

    case MSGENTER_DOWN:
        item++;
        inc = TRUE;
    }

    return FALSE;
}

static void near RedrawAll(PMAH pmah, XMSG *msg, int showhelp)
{
    Puts(enter_msg_init);
    DrawReaderScreen(pmah, FALSE);

    if (showhelp && (usr.help != EXPERT) && prm.hlp_hdrentry)
    {
        Puts(GRAY "\n");
        Display_File(DISPLAY_NONE, NULL, PRM(hlp_hdrentry));
    }

    DisplayMessageNumber(msg, this_msgnum, high_msg);
    DisplayMessageAttributes(msg, pmah);

    DisplayShowName(rbox_sho_fname, msg->from);
    DisplayShowDate(rbox_sho_fdate, (union stamp_combo *)&msg->date_written);

    if (*msg->from && (pmah->ma.attribs & MA_NET))
        DisplayShowAddress(rbox_sho_faddr, &msg->orig, pmah);

    DisplayShowName(rbox_sho_tname, msg->to);
    DisplayShowDate(rbox_sho_tdate, (union stamp_combo *)&msg->date_arrived);

    if (*netnode && (pmah->ma.attribs & MA_NET))
        DisplayShowAddress(rbox_sho_taddr, &msg->dest, pmah);

    DisplayMessageSubj(msg, pmah);
}
