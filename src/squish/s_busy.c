// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_busy.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#include "keys.h"
#include "msgapi.h"
#include "prog.h"
#include "squish.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static char *nodot_bsy = "bsy";
static char *dot_bsy = ".bsy";


int BusyFileOpenNN(NETADDR *n, int wait)
{
    char temp[PATHLEN];

    return (BusyFileOpen(MakeBusyName(n, temp), wait));
}


static char *near bsy_extension(char *name)
{
    char *bsyname, *point;


    bsyname = smalloc(strlen(name) + 10);
    (void)strcpy(bsyname, name);

    point = strrchr(bsyname, '.');


        if ((config.flag & FLAG_FRODO) && isxdigit(point[1]) && isxdigit(point[2]) &&
            isxdigit(point[3]))
        {
        }
        else
        {
            (void)strcpy(point, dot_bsy);
        }
    }

    return bsyname;
}


    if ((config.flag & FLAG_BSY) == 0)
        return 0;

    bsyname = bsy_extension(name);


    while ((bfile = cshopen(bsyname, O_EXCL | O_CREAT | O_WRONLY | O_BINARY)) == -1)
    {
        if (!wait)
            return -1;

        dir = sstrdup(bsyname);

        point = strrchr(dir, PATH_DELIM);

        if (point)
            *point = '\0';

        (void)make_dir(dir);
        free(dir);

        (void)sprintf(temp, " (%s busy; wait)", name);
        (void)printf(temp);

        while (fexist(bsyname))
        {
            if (khit() && kgetch() == K_ESC)
                break;

            tdelay(200);
        }

        for (bs = strlen(temp); bs--;)
            (void)printf("\b \b");
    }

    if (bfile != -1)
        (void)close(bfile);

    free(bsyname);
    return 0;
}


int BusyFileExist(NETADDR *n)
{
    char bsyname[PATHLEN];
    char *fname;

    if ((config.flag & (FLAG_FRODO | FLAG_BSY)) != FLAG_BSY)
        return FALSE;

    fname = bsy_extension(MakeBusyName(n, bsyname));

    return (fexist(fname));
}
