// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__MSDOS__) && defined(__386__)
int _fast do_tune(FILE *tunefile, int(_stdc *chkfunc)(void), int dv)
{
    NW(tunefile);
    NW(chkfunc);
    NW(dv);
    printf("fatal: do_tune not implemented\n");
    exit(1);
    return 0;
}

int _fast play_tune(char *filespec, char *name, int(_stdc *chkfunc)(void), int dv)
{
    NW(filespec);
    NW(name);
    NW(chkfunc);
    NW(dv);

    printf("fatal: play_tune not implemented\n");
    exit(1);
    return 0;
}


    if (*name == '*')
        play_tune = atoi(name + 1);

#ifdef __MSDOS__
    noisefunc = (dv ? dv_noise : noise);
#endif

    if ((tunefile = fopen(filespec, "r")) == NULL)
    {
        strcpy(temp, filespec);
        strcat(temp, ".bbs");

        if ((tunefile = fopen(temp, "r")) == NULL)
            return -1;
    }

