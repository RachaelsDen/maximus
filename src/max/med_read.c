// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: med_read.c,v 1.2 2003/06/04 23:53:49 wesgarland Exp $";
#pragma on(unreferenced)


#include "maxed.h"
#include <errno.h>

void Read_DiskFile(void)
{
    extern int linenum;

    FILE *infile;

    byte temp[PATHLEN];
    byte *s, *p, *o, *start;

    word x, y;
    word nextline;

    WhiteN();

    InputGetsLL(temp, PATHLEN, import_file);

    if ((infile = shfopen(temp, fopen_read, O_RDONLY)) == NULL)
    {
        Printf(cantopen + 1, temp, errno);
        return;
    }

    nextline = inmagnet ? num_lines : linenum;

    for (y = 0;
         num_lines < max_lines && nextline < max_lines && fgets(temp, LINELEN - 2, infile) != NULL;
         y++)
    {
        temp[LINELEN - 2] = '\0';
        Trim_Line(temp);

        for (s = temp; *s; s++)
        {
            if (*s < 0x20 && *s != '\t')
                *s = ' ';
            else if (*s > 0x7f && (mah.ma.attribs & MA_HIBIT) == 0)
                *s = nohibit[(byte)*s];
        }

        if (screen[nextline] == NULL)
            if (Allocate_Line(nextline))
                EdMemOvfl();

        if (inmagnet)
        {
            p = screen[num_lines];

            for (x = num_lines - 1; x >= offset + cursor_x + y; x--)
                screen[x + 1] = screen[x];

            screen[offset + cursor_x + y] = p;

            screen[offset + cursor_x + y][0] = '\r';
            start = screen[offset + cursor_x + y] + 1;
        }
        else
        {
            screen[linenum][0] = '\r';
            start = screen[linenum++] + 1;
        }

        for (s = temp, o = start; *s && o < start + LINELEN - 2; s++)
            if (*s == '\t')
            {
                int tabs;

                tabs = 8 - ((o - start) % 8);

                while (tabs-- && o < start + LINELEN - 2)
                    *o++ = ' ';
            }
            else
                *o++ = *s;

        *o = '\0';

        nextline++;
    }

    fclose(infile);
}

void Load_Message(HMSG msgh)
{
    extern int linenum;

    byte outline[MAX_LINELEN];
    byte linetype[1];
    byte last_msg_attr;
    byte *pp[1];
    byte *p;

    word nextline, x, y;

    last_msg_attr = MSGLINE_NORMAL;

    MsgSetCurPos(msgh, 0L);

    nextline = inmagnet ? num_lines : linenum;

    for (y = 0; num_lines < max_lines && nextline < max_lines;)
    {
        pp[0] = outline;

        if (Msg_Read_Lines(msgh, 1, usrwidth - (inmagnet ? 1 : 6), 0, pp, linetype, &last_msg_attr,
                           0) <= 0)
            break;

        if (!(linetype[0] & MSGLINE_KLUDGE))
        {

            if (screen[nextline] == NULL)
                if (Allocate_Line(nextline))
                    EdMemOvfl();

            if (inmagnet)
            {
                p = screen[num_lines];

                for (x = num_lines - 1; x >= offset + cursor_x + y; x--)
                    screen[x + 1] = screen[x];

                screen[offset + cursor_x + y] = p;

                if (linetype[0] & MSGLINE_SOFT)
                    screen[offset + cursor_x + y][0] = SOFT_CR;
                else
                    screen[offset + cursor_x + y][0] = HARD_CR;

                strcpy(screen[offset + cursor_x + y] + 1, outline);
            }
            else
            {
                if (linetype[0] & MSGLINE_SOFT)
                    screen[linenum][0] = SOFT_CR;
                else
                    screen[linenum][0] = HARD_CR;

                strcpy(screen[linenum++] + 1, outline);
            }

            nextline++;
            y++;
        }
    }

