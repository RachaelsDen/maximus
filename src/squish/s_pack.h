// SPDX-License-Identifier: GPL-2.0-or-later


#define REMAP_BUF_SIZE 4096

static char *msgbuf;
static long n_packed;
static long n_notsent;
static FILE *trklog = NULL;

static void near PackIt(struct _cfgarea *ar);
static void EXPENTRY AddToMsgBuf(byte OS2FAR *str);
static int near GateRouteMessage(XMSG *msg, dword mn, NETADDR *olddest);
static unsigned near Pack_Netmail_Msg(HAREA sq, dword *mn, struct _cfgarea *ar);
static int near Send_Message(HMSG mh, XMSG *msg, dword bytes, dword mn, struct _cfgarea *ar);
static int near OkToForward(XMSG *msg);
static int near Remap_Message(XMSG *msg, dword mn);
static void near Point_To_Fakenet_Dest(XMSG *msg);
static void near Point_To_Fakenet_Orig(XMSG *msg);
static void near Process_AttReqUpd(XMSG *msg, char *filename, word manual);
static void near Process_OneAttReqUpd(XMSG *msg, char *filename, int tflag, char *orig_fspec,
                                      char *pwd);
static void near TrackMessage(XMSG *msg, byte *ctrl);
static void near AddViaLine(byte *msgbuf, byte *ctrl);
static void near ExpandAndSend(XMSG *msg, int tflag, char *filename, char *pwd, char *szName);
