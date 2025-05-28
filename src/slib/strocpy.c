// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <string.h>

char *_fast strocpy(char *d, char *s)
{
    char *orig = s;

    memmove(d, s, strlen(s) + 1);
    return orig;
}
