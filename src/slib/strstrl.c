// SPDX-License-Identifier: GPL-2.0-or-later



#include "fctype.h"
#include "prog.h"
#include <stdio.h>
#include <string.h>

#define MAX_LSEARCH 32

long _fast stristrml(char *string, char *search[], long stopbit)
{
    int x;
    int max_keys;
    int last_found[MAX_LSEARCH];
    int strlen_search[MAX_LSEARCH];
    long ret_val = 0;
    char lower_string;

    for (max_keys = 0; (search[max_keys] != NULL) && (max_keys < MAX_LSEARCH); max_keys++)
    {
        strlen_search[max_keys] = strlen(search[max_keys]);
        last_found[max_keys] = 0;
    }

    if (string)
    {
        while (*string)
        {
            lower_string = f_tolwr(*string);

            for (x = 0; x < max_keys; x++)
            {
                if (lower_string == f_tolwr(search[x][last_found[x]]))
                    last_found[x]++;
                else
                {
                    if (last_found[x] != 0)
                    {
                        last_found[x] = 0;
                        continue;
                    }
                }

                if (last_found[x] == strlen_search[x])
                {
                    last_found[x] = 0;
                    ret_val |= 1 << x;

                    if (stopbit & (1 << x))
                        return (ret_val);
                }
            }

            string++;
        }
    }

    return (ret_val);
}
