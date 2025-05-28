// SPDX-License-Identifier: GPL-2.0-or-later


#include "ffind.h"
#include "mexall.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef MEX

int MexAddFHandle(struct _mex_instance_stack *pmis, int fd)
{
    int i;

    for (i = 0; i < MAX_MEXFH; ++i)
    {
        if (pmis->fht[i] == (word)-1)
        {
            pmis->fht[i] = (word)fd;
            return TRUE;
        }
    }

    return FALSE;
}

int MexDelFHandle(struct _mex_instance_stack *pmis, int fd)
{
    int i;

    for (i = 0; i < MAX_MEXFH; ++i)
    {
        if (pmis->fht[i] == (word)fd)
        {
            close(fd);
            pmis->fht[i] = (word)-1;
            return TRUE;
        }
    }

    return FALSE;
}


    if (!s)
        mode = -1;
    else
    {
        mode = 0;

        if (wMode & IOPEN_CREATE)
            mode |= O_CREAT | O_TRUNC;

        if ((wMode & IOPEN_RW) == IOPEN_RW)
            mode |= O_RDWR;
        else if (wMode & IOPEN_WRITE)
            mode |= O_WRONLY;
        else
            mode |= O_RDONLY;

        if (wMode & IOPEN_APPEND)
            mode |= O_APPEND;

        if (wMode & IOPEN_BINARY)
            mode |= O_BINARY;

        mode = sopen(s, mode, SH_DENYNO, S_IREAD | S_IWRITE);
        free(s);

        if (mode != -1)
        {
            if (!MexAddFHandle(pmisThis, mode))
            {
                close(mode);
                mode = -1;
            }
        }
    }

    regs_2[0] = mode;
    return MexArgEnd(&ma);
}


    fd = MexArgGetWord(&ma);
    MexArgGetRefString(&ma, &where, &wLen);
    len = MexArgGetWord(&ma);

    if ((s = malloc(len)) != NULL)
    {
        regs_2[0] = read(fd, s, len);
        MexKillString(&where);

        MexStoreByteStringAt(MexIaddrToVM(&where), s, (int)regs_2[0] > 0 ? regs_2[0] : 0);
        free(s);

word EXPENTRY intrin_readln(void)
{
    MA ma;
    IADDR where;
    word wLen;
    char *s;
    int fd;

    MexArgBegin(&ma);

    fd = MexArgGetWord(&ma);
    MexArgGetRefString(&ma, &where, &wLen);

#define MEX_MAX_LINE 512


        s[MEX_MAX_LINE] = 0;

        if (got > 0)
            s[got] = 0;


        lseek(fd, lPosn + (long)len, SEEK_SET);

        MexKillString(&where);
        MexStoreByteStringAt(MexIaddrToVM(&where), s, len);

word EXPENTRY intrin_write(void)
{
    MA ma;
    IADDR where;
    word wLen;
    char *s;
    int fd, len;

    MexArgBegin(&ma);
    fd = MexArgGetWord(&ma);
    s = MexArgGetRefString(&ma, &where, &wLen);
    len = MexArgGetWord(&ma);

    len = min(len, wLen);

    regs_2[0] = write(fd, s, len);


    return MexArgEnd(&ma);
}


    return MexArgEnd(&ma);
}


word EXPENTRY intrin_tell(void)
{
    MA ma;
    int fd;

    MexArgBegin(&ma);
    fd = MexArgGetWord(&ma);

    regs_4[0] = tell(fd);

    return MexArgEnd(&ma);
}


    return MexArgEnd(&ma);
}

word EXPENTRY intrin_rename(void)
{
    MA ma;
    char *oldname, *newname;

    MexArgBegin(&ma);
    oldname = MexArgGetString(&ma, FALSE);
    newname = MexArgGetString(&ma, FALSE);
    if (!oldname || !newname)
        regs_2[0] = FALSE;
    else
        regs_2[0] = (rename(oldname, newname) == 0);
    if (oldname)
        free(oldname);
    if (newname)
        free(newname);
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_remove(void)
{
    MA ma;
    char *filename;

    MexArgBegin(&ma);
    filename = MexArgGetString(&ma, FALSE);
    if (!filename)
        regs_2[0] = FALSE;
    else
    {
        regs_2[0] = (remove(filename) == 0);
        free(filename);
    }
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_filecopy(void)
{
    MA ma;
    char *oldname, *newname;
    int ret;

    MexArgBegin(&ma);
    oldname = MexArgGetString(&ma, FALSE);
    newname = MexArgGetString(&ma, FALSE);
    if (!oldname || !newname)
        ret = -1;
    else
        ret = lcopy(oldname, newname);
    if (oldname)
        free(oldname);
    if (newname)
        free(newname);

    regs_2[0] = (ret == 0);
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_fileexists(void)
{
    MA ma;
    char *filename;

    MexArgBegin(&ma);
    filename = MexArgGetString(&ma, FALSE);
    if (!filename)
        regs_2[0] = 0;
    else
    {
        regs_2[0] = fexist(filename);
        free(filename);
    }
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_filesize(void)
{
    MA ma;
    char *filename;

    MexArgBegin(&ma);
    filename = MexArgGetString(&ma, FALSE);
    if (!filename)
        regs_4[0] = -1;
    else
    {
        regs_4[0] = fsize(filename);
        free(filename);
    }
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_filedate(void)
{
    MA ma;
    char *filename;
    struct mex_stamp *ms;

    MexArgBegin(&ma);
    filename = MexArgGetString(&ma, FALSE);
    ms = MexArgGetRef(&ma);
    regs_4[0] = FALSE;
    if (filename)
    {
        FFIND *ff = FindOpen(filename, ATTR_READONLY | ATTR_SUBDIR);
        if (ff)
        {
            StampToMexStamp(&ff->scWdate, ms);
            FindClose(ff);
            regs_4[0] = TRUE;
        }
        free(filename);
    }
    return MexArgEnd(&ma);
}

