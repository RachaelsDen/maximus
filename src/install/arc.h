// SPDX-License-Identifier: GPL-2.0-or-later


#include "typedefs.h"

ulong compsize, origsize;
int unpackable;

struct _fizhdr
{
#define FIZ_ID 0x1a5a4946L
    long id;

    byte method;
    byte fnlen;

    word crc;

    dword origsize;
    dword compsize;
    union stamp_combo date;
};

#include "wdearc.h"

#define PATHLEN 120
