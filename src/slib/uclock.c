// SPDX-License-Identifier: GPL-2.0-or-later



#define _EXT_CLOCK_FUNC

#include "compiler.h"
#include <stdio.h>
#include <time.h>

#define us_TTIK                                                                                    \
    clock_t
    microclock(void)
{
    unsigned char msb, lsb;
    unsigned int tim_ticks;
    static int init = 0;
    unsigned long count, us_tmp;
    static unsigned long init_count;

    if (0 == init)
    {
    }

    count = *(unsigned long far *)MK_FP(BIOS_DS, B_TIKP) - init_count;
