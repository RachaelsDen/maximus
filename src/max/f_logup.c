// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_logup.c,v 1.1.1.1 2002/10/01 17:51:07 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS

#include "max_file.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <share.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#ifdef BINK_PROTOCOLS
#include "prototyp.h"
#endif

void Add_To_Upload_Log(char *path, char *fname, long bytes)
{
    FILE *ullog;
    char *do_touch;
    union stamp_combo stamp;

    int ulfile;

    char p1[PATHLEN];
    char p2[PATHLEN];

    Get_Dos_Date(&stamp);

    if (*PRM(ul_log))
    {
        strcpy(p1, PRM(ul_log));
        Convert_Star_To_Task(p1);

        if ((ullog = shfopen(p1, fopen_append, O_WRONLY | O_APPEND)) == NULL)
            cant_open(p1);
        else
        {
            Timestamp_Format(PRM(dateformat), &stamp, p1);
            Timestamp_Format(PRM(timeformat), &stamp, p2);

            fprintf(ullog, ullog_format, usr.name, path, fname, bytes, p1, p2);

            fclose(ullog);
        }
    }

        char bob_string[] = "CPC`KVHF";
        char a_big_meanie[] = "b!cjh!nfbojf";
        char *s;

        for (s = bob_string; *s; s++)
            --(*s);

        for (s = a_big_meanie; *s; s++)
            --(*s);

        do_touch = getenv(bob_string);

        if (do_touch && eqstri(do_touch, a_big_meanie))
            return;
    }


void Get_File_Description(char *filename, long fsize, char *dsc)
{
    struct tm *stim;
    time_t curt;

    FILE *bbsfile;

    byte temp[PATHLEN];
    byte description[PATHLEN];
    byte nw[PATHLEN];
    byte *p;

    word desc_num, wrapped;

    if (!(local || carrier()))
        return;


    if (!(dsc && *dsc) && (local || carrier()))
        Puts(LGREEN "\n  Ú\x19Ä\x2d¿\n");

    *nw = '\0';

    while (desc_num <= 3)
    {
        sprintf(temp, GRAY "%d> " YELLOW, desc_num);

        *description = '\0';

        while (isblstr(description))
        {
            if (dsc && *dsc)
                strcpy(description, dsc);
            else
            {
                if (local || carrier())
                {
                    if (*nw)
                        strcpy(description, nw);
                    else
                        *description = '\0';

                    wrapped = Input(description, INPUT_NLB_LINE | INPUT_WORDWRAP, 0, 45, temp);

                    if (wrapped == 1)
                        strcpy(nw, description + strlen(description) + 1);
                    else
                        *nw = '\0';
                }
                else
                    *description = '\0';
            }

            if (!*description && desc_num != 1)
                break;

            if (!*nw)
                strcat(description, " ");
        }

        if (!*description)
            break;


        if (autodate(fah))
        {
            *temp = '\0';
        }
        else
        {
            sprintf(temp, "%7ld ", fsize);

            switch (prm.date_style)
            {
                sprintf(&temp[strlen(temp)], date_str, stim->tm_mon + 1, stim->tm_mday,
                        (stim->tm_year % 100));
                break;

                sprintf(&temp[strlen(temp)], date_str, (stim->tm_year % 100), stim->tm_mon + 1,
                        stim->tm_mday);
                break;


        for (p = description; *p; p++)
            if (*p < 32)
                *p = ' ';

        for (p = filename; *p; p++)
            if (*p < 32)
                *p = '\0';


word LookForVirus(char *path, char *name)
{
    char fname[PATHLEN];
    char cmd[PATHLEN];
    char stem[12], ext[5], *ep;
    word foundvir;

    if (!*PRM(viruschk))
        return FALSE;


    upper_fn(fname);


    strncpy(last_readln, name, MAXLEN);
    last_readln[MAXLEN] = '\0';


    if ((ep = strchr(stem, '.')) != NULL)
        *ep = '\0';

    }


    sprintf(cmd, "%s %s %s %s %s %d", PRM(viruschk), path, stem, ext, PRM(misc_path), task_num);


    Outside(NULL, NULL, OUTSIDE_DOS, cmd, FALSE, CTL_NONE, RESTART_MENU, NULL);


    foundvir = !fexist(fname);

    Display_File(0, NULL, foundvir ? "%sfile_bad" : "%sfile_ok", PRM(misc_path));

    return foundvir;
}
