// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_util.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)

#include "dr.h"
#include "max_msg.h"
#include "prog.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Make_Clean_Directory(char *szDirName)
{
    Strip_Trailing(szDirName, PATH_DELIM);
    fixPathMove(szDirName);


    Add_Trailing(szDirName, PATH_DELIM);

    Clean_Directory(szDirName, FALSE);
    return 0;
}

extern char *qwk_path;

void Clean_Directory(char *szDirName, int rdir)
{
    FFIND *ff;
    char temp[PATHLEN];
    char *dot;
    int isQwk;

    fixPathMove(szDirName);
    isQwk = (szDirName == qwk_path);


            if (isQwk && !rdir && eqstrin(ff->szName, PRM(olr_name), strlen(PRM(olr_name))) &&
                (dot = strrchr(ff->szName, '.')) && eqstrin(dot + 1, "QW", 2))
                continue;

            strcpy(temp, szDirName);
            strcat(temp, ff->szName);

            unlink(temp);
        } while (FindNext(ff) == 0);

        FindClose(ff);
    }

