// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: med_scrn.c,v 1.1.1.1 2002/10/01 17:52:21 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS

#include "maxed.h"

void Redraw_Text(void)
{
    word x;


    if (cx > offset && cx < offset + usrlen)
    {
        if (!Mdm_keyp() || cx == cursor_x + offset)
        {
                }
                else
                    Printf("%0.*s", usrwidth - cy, screen[cx] + cy);
            }
            else
                Printf(end_widget, msg_text_col);

            if (cx >= max_lines || screen[cx] == NULL || (cy + strlen(screen[cx] + cy) <= usrwidth))
                Puts(CLEOL);

            if (update_cursor)
                Goto(cx - offset, cy + inc);

            if ((word)update_table[cx] >= cy)
                update_table[cx] = FALSE;
        }
        else
            update_table[cx] = TRUE;
    }
}


    scx = screen[offset + cursor_x];

    for (col = usrwidth; is_wd(scx[col]); col--)
        ;



            col++;


            if ((cursor_y -= (usrwidth - col)) < 1)
                cursor_y = 1;

            cx = cursor_x + 1;



            if (!is_wd(*lastpos) && scx[0] == SOFT_CR)
            {
                *++lastpos = ' ';
                *++lastpos = '\0';
            }


            if (screen[offset + cx][1])
            {
                if (strlen(scx + col) >= usrwidth)
                    *(scx + col + usrwidth) = '\0';


                memmove(screen[offset + cx] + 1, scx + col, y = strlen(scx + col));


                if (cursor_y < usrwidth && mode != MODE_NOUPDATE)
                    Puts(CLEOL);

                    Scroll_Down(SCROLL_LINES, cursor_x - SCROLL_LINES);


                New_Line(y);
            }

                scx[col] = '\0';



                New_Line(--y);

            if (strlen(screen[offset + cursor_x] + 1) >= usrwidth)
            {

                Word_Wrap(MODE_NOUPDATE);


            if (cx < TermLength())
                Goto(cx, cursor_y);

            if (!zerolen)
                cursor_y++;
            break;
        }
    }

        col = cursor_y;
        screen[offset + cursor_x][usrwidth - 1] = '\0';

        if (cursor_y == usrwidth)
            Carriage_Return(FALSE);
        else
        {
            screen[offset + cursor_x][usrwidth - 2] = '\0';
            Update_Line(offset + cursor_x, cursor_y, 0, FALSE);
        }
    }
#endif


        if (x < UPDATEBUF_LEN)
        {
            if (update_table[x])
            {
                if (updated && offset + cursor_x == x)
                    Goto(cursor_x, cursor_y);

                Update_Line(x, 1, 0, FALSE);
                updated = TRUE;
                last_update = TRUE;
            }
            else if (x != max_lines)
                last_update = FALSE;
        }
        else
        {

            if (last_update || offset != lastofs)
            {
                Goto(x - offset, 1);
                Puts(CLEOL);
            }
        }
    }

    lastofs = offset;

    if (updated)
    {
        Goto(cursor_x, cursor_y);
        vbuf_flush();
    }
}
