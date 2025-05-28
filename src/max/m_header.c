// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_header.c,v 1.2 2003/06/04 23:51:24 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_m_area

#include "keys.h"
#include "m_full.h"
#include "max_msg.h"
#include "mm.h"
#include "node.h"
#include "prog.h"
#include "userapi.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static int near SendWarnings(PMAH pmah);
static int near IsHeaderOkay(XMSG *msg, PMAH pmah);
static int near Parse_Alias_File(XMSG *msg, char *netnode);


int GetMsgAttr(XMSG *msg, PMAH pmah, char *mname, long mn, long highmsg)
{
    int ret;


    if (pmah->ma.attribs & MA_REAL)
    {
        memset(msg->from, 0, sizeof msg->from);
        strcpy(msg->from, usr.name);
    }
    else if ((pmah->ma.attribs & MA_ALIAS) && *usr.alias)
    {
        memset(msg->from, 0, sizeof msg->from);
        strcpy(msg->from, usr.alias);
    }


    if (SendWarnings(pmah) == -1)
        return -1;

    ret = 0;


    if (mn == 0)
        FixPrivateStatus(msg, pmah);

    Puts(enter_header_init);


    if ((pmah->ma.type & MSGTYPE_SDM) && zfree(PMAS(pmah, path)) < 10000L)
    {
        Puts(warn_splow);
        Press_ENTER();
    }


    if (!*msg->to)
    {
        return -1;
    }

    if (!*msg->subj && ((pmah->ma.attribs & (MA_NET | MA_ATTACH)) != (MA_NET | MA_ATTACH) ||
                        (msg->attr & MSGFILE) == 0))
    {
        return -1;
    }


    if ((pmah->ma.attribs & MA_ANON) && isblstr(msg->from))
        strcpy(msg->from, (pmah->ma.attribs & MA_REAL)                    ? (char *)usr.name
                          : ((pmah->ma.attribs & MA_ALIAS) && *usr.alias) ? (char *)usr.alias
                                                                          : (char *)usrname);

    if (strpbrk(msg->to, "@!") == NULL || strchr(msg->to, ' '))
        fancier_str(msg->to);

    if (strpbrk(msg->from, "@!") == NULL || strchr(msg->from, ' '))
        fancier_str(msg->from);


    if ((pmah->ma.attribs & MA_ATTACH) == 0 && (msg->attr & (MSGFILE | MSGURQ)))
    {
        temp = strdup(msg->subj);

        for (st = strtok(temp, cmd_delim); st; st = strtok(NULL, cmd_delim))
        {
            p = st;

            if (*p == '#' || *p == '^')
                p++;

            if (!fexist(p))
            {
                Printf(a_noex, p);
                Press_ENTER();
            }
        }
    }

    if (pmah->ma.attribs & MA_NET)
        return (CheckCredit(&msg->dest, pmah));
    else
        return 0;
}


    if ((huf = UserFileOpen(PRM(user_file), 0)) == NULL)
    {
        cant_open(PRM(user_file));
        return FALSE;
    }

    rc = UserFileFind(huf, name, NULL, &user) || UserFileFind(huf, NULL, name, &user);

    if (!show_us && (eqstri(name, usr.name) || eqstri(name, usr.alias)))
        rc = FALSE;

    UserFileClose(huf);

    return rc;
}

int CheckCredit(NETADDR *dest, PMAH pmah)
{
    NFIND *nf;
    int cost;

    if (!(pmah->ma.attribs & MA_NET))
        return 0;

    if ((nf = NodeFindOpen(dest)) == NULL)
    {
        if (!GEPriv(usr.priv, prm.unlisted_priv))
        {
            Puts(unlisteddest);
            Press_ENTER();
            return -1;
        }

        cost = prm.unlisted_cost;
    }
    else
    {
        cost = nf->found.cost;
        NodeFindClose(nf);
    }

    if (mailflag(CFLAGM_NETFREE))
        cost = 0;

    if (usr.debit + cost > usr.credit)
    {
        Puts(ncredit);
        Press_ENTER();
        return -1;
    }

    return 0;
}

