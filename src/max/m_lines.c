// SPDX-License-Identifier: GPL-2.0-or-later


#include "max_msg.h"
#include "mm.h"
#include "string.h"

word Msg_Read_Lines(HMSG msgh, word msglines, word width, word soft_width, byte **outline,
                    byte linetype[], byte *last_line_attr, word flag)
{
    static char last_initials[20] = "";
    int howmuch;
    word temp, outl, hard, cnt;

    byte *msgbuffer, *msgbuf, *p;

    byte *msgend;
    byte *start, *s, *out, *end, *outend;
    byte *hardcr;

    if ((msgbuffer = malloc(BMSGBUFLEN)) == NULL)
    {
        logit(mem_nrmb);
        return 0;
    }


    if (width >= MAX_MSGWIDTH)
        width = MAX_MSGWIDTH;


    for (temp = 0; temp < msglines; temp++)
    {
        *outline[temp] = '\0';
        linetype[temp] = MSGLINE_NORMAL;
    }


    linetype[0] = (byte)(*last_line_attr & ~MSGLINE_SOFT);
    *last_line_attr = '\0';


    if ((mah.ma.attribs & MA_ECHO) && strncmp(msgbuf, "AREA:", 5) == 0 &&
        !GEPriv(usr.priv, prm.ctla_priv))
    {

        while (*msgbuf == (unsigned char)'\x8d' || *msgbuf == '\x0a')
            msgbuf++;
    }


    while ((!msgeof || msgbuf < msgend) && *msgbuf && outl < msglines)
    {

        while ((*msgbuf == (unsigned char)'\x8d' || *msgbuf == '\x0a') && msgbuf < msgend)
        {
            msgbuf++;
        }

        if (msgbuf >= msgend)
            break;


        memset(out = outline[outl], '\0', 10);


        end = msgbuf + width - strlen(out);
        end = min(end, msgend);

        hardcr = strchr(msgbuf + 1, '\r');

        if (hardcr)
            end = min(end, hardcr);


        if ((hardcr != NULL && (sword)(hardcr - msgbuf) > (sword)width - strlen(out) &&
             hardcr < msgend) ||
            ((outl == 0 ? *last_line_attr : linetype[outl - 1]) & MSGLINE_SOFT))
        {
            end = min(end, msgbuf + soft_width - strlen(out));
        }

        outend = outline[outl] + width;

        for (hard = FALSE;; msgbuf++)
        {
            if (*msgbuf == '\r' || *msgbuf == '\0')
            {
                hard = TRUE;

                if (*msgbuf == '\r')
                    msgbuf++;

                break;
            }

            if (msgbuf >= end || out >= outend)
                break;

            if (*msgbuf == '\t')
            {
                for (cnt = 8 - ((out - outline[outl]) % 8) && out < outend; cnt--;)
                    *out++ = ' ';
            }
            else if (*msgbuf >= ' ' && *msgbuf != (unsigned char)'\x8d')
                *out++ = *msgbuf;
        }

        *out = '\0';

        p = outline[outl];


        if ((p[0] == '>' || p[1] == '>' || p[2] == '>' || p[3] == '>' || p[4] == '>') &&
            (linetype[outl] & MSGLINE_LASTWRAP) == 0)
        {
            char *s;

            linetype[outl] |= MSGLINE_QUOTE;
            strncpy(last_initials, p, 10);
            last_initials[10] = '\0';

            if ((s = strrchr(last_initials, '>')) != NULL)
            {
                if (s[1] == ' ')
                    s[2] = '\0';
                else
                    s[1] = '\0';
            }
        }



            if (s < start)
                s = end;

            msgbuf = s + 1;


    MsgSetCurPos(msgh, MsgGetCurPos(msgh) - (long)(msgend - msgbuf));

    return outl;
}


word ShowBody(HMSG msgh, word (*handle)(byte *txt, void *info, word lt), void *info,
              word norm_margin, word quote_margin, word flag)
{
    byte *ol[MAX_MSGDISPLAY];
    byte lt[MAX_MSGDISPLAY];
    byte last_msg_attr;
    word line, got, n_ol;

    last_msg_attr = 0;

    if ((n_ol = Alloc_Outline(ol)) < 1)
        return FALSE;

    while ((got = Msg_Read_Lines(msgh, n_ol, norm_margin, quote_margin, ol, lt, &last_msg_attr,
                                 flag)) > 0)
    {
        for (line = 0; line < got; line++)
            if (!(*handle)(ol[line], info, lt[line]))
            {
                Dealloc_Outline(ol);
                return FALSE;
            }
    }

    Dealloc_Outline(ol);
    return TRUE;
}

struct _handinfo
{
    FILE *out;
    word quote;
    word change;
    byte *initials;
    word num_n;
};


    if (!*txt)
    {
        hi->num_n++;
        return TRUE;
    }

    while (hi->num_n)
    {
        fputc('\n', hi->out);
        hi->num_n--;
    }

    if (hi->quote && QuoteThisLine(txt))
        fprintf(hi->out, " %s> ", hi->initials);

    fprintf(hi->out, "%s\n", txt);

    return TRUE;
}

int MsgBodyToFile(HMSG msgh, FILE *out, int quote, int chng, byte *initials, word flag)
{
    struct _handinfo hi;
    word mquote, mnormal;
    word len;

    hi.out = out;
    hi.quote = quote;
    hi.change = chng;
    hi.initials = initials;
    hi.num_n = 0;


    if (quote)
    {
        len = strlen(initials) + 3;

        mquote -= len;
        mnormal -= len;
    }
    else
        mquote = mnormal;

    return (ShowBody(msgh, BodyToFile, (void *)&hi, mnormal, mquote, flag));
}

long Read_Chars(HMSG msgh, char *s, int num)
{
    long n;

    if ((n = MsgReadMsg(msgh, NULL, MsgGetCurPos(msgh), num, s, 0L, NULL)) <= 0 || *s == '\0')
        msgeof = TRUE;

    return n;
}
