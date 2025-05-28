// SPDX-License-Identifier: GPL-2.0-or-later


#define IOTYPE _RTLENTRYF _EXPFUNC
#else
#define IOTYPE _stdc
#endif


int _stdc sopen(const char *name, int mode, int shacc, ...)
{
    return nsopen(name, mode, shacc, S_IREAD | S_IWRITE);
}

int _stdc open(const char *name, int mode, ...) { return nopen(name, mode, S_IREAD | S_IWRITE); }

#if defined(__TOPAZ__) || defined(__BORLANDC__)
int IOTYPE read(int fd, void *buf, unsigned len)
#else
int IOTYPE read(int fd, char *buf, unsigned len)
#endif
{
    return nread(fd, buf, len);
}

#if defined(__TOPAZ__) || defined(__BORLANDC__)
int IOTYPE write(int fd, const void *buf, unsigned len)
#else
int IOTYPE write(int fd, char *buf, unsigned len)
#endif
{
    return nwrite(fd, buf, len);
}

long IOTYPE lseek(int fd, long ofs, int pos) { return nlseek(fd, ofs, pos); }

long IOTYPE tell(int fd) { return ntell(fd); }

int IOTYPE close(int fd) { return nclose(fd); }

int IOTYPE dup(int fd) { return ndup(fd); }

int IOTYPE dup2(int fd1, int fd2) { return ndup2(fd1, fd2); }
#endif
