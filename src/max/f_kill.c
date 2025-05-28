// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_kill.c,v 1.1.1.1 2002/10/01 17:51:05 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "max_file.h"
#include "prog.h"
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>

void File_Kill(void)
{
    byte filename[PATHLEN];
    byte filespec[PATHLEN];
    byte temp[PATHLEN];

    WhiteN();

    InputGets(filename, file_to_kill);

    Strip_Path(filename);

    if (!*filename)
        return;

    sprintf(filespec, ss, FAS(fah, downpath), filename);

    if (!fexist(filespec))
    {
        if (IsInFilesBbs(&fah, filename, NULL, NULL))
            Remove_Files_Entry(filename, NULL);
        else
            Printf(cantfind + 1, filespec);

        return;
    }

    sprintf(temp, delete_yn, filename);

    if (GetyNAnswer(temp, 0) == YES)
    {
        if (unlink(filespec) == -1)
        {
            Printf(cant_unlink, filespec);
            Press_ENTER();
        }
        else
            Remove_Files_Entry(filename, NULL);
    }
    else
    {
