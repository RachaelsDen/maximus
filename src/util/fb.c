// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: fb.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)

#define NOVER
#define NOVARS
#define MAX_INCL_VER

#include "fb.h"
#include "areaapi.h"
#include "bfile.h"
#include "fbp.h"
#include "ffind.h"
#include "max.h"
#include "prmapi.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <share.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef OS_2
#define INCL_DOSMISC
#include "pos2.h"
#endif

#define MAX_FBBS_LINE 1024

#define MERGE_1_SIZE 16384
#define MERGE_2_SIZE 16384
#define MERGE_OUT_SIZE 32768


#ifdef OS_2
#ifdef __FLAT__
    DosError(FERR_DISABLEHARDERR);
#else
    DosError(HARDERROR_DISABLE);
#endif
#endif

    Hello("FB", "File Database Build Utility", VERSION, "1991, " THIS_YEAR);

    if ((finf = malloc(sizeof(struct _finf) * MAX_FINF)) == NULL)
        NoMem();

    Get_Dos_Date(&scNow);

    install_24();
    atexit(uninstall_24);

    if ((ppszAreas = malloc(argc * sizeof(char *))) == NULL)
        NoMem();

    if (argc < 2)
        Usage();

    pszMaximus = GetMaximus(argc, argv, 1);

    hp = PrmFileOpen(pszMaximus, 1);
    strcpy(adat_name, PrmFileString(hp, farea_name));


    for (i = 1; i < argc; i++)
    {
        if (*argv[i] == '?')
            Usage();
        else if (*argv[i] != '-' && *argv[i] != '/')
            ppszAreas[cAreas++] = argv[i];
        else
        {
            switch (tolower(argv[i][1]))
            {
                break;

            case '?':
                printf("Unknown command-line option '%s'\n", argv[i]);

    for (anum = 0; AreaFileFindNext(haff, &fah, FALSE) == 0; anum++)
    {
        char szFilesBbs[PATHLEN];
        char szFilePath[PATHLEN];

        if (!*FAS(fah, downpath) || (fah.fa.attribs & (FA_DIVBEGIN | FA_DIVEND | FA_NOINDEX)))
            continue;

        if (fah.fa.filesbbs)
            PrmRelativeString(hp, FAS(fah, filesbbs), szFilesBbs);
        else
        {
            PrmRelativeString(hp, FAS(fah, downpath), szFilesBbs);
            strcat(szFilesBbs, filesbbs_name);
        }

        if (cAreas == 0 || do_this_area(&fah, ppszAreas, fDoSlow))
        {
            char temp[PATHLEN];

            if (fDoSlow || (fah.fa.attribs & FA_SLOW) == 0)
            {
                if (fUp)
                {
                    PrmRelativeString(hp, FAS(fah, uppath), temp);
                    strcat(temp, filesbbs_name);
                }
                else
                    strcpy(temp, szFilesBbs);

                PrmRelativeString(hp, fUp ? FAS(fah, uppath) : FAS(fah, downpath), szFilePath);

                process_files_bbs(&fah, temp, szFilePath, ffsUpdate);
            }
        }

        if (!fSkipMerge)
        {
            {
                long lFileSize = fsize(szFilesBbs);

                if (lFileSize > 0)
                    lSize += lFileSize;
            }
#endif

            p->path = strdup(szFilesBbs);
            p->anum = anum;
            p->size = -1L;

            last = p;
            p->next = ap;
            ap = p;
            cAreasProcessed++;
        }
    }

#ifdef __FLAT__

    if (last)
    {
        unlink(master_idx);


            lcopy(ap->path, master_idx);
        }

        printf("\r                       \rDone!\n");
    }
#endif

    for (p = ap; p; last = p->next, free(p), p = last)
        if (p->path)
            free(p->path);

    AreaFileFindClose(haff);
    AreaFileClose(haf);

    free(ppszAreas);

    PrmFileClose(hp);
    free(finf);

    return EXIT_SUCCESS;
}


static word near do_this_area(PFAH pfah, char **ppszAreaList, int fDoSlow)
{
    int iLenStr;
    char **p;

    if (!fDoSlow && (pfah->fa.attribs & FA_SLOW))
        return FALSE;

    for (p = ppszAreaList; *p; p++)
    {
        iLenStr = strlen(*p);


        if (eqstri(PFAS(pfah, name), *p) ||
            ((*p)[iLenStr - 1] == '*' && strnicmp(*p, PFAS(pfah, name), iLenStr - 1) == 0))
        {
            return TRUE;
        }
    }

    return FALSE;
}


static void near make_finf(char *path)
{
    FFIND *ff;
    struct _finf *fi, *e;

    if ((ff = FindOpen(path, 0)) == NULL)
    {
        num_finf = 0;
        return;
    }

    num_finf = 0;
    fi = finf;
    e = finf + MAX_FINF;

    do
    {
        memset(fi->name, '\0', sizeof(fi->name));
        strncpy(fi->name, ff->szName, sizeof(fi->name));
        num_finf = -1;
    else
        qsort(finf, num_finf, sizeof(struct _finf), finf_comp);

    FindClose(ff);
}

static char fbbs_line[MAX_FBBS_LINE];
static int push_line = 0;

static char *nextfbbsline(char *buf)
{
    char *line;

    if (bbs == NULL)
        return NULL;
    line = (push_line) ? fbbs_line : Bgets(fbbs_line, MAX_FBBS_LINE, bbs);
    push_line = 0;
    if (line && buf)
    {
        strcpy(buf, line);
        line = buf;
    }
    return line;
}

    else
    {
        sprintf(temp, "%s" WILDCARD_ALL, path);
        make_finf(temp);
    }

    strcpy(temp, fbbs);
    make_ext(temp, fdat_ext);

    if ((dat = Bopen(temp, BO_CREAT | BO_TRUNC | BO_WRONLY | BO_BINARY, BSH_DENYNO, 4096)) == NULL)
    {
        cant_open(temp);
        return -1;
    }

    strcpy(temp, fbbs);
    make_ext(temp, fdmp_ext);

    if ((dmp = Bopen(temp, BO_CREAT | BO_TRUNC | BO_WRONLY | BO_BINARY, BSH_DENYNO, 4096)) == NULL)
    {
        cant_open(temp);
        return -1;
    }

    ch = 0;


static char *near descsize(char *psz, dword *plSize)
{
    dword lsize = 0L;

    while (*psz == ',' || isdigit(*psz))
    {
        psz++;
    }


static char *near descdate(char *psz, union stamp_combo *stamp)
{
    int mon, day, year, temp;

    if ((mon = atoi(psz)) != 0)
    {
        char *p = psz;

        while (*p && isdigit(*p++))
            ;

        if ((day = atoi(p)) != 0)
        {

            while (*p && isdigit(*p++))
                ;

            year = atoi(p);

            while (*p && isdigit(*p++))
                ;

                temp = year, year = day, day = temp;

            if (day && day < 32 && mon < 13)
            {
                if (stamp)
                {

                    stamp->msg_st.date.da = day;
                    stamp->msg_st.date.mo = mon;
                    stamp->msg_st.date.yr = (year - 80);
                }

                while (*p == ' ')
                    p++;


}


    if (*line <= ' ' || *line == '-' || *line >= 127)
        return 1;


    while ((nline = nextfbbsline(NULL)) != NULL)
    {
        if (isspace(*nline) || *nline == '+')
        {
            {
                int llen = strlen(line);
                int nlen = strlen(p);

            }
        }


    getword(line, fname, fbbs_delim, 1);
    desc = firstchar(line, fbbs_delim, 2);


    filepath = strrstr(fname, "/\\");

    if (filepath)
    {
        fancy_fn(fdat.name);


        strcpy(fname, filepath);
        strcat(fname, fdat.name);
    }
    else
    {
        strncpy(fdat.name, fname, MAX_FN_LEN);
        fdat.name[MAX_FN_LEN] = '\0';
        strupr(fdat.name);

        haspath = FALSE;

        if (num_finf == -1)
            strcpy(fname, path);
        else
            *fname = '\0';

        strcat(fname, fdat.name);

    fdat.flag = FF_FILE;


    if (desc && *desc == '/')
    {
        for (desc++; tolower(*desc) == 't' || tolower(*desc) == 'b'; desc++)
            if (tolower(*desc) == 't')
                fdat.flag |= FF_NOTIME;
            else
                fdat.flag |= FF_NOBYTES;


    nofind = 0;
    if (!filepath && (pfah->fa.attribs & FA_LISTDATE) && strpbrk(fname, "*?") == NULL)
    {
        dword *plSize = (num_finf == -1) ? &fdat.fsize : NULL;
        union stamp_combo *puCombo = (num_finf == -1) ? &fdat.udate : NULL;
        char *p = desc;

        while (isspace(*p))
            p++;


        p += strspn(desc, "0123456789");

        {
            desc = descsize(desc, plSize);
            desc = descdate(desc, puCombo);
        }

        memcpy(&fdat.fdate, &fdat.udate, sizeof(fdat.udate));
        write_entry(&fdat, desc, NULL, filepath, PFAS(pfah, acs));
    }
    else
    {


                strnncpy(fdat.name, ff->szName, sizeof(fdat.name));


                fdat.udate = ff->scCdate;
                fdat.fdate = ff->scWdate;
                fdat.fsize = ff->ulSize;


            if (strchr(fname, '*') || strchr(fname, '?'))
            {

                int iLo = 0;
                int iHi = num_finf - 1;
                int iTry, iComp;

                while (iLo <= iHi)
                {
                    iTry = (iLo + iHi) / 2;

                    f = finf + iTry;

                    strncpy(buf, f->name, 12);
                    buf[12] = 0;

                    iComp = strcmp(fname, buf);

                    if (iComp < 0)
                        iHi = iTry - 1;
                    else if (iComp > 0)
                        iLo = iTry + 1;
                    else
                    {

            if (!found)
            {
                fdat.flag |= FF_OFFLINE;
                write_entry(&fdat, desc, NULL, filepath, PFAS(pfah, acs));
            }
        }
    }

    if (filepath)
        free(filepath);

    return 0;
}


    if (GEdate(&fdat->fdate, &scNow))
    {
        fdat->fdate.ldate = 0;
        fdat->fdate.msg_st.date.mo = 1;
        fdat->fdate.msg_st.date.da = 1;
    }

    if (GEdate(&fdat->udate, &scNow))
    {
        fdat->udate.ldate = 0;
        fdat->udate.msg_st.date.mo = 1;
        fdat->udate.msg_st.date.da = 1;
    }

    if ((++ctr % 64L) == 0)
    {
        printf("\b\b\b\b%04ld", ctr);
        fflush(stdout);
    }

    fdat->uploader = 0L;

    pair = desc ? *desc : '\0';
    match = 0;


    if (pair == '(')
        match = ')';
    else if (pair == '[')
        match = ']';
    else if (pair == '<')
        match = '>';

    if (match)
    {

        for (s = desc + 1, p = NULL; desc && *s == ' ' || *s == '\t' || isdigit(*s); s++)
            if (!p && isdigit(*s))
                p = s;


        if (desc && *s == match)
        {
            fdat->times_dl = p ? (dword)atol(p) : 0L;


            strocpy(desc, s);

            fdat->flag |= FF_DLCTR;
        }
    }


    if (ul)
    {
        fdat->uploader = ofs;
        slen = strlen(ul) + 1;

        cBwrite(dmp, (char *)&slen, sizeof(word));
        cBwrite(dmp, ul, slen);

        ofs += sizeof(word) + slen;
    }


static void near cant_open(char *name) { printf("Error!  Can't open file `%s'.\n", name); }


static int _stdc idxcomp(const void *i1, const void *i2)
{
    return (strncmp(((FIDX *)i1)->name, ((FIDX *)i2)->name, MAX_FN_LEN));
}


void _fast NoMem(void)
{
    printf("\nOut of memory!\n");
    exit(1);
}

#ifdef __FLAT__

static unsigned long ReadFiles(FIDX *pfi, long lMaxSize, struct _alist *al, int *piGot, int cnt)
{
    long lFileSize;
    int iGotThis;
    int iFile;
    BFILE bf;

    if ((cnt % 4) == 0)
    {
        printf("\rReading (%d)", cnt);
        fflush(stdout);
    }

        return lMaxSize;
    }



    if (Bread(bf, pfi, lFileSize) != lFileSize)
    {
        printf("Fatal error reading %ld bytes from index file %s!\n", (long)lFileSize, al->path);
        exit(1);
    }

    Bclose(bf);


    for (iFile = iGotThis; --iFile >= 0;)
        pfi++->anum = al->anum;

    return lMaxSize - (iGotThis * sizeof(FIDX));
}

static void near sort_index(char *master_idx, struct _alist *al, long size)
{
    FIDX *pfi;
    BFILE bf;
    int got = 0;
    int cnt = 0;


    while (al)
    {
        size = ReadFiles(pfi + got, size, al, &got, cnt++);
        al = al->next;
    }

    printf("\r                         \rSorting...");
    fflush(stdout);

    qsort(pfi, got, sizeof(FIDX), idxcomp);

    printf("\rWriting...");
    fflush(stdout);

    if ((bf = Bopen(master_idx, BO_CREAT | BO_TRUNC | BO_WRONLY | BO_BINARY, BSH_DENYNO,
                    MERGE_OUT_SIZE)) == NULL)
    {
        cant_open(master_idx);
        exit(1);
    }

    if (Bwrite(bf, pfi, got * sizeof(FIDX)) != got * sizeof(FIDX))
        NoSpace();

    Bclose(bf);

    printf("\rDone!       \n");

    free(pfi);
}


static int near unlist(struct _alist *rem)
{
    struct _alist *p, *last;

    for (p = ap, last = NULL; p; last = p, p = p->next)
        if (p == rem)
        {
            free(p->path);

            if (last)
                last->next = p->next;
            else
                ap = p->next;

            free(p);
            return TRUE;
        }

    return FALSE;
}


static void near merge_lists(int len)
{
    char temp[PATHLEN];
    static int filectr = 0;
    struct _alist *s1, *s2, *p;
    word new_anum;
    int x;


        if (s1->size > 0)
        {
            strcpy(temp, s1->path);
            new_anum = s1->anum;
        }
        else
        {
            strcpy(temp, s2->path);
            new_anum = s2->anum;
        }
    }


static void near get_smallest(struct _alist **smaller, struct _alist **bigger)
{
    struct _alist *p;

    if (!ap)
    {
        *smaller = *bigger = NULL;
        return;
    }

    if (ap->size == -1L)
        ap->size = fsize(ap->path);

    if (ap->next->size == -1L)
        ap->next->size = fsize(ap->next->path);

    if (ap->size < ap->next->size)
    {
        *smaller = ap;
        *bigger = ap->next;
    }
    else
    {
        *smaller = ap->next;
        *bigger = ap;
    }

    for (p = ap->next->next; p; p = p->next)
    {
        if (p->size == -1L)
            p->size = fsize(p->path);

        if (p->size < (*smaller)->size)
        {
            *bigger = *smaller;
            *smaller = p;
        }
        else if (p->size < (*bigger)->size)
            *bigger = p;
    }
}


static int near merge_these_bfiles(BFILE bf1, BFILE bf2, BFILE bfo, struct _alist *a1,
                                   struct _alist *a2)
{
    FIDX b1, b2;
    int haveb1, haveb2;

    haveb1 = read_b(bf1, &b1, a1);
    haveb2 = read_b(bf2, &b2, a2);

    while (haveb1 && haveb2)
    {

static int near merge_these(struct _alist *a1, struct _alist *a2, char *into)
{
    BFILE bf1, bf2, bfo;
    int rc = -1;

    if ((bf1 = Bopen(a1->path, BO_RDONLY | BO_BINARY, BSH_DENYNO, MERGE_1_SIZE)) == NULL)
    {
        cant_open(a1->path);
        exit(1);
    }
    else
    {
        if ((bf2 = Bopen(a2->path, BO_RDONLY | BO_BINARY, BSH_DENYNO, MERGE_2_SIZE)) == NULL)
        {
            cant_open(a2->path);
            exit(1);
        }
        else
        {
            if ((bfo = Bopen(into, BO_CREAT | BO_TRUNC | BO_WRONLY | BO_BINARY, BSH_DENYNO,
                             MERGE_OUT_SIZE)) == NULL)
            {
                cant_open(into);
                exit(1);
            }
            else
            {
                rc = merge_these_bfiles(bf1, bf2, bfo, a1, a2);
                Bclose(bfo);
            }

            Bclose(bf2);
        }

        Bclose(bf1);
    }

    return rc;
}
#endif


static word near MatchWC(char *pat, char *fn)
{
    while (*pat && *fn)
    {
        if (*pat == '*' || *fn == '*')
        {

            while (*fn && *fn != '.')
                fn++;

            if (*pat != '.')
                pat++;

            while (*pat && *pat != '.')
                pat++;
        }
        else if (*pat == '?' || *fn == '?')
        {
            if (*pat != '.')
                pat++;

            if (*fn != '.')
                fn++;
        }
        else if (toupper(*pat++) != toupper(*fn++))
        {
            return FALSE;
        }
    }

    return (*pat == '\0' && *fn == '\0');
}
