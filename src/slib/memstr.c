// SPDX-License-Identifier: GPL-2.0-or-later



#include "fctype.h"
#include "prog.h"
#include <stdio.h>

char *_fast memstr(char *string, char *search, unsigned lenstring, unsigned strlen_search)
{
    unsigned x;
    unsigned last_found;

    for (x = last_found = 0; x < lenstring; x++)
    {
        if (string[x] == search[last_found])
            last_found++;
        else
        {
            if (last_found != 0)
            {
                last_found = 0;
                x--;
                continue;
            }
        }

        if (last_found == strlen_search)
            return ((string + x) - strlen_search) + 1;
    }

    return (NULL);
}
