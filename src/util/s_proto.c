// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_proto.c,v 1.1.1.1 2002/10/01 17:57:52 sdudley Exp $";
#pragma on(unreferenced)


#define SILT
#define NOVARS
#define NOINIT

#include "dr.h"
#include "max.h"
#include "prog.h"
#include "silt.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int Parse_Protocol(FILE *ctlfile, char *name)
{
    struct _proto pro;


    linenum++;

    memset(&pro, '\0', sizeof(struct _proto));

    while (fgets(line, MAX_LINE, ctlfile))
    {
        char word2[PATHLEN];
        char quote2[PATHLEN];
        char *line2;

        Strip_Comment(line);

        if (*line)
        {
            strcpy(temp, line);

            getword(line, p, ctl_delim, 1);
            getword(line, word2, ctl_delim, 2);
            line2 = fchar(line, ctl_delim, 2);
            strcpy(quote2, line2);

