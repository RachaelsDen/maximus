// SPDX-License-Identifier: GPL-2.0-or-later



#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef UNIX
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#if (defined(__MSDOS__) || defined(OS_2) || defined(NT)) && !defined(__IBMC__)
#include <dos.h>
#endif

#include "ffind.h"
#include "prog.h"


int _fast fexist(char *filename)
{
#ifdef UNIX
    if (strchr(filename, '?') || strchr(filename, '*'))
    {
#endif
        FFIND *ff;

        ff = FindOpen(filename, 0);

        if (ff)
        {
            FindClose(ff);
            return TRUE;
        }
        else
            return FALSE;
#ifdef UNIX
    }
    else
    {
        struct stat sb;
        char *fndup = fixPathDup(filename);
        int i;

        i = stat(fndup, &sb);
        fixPathDupFree(filename, fndup);

        if (i)
            return FALSE;

        return TRUE;
    }
#endif
}

long _fast fsize(char *filename)
{
#ifdef UNIX
    if (strchr(filename, '?') || strchr(filename, '*'))
    {
#endif
        FFIND *ff;
        long ret = -1L;

        ff = FindOpen(filename, 0);

        if (ff)
        {
            ret = ff->ulSize;
            FindClose(ff);
        }

        return ret;
#ifdef UNIX
    }
    else
    {
        struct stat sb;
        char *fndup = fixPathDup(filename);
        int i;

        i = stat(fndup, &sb);
        fixPathDupFree(filename, fndup);

        if (i)
            return -1;

        return sb.st_size;
    }
#endif
}

#if defined(__MSDOS__)
int _fast direxist(char *directory)
{
    FFIND *ff;
    char *tempstr;
    int ret;

    if ((tempstr = (char *)malloc(strlen(directory) + 5)) == NULL)
        return FALSE;

    strcpy(tempstr, directory);

    Add_Trailing(tempstr, '\\');


#ifdef UNIX
    if (eqstr(tempstr, "/"))
#else
    if ((isalpha(tempstr[0]) && tempstr[1] == ':' && (tempstr[2] == '\\' || tempstr[2] == '/') &&
         !tempstr[3]) ||
        eqstr(tempstr, "\\"))
#endif
    {
        free(tempstr);
        return TRUE;
    }

    l = strlen(tempstr);
    if (tempstr[l - 1] == '\\' || tempstr[l - 1] == '/')
