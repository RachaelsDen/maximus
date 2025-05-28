// SPDX-License-Identifier: GPL-2.0-or-later


struct _partial
{
};

};

static char area_tag[MAX_TAGLEN];


extern byte *msgbuf;
extern byte *begin_sb, *end_sb;

static char last_area[MAX_TAGLEN];

static char *msgb;
static unsigned long msglen;

static HAREA sq;
static struct _cfgarea *last_sq;

static struct _talist
{
    HAREA sq;
    struct _cfgarea *ar;
} * talist;

static int talist_init;

static void near TossBadMsgs(struct _cfgarea *ar);
static struct _cfgarea *GetBadmsgsArea(struct _inmsg *in);
static void near Copy_To_Header(struct _inmsg *in);
static void near Toss_Pkt(char *pktname, word tflag);
static int near TossReadMsgFromPkt(struct _inmsg *in);
static int near TossOneMsg(struct _inmsg *in, int badmsg, word tflag);
static int near Process_Transient_Mail(struct _inmsg *in);
static struct _cfgarea *near Get_Area_Tag(struct _inmsg *in, char *txt);
static void near Handle_Dupe(struct _cfgarea *ar);
static int near Open_Area(struct _cfgarea *ar);
static void near Close_Area(void);
static void near Toss_Packet_Sequence(char *path, word tflag);
static int near Decompress_Archive(char *arcname, char *get);
static int near PacketSecure(struct _inmsg *in);
static void near Write_Echotoss(char *echotoss);
static void near Get_TFS(struct _inmsg *in);
static struct _cfgarea *GetDupesArea(struct _inmsg *in);
static void near NewArea(char *name);
static void near ReadMaxMsgs(char *tosslog);
static void near WriteMaxMsgs(void);
static void near ReportSpeed(time_t secs);
static void near TossArchives(struct _tosspath *tp);
