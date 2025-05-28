// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __F_IDX_H_DEFINED
#define __F_IDX_H_DEFINED

#ifndef __FB_H_DEFINED
#include "fb.h"
#endif

struct _idxf
{
    FIDX fidx;
    char *pat;
    long lo, hi, last, next_found_ofs;
    int found, pat_len;
    int ifd;
};

typedef struct _idxf IDXF;

IDXF *IndexOpen(char *pat);
int IndexNext(IDXF *ix);
void IndexClose(IDXF *ix);
word FidxIsOkay(FIDX *fidx, FDAT *fdat, char *name, char *path, word check_cur, word check_priv,
                PFAH pfahIn);

