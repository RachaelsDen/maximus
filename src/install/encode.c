// SPDX-License-Identifier: GPL-2.0-or-later


#include "ar.h"
#include <stdlib.h>
#endif
    }
    for (i = DICSIZ; i < DICSIZ * 2; i++)
        parent[i] = NIL;
    avail = 1;
    for (i = 1; i < DICSIZ - 1; i++)
        next[i] = i + 1;
    next[DICSIZ - 1] = NIL;
    for (i = DICSIZ * 2; i <= MAX_HASH_VAL; i++)
        next[i] = NIL;
}

#define HASH(p, c) ((p) + ((c) << (DICBIT - 9)) + DICSIZ * 2)

static node child(node q, uchar c)
    while (parent[r] != q)
        r = next[r];
    return r;
}

static void makechild(node q, uchar c, node r)
}

static void delete_node(void)
{
#if PERCOLATE
    node q, r, s, t, u;
#else
    node r, s, t, u;
#endif

    if (parent[pos] == NIL)
        return;
    r = prev[pos];
    s = next[pos];
    next[r] = s;
    prev[s] = r;
    r = parent[pos];
    parent[pos] = NIL;
    if (r >= DICSIZ || --childcount[r] > 1)
        return;
#if PERCOLATE
    t = position[r] & ~PERC_FLAG;
#else
    t = position[r];
#endif
    if (t >= pos)
        t -= DICSIZ;
#if PERCOLATE
    s = t;
    q = parent[r];
    while ((u = position[q]) & PERC_FLAG)
    {
        u &= ~PERC_FLAG;
        if (u >= pos)
            u -= DICSIZ;
        if (u > s)
            s = u;
        position[q] = (s | DICSIZ);
        q = parent[q];
    }
    if (q < DICSIZ)
    {
        if (u >= pos)
            u -= DICSIZ;
        if (u > s)
            s = u;
        position[q] = s | DICSIZ | PERC_FLAG;
    }
#endif
    s = child(r, text[t + level[r]]);
    t = prev[s];
    u = next[s];
    next[t] = u;
    prev[u] = t;
    t = prev[r];
    next[t] = s;
    prev[s] = t;
    t = next[r];
    prev[t] = s;
    next[s] = t;
    parent[s] = parent[r];
    parent[r] = NIL;
    next[r] = avail;
    avail = r;
}

static void get_next_match(void)
{
    int n;

    remainder--;
    if (++pos == DICSIZ * 2)
    {
        memmove(&text[0], &text[DICSIZ], DICSIZ + MAXMATCH);
        n = fread_crc(&text[DICSIZ + MAXMATCH], DICSIZ, infile);

#if 0
            char *p, *e;

            for (p=text+DICSIZ, e=p+remainder; p < e; p++)
              *p=~*p;
          }
#endif

    printf(".");
    fflush(stdout);
    matchlen = 0;
    pos = DICSIZ;
    insert_node();
    if (matchlen > remainder)
        matchlen = remainder;
    while (remainder > 0 && !unpackable)
    {
        lastmatchlen = matchlen;
        lastmatchpos = matchpos;
        get_next_match();
        if (matchlen > remainder)
            matchlen = remainder;
        if (matchlen > lastmatchlen || lastmatchlen < THRESHOLD)
            output(text[pos - 1], 0);
        else
        {
            output(lastmatchlen + (UCHAR_MAX + 1 - THRESHOLD),
                   (pos - lastmatchpos - 2) & (DICSIZ - 1));
            while (--lastmatchlen > 0)
                get_next_match();
            if (matchlen > remainder)
                matchlen = remainder;
        }
    }
    huf_encode_end();
}
