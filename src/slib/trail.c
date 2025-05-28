// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <string.h>

char *_fast Strip_Trailing(char *str, char strip)
{
    int x;

    if (str && *str && str[x = strlen(str) - 1] == strip)
        str[x] = '\0';

    return str;
}

char *_fast Add_Trailing(char *str, char add)
{
    int x;

    if (!str)
        return NULL;

    if (*str)
    {
        if (str[x = strlen(str) - 1] != add)
        {
            str[x + 1] = add;
            str[x + 2] = '\0';
        }
    }
    else
    {
        str[0] = add;
        str[1] = '\0';
    }

    return str;
}
