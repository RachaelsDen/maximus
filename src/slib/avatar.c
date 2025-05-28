// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static byte *acol = "\x00\x04\x02\x06\x01\x05\x03\x07";

byte *_fast avt2ansi(sword new, sword old, char *ansi)
{
    char *orig = ansi;
    word fore, back;
    word oldfore, oldback;
    word blink, oldblink;

    *ansi = '\0';


    blink = new & 0x80;
    oldblink = old & 0x80;


    fore = new & 0x0f;
    back = (new >> 4) & 0x07;


    strcpy(ansi, "\x1b[");
    ansi += strlen(ansi);

    if (oldblink && !blink)
    {
        *ansi++ = '0';

        oldback = 0;
        oldfore = 7;

        if (fore != oldfore || back != oldback || blink)
            *ansi++ = ';';
    }


        if ((fore >> 3) != (oldfore >> 3))
        {
            *ansi++ = (char)('0' + ((fore >> 3) ? 1 : 0));

            if ((fore >> 3) == 0)
            {
            }


        if (fore != oldfore)
        {

            *ansi++ = '3';
            *ansi++ = (char)('0' + acol[(word)(fore & 0x07)]);
        }


    if (back != oldback)
    {
        *ansi++ = '4';
        *ansi++ = (char)('0' + acol[(word)(back & 0x07)]);

        if (blink)
            *ansi++ = ';';
    }

    if (blink)
        *ansi++ = '5';

