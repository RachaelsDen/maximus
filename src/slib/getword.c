// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <stdio.h>
#include <string.h>

int _fast getword(char *strng, char *dest, char *delim, int findword)
{
    int x, isw, sl_d, sl_s, wordno = 0;

    char *string, *oldstring, *firstchar;

    if (findword == 0)
    {
        *dest = '\0';
        return 0;
    }

    string = oldstring = strng;

    sl_d = strlen(delim);

    for (string = strng; *string; string++)
    {
        for (x = 0, isw = 0; x <= sl_d; x++)
            if (*string == delim[x])
                isw = 1;

        if (isw == 0)
        {
            oldstring = string;
            break;
        }
    }

    sl_s = strlen(string);

    for (firstchar = NULL, wordno = 0; (string - oldstring) <= sl_s; string++)
    {
        for (x = 0, isw = 0; x <= sl_d; x++)
            if (*string == delim[x])
            {
                isw = 1;
                break;
            }

        if ((!isw) && (string == oldstring))
            wordno++;

        if (wordno != findword)
        {
            if (isw && (string != oldstring))
            {
                for (x = 0, isw = 0; x <= sl_d; x++)
                    if (*(string + 1) == delim[x])
                    {
                        isw = 1;
                        break;
                    }

                if (isw == 0)
                    wordno++;
            }
        }
        else
        {
            if (isw && (string != oldstring))
            {
                for (x = 0, isw = 0; x <= sl_d; x++)
                    if (*(string - 1) == delim[x])
                    {
                        isw = 1;
                        break;
                    }

                if (isw == 0)
                    wordno++;
            }
        }

        if ((wordno == findword) && (firstchar == NULL))
            firstchar = string;

        if (wordno == (findword + 1))
        {
            strncpy(dest, (firstchar == oldstring ? firstchar : ++firstchar),
                    (unsigned int)(string - firstchar));
            dest[(unsigned int)(string - firstchar)] = '\0';
            break;
        }
    }

    if (firstchar == NULL || (firstchar && *firstchar == '\0'))
        *dest = '\0';

    return ((int)(firstchar - strng));
}
