// SPDX-License-Identifier: GPL-2.0-or-later


static void near RedrawAll(PMAH pmah, XMSG *msg, int showhelp);
int near GetAttributes(PMAH pmah, XMSG *msg);
int near GetFrom(PMAH pmah, XMSG *msg);
int near GetFromAddr(PMAH pmah, XMSG *msg);
int near GetToField(PMAH pmah, XMSG *msg);
int near GetToAddr(PMAH pmah, XMSG *msg);
int near GetSubject(PMAH pmah, XMSG *msg);
int near GetItemString(char *str, int max);
static void near DisplayShowDest(NETADDR *d);
