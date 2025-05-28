// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __SQUISH_H_DEFINED
#define __SQUISH_H_DEFINED

#include "apidebug.h"
#include "arc_def.h"
#include "ffind.h"
#include "skiplist.h"
#include "sqstat.h"
#include "sqver.h"

#if defined(NT)
#define SQNAME "Squish/NT"
#elif defined(__FLAT__) && !defined(UNIX)
#define SQNAME "Squish/386"
#elif defined(OS_2)
#define SQNAME "Squish/2"
#elif defined(UNIX)
#define SQNAME "Squish/UNIX"
#else
#define SQNAME "Squish"
#endif

extern byte *version;


#ifdef __MSDOS__
#define fastread(fd, buf, n) farread(fd, (char far *)buf, n)
#define fastwrite(fd, buf, n) farwrite(fd, (char far *)buf, n)
#else
#define fastread(fd, buf, n) read(fd, (char *)buf, n)
#define fastwrite(fd, buf, n) write(fd, (char *)buf, n)
#endif

#define ERL_NONE 0
#define ERL_ERROR 1
#define ERL_SENT_ECHO 2
#define ERL_TOSS_NET 3
#define ERL_TOSS_ECHO 4
#define ERL_MAXMSGS 5


#define MAX_TAGLEN 128

#define AddrMatch(ad1, ad2) MatchNN(ad1, ad2, FALSE)
#define AddrMatchNS(ad1, ad2) MatchNS(ad1, ad2, FALSE)
#define AddrMatchS(ad1, ad2) MatchSS(ad1, ad2, FALSE)

#ifdef OS_2
#define INCL_DOSMODULEMGR
#include <os2.h>


struct _perlist
{
    struct _perlist *next;
    struct _sblist node;
    char *name;
};


};







struct _groute
{

};

};


struct _fwdlist
{

#ifdef OS_2




struct _hpkt
{

#define MAX_HPKT_NAME 18

    struct _sblist from, to;
    byte name[MAX_HPKT_NAME];
    dword attr;
    byte trunc, del;
};


#include "squishp.h"

#define CVT_FLO 1
#define CVT_ARC 2
#define CVT_KILL 3
#define CVT_SFLO 4

#ifdef INITSQUISH
unsigned outbufmax = OUTBUF_LARGE;
unsigned writebufmax = WRITEBUF_LARGE;
unsigned maxmsglen = MAXMSGLEN_MED;
dword nmsg_tossed = 0L, nmsg_scanned = 0L, nmsg_sent = 0L;
#else
extern unsigned maxmsglen;
extern unsigned outbufmax;
extern unsigned writebufmax;
extern dword nmsg_tossed, nmsg_scanned, nmsg_sent;
#endif

extern struct _config config;

#ifndef INITSQUISH
extern
#endif
    struct _flotype
{
    byte *name;
    byte flavour;
} flo_str[]

#ifdef INITSQUISH
    = {{"Hold", 'H'}, {"Crash", 'C'}, {"Express", 'C'}, {"Direct", 'D'}, {"Normal", 'F'}, {NULL, 0}}
#endif
;

#ifndef INITSQUISH
extern dword cr3tab[];
#else

