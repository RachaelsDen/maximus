// SPDX-License-Identifier: GPL-2.0-or-later


int near TTYGetPrivate(PMAH pmah, XMSG *msg);
int near TTYGetNetmailAddress(PMAH pmah, XMSG *msg);
int near TTYGetToField(PMAH pmah, XMSG *msg);
int near TTYGetSubject(PMAH pmah, XMSG *msg);
int near TTYGetFrom(PMAH pmah, XMSG *msg);
int near TTYGetAttach(PMAH pmah, XMSG *msg);
static void near DisplayEmptyHeader(PMAH pmah);
static void near AskMessageAttrs(XMSG *msg);
