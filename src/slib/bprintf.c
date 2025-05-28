// SPDX-License-Identifier: GPL-2.0-or-later


#include "bfile.h"
#include "prog.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

void _stdc Bprintf(BFILE bf, char *format, ...)
{
    char *out;
    va_list var_args;

    if ((out = malloc(strlen(format) + 240)) == NULL)
        return;

    va_start(var_args, format);
    vsprintf(out, format, var_args);
    va_end(var_args);

    Bwrite(bf, out, strlen(out));

    free(out);
}
