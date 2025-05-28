// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <stdio.h>
#include <string.h>

char *_fast strrstr(char *str, char *delim)
{
    char *p;

    for (p = str + strlen(str) - 1; p >= str; p--)
        if (strchr(delim, *p))
            return p;

    return NULL;
}
