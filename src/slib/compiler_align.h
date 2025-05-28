// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef _COMPILER_ALIGN_H
#define _COMPILER_ALIGN_H

#if defined(__GNUC__)
#if !defined(__sparc)
#define PACKED __attribute__((packed))
#define ALIGNED __attribute__((aligned))
#define PACKED_ALIGNED __attribute__((packed, aligned))
#else
#ifdef SOLARIS
#include <sys/isa_defs.h>
#endif
#define PACKED
#ifdef _MAX_ALIGNMENT
#define PACKED_ALIGNED __attribute__((aligned(_MAX_ALIGNMENT * 8)))
#define ALIGNED __attribute__((aligned(_MAX_ALIGNMENT * 8)))
#else
#define PACKED_ALIGNED __attribute__((aligned))
#define ALIGNED __attribute__((aligned))
#endif
#endif
#else
#ifdef UNIX
#warning Unrecognized compiler; structure packing may be incorrect!
#endif
#define ALIGNED
#define PACKED_ALIGNED
#define PACKED
#endif

#if defined(__sparc) || defined(sparc) || defined(__mips) || defined(__PPC__) ||                   \
    defined(__powerpc__)
#define SLOPPY_ALIGNMENT_OKAY 0
#endif

#if defined(__alpha__)
#if defined(LINUX)
#endif

#if defined(_GNUC_)
#define returnCast(a) (typeof(a))
#define alignof(type)	offsetof(struct { char c; type member; }, member                           \
    }
#else
#define returnCast(a)
#endif

#if !SLOPPY_ALIGNMENT_OKAY
void *_aligndup(const void *unaligned, size_t alignment, size_t size);
void _unaligndup_free(void *unaligned, void *aligned, size_t size);
void *_alignStatic(const void *unaligned, size_t size);
void _unalign(void *unaligned, void *aligned, size_t size);

#define aligndup(a)		returnCast(a) _aligndup(a, alignof(*(a)), sizeof(*(a))))
#define unaligndup_free(a, b) _unalignfree(a, b, sizeof(*(a)))
#define alignStatic(a) returnCast(a) _alignStatic(a, sizeof(*(a)))
#define unalign(a, b) _unalign(a, b, sizeof(*(a)))
#else
#define aligndup(a) (a + 0)
#define unaligndup_free(a, b)                                                                      \
    do                                                                                             \
    {                                                                                              \
        ;                                                                                          \
    } while (0)
#define alignStatic(a) (a + 0)
#define unalign(a, b)                                                                              \
    do                                                                                             \
    {                                                                                              \
        ;                                                                                          \
    } while (0)
#endif

#if !defined(_MAX_ALIGNMENT)
#if defined _GNUC_
static union
{
    char c;
    short sh;
    int i;
    double d;
    float f;
    struct
    {
        char a[1];
    } st;
    void *v;
} alignmentTest;
#define _MAX_ALIGNMENT alignof(alignmentTest)
#else
