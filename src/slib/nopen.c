// SPDX-License-Identifier: GPL-2.0-or-later



#include "nopen.h"
#include "uni.h"
#include <dos.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>


char _stdc _nopen_cheat = 0;
extern int __NFiles;


static void near _wcclearflags(int fd)
{
    if (fd == -1 || fd >= __NFiles)
        return;

    __SetIOMode(fd, 0);
}

static void near _wcsetiomode(int fd, int mode)
{
    if (fd == -1 || fd >= __NFiles)
        return;



int _stdc nsopen(const char *name, int mode, int shacc, ...)
{
    union REGS save, r;
    int permiss = S_IREAD | S_IWRITE;
    int fd;

#ifndef __FLAT__
    struct SREGS sr;
#endif

    if (mode & O_CREAT)
    {
        va_list val;

        va_start(val, shacc);
        permiss = va_arg(val, int);
        va_end(val);
    }


#ifdef __FLAT__
    r.x.ecx = (permiss & S_IWRITE) == S_IWRITE ? 0x00 : 0x01;
    r.x.edx = (unsigned)name;
#else
    r.x.cx = (permiss & S_IWRITE) == S_IWRITE ? 0x00 : 0x01;
    sr.ds = FP_SEG(((char far *)name));
    r.x.dx = FP_OFF(((char far *)name));
#endif

    save = r;


    if (mode & O_EXCL)
        r.x.cflag = 1;
    else
    {

        if (r.x.cflag == 0 && (mode & O_TRUNC))
        {
#ifdef __FLAT__
            int tfd = r.x.eax;
#else
            int tfd = r.x.ax;
#endif

            nlseek(tfd, 0L, SEEK_SET);
            nwrite(tfd, "", 0);
        }
    }


#ifdef __FLAT__
        int386(0x21, &r, &r);
#else
        int86x(0x21, &r, &r, &sr);
#endif


        if (r.x.cflag == 0 && !_nopen_cheat)
        {

            if (shacc != SH_COMPAT)
            {
#ifdef __FLAT__
                nclose(r.x.eax);
#else
                nclose(r.x.ax);
#endif

            }
        }
    }

    if (r.x.cflag)
    {
#ifdef __FLAT__
        errno = r.x.eax;
#else
        errno = r.x.ax;
#endif
        return -1;
    }

#ifdef __FLAT__
    fd = r.x.eax;
#else
    fd = r.x.ax;
#endif

    if (fd != -1 && (mode & O_APPEND))
        nlseek(fd, 0L, SEEK_END);

    int386(0x21, &r, &r);

    if (r.x.cflag)
    {
        errno = r.x.eax;
        return -1;
    }

    return ((long)(r.w.dx << 16) | (long)r.w.ax);
#else
    r.x.bx = fd;
    r.x.cx = (int)(ofs >> 16);
    r.x.dx = (int)(ofs & 0xffffuL);
    int86(0x21, &r, &r);

    if (r.x.cflag)
    {
        errno = r.x.ax;
        return -1;
    }

    return ((long)r.x.dx << 16) | (long)r.x.ax;
#endif
}

int _stdc nclose(int fd)
{
    union REGS r;

    r.h.ah = 0x3e;

#ifdef __FLAT__
    r.x.ebx = fd;
    int386(0x21, &r, &r);
#else
    r.x.bx = fd;
    int86(0x21, &r, &r);
#endif

    _wcclearflags(fd);
#endif

    return (r.x.cflag ? -1 : 0);
}

int ndup(int fd)
{
    union REGS r;

#ifdef __FLAT__
    r.h.ah = 0x45;
    r.x.ebx = fd;

    int386(0x21, &r, &r);

    if (r.x.cflag)
    {
        errno = r.x.eax;
        return -1;
    }

    if (r.x.ax < __NFiles)
        __SetIOMode((int)r.x.ax, __IOMode(fd));
#endif

    return r.x.ax;
#endif
}

