// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_outr.c,v 1.3 2003/06/06 01:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS

#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(OS_2) && !defined(NT)
static int timer2 = FALSE;
static int set = TRUE;
#endif

extern int last_cc;
extern char strng[];

static int rip_wrap = 1;

#if defined(OS_2) || defined(NT) || defined(UNIX)

static void near CMDM_PPUTcw(int c)
{
    if (local)
        return;

    ComPutc(hcModem, c);
}

static void near CMDM_PPUTs(char *s)
{
    if (local)
        return;
    else
    {
#if (COMMAPI_VER > 1)
        extern HCOMM hcModem;
        BOOL lastState = ComBurstMode(hcModem, TRUE);

        ComWrite(hcModem, s, strlen(s));
        ComBurstMode(hcModem, lastState);
#else
        while (*s)
            ComPutc(hcModem, *s++);
#endif
    }
}
#define CMDM_PPUTc(c) CMDM_PPUTcw(c)


    if (set)
    {
        timer2 = FALSE;
        input_timeout = timerset(timeout_tics);
        set = FALSE;
    }


    y = shut_up;
    shut_up = TRUE;

    Check_Time_Limit(&input_timeout, &timer2);
    Mdm_check();

    shut_up = y;

    if (baud < 38400L)
        Delay((unsigned int)((38400L - baud) / 1920L));

    fFlow = FALSE;
}

static void near CMDM_PPUTcw(int c)
{
    if (local)
        return;

    set = TRUE;

    while (out_full())
        CMDM_wait();

    while (mdm_pputc(c) != 0x01)
        CMDM_wait();

#ifdef DEBUG_OUT
    if (dout_log)
        DebOutSentChar(c);
#endif
}

