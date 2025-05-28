// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_locl.c,v 1.2 2003/06/04 23:37:33 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_log
#define MAX_INCL_COMMS

#include "keys.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef ORACLE

static void near Fake_Noise(void);
static int near Priv_Adjust_Start(void);
static int near Parse_Local_Normal(int ch);
static int near Parse_Priv_Adjust(int ch);
static void near Local_Stats_Display(void);

VWIN *privwin = NULL;
static VPICK *vp;
PLIST *pl_privs = NULL;

int SetLocalKeystate(int setto)
{
    int wasstate = keyboard;
    keyboard = (setto || local) ? 1 : 0;
    return wasstate;
}

int LocalKeystate(void) { return keyboard; }


        if (ch >= '1' && ch <= '8')
            newkeys ^= (1L << (ch - '1'));
        else if (ch >= 'A' && ch <= 'X')
            newkeys ^= (1L << (ch - 'A' + 8));
        else
        {
#ifdef TTYVIDEO
            if (displaymode == VIDEO_IBM)
#endif
                WinPickAction(vp, ch);
#ifdef TTYVIDEO
            else
                Lputs(type_keys_to_toggle);
#endif
        }

        ShowWinKeys();

#ifdef TTYVIDEO
        if (displaymode == VIDEO_IBM)
#endif
            WinSync(privwin, FALSE);
        break;
    }

    return 1;
}

static int near Parse_Local_Normal(int ch)
{
    int c;
    char ptmp[16];

    switch (toupper(ch))
    {
    case K_ONEMORE:
        c = loc_getch();

#ifdef UNIX
        if (c == K_ESC)
            goto realEscape;


                if (inmagnet)
                    Fix_MagnEt();

                input_timeout = timerset(timeout_tics);
                break;

            case K_ALTJ:
                Shell_To_Dos();
                break;

            case K_ALTD:
                Fake_Noise();
                break;

            case K_ALTN:
                usr.bits ^= BITS_NERD;
                LocalMsg(nerd_toggled, (usr.bits & BITS_NERD) ? sys_on : sys_off);
                if (usr.bits & BITS_NERD)
                    ci_nerd();
                break;

            case K_UP:
            case K_PGUP:
                timeoff += (c == K_UP) ? 60 : 300;
                sent_time_almostup = FALSE;
                sent_time_5left = FALSE;
                LocalMsg(min_add, c == K_UP ? 1 : 5, c == K_UP ? blank_str : "s", timeleft());
                break;

            case K_DOWN:
            case K_PGDN:
                timeoff -= (c == K_DOWN) ? 60 : 300;
                sent_time_almostup = FALSE;
                sent_time_5left = FALSE;
                LocalMsg(min_less, c == K_DOWN ? 1 : 5, c == K_DOWN ? blank_str : "s", timeleft());
                break;
            }
        break;

    case K_CTRLC:
        brk_trapped++;
        break;

    case K_CTRLX:
        logit(log_axe);
        ci_ejectuser();
        mdm_dump(DUMP_ALL);
        mdm_hangup();
        break;

#ifndef UNIX
    case K_ESC:
#else
    case -2:
    realEscape:
#endif
        if (displaymode == VIDEO_IBM && dspwin)
        {
            WinClose(dspwin);
            dspwin = NULL;
            dspwin_time = 0L;
        }
        break;

    case 'A':
        LocalMsg(key_on);
        if (!snoop)
        {
            snoop = TRUE;
            Lputs(CLS);
        }

        keyboard = TRUE;
        break;

        return (Priv_Adjust_Start());


    if (string[x = strlen(string) - 1] == '\n')
    {
        string[x] = '\0';
        strcat(string, "\r\n");
    }

    WinPutsA(dspwin, string);

    free(string);
    return 0;
}

static void near Local_Stats_Display(void)
{
#ifdef __TURBOC__
    int _stdc (*prfunc)(char *format, ...);
#else
    int(_stdc * prfunc)(char *format, ...);
#endif
    char *temp, ptmp[8];

    if ((temp = malloc(80)) == NULL)
        return;


        WinPutsA(dspwin, "\x16\x6f");
        WinPutcA(dspwin, (byte)((col.pop_text >> 4) & 0x07));
    }

    sprintf(temp, "%s%s%s", privstr(usr.priv, ptmp), usr.xkeys ? "/" : blank_str, Keys(usr.xkeys));

#ifdef TTYVIDEO
    if (displaymode != VIDEO_IBM)
        (*prfunc)(stat_0);
