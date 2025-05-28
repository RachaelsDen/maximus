// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_abbs.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#include "alc.h"
#include "dr.h"
#include "max.h"
#include "msgapi.h"
#include "prog.h"
#include "squish.h"
#include <ctype.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ABBS_LEN 4096


        if ((s = strchr(line, ';')) != NULL)
            *s = '\0';

        (void)Strip_Trailing(line, '\n');

        if (!*line)
            continue;


        if (!found_origin)
        {
            found_origin = TRUE;

            if (strchr(line, '!'))
            {
                line[MAXORIGIN] = '\0';

                free(config.origin);

                config.origin = sstrdup(line);

#endif
        (void)strcpy(orig, line);

        flag = 0;
        type = MSGTYPE_ECHO;
        path = strtok(line, abbs_delim);

            {
                type = MSGTYPE_SQUISH | MSGTYPE_ECHO;

                if (!*++path)
                    path = strtok(NULL, abbs_delim);
            }
        }

        tag = strtok(NULL, abbs_delim);

        if (!tag || *tag == '\0')
            continue;

#ifdef UNIX
        strupr(tag);
#endif


        ar = Declare_Area(path, tag, s ? orig + (word)(s - line) : NULL, type, flag);

        if (ar && (ar->flag & (AFLAG_DUPES | AFLAG_NET)))
        {
            S_LogMsg("!Attempted to redeclare area %s as EchoMail", ar->name);
            exit(ERL_ERROR);
        }
    }

    free(orig);
    free(line);

    (void)fclose(abbs);

    if (config.dupes == NULL)
        config.dupes = config.badmsgs;
}

struct _cfgarea *Declare_Area(char *path, char *tag, char *nodes, word type, word flag)
{
    static char unknown_flag[] = "Unknown area declaration flag: \"%s\"\n";
    NETADDR naddr;
    struct _cfgarea *ar, *newar;
    struct _sblist *sb, *sbcheck, last;
    struct _perlist *pl;

    (void)strupr(tag);

    newar = smalloc(sizeof(struct _cfgarea));


    ar->flag |= flag;
    ar->type |= type;


        if (config.addr == NULL)
        {
            (void)printf("Error!  An 'Address' statement must be given before defining\n"
                         "the first message area!\n");
            exit(ERL_ERROR);
        }

        ar->primary = *config.addr;


        ar->path = sstrdup(fancy_fn(path));

#ifndef UNIX

    last = ar->primary;

    if (!nodes)
        s = NULL;
    else
        s = strtok(nodes, abbs_delim);

    while (s)
    {
        last.point = 0;

        if (*s == '/' || *s == '-')
        {
            (void)strlwr(s);

            switch (s[1])
            {
            case 'h':
                ar->flag |= AFLAG_HIDEMSG;
                break;

                ar->flag |= AFLAG_PASSTHRU;
                break;

                ar->type |= MSGTYPE_SQUISH;
                ar->type &= ~MSGTYPE_SDM;

                switch (s[2])
                {
                case 'm':
                    ar->sq_max_msgs = (dword)atol(s + 3);
                    break;
                case 's':
                    ar->sq_save_msgs = (dword)atol(s + 3);
                    break;
                case 'd':
                    ar->sq_keep_days = (word)atoi(s + 3);
                    break;
                case '\0':
                    break;
                default:
                    (void)printf(unknown_flag, s);
                }
                break;

                ar->primary.point = 0;

                ParseNN(s + 2, &ar->primary.zone, &ar->primary.net, &ar->primary.node,
                        &ar->primary.point, FALSE);
                last = ar->primary;
                break;

                sb = smalloc(sizeof(struct _sblist));
                *sb = ar->primary;
                sb->point = 0;

                ParseNN(s + 2, &sb->zone, &sb->net, &sb->node, &sb->point, FALSE);

                sb->next = ar->update_ok;
                ar->update_ok = sb;
                break;


                pl = smalloc(sizeof(struct _perlist));

                pl->node = config.def;
                ParseNN(s + 2, &pl->node.zone, &pl->node.net, &pl->node.node, &pl->node.point,
                        FALSE);

                if ((p = strchr(s, ',')) == NULL)
                {
                    free(pl);
                    S_LogMsg("!Invalid personal flag: %s", s);
                }
                else
                {

                    for (p = pl->name; (p = strchr(p, '_')) != NULL;)
                        *p++ = ' ';

                sb = smalloc(sizeof(struct _sblist));
                *sb = ar->primary;
                sb->point = 0;

                ParseNN(s + 2, &sb->zone, &sb->net, &sb->node, &sb->point, FALSE);

                sb->next = ar->norecv;
                ar->norecv = sb;
                break;

            default:
                (void)printf(unknown_flag, s);
            }
        }
        else if (*s == '#')
            ar->flag |= AFLAG_PASSTHRU;
        else if (isdigit(*s) || *s == '.')
        {
            struct _statlist *sl;

            sb = smalloc(sizeof(struct _sblist));

            *sb = last;

            Parse_NetNode(s, &sb->zone, &sb->net, &sb->node, &sb->point);

            last = *sb;

            for (sbcheck = ar->scan; sbcheck; sbcheck = sbcheck->next)
                if (MatchSS(sbcheck, sb, FALSE))
                {
                    S_LogMsg("!Area %s: node %s specified twice", ar->name,
                             Address(SblistToNetaddr(sbcheck, &naddr)));
                    continue;
                }

            sb->next = ar->scan;
            ar->scan = sb;


                (void)SblistToNetaddr(sb, &sl->node);

                sl->next = ar->statlist;
                ar->statlist = sl;
            }
        }
        else
        {
            S_LogMsg("!Junk in area definition:  `%s'", s);
        }

        s = strtok(NULL, abbs_delim);

        ar->num_scan++;
    }

    if ((ar->type & (MSGTYPE_SDM | MSGTYPE_SQUISH)) == 0)
        ar->type |= MSGTYPE_SDM;

    return ar;
}
