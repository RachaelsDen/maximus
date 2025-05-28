// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: killrcat.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#include <string.h>

#define INCL_VIO
#define INCL_DOS

#include "msgapi.h"
#include "prog.h"
#include "sqfeat.h"
#include <os2.h>

#define FLAG_BODY 0x01
#define FLAG_TO 0x02
#define FLAG_FROM 0x04
#define FLAG_SUBJ 0x08
#define FLAG_CASE 0x10
#define FLAG_EXCT 0x20

struct _kksearch
{
    int flag;
    char *txt;
    char *area;
    struct _kksearch *next;
};

static struct _kksearch *gpSearch;


    unsigned last_found = 0;
    unsigned strlen_search = strlen(search);
    byte l1, l2;
    unsigned i;

    if (string)
    {
        while (*string)
        {
            else
            {
                if (last_found != 0)
                {
                    string -= last_found - 1;
                    last_found = 0;
                    continue;
                }
            }

            string += l1;

            if (last_found == strlen_search)
                return (string - last_found);
        }
    }

    return (NULL);
}

int tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        c = 'a' + (c - 'A');

    return c;
}

char *firstchar(char *strng, char *delim, int findword)
{
    int x, isw, wordno = 0;
    unsigned sl_d, sl_s;

    char *string, *oldstring;


word FEATENTRY _export FeatureInit(struct _feat_init far *pfi)
{

    strcpy(pfi->szConfigName, "Killrcat");
    return 0;
}


word FEATENTRY _export FeatureConfig(struct _feat_config far *pfc)
{
    struct _kksearch *ps;
    char *p;

    NW(pfc);

    if ((ps = malloc(sizeof(struct _kksearch))) == NULL)
        return 0;

    ps->flag = 0;

    for (p = pfc->ppszArgs[1]; p && *p; p++)
        switch (tolower(*p))
        {
        case 'b':
            ps->flag |= FLAG_BODY;
            break;
        case 's':
            ps->flag |= FLAG_SUBJ;
            break;
        case 't':
            ps->flag |= FLAG_TO;
            break;
        case 'f':
            ps->flag |= FLAG_FROM;
            break;
        case 'c':
            ps->flag |= FLAG_CASE;
            break;
        case 'e':
            ps->flag |= FLAG_EXCT;
            break;

        default:
            VioPuts("Invalid KillrCat flag: `");
            VioPutc(*p);
            VioPuts("\r\n");
            break;
        }

    if (!pfc->ppszArgs[1] || !pfc->ppszArgs[2] || !pfc->ppszArgs[3])
    {
        VioPuts("Invalid configuration line: `");
        VioPuts(pfc->szConfigLine);
        VioPuts("\r\n");
        return 0;
    }

    ps->area = strdup(pfc->ppszArgs[2]);
    ps->txt = strdup(firstchar(pfc->szConfigLine, " \t\n", 4));

    ps->next = gpSearch;
    gpSearch = ps;

    return 0;
}


word FEATENTRY _export FeatureNetMsg(struct _feat_netmsg far *pfn)
{
    NW(pfn);
    return 0;
}

static int near exactcomp(char *t1, char *t2) { return (strcmp(t1, t2) == 0); }

static int near incomp(char *t1, char *t2)
{
    int x;

    x = !!stristr(t2, t1);
