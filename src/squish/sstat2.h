// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __SSTAT2_H_DEFINED
#define __SSTAT2_H_DEFINED

#include <time.h>



struct _tpkt
{
};


struct _tarea
{
    char tag[AH_TAGLEN];
    dword in_msgs;
    dword in_bytes;



struct _tnode
{
    NETADDR node;
    dword out_msgs;
    dword out_bytes;
};


struct _tdupe
{
    char tag[AH_TAGLEN];
    word n_dupes;
};

};

