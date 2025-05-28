// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: disp_dat.c,v 1.2 2003/06/04 23:12:08 wesgarland Exp $";
#pragma on(unreferenced)


#include "display.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef UNIX
        sprintf(d->scratch, "%s.BBS", PRM(quote));
#else
        sprintf(d->scratch, "%s.bbs", PRM(quote));
#endif

        if ((quotefile = shfopen(d->scratch, fopen_read, O_RDONLY)) == NULL)
            return 0;

        do
        {
            fseek(quotefile, bstats.quote_pos, SEEK_SET);

            while ((p = fgets(d->scratch, PATHLEN, quotefile)) != NULL)
            {
                Trim_Line(d->scratch);

                if (!*d->scratch)
                    break;

                Printf("%s\n", d->scratch);
            }

        Puts(usrname);
        break;

        longtime = time(NULL);
        localt = localtime(&longtime);

        strftime(d->scratch, 15, "%d %b %y", localt);
        Puts(d->scratch);
        break;

        Puts(firstname);
        break;

        Printf(pu, usr.time + timeonline());
        break;

        if (d->ck_abort)
            Mdm_flush_ck();
        else
            Mdm_flush();

        mdm_hangup();
        break;

        strftime(d->scratch, 26, asctime_format, localtime((time_t *)(&timeoff)));
        Puts(d->scratch);
        break;

        Printf(pl, usr.downtoday - ultoday);
        break;

        d->allanswers = TRUE;
        break;

        Printf(plu, usr.up);
        break;

        Printf("%lu:%lu", (long)(usr.up == 0 ? 0L : 1L),
               (long)(usr.down / (usr.up == 0L ? 1L : usr.up)));
        break;
    }

    return 0;
}
