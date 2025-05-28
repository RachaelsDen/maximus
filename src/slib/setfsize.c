// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <dos.h>

#if defined(__MSDOS__)

#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

int _fast setfsize(int fd, long size)
{
    union REGS r;
    long pos = tell(fd);

    lseek(fd, size, SEEK_SET);

#ifdef __386__
    r.h.ah = 0x40;
    r.x.ebx = fd;
    r.x.ecx = 0;
    r.x.edx = 0;

    int386(0x21, &r, &r);
#else
    r.h.ah = 0x40;
    r.x.bx = fd;
    r.x.cx = 0;
    r.x.dx = 0;

    int86(0x21, &r, &r);
#endif

    lseek(fd, pos, SEEK_SET);

    return 0;
}
#elif defined(OS_2)

#define INCL_DOSFILEMGR
#include <os2.h>

int _fast setfsize(int fd, long size) { return ((int)DosNewSize((HFILE)fd, (ULONG)size)); }

#elif defined(NT)

#include "pwin.h"

int _fast setfsize(int fd, long size)
{
    SetFilePointer((HANDLE)fd, size, NULL, FILE_BEGIN);
    return (!SetEndOfFile((HANDLE)fd));
}
#elif defined(UNIX)
int setfsize(int fd, long size)
{
    off_t off;

    if (!size)
        return 1;

    write(fd, "", 1);
    return 0;
}
#else
#error Unknown OS
#endif
