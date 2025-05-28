// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_cho.c,v 1.1.1.1 2002/10/01 17:51:32 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_chat

#include "alc.h"
#include "ffind.h"
#include "max_chat.h"
#include "mm.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef MCP
#define INCL_DOS
#include "mcp.h"
#include "pos2.h"
extern HPIPE hpMCP;
#endif

extern struct _cstat cstat;

extern word cur_ch;
extern word num_task;
extern word *tasks;

extern long scan_time;

static void near Chat_Toggle(void);
static void near Chat(int use_cb, int doing_answer);
static void near Page(void);
static void near ChatNotAvail(int tid);
static void near ChatCantPageSelf(void);
static int near Remove_From_Chat_List(byte tid);
static void near Add_To_Chat_List(byte tid);

int Exec_Chat(int type, char **result)
{
    *result = NULL;

    switch (type)
    {
    case who_is_on:
        Who_Is_On();
        break;
    case o_page:
        Page();
        break;
    case o_chat_cb:
        Chat(TRUE, FALSE);
        break;
    case o_chat_pvt:
        Chat(FALSE, TRUE);
        break;
    case chat_toggle:
        Chat_Toggle();
        break;
    default:
        logit(bad_menu_opt, type);
        return 0;
    }

    return 0;
}

static struct _cgs *near ChatFindOpen(void)
{
    static struct _cgs *cgs;

#ifndef MCP
    if (!*PRM(ipc_path))
        return NULL;
#endif

    if ((cgs = malloc(sizeof(struct _cgs))) == NULL)
        return NULL;

#ifdef MCP
    if (!hpMCP)
        return NULL;

    {
        USHORT usQuery = PMSG_QUERY_TASKLIST;
        OS2UINT cbRead, rc;
        byte tids[255];
        int i;


        for (i = 1; i < cbRead; i++)
            cgs->tids[i - 1] = tids[i];

        cgs->num_tid = cbRead - 1;
    }

#else
    {
        char temp[PATHLEN];
        FFIND *ff;


            if (sscanf(ff->szName, ipc_x, &tid) == 1)
                cgs->tids[cgs->num_tid++] = tid;

            if (FindNext(ff) != 0)
                break;
        }

        FindClose(ff);
    }

#endif


    cgs->ptr = 0;

    return cgs;
}


