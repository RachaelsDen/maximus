// SPDX-License-Identifier: GPL-2.0-or-later


#include "node.h"

int near addr_compare(void *key, void *desired, int len);
int near name_compare(void *key, void *desired, int len);
static long near btree(char *filename, void *desired,
                       int(near *compare)(void *key, void *desired, int len));
static int near get_ver7_info(unsigned long pos, NETADDRP faddr, struct _newnode *node,
                              char *net_info);
static struct _ndx *near get7node(int stream, dword pos, struct _ndx *ndx);
static void near unpk(char *instr, char *outp, int count);
