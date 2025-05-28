// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sq_idx.c,v 1.1.1.1 2002/10/01 17:54:31 sdudley Exp $";
#pragma on(unreferenced)

#define MSGAPI_HANDLERS
#define MSGAPI_NO_OLD_TYPES

#include "api_sq.h"
#include "apidebug.h"
#include "msgapi.h"
#include "prog.h"
#include <assert.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define HixSqd ((struct _sqdata *)(hix)->ha->apidata)

#ifdef __FLAT__
#define SEGMENT_SIZE (32767L / (long)sizeof(SQIDX))
#define SHIFT_SIZE 8192
#endif

#if defined(__FARDATA__) || defined(__FLAT__)
#define fmemmove memmove
#else
#define fmemmove f_memmove
#endif


    hix->id = ID_HIDX;
    hix->ha = ha;
    hix->lDeltaLo = -1;
    hix->lDeltaHi = -1;
    hix->cSeg = 0;
    hix->fBuffer = 0;
    hix->fHadExclusive = FALSE;

    return hix;
}


int _SquishBeginBuffer(HIDX hix)
{
    dword dwMsgs;
    int i;

    assert(hix->id == ID_HIDX);


    if ((hix->pss = palloc(sizeof(SQIDXSEG) * (unsigned)hix->cSeg)) == NULL)
    {
        msgapierr = MERR_NOMEM;
        hix->fBuffer = 0;
        return FALSE;
    }


    if ((hix->lAllocatedRecords = lseek(HixSqd->ifd, 0L, SEEK_END)) < 0)
    {
        msgapierr = MERR_BADF;
        hix->fBuffer = 0;
        return FALSE;
    }


    (void)lseek(HixSqd->ifd, 0L, SEEK_SET);


        if ((hix->pss[i].psqi = farpalloc((size_t)dwSize * (size_t)sizeof(SQIDX))) == NULL)
        {
            while (i--)
                farpfree(hix->pss[i].psqi);

            pfree(hix->pss);

            msgapierr = MERR_NOMEM;
            hix->fBuffer = 0;
            return FALSE;
        }

        hix->pss[i].dwMax = dwSize;


        if (dwSize != SEGMENT_SIZE)
            dwMsgs = 0;
        else
            dwMsgs -= SEGMENT_SIZE;

        hix->pss[i].dwUsed = dwSize;
    }


static SQIDX far *sidx(HIDX hix, dword dwMsg)
{
    dword dwStart = 1L;
    int i;

    for (i = 0; i < hix->cSeg; i++)
    {
        if (dwMsg >= dwStart && dwMsg < dwStart + hix->pss[i].dwUsed)
            return hix->pss[i].psqi + (size_t)(dwMsg - dwStart);

        dwStart += hix->pss[i].dwUsed;
    }

    return NULL;
}


static int near _SquishAppendIndexRecord(HIDX hix, SQIDX *psqi)
{
    SQIDXSEG *pss;


        hix->lAllocatedRecords = hix->ha->num_msg + 64;
        lSize = (hix->lAllocatedRecords - 1) * (long)sizeof(SQIDX);

        sqi.ofs = 0L;
        sqi.umsgid = (UMSGID)-1L;
        sqi.hash = (UMSGID)-1L;


        if (lseek(HixSqd->ifd, lSize, SEEK_SET) != lSize ||
            write(HixSqd->ifd, (char *)&sqi, sizeof sqi) != sizeof(sqi))
        {
            msgapierr = MERR_NODS;
            return FALSE;
        }
    }


        pss = hix->pss + hix->cSeg - 1;


        if (pss->dwMax < SEGMENT_SIZE)
        {
            SQIDX far *psqiNew;

            assert(pss->dwMax >= pss->dwUsed);


            if ((psqiNew = farpalloc(((size_t)pss->dwMax + MORE_SPACE) * sizeof(SQIDX))) == NULL)
            {
                msgapierr = MERR_NOMEM;
                return FALSE;
            }

            (void)fmemmove(psqiNew, pss->psqi, (size_t)pss->dwUsed * (size_t)sizeof(SQIDX));

            psqiNew[(size_t)pss->dwUsed] = *psqi;

            pss->dwUsed++;
            pss->dwMax += MORE_SPACE;

            farpfree(pss->psqi);
            pss->psqi = psqiNew;
            return TRUE;
        }
    }


    if ((pss = palloc(sizeof(SQIDXSEG) * (size_t)(hix->cSeg + 1))) == NULL)
    {
        msgapierr = MERR_NOMEM;
        return FALSE;
    }

    (void)memmove(pss, hix->pss, (size_t)hix->cSeg * sizeof(SQIDXSEG));
    hix->pss = pss;


    pss->dwUsed = 1;
    pss->dwMax = MORE_SPACE;
    *pss->psqi = *psqi;


