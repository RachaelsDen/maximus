// SPDX-License-Identifier: GPL-2.0-or-later


#define SQBUF_SIZE 16384

struct _alist
{
    char *name;
    struct _alist *next;
};

static char sqbuf[SQBUF_SIZE];
static long totold, totnew;

void _fast NoMem(void);