#endif

    (*prfunc)(stat_1, usr.name, usr.alias, baud);
    (*prfunc)(stat_2, temp, usr.phone, usr.dob_year, usr.dob_month, usr.dob_day);
    (*prfunc)(stat_3, (displaymode == VIDEO_IBM) ? col.pop_text : curattr,
              sc_time(&usr.ludate, temp), usr.city, chatreq ? ch_req : blank_str);
    (*prfunc)(stat_0);
    (*prfunc)(stat_4, TermWidth(), TermLength(), timeonline(), timeleft());
    (*prfunc)(stat_5, usr.msg);
    (*prfunc)(stat_6, usr.files, usr.times, usr.time);

    (*prfunc)(stat_7, Help_Level(usr.help), Sysop_Yes_or_No(usr.bits & BITS_TABS), usr.nulls,
              Sysop_Yes_or_No(usr.bits2 & BITS2_IBMCHARS));

    (*prfunc)(stat_8, Graphics_Mode(usr.video), Sysop_Yes_or_No((usr.bits2 & BITS2_BORED) == 0),
              Sysop_Yes_or_No(usr.bits2 & BITS2_MORE), Sysop_Yes_or_No(usr.bits2 & BITS2_CLS));

    (*prfunc)(stat_9, usr.downtoday, usr.down, usr.up, Sysop_Yes_or_No(usr.bits & BITS_HOTKEYS));

    if (usr.xp_flag & XFLAG_EXPDATE)
        FileDateFormat(&usr.xp_date, temp);
    else if (usr.xp_flag & XFLAG_EXPMINS)
        sprintf(temp, stat_mins, usr.xp_mins);
    else
        strcpy(temp, proto_none);

    (*prfunc)(stat_10, usr.credit, usr.debit,
              (usr.xp_flag & XFLAG_AXE) ? stat_hangup
                                        : ((usr.xp_flag & XFLAG_DEMOTE) ? stat_demote : proto_none),
              temp);

    (*prfunc)(stat_11, Sysop_Yes_or_No(usr.bits & BITS_RIP));

    (*prfunc)(stat_0);
    (*prfunc)(stat_12);
    (*prfunc)(stat_13);
    (*prfunc)(stat_14);
    (*prfunc)(stat_15);
    (*prfunc)(stat_16);

    (*prfunc)(CLEOL);

#ifdef TTYVIDEO
    if (displaymode == VIDEO_IBM)
#endif
        WinSync(dspwin, FALSE);
#ifdef TTYVIDEO
    else
        Lprintf("\n");
#endif

    dspwin_time = timerset(DSPWIN_TIME * 100);

    free(out);
    return;
}

void Priv_Down(void)
{
    int ucls = ClassLevelIndex(usr.priv);
    word clevel = (word)ClassGetInfo(ucls, CIT_LEVEL);
    else if (ucls-- > 0)
        usr.priv = (word)ClassGetInfo(ucls, CIT_LEVEL);
}

void Parse_FKey(int c)
{
    int l;
    char fkfile[PATHLEN];

    l = sprintf(
        fkfile, "%s%sF%d", PRM(misc_path),
        (c >= 59 && c <= 68)
            ? blank_str
            : ((c >= 84 && c <= 93)
                   ? "S"
                   : ((c >= 94 && c <= 103) ? "C" : ((c >= 104 && c <= 113) ? "A" : blank_str))),
        (c >= 59 && c <= 68)
            ? c - 58
            : ((c >= 84 && c <= 93)
                   ? c - 83
                   : ((c >= 94 && c <= 103) ? c - 93 : ((c >= 104 && c <= 113) ? c - 103 : 1))));

    strcpy(fkfile + l, ".vm");
    if (fexist(fkfile))
    {
        fkfile[l] = '\0';
        display_line = display_col = 1;
        Mex(fkfile);
    }
    else
    {
        strcpy(fkfile + l, ".?bs");
        if (fexist(fkfile))
        {
            fkfile[l] = '\0';
            display_line = display_col = 1;
            Display_File(0, NULL, percent_s, fkfile);
        }
        else
            l = 0;
    }

    if (l)
    {
        if (inmagnet && !inchat)
            Fix_MagnEt();

        vbuf_flush();

        input_timeout = timerset(timeout_tics);
    }
}

static void near Fake_Noise(void)
{
    char string[50];
    int x, y, len;

    ci_ejectuser();

    if (mdm_attr > 15)
        Puts(GRAY);

