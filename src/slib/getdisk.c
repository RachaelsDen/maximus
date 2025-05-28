// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <ctype.h>
#include <dos.h>

#ifdef OS_2
#define INCL_DOS
#include <os2.h>
#endif


#if defined(OS_2)

int _fast get_disk(void)
{
#ifdef __FLAT__
    ULONG drive, asdf;

    DosQueryCurrentDisk(&drive, &asdf);
    return ((int)drive - 1);
#else
    unsigned short drive;
    unsigned long dont_care;

    DosQCurDisk(&drive, &dont_care);
    return ((int)drive - 1);
#endif
}

#elif defined(__MSDOS__)

int _fast get_disk(void)
{
    union REGS regs;

    regs.h.ah = 0x19;
    intdos(&regs, &regs);
    return ((int)regs.h.al);
}

#elif defined(NT)

#include "pwin.h"

int _fast get_disk(void)
{
    char szPath[PATHLEN];

    GetCurrentDirectory(PATHLEN, szPath);
    return tolower(*szPath) - 'a';
}

#elif defined(UNIX)

#else
#error Unknown OS
#endif
