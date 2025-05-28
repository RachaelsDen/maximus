// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_in.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS

#include "keys.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <mem.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


static int near McpKeyGetch(void)
{
    int rc;

    if (!usStrokes)
        return -1;

    rc = *cbStrokeBuf;
    memmove(cbStrokeBuf, cbStrokeBuf + 1, --usStrokes);

    return rc;
}

static int near McpKeyPeek(void) { return usStrokes ? *cbStrokeBuf : -1; }

#endif

int loc_getch(void)
{
#ifdef MCP_VIDEO
    int ch;

    while (kpeek() == -1 && McpKeyPeek() == -1)
        DosSleep(1);

    if ((ch = kpeek()) != -1)
        return kgetch();

    return McpKeyGetch();
#else
    return kgetch();
#endif
}


#ifndef __GNUC__
static int near Inputv(char *dest, int type, int ch, int max, char *prompt, char *arg[1])
#else
static int near Inputv(char *dest, int type, int ch, int max, char *prompt, va_list arg)
#endif
{
    int ret = 0;
    char *s;

    if (prompt && strchr(prompt, '%'))
    {
        vsprintf(szInputString, prompt, arg);
        prompt = szInputString;
    }

    if (max == 0)
        max = BUFLEN;


        if (prompt)
        {

            Puts(prompt);
        }

        if ((type & INPUT_MSGENTER) || (type & INPUT_WORDWRAP))
            strcpy(linebuf, dest);

        ret = mdm_gets(linebuf, type, ch, min(max, BUFLEN - 1), prompt);
    }

    {
        {
            strcpy(dest, linebuf);

            if (ret == 1 && (type & INPUT_MSGENTER) == 0 && (type & INPUT_WORDWRAP))
                strcpy(dest + strlen(dest) + 1, linebuf + strlen(linebuf) + 1);

            *linebuf = '\0';
        }
    }

    return ret;
}

int cdecl Input_Charf(int type, char *extra, ...)
{
    int rc;
    va_list arg;

    va_start(arg, extra);
    rc = Input_Charv(type, extra, arg);
    va_end(arg);
    return rc;
}