int ndup2(int fd1, int fd2)
{
    union REGS r;

    r.h.ah = 0x46;

#ifdef __FLAT__
    r.x.ebx = fd1;
    r.x.ecx = fd2;

    int386(0x21, &r, &r);

    if (r.x.cflag)
    {
        errno = r.x.eax;
        return -1;
    }
#else
    r.x.bx = fd1;
    r.x.cx = fd2;

    int86(0x21, &r, &r);

    if (r.x.cflag)
    {
        errno = r.x.ax;
        return -1;
    }
#endif


    p = (char *)name;

                 (permiss & S_IWRITE) ? FILE_NORMAL : FILE_READONLY,
                 ((mode & O_WRONLY) == O_WRONLY ? OPEN_ACCESS_WRITEONLY
                  : (mode & O_RDWR) == O_RDWR   ? OPEN_ACCESS_READWRITE
                                                : OPEN_ACCESS_READONLY) |
                     (shacc == SH_DENYWR   ? OPEN_SHARE_DENYWRITE
                      : shacc == SH_DENYRD ? OPEN_SHARE_DENYREAD
                      : shacc == SH_DENYRW ? OPEN_SHARE_DENYREADWRITE
                                           : OPEN_SHARE_DENYNONE) |
                     OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_LOCALITY,
                 (permiss & S_IWRITE) ? FILE_NORMAL : FILE_READONLY,
                 ((mode & O_WRONLY) == O_WRONLY ? OPEN_ACCESS_WRITEONLY
                  : (mode & O_RDWR) == O_RDWR   ? OPEN_ACCESS_READWRITE
                                                : OPEN_ACCESS_READONLY) |
                     (shacc == SH_DENYWR   ? OPEN_SHARE_DENYWRITE
                      : shacc == SH_DENYRD ? OPEN_SHARE_DENYREAD
                      : shacc == SH_DENYRW ? OPEN_SHARE_DENYREADWRITE
                                           : OPEN_SHARE_DENYNONE) |
                     OPEN_FLAGS_NOINHERIT | OPEN_FLAGS_NO_LOCALITY,
    _wcsetiomode(hf, mode);
#endif

    if (hf != -1 && (mode & O_APPEND))
        nlseek(hf, 0L, SEEK_END);

    return hf;
}

int _stdc nread(int fd, char *buf, unsigned len)
{
#ifdef __FLAT__
    ULONG rc, got;
#else
    USHORT rc, got;
#endif

    rc = DosRead((HFILE)fd, buf, len, &got);

    if (rc)
    {
        errno = rc;
        return -1;
    }

    return got;
}

int _stdc nwrite(int fd, char *buf, unsigned len)
{
#ifdef __FLAT__
    ULONG rc, got;
#else
    USHORT rc, got;
#endif

    rc = DosWrite((HFILE)fd, buf, len, &got);

    if (rc)
    {
        errno = rc;
        return -1;
    }

    return got;
}

