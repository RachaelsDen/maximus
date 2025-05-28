// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include "uni.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#if defined(__SMALL__) || defined(__MEDIUM__)

#else

#ifdef OS_2
#define INCL_DOSMEMMGR
#include "pos2.h"
#endif

long _fast h_read(int fd, char huge *buf, long size)
{
    int ret;
    long rc = 0;

    while (size > 0)
    {
        unsigned long ulMax = 65536L - ((long)buf & 0xFFFF);
        ulMax = min(ulMax, size);
        ulMax = min(ulMax, 32767L);

        if (!size)
            return 0;

        if (!ulMax)
            return 0;

        ret = read(fd, (char *)buf, (unsigned)ulMax);

        if (ret < 0)
            return (long)ret;


        buf += (long)ret;
        rc += (long)ret;
        size -= ulMax;

        if (rc == 0)
            break;
    }

    return rc;
}
#endif
