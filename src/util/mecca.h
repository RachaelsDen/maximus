// SPDX-License-Identifier: GPL-2.0-or-later



#define DLE 16
#define PATHDELIM ".\\/"

struct _symbol
{
    char name[MAX_SYMBOLLEN];
    long location;
    long offset[MAX_OFFSETS];
    int offsetnum;
};


#ifdef MECCA_INIT

struct _table verbs[] = {


#include "mecca_vb.h"

    {"ZZZZZZZZZZ", 0, -1, "", NULL}};

int verb_table_size = (sizeof(verbs) / sizeof(verbs[0]));

int num_gt, num_lt, num_eq, num_ne, num_ge, num_le, num_above, num_below, num_equal, num_unequal,
    num_notequal, num_ae, num_be;