static void near CMDM_PPUTs(char *s)
{
    if (local)
        return;

    while (*s)
        CMDM_PPUTcw(*s++);
}

                if (ch == 10)
                {
                    rip_state = 0;
                    rip_state = 1;
                else
                    rip_state = -1;
                break;

            case 1:
                rip_state = 0;
                if (ch == '!')
                if (b36 < 10 && isalnum(ch))
                {
                    str3[b36++] = ch;
                    break;
                }
                str3[b36] = '\0';
                if (b36args(str3, args, 2, 2, 2, 2, 1, 1, 0) == 6)
                {
                    if (RipOriginX() != args[0] || RipOriginY() != args[1] ||
                        TermWidth() != args[2] || TermLength() != args[3])
                        display_line = display_col = current_line = current_col = 1;
                    SetRipOrigin(args[0], args[1]);
                    SetTermSize(args[2] - args[0], args[3] - args[1]);
                    rip_wrap = args[4] ? TRUE : FALSE;
                    SetRipFont(args[5]);
                }
                rip_state = 2;
                if (ch == 10)
                    rip_state = 4;
                else if (ch == 13)
                    rip_state = 3;
                rip_state = 2;
                switch (ch)
                {
                case 'w':
                    rip_state = 6;
                    b36 = 0;
                    break;

                case '*':
                    RipReset();
                    mdm_attr = -1;
                    rip_state = 2;

                current_col = 1;
                display_col = 1;
            }
            break;

            {
                current_line++;
                display_line++;
            }

            current_col = display_col = 1;
            wrap = FALSE;

            if (current_line > TermLength())

            if (timeleft() <= 0 && do_timecheck)
                TimeLimit();

            if (!local && !carrier())
                Lost_Carrier();

            if (loc_kbhit() && !keyboard && !local)
                Parse_Local(loc_getch());
            break;

        case 12:
            if (usr.bits2 & BITS2_CLS)
            {
                if (usr.video)
                    display_line = display_col = current_line = current_col = 1;

                if (usr.video == GRAPH_ANSI)
                    CMDM_PPUTs(ansi_cls);
                else
                    CMDM_PPUTcw('\x0c');

                    CMDM_PPUTs("\r");
                    rip_state = 0;
                }

                mdm_attr = DEFAULT_ATTR;
            }
            else
                CMDM_PPUTs("\r\n");
            break;

        case 13:
            wrap = FALSE;
            CMDM_PPUTcw('\r');
            current_col = display_col = 1;
            break;

        case 25:
            if (usr.video == GRAPH_AVATAR)
                CMDM_PPUTcw('\x19');

            state = 25;
            break;

        case '\x08':
            display_col--;
            current_col--;
            goto OutP;

        case 22:
            if (usr.video == GRAPH_AVATAR)
                CMDM_PPUTcw('\x16');

            state = 0;
            break;

        default:
            if (rip_state == -1 || rip_state < 2)
            {
                display_col++;

                if (++current_col > TermWidth())
                {
                    if (hasRIP() && !rip_wrap)
                    {
                        display_col--;
                        current_col--;
                    }
                    else
                    {
                        wrap = TRUE;
                        current_line++;
                        display_line++;

                        if (current_line > TermLength())
                state = 1;
                break;

            case 2:
                mdm_attr |= 0x80;

                if (usr.video == GRAPH_ANSI)
                    CMDM_PPUTs(ansi_blink);

                state = -1;
                break;

            case 3:
                current_line--;
                display_line--;

                if (usr.video == GRAPH_ANSI)
                    CMDM_PPUTs(ansi_up);

                state = -1;
                break;

            case 4:
                current_line++;
                display_line++;

                if (usr.video == GRAPH_ANSI)
                    CMDM_PPUTs(ansi_down);

                state = -1;
                break;

            case 5:
                current_col--;
                display_col--;

                if (usr.video == GRAPH_ANSI)
                    CMDM_PPUTs(ansi_left);

                state = -1;
                break;

            case 6:
                current_col++;
                display_col++;

                if (usr.video == GRAPH_ANSI)
                    CMDM_PPUTs(ansi_right);
                else if (!usr.video)
                    CMDM_PPUTcw(' ');

                state = -1;
                break;

            case 7:
                if (usr.video == GRAPH_ANSI)
                    CMDM_PPUTs(ansi_cleol);

                state = -1;
                break;

                break;

                state = 15;
                break;

                if (usr.video)
                {
                    int wasline = current_line;
                    int wascol = current_col;

                    byte seq[10];

                state = 30;
                break;

            default:
                state = -1;
            }
            break;

        case 1:

                if (ch & 0x80u && usr.video == GRAPH_AVATAR)
                    CMDM_PPUTs("\x16\x02");

                state = -1;
            }
            else
                state = 2;
            break;

            if (usr.video == GRAPH_AVATAR)
                CMDM_PPUTcw(ch);

            save_cx = (unsigned char)ch;
            state = 10;
            break;

            if (usr.video == GRAPH_AVATAR)
                CMDM_PPUTcw(ch);

            save_cx = (unsigned char)ch;
            state = 13;
            break;

            if (usr.video == GRAPH_AVATAR)
            {
                CMDM_PPUTcw(ch);
                state = -1;
            }
            else if (usr.video)
            {
                y = current_line;
                z = current_col;
                a = save_cx;
                state = -1;

                Mdm_printf(attr_string, a);

                for (x = 0; x < s2; x++)
                    Mdm_printf(clear_string, y + x, z, (char)ch + 1);

                Mdm_printf(goto_str, y, z);
            }
            break;

            if (usr.video == GRAPH_AVATAR)
                CMDM_PPUTcw(ch);

            s2 = ch;
            state = 17;
            break;

            if (usr.video == GRAPH_AVATAR)
            {
                CMDM_PPUTcw(ch);
                state = -1;
            }
            else if (usr.video)
            {
                y = current_line;
                z = current_col;
                a = save_cx;
                state = -1;

                Mdm_printf(attr_string, a);

                for (x = 0; x < s3; x++)
                    Mdm_printf(fill_string, y + x, z, s2, ch + 1);

                Mdm_printf(goto_str, y, z);
            }
            break;

            if (usr.video == GRAPH_AVATAR)
                CMDM_PPUTcw(ch);
            else
            {
                word x;
                byte c;

                c = (usr.bits2 & BITS2_IBMCHARS) ? (byte)save_cx : nohibit[(byte)save_cx];

                uch = (unsigned char)ch;

                for (x = 0; x < uch; x++)
                    CMDM_PPUTcw(c);
            }


void ResetAttr(void)
{
    byte last_attr = mdm_attr;

    mdm_attr = -1;

    if (last_attr != (byte)-1)
        Printf(attr_string, last_attr);
}
