// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <stdio.h>

#define MAXSLEN 255

void _fast encode(char *str, int *iarray, int len, int key)
{
    int x, c, inc, in[MAXSLEN];

    for (x = 0, inc = TRUE, c = 1; x < len; x++)
    {
        in[x] = str[x];
        if (inc)
        {
            iarray[x] = in[x] - key + c;
            inc = FALSE;
        }
        else
        {
            iarray[x] = in[x] + key - c;
            inc = TRUE;
            c++;
        }
    }
    iarray[x] = -1;
}

void _fast decode(int *iarray, char *str, int key)
{
    int x, c, inc, in[MAXSLEN];

    for (x = 0, inc = TRUE, c = 1; iarray[x] != -1; x++)
    {
        if (inc)
        {
            in[x] = iarray[x] + key - c;
            inc = FALSE;
        }
        else
        {
            in[x] = iarray[x] - key + c;
            inc = TRUE;
            c++;
        }
        str[x] = (char)in[x];
    }
    str[x] = '\0';
}
