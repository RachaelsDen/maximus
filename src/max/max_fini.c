// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_fini.c,v 1.1.1.1 2002/10/01 17:51:38 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_init
#define MAX_LANG_max_chat
#define MAX_INCL_COMMS

#include "dr.h"
#include "ffind.h"
#include "max_file.h"
#include "max_msg.h"
#include "prog.h"
#include "trackm.h"
#include "userapi.h"
#include <conio.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef ORACLE

static void near FreeAccess(void);
static void near Local_Cleanup(void);
static void near Write_User(void);
static void near ChatOff(void);


void FinishUp2(int hangup)
{
    long wasonfor;
    char temp[PATHLEN];

    Mdm_Flow(FLOW_OFF);

    if (hangup && rst_offset == -1L)

    while (PopMsgArea())
        ;

    while (PopFileArea())
        ;

    if (MsgCloseApi() == -1)
        logit(log_err_msgapi);

    if (this_logon_bad)
        usr.bits2 |= BITS2_BADLOGON;

    Lputs(GRAY);

    if (hangup && !in_wfc)
    {
        Lputc('\n');

        if (fLoggedOn && rst_offset == -1L)
            logit(log_user_off_line, *usrname ? usrname : user_text, usr.times, (long)wasonfor,
                  (long)usr.time + wasonfor);
    }

    ExitMsgAreaBarricade();
    ExitFileAreaBarricade();

    if (locked)
    {
        locked = FALSE;
        usr.priv = lockpriv;
    }

    if (fLoggedOn && !in_wfc)
    {
        usr.ludate = next_ludate;

        if (!nowrite_lastuser)
            Write_LastUser();

        TagWriteTagFile(&mtm);
    }

    DeinitTracker();

    usr.time += (int)wasonfor;
    usr.call++;

    if (usr.xp_flag & XFLAG_EXPMINS)
    {
        if ((signed long)usr.xp_mins - wasonfor <= 0)
            Xpired(REASON_TIME);
        else
            usr.xp_mins -= wasonfor;
    }

    if (fLoggedOn && !acsflag(CFLAGA_HIDDEN))
        ci_save();

    if ((fLoggedOn || this_logon_bad) && !nowrite_lastuser && !in_wfc)
    {
        Write_User();
        if (fLoggedOn && !acsflag(CFLAGA_HIDDEN))
        {
            char *name = usr.name;

            if ((prm.flags & FLAG_alias) && *usr.alias)
                name = usr.alias;

            strncpy(bstats.lastuser, name, sizeof bstats.lastuser);
        }
    }

    }

    LogClose();

    AreaFileClose(ham);
    AreaFileClose(haf);

    if (fossil_initd && rst_offset == -1L)
    {
        if (!local)
        {
            Mdm_Flow(FLOW_OFF);
            mdm_dump(DUMP_OUTPUT);

            mdm_baud((char)Decimal_Baud_To_Mask(prm.max_baud));
            mdm_cmd(PRM(m_busy));
        }

        mdm_deinit();

        fossil_initd = FALSE;
    }

    if (offsets)
        (free)(offsets);

    if (original_prompt)
    {

static void near ChatOff(void)
{
    char temp[PATHLEN];

    if (!*PRM(ipc_path))
        return;

    sprintf(temp, ipcxx_bbs, PRM(ipc_path), task_num);
    unlink(temp);
}

void Got_A_Null_Pointer(char *type, char *where)
{
    logit(">!Null ptr/%s%s. PLEASE REPORT BUG TO AUTHOR!", type, where);

#ifdef __NEARDATA__
    logit(">!DataSeg=%08lx%08lx%08lx%08lx", *(long *)0x0000, *(long *)0x0004, *(long *)0x0008,
          *(long *)0x000c);
#endif


    local_putc = (void(_stdc *)(int))fputchar;
    local_puts = (void(_stdc *)(char *))putss;

    if (!no_video)
        WinSync(win, TRUE);

#ifdef __MSDOS__
    if (multitasker == MULTITASKER_desqview)
        End_Shadow();
#endif

    WinClose(win);
    WinApiClose();
    VidClose();
}

{
    if (finished || in_wfc)
        return;

    ci_carrier();

    if (caller_online || !fLoggedOn)
    {
        Lputs(CYAN "\n");

        if (do_caller_vanished)
            logit(log_byebye);
    }

    caller_online = FALSE;

    Mdm_Flow(FLOW_OFF);
    mdm_dump(DUMP_ALL);

    quit(0);
}

{
    if (finished)
        return;

    if (!sent_time_5left && !shut_up)
    {
        sent_time_5left = TRUE;
        do_timecheck = FALSE;
        Puts(min5_left);
        do_timecheck = TRUE;
        vbuf_flush();
    }
}

{
    if (finished)
        return;

    ci_timelimit();

    logit(log_tlimit);

    do_timecheck = FALSE;

    if (!shut_up)
    {
        Puts(time_up);
        Display_File(0, NULL, time_file, PRM(misc_path));
    }

    vbuf_flush();
    mdm_hangup();
}

void Xpired(int reason)
{
    int xpflag;

    Display_File(0, NULL, "%sXP%s", PRM(misc_path), (reason == REASON_TIME) ? "TIME" : "DATE");

    xpflag = usr.xp_flag;
    usr.xp_flag &= ~(XFLAG_EXPMINS | XFLAG_EXPDATE | XFLAG_AXE | XFLAG_DEMOTE);
    usr.xp_mins = 0;
    usr.xp_date.ldate = 0L;

    ci_expired();

    if (xpflag & XFLAG_AXE)
    {
        usr.delflag |= UFLAG_DEL;


void ChatCleanUp(void)
{
    extern word *tasks;
    extern word num_task;

    char temp[PATHLEN];
    word x;

    if (!(tasks && in_node_chat))
        return;

    for (x = 0; x < num_task; x++)
    {
        sprintf(temp, ch_off_abnormally, usrname);

        if (ChatSendMsg((byte)tasks[x], CMSG_HEY_DUDE, strlen(temp) + 1, temp) == -1)
#ifdef DEBUG
            Printf("@MsgErr %d@", tasks[x]);
#else
            ;
#endif

        strcpy(temp, usrname);

        if (ChatSendMsg((byte)tasks[x], CMSG_EOT, strlen(temp) + 1, temp) == -1)
#ifdef DEBUG
            Printf("@MsgErr %d@", tasks[x]);
#else
            ;
#endif
    }

    num_task = 0;
    free(tasks);
}

{
    long flush_tout;

    if (!local)
    {

        flush_tout = timerset(1500);

        while (!out_empty() && !timeup(flush_tout))
            Giveaway_Slice();

        mdm_dump(DUMP_OUTPUT);

        if (!no_dtr_drop)
        {
            mdm_dtr(DTR_DOWN);
            Delay(250);
            mdm_dtr(DTR_UP);
        }
    }

    quit(0);
}

void medfini(void);


    if (el)
        erl = (char)el;
    else if (!fLoggedOn)
        erl = ERROR_RECYCLE;
    else if ((written_echomail || written_conf) && prm.echo_exit)
        erl = prm.echo_exit;
    else if (written_matrix && prm.edit_exit)
        erl = prm.edit_exit;
    else if (written_local && prm.local_exit)
        erl = prm.local_exit;

#ifndef ORACLE
static void near Write_User(void)
{
    HUF huf;
    struct _usr user;

    if ((huf = UserFileOpen(PRM(user_file), 0)) == NULL)
    {
        cant_open(PRM(user_file));
        Local_Beep(3);
        return;
    }

