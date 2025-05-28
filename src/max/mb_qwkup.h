// SPDX-License-Identifier: GPL-2.0-or-later


static char *near fix_basic_crap(char *str);
static int near Toss_QWK_Packet(char *name);
static int near QWK_Get_Rep_Header(int qfd, char *block);
static void near QWK_To_Xmsg(struct _qmhdr *qh, XMSG *msg, word msgn);
static int near Toss_QWK_Message(struct _qmhdr *qh, XMSG *msg, int qfd, char *block);
static int near all_caps(char *s);
static int near Receive_REP(char *name);
static int near Decompress_REP(char *rep_name);
