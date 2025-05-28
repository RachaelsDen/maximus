// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_intrin.c,v 1.1.1.1 2002/10/01 17:51:05 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "display.h"
#include "ffind.h"
#include "max_file.h"
#include "max_menu.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>

int Exec_File(int type, char **result, char *menuname)
{
    *result = NULL;

    switch (type)
    {
    case newfiles:
        *linebuf = '*';
        linebuf[1] = '\0';
        File_Locate();
        break;

    {
        strcpy(temp, PRM(protoname[protocol]));
    }
    else
    {
        for (ps = intern_proto; ps->name; ps++)
            if (ps->num == protocol)
            {
                strcpy(temp, ps->name);
                break;
            }
    }

    return temp;
}

long XferTime(sword protocol, long bytes)
{
    long cps, seconds;

    if (!bytes)
        return 0L;

    if (local || !baud)
        baud = 38400L;

    cps = baud / 10;
    seconds = bytes / cps;

    switch (protocol)
    {
        seconds = (seconds * 138) / 100;
        break;

        seconds = (seconds * 107) / 100;
        break;

    case PROTOCOL_YMODEMG:
        seconds = (seconds * 104) / 100;
        break;

        break;
    }

    return seconds;
}

void File_IsOffline(char *filename)
{
    Printf(file_offl, No_Path(fancy_fn(filename)));
    *filename = '\0';
}

void File_NotExist(char *filename)
{
    Printf(iseenoxhere, No_Path(fancy_fn(filename)));
    *filename = '\0';
}

void Strip_Path(char *filename)
{
    byte *p;

    if (filename == NULL)
        return;

    while ((p = strrchr(filename, '\\')) != NULL || (p = strrchr(filename, '/')) != NULL ||
           (p = strrchr(filename, ':')) != NULL)
    {
        if (p == NULL)
            return;

        *p = '\0';
        logit(supp_path, fancy_fn(filename));
        strocpy(filename, p + 1);
    }

    if (*filename && is_devicename(filename))
    {
        logit(udev, fancy_fn(filename));
        *filename = '\0';
        return;
    }

    filename[MAX_FN_LEN] = '\0';
}

sword IsBatch(sword protocol)
{
    if (protocol == PROTOCOL_XMODEM || protocol == PROTOCOL_XMODEM1K ||
        (protocol >= 0 && !(prm.protoflag[protocol] & XTERNBATCH)))
        return FALSE;
    else
        return TRUE;
}
