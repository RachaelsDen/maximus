// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_gets.c,v 1.3 2003/06/06 01:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS

#include "keys.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <mem.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef EMSI
#include "emsi.h"
#endif

static char *str;
static int num_ch;
static int cur_pos;

#ifdef TEST_VER
void Zoquo(void);
#else
#define Zoquo()
#endif

static void near Mdmgets_Home(void)
{
    if (cur_pos)
    {
        Printf(left_x, cur_pos);
        cur_pos = 0;
    }
}

static void near Mdmgets_End(int type, int c)
{
    char temp[PATHLEN];
    if (str[cur_pos])
    {
        Puts(Show_Pwd(str + cur_pos, temp, (char)((type & INPUT_ECHO) ? c : 0)));
        cur_pos += strlen(str + cur_pos);
    }
}

static void near Mdmgets_Cleft(void)
{
    int orig_pos;

    if (cur_pos)
    {
        orig_pos = cur_pos;

        cur_pos--;

        while (cur_pos && !isalnum(str[cur_pos]))
            cur_pos--;

        while (cur_pos && isalnum(str[cur_pos]))
            cur_pos--;

        if (!isalnum(str[cur_pos]))
            cur_pos++;

        if (orig_pos - cur_pos)
            Printf("\x16\x19\x02" LEFT "%c", orig_pos - cur_pos);
    }
}

static void near Mdmgets_Cright(void)
{
    int orig_pos;

    if (cur_pos < num_ch)
    {
        orig_pos = cur_pos;

        while (cur_pos < num_ch && isalnum(str[cur_pos]))
            cur_pos++;

        while (cur_pos < num_ch && !isalnum(str[cur_pos]))
            cur_pos++;

        if (cur_pos - orig_pos)
            Printf("\x16\x19\x02" RIGHT "%c", cur_pos - orig_pos);
    }
}

static void near Mdmgets_Left(void)
{
    if (cur_pos)
    {
        Puts(LEFT);
        cur_pos--;
    }
}

static void near Mdmgets_Right(int type, int c)
{
    if (str[cur_pos])
    {
        if (type & INPUT_ECHO)
            Putc(c);
        else
            Putc(str[cur_pos]);

        cur_pos++;
    }
}

static void near Rewrite_Line(int type, int c)
{
    char temp[PATHLEN];
    byte last_col;

    }
}

static void near Mdmgets_Bs(int type, int c)
{
    if (!cur_pos)
        return;

    strocpy(str + cur_pos - 1, str + cur_pos);

    Puts(bs_sp_bs);
    num_ch--;
    cur_pos--;


        if (cur_pos)
            Printf("\x19\x08%c", cur_pos);

        if ((type & INPUT_NOCLEOL) == 0)
            Puts(CLEOL);
        else
            Printf("\x19 %c\x19\x08%c", num_ch, num_ch);

        str[num_ch = cur_pos = 0] = '\0';
    }
}

