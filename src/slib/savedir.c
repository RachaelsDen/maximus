// SPDX-License-Identifier: GPL-2.0-or-later



#include "alc.h"
#include "dr.h"
#include "prog.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int _fast Save_Dir(char *orig_disk, char *orig_path[], char *path)
{
    char temp[PATHLEN];
    char dn;
    char *p;

    if (*orig_disk == -1)
        *orig_disk = (char)getdisk();

    strcpy(temp, path);

    if (isalpha(*temp) && temp[1] == ':')
        dn = (char)(toupper(*temp) - 'A');
    else
        dn = (char)getdisk();

    if ((p = strchr(temp, ':')) != NULL)
    {
        if (p == temp + 1)
        {
            setdisk(toupper(*temp) - 'A');
            chdir(temp + 2);
        }
    }
    else
        chdir(temp);

    return 0;
}

void _fast Restore_Dir(char *orig_disk, char *orig_path[])
{
    int x;

    for (x = 0; x < MAX_DRIVES; x++)
    {
        if (orig_path[x] && *orig_path[x])
        {
            chdir(orig_path[x]);

            free(orig_path[x]);
            orig_path[x] = NULL;
        }
    }

    setdisk(*orig_disk);

    *orig_disk = -1;
}
