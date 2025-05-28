// SPDX-License-Identifier: GPL-2.0-or-later



#if !defined(__PRM_H_DEFINED) || defined(FORCE)

#include "compiler.h"

#if defined(FORCE)
#undef OFS
typedef char OFS[PATHLEN];
#else
#define OFS word
#endif

#ifndef __netaddr_defined
#define __netaddr_defined
typedef struct _netaddr NETADDR;
struct _netaddr
{
    word zone;
    word net;
    word node;
    word point;
};
#endif

#ifndef __PRM_H_DEFINED
#ifndef MAX_DRIVES
#endif


#define PRM(s) (offsets + (prm.s))

#define MAXCLASS                                                                                   \
#define FLAG_break_clr                                                                             \
#define FLAG_lbaud96                                                                               \
#define FLAG_alias                                                                                 \
#define FLAG_ask_name                                                                              \


#define LOG_TERSE 0x02
#define LOG_VERBOSE 0x04
#define LOG_TRACE 0x06

#define LOG_terse LOG_TERSE
#define LOG_verbose LOG_VERBOSE
#define LOG_trace LOG_TRACE

#define MULTITASKER_AUTO -1
#define MULTITASKER_NONE 0
#define MULTITASKER_DOUBLEDOS 1
#define MULTITASKER_DESQVIEW 2
#define MULTITASKER_TOPVIEW 3
#define MULTITASKER_MLINK 4
#define MULTITASKER_MSWINDOWS 5
#define MULTITASKER_OS2 6
#define MULTITASKER_PCMOS 7
#define MULTITASKER_NT 8
#define MULTITASKER_UNIX 9

#define MULTITASKER_auto MULTITASKER_AUTO
#define MULTITASKER_none MULTITASKER_NONE
#define MULTITASKER_doubledos MULTITASKER_DOUBLEDOS
#define MULTITASKER_desqview MULTITASKER_DESQVIEW
#define MULTITASKER_topview MULTITASKER_TOPVIEW
#define MULTITASKER_mlink MULTITASKER_MLINK
#define MULTITASKER_mswindows MULTITASKER_MSWINDOWS
#define MULTITASKER_os2 MULTITASKER_OS2
#define MULTITASKER_pcmos MULTITASKER_PCMOS
#define MULTITASKER_nt MULTITASKER_NT
#define MULTITASKER_unix MULTITASKER_UNIX


struct cl_rec
{
    sword priv;
};


#ifdef FORCE
struct mfpointers
#else
struct m_pointers
#endif
{










    NETADDR address[ALIAS_CNT];




    word flags;
    word flags2;
    word flags3;
    word flags4;

    byte rsvd_lang;

    word max_glh_ptrs;
    word max_glh_len;

    word max_syh_ptrs;
    word max_syh_len;



#define PRM_HEAP_START sysop













    OFS timeformat;
    OFS dateformat;





    OFS high_msgarea;







