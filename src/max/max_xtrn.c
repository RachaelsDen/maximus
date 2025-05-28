// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_xtrn.c,v 1.2 2003/06/04 23:53:08 wesgarland Exp $";
#pragma on(unreferenced)

#define MAX_LANG_max_chat
#define MAX_INCL_COMMS

#include "dr.h"
#include "max_file.h"
#include "max_msg.h"
#include "mm.h"
#include "prog.h"
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <process.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#ifdef __WATCOMC__

    getword(cmd, progname, " ;", 1);


    for (s = strtok(newpath, " ;"); s || last; s = strtok(NULL, " ;"))
    {
        if (s)
        {
            (void)strcpy(this, s);
            Add_Trailing(this, PATH_DELIM);
        }
        else
        {
            (void)strcpy(this, "");
            last = FALSE;
        }

        (void)strcat(this, progname);

        try = strdup(this);

        if (!try)
        {
            free(newpath);
            return NULL;
        }

        if (!fexist_maybehidden(this))
        {
            (void)strcpy(this, try);
            (void)strcat(this, ".com");

            if (!fexist_maybehidden(this))
            {
                (void)strcpy(this, try);
                (void)strcat(this, ".exe");

                if (!fexist_maybehidden(this))
                {

        s = firstchar(cmd, " ;", 2);

        (void)strcat(this, " ");
        (void)strcat(this, s ? s : "");

        free(try);
        break;
    }

    free(newpath);

    rc = malloc(strlen(this) + 2);
    strcpy(rc, this);
    return rc;
}

    char *szRun;
    char *s;


    szRun[strlen(szRun) + 1] = 0;


    sprintf(szSwapName, "~~~max%02x.~~~", task_num);
    max_swap_filename = szSwapName;

    rc = do_exec(s, s + strlen(s) + 1, USE_EMS | USE_XMS | USE_FILE, 0xffff, NULL);

    if (rc >= 0x100)
    {
        if (rc >= 0x100 && rc <= 0x1ff)
            errno = ENOMEM;
        else if (rc >= 0x200 && rc <= 0x2ff)
            errno = ENOENT;
        else if (rc >= 0x300 && rc <= 0x3ff)
        {

static int near swapvp(char *szName, char **szArgs)
{
    char *szProg = malloc(PATHLEN * 2);
    int rc;

    NW(szName);

    if (!szProg)
    {
        errno = ENOMEM;
        return -1;
    }

    *szProg = 0;

    while (*szArgs)
    {
        strcat(szProg, *szArgs++);

        if (*szArgs)
            strcat(szProg, " ");
    }

    rc = swapsz(szProg);

    free(szProg);

    return rc;
}


static char *near GetComspec(void)
{
    char *comspec;

    comspec = getenv("COMSPEC");

    if (!comspec)
#if defined(__MSDOS__)
        comspec = "command.com";
#elif defined(OS_2) || defined(NT)
        comspec = "cmd.exe";
#elif defined(UNIX)
        comspec = "/bin/sh";
#else
#error Unknown OS
#endif

    return comspec;
}

int Outside(char *leaving, char *returning, int method, char *parm, int slogan, int ctltype,
            char restart_type, char *restart_name)
{

    struct _css *css;
    int tonline;

    char **args = NULL, *temp, *temp2 = NULL, *p, *s;

    sword erl, stay, reread, nofix;
    sword timeremain, x;

    byte save_inchat;
    long starttime;

#ifdef __MSDOS__
    int save_stdout, save_stdin;
    FILE *bat;
#else
    (void)restart_type;
    (void)restart_name;
#endif

    NW(slogan);


    if (method == OUTSIDE_ERRORLEVEL)
        method = OUTSIDE_RUN;
#endif

    ChatSaveStatus(css);

    if (!in_wfc)
        ChatSetStatus(FALSE, cs_outside);


        display_line = display_col = 1;

        if (leaving)
            Display_File(0, NULL, leaving);


        tonline = timeonline();

        Write_LastUser();


    if (!in_wfc)
        Mdm_flush_ck_tic(4000, FALSE, TRUE);

    mdm_deinit();

    Out_Save_Directories(stay);


    if (ctltype == CTL_NORMAL && !in_wfc)
        Write_External_Ctlfile(ctltype, parm, method);


        extern HCOMM hcModem;
        HFILE hf;
        int i;

        hf = ComGetFH(hcModem);

        for (i = 5; i < 50; i++)
            if (i != hf)
                DosSetFHandState(i, OPEN_FLAGS_NOINHERIT);
    }
#elif defined(__MSDOS__)

#ifdef __MSDOS__
    if (method == OUTSIDE_ERRORLEVEL)
    {

        strcpy(temp, parm);

        if (!in_wfc)
            logit(external_prog, parm);

        for (x = 0, p = strtok(temp, ctl_delim); p && x < MAX_EXECARGS;
             x++, p = strtok(NULL, ctl_delim))
        {
#ifndef OS_2
            if (*p == '<')
            {
                freopen(p + 1, fopen_read, stdin);
                x--;
            }
            else if (*p == '>')
            {
#endif
            {
                if ((args[x] = (char *)malloc(strlen(p) + 1)) == NULL)
                {
                    logit("!OA-MEMOVFL");
                    erl = -1;
                    goto RetProc;
                }

                strcpy(args[x], p);

                s = strrchr(args[x], '.');

                if (x == 0 && s &&
                    (strnicmp(s, ".bat", 4) == 0 || strnicmp(s, ".btm", 4) == 0 ||
                     strnicmp(s, ".cmd", 4) == 0))
                {
                    logit(log_badex1);
                    logit(log_badex2);

                    args[++x] = NULL;
                    erl = -1;
                    goto Skip;
                }
            }
        }

        args[x] = NULL;

        Close_Files();

        if (method == OUTSIDE_CHAIN)
        {

        strcpy(temp, parm);

        if (!in_wfc)
            logit(external_prog, temp);

        Close_Files();

        if ((prm.flags & FLAG_watchdog) && !local && !in_wfc)
            mdm_watchdog(1);

        IoPause();

#if defined(__WATCOMC__) && !defined(__FLAT__)
        _heapshrink();
#endif

#ifdef SWAP
        if (prm.flags2 & FLAG2_SWAPOUT)
        {
            strcpy(temp, GetComspec());
            strcat(temp, " /c ");
            strcat(temp, parm);

            erl = swapsz(temp);

            strcpy(temp, parm);
        }
        else
#endif
            erl = system(temp);

        IoResume();

        if ((prm.flags & FLAG_watchdog) && !local && !in_wfc)
            mdm_watchdog(0);

        Reopen_Files();

        if (!in_wfc)
            logit(return_prog, temp, erl);
    }
    else
        logit(log_badom);

RetProc:


    if (reread && !in_wfc)
    {
        word old_priv = usr.priv;
        word old_max2priv = usr.max2priv;

        Outside_Reread(timeremain, tonline);


        if (old_max2priv != usr.max2priv && old_priv == usr.priv)
            usr.priv = max3priv(usr.max2priv);

        Find_Class_Number();
        SetUserName(&usr, usrname);
    }


#if !(defined(OS_2) && defined(__FLAT__))
    brktrap();
#endif

#ifdef __MSDOS__
    Restore_Directories3();
#endif

    Out_Reinstall_Fossil();
    Out_Video_Up();

    display_line = display_col = 1;
    inchat = save_inchat;

    mdm_attr = curattr = -1;

    Puts(GRAY);

    if (returning && !in_wfc)
    {
        Display_File(0, NULL, returning);
        vbuf_flush();
    }

    ChatRestoreStatus(css);

    free(css);
    free(args);
    free(temp2);
    free(temp);

    return erl;
}

static void near Out_Save_Directories(int stay)
{
#ifndef __MSDOS__
    NW(stay);


#else
    char *temp;
    int disk, max_d, x;


    max_d = setdisk(disk);
    max_d = min(max_d, MAX_DRIVES);


    for (x = 0; x < max_d; x++)
        if (IsBit(prm.drives_to_save, x))
            break;


        if ((temp = malloc(PATHLEN)) != NULL)
        {
            for (x = 0; x < max_d; x++)
            {
                if (IsBit(prm.drives_to_save, x))
                {
                    sprintf(temp, "%c:.", 'A' + x);
                    Save_Directory3(temp);

                    if (!stay && orig_path2[x])
                        chdir(orig_path2[x]);
                }
            }

            free(temp);
        }



    fprintf(stdout, "\x08");

#if !(defined(OS_2) && defined(__FLAT__))
    brkuntrap();
#endif

    if ((prm.flags2 & FLAG2_NOCRIT) == 0)
        uninstall_24();

#else
        if (dspwin)
        {
            WinClose(dspwin);
            dspwin_time = 0L;
            dspwin = NULL;
        }

        Draw_StatusLine(STATUS_REMOVE);

#ifdef __MSDOS__
        if (multitasker == MULTITASKER_desqview)
            End_Shadow();
#endif

        if (!no_video && !in_wfc)
            WinSyncAll();
#endif
    }
}

static void near Out_Video_Up(void)
{
#ifdef TTYVIDEO
    if (displaymode == VIDEO_IBM)
    {
#endif
#ifdef SHUTVIDEO

        Lputs(CLS);
        fossil_getxy(&current_line, &current_col);
    }
#endif
}

static void near Out_Reinstall_Fossil(void)
{

    mdm_deinit();
    Fossil_Install(FALSE);
    Mdm_Flow_On();
}

static void near Close_Files(void)
{
    if ((prm.flags & FLAG_close_sf) == 0)
    {
        LogFlush();
        return;
    }


    LogClose();
}

static void near Reopen_Files(void)
{
    if (prm.flags & FLAG_close_sf)
    {
        if (!LogOpen())
            quit(ERROR_CRITICAL);
    }
}

static void near Outside_Reread(int tr, int tonline)
{
    char temp[PATHLEN];
    int ffile;

    if (task_num)
        sprintf(temp, lastusxx_bbs, original_path, task_num);
    else
        sprintf(temp, lastuser_bbs, original_path);

    if ((ffile = shopen(temp, O_RDONLY | O_BINARY)) == -1)
    {
        cant_open(temp);
        return;
    }

    read(ffile, (char *)&usr, sizeof(struct _usr));
    close(ffile);


    timeoff += (usr.timeremaining - tr) * 60L;


    usr.time -= tonline;


    if (*PRM(backfromdos) && !in_wfc)
        Display_File(0, NULL, PRM(backfromdos));


int Exec_Xtern(int type, struct _opt *thisopt, char *arg, char **result, char *menuname)
{
    int method;
    int ctl, ret;

    *result = NULL;

    switch (type)
    {
    case xtern_erlvl:
        method = OUTSIDE_ERRORLEVEL;
        break;
    case xtern_run:
        method = OUTSIDE_RUN;
        break;
    case xtern_concur:
        method = OUTSIDE_CONCUR;
        break;
    case xtern_chain:
        method = OUTSIDE_CHAIN;
        break;
    case xtern_dos:
        method = OUTSIDE_DOS;
        break;
    default:
        logit(bad_menu_opt, type);
        return 0;
    }

    if (thisopt->flag & OFLAG_REREAD)
        method |= OUTSIDE_REREAD;

    ctl = (thisopt->flag & OFLAG_CTL) ? CTL_NORMAL : CTL_NONE;

    ret = Outside(PRM(out_leaving), PRM(out_return), method, Strip_Underscore(arg), TRUE, ctl,
                  RESTART_MENU, menuname);

    Clear_KBuffer();

    return ret;
}

#ifndef ORACLE

static int near Form_Outside_Filename(char *in, char *out, int method)
{
    if (method != OUTSIDE_ERRORLEVEL)
    {
        getword(in, out, ".", 1);
        return 0;
    }

    getword(in, out, " .", 2);


static void near Write_External_Ctlfile(int ctltype, char *parm, int method)
{
    FILE *ctl;

    char temp[PATHLEN];
    char temp2[PATHLEN];
    long bd = steady_baud_l ? steady_baud_l : baud;

    NW(ctltype);

    if (Form_Outside_Filename(parm, temp, method))
        return;

    strcat(temp, ".ctl");

    if ((ctl = shfopen(Add_Task_Number(temp, temp2), fopen_write, O_WRONLY | O_CREAT | O_TRUNC)) ==
        NULL)
    {
        cant_open(temp2);
        return;
    }

    if (local)
        fprintf(ctl, xctl_keyboard);
    else
        fprintf(ctl, xctl_port_baud, port + 1, baud);

    if (!local)

        sprintf(tn, "%02x", task_num);

        p = strrchr(new, '.');
        s = strrchr(new, PATH_DELIM);

        if (s)
            s++;
        else
            s = new;

        if (!p)
            p = s + strlen(s);

        if (p <= s + 6)
            strocpy(p + 2, p);
        else if (p == s + 7)
        {
            strocpy(p + 1, p);
            p--;
        }
        else
            p -= 2;

        *p = *tn;
        *(p + 1) = *(tn + 1);
    }

    return new;
}