int SidxPut(HIDX hix, dword dwMsg, SQIDX *psqi)
{
    SQIDX far *psqiFound;
    int rc;

    assert(hix->id == ID_HIDX);

    if (!hix->fBuffer)
    {
        (void)lseek(HixSqd->ifd, (long)(dwMsg - 1) * (long)sizeof(SQIDX), SEEK_SET);

        if (farwrite(HixSqd->ifd, (char far *)psqi, sizeof(SQIDX)) != (int)sizeof(SQIDX))
        {
            msgapierr = MERR_NODS;
            return FALSE;
        }

        return TRUE;
    }


        if (dwMsg == hix->ha->num_msg + 1)
            rc = _SquishAppendIndexRecord(hix, psqi);
    }
    else
    {
        *psqiFound = *psqi;
        rc = TRUE;
    }

    if (rc)
    {
        if (hix->lDeltaLo == -1 || hix->lDeltaLo > (long)dwMsg)
            hix->lDeltaLo = (long)dwMsg;

        if (hix->lDeltaHi == -1 || hix->lDeltaHi < (long)dwMsg)
            hix->lDeltaHi = (long)dwMsg;
    }

    return rc;
}


    sqi.ofs = NULL_FRAME;
    sqi.umsgid = (UMSGID)-1L;
    sqi.hash = (dword)-1L;

    if (hix->fBuffer)
    {
        dword dwStart = 1L;


            if (dwMsg >= dwStart && dwMsg < dwStart + hix->pss[i].dwUsed)
            {
                int j = (int)(dwMsg - dwStart);
                unsigned rc = TRUE;


                (void)fmemmove(hix->pss[i].psqi + j, hix->pss[i].psqi + j + 1,
                               (size_t)(hix->pss[i].dwUsed - (dword)j - (dword)1) *
                                   (size_t)sizeof(SQIDX));

                hix->pss[i].dwUsed--;

                if (!_SquishAppendIndexRecord(hix, &sqi))
                    rc = FALSE;

                if (hix->lDeltaLo == -1 || hix->lDeltaLo > (long)dwMsg)
                    hix->lDeltaLo = (long)dwMsg;

                hix->lDeltaHi = (long)_SquishIndexSize(hix) / (long)sizeof(SQIDX);

                if (fFixPointers && rc)
                    return _SquishFixMemoryPointers(hix->ha, dwMsg, psqh);
                else
                    return rc;
            }

            dwStart += hix->pss[i].dwUsed;
        }


    (void)lseek(HixSqd->ifd, (long)dwMsg * (long)sizeof(SQIDX), SEEK_SET);

    if ((pcBuf = palloc(SHIFT_SIZE)) == NULL)
    {
        msgapierr = MERR_NOMEM;
        return FALSE;
    }

    while ((got = read(HixSqd->ifd, pcBuf, SHIFT_SIZE)) > 0)
    {

    (void)lseek(HixSqd->ifd, -(long)sizeof(SQIDX), SEEK_CUR);

    if (write(HixSqd->ifd, (char *)&sqi, sizeof(SQIDX)) != (int)sizeof(SQIDX))
    {
        msgapierr = MERR_BADF;
        return FALSE;
    }

    if (fFixPointers)
        return _SquishFixMemoryPointers(hix->ha, dwMsg, psqh);
    else
        return TRUE;
}


int _SquishEndBuffer(HIDX hix)
{
    int i;
    int rc = TRUE;
    long lSize;

    assert(hix->id == ID_HIDX);

    if (hix->fBuffer == 0)
        return FALSE;

    if (--hix->fBuffer != 0)
        return TRUE;


    if (hix->fHadExclusive)
        setfsize(HixSqd->ifd, lSize);


            if ((long)dwStart + (long)hix->pss[i].dwUsed > hix->lDeltaLo &&
                (long)dwStart <= hix->lDeltaHi)
            {
                size_t j, size;

                if ((long)dwStart > hix->lDeltaLo)
                    j = 0;
                else
                    j = (size_t)(hix->lDeltaLo - (long)dwStart);

                if ((long)dwStart + (long)hix->pss[i].dwUsed > hix->lDeltaHi)
                    size = (size_t)(hix->lDeltaHi - (long)dwStart + 1L);
                else
                    size = (size_t)(hix->pss[i].dwUsed);

                size -= j;

                uiWriteSize = (size_t)size * (size_t)sizeof(SQIDX);

                if (rc)
                {
                    if (farwrite(HixSqd->ifd, (char far *)(hix->pss[i].psqi + j), uiWriteSize) !=
                        (int)uiWriteSize)

                    {
                        msgapierr = MERR_NODS;
                        rc = FALSE;
                    }
                }
            }

            dwStart += hix->pss[i].dwUsed;
        }
    }

