// SPDX-License-Identifier: GPL-2.0-or-later


#error this file no longer used.


#include "mm.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

static int near NodeExist(NETADDR *d)
{
    struct _ndi ndi[NUM_NDI];

    int idxfile;
    long offset;
    word current_zone;
    word x, y;

    char temp[PATHLEN];

    current_zone = prm.address[0].zone;

    if (!*PRM(net_info))
        return -1;

    sprintf(temp, idxnode, PRM(net_info));

    if ((idxfile = shopen(temp, O_RDONLY | O_BINARY)) == -1)
    {

            if ((sword)ndi[x].node < 0)
                ndi[x].node = 0;

            if ((current_zone == d->zone || d->zone == 0 || prm.nlver == 5) &&
                ndi[x].net == d->net && ndi[x].node == d->node)
            {
                close(idxfile);
                return (int)offset + x;
            }
        }
    }

    close(idxfile);
    return -1;
}

int ReadNode(NETADDR *d, void *nodeptr)
{
    char temp[PATHLEN];

    int nlfile;

    word offset;
    word x;

    unsigned long n6size = 0L;

    if ((offset = NodeExist(d)) == (unsigned int)-1)
        return FALSE;
    else
    {
        if (prm.nlver == 6)
        {
            sprintf(temp, idxnode, PRM(net_info));

            x = (word)(fsize(temp) / (long)sizeof(struct _ndi));

            sprintf(temp, datnode, PRM(net_info));

            n6size = fsize(temp);
            n6size = n6size / (dword)x;
        }
        else
            sprintf(temp, sysnode, PRM(net_info));

        if ((nlfile = shopen(temp, O_RDONLY | O_BINARY)) == -1)
        {
