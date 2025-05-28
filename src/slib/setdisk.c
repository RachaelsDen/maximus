// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <dos.h>

#ifdef OS_2
#define INCL_DOS
#include <pos2.h>
#endif

#if defined(OS_2)

int _fast set_disk(int drive)
{
#ifdef __FLAT__
    DosSetDefaultDisk(drive + 1);
#else
