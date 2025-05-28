// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: v7.c,v 1.2 2003/06/04 23:46:22 wesgarland Exp $";
#pragma on(unreferenced)


#include "v7.h"
#include "mm.h"
#include "prog.h"
#include "v7p.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define get_nodelist_name(a) ;

static char unwrk[] = " EANROSTILCHBDMUGPKYWFVJXZQ-'0123456789";
static char nodelist_base[] = "NODEX";
static size_t namelen;

int V7FindNode(NETADDRP opus_addr, struct _newnode *node, char *net_info)
{
    long record;
    char index_filename[PATHLEN];

    node->NetNumber = node->NodeNumber = 0;


#ifndef UNIX
#endif

    record = btree(index_filename, (void *)opus_addr, addr_compare);

    if (record == -1)
        return 0;
    else
        return get_ver7_info((dword)record, opus_addr, node, net_info);
}

int V7FindName(char *name, NETADDRP faddr, struct _newnode *node, char *net_info)
{
    char last_name_first[80];
    char index_filename[PATHLEN];
    char midname[80];
    char *c, *p, *m;
    long record;

    faddr->zone = faddr->net = faddr->node = faddr->point = (word)-1;


    while ((*c = *p++) != 0)
    {
        if (*c == ' ')
            m = c;

        c++;
    }

    if (m)
    {
    }
    else

#else

    if ((nodeidx = malloc(sizeof(struct _ndx))) == NULL ||
        (noderef = malloc(sizeof(struct _ndx))) == NULL)
    {
        if (nodeidx)
            free(nodeidx);

        close(stream);
        return -1L;
    }


    record = noderef->ndx.CtlBlk.CtlRoot;


    while (nodeidx->ndx.INodeBlk.IndxFirst != -1)
    {
        if ((count = nodeidx->ndx.INodeBlk.IndxCnt) == 0)
        {
            j = 0;
        }
        else

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

static int near get_ver7_info(unsigned long pos, NETADDRP faddr, struct _newnode *node,
                              char *net_info)
{
    struct _vers7 vers7;
    char my_phone[40];
    char my_pwd[9];
    char aline[160];
    char aline2[160];
    char *fst;
#else
