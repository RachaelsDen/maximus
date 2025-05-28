// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __MAX_H_DEFINED
#define __MAX_H_DEFINED


#endif

#ifdef OS_2
#define MCP

#ifndef ORACLE
#define MCP_VIDEO
#endif

#ifndef __FLAT__

#ifdef NOVARS
#ifndef NOINIT
#define INITIALIZE_STATIC
#endif
#endif

#ifdef MAX_INITIALIZE
#define extrn
#define IS(x) = x
#define LEN(x) x
#else
#define extrn extern
#define IS(x)
#define LEN(x)
#endif

#include <time.h>

#ifndef __COMPILER_H_DEFINED
#include "compiler.h"
#endif

#ifndef __TYPEDEFS_H_DEFINED
#include "typedefs.h"
#endif

#include "utime.h"

#ifndef __PROG_H_DEFINED
#include "prog.h"
#endif

#ifndef __SQAPI_H_DEFINED
#include "msgapi.h"
#endif

#ifndef __EVENTS_H_DEFINED
#include "events.h"
#endif

#ifndef __DV_H_DEFINED
#include "dv.h"
#endif

#ifndef __WIN_H_DEFINED
#include "win.h"
#endif

#ifdef MAX_INCL_COMMS
#include "modem.h"
#endif

#ifdef PATHLEN
#undef PATHLEN
#endif

#ifdef BLINK
#undef BLINK
#endif

#ifdef DLE
#undef DLE
#endif

#ifdef lputs
#undef lputs
#endif


#ifdef __TURBOC__
#define isupsp(c) (_ctype[(c) + 1] & (_IS_UPP | _IS_SP))
#else
#define isupsp(c) (isupper(c) || isspace(c))
#endif

#define MNU(m, o) (((m).menuheap) + (m).o)
#define Mdm_keyp() (Mdm_kpeek() != -1)
#define Clear_KBuffer() *linebuf = '\0'
#define Save_Directory(path) Save_Dir(&orig_disk, orig_path, path)
#define Restore_Directories() Restore_Dir(&orig_disk, orig_path)
#define Save_Directory2(path) Save_Dir(&orig_disk2, orig_path2, path)
#define Restore_Directories2() Restore_Dir(&orig_disk2, orig_path2)
#define Save_Directory3(path) Save_Dir(&orig_disk3, orig_path3, path)
#define Restore_Directories3() Restore_Dir(&orig_disk3, orig_path3)
#define Yes_or_No(expr) ((expr) ? yes : no)
#define Sysop_Yes_or_No(expr) ((expr) ? sysop_yes : sysop_no)
#define loc_kbhit() (loc_peek() != -1)
#define Input(d, t, c, m, p) Inputf(d, t, c, m, "%s", p)
#define Input_Char(t, x) Input_Charf(t, "%s", x)
#define InputGetsWNH InputGets
#define InputGetseNH InputGetse
#define InputGetsNH InputGetsL
#define mdm_getsp(d, m) Inputf(d, INPUT_MSGENTER | INPUT_NLB_LINE, 0, m, NULL)
#define mdm_getspnc(d, m) Inputf(d, INPUT_MSGENTER | INPUT_NLB_LINE | INPUT_NOCLEOL, 0, m, NULL)
#define KeyGetRNP(p) Input_Charf(CINPUT_DISPLAY | CINPUT_PROMPT | CINPUT_NOXLT | CINPUT_DUMP, p)
#define GetYnAnswer(p, t) GetListAnswer(CYn, NULL, useyforyes, t, percent_s, p)
#define GetyNAnswer(p, t) GetListAnswer(yCN, NULL, useyforyes, t, percent_s, p)
#define GetYnnsAnswer(p, t) GetListAnswer(Yne, NULL, useyforyesns, t, percent_s, p)
#define GetYnhAnswer(h, p, t) GetListAnswer(CYnq, h, useyforyes, t, percent_s, p)
#define GetyNhAnswer(h, p, t) GetListAnswer(yCNq, h, useyforyes, t, percent_s, p)
#define UserHasKey(k) (usr.xkeys & (1L << (dword)(k)))
#define UserKeyOff(k) (usr.xkeys &= ~(1L << (dword)(k)))
#define UserKeyOn(k) (usr.xkeys |= (1L << (dword)(k)))
#define MsgAreaHasLock(a, l) ((a).msglock & (1L << (dword)(l)))
#define FileAreaHasLock(a, l) ((a).filelock & (1L << (dword)(l)))
#define GEPriv(p1, p2) ((word)(p1) >= (word)(p2))
#define LEPriv(p1, p2) ((word)(p1) <= (word)(p2))
#define Goto(xx, yy) Printf(goto_str, (char)(xx), (char)(yy))
#define lputc(c) (*local_putc)(c)
#define lputs(s) (*local_puts)(s)
#define isalnumpunct(ch) (!is_wd(ch))
#define UIDnum(n) ((prm.flags2 & FLAG2_UMSGID) ? MsgMsgnToUid(sq, (n)) : (n))
#define hasRIP() (!local && (usr.bits & BITS_RIP))






