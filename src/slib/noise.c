// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __MSDOS__

#if defined(__MSC__) || defined(__WATCOMC__)
#include "conio.h"
#define getvect(int) _dos_getvect(int)
#define setvect(int, func) _dos_setvect(int, func)
#define inportb(port) inp(port)
#define outportb(port, byte) outp(port, byte)
#endif

#define TIMER_PORT 0x61
#define COMMAND_REG 0x43
#define CHANNEL_2 0x42

{

    char oneSecond[8000 / 8];
    int i, b;
    FILE *file;

    if (freq > 8000)
        freq = 7999;

