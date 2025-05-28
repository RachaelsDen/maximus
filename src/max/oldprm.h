// SPDX-License-Identifier: GPL-2.0-or-later



#if !defined(__PRM_H_DEFINED) || defined(FORCE)

#if defined(FORCE)
#undef OFS
typedef char OFS[PATHLEN];
#else
#define OFS word
#endif

#ifndef __PRM_H_DEFINED

#define PRM(s) (offsets + (prm.s))


#define FLAG_lbaud96                                                                               \
#define FLAG_alias                                                                                 \
#define FLAG_ask_name                                                                              \


#define CHARSET_SWEDISH 0x01
#define CHARSET_CHINESE 0x02


#define NLVER_5 5
#define NLVER_6 6
#define NLVER_7 7
#define NLVER_FD 32

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


    byte rsvd999;















    OFS timeformat;
    OFS dateformat;





    OFS high_msgarea;


