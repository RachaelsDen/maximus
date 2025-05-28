// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: med_del.c,v 1.1.1.1 2002/10/01 17:52:19 sdudley Exp $";
#pragma on(unreferenced)


#include "maxed.h"

void BackSpace(void)
{
    word strlc, cx, cy;

    if (cursor_y - 1 > strlen(screen[offset + cursor_x] + 1) && cursor_y > 1)
        Cursor_Left();
    else
    {
        if (cursor_y > 1)
        {
            strocpy(screen[offset + cursor_x] + cursor_y - 1, screen[offset + cursor_x] + cursor_y);

            Putc('\x08');

            Update_Line(offset + cursor_x, --cursor_y, 0, TRUE);
        }
                              cursor_x +
                                  ((sword)offset - SCROLL_CASUAL >= 0 ? SCROLL_CASUAL : offset));

                strlc = strlen(screen[offset + cursor_x - 1] + 1) + 1;


                if (offset + cx <= num_lines && cursor_x + offset != 1)
                    cursor_x--;

                if (strlen(screen[offset + cursor_x] + 1) >= usrwidth)
                {
                    cx = cursor_x;

                    Goto(cx = cursor_x, cursor_y = usrwidth);

                    Word_Wrap(MODE_UPDATE);

                    cursor_x = cx;

    int cx, cy, ww;

    if (cursor_y <= linelen(offset + cursor_x))
    {
        if (linelen(offset + cursor_x) != 0)
        {
            strocpy(screen[offset + cursor_x] + cursor_y, screen[offset + cursor_x] + cursor_y + 1);

            Update_Line(offset + cursor_x, cursor_y, 0, TRUE);
        }
    }
            Delete_Line(cursor_x + 1);

            if (strlen(screen[offset + cursor_x] + 1) >= usrwidth)
            {
        {
            if (cursor_x == 1 && offset != 0)
                Scroll_Up(SCROLL_CASUAL, cursor_x + SCROLL_CASUAL);

            cursor_x = num_lines - offset;
            cursor_y = 1;
            Update_Position();
        }

        Goto(cursor_x, cursor_y);
    }
{
    if (cursor_y == 1 || isalnumpunct(screen[offset + cursor_x][cursor_y]) ||
        isalnumpunct(screen[offset + cursor_x][cursor_y - 1]) ||
        cursor_y > strlen(screen[offset + cursor_x] + 1))
    {
        while (((isalnumpunct(screen[offset + cursor_x][cursor_y])) &&
                cursor_y <= strlen(screen[offset + cursor_x] + 1)) &&
               cursor_y < usrwidth)
            Delete_Char();

        if (cursor_y >= strlen(screen[offset + cursor_x] + 1))
            Delete_Char();
        else
        {
            while (!isalnumpunct(screen[offset + cursor_x][cursor_y]) &&
                   screen[offset + cursor_x][cursor_y] && cursor_y < usrwidth)
                Delete_Char();
        }
    }
    else
    {
        while ((!isalnumpunct(screen[offset + cursor_x][cursor_y])) && cursor_y < usrwidth)
            Delete_Char();
    }
}
