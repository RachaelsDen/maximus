// SPDX-License-Identifier: GPL-2.0-or-later



#include "skiplist.h"
#include "prog.h"
#include "skiplisp.h"
#include <stdlib.h>


    sl->maxlevel = (maxlevel && maxlevel <= MAXLEVEL) ? maxlevel : MAXLEVEL;
    sl->partition = partition ? partition : PARTITION;
    sl->comp = comp;


    _SkipBlank(sl);
    return sl;
}


void *_fast SkipAddNode(SLIST *sl, void *data, word *exists)
{
    SLNODE *this;
    SLNODE *ptrs[MAXLEVEL];
    word level, n;

    if (exists)
        *exists = FALSE;


    if (this)
        this = this->next[0];


    if ((level = _SkipRandomLevel(sl)) > sl->highlevel)
    {

        ptrs[level] = sl->first;
    }


    for (n = 0; n <= level; n++)
    {
        this->next[n] = ptrs[n]->next[n];
        ptrs[n]->next[n] = this;
    }

    sl->nodes++;

    return this->data;
}


void *_fast SkipSearchList(SLIST *sl, void *data)
{
    SLNODE *this;


    if (this == NULL || (*sl->comp)(data, this->data) != 0)
        return NULL;

    return this->data;
}


    this = _SkipFindNode(sl, data, ptrs);


    if (this == NULL || (*sl->comp)(data, this->data) != 0)
        return SKIP_ENOENT;


    while (sl->highlevel && sl->first->next[sl->highlevel] == NULL)
        sl->highlevel--;

    sl->nodes--;

    return SKIP_OK;
}


    for (sn = sl->first->next[0]; sn; sn = next)
    {
        next = sn->next[0];
        _SkipFreeNode(sn);
    }

    free(sl);

    return SKIP_OK;
}


void *_fast SkipFirst(SLIST *sl)
{
    sl->last = sl->first->next[0];
    return sl->last ? sl->last->data : NULL;
}


    for (this = sl->first, lvl = sl->highlevel + 1; lvl;)
    {
        lvl--;

        while (this->next[lvl] && (*sl->comp)(this->next[lvl]->data, data) < 0)
            this = this->next[lvl];


        if (ptrs)
            ptrs[lvl] = this;
    }

    return this;
}


static SLNODE *near _fast _SkipCreateNode(word levels, void *data)
{
    SLNODE *sn;


    if ((sn->next = malloc(sizeof(SLNODE *) * levels)) == NULL)
    {
        free(sn);
        sn = NULL;
    }

    return sn;
}


    for (n = 0; n < sl->maxlevel; n++)
        sl->first->next[n] = NULL;

    sl->highlevel = 0;
}

static void near _fast _SkipFreeNode(SLNODE *sn)
{

    free(sn);
}

static word near _fast _SkipRandomLevel(SLIST *sl)
{
    word level = 0;

    while ((word)(rand() % sl->maxlevel) < sl->partition && level < sl->maxlevel)
    {
        level++;
    }

    return level;
}

#ifdef NEVER
void SkipCountLevel(SLIST *sl)
{
    struct _cfgarea *ar;
    SLNODE *sn;
    int i, cnt;
    static int asdf = 0;

    for (i = 0; i < sl->highlevel; i++)
    {
        for (cnt = 0, sn = sl->first->next[i]; sn; sn = sn->next[i])
            cnt++;

        printf("Level %d: %d\n", i, cnt);
    }
}
#endif
