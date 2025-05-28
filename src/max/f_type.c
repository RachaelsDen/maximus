// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_type.c,v 1.1.1.1 2002/10/01 17:51:10 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "max_file.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>

void File_Type(void)
{
    FILE *typefile;

    char path[PATHLEN];
    byte filename[PATHLEN];
    byte filespec[PATHLEN];
    byte buf[PATHLEN];
    char nonstop;

    word got, bad;
    word garbage;
    int ch, save;

    WhiteN();

    InputGets(filename, type_which);

    WhiteN();


    got = fread(buf, 1, sizeof(buf) - 1, typefile);

    bad = FALSE;
    garbage = 0;


        hi = buf + min(got, PATHLEN - 1);

        for (s = buf; s < hi; s++)
            if (*s && *s < ' ' && *s != '\r' && *s != '\n' && *s != '\x1b')
                garbage++;
    }

    if (bad || garbage >= 15)
    {
        Puts(type_for_text);
        Press_ENTER();

        fclose(typefile);
        return;
    }

    logit(log_disp, blank_str, filespec);

    nonstop = FALSE;

    fseek(typefile, 0L, SEEK_SET);

    display_line = display_col = 1;

    while ((ch = fgetc(typefile)) != EOF && ch != '\x1b' && ch != '\x1a')
    {
