// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: setlr.c,v 1.1.1.1 2002/10/01 17:57:36 sdudley Exp $";
#pragma on(unreferenced)

#include "msgapi.h"
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

static void near SetLR(char *name, UMSGID uid, int num_users)
{
    char fname[120];
    word wordid;
    int fd;

    printf("Creating lastread file...\n");


    if (argc < 3)
    {
        printf("Usage:\n\n"

               "SETLR <areaname> <num_users> [message_num]\n\n"

               "If <areaname> is a Squish-format area, add a '$' to the beginning of the path.\n");

        return 1;
    }

    mi.req_version = 0;
    MsgOpenApi(&mi);

    if ((ha = MsgOpenArea(argv[1] + (*argv[1] == '$'), MSGAREA_NORMAL,
                          *argv[1] == '$' ? MSGTYPE_SQUISH : MSGTYPE_SDM)) == NULL)
    {
        printf("Error!  Can't open message area %s!\n"
               "(use \"$d:\path\areaname\" for Squish-format areas!)\n");
        return 1;
    }

    high = MsgGetHighMsg(ha);
    printf("Highest message number is %ld.\n", high);

    num_users = atoi(argv[2]);

    if (argc >= 4)
        high = atoi(argv[3]);

    printf("Setting message number for all %d users to %ld.\n", num_users, high);

    uhigh = MsgMsgnToUid(ha, high);

    if (!uhigh)
    {
        printf("Error!  Message not found!\n");
        return 1;
    }

    MsgCloseArea(ha);
    MsgCloseApi();

    SetLR(argv[1], uhigh, num_users);

    printf("Done!\n");

    return 0;
}
