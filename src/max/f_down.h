// SPDX-License-Identifier: GPL-2.0-or-later


#include "fb.h"

static int near CanDownload(PFAH pfah, char *name, word *flag, char *path);
static int near InFileList(PFAH pfah, char *name, word *flag, char *pt);
static int near FileExist(char *path, char *name);
static int near IndexSearch(char *name, int do_tag, sword protocol);
static int near FindIndexFile(struct _fidx *fidx, int do_tag, sword protocol);
static int near FileLimitsOkay(unsigned long ulSize, int flags, sword protocol, long *realbytes,
                               long *prtime);
static int near GotFile(char *fname, long size, int do_tag, sword protocol, int flags);
