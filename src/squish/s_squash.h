// SPDX-License-Identifier: GPL-2.0-or-later


#define cvlen (sizeof(cv) / sizeof(cv[0]))

char *arcm_exts[] = {".su", ".mo", ".tu", ".we", ".th", ".fr", ".sa", NULL};


static char *routedelim = " \t\n\r";

static void near Check_Outbound_Areas(void);

static struct _defn
{
    char *name;
    char *xlat;
    struct _defn *next;
} * defns;
