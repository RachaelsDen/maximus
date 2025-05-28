// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: display.c,v 1.2 2003/06/06 01:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS
#define MAX_LANG_f_area

#include "display.h"
#include "displayp.h"
#include "ffind.h"
#include "max_file.h"
#include "max_msg.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef ORACLE
static sword near DisplayFilesBbs(DSTK *d);
#endif

static word near DispParsePriv(DSTK *d);
static void near PF(DSTK *d, word n);

int _stdc Display_File(word type, char *nonstop, char *fname, ...)
{
    DSTK *d, *dtsave;
    va_list var_args;


    if ((d = DispNewDstk(fname)) == NULL)
        return -1;

    d->type = type;
    DisplayInitDstk(d, nonstop);


    dtop = dtsave;

    return d->ret;
}

static DSTK *near DispNewDstk(char *fname)
{
    DSTK *d;

    if (++nested > MAX_NEST)
    {
        logit(log_max_nest, fname);
        nested--;
        return NULL;
    }

    if ((d = malloc(sizeof(DSTK))) == NULL)
    {
        logit(mem_none);
        nested--;
        return NULL;
    }

    return d;
}

static void DisplayCleanup(DSTK *d)
{
    free(d);


    if (--nested <= 0)
    {
        Restore_Directories2();
        nested = 0;
    }
}

static void near DisplayInitDstk(DSTK *d, byte *nonstop)
{

    d->nonstop = (nonstop ? nonstop : &d->intern_nonstop);


    if (nested <= 1 || (d->type & DISPLAY_FILESBBS))
    {

        d->ck_abort = d->automore = TRUE;


    dtop = d;

    *d->onexit = '\0';

    d->allanswers = d->recd_chars = FALSE;
    d->chcount = d->chcount_n = 0;
    d->questfile = NULL;
}

static sword near DisplayOneFile(DSTK *d)
{
    sword ret;

    if (nullptr())
        Got_A_Null_Pointer("file ", d->filename);

    d->skipcr = FALSE;
    d->beginline = TRUE;
    d->ret = 0;


    if (*d->filename == ':')
    {
#ifdef MEX
        Mex(d->filename + 1);
        *d->filename = '\0';
        *last_onexit = '\0';
#endif
        return 0;
    }

    if (DisplayOpenFile(d) != 0)
        return -1;


    return (DispCloseFiles(d, ret));
}

static sword near DisplayOpenFile(DSTK *d)
{
    d->bbsfile = -1;


        if (d->bbsfile != -1)
            d->type |= DISPLAY_NOLOCAL;
    }


    if (d->bbsfile == -1)
    {
        sprintf(d->scratch, ss, d->filename, dotbbs);

        d->bbsfile = shopen(d->scratch, O_RDONLY | O_BINARY | O_NOINHERIT);
    }


    if ((d->filebufr = malloc(FILEBUFSIZ)) == NULL)
        return (d->ret = DRET_NOMEM);

    d->bufp = d->highp = d->filebufr;


  strcpy(d->filename, d->scratch);
#endif
}

static sword near DispCloseFiles(DSTK *d, sword ret)
{
    close(d->bbsfile);

    if (d->filebufr)
    {
        free(d->filebufr);
        d->filebufr = NULL;
    }

    if (d->questfile)
    {
        fputc('\n', d->questfile);
        fclose(d->questfile);
    }


    if (*d->filename == '\0' && *d->onexit)
    {
        strcpy(d->filename, d->onexit);
        *d->onexit = '\0';
        ret = 0;
    }

    return ret;
}

static sword near DisplayNormal(DSTK *d)
{
#if (COMMAPI_VER > 1)
    extern HCOMM hcModem;
    BOOL lastState = ComBurstMode(hcModem, TRUE);
#endif
    word has_hot, doing_hotmenu;
    word ret, ch;
    byte was_no_local = no_local_output;


        if (doing_hotmenu && has_hot && ++d->chcount >= 4)
            if (DisplayHandleHotkey(d))
            {
                d->ret = DRET_HOT;
                break;
            }


        if (ch <= 26)
            ret = (*dispfn[ch])(d);
        else
            ret = DCNormal(d, ch);

        if (ret)
            break;

        if (display_col == 1 && d->automore && DispMoreYnBreak(d->nonstop, NULL, d->type))
        {
            d->ret = DRET_BREAK;
            break;
        }
    }

#if (COMMAPI_VER > 1)
    ComBurstMode(hcModem, lastState);
#endif
    no_local_output = was_no_local;
    return d->ret;
}

static sword near DisplayHandleHotkey(DSTK *d)
{
    sword mk;

    d->chcount = 0;

    if (!d->ck_abort || (mk = Mdm_keyp()) == 0)
        return FALSE;

    if (mk == '\x08' || mk == '\x09')
        Mdm_getcw();

        mdm_dump(DUMP_OUTPUT);
        return TRUE;
    }

    return FALSE;
}

#ifndef ORACLE

