// SPDX-License-Identifier: GPL-2.0-or-later


#define SFLAG_ECHO 0x0001
#define SFLAG_CONF 0x0002
#define SFLAG_NET 0x0004
#define SFLAG_LOCAL 0x0008
#define SFLAG_ALL (SFLAG_ECHO | SFLAG_CONF | SFLAG_NET | SFLAG_LOCAL)
#define SFLAG_FORCE 0x0010
#define SFLAG_NODEL 0x0020
#define SFLAG_QUIET 0x0040

#define SFLAG_DEFAULT (SFLAG_ALL | 0)

#define MAX_SCANAREA 512

typedef struct
{
    int num_msg;
    int high_msg;
} SBHDR;

typedef struct
{
