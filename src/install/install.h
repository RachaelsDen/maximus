// SPDX-License-Identifier: GPL-2.0-or-later


#include "bfile.h"

#define VERSION "3.00"
#define VERSIONNODOT "300"
#define DOSARCHIVE "MAX" VERSIONNODOT "R.ZIP"
#define OS2ARCHIVE "MAX" VERSIONNODOT "R.ZIP"

struct _updtab
{

    word flag;
    char *w1, *w2, *w3;
    word updword;
    char *replace;
    word wdata;
    word (*linefn)(char *line, BFILE in, BFILE out, word data);
};

struct _xlattab
{
    char *find;
    char *replace;
};

