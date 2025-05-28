// SPDX-License-Identifier: GPL-2.0-or-later


#include "alc.h"
#include "arc_def.h"
#include "prog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _fast Form_Archiver_Cmd(char *arcname, char *pktname, char *cmd, char *org)
{
    char *p;

    if (!arcname || !pktname || !cmd || !org)
    {
        *cmd = '\0';
        return;
    }

    strcpy(cmd, org);

    for (p = cmd; (p = strchr(cmd, '%')) != NULL;)
    {
        switch (p[1])
        {
        case 'a':
            strocpy(p + strlen(arcname), p + 2);
            memmove(p, arcname, strlen(arcname));
            break;

        case 'f':
            strocpy(p + strlen(pktname), p + 2);
            memmove(p, pktname, strlen(pktname));
            break;

        case '%':
            p++;
            strocpy(p, p + 1);
            break;
        }
    }
}
