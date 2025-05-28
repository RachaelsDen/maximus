// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __FDNODE_H_DEFINED
#define __FDNODE_H_DEFINED

#include "prog.h"

#define PVT_NODELIST 0x10000000Lu
#define POINT_NODELIST 0x20000000Lu


struct _gdx
{


struct _inf
{
    char nodes;
    word index;
    char rsvd[2];
};



struct _pdx
{

struct _pdb
{
    struct _inf inf;

    union
    {
        struct _pdx pdx[32];
        struct _hdr hdr;
        char flat[928];
    } d;
};




    byte zone_hi;
    byte zone_lo;

    byte net_hi;
    byte net_lo;

    byte node_hi;
    byte node_lo;

    byte point_hi;
    byte point_lo;


struct _udb
{
    struct _inf inf;

    union
    {
        struct _udx udx[32];
        struct _hdr hdr;
        char flat[1056];
    } d;
};





#define TYPE_ZC 0x01
#define TYPE_RC 0x02
#define TYPE_NC 0x03
#define TYPE_HC 0x04
#define TYPE_PVT 0x05
#define TYPE_HOLD 0x06
#define TYPE_DOWN 0x07
#define TYPE_POINT 0x09


struct _fdb
{
    struct _inf inf;

    union
    {
        struct _fdx fdx[32];
        struct _hdr hdr;
        char flat[736];
    } d;
};

int JoHoOpen(char *path, struct _johofile *jf, int userlist);
int JoHoLookup(int fd, size_t block_size, size_t rec_size, void *find, void *found,
               int (*compare)(void *, void *));
int JoHoFetch(void *f, struct _johofile *jf, struct _johonode *jn);
int JoHoClose(struct _johofile *jf);

