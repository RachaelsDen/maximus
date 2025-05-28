// SPDX-License-Identifier: GPL-2.0-or-later


static void near CleanupAfterSave(int chg, XMSG *msg, long save_to, PMAH pmah, char *msgarea,
                                  char *kludge, HAREA ha);
static void near Check_For_Origin(word *found_tear, char *temp);
static int near WriteErr(int opened);
static int near ProcessCC(UMSGID uid, char *line, XMSG *msg, int first);
static void near Handle_Carbon_Copies(long msgn, FILE *upfile, XMSG *msg);
