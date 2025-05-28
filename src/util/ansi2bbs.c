// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: ansi2bbs.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_INCL_VER

#include "max.h"
#include "prog.h"
#include <ctype.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSIBUFLEN 80

void WriteColour(int colour, FILE *bbsfile);
char blink;

#ifdef ANSI2MEC
#define A_DESC "An ANSI to .MEC file conversion program"
#ifndef UNIX
#define A_NAME "ANSI2MEC"
#define EXT ".MEC"
#else
#define A_NAME "ansi2mec"
#define EXT ".mec"
#endif

#define PutRepChr(ch, count)                                                                       \
    for (x = 0; x < count + 1; x++)                                                                \
        fprintf(bbsfile, "%c", ch);

#else
#define A_DESC "An ANSI to .BBS file conversion program"

#ifndef UNIX
#define A_NAME "ANSI2BBS"
#define EXT ".BBS"
#else
#define A_NAME "ansi2bbs"
#define EXT ".bbs"
#endif

#define PutRepChr(ch, count)                                                                       \
    ((ch == 25 || ch == 13 || ch == 10) ? fprintf(bbsfile, "%c\x19%c%c", ch, ch, count)            \
                                        : fprintf(bbsfile, "\x19%c%c", ch, count + 1));
#endif

#define Compress_Sequence()                                                                        \
    {                                                                                              \
        if (lastch != -1)                                                                          \
        {                                                                                          \
            if (lastcount <= 2)                                                                    \
            {                                                                                      \
                for (x = 0; x <= lastcount; x++)                                                   \
                    putc(lastch, bbsfile);                                                         \
            }                                                                                      \
            else                                                                                   \
                PutRepChr(lastch, lastcount);                                                      \
                                                                                                   \
            linelen += lastcount + 1;                                                              \
                                                                                                   \
            lastcount = 0;                                                                         \
            lastch = -1;                                                                           \
        }                                                                                          \
                                                                                                   \
        if (lastch != -1)                                                                          \
        {                                                                                          \
            linelen++;                                                                             \
            putc(lastch, bbsfile);                                                                 \
        }                                                                                          \
                                                                                                   \
        lastch = ch;                                                                               \
    }

int linelen;

#define MAX_LLEN 100

