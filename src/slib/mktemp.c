// SPDX-License-Identifier: GPL-2.0-or-later


#ifdef __WATCOMC__

#include "prog.h"
#include <string.h>

char *mktemp(char *tp)
{
    char *p;
    char *cp;

    p = tp + strlen(tp) - 6;
    strcpy(p, "AA.AAA");

    cp = p;

    while (fexist(tp))
    {
        if (*cp == 'Z')
        {
            *cp = 'A';
            cp++;
        }

        cp++;
    }

    return tp;
}

#endif
