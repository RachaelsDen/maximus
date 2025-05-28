// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: maid.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)

#define MAX_INCL_LANGUAGE
#define MAX_INCL_VER

#include "language.h"
#include "max.h"
#include "prm.h"
#include "prmapi.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LTFHEAP 64000u
#define MAX_CONTENTS 2048
#define MAX_VARLEN 48

#define MAX_INCLUDES 8

#define MF_LTF 0x01
#define MF_HEADER 0x02

#define MAX_HEAP_STR 256

static char *version = VERSION;
static char *heap;
static char *hptr;

#define MAX_DEFN 256

static struct _defn
{
    char *name;
    char *xlt;
} defn[MAX_DEFN];

static word hn_ofs = 0;
static int ndef = 0;
static int n_symbol = 0;
static int n_include = 0;
static int in_user_heap = 0;
static unsigned int file_ptrs = 0;
static unsigned int user_ptrs = 0;
static unsigned int alt_ptrs = 0;
static char *heapnames;
static int do_h = FALSE;
static int do_lth = FALSE;

static char szLangName[32];
static char out[MAX_CONTENTS];
static char varname[MAX_VARLEN];
static char heapname[MAX_VARLEN] = "";
static char *efile_format = "#define %s%s s_ret(0x%x)\n";
static char *efile_nformat = "#define n_%s%s 0x%x\n";
static char *mfile_format = "#define str_%s lstr(%u)\n";
static char *mfile_uformat = "#define str_%s hstr(lh_%s, %u)\n";
static char hname[PATHLEN];
static char lname[PATHLEN];
static char ename[PATHLEN];
static char mname[PATHLEN];
static char prmfile[PATHLEN];
static char err = FALSE;
static char firststring = TRUE;
static unsigned longest = 0;

static char iiname[PATHLEN];
static char *iname[MAX_INCLUDES];
static int linenum[MAX_INCLUDES];

struct _heap
{
    char *name;
    char *heapstart;
    int heapsym;
    int is_user_heap;
};

static struct _heap h[MAX_HEAP];
static int nh = 0;


        if (st == '"')
        {
            strcpy(temp, fname);
            ifile[n_include] = fopen(temp, "r");
        }


            if (*fname == '\\' || *fname == '/' || fname[1] == ':')
                strcpy(temp, fname);
            else
            {
                char *p = iname[n_include - 1];
                char *s = strrchr(p, '\\');
                char *q = strrchr(p, '/');


                strcpy(s, fname);
            }
            ifile[n_include] = fopen(temp, "r");
        }

        if (ifile[n_include] == NULL)
            ErrOpen(fname);

        else
        {
            if ((iname[n_include] = strdup(temp)) == NULL)
            {
                fclose(ifile[n_include]);
                --n_include;
                Error("Out of memory processing include file", fname, TRUE);
            }
            linenum[n_include] = 0;
        }
    }
}

