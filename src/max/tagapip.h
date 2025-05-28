// SPDX-License-Identifier: GPL-2.0-or-later


static int _TagGetMtagMem(struct _mtagidx *pmti, struct _mtagmem *pmtm);
static void near _TagNewPmtm(struct _mtagmem *pmtm);
static int near _TagPackMessages(FILE *in_i, FILE *in_d, FILE *out_i, FILE *out_d, int recnum);
static int near _TagRepackMtag(int recnum);
static int near _TagAddToFree(struct _mtagidx *pmti, int recnum);
static int near _TagReuseIdx(struct _mtagidx *pmti, int recnum);
static int near _TagReadIdx(struct _mtagidx *pmti);
