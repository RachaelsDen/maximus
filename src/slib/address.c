// SPDX-License-Identifier: GPL-2.0-or-later


#include "msgapi.h"
#include "prog.h"
#include <stdio.h>

byte *_fast Address(NETADDR *a)
{
    static char temp[30];
    char point[10];

    sprintf(point, ".%hu", (unsigned)a->point);

    sprintf(temp, "%hu:%hu/%hu%s", (unsigned)a->zone, (unsigned)a->net, (unsigned)a->node,
            a->point ? point : "");

    return temp;
}
