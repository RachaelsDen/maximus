// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_rest.c,v 1.1.1.1 2002/10/01 17:52:00 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS

#include "max_file.h"
#include "max_msg.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <share.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef __MSDOS__

int System_Restart(char *restart_name)
{
    struct _restart *rst;

    char temp[PATHLEN];

    int type;
    int userfile;


    usr.delflag = usr.df_save;


    sprintf(temp, restarxx_bbs, original_path, task_num);

    if ((userfile = shopen(temp, O_RDONLY | O_BINARY)) == -1)
    {
        cant_open(temp);
        quit(ERROR_FILE);
    }

    if ((rst = malloc(sizeof(struct _restart))) == NULL)
    {
        logit(mem_none);
        quit(ERROR_CRITICAL);
    }

    read(userfile, (char *)rst, sizeof(struct _restart));
    close(userfile);


    TagReadTagFile(&mtm);


    caller_online = TRUE;


    if (local)
        prm.flags &= ~FLAG_statusline;


    if (rst->ctltype != CTL_NONE)
    {
        struct _proto *pro;
        word fn;
        word got = 0;

        if ((pro = malloc(sizeof(struct _proto))) != NULL && FindProtocol(rst->last_protocol, pro))
        {
            FENTRY fent;

            MaxReadLog(pro, rst->ctltype == CTL_UPLOAD);
            free(pro);

            for (fn = 0; GetFileEntry(fn, &fent); fn++)
            {
                if (fent.fFlags & FFLAG_SENT)
                {
                    if (!got)
                        got = 1;
                    MaxSentFile(fn, TRUE, -1L);
                }
            }

            for (fn = 0; GetFileEntry(fn, &fent); fn++)
            {
                if ((got != -1) && (fent.fFlags & FFLAG_GOT))
                {
                    got = -1;
                    File_Process_Uploads(0L, rst->last_protocol, FAS(fah, uppath));
                    break;
                }
            }

            if (got == 1)
            {
                Puts(xfercomplete);
                Putc('\n');
            }
            else if (got == 0)
                Puts(xferaborted);

            Free_Filenames_Buffer(0);
        }
    }

    type = rst->restart_type;
    free(rst);

    return type;
}


    memset(rst, '\0', sizeof(struct _restart));

    rst->rst_ver = RST_VER;
    rst->origusr = origusr;
    rst->restart_type = restart_type;
    strcpy(rst->restart_name, restart_name ? restart_name : PRM(first_menu));
    strcpy(rst->menupath, menupath);
    strcpy(rst->menuname, CurrentMenuName());
    strcpy(rst->firstname, firstname);
    rst->next_ludate = next_ludate;
    strcpy(rst->last_onexit, last_onexit);
    rst->laston = usr.ludate.msg_st;

    strcpy(rst->fix_menupath, fix_menupath);
    rst->mn_dirty = mn_dirty;

    rst->lastmenu = lastmenu;
    rst->local = local;
    rst->port = port;
    rst->snoop = snoop;
    rst->keyboard = keyboard;
    rst->protocol_letter = protocol_letter;
    rst->chatreq = chatreq;

    rst->no_zmodem = no_zmodem;
    rst->timeon = timeon;
    rst->timeoff = timeoff;
    rst->timestart = timestart;
    rst->restart_offset = restart_offset;

    rst->usr_time = usrtime;
    rst->ultoday = ultoday;
    rst->written_echomail = written_echomail;
    rst->written_matrix = written_matrix;
    rst->current_baud = current_baud;
    rst->steady_baud = steady_baud;
    rst->date_newfile = date_newfile;
    rst->steady_baud_l = steady_baud_l;
    rst->baud = baud;
    rst->max_time = max_time;
    rst->getoff = getoff;
    rst->event_num = event_num;

    rst->ctltype = ctltype;
    strcpy(rst->parm, parm);
    rst->starttime = starttime;

    if (rst_offset == -1L)
        rst_offset = 0L;

    sprintf(temp, restarxx_bbs, original_path, task_num);

    if ((file = sopen(temp, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_DENYNONE,
                      S_IREAD | S_IWRITE)) == -1)
        cant_open(temp);
    else
    {
        write(file, (char *)rst, sizeof(struct _restart));
        close(file);
    }

    free(rst);

    save_tag_list(NULL);
}

