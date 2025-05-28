// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_wfc.c,v 1.3 2003/06/06 01:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_wfc
#define MAX_INCL_COMMS

#include "max_wfc.h"
#include "alc.h"
#include "events.h"
#include "keys.h"
#include "mm.h"
#include "modem.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>


static void near WFCMaxBaud(void)
{
    mdm_baud(Decimal_Baud_To_Mask(startbaud ? (unsigned int)startbaud : prm.max_baud));
}

void Wait_For_Caller(void)
{
    char *rsp;

    startbaud = baud;
    strcpy(usrname, us_short);
    ChatSetStatus(FALSE, cs_wfc);

    WFC_Init();

    Update_Status(wfc_waiting);

#if (COMMAPI_VER > 1)
    if (ComIsAModem(hcModem))
    {
#endif
        while ((rsp = Get_Modem_Response()) != NULL)
        {
            if (Process_Modem_Response(rsp))
                break;
        }
#if (COMMAPI_VER > 1)
    }
    else
    {
        while (!ComIsOnline(hcModem))
            usleep(250000);

        ComTxWait(hcModem, 1000);
        goto letsgo;
    }

        WinToTop(dspwin);

        VidHideCursor();

        WinTitle(win_stat, wfc_status_tit, TITLE_LEFT);
        WinTitle(win_modem, wfc_modem_tit, TITLE_LEFT);
        WinTitle(win_activ, wfc_activ_tit, TITLE_LEFT);
        WinTitle(win_keys, wfc_keys_tit, TITLE_LEFT);

        WinGotoXY(win_modem, 5, 0, FALSE);
        WinGotoXY(win_activ, 4, 0, FALSE);

        WinPutstr(win_keys, 0, 2, wfc_keys1);
        WinPutstr(win_keys, 0, 37, wfc_keys2);
        WinPutstr(win_keys, 1, 2, wfc_keys3);
        WinPutstr(win_keys, 1, 37, wfc_keys4);

        WinPutstr(win_stat, 0, 1, wfc_stat_nextev);
        WinPutstr(win_stat, 1, 1, wfc_stat_stat);
        WinPutstr(win_stat, 2, 1, wfc_stat_calltoday);
        WinPutstr(win_stat, 3, 1, wfc_stat_calltotal);
        WinPutstr(win_stat, 4, 1, wfc_stat_lastcaller);

        WinSync(win_stat, FALSE);
        WinSync(win_modem, FALSE);
        WinSync(win_activ, FALSE);
        WinSync(win_keys, FALSE);

        DrawMaxHeader();
    }

    in_wfc = TRUE;
    log_wfc = TRUE;
    do_timecheck = FALSE;

    kexit = FALSE;
    do_next_event = FALSE;

    Get_Next_Event();

    logit(log_wfc_waiting, (next_event_time - time(NULL)) / 60L);

    WFC_Init_Modem();
}

static void near WFC_Uninit(void)
{
#ifdef TTYVIDEO
    if (displaymode == VIDEO_IBM)
#endif
    {
        WinClose(win_keys);
        WinClose(win_activ);
        WinClose(win_modem);
        WinClose(win_stat);

        WinCls(win, CGRAY | _BLACK);
        WinSync(win, TRUE);
    }

    log_wfc = FALSE;
}

