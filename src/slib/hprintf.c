// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <io.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _stdc hprintf(int file, char *format, ...)
{
    va_list var_args;
    char *string;
    int x, y;

    if (strlen(format) > 256)
        return -1;

    if ((string = (char *)malloc(256)) == NULL)
        return (-2);

    va_start(var_args, format);
    x = vsprintf(string, format, var_args);
    va_end(var_args);

    y = write(file, string, strlen(string));
    free(string);

    return (x == y ? x : -1);
}