     0x00000000Lu, 0x77073096Lu, 0xee0e612cLu, 0x990951baLu, 0x076dc419Lu, 0x706af48fLu,
     0xe963a535Lu, 0x9e6495a3Lu, 0x0edb8832Lu, 0x79dcb8a4Lu, 0xe0d5e91eLu, 0x97d2d988Lu,
     0x09b64c2bLu, 0x7eb17cbdLu, 0xe7b82d07Lu, 0x90bf1d91Lu, 0x1db71064Lu, 0x6ab020f2Lu,
     0xf3b97148Lu, 0x84be41deLu, 0x1adad47dLu, 0x6ddde4ebLu, 0xf4d4b551uL, 0x83d385c7Lu,
     0x136c9856Lu, 0x646ba8c0Lu, 0xfd62f97aLu, 0x8a65c9ecLu, 0x14015c4fLu, 0x63066cd9Lu,
     0xfa0f3d63Lu, 0x8d080df5Lu, 0x3b6e20c8Lu, 0x4c69105eLu, 0xd56041e4Lu, 0xa2677172Lu,
     0x3c03e4d1Lu, 0x4b04d447Lu, 0xd20d85fdLu, 0xa50ab56bLu, 0x35b5a8faLu, 0x42b2986cLu,
     0xdbbbc9d6Lu, 0xacbcf940Lu, 0x32d86ce3Lu, 0x45df5c75Lu, 0xdcd60dcfLu, 0xabd13d59Lu,
     0x26d930acLu, 0x51de003aLu, 0xc8d75180Lu, 0xbfd06116Lu, 0x21b4f4b5Lu, 0x56b3c423Lu,
     0xcfba9599Lu, 0xb8bda50fLu, 0x2802b89eLu, 0x5f058808Lu, 0xc60cd9b2Lu, 0xb10be924Lu,
     0x2f6f7c87Lu, 0x58684c11Lu, 0xc1611dabLu, 0xb6662d3dLu, 0x76dc4190Lu, 0x01db7106Lu,
     0x98d220bcLu, 0xefd5102aLu, 0x71b18589Lu, 0x06b6b51fLu, 0x9fbfe4a5Lu, 0xe8b8d433Lu,
     0x7807c9a2Lu, 0x0f00f934Lu, 0x9609a88eLu, 0xe10e9818Lu, 0x7f6a0dbbLu, 0x086d3d2dLu,
     0x91646c97Lu, 0xe6635c01Lu, 0x6b6b51f4Lu, 0x1c6c6162Lu, 0x856530d8Lu, 0xf262004eLu,
     0x6c0695edLu, 0x1b01a57bLu, 0x8208f4c1Lu, 0xf50fc457Lu, 0x65b0d9c6Lu, 0x12b7e950Lu,
     0x8bbeb8eaLu, 0xfcb9887cLu, 0x62dd1ddfLu, 0x15da2d49Lu, 0x8cd37cf3Lu, 0xfbd44c65Lu,
     0x4db26158Lu, 0x3ab551ceLu, 0xa3bc0074Lu, 0xd4bb30e2Lu, 0x4adfa541Lu, 0x3dd895d7Lu,
     0xa4d1c46dLu, 0xd3d6f4fbLu, 0x4369e96aLu, 0x346ed9fcLu, 0xad678846Lu, 0xda60b8d0Lu,
     0x44042d73Lu, 0x33031de5Lu, 0xaa0a4c5fLu, 0xdd0d7cc9Lu, 0x5005713cLu, 0x270241aaLu,
     0xbe0b1010Lu, 0xc90c2086Lu, 0x5768b525Lu, 0x206f85b3Lu, 0xb966d409Lu, 0xce61e49fLu,
     0x5edef90eLu, 0x29d9c998Lu, 0xb0d09822Lu, 0xc7d7a8b4Lu, 0x59b33d17Lu, 0x2eb40d81Lu,
     0xb7bd5c3bLu, 0xc0ba6cadLu, 0xedb88320Lu, 0x9abfb3b6Lu, 0x03b6e20cLu, 0x74b1d29aLu,
     0xead54739Lu, 0x9dd277afLu, 0x04db2615Lu, 0x73dc1683Lu, 0xe3630b12Lu, 0x94643b84Lu,
     0x0d6d6a3eLu, 0x7a6a5aa8Lu, 0xe40ecf0bLu, 0x9309ff9dLu, 0x0a00ae27Lu, 0x7d079eb1Lu,
     0xf00f9344Lu, 0x8708a3d2Lu, 0x1e01f268Lu, 0x6906c2feLu, 0xf762575dLu, 0x806567cbLu,
     0x196c3671Lu, 0x6e6b06e7Lu, 0xfed41b76Lu, 0x89d32be0Lu, 0x10da7a5aLu, 0x67dd4accLu,
     0xf9b9df6fLu, 0x8ebeeff9Lu, 0x17b7be43Lu, 0x60b08ed5Lu, 0xd6d6a3e8Lu, 0xa1d1937eLu,
     0x38d8c2c4Lu, 0x4fdff252Lu, 0xd1bb67f1Lu, 0xa6bc5767Lu, 0x3fb506ddLu, 0x48b2364bLu,
     0xd80d2bdaLu, 0xaf0a1b4cLu, 0x36034af6Lu, 0x41047a60Lu, 0xdf60efc3Lu, 0xa867df55Lu,
     0x316e8eefLu, 0x4669be79Lu, 0xcb61b38cLu, 0xbc66831aLu, 0x256fd2a0Lu, 0x5268e236Lu,
     0xcc0c7795Lu, 0xbb0b4703Lu, 0x220216b9Lu, 0x5505262fLu, 0xc5ba3bbeLu, 0xb2bd0b28Lu,
     0x2bb45a92Lu, 0x5cb36a04Lu, 0xc2d7ffa7Lu, 0xb5d0cf31Lu, 0x2cd99e8bLu, 0x5bdeae1dLu,
     0x9b64c2b0Lu, 0xec63f226Lu, 0x756aa39cLu, 0x026d930aLu, 0x9c0906a9Lu, 0xeb0e363fLu,
     0x72076785Lu, 0x05005713Lu, 0x95bf4a82Lu, 0xe2b87a14Lu, 0x7bb12baeLu, 0x0cb61b38Lu,
     0x92d28e9bLu, 0xe5d5be0dLu, 0x7cdcefb7Lu, 0x0bdbdf21Lu, 0x86d3d2d4Lu, 0xf1d4e242Lu,
     0x68ddb3f8Lu, 0x1fda836eLu, 0x81be16cdLu, 0xf6b9265bLu, 0x6fb077e1Lu, 0x18b74777Lu,
     0x88085ae6Lu, 0xff0f6a70Lu, 0x66063bcaLu, 0x11010b5cLu, 0x8f659effLu, 0xf862ae69Lu,
     0x616bffd3Lu, 0x166ccf45Lu, 0xa00ae278Lu, 0xd70dd2eeLu, 0x4e048354Lu, 0x3903b3c2Lu,
     0xa7672661Lu, 0xd06016f7Lu, 0x4969474dLu, 0x3e6e77dbLu, 0xaed16a4aLu, 0xd9d65adcLu,
     0x40df0b66Lu, 0x37d83bf0Lu, 0xa9bcae53Lu, 0xdebb9ec5Lu, 0x47b2cf7fLu, 0x30b5ffe9Lu,
     0xbdbdf21cLu, 0xcabac28aLu, 0x53b39330Lu, 0x24b4a3a6Lu, 0xbad03605Lu, 0xcdd70693Lu,
     0x54de5729Lu, 0x23d967bfLu, 0xb3667a2eLu, 0xc4614ab8Lu, 0x5d681b02Lu, 0x2a6f2b94Lu,
     0xb40bbe37Lu, 0xc30c8ea1Lu, 0x5a05df1bLu, 0x2d02ef8dLu};

