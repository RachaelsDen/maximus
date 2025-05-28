// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_over.c,v 1.1.1.1 2002/10/01 17:51:08 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "max_file.h"
#include "prog.h"
#include <mem.h>
#include <stdio.h>
#include <string.h>

void File_Override_Path(void)
{
    byte path[PATHLEN];

    WhiteN();

    InputGets(path, full_ovr_path);

    if (!*path)
        return;

    if (!direxist(path))
    {
        Printf(cantfind, path);
        return;
    }

    Add_Trailing(path, '\\');

    strcpy(fah.heap + fah.fa.cbHeap, path);
    fah.fa.downpath = fah.fa.cbHeap;
    fah.fa.uppath = fah.fa.cbHeap;
    fah.fa.descript = fah.fa.cbHeap;
}
