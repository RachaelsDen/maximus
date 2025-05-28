// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <stdio.h>
#include <string.h>

void _fast colour_to_string(int colour, char *s)
{
    static char *colours[] = {"black",    "blue",         "green",      "cyan",
                              "red",      "magenta",      "brown",      "gray",
                              "darkgray", "lightblue",    "lightgreen", "lightcyan",
                              "lightred", "lightmagenta", "yellow",     "white"};

    colour &= 0x7f;

    if (colour < 16)
        sprintf(s, "%s", colours[colour]);
    else
        sprintf(s, "%s on %s", colours[colour % 16], colours[colour / 16]);
}