static char *near Get_Modem_Response(void)
{
#define RESP_TIMEOUT 500
#define MAX_RESP_LEN 60

    static char resp[MAX_RESP_LEN];
    char *rsptr;
    long tm1;

    mdm_dtr(DTR_UP);

    for (*resp = '\0'; *resp == '\0';)
    {
        tm1 = timerset(RESP_TIMEOUT);

        for (rsptr = resp; !timeup(tm1) && rsptr < resp + MAX_RESP_LEN;)
        {
#ifndef __MSDOS__
            if (!loc_kbhit())

                if (rsptr == resp)
                    tm1 = timerset(RESP_TIMEOUT);

                if (WFC_IdleInternal())
                    return NULL;
            }
            else
            {
                *rsptr = (char)mdm_ggetcw();

                if (*rsptr == '\r' || *rsptr == '\n')
                    break;

                rsptr++;
            }
        }


        if (eqstri(resp, "ok"))
            *resp = '\0';


        init_tmr = timerset(INIT_TIME);


        for (s = rsp + strlen(PRM(m_connect)); *s;)
        {
            {
                char *space = strchr(s, ' ');

                if (space)
                {
                    strncpy(arq_info, s + 1, space - s - 1);
                    arq_info[space - s - 1] = 0;
                    gotarq = TRUE;

                    s = space + 1;
                }
                else
                    s++;
            }
            else if (eqstrni(rsp, "fast", 4))
            {
                if (!gotbaud)
                {
                    baud = 9600L;
                    s += 4;
                    gotbaud = TRUE;
                }
                else
                    s++;
            }
            else if (isdigit(*s))
            {
                if (!gotbaud)
                {
                    baud = atol(s);

                    while (isdigit(*s))
                        s++;

                    gotbaud = TRUE;
                }
                else
                    s++;
            }
            else if (*s == '/' && !gotarq)
            {
                gotarq = TRUE;
                strnncpy(arq_info, ++s, ARQ_LEN - 1);
            }
            else
                s++;
        }

        if (!baud)
            baud = 300L;
        else if (baud == 1275L || baud == 75 || baud == 7512L || baud == 212L || baud == 12L)
        {
            baud = 1200L;
        }


        if (eqstri(arq_info, "pipe") || stristr(arq_info, "/vmp") || stristr(arq_info, "/tel"))
        {
            Delay(20);
        }
        else
        {
            Mdm_Flow(FLOW_OFF);


            WFC_Init_Modem();
            Update_Status(wfc_waiting);

            baud = 0L;
            *arq_info = '\0';
#endif

        return 1;
    }

    return 0;
}

static int near WFC_IdleInternal(void)
{
    static time_t last_ct = -1L;
    union stamp_combo now;
    time_t ct;

    if (loc_kbhit())
    {
        switch (loc_getch())
        {
        case K_ONEMORE:
            switch (loc_getch())
            {
            case K_ALTX:
                kexit = TRUE;
                return 1;

            case K_ALTJ:
#ifdef TTYVIDEO
                if (displaymode == VIDEO_IBM)
#endif
                {
                    if (dspwin)
                    {
                        WinClose(dspwin);
                        dspwin = NULL;
                    }

                    VidCls(CGRAY | _BLACK);
                }

                Shell_To_Dos();
                break;

            case K_ALTI:
                WFC_Init_Modem();
                Update_Status(wfc_waiting);
                break;

            case K_ALTB:
                break;

            case K_ALTK:
                local = TRUE;
                baud = 0L;
                return 1;
            }
            break;

        default:
            logit(log_wfc_keybjunk);
        }
    }

    ct = time(NULL);

    Get_Dos_Date(&now);

    if (now.dos_st.date != today.dos_st.date)
    {
        today = now;
        bstats.today_callers = 0;

        Update_Callers();

        Read_Event_File(event_num);
        Get_Next_Event();
    }

    if (ct >= next_event_time)
    {
        if (!next_event.erl)
            Get_Next_Event();
        else
        {
            next_event.flags |= EFLAG_DONE;
            Write_One_Event(&next_event);

            do_next_event = TRUE;
            return 1;
        }
    }

    if (last_ct != ct)
    {
        Update_Event_Time();
        DrawMaxHeader();

        if (init_tmr == -1)
            init_tmr = timerset(INIT_TIME);
    }


    Mdm_Flow(FLOW_OFF);
    Mdm_Flow(FLOW_ON);

    if (!out_empty())
        mdm_dump(DUMP_OUTPUT);

#ifdef OS_2
    ComWatchDog(hcModem, FALSE, 0);
#endif

    local = FALSE;

    UpdateStatWindow(wfc_initing);

    WFCMaxBaud();

    mdm_cmd(PRM(m_init));
    mdm_dtr(DTR_UP);
}