static void Process_Include(char *line)
{
    char temp[PATHLEN];
    char q, *s;

    getword(line, temp, " \t\n#", 2);
    q = 0;
    if (*(s = temp) == '"')
        q = '"';
    else if (*s == '<')
        q = '>';

    if (q != 0)
    {
        char *p = strchr(++s, q);
        if (p != NULL)
        {
            *p = '\0';

    for (p = temp; idchar(*s); s++)
        *p++ = *s;

    *p = '\0';

    for (x = 0; x < ndef; x++)
        if (eqstri(temp, defn[x].name))
        {
            strcpy(outp, defn[x].xlt);
            outp += strlen(outp);
            break;
        }

    if (x == ndef && *temp)
    {
        Error("Undefined variable", temp, FALSE);
    }

    *outp = '\0';
    return s;
}

        {
            *outp++ = '\\';

        {
            for (;;)
            {

                ++s;

            InQuote:

                {
                    *outp = '\0';
                    return;
                }
    }

    *outp = '\0';
}

static char *Get_Var_Name(char *line)
{
    char *s, *d;

    if (*s != '=')
    {
        Error("Invalid definition of symbol", varname, FALSE);
        return NULL;
    }

    while ((isspace(*++s) || *s == '=') && *s && *s != '\"')
        ;

    return s;
}

static void near Process_RLE(char *str)
{
    unsigned char *p, *end;
    unsigned char ch;

    for (p = str; *p;)
    {

            ch = *p;


            strocpy(p + 3, end);
            p += 3;
        }
        else
            p++;
    }
}

static void Process_Backslashes(char *str)
{
    int tint;
    char *out;
    char *s, *d;

    if ((out = malloc(strlen(str) + 1)) == NULL)
    {
        Error("No mem for backslash split", NULL, TRUE);
    }

    for (s = str, d = out; *s;)
    {
        if (*s != '\\')
            *d++ = *s++;
        else
        {
            ++s;

            if (*s == 'x' || *s == 'X')
            {
                if (sscanf(++s, "%02x", &tint) == 1)
                    *d++ = (char)tint;

                s += 2;
            }
            else if (*s == 'r')
            {
                *d++ = '\r';
                s++;
            }
            else if (*s == 'n')
            {
                *d++ = '\n';
                s++;
            }
            else if (*s == 'a')
            {
                *d++ = '\a';
                s++;
            }
            else
                *d++ = *s++;
        }
    }

    *d = '\0';
    strcpy(str, out);
    free(out);
}


                fprintf(mfile, "\n// Language heap: %s\n\n#ifdef INCL_%s\n\n", heapname, heapname);


        while (h[nh].as < (h[nh].ns - 1))
        {

        h[nh].a[h[nh].as] = hptr;
        h[nh].as++;
    }

    len = strlen(out) + 1;

    if (((hptr - heap) + len) > MAX_LTFHEAP)
        Error("Strings exceed maximum heap size", NULL, TRUE);

    memcpy(hptr, out, len);
    hptr += len;
    if (len > longest)
        longest = len;
}

static int Process_a_Line(void)
{
    static char line[MAX_CONTENTS];
    char temp[PATHLEN];
    word flags = in_user_heap ? LF_MEX : 0;
    int nws;

    while (fgets(line, MAX_CONTENTS, ifile[n_include]) == NULL)
    {
        fclose(ifile[n_include]);
        if (n_include-- == 0)
            return FALSE;
        free(iname[n_include + 1]);
    }

    linenum[n_include]++;

    Strip_Trailing(line, '\n');


        if (eqstrin(line + 1, "RIP", 3) || eqstrin(line + 1, "ALT", 3))
            flags |= LF_ALT;

            strocpy(line, line + 4);
        else
            strocpy(line, line + 5);
    }

    while (line[strlen(line) - 1] != ';' && strlen(line) < MAX_CONTENTS - 1 && *line != '#' &&
           *line != ':' && *line != '=')
    {
        strcat(line, " ");

        if (fgets(line + strlen(line), MAX_CONTENTS - strlen(line), ifile[n_include]) == NULL)
            Error("premature end of file", NULL, TRUE);

        linenum[n_include]++;

        Strip_Trailing(line, '\n');
    }

            if (mfile && !firststring)
                fprintf(mfile, "\n#endif // %s\n\n", heapname);
        }

        if (nh && n_symbol >= nh * MAX_HEAP_STR)
        {
            Error("Too many symbols in heap", heapname, TRUE);
        }
        else
            n_symbol = nh * MAX_HEAP_STR;

    nh++;


    if ((heapnames = malloc(MAX_HEAPNAMES)) == NULL)
    {
        printf("No mem for heapnames\n");
        exit(1);
    }

    hn_ofs = 0;
    for (x = 0; x < nh; x++)
    {
        word i = (word)strlen(h[x].name) + 1;
        if ((hn_ofs + i) > MAX_HEAPNAMES)
        {
            printf("Size of all heapnames exceeds maximum (%d)\n", MAX_HEAPNAMES);
            exit(1);
        }
        memcpy(heapnames + hn_ofs, h[x].name, i);
        h[x].nofs = hn_ofs;
        hn_ofs += i;
    }

    memset(&ginf, '\0', sizeof(struct _gheapinf));

    p = strrchr(iiname, PATH_DELIM);

    if (!p)
        p = strrchr(iiname, ':');

    if (p)
        p++;
    else
        p = iiname;

    strncpy(langfile, p, sizeof(langfile) - 1);
    langfile[sizeof(langfile) - 1] = 0;

    if ((p = strchr(langfile, '.')) != NULL)
        *p = 0;

    if (*szLangName)
        strcpy(ginf.language, szLangName);
    else
    {

        strcpy(ginf.language, langfile);
    }

    ginf.n_heap = (byte)nh;
    ginf.max_gptrs_len = ginf.max_gheap_len = 0;
    ginf.file_ptrs = file_ptrs;
    ginf.user_ptrs = user_ptrs;
    ginf.hn_len = hn_ofs;


    for (x = 2; x < nh; x++)
    {
        l = (h[x].ns + h[x].as) * sizeof(HOFS);

        if (l > ginf.max_gptrs_len)
            ginf.max_gptrs_len = l;

        if (x == nh - 1)
            l = hptr - h[x].heapstart;
        else
            l = h[x + 1].heapstart - h[x].heapstart;

        if (l > ginf.max_gheap_len)
            ginf.max_gheap_len = l;
    }

    printf("Strings: primary=%u user=%u alt=%u longest=%ub\n", file_ptrs, user_ptrs, alt_ptrs,
           longest);
    printf("   Heap: total=%ub max_heap_size=%ub max_ptr_size=%ub\n", hptr - heap,
           ginf.max_gheap_len, ginf.max_gptrs_len);

    fwrite((char *)&ginf, sizeof(struct _gheapinf), 1, lfile);
    fwrite((char *)heapnames, hn_ofs, 1, lfile);
    apos = ftell(lfile);

    if (hfile || efile)
        printf("\n");

    for (x = 0; x < nh; x++)
    {
        hd.start_ofs = -1L;
        hd.start_num = h[x].heapsym;
        hd.ndefs = h[x].ns;
        hd.adefs = h[x].as;
        hd.heapname = h[x].nofs;

        if (x == nh - 1)
            hd.hlen = hptr - h[x].heapstart;
        else
            hd.hlen = h[x + 1].heapstart - h[x].heapstart;

        if (hfile || efile)
            printf("Heap %c%02x, Size=%05d  Pointers=%-3d Alternates=%-3d (%s)\n",
                   (h[x].is_user_heap) ? '*' : ' ', x, hd.hlen, hd.ndefs, hd.adefs, h[x].name);

        fwrite((char *)&hd, sizeof(struct _heapdata), 1, lfile);
    }

    for (x = 0; x < nh; x++)
    {

        fclose(lfile);
        lfile = NULL;

        end = timerset(200);


            if (read(fd, (char *)&prm, sizeof(prm)) != sizeof(prm) || prm.id != 'M' ||
                prm.version != CTL_VER || prm.heap_offset != sizeof(struct m_pointers))
            {
                printf("\nNote: PRM file '%s' has not been updated.\n"
                       "(This is normal for an upgrade install.)\n",
                       prmfile);
            }
            else
            {


                if (ginf.max_gptrs_len > prm.max_ptrs)
                    prm.max_ptrs = ginf.max_gptrs_len;
                if (ginf.max_gheap_len > prm.max_heap)
                    prm.max_heap = ginf.max_gheap_len;


                lseek(fd, 0L, SEEK_SET);
                write(fd, (char *)&prm, sizeof(prm));

                printf("\n'%s' updated.\n", prmfile);
            }
            close(fd);
        }
    }

    printf("\nDone.\n");
}

