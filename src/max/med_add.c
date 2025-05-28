// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: med_add.c,v 1.1.1.1 2002/10/01 17:52:19 sdudley Exp $";
#pragma on(unreferenced)


#include "maxed.h"

static int near Insert_Line_Before_CR(int cx);
static void near Insert_At(word cx, word cy, char ch, word inc);


static void near AddFill(void)
{
    if (cursor_y > strlen(screen[offset + cursor_x] + 1) + 1)
    {
        memset(screen[offset + cursor_x] + strlen(screen[offset + cursor_x] + 1) + 1, ' ',

void Add_Character(int ch)
{
    word cx, cy;
    word oldoffset;
    word col;

    AddFill();

    if (cursor_y == usrwidth)
    {
        cy = cursor_y;

    if (insert || screen[offset + cursor_x][cursor_y] == '\0')
    {
        Insert_At(cursor_x, cursor_y, (char)ch, 1);

        if (screen[offset + cursor_x][cursor_y] == '\0')
            Putc(ch);

        if (strlen(screen[offset + cursor_x] + 1) >= usrwidth)
        {
            cx = cursor_x;
            cy = cursor_y;
            oldoffset = offset;

            cursor_y = usrwidth;

            Goto(cx, cursor_y);

            col = Word_Wrap(MODE_UPDATE);

            if (cursor_x >= usrlen)
                Scroll_Down(SCROLL_LINES, cursor_x - SCROLL_LINES);

            if (cy > strlen(screen[oldoffset + cx] + 1))
            {

static void near Insert_At(word cx, word cy, char ch, word inc)
{
    strocpy(screen[offset + cx] + cy + 1, screen[offset + cx] + cy);

    screen[offset + cx][cy] = ch;

    screen[offset + cx][usrwidth + 1] = '\0';

    if (screen[offset + cx][cy + 1] != '\0')
        Update_Line(offset + cursor_x, cursor_y, inc, TRUE);

    cursor_y += inc;
}


void New_Line(int col)
{
    word x;

    if (cursor_x + offset + 1 < max_lines)
    {
        cursor_x++;
        cursor_y = (col == 0 ? 1 : col);

        if (cursor_x + offset > num_lines)
        {
            for (x = num_lines + 1; x <= cursor_x + offset; x++)
            {
                if (Allocate_Line(x))
                    EdMemOvfl();
            }
        }
    }
}

word Carriage_Return(int hard)
{
    word cx;
    word temp;
    word added_line;
    word line;

    byte save_cr;

    if (eqstri(screen[cursor_x] + 1, "^z"))
    {
        screen[cursor_x][1] = '\0';
        return TRUE;
    }

    added_line = FALSE;

    if (cursor_x + 1 >= usrlen)
        Scroll_Down(SCROLL_LINES, cursor_x - SCROLL_LINES);

    cx = cursor_x + 1;


        for (line = num_lines + 1; line <= cx + offset; line++)
        {
            added_line = TRUE;

            if (Allocate_Line(line))
                EdMemOvfl();
        }
    }

    temp = 1;


        if (hard)
            *screen[offset + cursor_x] = HARD_CR;

        if (!(cx + offset > num_lines) && !added_line)
        {
            if (Allocate_Line(num_lines + 1))
                EdMemOvfl();
        }

        if (cursor_y < usrwidth)
            Puts(CLEOL);

        if ((temp = Insert_Line_Before_CR(cx)) != 0)
        {


            screen[offset + cursor_x][cursor_y] = '\0';

            Update_Line(offset + cx, 1, 0, FALSE);
        }
    }

    if (temp && offset + cursor_x != max_lines - 1)
    {
        Goto(++cursor_x, cursor_y = 1);

        Update_Position();
    }

    return FALSE;
}

static int near Insert_Line_Before_CR(int cx)
{
    word x;
    char *p;

    if (num_lines < max_lines)
    {
        if (screen[num_lines][1] != '\0')
        {
            if (Allocate_Line(num_lines + 1))
                EdMemOvfl();
        }

        p = screen[num_lines];

        for (x = min(num_lines - 1, max_lines - 1); x >= offset + cx; x--)
        {
            screen[x + 1] = screen[x];
            update_table[x + 1] = TRUE;
        }

        screen[offset + cx] = p;

        return 1;
    }
    else
    {
        Goto(cursor_x, cursor_y = 1);
        return 0;
    }
}

int Insert_Line_Before(int cx)
{
    word x;
    char *p;

    if (num_lines < max_lines - 1)
    {
        if (screen[num_lines][1] != '\0')
        {
            if (Allocate_Line(num_lines + 1))
                EdMemOvfl();
        }

        p = screen[num_lines];

        for (x = min(num_lines - 1, max_lines - 1); x >= offset + cx; x--)
        {
            screen[x + 1] = screen[x];
            update_table[x + 1] = TRUE;
        }

        screen[offset + cx] = p;

        return 1;
    }
    else
    {
        Goto(cursor_x, cursor_y = 1);
        return 0;
    }
}
