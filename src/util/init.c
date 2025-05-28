// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: init.c,v 1.1.1.1 2002/10/01 17:57:23 sdudley Exp $";
#pragma on(unreferenced)


#include "mecca.h"
#include "prog.h"
#include <stdio.h>
#include <string.h>

void Init_Table(void)
{
    int x, y;

    static int *set[NUM_NUMS + 1] = {
        NULL,       &num_gt,    &num_lt,    &num_eq,      &num_ne,       &num_ge, &num_le,
        &num_above, &num_below, &num_equal, &num_unequal, &num_notequal, &num_ae, &num_be};

    num_gt = num_lt = num_eq = num_ne = num_ge = num_le = num_above = num_below = num_equal =
        num_unequal = num_notequal = num_ae = num_be = -2;

    for (x = 0; x < verb_table_size; x++)
    {
        y = verbs[x].verbno;

        if (y >= 1 && y <= NUM_NUMS)
            *set[y] = x;
    }
}
