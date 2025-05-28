// SPDX-License-Identifier: GPL-2.0-or-later


#if defined(UNIX)
#include <sys/stat.h>
#endif

#include "prog.h"
#include <dos.h>


#ifdef __386__

        s.ds = FP_SEG(path);
        r.x.dx = FP_OFF(path);

        ret = int86x(0x21, &r, &r, &s);
    }
#endif

    return (r.x.cflag ? -1 : ret);
}

#elif defined(OS_2)

#include <os2.h>


int _fast cshopen(const char *path, int access)
{
    HFILE hf;
#ifdef __FLAT__
    ULONG rc, usAction;
#else
    USHORT rc, usAction;
#endif

    NW(access);
    rc = DosOpen((PSZ)path, &hf, &usAction, 0L, FILE_NORMAL, FILE_CREATE,
                 OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE | OPEN_FLAGS_NOINHERIT, 0L);
    return (rc ? -1 : hf);
}
#elif defined(NT) || defined(UNIX)
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <sys/stat.h>
#include <sys/types.h>

int _fast cshopen(const char *path, int access)
{
    return sopen(path, access | O_EXCL, SH_DENYNO, S_IREAD | S_IWRITE);
}
#else
#error unknown operating system. (posix: try "open(path, O_EXCL|access)")
#endif