#define VA_EXTONLY                                                                                 \


#define COL_POPUP_BOR (CYELLOW | _BLUE)



#define STATUS_NORMAL 0x00
#define STATUS_REMOVE 0x01
#define STATUS_FORCE 0x02

#define IREADLEN 60

#define MAX_MSGDISPLAY                                                                             \
#define MAX_MSGLINES                                                                               \
#define SEEK_SIZE                                                                                  \
#define MAX_NEST                                                                                   \
#define MAX_BUSYLOOP                                                                               \
#define CHANGE_SCREENLEN                                                                           \
#define RETIMEOUT                                                                                  \
#define MAX_EXECARGS                                                                               \
#define PREREGISTERED                                                                              \



#define OUTSIDE_CHAIN 0x02
#define OUTSIDE_RUN 0x03
#define OUTSIDE_DOS 0x04
#define OUTSIDE_CONCUR 0x05

#define SKIP_FILE 1
#define SKIP_LINE 2

#define DO_EITHER 0x00
#define DO_THEN 0x01
#define DO_ELSE 0x02

#define VAR_RETCODE 0x00

#define ACTION_EQ 0x00
#define ACTION_NE 0x01
#define ACTION_GT 0x02
#define ACTION_LT 0x03
#define ACTION_GE 0x04
#define ACTION_LE 0x05


#define INPUT_ALREADYCH                                                                            \
#define INPUT_NOCTRLC                                                                              \
#define INPUT_MSGENTER                                                                             \


#define CINPUT_DISPLAY                                                                             \
#define CINPUT_RTNHELP                                                                             \
#define CINPUT_ACCEPTABLE                                                                          \
#define CINPUT_PROMPT                                                                              \
#define CINPUT_LASTMENU                                                                            \
#define CINPUT_NOCTRLC                                                                             \
#define CINPUT_FULLPROMPT                                                                          \



#define AREATYPE_ECHO 0x04
#define AREATYPE_CONF 0x08

#define AREATYPE_ALL (AREATYPE_LOCAL | AREATYPE_MATRIX | AREATYPE_ECHO | AREATYPE_CONF)



#define BLINK "\x16\x02"
#define CLS "\x0c"
#define CLEOL "\x16\x07"

#define BLKONWHIT "\x16\x01\x70"
#define REDONWHIT "\x16\x01\x74"
#define WHITONWHIT "\x16\x01\x77"
#define MAGONBLUE "\x16\x01\x1d"
#define WHITONBLUE "\x16\x01\x1f"
#define YELONBLUE "\x16\x01\x1e"
#define LREDONBLUE "\x16\x01\x1c"
#define LMAGONBLUE "\x16\x01\x1d"
#define LCYANONBLUE "\x16\x01\x1b"
#define DKGRAYONWHIT "\x16\x01\x78"
#define CHATTR "\x16\x01%c"




#define HARD_CR                                                                                    \
#define SOFT_CR                                                                                    \

#define MODE_SCROLL                                                                                \

#ifdef __MSDOS__
#define MAX_LINES 250
#else
#define MAX_LINES 1000
#endif
#else

#define Cursor_LeftM(n)                                                                            \
    {                                                                                              \
        Goto(current_line, current_col - (n));                                                     \
        cursor_y -= min(cursor_y - 1, n);                                                          \
    }

#define DISGRACE 0x0000
#define PRIVIL 0x0004
#define ASSTSYSOP 0x0008
#define SYSOP 0x000A

#ifdef NUMBER_PRIVS
#define HIDDEN 0x7fff
#else
#define HIDDEN 0x000b
#endif
#endif


#ifndef _NDI_DEFINED
#define _NDI_DEFINED

struct _ndi
{
} __attribute__((packed, aligned(2)));
#endif

#include "colour.h"


#ifndef _SYS_DEFINED
#define _SYS_DEFINED

struct _sys
{
#include "tagapi.h"

struct _opt
{
#ifdef __FLAT__
#endif

} __attribute__((packed, aligned(2)));

#define DEFAULT_OPT_WIDTH 20

struct _menu
{


typedef struct _amenu
{
    struct _menu m;
    struct _opt *opt;
    char *menuheap;
} AMENU, *PAMENU;

#define MFLAG_MF_RIP 0x0400u




