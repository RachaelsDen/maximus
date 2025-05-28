// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <dos.h>

#if defined(OS_2)

#define INCL_DOS
#include <os2.h>

char *_fast canon(char *orig, char *dest)
{

char *_fast canon(char *orig, char *dest)
{
    union REGS r;
    struct SREGS s;

    r.h.ah = 0x60;

    s.ds = FP_SEG(orig);
    r.x.si = FP_OFF(orig);

    s.es = FP_SEG(dest);
    r.x.di = FP_OFF(dest);

    int86x(0x21, &r, &r, &s);

    return (r.x.cflag ? NULL : dest);
}