int ChatFindIndividual(byte tid, char *username, char *status, word *avail)
{
    struct _cstat cstat;

#ifdef MCP
    byte req[3];
    OS2UINT cbRead, rc;

    if (!hpMCP)
        return FALSE;

    *(USHORT *)req = PMSG_QUERY_TASKINFO;
    req[2] = tid;


static void near ChatFindClose(struct _cgs *cgs)
{
    if (cgs)
        free(cgs);
}

static void near Page(void)
{
    char temp[PATHLEN];

    word avail;
    byte tid;

#ifndef MCP
    if (!*PRM(ipc_path))
        return;
#endif

    for (strcpy(temp, qmark); eqstri(temp, qmark);)
    {
        WhiteN();

        InputGets(temp, ch_node_to_page);

        if (eqstri(temp, qmark))
            Who_Is_On();
    }

    if ((tid = (byte)atoi(temp)) != 0)
    {
        if (tid == task_num)
            ChatCantPageSelf();
        else if (!ChatFindIndividual(tid, NULL, NULL, &avail) || !avail)
            ChatNotAvail(tid);
        else
        {
            sprintf(temp, ch_being_paged, usrname, task_num);

            if (ChatSendMsg(tid, CMSG_PAGE, strlen(temp) + 1, temp) == -1)
#ifdef DEBUG
                Printf("*MsgErr*");
#else
                ;
#endif

            Printf(ch_waiting, tid);

            sprintf(linebuf, "%d", tid);
            Chat(FALSE, FALSE);
        }
    }
}


    if (avail)
    {
        usr.bits |= BITS_NOTAVAIL;
        ChatSetStatus(FALSE, cs_notavail);
    }
    else
    {

        if (x == task_num)
        {
            ChatCantPageSelf();
            return;
        }
        else if (!ChatFindIndividual((byte)x, temp, NULL, &avail) || (!doing_answer && !avail))
        {
            ChatNotAvail(x);
            return;
        }


        y = min(x, task_num);
        z = max(x, task_num);

        cc = (y * 256) + z;

        sprintf(stat, ch_chat_pvt, x);
        logit(log_pvt_start, temp, x);
    }

    if (*temp && cc)
    {

        if ((tasks = malloc(MAX_TASK * sizeof(int))) == NULL)
            return;


        *(int *)temp = cur_ch;
        strcpy(temp + 2, usrname);

        if ((cgs = ChatFindOpen()) == NULL)
            return;

        while (ChatFindNext(cgs, &tid, NULL, NULL, &avail))
            if (tid && tid != task_num)
                if (ChatSendMsg(tid, CMSG_ENQ, strlen(temp + 2) + 3, temp) == -1)
#ifdef DEBUG
                    Printf("%MsgErr %d%", tid);
#else
                    ;
#endif

        ChatFindClose(cgs);

        scan_time = CHAT_SCAN_TIME;
        in_node_chat = TRUE;

        ChatSaveStatus(&css);
        ChatSetStatus(FALSE, stat);

        Puts(ch_enter_chat);
        Puts(ch_help_str);

        for (;;)
        {
            colour = (byte)((task_num % 6) + 9);

            if (colour == 10)
                colour = 15;

            sprintf(prompt, ch_byline, usrname, colour);

            if (*nextw)
                strcpy(temp, nextw);
            else
                *temp = '\0';

            if (Input(temp, INPUT_NLB_LINE | INPUT_WORDWRAP, 0,
                      min(TermWidth() - 2, PATHLEN - 2) - 19, prompt) == 1)
            {
                strcpy(nextw, temp + strlen(temp) + 1);
            }
            else
                *nextw = '\0';

            if (eqstri(temp, "/w"))
            {
                Puts(ch_ulist_hdr);

                if (!num_task)
                    Puts(ch_alone);

                for (x = 0; x < num_task; x++)
                    if (ChatFindIndividual((byte)tasks[x], temp, NULL, NULL))
                    {
                        Puts(temp);
                        Putc('\n');
                    }

                Putc('\n');
            }
            else if (eqstri(temp, "/s"))
            {
                Who_Is_On();
                Putc('\n');
            }
            else if (eqstri(temp, "/?") || eqstri(temp, qmark))
                Display_File(0, NULL, ss, PRM(misc_path), "CHATHELP");
            else if (eqstri(temp, "/q"))
                break;
                strcat(prompt, temp);

        Check_For_Message(NULL, NULL);

        scan_time = NORM_SCAN_TIME;
        logit(log_exit_chat);
    }

    cur_ch = -1;
}

static void near Add_To_Chat_List(byte tid)
{
    word x;

#ifdef DEBUG
    Printf("@adding %d to chat list.\n", tid);
#endif

    if (tasks && num_task < MAX_TASK)
    {

        if (x == num_task)
            tasks[num_task++] = tid;
    }
}

static int near Remove_From_Chat_List(byte tid)
{
    word x, y;

    if (!tasks)
        return FALSE;

    for (x = 0; x < num_task; x++)
    {
        if (tasks[x] == (word)tid)
        {
            for (y = x; y < num_task - 1; y++)
                tasks[y] = tasks[y + 1];

            break;
        }
    }

    if (x == num_task)
        return FALSE;

    num_task--;
    return TRUE;
}


    case CMSG_HEY_DUDE:

        R_Cleol();
        Display_File(0, NULL, msg);
        vbuf_flush();
        break;

    case CMSG_PAGE:
#ifdef DEBUG
        Printf("@enq from tid %d --", tid);
#endif


        if (*(word *)msg == cur_ch)
        {
#ifdef DEBUG
            Printf(" sending ack.", tid);
#endif

            if (ChatSendMsg(tid, CMSG_ACK, 0, msg) == -1)
#ifdef DEBUG
                Printf("!MsgErr!");
#else
                ;
#endif

            Add_To_Chat_List(tid);

            R_Cleol();

            Printf(ch_xx_join, msg + 2);

            *redo = TRUE;
        }

#ifdef DEBUG
        Putc('\n');
#endif
        break;

#ifdef DEBUG
        Printf("@eot from tid %d.\n", tid);
#endif

        if (Remove_From_Chat_List(tid))
        {
            R_Cleol();
            Printf(ch_xx_leave, msg);
            WhiteN();
            Puts(ch_help_str);

            *redo = TRUE;
        }
        break;

    case CMSG_CDATA:

        if (*(word *)msg != cur_ch)
        {
#ifdef DEBUG
            Printf("#MsgUnSol %d# ", (int)*msg);
#endif

            ChatSendMsg(tid, CMSG_EOT, strlen(usrname) + 1, usrname);
        }

void ChatAPB(char *msg)
{
    static struct _cgs *cgs;
    word avail;
    byte tid;

#ifndef MCP
    if (!*PRM(ipc_path))
        return;
#endif

    if ((cgs = ChatFindOpen()) == NULL)
        return;

    while (ChatFindNext(cgs, &tid, NULL, NULL, &avail))
        if (avail && tid != task_num)
            if (ChatSendMsg(tid, CMSG_HEY_DUDE, strlen(msg) + 1, msg) == -1)
#ifdef DEBUG
                Printf("(MsgErr %d)", tid);
#else
                ;
#endif

    ChatFindClose(cgs);
}
