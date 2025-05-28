// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_log.c,v 1.1.1.1 2002/10/01 17:56:25 sdudley Exp $";
#pragma on(unreferenced)

#include "max.h"
#include "prog.h"
#include "squish.h"
#include <fcntl.h>
#include <share.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *logfile = NULL;
static char *slogfmt = "%c %02d %s %02d:%02d:%02d %s %s\n";


void cdecl OS2FAR S_LogLine(char OS2FAR *string)
{
    time_t gmt;
    struct tm *localt;
    static char log_line[MAX_LOG_LEN];

    gmt = time(NULL);
    localt = localtime(&gmt);

    (void)sprintf(log_line, slogfmt, *string, localt->tm_mday, months_ab[localt->tm_mon],
                  localt->tm_hour, localt->tm_min, localt->tm_sec, "SQSH", string + 1);

    if (logfile)
    {
        struct _ll *ll;

        for (ll = loglevels; ll->ch; ll++)
            if (ll->ch == (byte)*log_line)
                break;

        if ((!ll->ch) || (ll->ch && config.loglevel >= ll->lev))
            (void)fputs(log_line, logfile);
    }

    if (*string == '!' || *string == '@')
    {
        if (logfile)
        {
            (void)fflush(logfile);
            flush_handle(logfile);
        }

        (void)printf("\r                                                              "
                     "             \r%s",
                     log_line);
    }
}

