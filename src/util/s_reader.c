// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_reader.c,v 1.1.1.1 2002/10/01 17:57:52 sdudley Exp $";
#pragma on(unreferenced)


#define SILT
#define NOVARS
#define NOINIT

#include "dr.h"
#include "max.h"
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

int Parse_Reader(FILE *ctlfile)
{

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
            else if (eqstri(p, "end"))
                break;
            else if (eqstri(p, "archivers"))
            {
                getword(line, p, ctl_delim, 2);
                Make_Filename(prm.arc_ctl, p);
            }
            else if (eqstri(p, "packet"))
            {
                getword(line, p, ctl_delim, 3);
                p[8] = '\0';
                Make_String(prm.olr_name, p);
            }
            else if (eqstri(p, "work"))
            {
                getword(line, p, ctl_delim, 3);
                Make_Path(prm.olr_dir, p);

                if (!direxist(p))
                    makedir(p);
            }
            else if (eqstri(p, "phone"))
            {
                Make_String(prm.phone_num, fchar(line, ctl_delim, 3));
            }
            else if (eqstri(p, "max"))
            {
                getword(line, p, ctl_delim, 3);
                prm.max_pack = (word)atoi(p);
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
