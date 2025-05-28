// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_inq.c,v 1.1.1.1 2002/10/01 17:52:43 sdudley Exp $";
#pragma on(unreferenced)


#include "max_msg.h"
#include "prog.h"
#include <ctype.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Msg_Inquire(char *menuname)
{
    RipClear();

    Msg_Browse(BROWSE_ACUR | BROWSE_SEARCH | BROWSE_LIST, NULL, menuname);

#ifdef NEVER
    HMSG msgh;
    XMSG msg;
    struct _rep rexp;

        expr[PATHLEN], *p;

    int found, x, y, z;

    long msgn;

    while (1)
    {
        WhiteN();

        if (usr.bits & BITS_HOTKEYS)
            InputGetsLL(temp, PATHLEN, inq_prompt);
        else
        {
            if (!*linebuf)
                Puts(inq_p1);

            InputGetsLL(temp, PATHLEN, inq_p2);
        }

        strcpy(expr, temp);

        if (eqstr(temp, qmark))
            Display_File(0, NULL, PRM(msg_inquire));
        else
            break;
    }

    strlwr(temp);

    if (!*temp || Compile_REP(temp, &rexp) != 0)
    {
        Puts(inq_badexpr);
        return;
    }

    display_line = display_col = 1;
    nonstop = FALSE;

    Printf(inq_search, temp);

    for (msgn = 1L, found = FALSE;
         msgn < MsgHighMsg(sq) && (msgh = MsgOpenMsg(sq, MOPEN_READ, msgn)) != NULL; msgn++)
    {
        MsgReadMsg(msgh, &msg, 0L, 0L, NULL, 0L, NULL);
        MsgCloseMsg(msgh);

        if (MoreYnBreak(&nonstop, CYAN))
            break;

        if (brk_trapped || mdm_halt())
        {
            brk_trapped = 0;
            mdm_dump(DUMP_ALL);
            break;
        }

        Mdm_check();

        if (!CanSeeMsg(&msg))
            continue;

        strcpy(to, strlwr(msg.to));
        strcpy(from, strlwr(msg.from));
        strcpy(subject, strlwr(msg.subj));

        Strip_Ansi(to, usr.msg, msgn);
        Strip_Ansi(from, usr.msg, msgn);
        Strip_Ansi(subject, usr.msg, msgn);

        if ((p = stristrx(to, &rexp)) != NULL)
            z = 1;
        else
        {
            if ((p = stristrx(from, &rexp)) != NULL)
                z = 2;
            else
            {
                p = stristrx(subject, &rexp);
                z = 3;
            }
        }


        memmove(p + rexp.max_ch + 3, p + rexp.max_ch, strlen(p + rexp.max_ch) + 1);
        p[rexp.max_ch] = '\x16';
        p[rexp.max_ch + 1] = '\x01';
        p[rexp.max_ch + 2] = '\x07';

        for (y = 0; y < rexp.max_ch; y++)
            p[y] = toupper(p[y]);


        memmove(p + 3, p, strlen(p) + 1);
        p[0] = '\x16';
        p[1] = '\x01';
        p[2] = '\x0e';

            fancier_str(from);
            fancy_str(subject);
            break;

            fancier_str(from);
            fancier_str(to);
            break;
        }


    for (x = 0; x < rexp.max_ch; x++)
        if (rexp.table[x])
            free(rexp.table[x]);

    if (!found)
        Printf(inq_nf, expr);

    Clear_KBuffer();
#endif
}
