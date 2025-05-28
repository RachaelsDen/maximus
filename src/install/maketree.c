// SPDX-License-Identifier: GPL-2.0-or-later


#include "ar.h"

static int n, heapsize;
static short heap[NC + 1];
static ushort *freq, *sortptr, len_cnt[17];
static uchar *len;

{
    int j, k;

    k = heap[i];
    while ((j = 2 * i) <= heapsize)
    {
        if (j < heapsize && freq[heap[j]] > freq[heap[j + 1]])
            j++;
        if (freq[k] <= freq[heap[j]])
            break;
        heap[i] = heap[j];
        i = j;
    }
    heap[i] = k;
}

static void make_code(int n, uchar len[], ushort code[])
{
    int i;
    ushort start[18];

    start[1] = 0;
    for (i = 1; i <= 16; i++)
        start[i + 1] = (start[i] + len_cnt[i]) << 1;
    for (i = 0; i < n; i++)
        code[i] = start[len[i]]++;
}

int make_tree(int nparm, ushort freqparm[], uchar lenparm[], ushort codeparm[])
    sortptr = codeparm;
    do
        if (i < n)
            *sortptr++ = i;
        heap[1] = heap[heapsize--];
        downheap(1);
        freq[k] = freq[i] + freq[j];
        heap[1] = k;
}
