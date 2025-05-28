// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <ctype.h>
#include <string.h>

char *_fast cstrupr(char *s)
{
    char *orig = s;

    for (; *s; s++)
    {
        if (ischin(s))
            s++;
        else
            *s = (char)toupper(*s);
    }

    return orig;
}

char *_fast cstrlwr(char *s)
{
    char *orig = s;

    for (; *s; s++)
    {
        if (ischin(s))
            s++;
        else
            *s = (char)tolower(*s);
    }

    return orig;
}

char *_stdc cfancy_str(char *str)
{
    char *s;
    int lower = FALSE;

    s = str;

    if (s)
    {
        while (*s)
        {
            if (ischin(s))
            {
                s += 2;
                lower = TRUE;
            }
            else
            {
                *s = (char)(lower ? tolower(*s) : toupper(*s));
                lower = isalnum(*s++);
            }
        }
    }

    return str;
}
