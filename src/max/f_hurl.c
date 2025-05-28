// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_hurl.c,v 1.1.1.1 2002/10/01 17:51:03 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_m_area

#include "alc.h"
#include "max_file.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>

void File_Hurl(void)
{
    BARINFO bi;
    FAH fa = {0};

    FILE *outfilesbbs;

    byte an[MAX_ALEN];

    byte filename[PATHLEN];
    byte fbbs[PATHLEN];
    byte temp[MAX_FBBS_ENTRY];
    byte from[PATHLEN];
    byte to[PATHLEN];

    WhiteN();

    InputGets(filename, hurl_what);


    do
    {
        InputGets(temp, which_area);

        if (eqstri(temp, qmark))
            ListFileAreas(NULL, FALSE);
    } while (eqstri(temp, qmark));

    if (!*temp)
        return;

    SetAreaName(an, temp);

    memset(&fa, 0, sizeof fa);

    if (!ReadFileArea(haf, an, &fa) || !ValidFileArea(NULL, &fa, VA_PWD, &bi))
    {
        DisposeFah(&fa);

        if (*PRM(areanotexist))
            Display_File(0, NULL, PRM(areanotexist));
        else
            Puts(areadoesntexist);

        *linebuf = '\0';

        return;
    }


    if ((outfilesbbs = shfopen(fbbs, fopen_append, O_WRONLY | O_APPEND)) == NULL)
    {
        cant_open(fbbs);
        DisposeFah(&fa);

        *linebuf = '\0';
        return;
    }


        *temp = '\0';
        Remove_Files_Entry(filename, temp);

