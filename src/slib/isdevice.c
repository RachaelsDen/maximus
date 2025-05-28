// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <dos.h>
#include <io.h>
#include <string.h>

#if defined(__MSDOS__)


#define DEV_MASK 0x0047

unsigned _fast is_device(int fd)
{
    union REGS r;


#ifdef __386__
    r.x.ebx = fd;

    int386(0x21, &r, &r);

    if (r.x.cflag)
        return 0;
    else
        return !!(r.x.edx & DEV_MASK);
#else
    r.x.bx = fd;

    int86(0x21, &r, &r);

    if (r.x.cflag)
        return !!(r.x.dx & DEV_MASK);
    else
        return 0;
#endif
}
#elif defined(OS_2)
#define INCL_DOS
#include <pos2.h>

unsigned _fast is_device(int fd)
{
    OS2UINT usType;
    OS2UINT usDevAttr;

#ifdef __FLAT__
    DosQueryHType((HFILE)fd, &usType, &usDevAttr);
#else
    DosQHandType((HFILE)fd, &usType, &usDevAttr);
#endif

    return ((usType & 0xff) != HANDTYPE_FILE);
}
#elif defined(NT)

#include "pwin.h"

unsigned _fast is_device(int fd)
{
    DWORD rc;

    rc = GetFileType((HANDLE)_os_handle(fd));

    return (rc != FILE_TYPE_DISK);
}
#elif defined(UNIX)

#include "uni.h"
#include <sys/stat.h>

unsigned _fast is_device(int fd)
{
    struct stat st;

    if (fstat(fd, &st) != 0)
        return FALSE;

    return !!(st.st_mode & (S_IFIFO | S_IFCHR | S_IFBLK | S_IFSOCK));
}

#else
#error Unknown OS
#endif

#include "unistr.h"


        if (eqstri(filename, *pp) || (eqstrn(filename, *pp, len) && (*pp)[len] == '.'))
        {
            return TRUE;
        }
    }

    return FALSE;
}
