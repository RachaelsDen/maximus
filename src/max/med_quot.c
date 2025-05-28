// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: med_quot.c,v 1.1.1.1 2002/10/01 17:52:20 sdudley Exp $";
#pragma on(unreferenced)


#include "m_reply.h"
#include "maxed.h"

static int near Quote_Read(void);

void Quote_OnOff(struct _replyp *pr)
{
    XMSG msg;

        {
            MsgCloseMsg(qmh);

            quoting = FALSE;
            qmh = NULL;

            usrlen += QUOTELINES;
            Fix_MagnEt();
        }
        else
        {
            qmh = MsgOpenMsg(pr->fromsq, MOPEN_READ,
                             MsgUidToMsgn(pr->fromsq, pr->original, UID_EXACT));
            if (qmh == NULL)
                return;

            if (MsgReadMsg(qmh, &msg, 0L, 0L, NULL, 0L, NULL) == -1)
            {
                MsgCloseMsg(qmh);
                return;
            }

            Parse_Initials(msg.from, initials);

            quoting = TRUE;
            usrlen -= QUOTELINES;

            if (cursor_x >= usrlen)
            {
                offset += (cursor_x - usrlen) + 1;
                cursor_x = usrlen - 1;
            }

            if (usr.bits2 & BITS2_CLS)
                Puts(CLS);
            else
                NoFF_CLS();

            Redraw_Text();
            Redraw_StatusLine();

            cur_quotebuf = -1;
            last_quote = 0x7fff;

    {
        Goto(usrlen, 1);
        Puts(max_not_reply);
        Goto(cursor_x, cursor_y);

        vbuf_flush();

        while (!Mdm_keyp())
            Giveaway_Slice();

        Redraw_StatusLine();
    }

    vbuf_flush();
}


void Quote_Down(void)
{
    last_msg_attr = MSGLINE_NORMAL;

    if (cur_quotebuf < MAX_QUOTEBUF - 1 && cur_quotebuf < last_quote)
        quote_pos[++cur_quotebuf] = MsgGetCurPos(qmh);


                temp = QUOTELINES;
                break;
            }
        }
    }

    Printf(msg_text_col);


    for (ln = 0; ln < QUOTELINES && num_lines < max_lines - 1; ln++)
    {
        if (*(quotebuf + (ln * MAX_LINELEN)) != '\x16')
        {

            p = screen[num_lines];

            for (x = num_lines - 1; x >= offset + cursor_x; x--)
            {
                screen[x + 1] = screen[x];
                update_table[x + 1] = TRUE;
            }


            screen[offset + cursor_x] = n = p;


            if (QuoteThisLine(quotebuf + (ln * MAX_LINELEN)))
            {
                *n++ = ' ';

                for (s = initials; *s; s++)
                    *n++ = *s;

                *n++ = '>';
                *n++ = ' ';
            }

            strcpy(n, quotebuf + (ln * MAX_LINELEN));

            update_table[offset + cursor_x] = TRUE;
            cursor_x++;
        }
        else
            break;
    }

