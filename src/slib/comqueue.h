// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __COMQUEUE_H_DEFINED
#define __COMQUEUE_H_DEFINED

typedef struct
{
} COMQUEUE;

typedef COMQUEUE *PCOMQUEUE;


#define QueueEmpty(q)                                                                              \
    ((q)->pbHead == (q)->pbTail || ((q)->pbHead == (q)->pbEnd && (q)->pbTail == (q)->pbBuf))


#define QueueWrapPointersRemove(q) ((q)->pbHead == (q)->pbEnd ? ((q)->pbHead = (q)->pbBuf) : 0)


#define QueueGetSize(q)                                                                            \
    (QueueWrapped(q) ? ((q)->pbEnd - (q)->pbHead) + ((q)->pbTail - (q)->pbBuf)                     \
                     : (q)->pbTail - (q)->pbHead)


#define QueueWrapPointersInsert(q) ((q)->pbTail == (q)->pbEnd ? ((q)->pbTail = (q)->pbBuf) : 0)


#define QueueGetFree(q)                                                                            \
    (QueueWrapped(q) ? (q)->pbHead - (q)->pbTail - 1                                               \
                     : ((q)->pbEnd - (q)->pbTail) + ((q)->pbHead - (q)->pbBuf))


#define QueueInsertContig(q, size)                                                                 \
    do                                                                                             \
    {                                                                                              \
        (q)->pbTail += size;                                                                       \
        QueueWrapPointersInsert(q);                                                                \
    } while (0)


#define QueueRemoveContig(q, size)                                                                 \
    do                                                                                             \
    {                                                                                              \
        (q)->pbHead += size;                                                                       \
        QueueWrapPointersRemove(q);                                                                \
    } while (0)

