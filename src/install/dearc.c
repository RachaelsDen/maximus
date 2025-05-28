// SPDX-License-Identifier: GPL-2.0-or-later


#include "ar.h"
#include "arc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uchar buffer[DICSIZ];
static void near err_read(char *name);

int main(int argc, char *argv[])
{
    char temp[PATHLEN];
    char *dot, *bs;

    if (argc < 2)
        usage();

    make_crctable();

    strcpy(temp, argv[1]);

    bs = strrchr(temp, '\\');
    dot = strrchr(temp, '.');

    if ((!bs && !dot) || (bs && (dot == NULL || dot < bs)))
        strcat(temp, ".fiz");

    dearcit(temp, argc == 2 ? "" : argv[2]);

    return 0;
}

void dearcit(char *arcname, char *path)
{
    struct _fizhdr fh;
    char fname[120];
    word n;

    if ((arcfile = fopen(arcname, "rb")) == NULL)
        err_open(arcname);

    while (fread((char *)&fh, sizeof(fh), 1, arcfile) == 1)
    {
        origsize = compsize = unpackable = 0;

        if (fread(fname, fh.fnlen, 1, arcfile) != 1)
            err_read(arcname);

        fname[fh.fnlen] = '\0';

