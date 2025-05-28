// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_out.c,v 1.2 2003/06/06 01:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#include "mm.h"
#include "prog.h"
#include <conio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(NT) || defined(UNIX)
#include "ntcomm.h"
#else
#define COMMAPI_VER 0
#endif

int last_cc = -1;
char strng[20];
static char *szOutString = NULL;

void OutputAllocStr(void)
{
    if (szOutString == NULL && (szOutString = malloc(MAX_PRINTF)) == NULL)
    {
        printf(printfstringtoolong, "P");
        quit(ERROR_CRITICAL);
    }
}

void OutputFreeStr(void)
{
    free(szOutString);
    szOutString = NULL;
}


int _stdc Lprintf(char *format, ...)
{
    va_list var_args;
    int x;

    char string[MAX_PRINTF];

    if (strlen(format) >= MAX_PRINTF)
    {
        printf(printfstringtoolong, "Lp");
        return -1;
    }

    va_start(var_args, format);
    x = vsprintf(string, format, var_args);
    va_end(var_args);

    Lputs(string);
    return x;
}


    if (in_file_xfer)
        vbuf_flush();
}
