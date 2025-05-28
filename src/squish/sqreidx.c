// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sqreidx.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#define NO_MSGH_DEF

#include "alc.h"
#include "api_sq.h"
#include "msgapi.h"
#include "prog.h"
#include "sqver.h"
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define VERSION SQVERSION

#ifndef UNIX
#define SQI_EXT ".SQI"
#else
#define SQI_EXT ".sqi"
#endif

char *idxname = "$$TEMP$$" SQI_EXT;

int _stdc main(int argc, char *argv[])
{
    char temp[PATHLEN];
    SQIDX idx;
    XMSG msg;
    MSG *in_area;
    MSGH *in_msg;
    dword umsgid;
    dword msgn;
    int idxfile;

    umsgid = 1L;

    printf("\nSQREIDX  SquishMail Database Reindexing Utility, Version " VERSION ".\n");
    printf("Copyright 1991, " THIS_YEAR " by Lanius Corporation.  All rights reserved.\n\n");

    if (argc < 2)
    {
        printf("Command-line format:\n\n");

        printf("  SQREIDX <area_name>\n\n");

        printf("SQREIDX will reconstruct the .SQI file for the named area.  (If the linked\n");
        printf("lists are grunged, or you wish to rebuild the entire file, try using\n");
        printf("SQFIX instead.)\n");

        exit(1);
    }

    printf("Rebuilding index for area %s\n", argv[1]);


    sprintf(temp, "%s" SQI_EXT, argv[1]);

    if ((idxfile = open(temp, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, S_IREAD | S_IWRITE)) == -1)
    {
        printf("Error opening index file `%s' for write!\n", temp);
        exit(1);
    }

    memset(&idx, '\0', sizeof(SQIDX));
    write(idxfile, (char *)&idx, sizeof(SQIDX));
    close(idxfile);