    dword num_callers;
    dword quote_pos;
    dword msgs_written;
    time_t online_date;
    dword total_dl;
    dword total_ul;
    sword today_callers;
    union stamp_combo date;
    byte lastuser[36];
} __attribute__((packed, aligned(1)));


struct _proto
{


typedef struct _llpush
{
    union
    {
        MAH mah;
        FAH fah;
    } ah;

    BARINFO biOldPriv;

struct _cgs
{
    int ptr;
    char num_tid;
    char rsvd;

    int tids[255];
};


struct _cdat
{
    word tid;
    word type;
    word len;

#ifdef MCP
    word dest_tid;
    dword rsvd1;
#else
    dword rsvd1;
    word rsvd2;
#endif
} __attribute__((packed, aligned(2)));


struct _css
{
    word avail;
    byte status[80];
} __attribute__((packed, aligned(2)));


struct _restart
{







    struct _css css;

    char log_name[80];

} __attribute__((packed, aligned(2)));


#ifdef MAX_INCL_VER

#ifdef MAX_INCL_VARS
char *receive_file(char *fpath, char *fname, char protocol);


#ifndef _NODE_DEFINED
#define _NODE_DEFINED

} __attribute__((packed, aligned(2)));
#endif

#ifndef _NEWNODE_DEFINED
#define _NEWNODE_DEFINED

#define B_hub 0x0001
#define B_host 0x0002
#define B_region 0x0004
#define B_zone 0x0008
#define B_CM 0x0010
#define B_res1 0x0020
#define B_res2 0x0040
#define B_res3 0x0080
#define B_res4 0x0100
#define B_res5 0x0200
#define B_res6 0x0400
#define B_res7 0x0800
#define B_point 0x1000
#define B_res9 0x2000
#define B_resa 0x4000
#define B_resb 0x8000



#define pFido 0x00
#define pRover 0x01
#define pSEAdog 0x02
#define pSlick 0x04
#define pOpus 0x05
#define pDutchie 0x06
#define pTabby 0x08
#define pWolf68k 0x0A
#define pQMM 0x0B
#define pFrontDoor 0x0C
#define pMailMan 0x11
#define pOOPS 0x12
#define pGSPoint 0x13
#define pBGMail 0x14
#define pBinkScan 0x19
#define pDBridge 0x1A
#define pBinkleyTerm 0x1B
#define pYankee 0x1C
#define pDaisy 0x1E
#define pPolarBear 0x1F
#define pTheBox 0x20
#define pSTARgate2 0x21
#define pTMail 0x22
#define pTCOMMail 0x23
#define pBananna 0x24
#define pRBBSMail 0x25
#define pAppleNetmail 0x26
#define pChameleon 0x27
#define pMajikBoard 0x28
#define pQMail 0x29
#define pPointClick 0x2A
#define pA3Bundler 0x2B
#define pFourDog 0x2C
#define pMSGPACK 0x2D
#define pAMAX 0x2E
#define pDomComSys 0x2F
#define pLesRobot 0x30
#define pRose 0x31
#define pParagon 0x32
#define pBinkST 0x33
#define pStarNet 0x34
#define pZzyZx 0x35
#define pQEcho 0x36
#define pBOOM 0x37
#define pPBBS 0x38
#define pTrapDoor 0x39
#define pWelmat 0x3A
#define pNetGate 0x3B
#define pOdie 0x3C
#define pQuickGimme 0x3D
#define pdbLink 0x3E
#define pTosScan 0x3F
#define pBeagle 0x40
#define pIgor 0x41
#define pTIMS 0x42
#define pIsis 0x43
#define pAirMail 0x44
#define pXRS 0x45
#define pJuliet 0x46
#define pJabberwocky 0x47
#define pXST 0x48
#define pMailStorm 0x49
#define pBIXMail 0x4A
#define pIMAIL 0x4B
#define pFTNGate 0x4C
#define pRealMail 0x4D
#define pLora 0x4E
#define pTDCS 0x4F
#define pInterMail 0x50
#define pRFD 0x51
#define pYuppie 0x52
#define pEMMA 0x53
#define pQBoxMail 0x54
#define pNumber4 0x55
#define pNumber5 0x56
#define pGSBBS 0x57
#define pMerlin 0x58
#define pTPCS 0x59
#define pRaid 0x5A
#define pOutpost 0x5B
#define pNizze 0x5C
#define pArmadillo 0x5D
#define prfmail 0x5E
#define pMsgtoss 0x5F
#define pInfoTex 0x60
#define pGEcho 0x61
#define pCDEhost 0x62
#define pPktize 0x63
#define pMax 0x7a

#ifndef _PKTHDR_DEFINED
#define _PKTHDR_DEFINED



} __attribute__((packed, aligned(2)));

#endif

#define cREV2P 0x0001
#define cREV2 0x0000

    word dest_zone;

    byte orig_domain[8];
    byte dest_domain[8];


#ifdef MAX_INCL_PROTO
#include "proto.h"
#endif

#if defined(ORACLE) && defined(__TURBOC__)


#pragma warn - par
#pragma warn - aus
#pragma warn - use

#endif

