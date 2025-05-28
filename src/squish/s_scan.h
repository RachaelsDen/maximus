// SPDX-License-Identifier: GPL-2.0-or-later


static void near AddAreaTag(char *txt, struct _cfgarea *ar);
static int _stdc sbl_comp_nz(const void *s1, const void *s2);
static void near Insert_Sb_Node(struct _sblist *look, struct _sblist *sb, unsigned *num_sb);
static int near Need_To_Scan(struct _cfgarea *ar, struct _sblist *scanto, struct _sblist *sb,
                             unsigned num_sb, XMSG *msg);
static void near Add_Outbuf(struct _sblist *to, struct _pktprefix *pp, byte *lump,
                            unsigned long lumplen, char *text, unsigned long textlen, int flavour,
                            struct _cfgarea *ar);
static void near Fix_SeenBys(struct _sblist *sb, unsigned num_sb, char *mbuf, unsigned smask,
                             struct _cfgarea *ar);
static void near Add_Us_To_Path(struct _cfgarea *ar, char *msgbuf);
static void near Add_Tear_Line(char *msgbuf, struct _cfgarea *ar, XMSG *msg);

#define SCAN_NOPOINT 0x01
#define SCAN_TINY 0x02
