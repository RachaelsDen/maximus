// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_misc.c,v 1.1.1.1 2002/10/01 17:51:08 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "max_file.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void Dont_Use_Wildcards(char *name)
{
    Printf(no_wildcard, name);

    Puts(no_wc1);
    Puts(no_wc2);
    Press_ENTER();
}

char *Remove_Files_Entry(char *filename, char *description)
{
    FILE *infilesbbs, *outfilesbbs;

    byte *line;
    byte *temp;
    byte poo_name[PATHLEN];
    byte fromname[PATHLEN];

    word fnlen;

    fnlen = strlen(filename);
    upper_fn(filename);

    if (description)
        *description = '\0';

    if (*FAS(fah, filesbbs))
        strcpy(fromname, FAS(fah, filesbbs));
    else
        sprintf(fromname, ss, FAS(fah, downpath), files_bbs);

    if ((infilesbbs = shfopen(fromname, fopen_readb, O_RDONLY | O_BINARY)) == NULL)
    {
        cant_open(fromname);
        return NULL;
    }

    sprintf(poo_name, files_poo, PRM(temppath), task_num);

    if ((outfilesbbs = shfopen(poo_name, fopen_write, O_WRONLY | O_TRUNC | O_CREAT)) == NULL)
    {
        cant_open(poo_name);
        fclose(infilesbbs);
        return NULL;
    }

    if ((line = malloc(MAX_FBBS_ENTRY)) == NULL || (temp = malloc(PATHLEN)) == NULL)
    {
        if (line)
            free(line);

        logit(mem_none);
        fclose(outfilesbbs);
        fclose(infilesbbs);
        return NULL;
    }

    while (fbgets(line, MAX_FBBS_ENTRY, infilesbbs))
    {
        strcat(line, "\n");


            if (description)
                strcpy(description, line);
        }
        else
        {
            if (fputs(line, outfilesbbs) == EOF)
            {
                Printf(err_writ, poo_name);

                free(temp);
                free(line);
                fclose(outfilesbbs);
                fclose(infilesbbs);

                return NULL;
            }
        }
    }

    free(line);

    fclose(outfilesbbs);
    fclose(infilesbbs);


    if (*FAS(fah, filesbbs))
        unlink(fromname);
    else
        move_file(fromname, temp);


void CreateDate(char *out, union stamp_combo *date)
{
    switch (prm.date_style)
    {

    default:
    case -1:
    case 0:
        sprintf(out, date_str, date->msg_st.date.mo, date->msg_st.date.da,
                (date->msg_st.date.yr + 80) % 100);
        break;

    case 1:
        sprintf(out, date_str, date->msg_st.date.da, date->msg_st.date.mo,
                (date->msg_st.date.yr + 80) % 100);
        break;

    case 2:
    case 3:
        sprintf(out, prm.date_style == 2 ? date_str : datestr, (date->msg_st.date.yr + 80) % 100,
                date->msg_st.date.mo, date->msg_st.date.da);
        break;
    }
}


    scanfmt = scan_str;

    if (last->msg_st.date.mo == 0)
        last->msg_st.date.mo = 1;

    if (last->msg_st.date.da == 0)
        last->msg_st.date.da = 1;


    switch (prm.date_style)
    {
    default:
    case -1:
    case 0:
        a1 = piMonth;
        a2 = piDay;
        a3 = piYear;
        break;
    case 1:
        a1 = piDay;
        a2 = piMonth;
        a3 = piYear;
        break;
    case 2:
        a1 = piYear;
        a2 = piMonth;
        a3 = piDay;
        break;
    case 3:
        a1 = piYear;
        a2 = piMonth;
        a3 = piDay;
        scanfmt = datestr;
        break;
    }

    InputGets(temp, "%s%s: ", promptprefix, dtfmt);


    new_date->msg_st.time.hh = 0;
    new_date->msg_st.time.mm = 0;
    new_date->msg_st.time.ss = 0;


        new_date->msg_st.time = last->msg_st.time;
    }

    if (!*temp || (sscanf(temp, scanfmt, a1, a2, a3) == 3 && *piMonth >= 1 && *piMonth <= 12 &&
                   *piDay >= 1 && *piDay <= 31))
    {
        new_date->msg_st.date.mo = *piMonth;
        new_date->msg_st.date.da = *piDay;

            new_date->msg_st.date.yr = last->msg_st.date.yr;
            new_date->msg_st.date.yr = *piYear + 20;

        return 0;
    }
    else
    {
        Puts(bad_date);
        return -1;
    }
}

