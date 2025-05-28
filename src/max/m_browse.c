// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_browse.c,v 1.1.1.1 2002/10/01 17:52:38 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_m_browse

#include "m_browse.h"
#include "dr.h"
#include "max_msg.h"
#include "prog.h"
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int last_title;
extern int idling;


        if (!PushMsgArea(usr.msg, 0))
            ret = -1;
        else
        {
            ret = Browse_Scan_Areas(&b);


        ForceGetMsgArea();
    }

    if (b.wildcard)
        free(b.wildcard);

    Deinit_Search(b.first);
    in_mcheck = FALSE;

    if ((b.bflag & BROWSE_LIST) && !nonstop && MenuNeedMore())
    {
        Puts(CYAN);
        MoreYnns();
    }

    return ret;
}


        while ((b->bflag & (BROWSE_AWLD | BROWSE_AGRP)) && !b->wildcard)
        {
            char temp[PATHLEN];

            if (b->bflag & BROWSE_AGRP)
                b->wildcard = strdup(MessageSection(usr.msg, temp));
            else
            {
                char wc[PATHLEN];

                WhiteN();
                InputGetsL(wc, PATHLEN - 1, br_which_areas);
                Puts(browse_which_c);

                if (!*wc)
                    return -1;

                b->wildcard = strdup(wc);
            }
        }

        if (!*linebuf)
            Puts(browse_select_c);
    }

    return 0;
}


    va_start(varg, cowabunga);

    first = TRUE;

    t_name = va_arg(varg, char *);
    t_true = va_arg(varg, int);

    while (t_name)
    {
        do
        {
            n_name = va_arg(varg, char *);

            if (n_name)
                n_true = va_arg(varg, int);
            else
                n_true = FALSE;
        } while (n_name && !n_true);

        if (t_true)
        {
            if (!first)
            {
                Puts(br_comma);

                if (!n_name)
                    Puts(br_then_or);
            }

            Puts(t_name);
            first = FALSE;
        }

        t_true = n_true;
        t_name = n_name;
    }

    va_end(varg);
}

static void near Browse_Display_Search_Criteria(SEARCH *first)
{
    SEARCH *s;


    Puts(br_max_will);

    for (s = first; s; s = s->next)
    {
        if (!s->txt)
            continue;

        if (s != first)
        {
            if (s->flag & SF_OR)
                Puts(br_or);
            else
                Puts(br_and);
        }

        Printf(br_in_the_xxx_fields, s->txt);

        Browse_Show_List(NULL, br_field_to, (int)(s->where & WHERE_TO), br_field_from,
                         (int)(s->where & WHERE_FROM), br_field_subj, (int)(s->where & WHERE_SUBJ),
                         br_field_body, (int)(s->where & WHERE_BODY), NULL);

        if ((s->where & WHERE_BODY) == 0)
            Puts(br_field_maybe_plural);

        Putc('\n');
    }
}

static int near Browse_Get_Search_Where(SEARCH *s, BROWSE *b)
{
    char temp[PATHLEN];
    byte *p;

    while ((s->where & WHERE_ALL) == 0)
    {
        AlwaysWhiteN();

        if (usr.help == NOVICE && !*linebuf)
        {
            Puts(br_s_where_verbose);
            InputGets(temp, browse_select_s);
        }
        else
            InputGets(temp, br_s_where);

        if (!*linebuf)
            Puts(browse_select_c);

        if (!*temp)
            return -1;

        strupr(temp);

        for (p = temp; *p; p++)
        {
            if (*p == br_sk[0])
                s->where |= WHERE_TO;
            else if (*p == br_sk[1])
                s->where |= WHERE_FROM;
            else if (*p == br_sk[2])
                s->where |= WHERE_SUBJ;
            else if (*p == br_sk[3])
            {
                s->where |= WHERE_BODY;
                b->bflag |= BROWSE_GETTXT;
            }
            else if (*p == br_sk[4])
                return -1;
            else if (*p == br_sk[5])
                Display_File(0, NULL, browse_fname, PRM(misc_path));
            else
                Printf(dontunderstand, *p);
        }
    }

    return 0;
}

static int near Browse_Get_Search_Next(SEARCH *s)
{
    byte ch;

    if (!*linebuf)
    {
        Putc('\n');

        Puts(br_s_opt_lim + 1);
        Puts(br_s_opt_exp + 1);
        Puts(br_s_opt_go + 1);
        Puts(br_s_opt_quit + 1);

        Putc('\n');
    }

    do
    {
        ch = (byte)KeyGetRNP(browse_select_s);

        if (ch == *br_s_opt_lim)
        {
            s->next = malloc(sizeof(SEARCH));

            if (s->next)
            {
                Init_Search(s->next);
                s->next->flag = SF_AND;
            }
        }
        else if (ch == *br_s_opt_exp)
        {
            s->next = malloc(sizeof(SEARCH));

            if (s->next)
            {
                Init_Search(s->next);
                s->next->flag = SF_OR;
            }
        }
        else if (ch == *br_s_opt_go)
            s->next = NULL;
        else if (ch == '?')
            Display_File(0, NULL, browse_fname, PRM(misc_path));
        else if (ch == *br_s_opt_quit || ch == '\0' || ch == '\r')
        {
            Puts(browse_select_c);
            return -1;
        }
        else
            Printf(dontunderstand, ch);
    } while (s->next == NULL && ch != *br_s_opt_go);

    if (!*linebuf)
        Puts(browse_select_c);

    return 0;
}

static int near Browse_Get_Search_Text(SEARCH *s)
{
    char temp[PATHLEN];

    WhiteN();
    InputGetsLL(temp, PATHLEN - 1, br_text_to_search);

    if (!*linebuf)
        Puts(browse_select_c);

    if (!*temp)
        return -1;

    s->txt = strdup(temp);

    return 0;
}

static int near Browse_Get_Search(BROWSE *b)
{
    SEARCH *s;
    int crit;

    s = b->first;
    crit = 0;

    do
    {
        if (Browse_Get_Search_Where(s, b) == -1)
            return -1;

        if (Browse_Get_Search_Text(s) == -1)
            return -1;

        Browse_Display_Search_Criteria(b->first);

        if (Browse_Get_Search_Next(s) == -1)
            return -1;

        s = s->next;

    } while (s && ++crit <= 16);

    b->bflag |= BROWSE_SEARCH;

    return 0;
}

static int near Browse_Get_Type(BROWSE *b)
{
    SEARCH *s;
    char temp[PATHLEN];
    byte ch;

    if ((b->bflag & BROWSE_TYPE) == 0 && b->first->txt == NULL)
    {
        do
        {
            WhiteN();

            if (usr.help == NOVICE && !*linebuf)
            {
                Puts(br_type_verbose);
                ch = (byte)toupper(KeyGetRNP(browse_select_s));
            }
            else
                ch = (byte)toupper(KeyGetRNP(br_type));

            if (ch == br_typek[0])
                b->bflag |= BROWSE_ALL;
            else if (ch == br_typek[1] || ch == '\r' || ch == '\0')
                b->bflag |= BROWSE_NEW;
