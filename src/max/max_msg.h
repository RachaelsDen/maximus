// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __MAX_MSG_H_DEFINED
#define __MAX_MSG_H_DEFINED




#define MAX_NETNODE 50

#define MSGKEY_PRIVATE 0
#define MSGKEY_CRASH 1
#define MSGKEY_READ 2
#define MSGKEY_SENT 3
#define MSGKEY_FILE 4
#define MSGKEY_FWD 5
#define MSGKEY_ORPHAN 6
#define MSGKEY_KILL 7
#define MSGKEY_LOCAL 8
#define MSGKEY_HOLD 9
#define MSGKEY_XX2 10
#define MSGKEY_FRQ 11
#define MSGKEY_RRQ 12
#define MSGKEY_CPT 13
#define MSGKEY_ARQ 14
#define MSGKEY_URQ 15
#define MSGKEY_LATTACH                                                                             \
enum
{
    TAG_TOGGLE = 0,
    TAG_ADD = 1,
    TAG_DEL = 2
};

