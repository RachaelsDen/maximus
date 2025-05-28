// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: node.c,v 1.1.1.1 2002/10/01 17:52:53 sdudley Exp $";
#pragma on(unreferenced)

#include "node.h"
#include "fdnode.h"
#include "mm.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int namecomp(void *n1, void *v2);
int addrcomp(void *v1, void *v2);
int phcomp(void *s1, void *r2);

static int near V56FindOpen(NFIND *nf);
static NFIND *near V7FindOpen(NFIND *nf);
static NFIND *near FDFindOpen(NFIND *nf);
static word near FDCostOf(int fdafd, word rec_num);
static word near FDLookUpCost(struct _johofile *jf, struct _johonode *jn);

NFIND *NodeFindOpen(NETADDR *find)
{
    NFIND *nf;

    if ((nf = malloc(sizeof(NFIND))) == NULL)
        return NULL;

    memset(nf, 0, sizeof *nf);

    nf->find = *find;


    tofind = nf->find;

    if (V7FindNode(&tofind, &node6, PRM(net_info)) ||
        (tofind.point && (tofind.point = 0, V7FindNode(&tofind, &node6, PRM(net_info)))))
    {
        nf->found.zone = tofind.zone;
        nf->found.net = tofind.net;
        nf->found.node = tofind.node;
        nf->found.point = tofind.point;
        nf->found.cost = node6.Cost;

        strcpy(nf->found.name, node6.SystemName);
        strcpy(nf->found.phone, node6.PhoneNumber);
        strcpy(nf->found.city, node6.MiscInfo);
        nf->found.flag = node6.NodeFlags;
        return nf;
    }

    NodeFindClose(nf);
    return NULL;
}

static NFIND *near FDFindOpen(NFIND *nf)
{
    struct _johonode jn;
    struct _johofile jf;
    int good = FALSE;
    struct _fdx found;
    NETADDR find;

    find = nf->find;
    find.point = 0;

    if (JoHoOpen(PRM(net_info), &jf, FALSE))
    {
        if (JoHoLookup(jf.fdfd, sizeof(struct _fdb), sizeof(struct _fdx), &find, &found,
                       addrcomp) &&
            JoHoFetch(&found, &jf, &jn))
        {
            nf->found.zone = (found.zone_hi << 8) | found.zone_lo;
            nf->found.net = (found.net_hi << 8) | found.net_lo;
            nf->found.node = (found.node_hi << 8) | found.node_lo;
            nf->found.point = (found.point_hi << 8) | found.point_lo;

            nf->found.cost = FDLookUpCost(&jf, &jn);

            strcpy(nf->found.name, jn.system);
            strcpy(nf->found.phone, jn.phone);
            strcpy(nf->found.city, jn.city);
            nf->found.flag = 0;
            good = TRUE;
        }

        JoHoClose(&jf);

        if (good)
            return nf;
    }

    NodeFindClose(nf);
    return NULL;
}


