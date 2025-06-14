/*
 * Maximus Version 3.02
 * Copyright 1989, 2002 by Lanius Corporation.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/*# name=Returns soundex code for given string
 */

#include "prog.h"
#include <ctype.h>
#include <stdio.h>

char *_fast soundex(char *str) /* get soundex code for a string */
{
    static char soundexbuf[81];

    /*           abcdefghijklmnopqrstuvwxyz */
    char *table = "01230120022455012623010202";

    char *sdx = soundexbuf, lastchr = ' ';

    while (*str)
    {
        if (isalpha(*str) && (*str != lastchr))
        {
            *sdx = *(table + toupper(*str) - 'A');

            if ((*sdx != '0') && (*sdx != lastchr))
                lastchr = *sdx++;
        }

        str++;
    }

    *sdx = '\0';

    return (soundexbuf);
}
