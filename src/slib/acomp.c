// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int _stdc AreaNameComp(byte *a1, byte *a2)
{
    int id1 = isdigit(*a1), id2 = isdigit(*a2);
    long at1, at2;

    if (id1 || id2)
    {

        at1 = atol(a1);
        at2 = atol(a2);

        if (at1 != at2)
            return (int)(at1 - at2);
    }

#if defined(UNIX)
    return strcasecmp(a1, a2);
#else
    return (stricmp(a1, a2));
#endif
}
