// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sq_msg.c,v 1.1.1.1 2002/10/01 17:54:32 sdudley Exp $";
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
#include <stdlib.h>
#include <string.h>


    if ((hmsg = palloc(sizeof *hmsg)) == NULL)
        return NULL;

    (void)memset(hmsg, 0, sizeof *hmsg);


static unsigned near _SquishHeaderValidRead(HAREA ha, SQHDR *psqh)
{
    if (psqh->next_frame > Sqd->foEnd || psqh->prev_frame > Sqd->foEnd)
    {
        msgapierr = MERR_BADF;
        return FALSE;
    }


static dword near _SquishTranslateNum(HAREA ha, dword dwMsg)
{
    if (dwMsg == MSGNUM_CUR)
        return ha->cur_msg;
    else if (dwMsg == MSGNUM_PREV)
        return ha->cur_msg - 1;
    else if (dwMsg == MSGNUM_NEXT)
        return ha->cur_msg + 1;
    else
        return dwMsg;
}


static unsigned near _SquishOpenMsgExisting(HMSG hmsg, dword dwMsg)
{
    SQHDR sqh;
    FOFS foMsg;


        if (dwMsg == 0)
        {
            HSqd->foPrev = NULL_FRAME;
            HSqd->foCur = NULL_FRAME;
            HSqd->foNext = HSqd->foFirst;
            hmsg->ha->cur_msg = 0;
        }

        msgapierr = MERR_NOENT;
        return FALSE;
    }


    if ((foMsg = _SquishGetFrameOfs(hmsg->ha, dwMsg)) == NULL_FRAME)
        return FALSE;


    if (!_SquishReadHdr(hmsg->ha, foMsg, &sqh) || !_SquishHeaderValidRead(hmsg->ha, &sqh))
    {
        return FALSE;
    }


static unsigned near _SquishBlankOldMsg(HMSG hmsg, dword dwMsg)
{
    SQIDX sqi;

    assert(HSqd->fHaveExclusive);

    if (!SidxGet(HSqd->hix, dwMsg, &sqi))
        return FALSE;


    hmsg->foRead = sqi.ofs;


    if (hmsg->sqhRead.frame_type == FRAME_UPDATE)
    {
        msgapierr = MERR_SHARE;
        return FALSE;
    }


    hmsg->uidUs = sqi.umsgid;


static unsigned near _SquishBlankNewMsg(HMSG hmsg)
{
    SQIDX sqi;

    assert(HSqd->fHaveExclusive);

    sqi.ofs = NULL_FRAME;
    sqi.hash = (dword)-1L;
    sqi.umsgid = HSqd->uidNext++;
    hmsg->uidUs = sqi.umsgid;

    return (unsigned)SidxPut(HSqd->hix, hmsg->dwMsg, &sqi);
}


static unsigned near _SquishReduceMaxInternal(HAREA ha, dword *pdwDeleted, FOFS *pfoFirst,
                                              FOFS *pfoFirstPrior)
{
    SQIDX sqi;
    SQHDR sqh;


        *pfoFirst = sqh.next_frame;

        if (*pfoFirstPrior == NULL_FRAME)
            *pfoFirstPrior = sqh.prev_frame;


static unsigned near _SquishReduceMaxPointers(HAREA ha, FOFS foFirst, dword dwDeleted,
                                              FOFS foFirstPrior)
{
    unsigned rc = TRUE;


    if (Sqd->wSkipMsg == 0)
    {
        Sqd->foFirst = foFirst;
        foFirstPrior = NULL_FRAME;
    }
    else
    {

    if (ha->cur_msg == (dword)Sqd->wSkipMsg + dwDeleted + 1)
    {

        if (Sqd->wSkipMsg == 0 || ha->num_msg == 0)
            Sqd->foPrev = NULL_FRAME;
        else
            Sqd->foPrev = _SquishGetFrameOfs(ha, (dword)Sqd->wSkipMsg);
    }
    else if (ha->cur_msg == (dword)Sqd->wSkipMsg)
    {

    if (ha->cur_msg > (dword)Sqd->wSkipMsg)
    {
        if (ha->cur_msg <= (dword)Sqd->wSkipMsg + dwDeleted)
        {
            SQHDR sqh;
            FOFS fo;


            if (Sqd->wSkipMsg &&
                (fo = _SquishGetFrameOfs(ha, (dword)Sqd->wSkipMsg)) != NULL_FRAME &&
                _SquishReadHdr(ha, fo, &sqh))
            {
                Sqd->foCur = fo;
                Sqd->foPrev = sqh.prev_frame;
                Sqd->foNext = sqh.next_frame;
                ha->cur_msg = Sqd->wSkipMsg;
            }
            else
            {
                Sqd->foNext = Sqd->foFirst;
                Sqd->foCur = NULL_FRAME;
                Sqd->foPrev = NULL_FRAME;
                ha->cur_msg = 0;
            }
        }
        else
        {

            ha->cur_msg -= dwDeleted;
        }
    }


    if (ha->num_msg == 0)
    {
        Sqd->foFirst = NULL_FRAME;
        Sqd->foLast = NULL_FRAME;
        Sqd->foNext = NULL_FRAME;
        Sqd->foPrev = NULL_FRAME;
        Sqd->foCur = NULL_FRAME;
    }

    return rc;
}


static unsigned near _SquishReduceMaxMsgs(HAREA ha)
{
    FOFS foFirstPrior = NULL_FRAME;
    FOFS foFirst = NULL_FRAME;
    dword dwDeleted = 0;
    unsigned rc = TRUE;

    assert(Sqd->fHaveExclusive);


    if (!_SquishBeginBuffer(Sqd->hix))
        return FALSE;


    if (!_SquishReduceMaxPointers(ha, foFirst, dwDeleted, foFirstPrior))
        rc = FALSE;


static unsigned near _SquishOpenMsgCreate(HMSG hmsg, dword dwMsg)
{
    unsigned rc = TRUE;


    if (!_SquishExclusiveBegin(hmsg->ha))
        return FALSE;


    if (dwMsg == 0)
        rc = _SquishReduceMaxMsgs(hmsg->ha);


    if (rc)
    {
        if (dwMsg)
            rc = _SquishBlankOldMsg(hmsg, dwMsg);
        else
            rc = _SquishBlankNewMsg(hmsg);
    }


    if (!_SquishExclusiveEnd(hmsg->ha))
        rc = FALSE;

    return rc;
}


    if ((hmsg = NewHmsg(ha, wMode)) == NULL)
        return NULL;


    if (wMode == MOPEN_CREATE)
        fOpened = _SquishOpenMsgCreate(hmsg, dwMsg);
    else
        fOpened = _SquishOpenMsgExisting(hmsg, dwMsg);


        pfree(hmsg);
        hmsg = NULL;
    }

    return hmsg;
}


static unsigned near _SquishCloseUndoWrite(HMSG hmsg)
{
    if (!_SquishExclusiveBegin(hmsg->ha))
        return FALSE;


static unsigned near _SquishCloseRemoveList(HMSG hmsg)
{
    HMSG hm = HSqd->hmsgOpen;

    if (!hm)
    {
        msgapierr = MERR_BADA;
        return FALSE;
    }


    while (hm)
    {

sword MAPIENTRY SquishCloseMsg(HMSG hmsg)
{
    if (MsgInvalidHmsg(hmsg))
        return -1;


    (void)_SquishCloseRemoveList(hmsg);


    pfree(hmsg);
    return 0;
}
