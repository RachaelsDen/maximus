// SPDX-License-Identifier: GPL-2.0-or-later


#include "bfile.h"
#include "nopen.h"
#include "prog.h"
#include <dos.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <share.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


static int near TranslateBShare(int fShare)
{
    if (fShare & BSH_COMPAT)
        return SH_COMPAT;
    else if (fShare & BSH_DENYNO)
        return SH_DENYNO;
    else if (fShare & BSH_DENYRW)
        return SH_DENYRW;
    else if (fShare & BSH_DENYWR)
        return SH_DENYWR;
    else if (fShare & BSH_DENYRD)
        return SH_DENYRD;
    else
        return SH_DENYNO;
}


    if (b->lDeltaLo == -1)
        return 0;


    lseek(b->fd, b->lPos + b->lDeltaLo, SEEK_SET);

    size = (size_t)(b->lDeltaHi - b->lDeltaLo);


static int near Brefill(BFILE b)
{
    long lNewPos;
    unsigned uiSaved;
    int iGot;


    uiSaved = (unsigned)(b->pcBufEnd - b->pcBufCur);

    if (b->pcBuf != b->pcBufCur)
        memmove(b->pcBuf, b->pcBufCur, uiSaved);



    lNewPos = b->lPos + (b->pcBufEnd - b->pcBuf);

    if (lseek(b->fd, lNewPos, SEEK_SET) != lNewPos)
        return -1;


    b->pcBufEnd += iGot;
    return 0;
}


    if ((b = malloc(sizeof(*b))) == NULL)
    {
        errno = ENOMEM;
        return NULL;
    }

    memset(b, '\0', sizeof *b);


    if ((b->fd = nsopen(pszName, TranslateBMode(fMode), TranslateBShare(fShare),
                        S_IREAD | S_IWRITE)) == -1)
    {
        free(b);
        return NULL;
    }


    b->pcBufCur = b->pcBuf;
    b->pcBufEnd = b->pcBuf;
    b->stBufSize = stBufSize;
    b->lDeltaLo = b->lDeltaHi = -1;

    b->lPos = 0L;

    return b;
}


    rc = Bflush(b);


    nclose(b->fd);
    free(b);

    return rc == 0 ? 0 : -1;
}


    if ((b->fMode & BO_RDONLY) == 0)
    {
        errno = EACCES;
        return -1;
    }

    do
    {
        unsigned uiPass;


            memmove(pvBuf, b->pcBufCur, uiPass);


        if (uiPass == 0 || b->pcBufCur == b->pcBufEnd)
            if (Brefill(b) == -1)
                break;
    } while (uiSize);

    return uiGot;
}


        uiPass = (unsigned)(b->stBufSize - (b->pcBufCur - b->pcBuf));
        uiPass = min(uiPass, uiSize);


            memmove(b->pcBufCur, pvBuf, uiPass);


            b->pcBufCur += uiPass;

            if (b->pcBufCur > b->pcBufEnd)
                b->pcBufEnd = b->pcBufCur;

            pvBuf = (void *)((char *)pvBuf + uiPass);
            uiGot += uiPass;
            uiSize -= uiPass;
        }


int _fast _Bgetc(BFILE b)
{
    if (b->pcBufCur < b->pcBufEnd)
        return *b->pcBufCur++;

    Brefill(b);

    if (b->pcBufCur < b->pcBufEnd)
        return *b->pcBufCur++;
    else
        return EOF;
}


        lNewPos = lseek(b->fd, 0L, SEEK_END);


int _fast Bfileno(BFILE b) { return b->fd; }


char *_fast Bgets(char *pszOut, unsigned uiMaxLen, BFILE b)
{
    int ch = 0;
    char *s, *end;

    for (s = pszOut, end = s + uiMaxLen; s < end;)
    {
        if ((ch = Bgetc(b)) == '\n' || ch == EOF)
            break;

        *s++ = (char)ch;
    }

    *s++ = '\0';

    if (ch == EOF && s == pszOut + 1)
        return NULL;

    Strip_Trailing(pszOut, '\r');

    return pszOut;
}

