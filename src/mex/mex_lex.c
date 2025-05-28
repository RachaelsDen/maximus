// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mex_lex.c,v 1.2 2003/06/05 01:10:36 wesgarland Exp $";
#pragma on(unreferenced)

#include "mex.h"
#include "mex_lexp.h"
#include "prog.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern YYSTYPE yylval;
static MACRO macro = {0};
static MACDEF macList = NULL;
static FILESTACK fstk[MAX_INCLUDE];
static int iStack = -1;
static XLTABLE xlt[] = {{'n', '\n'}, {'r', '\r'}, {'a', '\a'}, {'b', '\b'},
                        {'f', '\f'}, {'v', '\v'}, {'t', '\t'}, {0, 0}};

static byte ifstatus[MAX_IFBLKS];
static byte ifdone[MAX_IFBLKS];
static int iBlock = -1;


int pop_fstk(void)
{
    if (iStack < 0)
        return FALSE;

    fclose(fstk[iStack].fp);

    if (fstk[iStack].name)
    {
        free(fstk[iStack].name);
        fstk[iStack].name = NULL;
    }


    if (--iStack >= 0)
        strcpy(filename, fstk[iStack].name);

    return TRUE;
}


int pull_character(void)
{
    int ch = EOF;

    if (macro.fInMacro)
    {
        if (macro.iPos >= macro.md->iLength - 1)
            macro.fInMacro = FALSE;

#ifdef DEBUGLEX
        printf("%c*", macro.md->szText[macro.iPos]);
#endif
        return macro.md->szText[macro.iPos++];
    }


int peek_character(void)
{
    int ch, i;

    if (macro.fInMacro)
        return macro.md->szText[macro.iPos];

    i = iStack;


static int near process_colon(void)
{
    int c;

    if ((c = peek_character()) == '=')
    {
        pull_character();
        return T_ASSIGN;
    }

    return T_COLON;
}


static int near process_lessthan(void)
{
    int c;

    if ((c = peek_character()) == '=')
    {
        pull_character();
        return T_LE;
    }

    if (c == '>')
    {
        pull_character();
        return T_NOTEQUAL;
    }

    return T_LT;
}

        return TRUE;


static int near process_digit(int c)
{
    word type = TYPE_DEC;
    int fLong = FALSE;
    int fUnsigned = FALSE;
    char *scan;
    char *p, *e;


    *p++ = (char)c;


    while (p < e && (c = peek_character()) != EOF && (isxdigit(c) || tolower(c) == 'x'))
    {
        pull_character();
        *p++ = (char)c;
    }

    *p = '\0';


    if (p == e)
        warn(MEXERR_WARN_CONSTANTTRUNCATED, yytext);


    do
    {
        c = peek_character();
        c = tolower(c);

        if (c == 'l')
        {
            fLong = TRUE;
            pull_character();
        }


        if (c == 'u')
        {
            fUnsigned = TRUE;
            pull_character();
        }
    } while (c == 'l' || c == 'u');

    scan = yytext;


    if (yylval.constant.dwval < 65536L && !fLong)
    {
        yylval.constant.val = (word)yylval.constant.dwval;
        return T_CONSTWORD;
    }

    return T_CONSTDWORD;
}


    if ((c = pull_character()) == EOF || c == '\n' || c == '\r')
    {
        error(MEXERR_UNTERMCHARCONST);
        if (c == '\n')
            linenum++;
        return FALSE;
    }


    if (pull_character() != '\'')
    {
        error(MEXERR_INVALCHARCONST);
        return FALSE;
    }

    return TRUE;
}


    str = sptr = smalloc(slen = STR_BLOCK);


        if (sptr - str >= slen - 1)
        {
            olds = str;
            str = realloc(str, slen += STR_BLOCK);

            if (str == NULL)
                NoMem();

            sptr = str + (sptr - olds);
        }


            while ((c = peek_character()) == ' ' || c == '\t' || c == '\n' || c == '\r')
            {
                if (pull_character() == '\n')
                    linenum++;
            }


            if (c == '"')
                pull_character();
            else
                break;
        }

            if ((c = pull_character()) == EOF)
                break;

            for (x = xlt; x->from; x++)
                if (c == x->from)
                {
                    *sptr++ = x->to;
                    break;
                }


            if (!x->from)
            {
        {
            *sptr++ = (char)c;
        }
    }

    if (c == EOF)
        error(MEXERR_UNTERMSTRINGCONST);

    *sptr = '\0';
    yylval.constant.lit = str;

    return T_CONSTSTRING;
}


    if (md != NULL)
    {
        if (md == macList)
            macList = md->next;
        else
        {
            MACDEF dd;

            for (dd = macList; dd->next != md; dd = dd->next)
                ;
            dd->next = md->next;
        }
        free(md->szName);
        free(md->szText);
        free(md);
    }
}


    p = m + strlen(m) + 1;
    strtok(p, "\n");

    if ((md = find_macro(m)) != NULL)
    {

    md->szName = strdup(m);
    md->szText = strdup(p);
    md->iLength = strlen(md->szText);


static void near process_ifdef(char *line, byte inblock, byte which)
{
    char *p;

    if ((p = strtok(line, " \t\n")) == NULL)
    {
        error(MEXERR_INVALIDIFDEF);
        return;
    }

    if (++iBlock >= MAX_IFBLKS)
    {
        error(MEXERR_TOOMANYNESTEDIFDEF);
        iBlock--;
    }

    if (!inblock)
        ifstatus[iBlock] = 0;
    else
        ifstatus[iBlock] = find_macro(p) ? which : !which;

    ifdone[iBlock] = ifstatus[iBlock];
}

static void near process_endif()
{
    if (iBlock-- == -1)
    {
        error(MEXERR_UNMATCHEDENDIF);
        iBlock = 0;
    }
}

static void near process_else()
{
    if (iBlock == -1)
        error(MEXERR_UNMATCHEDELSE);
    else
    {

        if (ifdone[iBlock])
            ifstatus[iBlock] = 0;


        if (ifstatus[iBlock])
        {
            int i;

            for (i = iBlock; i-- > 0;)
            process_ifdef(line, TRUE, TRUE);
        }
    }
}


    for (s = ppbuf; s < ppbuf + PPLEN - 1 && (*s = (char)peek_character()) != EOF && *s != '\n';
         s++)
    {
        pull_character();
    }


    *++s = '\0';


        if ((p = strstr(s, "//")) != NULL)
            *p = 0;


static int near process_dot(void)
{
    int c;


    if ((c = peek_character()) == '.')
    {
        pull_character();

        if ((c = peek_character()) == '.')
        {
            pull_character();
            return T_ELLIPSIS;
        }

        return T_RANGE;
    }


static int near process_id(int c, int *prc)
{
    MACDEF md;
    struct _id *i;
    char *p, *e;


    p = yytext;
    e = yytext + MAX_ID_LEN - 1;


    for (*p++ = (char)c; (*p = (char)peek_character()) != EOF && isidchar(*p) && p < e; p++)
        pull_character();


    for (i = idlist; i->name; i++)
        if (eqstri(yytext, i->name))
        {
            *prc = i->value;
            return TRUE;
        }


    yylval.id = strdup(yytext);

    if (!macro.fInMacro && (md = find_macro(yytext)) != NULL)
    {
        macro.fInMacro = TRUE;
        macro.iPos = 0;
        macro.md = md;

        return FALSE;
    }

    *prc = T_ID;
    return TRUE;
}


    while ((c = pull_character()) != EOF)
    {

                break;
            }
        }
        else
        {
            switch (c)
            {
            case '\n':
                linenum++;
                break;
            case ' ':
            case '\t':
            case '\r':
                break;
            case '{':
                return T_BEGIN;
            case '}':
                return T_END;
            case ':':
                return process_colon();
            case '=':
                return T_EQUAL;
            case '>':
                return process_morethan();
            case '<':
                return process_lessthan();
            case '*':
                return T_BMULTIPLY;
            case '&':
                return T_BAND;
            case '|':
                return T_BOR;
            case '/':
                if (process_slash())
                    return T_BDIVIDE;
                break;
            case '%':
                return T_BMODULUS;
            case '+':
                return T_BPLUS;
            case '-':
                return T_MINUS;
            case '(':
                return T_LPAREN;
            case ')':
                return T_RPAREN;
            case '[':
                return T_LBRACKET;
            case ']':
                return T_RBRACKET;
            case ',':
                return T_COMMA;
            case ';':
                return T_SEMICOLON;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return process_digit(c);
            case '\'':
                if (process_character_constant())
                    return T_CONSTBYTE;
                break;
            case '\"':
                return process_string();
            case '#':
                process_preprocessor(TRUE);
                break;
            case '.':
                return process_dot();
                break;
            default:
                if (process_id(c, &rc))
                    return rc;
                break;

    if (iBlock != -1)
        error(MEXERR_UNMATCHEDIFDEF);