int DoEditKey(int type, char *str, int key, int c)
{
    if (type & INPUT_SCAN)
        return key << 8;

    if (!usr.video)
        return FALSE;

    switch (key)
    {
    case K_HOME:
        if (str)
            Mdmgets_Home();
        break;

    case K_END:
        if (str)
            Mdmgets_End(type, c);
        break;

    case K_DEL:
        if (str)
            Mdmgets_Del(type, c);
        break;

    case K_LEFT:
        if (str)
            Mdmgets_Left();
        break;

    case K_RIGHT:
        if (str)
            Mdmgets_Right(type, c);
        break;

        if (type & INPUT_MSGENTER)
            return MSGENTER_UP;
        break;


int mdm_gets(char *string, int type, int c, int max, char *prompt)
{
    char temp[PATHLEN];
    char *msgprompt;
    int timer2, rc;
    byte ch = 0;

    str = string;
    num_ch = 0;

#ifdef EMSI
    EmsiCheck(0);
#endif

    if (max <= 0)
        max = BUFLEN;

    if (type & (INPUT_MSGENTER | INPUT_WORDWRAP | INPUT_DEFAULT))
    {
        if (!(type & INPUT_NOECHO))
        {
            if ((type & INPUT_NOCLEOL) == 0)
                Puts(CLEOL);

            Puts(string);
        }

        num_ch = strlen(string);
    }


        timer2 = FALSE;
        input_timeout = timerset(timeout_tics);

        string[num_ch] = '\0';
        msgprompt = prompt ? prompt : blank_str;

        while (!Mdm_keyp())
        {
            if (halt())
            {
                if (prompt && !(type & (INPUT_NOCTRLC | INPUT_NOECHO)))
                {
                    mdm_dump(DUMP_ALL);
                    ResetAttr();

                    num_ch = cur_pos = 0;

                    Putc('\n');
                    Puts(prompt);

                    vbuf_flush();
                    string[num_ch] = '\0';
                }
            }

            Check_Time_Limit(&input_timeout, &timer2);
            Check_For_Message(msgprompt, string);
            Giveaway_Slice();
        }

        ch = (unsigned char)Mdm_getcw();
#warning Potential security problem? Can remote send local scan code?

#ifdef EMSI

        if (EmsiCheck(ch))
        {
            string[num_ch = 0] = '\0';
            ch = 1;
        }
#endif

        timer2 = FALSE;

        string[num_ch] = '\0';

        switch (ch)
        {
            if (Mdm_kpeek() == K_ESC)
            {
                ch = (unsigned char)Mdm_getcw();
                if (ch == K_ESC)
                    goto realEscape;
            }
#endif

#if defined(TEST_VER) && defined(OS_2)
            else if (loc_peek() == K_ALTB)
            {
                char far *null = 0L;

                loc_getch();
            {
                loc_getch();

                Shell_To_Dos();

                Printf("\n%s%s", prompt ? prompt : blank_str, string);
            }
            else if ((rc = DoEditKey(type, string, Mdm_getcw(), c)) != FALSE)
                return rc;
            break;

            if (usr.bits2 & BITS2_IBMCHARS)
            {
                DoEditKey(type, string, K_DEL, c);
                break;
            }
            if (!(type & INPUT_NOECHO))
                Mdmgets_Bs(type, c);
            break;

            if ((type & INPUT_MSGENTER) && usr.video)
                return MSGENTER_DOWN;
            else if (ch == K_CTRLX)
            {
                if (!(type & INPUT_NOECHO))
                {
                    Puts(bs_sn);

                    if (prompt)
                        Puts(prompt);
                }

                string[num_ch = cur_pos = 0] = '\0';
            }
            break;

        case K_CTRLY:
            if (!(type & INPUT_NOECHO))
                Mdmgets_Clear(type);
            break;

#endif
            if ((ch = Mdm_getcw()) == K_ESC)
            {
                if (type & INPUT_MSGENTER)
                    return -1;
            }
            else if (ch == '[' || ch == 'O')
            {
                ch = Mdm_getcw();

                rc = DoEditKey(type, string,
                               ch == 'A'   ? K_UP
                               : ch == 'B' ? K_DOWN
                               : ch == 'C' ? K_RIGHT
                               : ch == 'D' ? K_LEFT
                               : ch == 'H' ? K_HOME
                               : ch == 'K' ? K_END
                                           : 0,
                               c);

                if (rc != FALSE)
                    return rc;
            }
            break;


        case '+':
            if (!(type & INPUT_NOECHO))
                Puts(sp_bs);
                            {
                                if (!(type & INPUT_NOECHO))
                                    Putc(ch);
                            }
                            else
                            {

                                num_bs = num_ch - idx - 1;

                                if (num_bs && !(type & INPUT_NOECHO))
                                    Printf((usr.video == GRAPH_TTY || (type & INPUT_NOCLEOL))
                                               ? "\x19\x08%c\x19 %c"
                                               : "\x19\x08%c" CLEOL,
                                           num_bs, num_bs);
                            }

                            strocpy(string + idx + 2, string + idx + 1);
                            string[idx + 1] = '\0';
                            break;
                        }
                    }

                    if (!(type & INPUT_NOECHO))
                        Putc('\n');
                    vbuf_flush();
                    return 1;
                }
            }
            break;
        }

        vbuf_flush();
    }

    vbuf_flush();

    return *string;
}
