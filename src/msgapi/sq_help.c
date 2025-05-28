// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sq_help.c,v 1.1.1.1 2002/10/01 17:54:29 sdudley Exp $";
#pragma on(unreferenced)

#define MSGAPI_HANDLERS
#define MSGAPI_NO_OLD_TYPES

#include "api_sq.h"
#include "apidebug.h"
#include "msgapi.h"
#include "prog.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>


unsigned _SquishWriteBaseHeader(HAREA ha, SQBASE *psqb)
{
    if (lseek(Sqd->sfd, 0L, SEEK_SET) != 0 ||
        write(Sqd->sfd, (char *)psqb, sizeof *psqb) != (int)sizeof *psqb)
    {
        msgapierr = MERR_NODS;
        return FALSE;
    }

    return TRUE;
}


unsigned _SquishInsertFreeChain(HAREA ha, FOFS fo, SQHDR *psqh)
{
    SQHDR sqh = *psqh;

    assert(Sqd->fHaveExclusive);

    sqh.id = SQHDRID;
    sqh.frame_type = FRAME_FREE;
    sqh.msg_length = sqh.clen = 0L;


        if (!_SquishWriteHdr(ha, fo, &sqh))
            return FALSE;

        Sqd->foFree = Sqd->foLastFree = fo;
        return TRUE;
    }


    sqh.prev_frame = Sqd->foLastFree;
    sqh.next_frame = NULL_FRAME;


    if (_SquishWriteHdr(ha, fo, &sqh))
    {
        Sqd->foLastFree = fo;
        return TRUE;
    }
    else
    {

        (void)_SquishSetFrameNext(ha, sqh.prev_frame, NULL_FRAME);
        return FALSE;
    }
}


unsigned _SquishSetFramePrev(HAREA ha, FOFS foModify, FOFS foValue)
{
    SQHDR sqh;

    if (!_SquishReadHdr(ha, foModify, &sqh))
        return FALSE;

    sqh.prev_frame = foValue;

    return _SquishWriteHdr(ha, foModify, &sqh);
}


unsigned _SquishWriteMode(HMSG hmsg)
{
    if (hmsg->wMode != MOPEN_CREATE && hmsg->wMode != MOPEN_WRITE && hmsg->wMode != MOPEN_RW)
    {
        msgapierr = MERR_EACCES;
        return FALSE;
    }

    return TRUE;
}


    if (dwMsg == ha->cur_msg)
        return Sqd->foCur;
    else if (dwMsg == ha->cur_msg - 1)
        return Sqd->foPrev;
    else if (dwMsg == ha->cur_msg + 1)
        return Sqd->foNext;


    if (!SidxGet(Sqd->hix, dwMsg, &sqi))
        return NULL_FRAME;

    return sqi.ofs;
}


    if (fo < sizeof(SQBASE))
    {
        msgapierr = MERR_BADA;
        return FALSE;
    }


unsigned _SquishWriteHdr(HAREA ha, FOFS fo, SQHDR *psqh)
{

unsigned _SquishFixMemoryPointers(HAREA ha, dword dwMsg, SQHDR *psqh)
{
    assert(Sqd->fHaveExclusive);


    if (dwMsg == ha->cur_msg + 1)
        Sqd->foNext = psqh->next_frame;

    if (dwMsg == ha->cur_msg - 1)
        Sqd->foPrev = psqh->prev_frame;


        if (!_SquishReadHdr(ha, psqh->prev_frame, &sqh))
        {

            Sqd->foCur = psqh->prev_frame;
            Sqd->foPrev = sqh.prev_frame;
            Sqd->foNext = sqh.next_frame;
            ha->cur_msg--;
        }
    }
    else
    {

        if (ha->cur_msg >= dwMsg)
            ha->cur_msg--;
    }


unsigned _SquishFreeIndex(HAREA ha, dword dwMsg, SQIDX *psqi, dword dwIdxSize, unsigned fWrite)
{
    unsigned rc = TRUE;
    long ofs;

    if (fWrite)
    {

        rc = (lseek(Sqd->ifd, ofs, SEEK_SET) == ofs &&
              write(Sqd->ifd, (char *)psqi, (unsigned)dwIdxSize) == (int)dwIdxSize);
    }

    pfree(psqi);

    return rc;
}

#if 0

  dwIdxSize = ((long)ha->num_msg - (long)dwMsg + 1L) * (long)sizeof(SQIDX);



  if ((psqi=palloc((size_t)dwIdxSize))==NULL)
  {
    msgapierr=MERR_NOMEM;
    return NULL;
  }



  if (lseek(Sqd->ifd, ofs, SEEK_SET) != ofs ||
      read(Sqd->ifd, (char *)psqi, (unsigned)dwIdxSize) != (signed)dwIdxSize)
  {
    msgapierr=MERR_BADF;
    pfree(psqi);
    return NULL;
  }

  *pdwIdxSize=dwIdxSize;
  return psqi;
}


unsigned _SquishRemoveIndex(HAREA ha, dword dwMsg, SQIDX *psqiOut, SQHDR *psqh)
{
  dword dwIdxSize;
  SQIDX *psqiLast;
  SQIDX *psqi;
  unsigned rc;

  assert(Sqd->fHaveExclusive);


  if (psqiOut)
    memmove(psqiOut, psqi, sizeof(SQIDX));



  psqiLast=psqi + (ha->num_msg - (long)dwMsg);

  psqiLast->ofs=NULL_FRAME;
  psqiLast->umsgid=(UMSGID)-1L;
  psqiLast->hash=(dword)-1L;



  if (rc)
    rc=_SquishFixMemoryPointers(ha, dwMsg, psqh);

  return rc;
}
#endif
