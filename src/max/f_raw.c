// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_raw.c,v 1.1.1.1 2002/10/01 17:51:09 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "ffind.h"
#include "max_file.h"
#include "prog.h"
#include <mem.h>
#include <stdio.h>
#include <string.h>

void File_Raw(void)
{
    FFIND *ff;
    union stamp_combo stamp;

    byte filename[PATHLEN];
    byte filespec[PATHLEN];
    byte size[PATHLEN];
    byte date[PATHLEN];
    byte nonstop;

    int ret;

    if (!*linebuf)
        Display_File(0, NULL, "%sRAWDIR", FAS(fah, downpath));

    WhiteN();

    InputGets(filename, fname_mask);

    WhiteN();

    Strip_Path(filename);

