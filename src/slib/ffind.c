// SPDX-License-Identifier: GPL-2.0-or-later



#ifdef UNIX
#ifdef SOLARIS
#define __EXTENSIONS__
#endif
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef UNIX
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#endif
#include "compiler.h"

#ifndef __IBMC__
#include <dos.h>
#endif

#ifdef __TURBOC__
#include <dir.h>
#endif

#include "ffind.h"

#if defined(OS_2)
#define INCL_NOPM
#define INCL_DOS
#include <os2.h>

#ifdef __FLAT__
static void near CopyFBUF2FF(FFIND *ff, FILEFINDBUF3 *findbuf)
#else
static void near CopyFBUF2FF(FFIND *ff, FILEFINDBUF *findbuf)
#endif
{
    ff->usAttr = findbuf->attrFile;
    ff->ulSize = findbuf->cbFile;

    ff->scWdate.dos_st.time = *((USHORT *)&findbuf->ftimeLastWrite);
    ff->scWdate.dos_st.date = *((USHORT *)&findbuf->fdateLastWrite);

    ff->scCdate.dos_st.time = *((USHORT *)&findbuf->ftimeCreation);
    ff->scCdate.dos_st.date = *((USHORT *)&findbuf->fdateCreation);

    ff->scAdate.dos_st.time = *((USHORT *)&findbuf->ftimeLastAccess);
    ff->scAdate.dos_st.date = *((USHORT *)&findbuf->fdateLastAccess);

    if (!ff->scCdate.ldate)
        ff->scCdate.ldate = ff->scWdate.ldate;

    if (!ff->scAdate.ldate)
        ff->scAdate.ldate = ff->scWdate.ldate;

    strncpy(ff->szName, findbuf->achName, sizeof(ff->szName));
}

        ULONG usSearchCount = 1;
        FILEFINDBUF3 findbuf;
#else
        USHORT usSearchCount = 1;
        FILEFINDBUF findbuf;
#endif

        ff->hdir = HDIR_CREATE;

#ifdef __FLAT__
        if (DosFindFirst(filespec, &ff->hdir, attribute, &findbuf, sizeof findbuf, &usSearchCount,
                         FIL_STANDARD) == 0)
#else
        if (DosFindFirst(filespec, &ff->hdir, attribute, &findbuf, sizeof findbuf, &usSearchCount,
                         0L) == 0)
#endif
        {
            CopyFBUF2FF(ff, &findbuf);
        }
        else
        {
            free(ff);
            ff = NULL;
        }
    }

    return ff;
}

int _fast FindNext(FFIND *ff)
{
    int rc = -1;

    if (ff)
    {
#ifdef __FLAT__
        ULONG usSearchCount = 1;
        FILEFINDBUF3 findbuf;
#else
        USHORT usSearchCount = 1;
        FILEFINDBUF findbuf;
#endif

        if (ff->hdir && DosFindNext(ff->hdir, &findbuf, sizeof findbuf, &usSearchCount) == 0)
        {
            CopyFBUF2FF(ff, &findbuf);
            rc = 0;
        }
    }

    return rc;
}

void _fast FindClose(FFIND *ff)
{
    if (ff)
    {
        if (ff->hdir)
            DosFindClose(ff->hdir);

        free(ff);
    }
}


FFIND *_fast FindInfo(char *filespec)
{
    FFIND *ff;
    FILESTATUS fs;
    char *f;

    ff = malloc(sizeof(*ff));
    if (!ff)
        return NULL;

    memset(ff, 0, sizeof(*ff));

#ifdef __FLAT__
    if (DosQueryPathInfo(filespec, FIL_STANDARD, (PBYTE)&fs, sizeof(fs)) == 0)
#else
    if (DosQPathInfo(filespec, FIL_STANDARD, (PBYTE)&fs, sizeof(fs), 0L) == 0)
#endif
    {
        ff->usAttr = fs.attrFile;
        ff->ulSize = fs.cbFile;

        ff->scWdate.dos_st.time = *((USHORT *)&fs.ftimeLastWrite);
        ff->scWdate.dos_st.date = *((USHORT *)&fs.fdateLastWrite);

        ff->scCdate.dos_st.time = *((USHORT *)&fs.ftimeCreation);
        ff->scCdate.dos_st.date = *((USHORT *)&fs.fdateCreation);

        ff->scAdate.dos_st.time = *((USHORT *)&fs.ftimeLastAccess);
        ff->scAdate.dos_st.date = *((USHORT *)&fs.fdateLastAccess);

        if ((f = strrchr(filespec, '\\')) == NULL)
            f = filespec;
        else
            f++;

        strncpy(ff->szName, f, sizeof(ff->szName));
    }
    else
    {
        free(ff);
        return NULL;
    }

    return ff;
}

#elif defined(NT)

static void near CopyWFD2FF(FFIND *ff, WIN32_FIND_DATA *pwfd)
{
    ff->usAttr = pwfd->dwFileAttributes;
    ff->ulSize = pwfd->nFileSizeLow;

    FileTimeToDosDateTime(&pwfd->ftLastWriteTime, &ff->scWdate.dos_st.date,
                          &ff->scWdate.dos_st.time);

    FileTimeToDosDateTime(&pwfd->ftCreationTime, &ff->scCdate.dos_st.date,
                          &ff->scCdate.dos_st.time);

    FileTimeToDosDateTime(&pwfd->ftLastAccessTime, &ff->scAdate.dos_st.date,
                          &ff->scAdate.dos_st.time);

    strncpy(ff->szName, pwfd->cFileName, sizeof(ff->szName));
}

