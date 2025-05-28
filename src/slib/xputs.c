// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"

void _stdc xputch(char ch)
{
#ifndef __MSDOS__
    putchar(ch);
#else
    xputchr(ch);
#endif
}

void _stdc xputs(char *s)
{
    while (*s)
        xputch(*s++);
}
