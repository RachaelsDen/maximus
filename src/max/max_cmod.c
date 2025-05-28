// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_cmod.c,v 1.2 2003/06/04 23:35:23 wesgarland Exp $";
#pragma on(unreferenced)

#define MAX_LANG_max_init
#define MAX_LANG_f_area
#define MAX_LANG_max_chat
#define MAX_INCL_COMMS

#include "alc.h"
#include "keys.h"
#include "mm.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

static int pm_getch(void);
static int near Open_Chatlog(void);

void ChatMode(void)
{
    struct _fossil_info finfo;
    char *chatprog;
    char temp[PATHLEN];
    char lastword[BUFLEN];
    char savekb, savesnoop, savedotc;
    word savebits2;
    struct _css css;

    dword add1, add2;

    word lastidx;
    byte col;

    sword last_speaker, break_loop;
    sword ch, len, c;

    long startchat;

    fossil_inf((struct _fossil_info far *)&finfo);

    num_yells = 0;


    ChatSaveStatus(&css);


    if (*usr.name == '\0')
        usr.bits2 &= ~BITS2_IBMCHARS;

    chatlog = NULL;
    keyboard = snoop = TRUE;
    do_timecheck = FALSE;

    logit(log_chat, entering, the_chatmode);
    startchat = time(NULL);

        {
            Mex(chatprog + 1);
        }
        else
        {
            Outside(NULL, NULL, OUTSIDE_DOS, chatprog, FALSE, CTL_NONE, RESTART_MENU, NULL);
        }
    }
    else
    {

        *lastword = '\0';
        lastidx = 0;
        last_speaker = -1;
        LocalMsg(chat_on);

        if (*PRM(chat_fbegin))
            Display_File(0, NULL, PRM(chat_fbegin));
        else
            Puts(chat_start);

        col = 1;

        Mdm_Flow_Off();
        vbuf_flush();
        break_loop = FALSE;

                    c = pm_getch();

#ifdef UNIX
                    if (c == K_ESC)
                    {
                        {
                            if (Open_Chatlog())
                                LocalMsg(chat_capon);
                        }
                    }
                    else if (c == K_ALTJ)
                    {


                        *lastword = '\0';

                        switch (c)
                        {
                        case K_UP:
                            if (current_line > 1)
                                Puts(UP);
                            break;

                        case K_LEFT:
                            if (current_col > 1)
                            {
                                col--;
                                Puts(LEFT);
                            }
                            break;

                        case K_RIGHT:
                            if (current_col < TermWidth() && current_col < (byte)(finfo.width - 1))
                            {
                                col++;
                                Puts(RIGHT);
                            }
                            break;

                        case K_DOWN:
                            if (current_line < usr.len && current_line < (byte)(finfo.height))
                            {
                                Puts(DOWN);
                            }
                            break;
                        }
                    }

                    vbuf_flush();
                    break;

                case 7:
                    Putc('\a');
                    vbuf_flush();
                    ch = 0;
                    break;

#ifdef UNIX
                realEscape:
                case -2:
#else
                        {
                            if (current_col > 1)
                            {
                                col--;
                                Puts(LEFT);
                                *lastword = '\0';
                            }
                            break;

                            if (current_line < (byte)(min(usr.len, finfo.height)))
                            {
                                Puts(DOWN);
                                *lastword = '\0';
                            }
                            break;
                        }

                        vbuf_flush();
                    }

                    ch = 0;
                    break;
                }
            }
            else
            {
                ch = 0;
                Check_For_Message(NULL, NULL);

                if (!local && !carrier())
                    break;

                Giveaway_Slice();
            }

            if (break_loop)
                break;

            switch (ch)
            {

                if (col > 1)
                {
                    col--;
                    Puts(bs_sp_bs);

                    if (lastidx)
                        lastword[--lastidx] = '\0';

                Putc('\n');
                lastword[lastidx = 0] = '\0';
                col = 1;

                if (chatlog)
                    fputc('\n', chatlog);

                break;

                Puts("+\x08");
                if (chatlog)
                    fputc(ch, chatlog);

                Putc(ch);
                col++;

                if (lastidx >= (word)sizeof(lastword) - 2)

                if (ch == ' ' || ch == ',' || ch == '-')
                    lastword[lastidx = 0] = '\0';

                if (col >= (byte)(TermWidth() - 4))
                {
                    if (strlen(lastword) > (word)(TermWidth() / 2))
                    {
                        if (chatlog)
                            fputc('\n', chatlog);

                        Puts(CLEOL "\n");
                        lastword[lastidx = 0] = '\0';
                        col = 1;
                    }
                    else
                    {
                        }


        if (local || carrier())
        {
            if (*PRM(chat_fend))
                Display_File(0, NULL, PRM(chat_fend));
            else
                Puts(chat_end);
        }
    }

    logit(log_chat, exiting, the_chatmode);


    if (timeoff < (dword)(time(NULL) + 60L))
        timeoff = time(NULL) + 60L;

    do_timecheck = savedotc;


    if ((fd = shopen(prmname, O_RDWR | O_BINARY | O_NOINHERIT)) != -1)
    {
        write(fd, (char *)&prm, sizeof(struct m_pointers));
        close(fd);
    }
}

static int pm_getch(void)
{
    for (;;)
    {
        if (loc_kbhit())
            return (loc_getch());

        if (mdm_avail())
            return (mdm_ggetcw());
    }
}
