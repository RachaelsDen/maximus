// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"

#define CENTURY 19


int _fast zeller(int m, int d, int y)
{
    int f;

    if (m > 2)
        m -= 2;
    else
    {
        m += 10;
        y--;
    }

    f = (((13 * m - 1) / 5) + (y / 4) + (CENTURY / 4) + y + d - (2 * CENTURY)) % 7;

    return f;
}
