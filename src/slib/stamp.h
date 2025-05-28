// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef __STAMP_H_DEFINED
#define __STAMP_H_DEFINED

#include "compiler_align.h"
#include "compiler_details.h"
#include "typedefs.h"

#define STAMP_BITFIELD uint32
#define HALF_STAMP_BITFIELD uint16

/** DOS-style datestamp */
struct _timestamp
{
#if defined(PROJECT_LITTLE_ENDIAN)
    STAMP_BITFIELD da : 5;
    STAMP_BITFIELD mo : 4;
    STAMP_BITFIELD yr : 7;
    STAMP_BITFIELD ss : 5;
    STAMP_BITFIELD mm : 6;
    STAMP_BITFIELD hh : 5;
#elif defined(PROJECT_BIG_ENDIAN)
    STAMP_BITFIELD ss : 5;
    STAMP_BITFIELD mm : 6;
    STAMP_BITFIELD hh : 5;
    STAMP_BITFIELD da : 5;
    STAMP_BITFIELD mo : 4;
    STAMP_BITFIELD yr : 7;
#else
#error Neither PROJECT_BIG_ENDIAN nor PROJECT_LITTLE_ENDIAN are defined!
#endif
} PACKED;

union _stampu
{
    struct _timestamp date;
    struct _timestamp time;
};

struct _dos_st
{
#if defined(PROJECT_LITTLE_ENDIAN)
    HALF_STAMP_BITFIELD date PACKED;
    HALF_STAMP_BITFIELD time PACKED;
#elif defined(PROJECT_BIG_ENDIAN)
    HALF_STAMP_BITFIELD time PACKED;
    HALF_STAMP_BITFIELD date PACKED;
#else
#error Neither PROJECT_BIG_ENDIAN nor PROJECT_LITTLE_ENDIAN are defined!
#endif
} PACKED;

/* Union so we can access stamp as "int" or by individual components */

union stamp_combo
{
    STAMP_BITFIELD ldate;
    union _stampu msg_st;
    struct _dos_st dos_st;
} PACKED;

typedef union stamp_combo SCOMBO;

/* strange union-union-struct to preserve original
 * semantic as much as possible; it was union-struct-struct.
 *
 * so, hopefully, most code that looks like this:
 * stamp_combo.msg_st.date.mo will still work with
 * a simple variable declaration change..
 *
 * Original syntax was no good because on some machines
 * (e.g. sparc) you can't declare structs on less than
 * a 32-bit boundary (gcc 2.95.2) no matter how hard you
 * try (packed, aligned)
 *
 * 		old					new
 * stamp_combo	struct _stamp				union _stampu
 * msg_st	{ struct _date; struct _time }		struct _timestamp
 * dos_st	{ int16; int16; }			{ int16; int16; }
 */
#endif /* __STAMP_H_DEFINED */