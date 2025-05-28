// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_outl.c,v 1.2 2003/06/04 23:46:22 wesgarland Exp $";
#pragma on(unreferenced)


#include "mm.h"
#include "prog.h"
#include <conio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int last_cc;
extern char strng[];

#ifdef MCP_VIDEO
#define INCL_DOS
#include "mcp.h"
#include "pos2.h"

#define MCP_OUT_HDR (sizeof(USHORT))

static byte mcp_out_buf[MCP_OUT_BUF_MAX];
static byte *const mcp_beg = mcp_out_buf + MCP_OUT_HDR;
static byte *mcp_cur = mcp_out_buf + MCP_OUT_HDR;
static byte *const mcp_end = mcp_out_buf + MCP_OUT_BUF_MAX;

extern HPIPE hpMCP;

    static OS2UINT usSent;

    if (mcp_cur > mcp_beg)
    {
        if (hpMCP)
        {
#define Lputc near Lputc_Mcp
#define Lputs Lputs_Mcp

static void near Lputs(char *s)
{
    while (*s)
        Lputc_Mcp(*s++);
}
#endif

void Lputc(int ch)
{
    static char str2[25];
    static char state = -1;
    static char newattr;

    static word s2, s3;

    static byte uch;
    static byte save_cx;

        switch (rip_state)
        {
                return;
            }

            rip_state = 5;
            return;

            {
                rip_state = 3;
                return;
            }
            return;

            {
                rip_state = 4;
                return;
            }
            if (ch == 10 || ch == 13)
                rip_state = 0;
            if (ch == '|')
            {
                rip_state = 2;
                return;
            }


            if (last_cc == -1)
            {
                fossil_getxy(&save_cx, strng);
                last_cc = (*strng) + 1;
            }

            for (x = 0; x < (word)(9 - (last_cc % 8)); x++)
                lputc(' ');

            last_cc = -1;
            break;

        case 10:
#ifdef TTYVIDEO
            if (displaymode == VIDEO_IBM)
            {
#endif
                WinPutc(win, 13);
                WinPutc(win, 10);
#ifdef TTYVIDEO
            }
            else
            {
#endif

                lputc(10);
            }
#endif
            break;

        case 12:
            if (usr.bits2 & BITS2_CLS)
            {
                vbuf_flush();

                curattr = DEFAULT_ATTR;

#ifdef TTYVIDEO
                if (displaymode == VIDEO_IBM)
                {
#endif
                    WinCls(win, CGRAY);
                    WinSetAttr(win, curattr);
#ifdef TTYVIDEO
                }
                else
                    lputs(ansi_cls);
#endif

            if (caller_online || local)
                break;
            else
                Local_Beep(1);
            break;

        default:
            lputc((usr.bits2 & BITS2_IBMCHARS) ? ch : nohibit[(byte)ch]);
            break;
        }
    }
    else
        switch (state)
        {
        case 0:
            switch (ch)
            {
#ifdef TTYVIDEO
                    else
                        lputs(ansi_blink);
#endif
                }
                state = -1;
                break;

            case 3:
                if (usr.video || in_file_xfer)
                {
#ifdef TTYVIDEO
                    if (displaymode == VIDEO_IBM)
#endif
                        WinGotoXY(win, WinGetRow(win) - 1, WinGetCol(win), FALSE);
#ifdef TTYVIDEO
                    else
                        lputs(ansi_up);
#endif
                }
                state = -1;
                break;

            case 4:
                if (usr.video)
                {
#ifdef TTYVIDEO
                    if (displaymode == VIDEO_IBM)
#endif
                        WinGotoXY(win, WinGetRow(win) + 1, WinGetCol(win), FALSE);
#ifdef TTYVIDEO
                    else
                        lputs(ansi_down);
#endif
                }
                state = -1;
                break;

            case 5:
                if (usr.video)
                {
#ifdef TTYVIDEO
                    if (displaymode == VIDEO_IBM)
#endif
                        WinGotoXY(win, WinGetRow(win), WinGetCol(win) - 1, FALSE);
#ifdef TTYVIDEO
                    else
                        lputs(ansi_left);
#endif
                }
                state = -1;
                break;

            case 6:
                if (usr.video)
                {
#ifdef TTYVIDEO
                    if (displaymode == VIDEO_IBM)
#endif
                        WinGotoXY(win, WinGetRow(win), WinGetCol(win) + 1, FALSE);
#ifdef TTYVIDEO
                    else
                        lputs(ansi_right);
#endif
                }
                else
                    lputc(' ');
                state = -1;
                break;

            case 7:
                if (usr.video)
                {
#ifdef TTYVIDEO
                    if (displaymode == VIDEO_IBM)
#endif
                        WinCleol(win, WinGetRow(win), WinGetCol(win), WinGetAttr(win));
#ifdef TTYVIDEO
                    else
                        lputs(ansi_cleol);
#endif
                }

                state = -1;
                break;

                break;

                state = 15;
                break;

                if (usr.video)
                {
                    int wasline = WinGetRow(win) + 1;
                    int wascol = WinGetCol(win) + 1;

                    strcpy(str2, "\n" CLEOL);
                    save_cx = x = 3;
                }
                state = -1;
                break;

            {
                if (usr.video)
                {
#ifdef TTYVIDEO
                    if (displaymode == VIDEO_IBM)
#endif
                        WinSetAttr(win, (byte)ch);
#ifdef TTYVIDEO
                    else
                        lputs(avt2ansi(ch, curattr, strng));
#endif

                    curattr = (char)ch;
                }

                state = -1;
            }
            else
                state = 2;
            break;

            save_cx = (unsigned char)ch;
            state = 10;
            break;

            save_cx = (unsigned char)ch;
            state = 13;
            break;

            y = current_line;
            z = current_col;
            a = save_cx;
            state = -1;

            if (usr.video)
            {
                Lprintf(attr_string, a);

                for (x = 0; x < s2; x++)
                    Lprintf(clear_string, y + x, z, (char)ch + 1);

                Lprintf(goto_str, y, z);
            }
            break;

            s2 = ch;
            state = 17;
            break;

            y = current_line;
            z = current_col;
            a = save_cx;
            state = -1;

            if (usr.video)
            {
                Lprintf(attr_string, a);

                for (x = 0; x < s3; x++)
                    Lprintf(fill_string, y + x, z, s2, ch + 1);

                Lprintf(goto_str, y, z);
            }
            break;

        {
            word x;
            byte c;

            c = (usr.bits2 & BITS2_IBMCHARS) ? (byte)save_cx : nohibit[(byte)save_cx];

            uch = (byte)ch;

            for (x = 0; x < uch; x++)
                lputc(c);

            state = -1;
        }
        break;

        case 30:
            save_cx = (unsigned char)ch;
            x = 0;
            state = 31;
            break;

        case 31:
            if (x < 24 && x < save_cx)
                str2[x++] = (char)ch;
            else
            {
                word y;

                str2[x] = '\0';
                state = -1;

                uch = (byte)ch;

                for (y = 0; y < uch; y++)
                    Lputs(str2);
            }
            break;

        default:
            state = -1;
            break;
        }
}