static word near FDLookUpCost(struct _johofile *jf, struct _johonode *jn)
{
    static char our_prefix[20] = "";
    static int got_prefix = FALSE;
    struct _pdx p;
    word cost = 0;

    char name[PATHLEN];
    char phone[60];
    char *s;

    int phfd, fdafd, got;

    sprintf(name, "%sPHONE.FDX", PRM(net_info));


    while ((got = JoHoLookup(phfd, sizeof(struct _pdb), sizeof(struct _pdx), phone, &p, phcomp)) ==
           0)
    {
        Strip_Trailing(phone, '-');

        if ((s = strrchr(phone, '-')) != NULL && s[1])
            s[1] = '\0';
        else
            break;
    }


        if (!got_prefix)
        {
            struct _fdx found;
            struct _johonode our_jn;
            NETADDR prim;


            got_prefix = TRUE;

            prim = prm.address[0];

            if (JoHoLookup(jf->fdfd, sizeof(struct _fdb), sizeof(struct _fdx), &prim, &found,
                           addrcomp) &&
                JoHoFetch(&found, jf, &our_jn))
            {
                char *s;

                strncpy(our_prefix, our_jn.phone, 19);


        if (*our_prefix == '\0' || eqstrn(jn->phone, our_prefix, strlen(our_prefix)))
        {
            if (JoHoLookup(phfd, sizeof(struct _pdb), sizeof(struct _pdx), (void *)"DOM", &p,
                           phcomp))
                cost = FDCostOf(fdafd, p.rec_num);
        }

    lseek(fdafd, rec_num * (long)sizeof(struct _pda), SEEK_SET);

    if (read(fdafd, (char *)&pda, sizeof(pda)) == sizeof(pda))

int FDFindName(char *find, NETADDR *n, char *path)
{
    struct _johofile jf;
    struct _udx f;
    int success = FALSE;

    cstrupr(find);

    if (!JoHoOpen(path, &jf, TRUE))
        return FALSE;

    if (JoHoLookup(jf.ufd, sizeof(struct _udb), sizeof(struct _udx), find, &f, namecomp))
    {
        n->zone = (f.zone_hi << 8) | f.zone_lo;
        n->net = (f.net_hi << 8) | f.net_lo;
        n->node = (f.node_hi << 8) | f.node_lo;
        n->point = (f.point_hi << 8) | f.point_lo;

        success = TRUE;
    }

    JoHoClose(&jf);

    return success;
}

int NodeFindNext(NFIND *nf)
{
    int got;
    struct _ndi *p, *e;
    struct _v56 *v56;
    word rec;
    struct _node node5;
    struct _newnode node6;


        if (v56->idxcur >= v56->idxcnt)
        {
            lseek(v56->ifd, v56->pos * (long)sizeof(struct _ndi), SEEK_SET);

            got = read(v56->ifd, (char *)v56->idxbuf, NUM_NDI * sizeof(struct _ndi));
            got /= sizeof(struct _ndi);


            v56->pos += (long)got;

            v56->idxcnt = got;
            v56->idxcur = 0;
        }

            {
                v56->zone = p->net;
                v56->net = p->net;
                v56->node = 0;
                v56->point = 0;

                nf->found.flag |= B_zone;
            }
            {
                v56->point = p->net;
                nf->found.flag |= B_point;
            }

            if ((v56->zone == nf->find.zone || nf->find.zone == ZONE_ALL) &&
                (v56->net == nf->find.net || nf->find.net == NET_ALL) &&
                (v56->node == nf->find.node || nf->find.node == NODE_ALL))
            {
                break;
            }
        }


    rec = (int)v56->pos - (e - p);

    lseek(v56->dfd, rec * (long)v56->recsize, SEEK_SET);

    if (read(v56->dfd, (prm.nlver == 5 ? (char *)&node5 : (char *)&node6), v56->recsize) !=
        (signed)v56->recsize)
    {
        return -1;
    }

    }
    else
    {
        nf->found.zone = v56->zone;
        nf->found.net = v56->net;
        nf->found.node = v56->node;
        nf->found.point = v56->point;
        nf->found.cost = node6.Cost;

        strcpy(nf->found.name, node6.SystemName);
        strcpy(nf->found.phone, node6.PhoneNumber);
        strcpy(nf->found.city, node6.MiscInfo);
        nf->found.flag = node6.NodeFlags;
    }

    return 0;
}

void NodeFindClose(NFIND *nf)
{
    if (!nf)
        return;

    if (prm.nlver == NLVER_5 || prm.nlver == NLVER_6)
    {
        if (nf->v56.idxbuf)
            free(nf->v56.idxbuf);

        close(nf->v56.ifd);
        close(nf->v56.dfd);
    }
    else if (prm.nlver == NLVER_7)
    {
    }

    free(nf);
}


        return i;
    }
}
