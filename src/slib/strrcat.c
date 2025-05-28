// SPDX-License-Identifier: GPL-2.0-or-later



#include "alc.h"
#include "prog.h"
#include <stdio.h>
#include <string.h>

char *_fast strrcat(char *string1, char *string2)
{
    static char *buffer = NULL;
    char *ptr;

            free(buffer);

            *ptr++ = *string1++;


