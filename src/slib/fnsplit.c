// SPDX-License-Identifier: GPL-2.0-or-later



#include "dr.h"
#include "prog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __TURBOC__

#define WILDCARDS 0x01
#define EXTENSION 0x02
#define FILENAME 0x04
#define DIRECTORY 0x08
#define DRIVE 0x10

#endif

#if defined(__MSC__) || defined(__WATCOMC__)
#define MAXPATH _MAX_PATH
#endif

#if defined(UNIX)
#include <sys/param.h>
#define MAXPATH MAXPATHLEN
#endif

#ifdef __TOPAZ__
int _RTLENTRYF _EXPFUNC fnsplit(const char *path, char *drive, char *dir, char *name, char *ext)
#else
int _stdc fnsplit(const char *path, char *drive, char *dir, char *name, char *ext)
#endif
{
    int flag = FILENAME, x;

    char temp[MAXPATH], *s;

    if (strchr(path, ':'))
    {
        if (drive)
        {
            strncpy(drive, path, 2);
            drive[2] = '\0';
        }

        flag |= DRIVE;
        path += 2;
    }
    else if (drive)
        *drive = '\0';

    s = strrchr(path, PATH_DELIM);
#if defined(UNIX)
    if (!s)
