// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <stdio.h>

#define LESS -1
#define EQUAL 0
#define MORE 1

int _fast sbsearch(char *key, char *base[], unsigned int num)
{
    int x, lastx = -1, lasthi, lastlo;

    char *s, *t;

    lasthi = num;
    lastlo = 0;

    for (;;)
    {
        x = ((lasthi - lastlo) >> 1) + lastlo;

        if (lastx == x)
            return -1;

        lastx = x;

        for (s = key, t = base[x]; *s == *t; s++, t++)
            if (!*s)
