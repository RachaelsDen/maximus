// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_match.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#define NOVARS

#include "s_match.h"
#include "alc.h"
#include "max.h"
#include "prog.h"
#include "squish.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MATCHOUT *MatchOutOpen(NETADDR *who, int type, byte flavour)
{
    MATCHOUT *mo;
    extern struct _hpkt *hpl;

    if (config.flag & FLAG_FRODO)
        return (HoleMatchOutOpen(who, type, flavour));

    if ((mo = (MATCHOUT *)malloc(sizeof(MATCHOUT))) == NULL)
        return NULL;

    if (who->zone == ZONE_ALL)
    {

        mo->cur_ob = (sword)FindOutbound(who->zone);
        mo->high_ob = mo->cur_ob + 1;
    }

    if (mo->cur_ob == -1 || mo->high_ob == -1)
    {
        free(mo);
        return (HoleMatchOutOpen(who, type, flavour));
    }

    mo->ff = mo->parentff = NULL;
    mo->who = *who;
    mo->flavour = flavour;
    mo->type = (sword)type;
    mo->config = &config;
    mo->hpkt = hpl;

    if (!MatchOutNext(mo))
    {
        free(mo);
        return NULL;
    }

    return (mo);
}

int MatchOutNext(MATCHOUT *mo)
{
    char net[20];
    char node[20];
    char doname[PATHLEN];
    char temp[PATHLEN];
    byte *p;

    int found;

    mo->got_type = 0;
    mo->fFromHole = FALSE;

    if (config.flag & FLAG_FRODO)
        return (HoleMatchOutNext(mo));

    if (mo->cur_ob >= mo->high_ob)
        return (HoleMatchOutNext(mo));

        {

            if (mo->who.net == NET_ALL)
                (void)strcpy(net, fourqs);
            else
                (void)sprintf(net, p04x, mo->who.net);

            if (mo->who.node == NODE_ALL)
                (void)strcpy(node, fourqs);
            else
                (void)sprintf(node, p04x, mo->who.node);


            (void)sprintf(temp, "%s%s%s.*", FixOutboundName(config.ob[mo->cur_ob]), net, node);

            mo->ff = FindOpen(temp, MSDOS_SUBDIR);
        }

            FindClose(mo->ff);
            mo->ff = NULL;
        }


        if (mo->ff == NULL)
        {
            mo->ff = mo->parentff;
            mo->parentff = NULL;


            if (FindNext(mo->ff) != 0)
            {
                FindClose(mo->ff);
                mo->ff = NULL;
            }
        }

        if (mo->ff == NULL)
        {

            if (++mo->cur_ob >= mo->high_ob)
                return (HoleMatchOutNext(mo));
            else
            {

                continue;
            }
        }


#ifndef UNIX
        if ((p = strchr(strupr(mo->ff->szName), '.')) != NULL)
#else
        if ((p = strchr(mo->ff->szName, '.')) != NULL)
#endif
        {

            if (p[1] == 'P' && p[2] == 'N' && p[3] == 'T' && mo->who.point)
            {

                if (mo->who.point == POINT_ALL)
                    (void)strcat(temp, "*.*");
                else
                    (void)sprintf(temp + strlen(temp), "%08hx.*", mo->who.point);


                mo->parentff = mo->ff;


                    mo->found.zone = config.ob[mo->cur_ob];


                if (mo->ff == NULL)
                {
                    mo->got_type = found = MATCH_UNKNOWN;
                    mo->ff = mo->parentff;
                    mo->parentff = NULL;
                }
                else
                {
                    char *oldp = p;



                mo->flavour = (byte)toupper(mo->flavour);

                if (mo->flavour == 0 || mo->flavour == p[1] ||
                    (mo->flavour == 'F' && p[1] == 'O') || (mo->flavour == 'O' && p[1] == 'F') ||
                    (mo->flavour == 'L' && p[1] == 'N') || (mo->flavour == 'U' && p[1] != 'N'))
                {

                            mo->found.zone = config.ob[mo->cur_ob];
                            mo->found.point = 0;
                        }
                    }

                    (void)strcpy(doname, FixOutboundName(config.ob[mo->cur_ob]));

        }
    }


    (void)strcpy(mo->name, doname);
#ifndef UNIX
    (void)strupr(mo->name);
#endif
    return 1;
}

void MatchOutClose(MATCHOUT *mo)
{
    if (mo)
    {
        if (config.flag & FLAG_FRODO)
        {
            HoleMatchOutClose(mo);
            return;
        }

        if (mo->ff)
            FindClose(mo->ff);

        free(mo);
    }
}

static int near FindOutbound(word zone)
{
    int i;

    for (i = (int)config.num_ob - 1; i >= 0; i--)
        if (config.ob[i] == zone)
            return i;

    return -1;
}
