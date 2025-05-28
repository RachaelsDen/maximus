// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_log.c,v 1.1.1.1 2002/10/01 17:51:47 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_init
#define MAX_LANG_max_chat
#define MAX_LANG_max_main
#define MAX_INCL_COMMS

#include "alc.h"
#include "display.h"
#include "ffind.h"
#include "max_msg.h"
#include "md5.h"
#include "prog.h"
#include "trackm.h"
#include "ued.h"
#include "userapi.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <share.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#ifdef EMSI
#include "emsi.h"
#endif

static void near doublecheck_rip(void);
static void near doublecheck_ansi(void);
static void near Calc_Timeoff(void);
static void near Logo(char *key_info);
static void near Banner(void);
static int near GetName(void);
static int near Find_User(char *username);
static void near NewUser(char *username);
static void near Get_AnsiMagnEt(void);
static void near Check_For_User_On_Other_Node(void);
static void near Set_OnOffTime(void);
static void near Write_Active(void);
static int near InvalidPunctuation(char *string);
static int near checkterm(char *prompt, char *helpfile);

static char szBadUserName[] = "%sbad_user";

#define USR_BLOCK 9

void Login(char *key_info)
{
    signed int left;
    int newuser;

    Calc_Timeoff();

    if (!local && !waitforcaller)
        logit(log_caller_bps, baud);

    caller_online = TRUE;

    if (!local)
        mdm_baud(current_baud);

    Mdm_Flow_On();

    if (!local)
        Logo(key_info);


    InitTracker();
#endif


    if (usr.bits & BITS_NOTAVAIL)
        ChatSetStatus(FALSE, cs_notavail);
    else
        ChatSetStatus(TRUE, cs_avail);

    mdm_attr = curattr = -1;
    Puts(CYAN);


    if (!newuser && *ClassFile(cls))
        Display_File(0, NULL, ClassFile(cls));

    if (prm.flags & FLAG_lbaud96)
        usr.ludate = next_ludate;
#endif

    if (usr.time)
        Display_File(0, NULL, PRM(timewarn));
}

static void near Logo(char *key_info)
{
#ifndef KEY
    NW(key_info);
#endif

    mdm_dump(DUMP_INPUT);

    Putc('\n');

#ifdef EMSI
    EmsiTxFrame(EMSI_IRQ);
#endif

    Printf("%s v%s ", name, version);

#ifdef KEY
    Printf("\nSystem: %s\n"
           " SysOp: %s",
           key_info + strlen(key_info) + 1, key_info);
#endif
}

static void near Banner(void)
{
    if ((!*linebuf && !local) || eqstri(linebuf, "-"))
    {
        *linebuf = '\0';
        Display_File(0, NULL, PRM(logo));
    }
    else if (!*linebuf)
        strcpy(linebuf, PRM(sysop));
}

