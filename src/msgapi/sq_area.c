// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sq_area.c,v 1.2 2003/06/05 22:54:50 wesgarland Exp $";
#pragma on(unreferenced)

#define MSGAPI_HANDLERS
#define MSGAPI_NO_OLD_TYPES

#include "api_sq.h"
#include "apidebug.h"
#include "msgapi.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


unsigned _SquishCloseOpenAreas(void)
{
#ifdef OS_2
    static char szDoneCloseMsg[] = "MsgAPI is done closing areas.\r\n";
#endif

    HAREA ha, haNext;


static struct _apifuncs sq_funcs = {
    SquishCloseArea,  SquishOpenMsg,   SquishCloseMsg,     SquishReadMsg,      SquishWriteMsg,
    SquishKillMsg,    SquishLock,      SquishUnlock,       SquishSetCurPos,    SquishGetCurPos,
    SquishMsgnToUid,  SquishUidToMsgn, SquishGetHighWater, SquishSetHighWater, SquishGetTextLen,
    SquishGetCtrlLen, SquishGetNextUid};


static unsigned near _SquishUnlinkBaseFiles(byte OS2FAR *szName)
{
    char szFile[PATHLEN];
    unsigned rc = TRUE;

    (void)strcpy(szFile, szName);
    (void)strcat(szFile, dot_sqd);

    if (unlink(szFile) != 0)
        rc = FALSE;

    (void)strcpy(szFile, szName);
    (void)strcat(szFile, dot_sqi);

    if (unlink(szFile) != 0)
        rc = FALSE;

    return rc;
}


static unsigned near _SquishValidateBaseHeader(SQBASE *psqb)
{
    if (psqb->num_msg > psqb->high_msg || psqb->num_msg > psqb->uid + 1 ||
        psqb->high_msg > psqb->uid + 1 || psqb->num_msg > 1000000L ||
        psqb->num_msg != psqb->high_msg || psqb->len < sizeof(SQBASE) || psqb->len >= 1024 ||
        psqb->begin_frame > psqb->end_frame || psqb->last_frame > psqb->end_frame ||
        psqb->free_frame > psqb->end_frame || psqb->last_free_frame > psqb->end_frame ||
        psqb->end_frame == 0)
    {
        msgapierr = MERR_BADF;
        return FALSE;
    }

    return TRUE;
}


unsigned _SquishCopyDataToBase(HAREA ha, SQBASE *psqb)
{
    (void)memset(psqb, 0, sizeof(SQBASE));

    psqb->len = Sqd->cbSqbase;
    psqb->sz_sqhdr = Sqd->cbSqhdr;
    psqb->skip_msg = Sqd->wSkipMsg;
    psqb->max_msg = Sqd->dwMaxMsg;
    psqb->keep_days = Sqd->wMaxDays;
    psqb->high_water = Sqd->dwHighWater;
    psqb->uid = Sqd->uidNext;
    psqb->begin_frame = Sqd->foFirst;
    psqb->last_frame = Sqd->foLast;
    psqb->free_frame = Sqd->foFree;
    psqb->last_free_frame = Sqd->foLastFree;
    psqb->end_frame = Sqd->foEnd;

    psqb->num_msg = ha->num_msg;
    psqb->high_msg = ha->high_msg;
    psqb->high_water = ha->high_water;

    return TRUE;
}


    Sqd->foNext = Sqd->foFirst;
    Sqd->foCur = NULL_FRAME;
    Sqd->foPrev = NULL_FRAME;
    ha->cur_msg = 0;
    ha->sz_xmsg = XMSG_SIZE;
    return TRUE;
}


static unsigned near _SquishCreateNewBase(HAREA ha, byte OS2FAR *szName)
{

    if (!_SquishOpenBaseFiles(ha, szName, O_CREAT | O_TRUNC))
        return FALSE;

    if (!_SquishFillBaseHeader(&sqb, szName) || !_SquishWriteBaseHeader(ha, &sqb) ||
        !_SquishCopyBaseToData(ha, &sqb) || !_SquishSetBaseDefaults(ha))
    {

static unsigned near _SquishOpenExistingBase(HAREA ha, byte OS2FAR *szName)
{

    if (!_SquishOpenBaseFiles(ha, szName, 0))
        return FALSE;

    if (!_SquishReadBaseHeader(ha, &sqb) || !_SquishValidateBaseHeader(&sqb) ||
        !_SquishCopyBaseToData(ha, &sqb) || !_SquishSetBaseDefaults(ha))
    {
        _SquishCloseBaseFiles(ha);
        return FALSE;
    }

    return TRUE;
}


    if ((ha = (HAREA)palloc(sizeof(*ha))) == NULL)
        return NULL;

    (void)memset(ha, 0, sizeof *ha);

    ha->id = MSGAPI_ID;
    ha->len = sizeof(struct _msgapi);
    ha->type = wType & ~MSGTYPE_ECHO;
    ha->isecho = (byte) !!(wType & MSGTYPE_ECHO);

    return ha;
}


    if (!szName)
    {
        msgapierr = MERR_BADA;
        return NULL;
    }


    if ((ha->apidata = (void *)palloc(sizeof(struct _sqdata))) == NULL)
    {
        pfree(ha);
        return NULL;
    }

    memset(ha->apidata, 0, sizeof(struct _sqdata));


    *ha->api = sq_funcs;


    msgapierr = 0;

    if (wMode == MSGAREA_NORMAL || wMode == MSGAREA_CRIFNEC)
        fOpened = _SquishOpenExistingBase(ha, szName);
    else
        msgapierr = MERR_NOENT;


    if (fOpened)
    {

    return ha;
}


    for (hm = Sqd->hmsgOpen; hm; hm = hmNext)
    {
        hmNext = hm->hmsgNext;

        if (SquishCloseMsg(hm) == -1)
        {
            msgapierr = MERR_EOPEN;
            return FALSE;
        }
    }

    return TRUE;
}

static unsigned near _SquishRemoveAreaList(HAREA haThis)
{
    HAREA ha, haNext;

    if (!haOpen)
    {
        msgapierr = MERR_BADA;
        return FALSE;
    }


    for (ha = haOpen; ha; ha = haNext)
    {
        haNext = Sqd->haNext;

        if (haNext == haThis)
        {
            Sqd->haNext = ((SQDATA *)(haThis->apidata))->haNext;
            return TRUE;
        }
    }

    msgapierr = MERR_BADA;
    return FALSE;
}


    if (!_SquishCloseAreaMsgs(ha))
        return -1;


    if (Sqd->fLockFunc)
    {
        if (Sqd->fLocked)
            Sqd->fLocked = 1;

        Sqd->fLockFunc = 1;

        SquishUnlock(ha);
    }

    (void)_SquishCloseIndex(Sqd->hix);


    (void)_SquishRemoveAreaList(ha);


    ha->id = 0;

    pfree(ha->api);
    pfree(ha->apidata);
    pfree(ha);

    return 0;
}

