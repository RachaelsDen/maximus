// SPDX-License-Identifier: GPL-2.0-or-later


struct _args
{
    byte echotoss[PATHLEN];
    byte cfgname[PATHLEN];
    byte areasbbs[PATHLEN];
    byte sched[PATHLEN];
    byte logfile[PATHLEN];

    word do_pack;
    word action;
    word leave_packets;

    byte **toscan;
    NETADDR n;
};

#if 0
static void near test_harness(char *name);
#endif

static void near ParseArgs(struct _args *ags, byte *argv[]);
static void near CleanupConfig(void);
static void near SquishSquashCycle(void);
static void near InitializeConfig(void);
