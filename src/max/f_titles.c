// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_titles.c,v 1.1.1.1 2002/10/01 17:51:10 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "display.h"
#include "max_file.h"
#include "prog.h"
#include <ctype.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void File_Titles(void)
{
    char filepath[PATHLEN];
    char temp[BUFLEN];
    char *s;
    char nonstop = 0;

    word attr;

    WhiteN();

    InputGetsLL(temp, 0, file_title);

    if (*FAS(fah, filesbbs))
        strcpy(filepath, FAS(fah, filesbbs));
    else
        sprintf(filepath, ss, FAS(fah, downpath), sfiles);

    attr = DISPLAY_FILESBBS;
    matches = 0;
    first_search = TRUE;

    if (!*temp || eqstr(temp, "="))
        ;
    else if (*temp == '*')
    {
        if ((s = firstchar(temp + 1, cmd_delim, 1)) != NULL && isdigit(*s))
            strcpy(linebuf, s);

        if (Get_New_Date(&new_date, &date_newfile, dtsf) == -1)
            return;


    Puts(CYAN "\n");

    display_line = display_col = 1;

    Display_File(attr, &nonstop, filepath);

        DispMoreYnBreak(&nonstop, CYAN, DISPLAY_FILESBBS);
    }
}
