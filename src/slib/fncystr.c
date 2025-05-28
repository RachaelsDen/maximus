// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <ctype.h>
#include <stdio.h>

char *_stdc fancy_str(char *str)
{
    char *s;
    int lower = FALSE;

    s = str;

    if (s)
    {
        while (*s)
        {
            if (lower)
                *s = (char)tolower(*s);
            else
                *s = (char)toupper(*s);

            lower = isalnum((int)*s++);
        }
    }

    return str;
}
