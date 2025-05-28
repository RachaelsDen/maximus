// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <stdio.h>
#include <string.h>


char *_fast Area_Name(int area)
{
    static char aname[3];

    aname[0] = (char)(area >> CHAR_BITS);
    aname[1] = (char)(area & 0x00ff);
    aname[2] = '\0';

    if (aname[0] == '0' && aname[1])
    {
        aname[0] = aname[1];
        aname[1] = '\0';
    }

    return strupr(aname);
}


int _fast Set_Area_Name(char *aname)
{
    int area;

    strupr(aname);

    if ((aname[0] >= 'A' && aname[0] <= 'Z') || (aname[0] >= '0' && aname[0] <= '9'))
    {
        area = aname[0] << CHAR_BITS;

        if ((aname[1] >= 'A' && aname[1] <= 'Z') || (aname[1] >= '0' && aname[1] <= '9'))
            area |= aname[1];
        else
            area = ('0' << CHAR_BITS) | aname[0];
    }
    else
        area = ('0' << CHAR_BITS) | '0';

    return area;
}