static void near Clear_MNP_Garbage(void)
{
    long done = timerset(500);
    int state = 0;
    int ch;


    if (*s)
        s[strlen(s) - 1] = '\0';

#ifdef TTYVIDEO
    if (displaymode == VIDEO_IBM)
#endif
    {
        WinPutc(win_activ, '\r');
        WinPutc(win_activ, '\n');
        WinPuts(win_activ, s);
        WinSync(win_activ, FALSE);
        VidHideCursor();
    }
}

static void near Get_Next_Event(void)
{
    union stamp_combo sc_now;
    struct tm tm_now;
    time_t lo_now;

    union stamp_combo sc_evtstart;
    struct tm tm_evtstart;
    time_t lo_evtstart;

    int today;

    today = TRUE;


    if (!GetEvent(EFLAG_ERLVL, EFLAG_DONE, &next_event, FALSE))
    {

            memset(&next_event, '\0', sizeof(struct _event));
            next_event_time = time(NULL) + (1440L * 60L);
            return;
        }
    }


    lo_now = mktime(&tm_now);

    DosDate_to_TmDate(&sc_evtstart, &tm_evtstart);


    if (!today)
        next_event_time += (1440L * 60L);


    if (next_event_time < lo_now)
        next_event_time = lo_now;
}

static void near DrawMaxHeader(void)
{
    time_t now;
    struct tm *lt;
    char *temp;
    char *temp2;

#ifdef TTYVIDEO
    if (displaymode != VIDEO_IBM)
        return;
#endif

    now = time(NULL);
    lt = localtime(&now);

    if ((temp = malloc(80)) == NULL || (temp2 = malloc(80)) == NULL)
    {
        if (temp)
            free(temp);

        return;
    }

    strftime(temp, 79, wfc_maxbanner, lt);
    sprintf(temp2, temp, version);

    WinSetAttr(win, col.wfc_name);
    WinCenter(win, 0, temp2);

    WinHline(win, 1, 0, VidNumCols() - 4, BORDER_SINGLE, col.wfc_line);

    WinSync(win, FALSE);
    VidHideCursor();

#ifdef MCP_VIDEO
    if (mcp_video)
        SendVideoDump();
#endif

    free(temp2);
    free(temp);
}

static void near UpdateStatWindow(char *status)
{
    Update_Event_Time();
    Update_Status(status);
    Update_Callers();
    Update_Lastuser();
}

static void near Update_Event_Time(void)
{
    char temp[80];

#ifdef TTYVIDEO
    if (displaymode != VIDEO_IBM)
        return;
#endif

    sprintf(temp, wfc_event_time, (next_event_time - time(NULL)) / 60L);
    WinPutstr(win_stat, 0, 16, temp);
    WinSync(win_stat, FALSE);
}

static void near Update_Status(char *status)
{
#ifdef TTYVIDEO
    if (displaymode != VIDEO_IBM)
    {
        logit(log_wfc_status, status);
        return;
    }
#endif

    WinGotoXY(win_stat, 1, 16, FALSE);
    WinPuts(win_stat, status);

    WinCleol(win_stat, WinGetRow(win_stat), WinGetCol(win_stat), WinGetAttr(win_stat));

    WinSync(win_stat, FALSE);
}

static void near Update_Callers(void)
{
    char temp[80];

#ifdef TTYVIDEO
    if (displaymode != VIDEO_IBM)
        return;
#endif

    sprintf(temp, pd, bstats.today_callers);
    WinPutstr(win_stat, 2, 16, temp);

    sprintf(temp, pl, bstats.num_callers);
    WinPutstr(win_stat, 3, 16, temp);
    WinSync(win_stat, FALSE);
}

static void near Update_Lastuser(void)
{
    char temp[80];
    struct _usr user;
    int lu;

#ifdef TTYVIDEO
    if (displaymode != VIDEO_IBM)
        return;
#endif

    sprintf(temp, task_num ? lastusxx_bbs : lastuser_bbs, original_path, task_num);

    if ((lu = shopen(temp, O_RDONLY | O_BINARY)) == -1)
        WinPutstr(win_stat, 4, 16, wfc_no_last_caller);
    else
    {
        if (read(lu, (char *)&user, sizeof(struct _usr)) == sizeof(struct _usr))
        {