static sword near DisplayFilesBbs(DSTK *d)
{
#if (COMMAPI_VER > 1)
    extern HCOMM hcModem;
    BOOL lastState = ComBurstMode(hcModem, TRUE);
#endif
    byte last_col;
    word ret, ch;
    byte was_no_local = no_local_output;


        if ((ch = DispGetChar()) == DISP_EOF)
            break;

        {
            if (ProcessFBBSLine(d, ch))
            {
                d->ret = DRET_BREAK;
                break;
            }
        }
        else if ((d->type & (DISPLAY_NEWFILES | DISPLAY_SEARCH)) == 0)
        {
            if (ch <= 26)
                ret = (*dispfn[ch])(d);
            else
                ret = DCNormal(d, ch);

            if (ret)
                break;
        }

        last_col = current_col;
    }

    no_local_output = was_no_local;
#if (COMMAPI_VER > 1)
    ComBurstMode(hcModem, lastState);
#endif
    return d->ret;
}

static word near ProcessFBBSLine(DSTK *d, word ch)
{
    sword ret;

    if (ch == '@' && d->beginline && !acsflag(CFLAGA_FHIDDEN))
        return TRUE;
    else if (ch == '\r')
        d->beginline = TRUE;
    else if (ch == '-')
    {
        if ((d->type & (DISPLAY_NEWFILES | DISPLAY_SEARCH)) == 0)
            Puts(WHITE "-");

        d->beginline = FALSE;
    }
    else if (ch <= 32 || ch >= 127)
    {
        d->beginline = (ch == 10);

        if ((d->type & (DISPLAY_NEWFILES | DISPLAY_SEARCH)) == 0 || ch == 16)
        {
            if (ch == 22)
                wrap = TRUE;


        *d->scratch = (byte)ch;


    Putc('\x16');
    Putc(ch = DispSlowGetChar(d));

    switch (ch)
    {
            ch = DispSlowGetChar(d);
        }

        Putc(ch);
        break;

    case '\x08':
        PF(d, 2);
        break;

        PF(d, 4);
        break;

        Putc(ch = DispSlowGetChar(d));
        PF(d, ch + 1);
        break;
    }

#if (COMMAPI_VER > 1)
    ComBurstMode(hcModem, lastState);
#endif
    return FALSE;
}

word near DCMaximus(DSTK *d)
{
    word ret;

    d->recd_chars = TRUE;
    return FALSE;
}

word near DCCKOff(DSTK *d)
{
    d->ck_abort = FALSE;
    return FALSE;
}
word near DCCKOn(DSTK *d)
{
    d->ck_abort = TRUE;
    return FALSE;
}
word near DCMoreOn(DSTK *d)
{
    d->automore = TRUE;
    return FALSE;
}
word near DCParseData(DSTK *d)
{
    DisplayDatacode(d);
    return FALSE;
}
word near DCMoreOff(DSTK *d)
{
    d->automore = FALSE;
    return FALSE;
}
word near DCNul(DSTK *d)
{
    DCNormal(d, 0);
    return FALSE;
}
word near DC8(DSTK *d)
{
    DCNormal(d, 0x08);
    return FALSE;
}
word near DC9(DSTK *d)
{
    DCNormal(d, 0x09);
    return FALSE;
}
word near DCe(DSTK *d)
{
    DCNormal(d, 0x0e);
    return FALSE;
}
word near DC11(DSTK *d)
{
    DCNormal(d, 0x11);
    return FALSE;
}
word near DC12(DSTK *d)
{
    DCNormal(d, 0x12);
    return FALSE;
}
word near DC13(DSTK *d)
{
    DCNormal(d, 0x13);
    return FALSE;
}
word near DC14(DSTK *d)
{
    DCNormal(d, 0x14);
    return FALSE;
}
word near DC15(DSTK *d)
{
    DCNormal(d, 0x15);
    return FALSE;
}
word near DC18(DSTK *d)
{
    DCNormal(d, 0x18);
    return FALSE;
}

#ifndef ORACLE
static void near DispReadline(DSTK *d, char *str, sword limit)
{
    word ch;
    char *p = str;

    while (--limit > 0 && (ch = DispSlowGetChar(d)) != '\n' && ch != DISP_EOF)
        *p++ = (char)ch;

    *p = '\0';
}
#endif

        {
            s1 = DispSlowGetChar(d);
            s2 = DispSlowGetChar(d);

                break;
        }
        else
            *s++ = (char)c;
    }

    for (s--; s >= orig && *s <= 32; s--)
        *s = '\0';
}

        DispGetToBlank(d, d->scratch);
        return PrivOK(d->scratch, FALSE) ? SKIP_NONE : SKIP_LINE;

    case 'B':
    case 'Q':
    case 'X':
        return (Priv_Code(DispSlowGetChar(d), ch));

    case 'F':
        ch = DispSlowGetChar(d);

        cantag = (local || (baud >= ClassGetInfo(cls, CIT_MIN_XFER_BAUD))) &&
                 CanAccessFileCommand(&fah, file_tag, 0, NULL);

        c = GetListAnswer(cantag ? MoreYnTag : Yne, NULL, cantag ? useyforyesnst : useyforyesns,
                          CINPUT_NOLF | CINPUT_DISPLAY,
                          cantag ? fbbs_more_promptt : fbbs_more_prompt);

        if (usr.video == GRAPH_TTY)
        {
            if (c == *Tag)
                Putc('\n');
            else
                Puts(moreynns_blank);
        }
        else
            Puts(fbbs_more_blank);

        if (c == *Tag && cantag)
        {
