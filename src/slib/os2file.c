// SPDX-License-Identifier: GPL-2.0-or-later



#if defined(OS_2)

#include "prog.h"
#include <errno.h>

#define INCL_NOPM
#define INCL_DOS
#include <os2.h>

int far pascal farread(int handle, char far *buf, unsigned int len)
{
#ifdef __FLAT__
    ULONG bytesRead;
#else
    USHORT bytesRead;
#endif

    if (DosRead(handle, buf, len, &bytesRead))
    {
        errno = EBADF;
        return -1;
    }
    else
        return (int)bytesRead;
}

int far pascal farwrite(int handle, char far *buf, unsigned int len)
{
#ifdef __FLAT__
    ULONG bytesWrite;
#else
    USHORT bytesWrite;
#endif

    if (DosWrite(handle, buf, len, &bytesWrite))
    {
        errno = EBADF;
        return -1;
    }
    else
        return (int)bytesWrite;
}

#elif defined(NT) || defined(UNIX)
#include "prog.h"
#include <fcntl.h>
#include <io.h>

int far pascal farread(int handle, char far *buf, unsigned int len)
{
    return read(handle, buf, len);
}

int far pascal farwrite(int handle, char far *buf, unsigned int len)
{
    return write(handle, buf, len);
}
#else
#error Unknown OS!
#endif
