// SPDX-License-Identifier: GPL-2.0-or-later



#include "fctype.h"
#include "prog.h"
#include <stdio.h>
#include <string.h>

#define MAX_SEARCH 16

int _fast stricmpm(char *string, char *search[], int stopbit)
{
    int x;
    int max_keys;
    int last_found[MAX_SEARCH];
    int strlen_search[MAX_SEARCH];
    int ret_val = 0;
    char lower_string;

    for (max_keys = 0; (search[max_keys] != NULL) && (max_keys < MAX_SEARCH); max_keys++)
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
                if ((last_found[x] != -1) && (lower_string == f_tolwr(search[x][last_found[x]])))
                    last_found[x]++;
                else
                    last_found[x] = -1;

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