#ifndef __GNUC__
static int near Input_Charv(int type, char *extra, char *arg[1])
#else
static int near Input_Charv(int type, char *extra, va_list arg)
#endif
{
    int mdm_keyp;
    int isnllb;
    int timer2;

    char *of;
    unsigned ret = 0;

    if (extra)
    {
        vsprintf(szCharString, extra, arg);
        extra = szCharString;
    }


                    if (*linebuf == K_CTRLX)
                        Puts(bs_sn);

                    if (*linebuf == K_CTRLX && (type & CINPUT_PROMPT))
                        Puts(extra);

                    vbuf_flush();

                    mdm_keyp = FALSE;

                    *linebuf = '\0';
                    continue;
                }

                if ((type & CINPUT_DISPLAY) || !(usr.bits & BITS_HOTKEYS))
                {
                    Putc((*linebuf == '\n' || *linebuf == '\r') ? ' ' : *linebuf);
                    Putc((type & CINPUT_NOLF) ? '\r' : '\n');
                }

                vbuf_flush();

                linebuf[1] = '\0';
            }
        }

    {

        ret = *linebuf;

        if ((type & CINPUT_NOUPPER) == 0)
            ret = (char)toupper(ret);

        if (*linebuf && *linebuf != '\r')
        {
            if (type & CINPUT_LASTMENU)
                lastmenu = (byte)toupper(linebuf[0]);

            if ((of = firstchar(linebuf + 1, cmd_delim, 1)) == NULL)
                of = blank_str;

            strocpy(linebuf, of);
        }
        else
        {

    return (int)ret;
}


int cdecl GetListAnswer(char *list, char *help_file, char *invalid_response, int type,
                        char *o_prompt, ...)
{
    int len, ch;
    int isnllb;
    int retval;
    int rtnhelp = !!(type & CINPUT_RTNHELP);

    char *p;
    char *scratch;

    static char lvl = -1;


    if (++lvl == MAX_RECUR ||
        (aszListString[lvl] == NULL && (aszListString[lvl] = malloc(MAX_PRINTF)) == NULL))
    {
        --lvl;
        printf(printfstringtoolong, "GetListAnswer:vs");
        return -1;
    }

    scratch = aszListString[lvl];

    if (o_prompt == NULL)
        *scratch = '\0';
    else
    {
        if (strchr(o_prompt, '%') == NULL)

            va_start(arg, o_prompt);
            vsprintf(scratch, o_prompt, arg);
            va_end(arg);
        }
    }


    if (hasRIP() && strstr(scratch, "!|"))
    {
        type |= CINPUT_FULLPROMPT;
        type &= ~CINPUT_DISPLAY;
    }

    if (!(type & CINPUT_FULLPROMPT))
    {
        int first = TRUE;


        if (!first)
        {
            scratch[len] = '\0';

            if (help_file != NULL && *help_file)
                strcpy(scratch + len, eq_help);

            strcat(scratch, listanswer_right);
        }
    }

    isnllb = !*linebuf;

#define NO_RET (byte)'\xff'

    retval = NO_RET;

    while (retval == NO_RET)
    {
        ch = Input_Char(type | (isnllb ? CINPUT_PROMPT : 0), (isnllb ? scratch : NULL));

        if (ch <= 255)
            ch = toupper(ch);

        for (p = list; *p; p++)
        {
            if (ch == (int)toupper(*p) || (ch == '\r' && *p == '|') || (ch == '|' && *p == '\r') ||
                (isupper(*p) && (ch == '\r' || ch == '\x00' || ch == '|')))
            {
                retval = (byte)toupper(*p);
                break;
            }
        }


            if (type & CINPUT_ANY)
            {
                retval = ch;
                break;
            }

            if (invalid_response && *invalid_response)
                Printf("\r%s", invalid_response);

            Clear_KBuffer();
            isnllb = TRUE;
            retval = NO_RET;
        }
        else if (*(p + 1) == '\0' && help_file && *help_file)
        {
            Putc('\n');

            Display_File(0, NULL, help_file);

            if (!rtnhelp)
                retval = NO_RET;
        }
    }


int MoreYn(void)
{
    int c;

    Puts(CLEOL);
    c = GetYnAnswer(more_prompt, CINPUT_NOLF);

    if (usr.video == GRAPH_TTY)
        Puts(moreyn_blank);
    else
        Puts(CLEOL);

    return (c);
}

#endif

byte MoreYnns(void)
{
    byte c;

    Puts(CLEOL);
    c = GetYnnsAnswer(more_prompt, CINPUT_NOLF | CINPUT_DISPLAY);

    if (usr.video == GRAPH_TTY)
        Puts(moreynns_blank);
    else
        Puts(CLEOL);

    return (c);
}

signed int timeleft(void)
{
    static signed long temptime;

    if ((temptime = (signed long)time(NULL)) > (signed long)timeoff)
        return -1;
    else
        return ((int)(((signed long)timeoff - temptime) / 60L) + 1);
}

signed int timeonline(void) { return ((int)((time(NULL) - (signed long)timeon) / 60L)); }


    if (*linebuf && (*linebuf == '|' || strchr(cmd_delim, *linebuf)))
    {
        p = linebuf + 1;

        while (*p && strchr(cmd_delim, *p))
            p++;

        strocpy(linebuf, p);
        return;
    }

    Puts(prompt);
    vbuf_flush();


int MoreYnBreak(char *nonstop, char *colour)
{
    byte ch;

    if (display_line >= (byte)TermLength() && (usr.bits2 & BITS2_MORE))
    {
        if (*nonstop)
        {
            display_line = 1;
            vbuf_flush();
            return FALSE;
        }

        if (colour != NULL)
            Puts(colour);

        if ((ch = MoreYnns()) == YES)
            ;
        else if (ch == M_NONSTOP)
            *nonstop = TRUE;
        else if (ch == NO)
        {
            display_line = 1;
            return TRUE;
        }

        display_line = 1;
    }

    return FALSE;
}


void EatNulAfterCr(void)
{
#if defined(OS_2) || defined(UNIX)
    long t;

    if (GetConnectionType() == CTYPE_TELNET)
    {
