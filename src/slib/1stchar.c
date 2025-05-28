// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <stdio.h>
#include <string.h>


char *_fast firstchar(char *strng, char *delim, int findword)
{
    int x, isw, sl_d, sl_s, wordno = 0;

    char *string, *oldstring;

