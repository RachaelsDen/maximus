// SPDX-License-Identifier: GPL-2.0-or-later



#include "dr.h"
#include "prog.h"
#include <string.h>

int _fast make_dir(char *dirC)
{
    char temp[PATHLEN], save[PATHLEN], *s;
    char *dir;
    int x;

    dir = fixPathDup(dirC);

    strcpy(save, dir);

    if (save[x = strlen(save) - 1] == '\\' && strlen(save) != 3)
        save[x] = '\0';

    strcpy(s = temp, save);

    while (s)
    {
        if ((s = strchr(s, '\\')) == NULL)
            break;

        if (s == temp || (s == temp + 2 && *temp && temp[1] == ':'))
        {
            s++;
            continue;
        }

        *s++ = '\0';

        if (!direxist(temp) && mkdir(temp) == -1)
        {
            fixPathDupFree(dirC, dir);
            return -1;
        }

        strcpy(temp, save);
    }

    fixPathDupFree(dirC, dir);
    return (mkdir(temp));
}
