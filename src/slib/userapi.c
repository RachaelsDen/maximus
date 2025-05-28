// SPDX-License-Identifier: GPL-2.0-or-later


#include "userapi.h"
#include "compiler.h"
#include "max.h"
#include "prog.h"
#include "uni.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef OS_2
#define INCL_DOS
#include "pos2.h"
#endif

dword _fast UserHash(byte *f)
{
    dword hash = 0, g;
    signed char *p;

    for (p = f; *p; p++)
    {
        hash = (hash << 4) + (dword)tolower(*p);

        if ((g = (hash & 0xf0000000L)) != 0L)
        {
            hash |= g >> 24;
            hash |= g;
        }
    }

    return (hash & 0x7fffffffLu);
}


static void near _RebuildIndex(HUF huf)
{
    long idxsize = lseek(huf->fdndx, 0L, SEEK_END) / (long)sizeof(USRNDX);
    long size = UserFileSize(huf);
    struct _usr user;
    USRNDX usrndx;


    if (size == idxsize)
        return;

    lseek(huf->fdbbs, 0L, SEEK_SET);
    lseek(huf->fdndx, 0L, SEEK_SET);


static int near _UserMatch(HUF huf, long ofs, char *name, char *alias, struct _usr *pusr)
{
    long pos = (long)sizeof(struct _usr) * ofs;
    int fNameMatch;
    int fAliasMatch;

    if (lseek(huf->fdbbs, pos, SEEK_SET) != pos)
        return FALSE;

    if (read(huf->fdbbs, (char *)pusr, sizeof *pusr) != sizeof *pusr)
        return FALSE;

    fNameMatch = (name && eqstri(pusr->name, name));
    fAliasMatch = (alias && eqstri(pusr->alias, alias));

    return ((fNameMatch && !alias) || (fAliasMatch && !name) || (fNameMatch && fAliasMatch) ||
            (!name && !alias));
}


HUF _fast UserFileOpen(char *name, int mode)
{
    char filename[PATHLEN];
    int tries;
    HUF huf;

    if ((huf = malloc(sizeof(*huf))) == NULL)
        return NULL;

    huf->id_huf = ID_HUF;

    strcpy(filename, name);
    strcat(filename, ".bbs");

    for (tries = 10; tries--;)
    {
        if ((huf->fdbbs =
                 sopen(filename, O_RDWR | O_BINARY | mode, SH_DENYNO, S_IREAD | S_IWRITE)) != -1)
            break;

#ifdef OS_2
        if (fexist(name))
            DosSleep(1L);
#endif
    }

    if (huf->fdbbs == -1)
    {
        free(huf);
        return NULL;
    }

    strcpy(filename, name);
    strcat(filename, ".idx");

    if ((huf->fdndx = sopen(filename, O_RDWR | O_BINARY | mode, SH_DENYNO, S_IREAD | S_IWRITE)) ==
        -1)
    {

long _fast UserFileSize(HUF huf)
{
    long len;

    if (!huf || huf->id_huf != ID_HUF)
        return -1L;

    len = lseek(huf->fdbbs, 0L, SEEK_END);
    len /= (long)sizeof(struct _usr);

    return len;
}

int _fast UserFileSeek(HUF huf, long rec, struct _usr *pusr, int sz)
{
    long len;

    if ((len = UserFileSize(huf)) == -1L)
        return FALSE;

    if (rec == -1)
        rec = len - 1;

    if (rec < 0 || rec >= len)
        return FALSE;

    lseek(huf->fdbbs, rec * sizeof(struct _usr), SEEK_SET);
    return read(huf->fdbbs, (char *)pusr, sz) == sz;
}


static int _fast _UserFileFind(HUF huf, char *name, char *alias, struct _usr *pusr, long *plOfs,
                               long lStartOfs, int fForward)
{
    dword hash_name = name ? UserHash(name) : -1L;
    dword hash_alias = alias ? UserHash(alias) : -1L;
    USRNDX *pun, *pu;
    long ofs;
    int got;


    if ((pun = malloc(sizeof(USRNDX) * UNDX_BLOCK)) == NULL)
        return FALSE;


        got /= (int)sizeof(USRNDX);

        for (pu = fForward ? pun : pun + got - 1; got--; fForward ? pu++ : pu--)
        {
            if (name && hash_name == pu->hash_name && !alias ||
                alias && hash_alias == pu->hash_alias && !name ||
                hash_name == pu->hash_name && hash_alias == pu->hash_alias || !name && !alias)
            {

int _fast UserFileFind(HUF huf, char *name, char *alias, struct _usr *pusr)
{
    long ofs;

    if (!huf || huf->id_huf != ID_HUF)
        return FALSE;

    return _UserFileFind(huf, name, alias, pusr, &ofs, 0L, TRUE);
}


HUFF _fast UserFileFindOpen(HUF huf, char *name, char *alias)
{
    HUFF huff;

    if (!huf || huf->id_huf != ID_HUF)
        return NULL;

    if ((huff = malloc(sizeof *huff)) == NULL)
        return NULL;

    huff->id_huff = ID_HUFF;
    huff->huf = huf;
    huff->lLastUser = -1L;
    huff->ulStartNum = 0L;
    huff->cUsers = 0;


int _fast UserFileFindNext(HUFF huff, char *name, char *alias)
{
    HUF huf;
    dword dwSize;
    long ofs;

    if (!huff || huff->id_huff != ID_HUFF)
        return FALSE;

    huf = huff->huf;
    dwSize = UserFileSize(huf);


    if (name || alias)
    {
        if (_UserFileFind(huf, name, alias, &huff->usr, &ofs, huff->lLastUser + 1, TRUE))
        {
            huff->lLastUser = ofs;
            return TRUE;
        }

        return FALSE;
    }


        if (ofs < huff->ulStartNum || ofs >= huff->ulStartNum + huff->cUsers)
        {
            int size = UBBS_BLOCK * sizeof(struct _usr);
            int got;

            lseek(huf->fdbbs, ofs * (long)sizeof(struct _usr), SEEK_SET);
            got = read(huf->fdbbs, (char *)huff->pusr, size);


            if (got < 0 || ofs < huff->ulStartNum || ofs >= huff->ulStartNum + huff->cUsers)
            {
                huff->lLastUser = UserFileSize(huf);
                return FALSE;
            }
        }

        huff->usr = huff->pusr[ofs - huff->ulStartNum];
        huff->lLastUser = ofs;
        return TRUE;
    }

    huff->lLastUser = UserFileSize(huf);
    return FALSE;
}


    if (name || alias)
    {
        if (_UserFileFind(huf, name, alias, &huff->usr, &ofs, huff->lLastUser - 1, FALSE))
        {
            huff->lLastUser = ofs;
            return TRUE;
        }

        return FALSE;
    }


        if (ofs < huff->ulStartNum || ofs >= huff->ulStartNum + huff->cUsers)
        {
            int size = UBBS_BLOCK * sizeof(struct _usr);
            int got;

            lseek(huf->fdbbs, ofs * (long)sizeof(struct _usr), SEEK_SET);
            got = read(huf->fdbbs, (char *)huff->pusr, size);

            if (got >= 0)
                got /= sizeof(struct _usr);

            if (got >= 0)
            {
                huff->ulStartNum = ofs;
                huff->cUsers = got;
            }


int _fast UserFileFindClose(HUFF huff)
{
    if (!huff || huff->id_huff != ID_HUFF)
        return FALSE;

    free(huff->pusr);
    free(huff);

    return TRUE;
}


    if (!_UserFileFind(huf, name, alias, &usr, &ofs, 0L, TRUE))
        return FALSE;


    usrndx.hash_name = UserHash(pusr->name);
    usrndx.hash_alias = UserHash(pusr->alias);


int _fast UserFileCreateRecord(HUF huf, struct _usr *pusr, int fCheckUnique)
{
    USRNDX usrndx;
    long ofs = UserFileSize(huf);
    struct _usr junkusr;


    lseek(huf->fdbbs, ofs * (long)sizeof(struct _usr), SEEK_SET);
    lseek(huf->fdndx, ofs * (long)sizeof(USRNDX), SEEK_SET);


    return write(huf->fdbbs, (char *)pusr, sizeof *pusr) == sizeof *pusr &&
           write(huf->fdndx, (char *)&usrndx, sizeof(USRNDX)) == sizeof(USRNDX);
}


int _fast UserFileClose(HUF huf)
{
    if (!huf || huf->id_huf != ID_HUF)
        return FALSE;

    if (huf->fdbbs != -1)
        close(huf->fdbbs);

    if (huf->fdndx != -1)
        close(huf->fdndx);

    memset(huf, 0, sizeof huf);
    free(huf);
    return TRUE;
}
