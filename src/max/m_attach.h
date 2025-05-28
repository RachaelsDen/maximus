// SPDX-License-Identifier: GPL-2.0-or-later


static int near Make_Attach_Directory(void);
static int near Receive_Attach(void);
static struct _arcinfo *near attach_archiver();
static int near Compress_Attach_Files(PMAH pmah, char *szAttachName, dword *pulFlags);
static int near Send_Attach(int fDelok);
static int near Decompress_Attach(char *szName);
static void near Update_Attach_Db(PMAH pmah, HAREA marea, XMSG *msg, UMSGID uid, char *szFileName,
                                  dword ulFlags);
