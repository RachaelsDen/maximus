// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_bor.c,v 1.1.1.1 2002/10/01 17:51:28 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_bor

#include "alc.h"
#include "m_reply.h"
#include "max_edit.h"
#include "max_msg.h"
#include "maxedp.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int linenum;
static struct _replyp *preply;

static void near Bored_GetLine(int max);
static void near Bored_Continue(void);

int Bored_Menu(XMSG *msg)
{
    return Display_Options(*PRM(edit_menu) ? PRM(edit_menu) : "EDIT", msg);
}

int Bored(XMSG *msg, HMSG msgh, struct _replyp *pr)
{
    long tlong;

    preply = pr;
    linenum = 1;
    num_lines = 0;
    usrwidth = (byte)min(TermWidth(), LINELEN);

    tlong = (coreleft() - BORED_SAVE_MEM) / (LINELEN * 2L);

    max_lines = (int)min(tlong, (long)MAX_LINES);

    {
}

static void near Bored_GetLine(int max)
{
    char string[LINELEN + 1];
    char nextstring[MAX_WRAPLEN + 2];
    char temp[LINELEN];

    int linecount;
    int wrapped;

    *nextstring = '\0';
    *string = '\0';

    linecount = 0;

    Clear_KBuffer();

    Printf(LGREEN "   Ú\x19Ä%c¿\n", usrwidth - 7);

    while (max == 0 || linecount < max)
    {
        if (num_lines == max_lines - 2)
            Puts(last_line);

        if (num_lines >= max_lines - 1)
        {
            Puts(toomanylines);
            return;
        }

        strcpy(string, nextstring);

        sprintf(temp, GRAY "%2d: " YELLOW, linenum);

        wrapped = FALSE;

        if (Input(string, INPUT_NLB_LINE | INPUT_WORDWRAP, 0, min(usrwidth - 3, LINELEN) - 4,
                  temp) == 1)
        {
            wrapped = TRUE;
            strcpy(nextstring, string + strlen(string) + 1);
        }
        else
            *nextstring = '\0';

        if (!*string)
            break;
        else
        {
            if (Allocate_Line(linenum))
                EdMemOvfl();

            if (wrapped)
                screen[linenum][0] = SOFT_CR;

            strcpy(screen[linenum] + 1, string);
            *string = '\0';

            linecount++;
            linenum++;
        }
    }
}

static void near Bored_List(XMSG *msg)
{
    word x;
    char nonstop;

    display_line = display_col = 1;
    nonstop = FALSE;

    Puts("\n\n" CLS);

    Printf(list_from, Strip_Ansi(msg->from, NULL, 0L));
    Printf(list_to, Strip_Ansi(msg->to, NULL, 0L));
    Printf(list_subj, Strip_Ansi(msg->subj, NULL, 0L));

    for (x = 1; x <= num_lines; x++)
    {
        if (MoreYnBreak(&nonstop, CYAN))
            break;

        Printf(blfmt1, x, screen[x] + 1);
        Putc('\n');
    }

    Putc('\n');
}

static void near Bored_To(XMSG *msg)
{
    Printf(bed_to, Strip_Ansi(msg->to, NULL, 0L));

    if (!(prm.flags & FLAG_no_ulist) && !(mah.ma.attribs & MA_NET))
        Puts(bed_lu);

    for (;;)
    {
        Puts(CYAN);
        InputGetsL(msg->to, XMSG_TO_SIZE - 1, bto);

        if (eqstr(msg->to, qmark) && (prm.flags & FLAG_no_ulist) == 0)
            UserList();
        else if (eqstri(msg->to, sysop_txt) && (mah.ma.attribs & MA_NET) == 0)
        {
            strcpy(msg->to, PRM(sysop));
            break;
        }
        else if (*msg->to)
        {
            if ((mah.ma.attribs & (MA_NET | MA_SHARED)) == 0 && (msg->attr & MSGPRIVATE) &&
                !IsInUserList(msg->to, TRUE))
            {
                Puts(userdoesntexist);
            }
            else
                break;
        }
    }

    Clear_KBuffer();
}

static void near Bored_From(XMSG *msg)
{
    Printf(bfrom, Strip_Ansi(msg->from, NULL, 0L));

    do
    {
        Puts(CYAN);
        InputGetsL(msg->from, XMSG_FROM_SIZE - 1, bfromsp);
    } while (*msg->from == '\0');

    Clear_KBuffer();
}

static void near Bored_Subject(XMSG *msg)
{
    Printf(bsubj, Strip_Ansi(msg->subj, NULL, 0));

    if ((mah.ma.attribs & (MA_NET | MA_ATTACH)) == (MA_NET | MA_ATTACH) &&
        !mailflag(CFLAGM_ATTRANY))
    {
        Puts(cant_change_field);
        Press_ENTER();
        return;
    }

    do
    {
        Puts(CYAN);
        InputGetsL(msg->subj, XMSG_SUBJ_SIZE - 1, bsubject);
    } while (*msg->subj == '\0');

    Clear_KBuffer();
}

static void near Bored_Handling(XMSG *msg)
{
    word x;
    byte ch;

    if (inmagnet)
        Puts(CLS);

    do
    {
        if (!*linebuf)
        {
            Puts("\n" CLS);

            for (x = 0; x < 16; x++)
            {
                Printf(YELLOW "%c" GRAY ")%s", s_ret(n_msg_attr0 + x)[0],
                       &(s_ret(n_msg_attr0 + x)[1]));

                Printf(rle_str, '.', 20 - (strlen(s_ret(n_msg_attr0 + x)) + 1));

                Printf(WHITE " %s\n", (msg->attr & (1 << x)) ? yep : nope);
            }

            Puts(edlist_quit);
        }

        ch = (byte)toupper(KeyGetRNP(select_p));

        for (x = 0; x < 16; x++)
            if (ch == (s_ret(n_msg_attr0 + x))[0])
            {
                if (msg->attr & (1 << x))
                    msg->attr &= ~(1 << x);
                else
                {

                    if ((1 << x) == MSGFILE && (msg->attr & MSGFILE) == 0 &&
                        (mah.ma.attribs & (MA_NET | MA_ATTACH)) == (MA_NET | MA_ATTACH) &&
                        !mailflag(CFLAGM_ATTRANY))
                    {
                        *msg->subj = 0;
                    }

                    msg->attr |= (1 << x);
                }

                break;
            }
    } while (ch != 'Q' && ch != '\0' && ch != '|' && ch != '\r');
}

static void near Bored_Delete(void)
{
    char temp[BUFLEN];
    word from, to, ln, move;
    word old_num_lines;

    WhiteN();

    InputGets(temp, line_del_from);

    from = atoi(temp);

    if (*temp == '\0' || from == 0 || from > num_lines)
        return;

    InputGets(temp, line_del_to);

    to = atoi(temp);

    if (*temp == '\0' || to == 0 || to > num_lines || to < from)
        return;

    old_num_lines = num_lines;

    for (ln = from; ln <= to; ln++)
        Free_Line(ln);


    memset(screen + num_lines + 1, '\0', (old_num_lines - num_lines) * sizeof(char *));
}

static void near Bored_Insert(void)
{
    char temp[BUFLEN];
    word cx, x;

    WhiteN();

    InputGets(temp, ins_bef);

    cx = atoi(temp);

    if (!(cx > 0 && cx <= num_lines && num_lines < max_lines - 1))
    {
        Puts(toomanylines);
        return;
    }

    if (Allocate_Line(num_lines + 1))
        EdMemOvfl();

    for (x = num_lines - 1; x >= cx; x--)
    {
        screen[x + 1][0] = screen[x][0];
        strocpy(screen[x + 1] + 1, screen[x] + 1);
    }

    screen[cx][0] = '\r';
    screen[cx][1] = '\0';

    if (!*linebuf)
        Puts(line_ins);


            if ((p = stristr(screen[cx] + 1, search)) != NULL)
            {
                if (strlen(replace) >= strlen(search))
                {
                    if (strlen(replace) != strlen(search))
                        strocpy(p + (strlen(replace) - strlen(search)), p);

                    memmove(p, replace, strlen(replace));
                }
                else
                {
                    memmove(p, replace, strlen(replace));

                    memmove(p + strlen(replace), p + strlen(search), strlen(p + strlen(replace)));
                }
            }

            Putc('\n');
            Printf(blfmt1, cx, screen[cx] + 1);
            Putc('\n');
        }
    }
}

