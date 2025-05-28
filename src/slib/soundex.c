// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <ctype.h>
#include <stdio.h>

    char *table = "01230120022455012623010202";

    char *sdx = soundexbuf, lastchr = ' ';

    while (*str)
    {
        if (isalpha(*str) && (*str != lastchr))
        {
            *sdx = *(table + toupper(*str) - 'A');

            if ((*sdx != '0') && (*sdx != lastchr))
                lastchr = *sdx++;
        }

        str++;
    }

    *sdx = '\0';

    return (soundexbuf);
}
