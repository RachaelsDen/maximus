// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <string.h>

char *_fast strnncpy(char *to, char *from, int n)
{
    strncpy(to, from, n);

    if (strlen(from) >= n - 1)
        to[n - 1] = '\0';

    return to;
}
