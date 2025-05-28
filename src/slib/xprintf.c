// SPDX-License-Identifier: GPL-2.0-or-later



#include "alc.h"
#include "prog.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _stdc xprintf(char *format, ...)
{
    va_list var_args;
    char *string;
    int x;

    string = (char *)malloc(256);

    if (string == NULL || strlen(format) > 256)
    {
        if (string)
            free(string);

#ifndef NDEBUG
        printf("XPRINTF: [Out of memory!]\n");
#endif
        return -1;
    }

    va_start(var_args, format);
    vsprintf(string, format, var_args);
    va_end(var_args);

    xputs(string);
    x = strlen(string);
    free(string);

    return x;
}