struct _hinfo
{
    char nonstop;
    char display_msg;
    word total_lines;
    word startline;
    word endline;
    byte *initials;
    word lc;
};


        imsgh = msgh;
    else
        imsgh = MsgOpenMsg(sq, MOPEN_READ, lmsg);

    if (!imsgh)
        return FALSE;

    MsgReadMsg(imsgh, &imsg, 0L, 0L, NULL, 0L, NULL);
    Parse_Initials(imsg.from, initials);

    if ((out = shfopen(name, fopen_write, O_WRONLY | O_CREAT | O_TRUNC | O_NOINHERIT)) == NULL)
    {
        if (!msgh)
            MsgCloseMsg(imsgh);

        return FALSE;
    }

    MsgBodyToFile(imsgh, out, msgh == NULL, msgh != NULL, initials, flag);

    fclose(out);


    if (pr)
        MessageToFile(pr->fromsq, MsgUidToMsgn(pr->fromsq, pr->original, UID_EXACT), msgh, msgtemp,
                      MRL_QEXP);
    else if (msgh)
        MessageToFile(sq, last_msg, msgh, msgtemp, 0);


    FileDate(msgtemp, &d1);

    erlv =
        Outside(NULL, NULL, OUTSIDE_RUN | OUTSIDE_STAY, temp, FALSE, CTL_NONE, RESTART_MENU, NULL);


    FileDate(msgtemp, &d2);

    if ((d1.ldate == d2.ldate && pr != NULL) || erlv)
    {
        unlink(msgtemp);
        return ABORT;
    }