static int near GetName(void)
{

    fname = malloc(BUFLEN);
    lname = malloc(BUFLEN);
    username = malloc(BUFLEN * 3);
    pwd = malloc(BUFLEN);
    quest = malloc(PATHLEN);

    if (!(fname && lname && username && pwd && fname && quest))
    {
        logit(mem_none);
        quit(ERROR_CRITICAL);
    }

    for (;;)
    {
        found_it = FALSE;

        *fname = *lname = '\0';

        if (!*linebuf)
            Putc('\n');


    if (Mdm_keyp() != '*' && *what_first_name != '\n' &&
        !fAbort && !fEMSI && !fGotICI)
      EmsiTxFrame(EMSI_IRQ);
}
#endif
#endif

        sprintf(quest, what_first_name, (prm.flags & FLAG_alias) ? s_alias : blank_str);

        InputGetsWNH(fname, quest);

        if (!*fname)
        {
            if (local)
                quit(0);
            else
                continue;
        }

        if (!(((byte)toupper(*linebuf) == YES || (byte)toupper(*linebuf) == NO) &&
              (strpbrk(linebuf, cmd_delim) == linebuf + 1 || !linebuf[1])))
        {


            if (!*linebuf)
            {
                strncpy(username, fname, 35);
                username[35] = '\0';
                fancier_str(username);

                found_it = Find_User(username);
            }

            if (!found_it && (prm.flags2 & FLAG2_1NAME) == 0)
            {
                sprintf(quest, what_last_name, (prm.flags & FLAG_alias) ? s_alias : blank_str);

                InputGetsWNH(lname, quest);

            }
        }

        sprintf(username, "%s%s%s", fname, *lname ? " " : blank_str, lname);


            strcpy(usr.name, username);
            SetUserName(&usr, usrname);

            Display_File(0, NULL, PRM(notfound));
        }

        save = usr.help;
        usr.help = NOVICE;

        saveb = usr.bits;
        usr.bits &= ~BITS_HOTKEYS;

        if (!*linebuf)
            Putc('\n');

        if (GetYnAnswer(username, 0) == NO)
        {
            if (!local)
                logit(brain_lapse, username);

            Blank_User(&usr);
            continue;
        }

        usr.help = save;
        usr.bits = saveb;


            ci_init();

            if (InvalidPunctuation(username))
            {
                Clear_KBuffer();
                Puts(invalid_punct);
                continue;
            }

            logit(so_and_so_calling, username);
            logit(log_not_in_ulist, username);

            Bad_Word_Check(username);

            Clear_KBuffer();

            NewUser(username);

            ci_init();
        }
        else
        {

            ci_init();

            logit(so_and_so_calling, username);

            if (*usr.alias && !eqstri(usr.name, usr.alias))
            {


#ifdef CANENCRYPT
                if (*usr.pwd || (usr.bits & BITS_ENCRYPT))
#else
                if (*usr.pwd)
#endif
                {
                    if (!*linebuf)
                        Putc('\n');

                    InputGetseNH(pwd, '.', usr_pwd);
                }


        if ((usr.bits2 & BITS2_CONFIGURED) == 0)
        {
            if (prm.not_configured)
                Display_File(0, NULL, PRM(not_configured));

static void near doublecheck_ansi(void)
{
    if ((prm.flags2 & FLAG2_CHKANSI) && (usr.video == GRAPH_ANSI) && !autodetect_ansi() &&
        checkterm(check_ansi, "why_ansi"))
    {
        usr.video = GRAPH_TTY;
        usr.bits &= ~BITS_RIP;
        SetTermSize(0, 0);
    }
}


static void near doublecheck_rip(void)
{
    if ((prm.flags2 & FLAG2_CHKRIP) && (usr.bits & BITS_RIP) && !autodetect_rip() &&
        checkterm(check_rip, "why_rip"))
    {
        usr.bits &= ~BITS_RIP;
        SetTermSize(0, 0);
    }

    Set_Lang_Alternate(hasRIP());
}


    if ((huf = UserFileOpen(PRM(user_file), mode)) == NULL)
    {
        cant_open(PRM(user_file));
        Local_Beep(3);
        quit(ERROR_FILE);
    }

    if (!UserFileFind(huf, username, NULL, &usr) && !UserFileFind(huf, NULL, username, &usr))
    {
        ret = FALSE;
    }
    else
    {

        if (usr.delflag & UFLAG_DEL)
            ret = FALSE;
        else
        {

static void near NewUser(char *username)
{
    HUF huf;

    Blank_User(&usr);

    strcpy(usr.name, username);
    SetUserName(&usr, usrname);

    if (create_userbbs)
    {


        if ((huf = UserFileOpen(PRM(user_file), 0)) == NULL)
        {
            cant_open(PRM(user_file));
            quit(ERROR_FILE);
        }

        usr.lastread_ptr = Find_Next_Lastread(huf);

        UserFileClose(huf);
    }


    logit(log_applic);

    if (prm.logon_priv == PREREGISTERED && !create_userbbs)
    {
        if (*PRM(application))
            Display_File(0, NULL, PRM(application));
        else
            Puts(pvt_system);

        mdm_hangup();
    }

    if (*PRM(application))
        Display_File(0, NULL, PRM(application));

    Chg_City();

    if ((prm.flags & FLAG_ask_name) == 0)
        *usr.alias = '\0';
    else
    {
        Chg_Alias();

        Bad_Word_Check(usr.alias);
    }

    if (prm.flags & FLAG_ask_phone)
        Chg_Phone();
    else
        *usr.phone = '\0';


    if ((huf = UserFileOpen(PRM(user_file), 0)) == NULL)
    {
        cant_open(PRM(user_file));
        quit(ERROR_FILE);
    }


                    logit(log_rip_enabled_ndt);
                    doublecheck_rip();
                }
            }
        }

        if (usr.video != GRAPH_TTY)
        {
            sprintf(string, "%swhy_fsed", PRM(misc_path));

            NoWhiteN();

            if (GetYnhAnswer(string, get_fsed, 0) == YES)
            {
                usr.bits2 &= ~BITS2_BORED;
                usr.bits |= BITS_FSR;
            }
            else
            {
                usr.bits2 |= BITS2_BORED;
                if (!(usr.bits & BITS_RIP))
                    usr.bits &= ~BITS_FSR;
            }
        }

        sprintf(string, "%swhy_pc", PRM(misc_path));

        NoWhiteN();

        if (GetYnhAnswer(string, get_ibmpc, 0) == YES)
            usr.bits2 |= BITS2_IBMCHARS;
        else
            usr.bits2 &= ~BITS2_IBMCHARS;

        if (usr.bits & BITS_RIP)
        {
            usr.bits |= BITS_HOTKEYS | BITS_FSR;
            usr.bits2 |= BITS2_CLS;
        }
        else
        {
            NoWhiteN();

            sprintf(string, "%swhy_hot", PRM(misc_path));

            if (GetYnhAnswer(string, get_hotkeys, 0) == YES)
                usr.bits |= BITS_HOTKEYS;
            else
                usr.bits &= ~BITS_HOTKEYS;
        }

        Set_Lang_Alternate(hasRIP());

    {
        usr.video = GRAPH_TTY;
        usr.bits &= ~BITS_RIP;
        usr.bits2 |= BITS2_BORED;
    }
}

static int near checkterm(char *prompt, char *helpfile)
{
    char string[PATHLEN];

    sprintf(string, ss, PRM(misc_path), helpfile);

    NoWhiteN();
    return (GetYnhAnswer(string, prompt, 0) == YES);
}

void Validate_Runtime_Settings(void)
{
    BARINFO bi;

    Find_Class_Number();


    if (usr.video && baud < prm.speed_graphics && !local)
    {
        usr.video = GRAPH_TTY;
        usr.bits2 |= BITS2_BORED;
    }

    if (prm.flags & FLAG_no_magnet)
        usr.bits2 |= BITS2_BORED;

    if (usr.help != NOVICE && usr.help != REGULAR && usr.help != EXPERT)
        usr.help = NOVICE;

    if (usr.width < 20)
        usr.width = 20;

    if (usr.width > 132)
        usr.width = 132;

    if (usr.len < 8)
        usr.len = 8;

    if (usr.len > 200)
        usr.len = 200;

    if (usr.lang > prm.max_lang)
        usr.lang = 0;

    if (usr.bits & BITS_RIP)
    {
        usr.bits |= (BITS_HOTKEYS | BITS_FSR);
        usr.bits2 |= BITS2_CLS;
    }

    if (usr.bits & BITS_FSR)
        usr.bits2 |= BITS2_MORE;

#ifdef MUSTENCRYPT


    if (!(prm.flags2 & FLAG2_NOENCRYPT) && *usr.pwd && (usr.bits & BITS_ENCRYPT) == 0)
    {

        byte abMd5[MD5_SIZE];


        string_to_MD5(strlwr(usr.pwd), abMd5);

        memcpy(usr.pwd, abMd5, sizeof usr.pwd);
        usr.bits |= BITS_ENCRYPT;
    }
#endif


    if (!ValidMsgArea(usr.msg, NULL, VA_VAL | VA_PWD | VA_EXTONLY, &bi))
    {
        char temp[PATHLEN];

        Parse_Outside_Cmd(PRM(begin_msgarea), temp);
        SetAreaName(usr.msg, temp);
    }

    ForceGetFileArea();
    ForceGetMsgArea();
}

int Bad_Word_Check(char *username)
{
    FILE *baduser;

    char usrword[PATHLEN];
    char fname[PATHLEN];
    char line[PATHLEN];
    char *p;

    sprintf(fname, "%sbaduser.bbs", original_path);


            if ((*line == '~' && (stristr(p, line + 1) || stristr(username, line + 1))) ||
                (*line != '~' && (eqstri(p, line) || eqstri(username, line))))
            {
                fclose(baduser);


                return TRUE;
            }

            p = strtok(NULL, cmd_delim);
        }
    }

    fclose(baduser);

    return FALSE;
}