long _stdc nlseek(int fd, long ofs, int pos)
{
#ifdef __FLAT__
    ULONG rc;
#else
    USHORT rc;
#endif

    ULONG newpos;

#ifdef __FLAT__
    rc = DosSetFilePtr((HFILE)fd, ofs,
#else
    rc = DosChgFilePtr((HFILE)fd, ofs,
#endif
                       pos == SEEK_END   ? FILE_END
                       : pos == SEEK_CUR ? FILE_CURRENT
                                         : FILE_BEGIN,
                       &newpos);

    if (rc)
    {
        errno = rc;
        return -1;
    }

    return newpos;
}

int _stdc nclose(int fd)
{
#ifdef __FLAT__
    ULONG rc;
#else
    USHORT rc;
#endif

    rc = DosClose(fd);

    if (rc)
    {
        errno = rc;
        return -1;
    }

    if ((int)hfNew < __NFiles)
        __SetIOMode((int)hfNew, __IOMode(fd));
#endif

    return (int)hfNew;
}

int _stdc ndup2(int fd1, int fd2)
{
    HFILE hfNew = (HFILE)fd2;
    OS2UINT rc;

    if ((rc = DosDupHandle((HFILE)fd1, &hfNew)) != 0)
    {
        errno = rc;
        return -1;
    }


int _stdc nsopen(const char *name, int mode, int shacc, ...)
{
    return sopen(name, mode, shacc, S_IREAD | S_IWRITE);
}

int _stdc nread(int fd, char *buf, unsigned len) { return read(fd, buf, len); }

int _stdc nwrite(int fd, char *buf, unsigned len) { return write(fd, buf, len); }

long _stdc nlseek(int fd, long ofs, int pos) { return lseek(fd, ofs, pos); }

int _stdc nclose(int fd) { return close(fd); }

int _stdc ndup(int fd) { return dup(fd); }

int _stdc ndup2(int fd1, int fd2) { return dup2(fd1, fd2); }

#else
#error Unknown OS
#endif

#ifdef VALIDATTION_SUITE_1
main()
{
    int fd;
    char buf[2];

    if ((fd = nopen("open.obj", O_RDONLY | O_BINARY)) == -1)
    {
        printf("err opening open.obj\n");
        return 1;
    }

    printf("ntell(fd)=%ld\n", ntell(fd));

    printf("nread(fd, buf, 2)=%d\n", nread(fd, buf, 2));

    printf("ntell(fd)=%ld\n", ntell(fd));

    printf("nlseek(fd, 1, SEEK_SET)=%ld\n", nlseek(fd, 1L, SEEK_SET));

    printf("ntell(fd)=%ld\n", ntell(fd));

    printf("hdr=%c%c\n", buf[0], buf[1]);

    printf("nclose(fd)=%d\n", nclose(fd));
}
#endif

#ifdef VALIDATION_SUITE_2

main()
{
    int fd;

    if ((fd = nopen("nopen.obj", O_CREAT | O_TRUNC | O_EXCL | O_RDWR | O_BINARY,
                    S_IREAD | S_IWRITE)) == -1)
    {
        printf("  OK: O_EXCL1 (%d)\n", fd);
    }
    else
    {
        printf("FAIL: O_EXCL1\n");
        nclose(fd);
    }

    unlink("notexist.fil");

    if ((fd = nopen("notexist.fil", O_CREAT | O_TRUNC | O_EXCL | O_RDWR | O_BINARY,
                    S_IREAD | S_IWRITE)) == -1)
    {
        printf("FAIL: O_EXCL2 (%d)\n", fd);
    }
    else
    {
        printf("  OK: O_EXCL2\n");
        nclose(fd);
    }

    unlink("notexist.fil");

    if ((fd = nopen("notexist.fil", O_CREAT | O_EXCL | O_RDWR | O_BINARY, S_IREAD | S_IWRITE)) ==
        -1)
    {
        printf("FAIL: O_EXCL3 (%d)\n", fd);
    }
    else
    {
        printf("  OK: O_EXCL3\n");
        nclose(fd);
    }

    unlink("notexist.fil");

    if ((fd = nopen("notexist.fil", O_RDONLY | O_BINARY | O_EXCL, S_IREAD | S_IWRITE)) == -1)
    {
        printf("  OK: O_RDONLY1\n");
    }
    else
    {
        printf("FAIL: O_RDONLY1\n");
        nclose(fd);
    }

    if ((fd = nopen("notexist.fil", O_RDONLY | O_BINARY, S_IREAD | S_IWRITE)) == -1)
    {
        printf("  OK: O_RDONLY2\n");
    }
    else
    {
        printf("FAIL: O_RDONLY2\n");
        nclose(fd);
    }

    if ((fd = nopen("nopen.obj", O_RDONLY | O_BINARY, S_IREAD | S_IWRITE)) == -1)
    {
        printf("FAIL: O_RDONLY3 (%d)\n", fd);
    }
    else
    {
        if (nlseek(fd, 0, SEEK_END) > 1)
            printf("  OK: O_RDONLY3\n");
        else
            printf("FAIL: O_RDONLY3 (truncated)\n");

        nclose(fd);
    }

    if ((fd = nopen("nopen.obj", O_CREAT | O_RDWR | O_BINARY, S_IREAD | S_IWRITE)) == -1)
    {
        printf("FAIL: O_CREAT1 (%d)\n", fd);
    }
    else
    {
        if (nlseek(fd, 0, SEEK_END) > 1)
            printf("  OK: O_CREAT1\n");
        else
            printf("FAIL: O_CREAT1 (truncated)\n");

        nclose(fd);
    }

    if ((fd = nopen("nopen.obj", O_CREAT | O_TRUNC | O_RDWR | O_BINARY, S_IREAD | S_IWRITE)) == -1)
    {
        printf("FAIL: O_CREAT2 %d %d\n", fd, errno);
    }
    else
    {
        if (nlseek(fd, 0, SEEK_END) != 0)
            printf("FAIL: O_CREAT2 (not truncated)\n");
        else
            printf("  OK: O_CREAT2\n");

        nwrite(fd, "foo", 3);
        nclose(fd);
    }

    if ((fd = nopen("new.fil", O_CREAT | O_RDWR | O_BINARY, S_IREAD | S_IWRITE)) == -1)
    {
        printf("FAIL: O_CREAT3 (%d)\n", fd);
    }
    else
    {
        if (nlseek(fd, 0, SEEK_END) == 0)
        {
            long ofs;

            if ((ofs = nlseek(fd, 0x1234, SEEK_SET)) != 0x1234)
                printf("FAIL: O_CREAT3 (ofs=%lx)\n", ofs);
            else
                printf("  OK: O_CREAT3\n");

            nwrite(fd, "foo bar", 7);
        }
        else
            printf("FAIL: O_CREAT3 (not truncated)\n");

        nclose(fd);
    }

    unlink("new.fil");
    return 0;
}

#endif
