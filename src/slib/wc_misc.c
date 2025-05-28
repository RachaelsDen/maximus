// SPDX-License-Identifier: GPL-2.0-or-later



// This should only be used for WC!

#ifdef __WATCOMC__

#include "alc.h"
#include "prog.h"
#include <conio.h>
#include <dos.h>
#include <errno.h>
#include <mem.h>

int _fast wc_grow_handles(int n) { return _grow_handles(n > 101 ? n : 101); }

#if defined(__MSDOS__)
int _stdc getcurdir(int drive, char *directory)
{
    union REGS r;

    r.h.ah = 0x47;
    r.h.dl = (byte)drive;

#ifdef __FLAT__
    r.x.esi = FP_OFF(directory);
    int386(0x21, &r, &r);
#else
    {
        struct SREGS sr;

        sr.ds = FP_SEG(directory);
        r.x.si = FP_OFF(directory);
        int86x(0x21, &r, &r, &sr);
    }
#endif

    return (r.x.cflag == 0 ? 0 : -1);
}
#elif defined(OS_2)

#define INCL_DOS
#include <os2.h>

int _stdc getcurdir(int drive, char *directory)
{
#ifdef __FLAT__
    ULONG buflen = PATHLEN;

    return (DosQueryCurrentDir((ULONG)drive, directory, &buflen) == 0 ? 0 : -1);
#else
    USHORT buflen = 120;

    return (DosQCurDir(drive, directory, &buflen) == 0 ? 0 : -1);
#endif
}

#elif defined(NT)

#include "pwin.h"

int _stdc getcurdir(int drive, char *directory)
{
    int old_disk, rc;

    old_disk = getdisk();

    setdisk(drive);
    rc = GetCurrentDirectory(PATHLEN, directory);
    setdisk(old_disk);

    return (rc > 0 ? 0 : -1);
}

#endif

#ifndef __FLAT__
void far *farcalloc(int n, int m)
{
    void far *p;

    p = malloc(n * m);

    if (!p)
        return NULL;

#ifdef __FLAT__
    memset(p, '\0', m * n);
#else
    _fmemset(p, '\0', m * n);
#endif

    return p;
}