static void Compile_Language(HPRM hp)
{
    iname[0] = iiname;

    ifile[0] = hfile = lfile = efile = NULL;


    if ((ifile[0] = fopen(iiname, "r")) == NULL)
    {
        char temp[PATHLEN];


    while (Process_a_Line())
        ;

    Write_Heap();

    if (efile)
    {
        fprintf(efile, "#define n_lang_ptrs %u\n", file_ptrs);
        fprintf(efile, "#endif\n");
        fclose(efile);
    }

    if (lfile)
        fclose(lfile);

    if (mfile)
        fclose(mfile);

    if (hfile)
        fclose(hfile);
}

static void Maid_Format(void)
{
    printf("Format:\n\n");

    printf("  maid <filename[.mad]> [-n<name>] [-d] [-s] [-p[prmname]]\n\n");

    printf("   -n<name>  Set language name to <name>\n");
    printf("   -d        Produce dynamic language include file (.lth)\n");
    printf("   -s        Produce static language include file (.h)\n");
    printf("   -p<file>  Update specified .PRM file.  (Defaults to MAXIMUS environment\n"
           "             variable.  Use '-p' with no argument to disable PRM updating.)\n");
    exit(1);
}

static void Make_Name(char *in, char *out, char *ext)
{
    char *s;

    strcpy(out, in);

    if ((s = strrchr(out, '.')) != NULL)
        *s = '\0';

    strcat(out, ext);
}

static void Process_Switches(int argc, char *argv[])
{
    int x;
    char *last_slash;

    for (x = 1; x < argc; x++)
    {
        if (*argv[x] == '/' || *argv[x] == '-')
        {
            switch (argv[x][1])
            {
                do_lth = TRUE;
                break;

                break;

            default:
                printf("Unknown argument: '%s'!\n", argv[x]);
                Maid_Format();
            }
        }
        else
            strcpy(iiname, argv[x]);
    }

    if (!*iiname)
        Maid_Format();

    if ((last_slash = strrstr(iiname, "\\/:")) == NULL)
        last_slash = iiname;

    if (!strchr(last_slash, '.'))
        strcat(iiname, ".mad");
}

int _stdc main(int argc, char *argv[])
{
    char *pszMaximus;
    HPRM hp;

    NW(flags);

    printf("\nMAID  Maximus International Definitions Compiler, Version %s\n", version);
    printf("Copyright 1990, " THIS_YEAR " by Lanius Corporation.  All rights reserved.\n\n");

    pszMaximus = GetMaximus(argc, argv, 1);
    strcpy(prmfile, pszMaximus);

    Process_Switches(argc, argv);

    if ((heap = hptr = malloc(MAX_LTFHEAP)) == NULL)
    {
        printf("Not enough memory to process language file.  Aborting...\n");
        exit(1);
    }

    hp = PrmFileOpen(pszMaximus, FALSE);
    Compile_Language(hp);

    if (hp)
        PrmFileClose(hp);

    free(heap);

    if (err)
    {
dword MAPIENTRY SquishHash(byte OS2FAR *f)
{
    NW(f);
    return 0;
}

void NoMem() { fprintf(stderr, "Out of memory!"); }