int _stdc main(int argc, char *argv[])
{
    FILE *ansifile, *bbsfile;

    char ansibuf[ANSIBUFLEN], temp[ANSIBUFLEN], inname[PATHLEN], outname[PATHLEN], high, lasthigh,
        *p;

    unsigned char colour;

    int ch, lastch, lastcount, last_x, x, y;

    long offset;

    lastch = -1;
    lastcount = 0;
    last_x = 1;


    Hello(A_NAME, A_DESC, VERSION, "1990, " THIS_YEAR);

    if (argc < 2)
    {
        printf("Usage:\n\n");

        printf("  %s <infile> <outfile>\n\n", A_NAME);

        printf("If no extension is specified for <infile>, then %s will use .ANS by\n", A_NAME);
        printf("default.  If no <outfile> is specified, then <infile> will be used, but with\n");
        printf("an extension of %s.\n", EXT);

        exit(1);
    }

    strcpy(inname, argv[1]);

    if ((p = strchr(inname, '.')) == NULL)
#ifndef UNIX
        strcat(inname, ".ANS");
#else
        strcat(inname, ".ans");
#endif

    if (argc < 3)
    {
        strcpy(outname, inname);

        if ((p = strrchr(outname, '.')) == NULL)
            strcat(outname, EXT);
        else
            strcpy(p, EXT);
    }
    else
        strcpy(outname, argv[2]);

    if ((p = strrchr(outname, '.')) == NULL)
        strcat(outname, EXT);

        {
            if (lastch == '[')
                lastcount++;
            else
                Compress_Sequence();
        }
#endif

        if (ch == '\n')
        {
            lastch = -1;
            lastcount = 0;
            putc('\r', bbsfile);
            putc('\n', bbsfile);
            linelen = 0;
        }
        else if (ch != '\x1b')
        {
            if (ch == lastch)
                lastcount++;
            else
                Compress_Sequence();
        }
        else
        {
            if (lastch != -1)
            {
#ifndef ANSI2MEC
                if (lastcount <= 2)
                {
#endif
                    for (x = 0; x <= lastcount; x++)
                        putc(lastch, bbsfile);
#ifndef ANSI2MEC
                }
                else if (lastcount == 25)
                    fprintf(bbsfile, "\x19%c\x19%c", lastch, lastch);
                else
                    fprintf(bbsfile, "\x19%c%c", lastch, lastcount + 1);
#endif

                linelen += lastcount;
                lastcount = 0;
                lastch = -1;
            }

            for (x = 0; x < ANSIBUFLEN - 1; x++)
            {
                ansibuf[x] = (char)(ch = getc(ansifile));

                if (isalpha(ch))
                {
                    ansibuf[x + 1] = '\0';
                    break;
                }
            }

            memmove(ansibuf, ansibuf + 1, strlen(ansibuf) + 1);

            switch (ch)
            {

            case 'u':
                break;

            case 's':
                offset = ftell(ansifile);

                for (;;)
                {
                    while ((ch = getc(ansifile)) != '\x1b' && ch != EOF)
                        ;

                    {
                        fseek(ansifile, offset, SEEK_SET);
                        break;
                    }
                }
                break;

                        if (!blink)
                        {
                            colour += 128;
                            blink = TRUE;
                        }
                        break;

                    case '7':
                        high = blink = FALSE;
                        colour = 112;
                        break;

                    case '3':
                        colour = (char)((colour / 16) * 16);

                        if (high)
                            colour += 8;

                        switch (temp[1])
                        {
                        case '1':
                            colour += 4;
                            break;

                        case '2':
                            colour += 2;
                            break;

                        case '3':
                            colour += 6;
                            break;

                        case '4':
                            colour++;
                            break;

                        case '5':
                            colour += 5;
                            break;

                        case '6':
                            colour += 3;
                            break;

                        case '7':
                            colour += 7;
                            break;
                        }
                        break;

                    case '4':
                            break;

                        case '1':
                            colour += 4 * 16;
                            break;

                        case '2':
                            colour += 2 * 16;
                            break;

                        case '3':
                            colour += 6 * 16;
                            break;

                        case '4':
                            colour += 16;
                            break;

                        case '5':
                            colour += 5 * 16;
                            break;

                        case '6':
                            colour += 3 * 16;
                            break;

                        case '7':
                            colour += 7 * 16;
                            break;
                        }
                        break;
                    }
                }

                lasthigh = high;

                WriteColour(colour, bbsfile);

                if (high)
                    colour -= 8;
                break;

#ifdef ANSI2MEC
                linelen += 7;
                fprintf(bbsfile, "[cleol]");
#else
                fprintf(bbsfile, "\x16\x07");
#endif
                break;

                if (*ansibuf != 'B')
                    y = atoi(ansibuf);
                else
                    y = 1;

#ifdef ANSI2MEC
                if (y > 3)
                {
                    linelen += 21;
                    fprintf(bbsfile, "[repeatseq 2 down %d]", y);
                }
                else
                {
                    linelen += 2 + (5 * y);

                    fprintf(bbsfile, "[");

                    for (x = 0; x < y; x++)
                        fprintf(bbsfile, "%sdown", x ? " " : "");

                    fprintf(bbsfile, "]");
                }
#else
                if (y > 3)
                    fprintf(bbsfile, "\x16\x19\x02\x16\x04%c", (char)y);
                else
                    for (x = 0; x < y; x++)
                        fprintf(bbsfile, "\x16\x04");
#endif
                break;

                if (*ansibuf != 'C')
                    y = atoi(ansibuf);
                else
                    y = 1;

#ifdef ANSI2MEC
                if (y > 3)
                {
                    linelen += 21;
                    fprintf(bbsfile, "[repeatseq 2 left %d]", y);
                }
                else
                {
                    linelen += 2 + (5 * y);

                    fprintf(bbsfile, "[");

                    for (x = 0; x < y; x++)
                        fprintf(bbsfile, "%sleft", x ? " " : "");

                    fprintf(bbsfile, "]");
                }
#else
                if (y > 3)
                    fprintf(bbsfile, "\x16\x19\x02\x16\x05%c", (char)y);
                else
                    for (x = 0; x < y; x++)
                        fprintf(bbsfile, "\x16\x05");
#endif
                break;

