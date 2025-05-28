// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: med_misc.c,v 1.1.1.1 2002/10/01 17:52:19 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS

#include "maxed.h"
#include <stddef.h>


void Piggy(void)
{
    word x, ofs, cx, cy;

    byte temp[MAX_LINELEN * 2];
    byte temp2[PATHLEN];
    byte *o, *s, *p, *l;

    if (no_piggy)
        return;

    ofs = offset;
    cx = cursor_x;
    cy = cursor_y;

    for (x = 1; x <= num_lines; x++)
    {
        for (s = screen[x] + 1; *s; s++)
        {
            if (isalpha(*s))
            {
                o = s;

                p = temp;

                while (isalpha(*s) || *s == '\'')
                    *p++ = *s++;

                *p = '\0';


                    x = offset + cursor_x;

void MagnEt_Bad_Keystroke(void)
{
    Goto(usrlen, 1);

    Printf(max_no_understand, ck_for_help);

    Goto(cursor_x, cursor_y);
    vbuf_flush();

    if (Mdm_getcwcc() == 0)
        Mdm_getcwcc();


    Redraw_StatusLine();
}
