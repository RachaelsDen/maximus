// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <stdio.h>

#define MAXSLEN 255

void _fast c_encode(char *str, char *iarray, int len, int key)
{
    int x, c, inc;

    for (x = 0, inc = TRUE, c = 1; x < len; x++)
    {
        if (inc)
        {
            iarray[x] = (char)(str[x] - key + c);
            inc = FALSE;
        }
        else
        {
            iarray[x] = (char)(str[x] + key - c);
            inc = TRUE;
            c++;
        }
    }

    iarray[x] = -1;
}

void _fast c_decode(char *iarray, char *str, int key)
{
    int x, c, inc;

    for (x = 0, inc = TRUE, c = 1; iarray[x] != -1; x++)
    {
        if (inc)
        {
            str[x] = (char)(iarray[x] + key - c);
            inc = FALSE;
        }
        else
        {
            str[x] = (char)(iarray[x] - key + c);
            inc = TRUE;
            c++;
        }
    }
    str[x] = '\0';
}
