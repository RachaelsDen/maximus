// SPDX-License-Identifier: GPL-2.0-or-later

#include <curses.h>
#include <stdio.h>
#include <unistd.h>

inline void clrscr(void)
{
    if (!stdscr)
    {
