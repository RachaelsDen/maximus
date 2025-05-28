// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: os2.c,v 1.1.1.1 2002/10/01 17:52:59 sdudley Exp $";
#pragma on(unreferenced)


#ifndef OS_2
void OS2Init(void) {}
#else

#include "mm.h"
#include <stdio.h>

#define INCL_DOS
#define INCL_KBD
#define INCL_NOPM
#include <os2.h>

void OS2Init(void)
{

#ifdef __WATCOMC__
    KBDINFO kbdi;

    kbdi.cb = sizeof(kbdi);
    KbdGetStatus(&kbdi, 0);
    kbdi.fsMask &= ~(KEYBOARD_ASCII_MODE | KEYBOARD_ECHO_ON);
    kbdi.fsMask |= KEYBOARD_BINARY_MODE | KEYBOARD_ECHO_OFF;
    KbdSetStatus(&kbdi, 0);

    setvbuf(stdout, NULL, _IOFBF, 1024);


    medinit();
}

