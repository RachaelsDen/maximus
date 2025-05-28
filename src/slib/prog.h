// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __PROG_H_DEFINED
#define __PROG_H_DEFINED

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef SJD
#define SJD
#endif

#include "compiler.h"
#include "stamp.h"
#include "typedefs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NULLL (void far *)NULL
#else
#define NULLL NULL
#endif
#endif

#ifdef __FARDATA__
#include "alc.h"

#if !defined(_lint)
#define malloc(n) farmalloc(n)
#define calloc(n, u) farcalloc(n, u)
#define free(p) farfree(p)
#define realloc(p, n) farrealloc(p, n)
#endif

#if defined(__TURBOC__) && !defined(__TOPAZ__)
#define coreleft() farcoreleft()
#endif
#else
unsigned cdecl coreleft(void);
unsigned long cdecl farcoreleft(void);
#endif

#if defined(__WATCOMC__) || defined(__MSC__) || defined(_lint)

#define farmalloc(n) _fmalloc(n)
#define farfree(p) _ffree(p)
#define farrealloc(p, n) _frealloc(p, n)
    void far *farcalloc(int n, int m);

#ifdef _MSC_VER
#if _MSC_VER >= 600
#define farcalloc(a, b) _fcalloc(a, b)

#define da_year year
#define da_day day
#define da_mon month

#define ti_min minute
#define ti_hour hour
#define ti_hund hsecond
#define ti_sec second

#define getdate _dos_getdate
#define gettime _dos_gettime

#define NO_STRFTIME


#elif defined(__TURBOC__)

#define dosdate_t date
#define dostime_t time

#if (__TURBOC__ >= 0x0295) || defined(__TOPAZ__)
#define ENOTSAM EXDEV

    int _stdc fnsplit(const char *path, char *drive, char *dir, char *name, char *ext);
    int _stdc getcurdir(int drive, char *directory);

    int fossil_wherex(void);
    int fossil_wherey(void);
    void fossil_getxy(char *row, char *col);

#define textattr(attr)
#define getdisk() get_disk()
#define setdisk(drive) set_disk(drive)

#define getvect(int) _dos_getvect(int)
#define setvect(int, func) _dos_setvect(int, func)

#ifndef inportb
#define inportb(port) inp(port)
#endif

#define inport(port) inpw(port)

#ifndef outportb
#define outportb(port, byte) outp(port, byte)
#endif

#define outport(port, byte) outpw(port, byte)

#if !defined(MK_FP) && !defined(_lint)
#define MK_FP(seg, off) (void far *)((unsigned long)(seg) << 16L | (off))
#endif
#endif

#if defined(__MSC__) || defined(UNIX)
    int _fast lock(int fh, long offset, long len);
    int _fast unlock(int fh, long offset, long len);
#endif

#ifdef __MSC__
#undef toupper
#if __WATCOMC__ == 900
    FILE *fdopen(int __handle, const char *__mode);
#endif
#endif

#ifndef cpp_begin
#ifdef __cplusplus
#define cpp_begin()                                                                                \
    extern "C"                                                                                     \
    {
#define cpp_end() }
#else
#define cpp_begin()
#define cpp_end()
#endif
#endif

#if !defined(UNIX) || !defined(HAVE_TIMER_T)
#if !defined(__timer_t_defined) && !defined(__FreeBSD__)
    typedef long timer_t;
#endif
#endif

#define REGISTER

#ifndef TRUE
#define FALSE 0
#define TRUE 1
#endif

#ifdef PATHLEN
#undef PATHLEN
#endif

#define LITTLE_ENDIAN
#endif

#if defined(BIG_ENDIAN) && defined(LITTLE_ENDIAN)
#error BIG_ENDIAN and LITTLE_ENDIAN cannot both be defined at the same time!
#endif

#if !defined(BIG_ENDIAN) && !defined(LITTLE_ENDIAN)
#error Either BIG_ENDIAN or LITTLE_ENDIAN must be defined!
#endif

#ifdef __MSDOS__
#define WILDCARD_ALL "*.*"
#else
#define WILDCARD_ALL "*"
#endif


#if !defined(UNIX)
#define NULL_DEVICE "nul"
#define NULL_DEVICE "/dev/null"
#endif

#endif

#define ZONE_ALL 56685u
#define NET_ALL 56685u
#define NODE_ALL 56685u
#define POINT_ALL 56685u

#define THIS_YEAR "2003"

#define Hello(prog, desc, version, year)                                                           \
    (void)printf("\n" prog "  " desc ", Version %s.\nCopyright " year                              \
                 " by Lanius Corporation.  All rights reserved.\n\n",                              \
                 version)
#define shopen(path, access) sopen(path, access, SH_DENYNONE, S_IREAD | S_IWRITE)
#define GTdate(s1, s2) (GEdate(s1, s2) && (s1)->ldate != (s2)->ldate)
#define carrier_flag (prm.carrier_mask)
#define BitOff(a, x) ((void)((a)[(x) / CHAR_BITS] &= ~(1 << ((x) % CHAR_BITS))))
#define BitOn(a, x) ((void)((a)[(x) / CHAR_BITS] |= (1 << ((x) % CHAR_BITS))))
#define IsBit(a, x) ((a)[(x) / CHAR_BITS] & (1 << ((x) % CHAR_BITS)))


#if !defined(UNIX)
#define fancy_fn(s) fancy_str(s)
#define cfancy_fn(s) cfancy_str(s)
#define upper_fn(s) strupr(s)
#define lower_fn(s) strlwr(s)
#else
#define fancy_fn(s) (s)
#define cfancy_fn(s) (s)
#define upper_fn(s) (s)
#define lower_fn(s) (s)
#endif

#ifndef updcrc
#define updcrc(cp, crc) (crctab[((crc >> 8) & 255) ^ cp] ^ (crc << 8))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif


    struct __priv
    {
        char *name;
        int priv;
    };

    extern char _vstdc months[][10];
    extern char _vstdc weekday[][10];

    extern char _vstdc months_ab[][4];
    extern char _vstdc weekday_ab[][4];

    extern struct __priv _vstdc _privs[];

#include "progprot.h"

#ifndef NO_STRFTIME

#include <sys/types.h>
#include <time.h>

    time_t _stdc mktime(struct tm *tm_ptr);
#endif

