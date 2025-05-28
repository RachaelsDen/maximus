// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_system.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define SILT
#define NOVARS
#define NOINIT

#include "dr.h"
#include "max.h"
#include "opusprm.h"
#include "prog.h"
#include "silt.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int Parse_System(FILE *ctlfile)
{
    int x;

    char *s2;

    linenum++;

    while (fgets(line, MAX_LINE, ctlfile))
    {
        Strip_Comment(line);

        if (*line)
        {
            strcpy(temp, line);

            getword(line, p, ctl_delim, 1);

            if (!*p)
                ;

                    if ((x = open(temp, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE)) != -1)
                        close(x);
                }
                else if (eqstri(p, "outbound"))
                {
                    s2 = fchar(line, ctl_delim, 3);
                    Make_Path(prm.junk, s2);
                }
                else if (eqstri(p, "inbound"))
                {
                    s2 = fchar(line, ctl_delim, 3);
                    Make_Path(prm.inbound_files, s2);
                }
                else if (eqstri(p, "ipc"))
                {
                    s2 = fchar(line, ctl_delim, 3);
                    Make_Path(prm.ipc_path, s2);

                    if (!direxist(s2))
                        makedir(s2);
                }
                else
                    Unknown_Ctl(linenum, p);
            }
            else if ((x = 1, eqstri(p, "uses")) || (x = 2, eqstri(p, "file")))
            {
                getword(line, p, ctl_delim, 2);
                s2 = fchar(line, ctl_delim, 3);

                Add_Filename(s2);

                if (eqstri(p, "password"))
                    Make_Filename(prm.user_file, s2) else if (eqstri(p, "access"))
                        Make_Filename(prm.access, s2) else if (eqstri(p, "callers"))
                            Make_Filename(prm.caller_log, s2) else Unknown_Ctl(linenum, p);

            {
                getword(line, p, ctl_delim, 2);

                if (eqstri(p, "file"))
                {
                    char *p;

                    strcpy(temp, fchar(line, ctl_delim, 3));
                    Make_Filename(prm.log_name, temp);

                prm.task_num = (char)atoi(fchar(line, ctl_delim, 2));
            {
                getword(line, p, ctl_delim, 2);

                prm.flags |= FLAG_watchdog;
            else if (eqstri(p, "swap"))
                prm.flags2 |= FLAG2_SWAPOUT;
                    prm.flags |= FLAG_close_sf;
                else
                    Unknown_Ctl(linenum, p);
            }
            else if (eqstri(p, "no"))
            {
                getword(line, p, ctl_delim, 2);

                if (eqstri(p, "share") || eqstri(p, "share.exe"))
                    prm.flags2 |= FLAG2_noshare;
                else if (eqstri(p, "password"))
                    prm.flags2 |= FLAG2_NOENCRYPT;
                else
                    Unknown_Ctl(linenum, p);
            }
            else if (eqstri(p, "app") || eqstri(p, "application"))
                ;
            else
                Unknown_Ctl(linenum, p);
        }

        linenum++;
    }

    linenum++;

    return 0;
}
