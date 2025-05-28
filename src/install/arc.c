// SPDX-License-Identifier: GPL-2.0-or-later


#include "arc.h"
#include "ar.h"
#include "ffind.h"
#include "prog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void near usage(void);
static void near err_open(char *name);
static void near err_write(char *name);
static void store(void);

#define FALSE 0
#define TRUE 1

int main(int argc, char *argv[])
{
    char outname[PATHLEN];
    char line[PATHLEN];
    char temp[PATHLEN];
    char *file;
    FFIND *ff;
    FILE *fp = NULL;
    word dofile, i;

    if (argc < 3)
        usage();

    strcpy(outname, argv[1]);

    if (!strchr(outname, '.'))
        strcat(outname, ".fiz");

    if ((outfile = fopen(outname, "w+b")) == NULL)
        err_open(temp);

    make_crctable();

    for (i = 2; i < argc; i++)
    {
        dofile = FALSE;

        if (*argv[i] == '@')
        {
            dofile = TRUE;

            argv[i]++;

            if ((fp = fopen(argv[i], "r")) == NULL)
            {
                printf("Error reading %s!\n", argv[i]);
                continue;
            }
        }

        while (!dofile || fgets(line, PATHLEN, fp))
        {
            if (fp)
            {
                word x;

                if (line[x = strlen(line) - 1] == '\n')
                    line[x] = '\0';

                file = line;
            }
            else
                file = argv[i];

            if ((ff = FindOpen(file, 0)) == NULL)
            {
                printf("can't find %s\n", file);
                continue;
            }

            do
            {
                char *p;

                strcpy(temp, file);

                p = strrchr(temp, '\\');

                if (p)
                    p[1] = '\0';
                else
                    *temp = '\0';

                strcat(temp, ff->szName);

                if (stricmp(temp, outname) != 0)
                    arcit(temp);
            } while (FindNext(ff) == 0);

            FindClose(ff);

            if (!dofile)
                break;
        }

        if (dofile)
        {
            fclose(fp);
            fp = NULL;
        }
    }

    fclose(outfile);

    return 0;
}

void arcit(char *inname)
{
    struct _fizhdr fh;
    char *p;
    long pos;

    if ((infile = fopen(inname, "rb")) == NULL)
        err_open(inname);

    printf("archiving %s", inname);
    fflush(stdout);

    origsize = compsize = unpackable = 0;

    crc = INIT_CRC;

    pos = ftell(outfile);

    if (fwrite((char *)&fh, sizeof(fh), 1, outfile) != 1)
        err_write("archive");

