// SPDX-License-Identifier: GPL-2.0-or-later



#include "dr.h"
#include "prog.h"
#include <ctype.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *_fast make_fullfname(char *path)
{
    static char full[PATHLEN * 3];
    char dir[PATHLEN];
    char *updir;
    char *supdir;
    int len;

    if (*path == '$')
        path++;