static void near Check_For_User_On_Other_Node(void)
{
    int lastuser;
    sword ret;

    struct _usr user;

    char fname[PATHLEN];

    word their_task;

    FFIND *ff;

    sprintf(fname, active_star, original_path);

    for (ff = FindOpen(fname, 0), ret = 0; ff && ret == 0; ret = FindNext(ff))
    {
        if (sscanf(cstrlwr(ff->szName), active_x_bbs, &their_task) != 1)
            continue;


        if (eqstri(user.name, usr.name))
        {
            Display_File(0, NULL, "%sACTIVE_2", PRM(misc_path));
            ci_ejectuser();
            mdm_hangup();
        }
    }

    FindClose(ff);
}


static void near Set_OnOffTime(void)
{
    union stamp_combo today;

    Get_Dos_Date(&today);


    next_ludate = today;


    if (usr.ludate.dos_st.date != next_ludate.dos_st.date)
    {
        usr.time = 0;
        usr.call = 0;
        usr.time_added = 0;
        usr.downtoday = 0;
        usr.ndowntoday = 0;
    }

    if (usr.time >= (word)ClassGetInfo(cls, CIT_DAY_TIME) ||
        usr.call >= (word)ClassGetInfo(cls, CIT_MAX_CALLS))
    {
        do_timecheck = FALSE;

        logit(log_exc_daylimit);
        Display_File(0, NULL, PRM(daylimit));

        Printf(tlimit1, ClassGetInfo(cls, CIT_CALL_TIME));
        Printf(tlimit2, usr.time);

        do_timecheck = TRUE;
        ci_ejectuser();


    Calc_Timeoff();
}


static void near Write_Active(void)
{
    int file;
    char fname[PATHLEN];

    sprintf(fname, activexx_bbs, original_path, task_num);

    if ((file = sopen(fname, O_CREAT | O_WRONLY | O_BINARY, SH_DENYWR, S_IREAD | S_IWRITE)) == -1)
        cant_open(fname);
    else
        close(file);
}



static int near InvalidPunctuation(char *string)
{
    char *badstring;
    char *badalias;

    if (prm.charset == CHARSET_SWEDISH)
    {
        badstring = ",/=@#$%^&()";
        badalias = "!*+:<>?~_";
    }
    else
    {
        badstring = "\",/\\[]=@#$%^&()";
        badalias = "!*+:<>?{|}~_";
    }

    if (strpbrk(string, badstring) != NULL)
        return TRUE;
    else
    {
        if (prm.flags & FLAG_alias)
            return FALSE;
        else
            return ((strpbrk(string, badalias) != NULL));
    }
}

void Get_Pwd(void)
{
    char got[PATHLEN];
    char check[PATHLEN];

    do
    {
        Clear_KBuffer();

        InputGetsLe(got, BUFLEN, '.', get_pwd1);

        if (strlen(got) < 4 || strlen(got) > 15 || strpbrk(got, cmd_delim))
        {
            Puts(bad_pwd1);
            *got = 0;
            continue;
        }

        Clear_KBuffer();

        InputGetsLe(check, BUFLEN, '.', check_pwd2);

        if (!eqstri(got, check))
        {
            Printf(bad_pwd2, got, check);
            *got = 0;
        }
        else
        {
#if defined(CHANGEENCRYPT) || defined(MUSTENCRYPT)
            usr.bits &= ~BITS_ENCRYPT;
            if (!(prm.flags2 & FLAG2_NOENCRYPT))
            {
                byte abMd5[MD5_SIZE];

                string_to_MD5(strlwr(got), abMd5);

                memcpy(usr.pwd, abMd5, sizeof usr.pwd);
                usr.bits |= BITS_ENCRYPT;
            }
            else
#endif
                strcpy(usr.pwd, cfancy_str(got));

            Get_Dos_Date(&usr.date_pwd_chg);
        }
    } while (*got == '\0');
}

static void near Calc_Timeoff(void)
{
    word mins;

    dword min_1;
    dword min_2;
    dword min_3;


    if (caller_online)
    {
        mins = (word)ClassGetInfo(cls, CIT_DAY_TIME) - usr.time + usr.time_added;
        mins = min(mins, (word)ClassGetInfo(cls, CIT_CALL_TIME));
    }
    else
        mins = prm.logon_time;

    min_1 = timeon + (dword)(mins * 60L);
    min_2 = timestart + (dword)(max_time * 60L);

    if (usr.xp_flag & XFLAG_EXPMINS)
        min_3 = timeon + ((long)(usr.xp_mins + 1) * 60L);
    else
        min_3 = min_2;

    timeoff = min(min_1, min_2);
    timeoff = min(timeoff, min_3);
}

#ifndef ORACLE


    if ((x = Mdm_kpeek_tic(200)) == 27)
        x = TRUE;
    else
        x = FALSE;

    while (Mdm_kpeek_tic(50) != -1)
        Mdm_getcw();
    mdm_dump(DUMP_INPUT);

    return x;
}


    mdm_dump(DUMP_INPUT);
    Mdm_puts(rip_autodetect);
    Mdm_flush();

