// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: msgtrack.c,v 1.1.1.1 2002/10/01 17:56:06 sdudley Exp $";
#pragma on(unreferenced)


#define INCL_NOPM
#include "msgtrack.h"
#include "msgapi.h"
#include "sqfeat.h"
#include <fcntl.h>
#include <io.h>
#include <os2.h>
#include <share.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

typedef NETADDR *NETADDRP;


byte *_fast Address(NETADDR *a)
{
    static char temp[30];
    char point[10];

    sprintf(point, ".%hu", (unsigned)a->point);

    sprintf(temp, "%hu:%hu/%hu%s", (unsigned)a->zone, (unsigned)a->net, (unsigned)a->node,
            a->point ? point : "");

    return temp;
}

    strcpy(pfi->szConfigName, p);

word FEATENTRY _export FeatureConfig(struct _feat_config far *pfc)
{
    NW(pfc);

    if (stricmp(pfc->ppszArgs[1], "Nodelist") == 0)
        strcpy(szNodexName, pfc->ppszArgs[2]);
    else if (stricmp(pfc->ppszArgs[1], "Kill") == 0)
        fKill = TRUE;
    else
    {
        char temp[120];

        sprintf(temp, "!Unknown keyword: \"MsgTrack %s\"\n", pfc->ppszArgs[1]);
        (*pfnLogMsg)(temp);
        return 1;
    }

    return 0;
}


static long near btree(char *filename, void *desired,
                       int(near *compare)(void *key, void *desired, int len))
{
    int j, k, l;
    struct _ndx *nodeidx = NULL;
    struct _ndx *noderef = NULL;
    struct _IndxRef *ip = NULL;
    struct _LeafRef *lp = NULL;
    char aline[160];
    char *tp;
    char *np;

    long record, foundrec = -1L;
    int count;

    int stream;

    if ((stream = sopen(filename, O_RDONLY | O_BINARY | O_NOINHERIT, SH_DENYNO,
                        S_IREAD | S_IWRITE)) == -1)
    {

    if (get7node(stream, 0L, noderef) != noderef)
    {
        free(noderef);
        free(nodeidx);
        close(stream);
        return -1L;
    }


    if (get7node(stream, (unsigned long)(record * noderef->ndx.CtlBlk.CtlBlkSize), nodeidx) !=
        nodeidx)
    {
        free(noderef);
        free(nodeidx);
        close(stream);
        return -1L;
    }


    while (nodeidx->ndx.INodeBlk.IndxFirst != -1)
    {
        if ((count = nodeidx->ndx.INodeBlk.IndxCnt) == 0)
        {
            free(noderef);
            free(nodeidx);
            close(stream);
            return (-1L);
        }


            k = (*compare)((void *)aline, desired, l);

            if (k > 0)
                break;

            if (k == 0)
            {


                free(noderef);
                free(nodeidx);
                close(stream);

                return (nodeidx->ndx.INodeBlk.IndxRef[j].IndxData);
            }
        }

        if (j == 0)
            record = nodeidx->ndx.INodeBlk.IndxFirst;
        else
            record = (nodeidx->ndx.INodeBlk.IndxRef[--j]).IndxPtr;

        if (get7node(stream, (unsigned long)(record * noderef->ndx.CtlBlk.CtlBlkSize), nodeidx) !=
            nodeidx)
        {
            free(noderef);
            free(nodeidx);
            close(stream);
            return (-1L);
        }
    }




            k = (*compare)((void *)aline, desired, l);

            if (k > 0)
                break;

            if (k == 0)
            {
                foundrec = (nodeidx->ndx.LNodeBlk.LeafRef[j]).KeyVal;
                break;
            }
        }
    }

    free(noderef);
    free(nodeidx);
    close(stream);

    return (foundrec);
}


static unsigned near FeatListed(struct _feat_netmsg far *pfn)
{
    NETADDR n = pfn->pMsg->dest;
    long rec;

    rec = btree(szNodexName, (void *)&n, addr_compare);

    if (rec != -1)
        return TRUE;

    if (n.point)
    {
        n.point = 0;
        rec = btree(szNodexName, (void *)&n, addr_compare);
    }

    return (rec != -1);
}


    memset(&msg, 0, sizeof msg);
    msg.orig = pfn->us;
    msg.dest = pfn->pMsg->orig;

    printf("msg orig=%s\n", Address(&msg.orig));
    printf("msg dest=%s\n", Address(&msg.dest));


    MsgWriteMsg(hmsg, FALSE, &msg, bounce, strlen(bounce),
                strlen(bounce) + strlen(pfn->pszMsgTxt) + strlen(trailer) + 1, 0, NULL);

    if (bounce)
        free(bounce);


    MsgWriteMsg(hmsg, TRUE, NULL, pfn->pszMsgTxt, strlen(pfn->pszMsgTxt), 0, 0, NULL);

    MsgWriteMsg(hmsg, TRUE, NULL, trailer, strlen(trailer) + 1, 0, 0, NULL);


    pfn->ulAction = FACT_SKIP | FACT_HIDE;

    if (fKill)
        pfn->ulAction |= FACT_KILL;
    else
    {
        pfn->ulAction |= FACT_RWMSG;
        pfn->pMsg->attr |= MSGSENT | MSGORPHAN;
    }
}


    if (!configured)
    {
        if (access(szNodexName, 0) == -1)
        {
            if (!done_err)
            {
                printf("Error!  Nodelist index `%s' does not exist!\n", szNodexName);
                done_err = TRUE;
            }

            return 0;
        }

        configured = TRUE;
    }



    BounceMessage(pfn);

    return 0;
}

word FEATENTRY _export FeatureTossMsg(struct _feat_toss far *pft)
{
    NW(pft);
    return 0;
}

word FEATENTRY _export FeatureScanMsg(struct _feat_scan far *pfs)
{
    NW(pfs);
    return 0;
}

word FEATENTRY _export FeatureTerm(struct _feat_term far *pft)
{
    NW(pft);
    return 0;
}

#ifdef __FLAT__
void FEATENTRY _export Feature32Bit(void)
#else
void FEATENTRY _export Feature16Bit(void)
#endif
{
}
