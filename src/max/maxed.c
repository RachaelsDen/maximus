// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: maxed.c,v 1.1.1.1 2002/10/01 17:51:23 sdudley Exp $";
#pragma on(unreferenced)


#define INIT_MAXED
#define MAX_INCL_COMMS

#include "maxed.h"
#include "keys.h"
#include "m_reply.h"

static word near Process_Scan_Code(struct _replyp *pr);
static word near Process_Cursor_Key(void);
static void near Process_Control_Q(void);
static word near Process_Control_K(struct _replyp *pr);
static void near Init_Vars(void);

#if 1

    timer2 = FALSE;
    input_timeout = timerset(timeout_tics);

    while (!Mdm_keyp() && !brk_trapped)
    {
        Check_Time_Limit(&input_timeout, &timer2);
        Check_For_Message(NULL, NULL);
        Giveaway_Slice();
    }

    if (brk_trapped)
    {
        brk_trapped = 0;
        return '\x03';
    }

    return (Mdm_getcw());
}
#else

int Mdm_getcwcc(void)
{
    while (Mdm_kpeek_tic(timeout_tics) == -1 && !brk_trapped)
    {
        logit(mem_nmsgb);
        Puts(mem_nmsgb);

        Press_ENTER();
    }

        in_msghibit++;


        (void)mdm_ctrlc(0);
        Mdm_Flow_Off();

        update_table[max_lines] = TRUE;

        Init_Vars();

        Puts(maxed_init);

        if (!(usr.bits2 & BITS2_CLS))
            NoFF_CLS();

        if (Allocate_Line(offset + 1))
            EdMemOvfl();

        break_loop = FALSE;

        if (msgh)
        {
            Load_Message(msgh);
            Redraw_Text();
            Do_Update();
        }

        redo_status = FALSE;

        {
            for (;;)
            {

                while (!break_loop)
                {
                    screen[max_lines][0] = SOFT_CR;
                    screen[max_lines][1] = '\0';


                    if (!(offset + cursor_x >= max_lines - usrlen))
                        update_table[max_lines] = TRUE;


                    if (redo_status)
                    {
                        Redraw_StatusLine();
                        redo_status = FALSE;
                    }

                    switch (ch)
                    {
                        Delete_Char();
                        break;


                        if (usr.bits2 & BITS2_IBMCHARS)
                        {
                            Delete_Char();
                            break;
                        }
                        BackSpace();
                        break;

                        if (Carriage_Return(TRUE))
                        {
                            ret = SAVE;
                            goto BackToCaller;
                        }
                        break;

                    case K_CTRLN:
                    case K_CTRLO:
                        MagnEt_Help();
                        break;

                    case K_CTRLQ:
                        Process_Control_Q();
                        break;

                    case K_CTRLR:
                        Page_Up();
                        break;

                    case K_CTRLS:
                        Cursor_Left();
                        break;

                    case K_CTRLT:
                        Delete_Word();
                        break;

                    case K_CTRLV:
                        Toggle_Insert();
                        break;

                    case K_CTRLW:
                        Redraw_Text();
                        Redraw_StatusLine();
                        Redraw_Quote();
                        break;

                    case K_CTRLX:
                        Cursor_Down(TRUE);
                        break;

                    case K_CTRLY:

                            Delete_Line(cursor_x);
                        }

                        cursor_y = 1;

                        Goto(cursor_x, cursor_y);
                        break;

                    case K_CTRLZ:
                        ret = SAVE;
                        goto BackToCaller;

                    case K_ESC:
                        if (Process_Cursor_Key() == ABORT)
                            break_loop = TRUE;
                        break;

                    case K_CTRLB:
                    case K_CTRLU:
                    case '\x1c':
                    case '\x1e':
                    case '\x1f':
                        MagnEt_Bad_Keystroke();


                            Puts(happy);
                            Printf(msg_text_col);

                            Goto(cursor_x, cursor_y);
                            state = 0;
                        }
                        else
                            state = 0;

                        if (ch > 31 && (ch < 127 || ((mah.ma.attribs & MA_HIBIT))))
                            Add_Character(ch);
                    }

                    break;
                    }
                }

                Puts("\n" CLEOL);

                WhiteN();

                else
                {
                    (void)mdm_ctrlc(0);
                    Mdm_Flow_Off();

                    Redraw_Text();
                    Redraw_StatusLine();
                    Redraw_Quote();



    Free_All();

    if (usr.bits2 & BITS2_CLS)
        Puts(CLS);
    else
        NoFF_CLS();

    ret = ABORT;

BackToCaller:

    in_msghibit--;

    Mdm_Flow_On();

    if (quoting)
        MsgCloseMsg(qmh);

    free(update_table);
    free(quotebuf);
    free(quote_pos);

    return ret;
}

static word near Process_Scan_Code(struct _replyp *pr)
{
            Quote_OnOff(pr);
            break;

            return ABORT;

        return ABORT;

            Cursor_Up();
            break;

            Cursor_Right();
            break;

            Cursor_BeginLine();
            break;

        Cursor_BeginLine();
        break;

    case 4:
        Puts(CLEOL);
        screen[offset + cursor_x][cursor_y] = '\0';
        break;

    default:
        MagnEt_Bad_Keystroke();
        break;
    }

    Goto(usrlen, usrwidth - 3);
    Puts(YELONBLUE "  ");
    Goto(cursor_x, cursor_y);
    Printf(msg_text_col);
    vbuf_flush();
}

static word near Process_Control_K(struct _replyp *pr)
{
    int ret, ch;

    Goto(usrlen, usrwidth - 3);
    Puts(YELONBLUE "^K");
    Goto(cursor_x, cursor_y);
    Printf(msg_text_col);
    vbuf_flush();

    ret = NOTHING;

    ch = Mdm_getcwcc();

    switch (toupper(ch))
    {
        break;

    case 4:
    case 19:
        ret = ABORT;
        break;

    default:
        MagnEt_Bad_Keystroke();
    }

    Goto(usrlen, usrwidth - 3);
    Puts(YELONBLUE "  ");
    Goto(cursor_x, cursor_y);
    Printf(msg_text_col);
    vbuf_flush();

    return ret;
}

static void near Init_Vars(void)
{
    word line;

    offset = 0;
    num_lines = offset;
    cursor_x = cursor_y = 1;
    quoting = pos_to_be_updated = skip_update = FALSE;
    insert = update_table[max_lines] = TRUE;

    usrwidth = min((byte)LINELEN, TermWidth());


    usrlen = (byte)(TermLength() - ((prm.flags & FLAG_statusline) ? 1 : 0));
    usrlen = min(TermLength(), usrlen);

    for (line = 0; line < max_lines; line++)
        update_table[line] = FALSE;
}

void EdMemOvfl(void)
{
    logit(mem_nmsgb);
    Puts(mem_nmsgb + 1);

    Press_ENTER();

}
