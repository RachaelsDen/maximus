// SPDX-License-Identifier: GPL-2.0-or-later

#include <fcntl.h>
#include <prog.h>
#include <stdarg.h>
#include <stdio.h>
#include <uni.h>
#include <unistd.h>

#ifdef sopen
#undef sopen
#endif

char *fixPathDup(const char *filename)
{

    char *fnDup;
    char *slash;

    if (!filename)
        return NULL;

    if (filename[0] && (filename[1] == ':'))
        filename = filename + 2;

    if (!strchr(filename, '\\'))
        return (char *)filename;

    fnDup = strdup(filename);
    if (!fnDup)

    va_list ap;
    int fd;
    int perms;
    int lockMode = LOCK_NB;
    char *filename_dup;
    int no_inherit = 0;

    va_start(ap, shacc);
    perms = va_arg(ap, int);
    va_end(ap);

    if (openMode & O_NOINHERIT)
    {
        openMode &= ~O_NOINHERIT;
        no_inherit = 1;
    }


    else if (shacc & SH_DENYRD)
    if ((openMode & O_RDWR) != O_RDWR)
    {
        if (((lockMode & LOCK_SH) && !(openMode & O_RDONLY)) ||
            ((lockMode & LOCK_EX) && !(openMode & O_WRONLY)))
        {
            openMode &= ~(O_RDONLY | O_WRONLY);
            openMode |= O_RDWR;
        }
    }
