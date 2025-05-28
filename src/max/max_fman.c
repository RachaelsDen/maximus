// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_fman.c,v 1.1.1.1 2002/10/01 17:51:38 sdudley Exp $";
#pragma on(unreferenced)


#include "max_area.h"
#include "mm.h"
#include "prog.h"
#include <dos.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>


    user = usr;


    user.max2priv = max2priv(user.priv);

    user.timeremaining = timeleft();


    if (local)

        if (lcopy(fromfile, tofile) == 0)
        {
            unlink(fromfile);
            return 0;
        }
        else
            return -1;
    }

    return 0;
}

int cdecl utime(char *name, struct utimbuf *times)
{
    int handle;
    struct date d;
    struct time t;
    struct ftime ft;

    unixtodos(times->modtime, &d, &t);
    ft.ft_tsec = t.ti_sec / 2;
    ft.ft_min = t.ti_min;
    ft.ft_hour = t.ti_hour;
    ft.ft_day = d.da_day;
    ft.ft_month = d.da_mon;
    ft.ft_year = d.da_year - 1980;

    if ((handle = shopen(name, O_RDWR | O_NOINHERIT)) == -1)
        return -1;

    setftime(handle, &ft);
    close(handle);
    return 0;
}

#endif
