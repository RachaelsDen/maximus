// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mecca.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define MECCA
#define SILT
#define SILT_INIT
#define MECCA_INIT
#define MAX_INCL_VER

#include "mecca.h"
#include "alc.h"
#include "ffind.h"
#include "max.h"
#include "prog.h"
#include <ctype.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _symbol *symbol[MAX_SYM] = {NULL};
unsigned char tokenbuf[MAX_TOKENLEN + 1];

            case 't':
                time_comp = TRUE;
                break;
            }
        }
        else if (*av1)
            strcpy(av2, argv[x]);
        else
            strcpy(av1, argv[x]);
    }

    if ((ff = FindOpen(av1, 0)) == NULL)
    {
        strcpy(temp, av1);
        strcat(temp, ".mec");

        if ((ff = FindOpen(temp, 0)) == NULL)
        {
            strcpy(temp, av1);
            strcat(temp, ".mer");

            if ((ff = FindOpen(temp, 0)) == NULL)
            {
                errs++;
                printf("File not found: `%s'\n", av1);
                return;
            }
        }
    }

    for (ret = 0; ret == 0; ret = FindNext(ff))
    {
        int wastype = o_type;

        strcpy(inname, av1);
        max_len = 12;

        if ((p = strrchr(inname, '/')) != NULL || (p = strrchr(inname, '\\')) != NULL ||
            (p = strrchr(inname, ':')) != NULL)
        {
            *(p + 1) = '\0';
            max_len = strlen(inname) + 12;
            strcpy(p + 1, ff->szName);
        }
        else
            strcpy(inname, ff->szName);

        if ((p = strchr(av1, '.')) != NULL && *(p + 1) == '\0')
            strcat(inname, ".");

        if (strchr(av1, '*') || strchr(av1, '?'))
        {
            if (*av2)
            {
                strcpy(outname, av2);

#ifndef UNIX
                if (outname[strlen(outname) - 1] != '\\' && outname[strlen(outname) - 1] != ':')
#else
                if (outname[strlen(outname) - 1] != PATH_DELIM)
#endif
                    strcat(outname, PATH_DELIMS);
            }
            else
                strcpy(outname, inname);

            if ((p = strrchr(outname, '\\')) != NULL || (p = strrchr(outname, '/')) != NULL ||
                (p = strrchr(outname, ':')) != NULL)
            {
                *(p + 1) = '\0';
                strcat(outname, ff->szName);

                if ((p = strrchr(outname, '.')) != NULL)
                    *p = '\0';
            }
            else
                *outname = '\0';
        }
        {
            while ((p = strpbrk(p, PATHDELIM)) != NULL)
            {
                if (*p == '\\' || *p == '/')
                    found_extension = FALSE;

                if (*p == '.')
                {
                    found_extension = TRUE;
                    if (eqstri(p + 1, "mer"))
                        o_type = 1;
                }

                p++;
            }
        }

        strcpy(temp, inname);

        if (found_extension)
        {
            if (!*outname)
            {
        {
            while ((p = strpbrk(p, PATHDELIM)) != NULL)
            {
                if (*p == '\\' || *p == '/')
                    found_extension = FALSE;

                if (*p == '.')
                    found_extension = TRUE;

                p++;
            }
        }

        if (!found_extension)
            strcat(outname, exts[o_type]);

        lcol = 7;
        n_scol = 0;

        Compile(inname, outname, 0, time_comp);
        o_type = wastype;
    }

    FindClose(ff);
}


void Compile(char *inname, char *outname, int mode, int time_comp)
{
    SCOMBO in_st, out_st;

    char *amode;

    FILE *infile, *outfile;

    FFIND *inf, *outf;

    int ch;
    int tokenidx;
    int lastch;
    int lastcount;
    int x, y;

    lastch = -1;
    lastcount = 0;

    if (!mode)
    {
        last_goto = FALSE;

        if (eqstri(inname, outname))
        {
            errs++;
            printf("Can't compile %s to itself!  Skipping.\n", inname);
            return;
        }

        if (time_comp)
        {
            if ((inf = FindInfo(inname)) != NULL)
            {
                if ((outf = FindInfo(outname)) != NULL)
                {
                    in_st = inf->scWdate;
                    in_st = inf->scWdate;

                    out_st = outf->scWdate;
                    out_st = outf->scWdate;

                    FindClose(outf);

        if (ch == '\r')
            continue;
#endif

        if (!o_type && ch == lastch && ch != '[')
            lastcount++;
        else
            Compress_Sequence();

        if (ch == '\n')
        {
            putc('\r', outfile);
            putc('\n', outfile);
            lastcount = 0;
            lastch = -1;
        }
        else if (ch == '[')
        {
            ch = -1;
            tokenidx = 0;
            tokenbuf[0] = '\0';

                if (ch == '\r')
                    continue;
#endif
                tokenbuf[tokenidx++] = (unsigned char)ch;
            }

            if (tokenbuf[0] != '[')
            {
                lastch = -1;
                lastcount = 0;

                tokenbuf[tokenidx - 1] = '\0';

                if (tokenidx == MAX_TOKENLEN)
                {
                    printf("    Token too long: `%s'\n", tokenbuf);
                    errs++;
                }


    static struct
    {
    } ptokens[] = {{"below", "\x10"
                             "B%c"},
                   {"equal", "\x10"
                             "Q%c"},
                   {"file", "\x10"
                            "F%c"},
                   {"line", "\x10"
                            "L%c"},
                   {"xclude", "\x10"
                              "X%c"},
                   {NULL, NULL}};

    p = strtok(tokenbuf, TOKENDELIM);

    while (p)
    {
        if (*p == '/')
        {
            p++;
            define = TRUE;
        }
        else
            define = FALSE;

        if ((verbnum = sssearch(p, verbs, verb_table_size)) == 0xffffu)
        {
                fputc(atoi(p), *outfile);
            else
            {
                int i;

                for (i = 0; ptokens[i].token; ++i)
                    if (stricmp(p + 1, ptokens[i].token) == 0)
                    {
                        if (define)
                            printf(err_rsvd, p);

                        fprintf(*outfile, ptokens[i].pfseq, toupper(*p));
                        break;
                    }

                inf.p = &p;
                inf.infile = NULL;
                inf.outfile = outfile;
                inf.outname = outname;
                inf.inname = inname;
                inf.verbnum = verbnum;

    {
        p = strtok(NULL, TOKENDELIM);

        fseek(outfile, -1L, SEEK_CUR);
#ifdef UNIX

        if (*p != '\\' && *p != '/' && p[1] != ':')
        {
            char *s = strrchr(inf->inname, PATH_DELIM);
            if (s != NULL)
            {
                int i = s - inf->inname;
                if ((szName = malloc(strlen(p) + i + 2)) == NULL)
                    NoMem();
                strncpy(szName, inf->inname, i);
                szName[i++] = PATH_DELIM;
                strcpy(szName + i, p);
            }
        }

        Compile(szName, inf->outname, 1, FALSE);

        if (szName != p)
            free(szName);

        if ((*inf->outfile = fopen(inf->outname, "r+b")) == NULL)
        {
            printf("\a    Error reopening `%s' for output!\n", inf->outname);
            errs++;
            return;
        }

#if 0
    if (setvbuf(*inf->outfile,NULL,_IOFBF,INOUT_BUFFER))
      NoMem();
#endif

        fseek(*inf->outfile, 0L, SEEK_END);
    }
}

void P_Copy(struct _inf *inf)
{
    FILE *copyfile, *outfile;

    char *p;
    int ch;

    p = strtok(NULL, TOKENDELIM);
    outfile = *inf->outfile;

    fixPathMove(p);
    if (p && (copyfile = fopen(p, "rb")) != NULL)
    {
        while ((ch = getc(copyfile)) != EOF)
        {
#ifdef UNIX

        if (*keystr)
            fprintf(outfile,
                    "\x17"
                    "k%c%s ",
                    ((verbnum == num_eq || (verbnum == num_ge) || (verbnum == num_gt)) ? 'I' : 'N'),
                    keystr);

        if (type == 2 && verbnum != num_lt && verbnum != num_below)
            fprintf(outfile, "\x0f"
                             "Q\r\n");
    }
}

void P_Iftime(struct _inf *inf)
{
    int hh, mm;

    char temp[PATHLEN], *p, *p2;

    word vn;

    p = strtok(NULL, TOKENDELIM);
    p2 = strtok(NULL, TOKENDELIM);

    if ((vn = sssearch(p, verbs, verb_table_size)) == 0xffffu || !IsValidTimeVerb(vn))
    {
        printf("\a    Invalid time token: `%s'!\n", p);
        errs++;
    }
    else
    {
        if (sscanf(p2, "%d:%d", &hh, &mm) != 2)
        {
            printf("\a    Invalid time format: `%s'!\n", p2);
            errs++;
        }
        else
        {
            strcpy(temp, "\x17t");

            if (vn == num_gt || vn == num_above)
                strcat(temp, "\x01");
            else if (vn == num_lt || vn == num_below)
                strcat(temp, "\x02");
            else if (vn == num_eq || vn == num_equal)
                strcat(temp, "\x03");
            else if (vn == num_ne || vn == num_unequal || vn == num_notequal)
                strcat(temp, "\x04");
            else if (vn == num_ge || vn == num_ae)
                strcat(temp, "\x05");
            else if (vn == num_le || vn == num_be)
                strcat(temp, "\x06");

            strcat(temp, "%c%c");
            fprintf(*inf->outfile, temp, hh + 1, mm + 1);
        }
    }
}

void Process_Label(char *p, int define, FILE *outfile)
{
    word vn;

    if (sssearch(p, verbs, verb_table_size) != 0xffffu)
    {
        printf(err_rsvd, p);
        errs++;
    }

    for (vn = 0; symbol[vn] && vn < MAX_SYM; vn++)
        if (eqstr(symbol[vn]->name, p))
            break;

    if (vn == MAX_SYM)
    {
        printf("\a    Error!  Too many symbols defined!\n");
        errs++;
    }
    else
    {

        if (*s > *t)
            lastlo = try;
        else
            lasthi = try;
    }
}

void Put_Colour(FILE *outfile, int col)
{
    if (col >= 160)
        fprintf(outfile, "\x16\x01%c", col - 128);
    else
        fprintf(outfile, "\x16\x01\x10%c", col | 0x80);
}

int Colour_Num(char *name)
{
    word vn;

    if ((vn = sssearch(name, verbs, verb_table_size)) == 0xffffu)
    {
        printf("    Invalid colour: `%s'\n", name);
        errs++;

        return 7;
    }

    return (verbs[vn].colour);
}

int isdigitstr(char *s)
{
    while (*s)
        if (!isdigit(*s++))
            return FALSE;

    return TRUE;
}

void Invert_Logical(word *verbnum)
{
    if (*verbnum == num_gt || *verbnum == num_above)
        *verbnum = num_le;
    else if (*verbnum == num_lt || *verbnum == num_below)
        *verbnum = num_ge;
    else if (*verbnum == num_eq || *verbnum == num_equal)
        *verbnum = num_ne;
    else if (*verbnum == num_ne || *verbnum == num_unequal || *verbnum == num_notequal)
        *verbnum = num_eq;
    else if (*verbnum == num_ge || *verbnum == num_ae)
        *verbnum = num_lt;
    else if (*verbnum == num_le || *verbnum == num_be)
        *verbnum = num_gt;
}

int IsValidTimeVerb(word verbnum)
{
    if (verbs[verbnum].fptr == P_Priv)
        return TRUE;
    else
        return FALSE;
}

word Determine_Type(char *s)
{
    if (!s || eqstri(s, "see") || eqstri(s, "show") || eqstri(s, "line"))
        return 0;
    else if (eqstri(s, "skip") || eqstri(s, "noshow"))
        return 1;
    else if (eqstri(s, "quit") || eqstri(s, "exit"))
        return 2;

    printf("\a    Invalid action: `%s'\n", s);

    return 0;
}


void Output_Code(word verbnum, FILE *outfile, int *lcol)
{
    if (verbnum < verb_table_size)
    {
        fputs(verbs[verbnum].translation, outfile);

        if (verbs[verbnum].colour != -1)
            *lcol = verbs[verbnum].colour;
    }
}
