// SPDX-License-Identifier: GPL-2.0-or-later


typedef struct _rnum
{
    struct _rnum *next;
    word num;
} RNUM;

typedef struct _ren
{

} REN;

#define REN_DELTA 0x01
#define REN_DELETE 0x02
