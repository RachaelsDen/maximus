// SPDX-License-Identifier: GPL-2.0-or-later



#include "compiler.h"
#include "typedefs.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int brk_trapped = 0;
static byte brk_is_trapped = 0;

#if defined(__MSDOS__)

#include "prog.h"
#include <conio.h>
#include <dos.h>

static void _intr new_9(void);
static void _intr trap_break(void);

static void(_intr *old_9)(void);
static void(_intr *old_23)(void);
static void(_intr *old_1b)(void);

void _fast brktrap(void)
{
    if (brk_is_trapped)
        return;

    brk_is_trapped = TRUE;

    setvect(0x1b, (_veccast)old_1b);
    setvect(0x09, (_veccast)old_9);
}

static void _intr new_9(void)
{
    static char far *shift_state = (char far *)0x417;

    static int scancode, kcode;

        {
            brk_trapped++;

            outportb(0x20, 0x20);
}


#define INCL_DOS
#include <os2.h>

#include <stdio.h>

static EXCEPTIONREGISTRATIONRECORD *perr;
static FILE *fpOut;
static int fTrapTrap = FALSE;

static void outfn(char *fmt, ...)
{
    va_list va;

    if (fpOut)
    {
        va_start(va, fmt);
        vfprintf(fpOut, fmt, va);
        va_end(va);
    }

    va_start(va, fmt);
    vfprintf(stdout, fmt, va);
    va_end(va);
}


static int MemAddrOk(unsigned long ulAddr)
{
    ULONG rc;
    ULONG ulRegSize = 1;
    ULONG ulAllocFlags;

    rc = DosQueryMem((PVOID)ulAddr, &ulRegSize, &ulAllocFlags);

    return (rc == 0 && (ulAllocFlags & PAG_READ));
}

static void WalkStack(unsigned long eip, unsigned long ebp)
{
    static int cnt = 0;

    outfn("Stk at %08lx:\n", eip);

    while (MemAddrOk(ebp))
    {
        ULONG ulAddr = *(unsigned long *)(ebp + 4);

        if (ulAddr == 0xffffffffLu)
            break;

        outfn("%08lx%c", ulAddr, (++cnt % 5) == 0 ? '\n' : ' ');


static ULONG _System ExceptionHandler(PEXCEPTIONREPORTRECORD perepr,
                                      struct _EXCEPTIONREGISTRATIONRECORD *peregr,
                                      PCONTEXTRECORD pcr, PVOID pv)
{
    static int i;
    static PTIB ptib;
    static PPIB ppib;
    static char szFile[30];
    static ULONG ulTime;
    static ULONG ulMustCount = 0;

    NW(peregr);
    NW(pv);

    switch (perepr->ExceptionNum)
    {
    case XCPT_SIGNAL:
        if (perepr->ExceptionInfo[0] == XCPT_SIGNAL_INTR ||
            perepr->ExceptionInfo[0] == XCPT_SIGNAL_BREAK)
        {

#include "pwin.h"


void _fast brktrap(void)
{
    if (!brk_is_trapped)
    {
        brk_is_trapped = TRUE;
        SetConsoleCtrlHandler(BreakHandler, TRUE);
    }
}