int attrmatch(unsigned int required, unsigned int actual)
{
    if ((actual & ATTR_SYSTEM) && (required & ATTR_SYSTEM) == 0)
        return FALSE;

    if ((actual & ATTR_HIDDEN) && (required & ATTR_HIDDEN) == 0)
        return FALSE;

    if ((actual & ATTR_SUBDIR) && (required & ATTR_SUBDIR) == 0)
        return FALSE;

    return TRUE;
}

FFIND *_fast FindOpen(char *filespec, unsigned short attribute)
{
    FFIND *ff;

    NW(attribute);

    ff = malloc(sizeof(FFIND));

    if (ff)
    {
        WIN32_FIND_DATA wfd;

        ff->uiAttrSearch = attribute;

        if ((ff->hdir = FindFirstFile(filespec, &wfd)) != INVALID_HANDLE_VALUE)
        {
            CopyWFD2FF(ff, &wfd);


    ff->scAdate = ff->scWdate = ff->scCdate;
    ff->ulSize = ff->__dta.ulSize;

    memset(ff->szName, '\0', sizeof(ff->szName));
    memmove(ff->szName, ff->__dta.achName, sizeof(ff->szName));
    strupr(ff->szName);
}

FFIND *_fast FindOpen(char *filespec, unsigned short attribute)
{
    FFIND *ff;

    ff = malloc(sizeof(FFIND));

    if (ff)
    {
        if (__dfindfirst(filespec, attribute, &ff->__dta) == 0)
            CopyDTA2FF(ff);
        else
        {
            free(ff);
            ff = NULL;
        }
    }

    return ff;
}

int _fast FindNext(FFIND *ff)
{
    int rc = -1;

    if (ff)
    {
        if ((rc = __dfindnext(&ff->__dta)) == 0)
            CopyDTA2FF(ff);
    }

    return rc;
}

void _fast FindClose(FFIND *ff)
{
    if (ff)
        free(ff);
}

FFIND *_fast FindInfo(char *filespec) { return FindOpen(filespec, 0); }

#elif UNIX

static int populateFF(FFIND *ff, const char *filename, struct stat *sb_p)
{
    struct stat sb;
    struct tm timebuf;
    const char *basename;

    basename = strrchr(filename, '/');
    if (basename)
        basename++;
    else
        basename = filename;

    if (sb_p)
        sb = *sb_p;
    else
    {
        if (stat(filename, &sb))

    TmDate_to_DosDate(localtime_r(&sb.st_ctime, &timebuf),
int FindNext(FFIND *ff)
{
#if defined(FAKE_GLOB_ONLYDIR)
    struct stat sb;
#endif
    struct stat *sb_p = NULL;

    if (!ff || !ff->globInfo.gl_pathc)
    for (; ff->globNext < ff->globInfo.gl_pathc; ff->globNext++)
    {
#if defined(FAKE_GLOB_ONLYDIR)
        if ((ff->globFlags & GLOB_PERIOD) && !strchr(ff->globExpr, '.'))
            if (strchr(ff->globInfo.gl_pathv[ff->globNext], '.'))
                continue;
#endif
        if (populateFF(ff, ff->globInfo.gl_pathv[ff->globNext++], sb_p) == 0)
}

FFIND *FindOpen(char *filespec, unsigned short attribute)
{

    FFIND *ff;
    char unix_filespec[1024];
    if (attribute & ATTR_SUBDIR)
        ff->globFlags |= GLOB_ONLYDIR;

    }

#if defined(FAKE_GLOB_PERIOD)
    strncpy(ff->globExpr, unix_filespec, sizeof(ff->globExpr));
    ff->globExpr[sizeof(ff->globExpr) - 1] = (char)0;
#endif

    if (glob(unix_filespec, ff->globFlags & GLOB_FLAGS_MASK, NULL, &(ff->globInfo)))
    {
        free(ff);
        return NULL;
    }


    if (FindNext(ff) == 0)
        return ff;

    free(ff);
    return NULL;
}

FFIND *FindInfo(char *filespec)
{

    FFIND *ff;

    ff = calloc(sizeof(*ff), 1);
    if (!ff)
        return NULL;

    if (populateFF(ff, filespec, NULL))
    {
        free(ff);
        return NULL;
    }

    return ff;
}

void FindClose(FFIND *ff)
{


    FFIND *ff;
    int done = FALSE;
    char full[66];

    strcpy(full, path);
    strcat(full, WILDCARD_ALL);

    if (ff = FindOpen(full, ATTR_SUBDIR))
    {

        for (done = FALSE; !done; done = FindNext(ff))
        {
            if ((ff->usAttr & ATTR_SUBDIR) && (ff->szName[0] != '.'))
            {
                strcpy(full, path);
                strcat(full, ff->szName);
                puts(full);

                {
                    char temp[120];
                    FFIND *f;

                    strcpy(temp, full);
                    strcat(temp, PATH_DELIMS WILDCARD_ALL);

                    if ((f = FindOpen(temp, 0)) != NULL)
                    {
                        do
                        {
                            printf("\t%s\n", f->szName);
                        } while (FindNext(f) == 0);

                        FindClose(f);
                    }
                }

                strcat(full, PATH_DELIMS);
                if (!walk(full))
                    return (FALSE);
            }
        }
        FindClose(ff);
        return (TRUE);
    }
    else
    {
        puts("FindOpen() failed");
    }
    return (FALSE);
}

#endif