int Get_FidoList_Name(XMSG *msg, char *netnode, char *fidouser)
{
    NETADDR *d;
    FILE *ulfile;

    char line[120];
    char name[60], *p;

    long lo, hi, last, tryit;
    int linelen, comp;


    if (prm.nlver == NLVER_7)
    {
        struct _newnode node;
        NETADDR dest;

        if (V7FindName(msg->to, &dest, &node, PRM(net_info)))
        {
            strcpy(netnode, Address(&dest));
            return TRUE;
        }
    }

    for (p = msg->to; *p && *p != ' '; p++)
        ;

#endif


#if !defined(__GNUC__)
        sprintf(name, "%s %-0.*s", p + 1, p - msg->to, msg->to);
#else
#else
    sprintf(name, "%s %s", p + 1, msg->to);
#endif

    if ((ulfile = shfopen(fidouser, fopen_readb, O_RDONLY | O_BINARY | O_NOINHERIT)) == NULL)
        return FALSE;


        fseek(ulfile, 0L, SEEK_END);

        if (linelen)
        {
            hi = ftell(ulfile) / linelen;


                    p = line + strlen(name);


                    if (isdigit(*p))
                    {
                        d = &msg->dest;
                        MaxParseNN(p, d);
                        strcpy(netnode, Address(d));
                    }

                    break;
                }
                else if (comp < 0)
                    hi = tryit;
                else
                    lo = tryit;
            }
        }
    }

    fclose(ulfile);

    return (*netnode != '\0');
}

static int near Parse_Alias_File(XMSG *msg, char *netnode)
{
    FILE *alias;
    char temp[PATHLEN];
    char *tptr;
    char *p;
    int gotit;

#ifndef UNIX
    sprintf(temp, "%sNAMES.MAX", PRM(sys_path));
#else
    sprintf(temp, "%snames.max", PRM(sys_path));
#endif

    if ((alias = shfopen(temp, fopen_read, O_RDONLY | O_NOINHERIT)) == NULL)
        return FALSE;

    gotit = FALSE;

    while (fgets(temp, PATHLEN, alias) != NULL)
    {
        tptr = temp;

        Strip_Trailing(tptr, '\n');


        if (*tptr == '*')
        {
            if (!mailflag(CFLAGM_ATTRANY))
                continue;

            tptr++;
        }

        if ((p = strtok(tptr, comma)) == NULL)
            continue;

        if (eqstri(p, "end"))
            break;

        if (eqstri(msg->to, p))
        {
            if ((p = strtok(NULL, comma)) == NULL)
                continue;

            strcpy(msg->to, p);

            if ((p = strtok(NULL, comma)) != NULL)
            {
                strcpy(netnode, p);

                if ((p = strtok(NULL, comma)) != NULL)
                    strcpy(msg->subj, p);
            }

            gotit = TRUE;
            break;
        }
    }

    fclose(alias);

    return gotit;
}

int AreaIsReadOnly(PMAH pmah)
{
    char temp[PATHLEN];


    if ((pmah->ma.attribs & MA_READONLY) && !mailflag(CFLAGM_RDONLYOK))
    {
        char *roname = "%sreadonly.bbs";
        char *sroname = "%s.sqx";
        char *rname = ((pmah->ma.type & MSGTYPE_SDM) ? roname : sroname);
        char *path = MAS(*pmah, path);


            Puts(rd_only);
            Press_ENTER();
        }

        return TRUE;
    }

    return FALSE;
}

void FixPrivateStatus(XMSG *msg, PMAH pmah)
{
    int i;


    if ((pmah->ma.attribs & (MA_PUB | MA_PVT)) == (MA_PUB | MA_PVT))
        ;
    else if (pmah->ma.attribs & MA_PVT)
        msg->attr |= MSGPRIVATE;
    else if (pmah->ma.attribs & MA_PUB)
        msg->attr &= ~MSGPRIVATE;

