// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __NEWAREA_H_DEFINED
#define __NEWAREA_H_DEFINED

#include "option.h"

#ifndef __netaddr_defined
#define __netaddr_defined
typedef struct _netaddr NETADDR;
struct _netaddr
{
    word zone;
    word net;
    word node;
    word point;
};
#endif



#define MAREA_ID 0x1a49023fL
#define FAREA_ID 0x1a01953aL







#define FA_CDROM (FA_SLOW | FA_STAGED | FA_NONEW)
#define FA_FREEALL (FA_FREETIME | FA_FREESIZE)

typedef struct _msgarea
{


typedef struct _barinfo
{

typedef struct _mahandle
{
    OVERRIDE *pov;
    char *heap;
    MAREA ma;
    int heap_size;

    BARINFO bi;
} MAH, *PMAH;

typedef struct _fahandle
{
    OVERRIDE *pov;
    char *heap;
    FAREA fa;
    int heap_size;

    BARINFO bi;
} FAH, *PFAH;


typedef struct _mfidx
{
