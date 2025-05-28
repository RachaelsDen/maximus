// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sq_write.c,v 1.2 2003/06/05 22:54:50 wesgarland Exp $";
#pragma on(unreferenced)

#define MSGAPI_HANDLERS
#define MSGAPI_NO_OLD_TYPES

#include "api_sq.h"
#include "apidebug.h"
#include "msgapi.h"
#include "prog.h"
#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <string.h>


static unsigned near _SquishProbeFreeChain(HAREA ha, dword dwLen, FOFS *pfo, SQHDR *psqh,
                                           dword *pdwFrameLen)
{
    FOFS foThis, foLast;

    assert(Sqd->fHaveExclusive);


    for (foThis = Sqd->foFree; foThis != NULL_FRAME; foLast = foThis, foThis = psqh->next_frame)
    {

        if (psqh->frame_type != FRAME_FREE || foLast != psqh->prev_frame ||
            psqh->next_frame == foThis)
        {
            msgapierr = MERR_BADF;
            return FALSE;
        }


static unsigned near _SquishRemoveFreeChain(HAREA ha, FOFS fo, SQHDR *psqh)
{
    assert(Sqd->fHaveExclusive);


    if ((psqh->prev_frame == NULL_FRAME && fo != Sqd->foFree) ||
        (psqh->next_frame == NULL_FRAME && fo != Sqd->foLastFree))
    {
        msgapierr = MERR_BADF;
        return FALSE;
    }


    if (psqh->next_frame)
        if (!_SquishSetFramePrev(ha, psqh->next_frame, psqh->prev_frame))
            return FALSE;


static unsigned near _SquishGetFrameEOF(HAREA ha, FOFS *pfo, dword dwLen)
{
    char nul = 0;
    long ofs;

    assert(Sqd->fHaveExclusive);


    ofs = Sqd->foEnd + (long)Sqd->cbSqhdr + (long)dwLen - 1L;


    *pfo = Sqd->foEnd;
    Sqd->foEnd = ofs + 1;
    return TRUE;
}


static unsigned near _SquishGetNewFrame(HMSG hmsg, dword dwLen, FOFS *pfoNew, dword *pdwFrameLen)
{
    SQHDR sqh;
    FOFS fo;

    assert(HSqd->fHaveExclusive);


    if (!_SquishProbeFreeChain(hmsg->ha, dwLen, &fo, &sqh, pdwFrameLen))
        return FALSE;


    *pdwFrameLen = 0;
    return _SquishGetFrameEOF(hmsg->ha, pfoNew, dwLen);
}


static unsigned near _SquishLinkMessageFrame(HMSG hmsg, dword dwTotal, dword dwCtrlLen,
                                             dword dwFrameLen)
{
    assert(HSqd->fHaveExclusive);
    assert(dwFrameLen == 0 || dwFrameLen >= dwTotal);


    if (hmsg->foRead)
    {

        if (hmsg->sqhWrite.next_frame != NULL_FRAME)
        {
            if (!_SquishSetFramePrev(hmsg->ha, hmsg->sqhWrite.next_frame, hmsg->foWrite))
            {
                return FALSE;
            }
        }
    }
    else
    {

    if (hmsg->sqhWrite.prev_frame != NULL_FRAME)
    {
        if (!_SquishSetFrameNext(hmsg->ha, hmsg->sqhWrite.prev_frame, hmsg->foWrite))
        {
            return FALSE;
        }
    }


        assert(hmsg->foRead == HSqd->foFirst || HSqd->foFirst == NULL_FRAME);
        HSqd->foFirst = hmsg->foWrite;
    }


        if (hmsg->foRead)
            assert(hmsg->foRead == HSqd->foLast);

        HSqd->foLast = hmsg->foWrite;
    }


    return _SquishWriteHdr(hmsg->ha, hmsg->foWrite, &hmsg->sqhWrite);
}


static unsigned near _SquishGetWriteFrame(HMSG hmsg, dword dwTxtTotal, dword dwCtrlLen)
{
    dword dwTotal = (dword)XMSG_SIZE + dwTxtTotal + dwCtrlLen;
    dword dwFrameLen = 0;

    assert(HSqd->fHaveExclusive);


    if (hmsg->wMode == MOPEN_RW || hmsg->wMode == MOPEN_WRITE)
    {
        if (dwTotal > hmsg->sqhRead.msg_length)
        {
            msgapierr = MERR_TOOBIG;
            return FALSE;
        }


        hmsg->foWrite = hmsg->foRead;
        hmsg->sqhWrite = hmsg->sqhRead;
    }
    else if (hmsg->wMode == MOPEN_CREATE)
    {

        if (hmsg->foRead)
        {
            if (!_SquishInsertFreeChain(hmsg->ha, hmsg->foRead, &hmsg->sqhRead))
                return FALSE;
        }


        if (!_SquishGetNewFrame(hmsg, dwTotal, &hmsg->foWrite, &dwFrameLen))
        {

            if (hmsg->foRead)
            {

                (void)_SquishRemoveIndexEntry(HSqd->hix, hmsg->dwMsg, NULL, &hmsg->sqhRead, TRUE);
            }

            hmsg->foWrite = NULL_FRAME;
            return FALSE;
        }


static unsigned near _SquishWriteXmsg(HMSG hmsg, PXMSG pxm, dword *pdwOfs)
{
    XMSG xmsg;
    long ofs = hmsg->foWrite + HSqd->cbSqhdr;

        if (SidxGet(HSqd->hix, hmsg->dwMsg, &sqi))
            hmsg->uidUs = sqi.umsgid;
    }


    if (!hmsg->uidUs)
    {
        xmsg.attr &= ~MSGUID;
        xmsg.umsgid = (UMSGID)0L;
    }
    else
    {
        xmsg.attr |= MSGUID;
        xmsg.umsgid = hmsg->uidUs;
    }


static unsigned near _SquishWriteCtrl(HMSG hmsg, byte OS2FAR *szCtrl, dword dwCtrlLen,
                                      dword *pdwOfs)
{
    long ofs;


    if (dwCtrlLen > hmsg->sqhWrite.clen)
        dwCtrlLen = hmsg->sqhWrite.clen;


    ofs = hmsg->foWrite + HSqd->cbSqhdr + XMSG_SIZE;


static unsigned near _SquishWriteTxt(HMSG hmsg, unsigned fAppend, byte OS2FAR *szTxt,
                                     dword dwTxtLen, dword *pdwOfs)
{
    dword dwMaxWrite;
    long ofs;


    dwMaxWrite = hmsg->sqhWrite.msg_length - XMSG_SIZE - hmsg->sqhWrite.clen;


    if (*pdwOfs != (dword)ofs)
        if (lseek(HSqd->sfd, ofs, SEEK_SET) != ofs)
        {
            msgapierr = MERR_NODS;
            return FALSE;
        }

    if (write(HSqd->sfd, (char *)szTxt, (unsigned)dwMaxWrite) != (int)dwMaxWrite)
    {
        msgapierr = MERR_NODS;
        return FALSE;
    }

    *pdwOfs = (dword)ofs + dwMaxWrite;


static unsigned near _SquishUpdateIndex(HMSG hmsg, PXMSG pxm)
{
    SQIDX sqi;

    if (!SidxGet(HSqd->hix, hmsg->dwMsg, &sqi))
        return FALSE;


    sqi.ofs = hmsg->foWrite;
    sqi.hash = SquishHash(pxm->to);


sword MAPIENTRY SquishWriteMsg(HMSG hmsg, word fAppend, PXMSG pxm, byte OS2FAR *szTxt,
                               dword dwTxtLen, dword dwTxtTotal, dword dwCtrlLen,
                               byte OS2FAR *szCtrl)
{
    dword dwOfs = (dword)-1L;


    if ((sdword)dwCtrlLen < 0)
        dwCtrlLen = 0L;

    if ((sdword)dwTxtTotal < 0)
        dwTxtTotal = 0L;


    if (!hmsg->foWrite)
    {
        unsigned rc;


    if (pxm)
        if (!_SquishWriteXmsg(hmsg, pxm, &dwOfs))
            return -1;

    if (szCtrl)
        if (!_SquishWriteCtrl(hmsg, szCtrl, dwCtrlLen, &dwOfs))
            return -1;

    if (szTxt)
        if (!_SquishWriteTxt(hmsg, fAppend, szTxt, dwTxtLen, &dwOfs))
            return -1;

    hmsg->fWritten = TRUE;


    if (pxm)
        if (!_SquishUpdateIndex(hmsg, pxm))
            return -1;

    return 0;
}
