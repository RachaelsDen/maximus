// SPDX-License-Identifier: GPL-2.0-or-later


#include "skiplist.h"

#define MAXLEVEL 16
#define PARTITION 4

static SLNODE *near _fast _SkipCreateNode(word levels, void *data);
static void near _fast _SkipBlank(SLIST *sl);
static SLNODE *near _fast _SkipFindNode(SLIST *sl, void *data, SLNODE *ptrs[]);
static void near _fast _SkipFreeNode(SLNODE *sn);
static word near _fast _SkipRandomLevel(SLIST *sl);
