// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>


    word last_found = 0;
    word strlen_search = strlen(search);
    byte l1, l2;
    word i;

    if (string)
    {
        while (*string)
        {
            else
            {
                if (last_found != 0)
                {
                    string -= last_found - 1;
                    last_found = 0;
                    continue;
                }
            }

            string += l1;

            if (last_found == strlen_search)
                return (string - last_found);
        }
    }

    return (NULL);
}
