// SPDX-License-Identifier: GPL-2.0-or-later

#include "viocurses.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


int VioSetCurPos(int row, int column, void *handle)
{
    if (stdscr)
        move(row, column);
    return 0;
}

int VioWrtTTY(const char *string, size_t length, void *handle)
{
    char *buf = NULL;

        if (stdscr)
        {
            addstr(string);
            refresh();
        }
    }
    else
        return 1;

    if (buf)
        free(buf);

    return 0;
}

chtype cursesAttribute(unsigned char dosAttribute)
{

    chtype ch;

