// SPDX-License-Identifier: GPL-2.0-or-later



#include <ctype.h>
#include <dos.h>
#include <limits.h>
#include <stdio.h>

#if defined(UNIX)
#if defined(SYSV)
#include <sys/statvfs.h>
typedef struct statvfs st_statfs;
#define statfs(a, b) statvfs(a, b)
#elif defined(__FreeBSD__)
#include <sys/mount.h>
#include <sys/param.h>
typedef struct statfs st_statfs;
#else
#include <sys/vfs.h>
typedef struct statfs st_statfs;
#endif
#endif

#include "prog.h"

static long CalcFreeSpace(long lSectorsPerCluster, long lBytesPerSector, long lFreeClusters);

#if defined(OS_2)

#define INCL_NOPM
#include <os2.h>

long _stdc zfree(char *drive)
{
    int driveno;
    FSALLOCATE dt;

    if (!drive || !*drive || drive[1] != ':')
    else
        driveno = (unsigned char)(toupper(*drive) - 'A' + 1);

#ifdef __386__
    r.x.eax = 0x3600;



    return sb.f_bavail * sb.f_bsize;
#if defined(SYSV)
#undef statfs
#endif
}
#else
#error Unknown OS
#endif

static long CalcFreeSpace(long lSectorsPerCluster, long lBytesPerSector, long lFreeClusters)
{
    long rc;
    long lBytesPerCluster;

    lBytesPerCluster = lSectorsPerCluster * lBytesPerSector;
    rc = lFreeClusters * lBytesPerCluster;

