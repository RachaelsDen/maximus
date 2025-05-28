// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __NODE_H_DEFINED
#define __NODE_H_DEFINED

typedef NETADDR *NETADDRP;

typedef struct
{
    NETADDR find;
    struct _maxnode found;

    struct _v56
    {
        int dfd, ifd;
        long pos;
        word zone, net, node, point;

        word recsize, idxcnt, idxcur;

        struct _ndi *idxbuf;
    } v56;

} NFIND;

NFIND *NodeFindOpen(NETADDR *find);
int NodeFindNext(NFIND *nf);
void NodeFindClose(NFIND *nf);
int V7FindNode(NETADDRP opus_addr, struct _newnode *node, char *net_info);
int V7FindName(char *name, NETADDRP faddr, struct _newnode *node, char *net_info);
int FDFindName(char *find, NETADDR *n, char *path);

