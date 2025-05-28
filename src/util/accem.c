// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: accem.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define ACCEM
#define SILT
#define SILT_INIT
#define MAX_INCL_VER
#define MECCA_INIT

#include "max.h"
#include "mecca.h"
#include "prog.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMPILED 10

void Process_Colour_Code(FILE *bbsfile, FILE *mecfile);
int sstsearch(char *key, struct _table base[], unsigned int num);
void Get_Number_String(FILE *bbsfile, char *string, int max_len);
int _stdc trcmp(void *, void *);

long offsets[MAX_OFFSETS], fpos;

int num_offsets, llen;

int _stdc main(int argc, char *argv[])
{
    struct _inf inf;

    FILE *bbsfile, *mecfile;

    char string[MAX_COMPILED + 5], temp[PATHLEN], inname[PATHLEN], outname[PATHLEN], *s, *p;

    long save_fp, tl;

    int verbnum, split, iter, ch, x;

    Hello("ACCEM", "The Maximus Embedded Command Decompiler", VERSION, "1990, " THIS_YEAR);

    if (argc < 2)
    {
        printf("Usage: ACCEM <infile> [outfile] [-s]\n\n");

        printf("If no extension is specified for <infile>, then ACCEM will default to\n");
        printf("an extension of .BBS.  Likewise, if no extension is specified for\n");
        printf("[outfile], then ACCEM will default to an extension of .MEC.  If no\n");
        printf("[outfile] is specified, then ACCEM will use the root of the input\n");
        printf("filename, with an extension of .MEC.\n\n");

        printf("The `-s' command-line parameter is optional: if used, it will cause\n");
        printf("ACCEM to split any lines which are over 100 characters in length, by\n");
        printf("placing an empty brace at the end of the line.  MECCA will ignore this\n");
        printf("brace when compiling, and act as if the two lines were one.  However,\n");
        printf("this switch may be necessary if your editor cannot handle lines over a\n");
        printf("certain length.\n");

        return 1;
    }

    split = FALSE;

    strcpy(inname, argv[1]);

    if (argc == 3 && (eqstri(argv[2], "-s") || eqstri(argv[2], "/s")))
    {
        split = TRUE;
        argc--;
    }

    if (argc >= 3)
    {
        strcpy(outname, argv[2]);

        if (argc >= 4 && (eqstri(argv[3], "-s") || eqstri(argv[3], "/s")))
            split = TRUE;
    }
    else
    {
        strcpy(outname, inname);

        if ((s = strchr(outname, '.')) != NULL)
            *s = '\0';
    }

    p = strchr(inname, '.');
    if (!p)
    {
        p = inname + strlen(inname);
        strcpy(p, ".bbs");

        if (!fexist(inname))
        {
            strcpy(p, ".rbs");

            if (!fexist(inname))
                strcpy(p, ".bbs");
        }
    }

    fancy_fn(outname);

    iqsort((char *)verbs, verb_table_size, sizeof(verbs[0]), trcmp);
    Init_Table();

    fixPathMove(inname);
    if ((bbsfile = fopen(inname, "rb")) == NULL)
    {
        printf("Error opening `%s' for read!\n", argv[1]);
        exit(1);
    }

    fixPathMove(outname);
    if ((mecfile = fopen(outname, "wb")) == NULL)
    {
        printf("Error opening `%s' for write!\n", argv[2]);
        exit(1);
    }

    num_offsets = llen = 0;

    printf("Compiling `%s' to `%s':\n\n", inname, outname);

    printf("Pass 1: Building jump table\n");

    for (ch = 0; ch != EOF;)
    {
        if ((ch = fgetc(bbsfile)) == '\x0f' && (ch = fgetc(bbsfile)) == 'V')
        {
            Get_Number_String(bbsfile, string, 5);
            tl = atol(string);

            for (x = 0; x < num_offsets; x++)
                if (offsets[x] == tl)
                    break;

                {
                    Process_Colour_Code(bbsfile, mecfile);
                    break;
                }
                else
                    strcpy(string, "\x16");
                fseek(bbsfile, fpos = save_fp + 1, SEEK_SET);


                    static char privch[] = "BQFLX";

                    if ((p = strchr(privch, ch)) != NULL)
                    {

                        static char *privtok[] = {"[%cbelow]", "[%cequal]", "[%cfile]", "[%cline]",
                                                  "[%cxclude]"};

                        fpos += 2;
                        llen += fprintf(mecfile, privtok[p - privch], tolower(fgetc(bbsfile)));
                        continue;
                    }

        if (*s > *t)
            lastlo = x;
        else
            lasthi = x;
    }
}

void Process_Colour_Code(FILE *bbsfile, FILE *mecfile)
{
    int ch;
    char temp[PATHLEN];

        {
            fputc('[', *inf->outfile);
            llen++;
        }

        fputc(ch, *inf->outfile);
        llen++;
    }
}

void P_Repeatseq(struct _inf *inf)
{
    char temp[PATHLEN];

    int ch;

    sprintf(temp, "[repeatseq %d", ch = fgetc(inf->infile));

    ch++;

    while (ch--)
        sprintf(&temp[strlen(temp)], " %d", fgetc(inf->infile));

    strcat(temp, "]");

    llen += strlen(temp);

    fputs(temp, *inf->outfile);
}

void P_Goto(struct _inf *inf)
{
    char string[6], temp[PATHLEN];
    long tl;
    int x;

    Get_Number_String(inf->infile, string, 5);
    tl = atol(string);

    for (x = 0; x < num_offsets; x++)
        if (tl == offsets[x])
        {
            sprintf(temp, "[goto L%d]", x);
            fputs(temp, *inf->outfile);
            llen += strlen(temp);
            break;
        }

    if (x == num_offsets)
    {
        fprintf(*inf->outfile, "[goto Unknown]");
        llen += 14;
    }
}

void P_Textsize(struct _inf *inf)
{
    int ch;
    char temp[PATHLEN];

    fpos += 2;

    ch = fgetc(inf->infile);

    sprintf(temp, "[textwin %2d %2d]", ch, fgetc(inf->infile));
    fputs(temp, *inf->outfile);
    llen += strlen(temp);
}
