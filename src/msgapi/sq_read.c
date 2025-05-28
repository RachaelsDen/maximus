// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sq_read.c,v 1.2 2003/06/05 22:54:50 wesgarland Exp $";
#pragma on(unreferenced)

#define MSGAPI_HANDLERS
#define MSGAPI_NO_OLD_TYPES

#include "api_sq.h"
#include "apidebug.h"
#include "msgapi.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>


    *pdwOfs = (dword)ofs + (dword)XMSG_SIZE;


    if (pxm->attr & MSGUID)
    {
        hmsg->uidUs = pxm->umsgid;
        pxm->attr &= ~MSGUID;
        pxm->umsgid = 0L;
    }

    return TRUE;
}


    if (*pdwOfs != (dword)ofs)
        if (lseek(HSqd->sfd, ofs, SEEK_SET) != ofs)
        {
            msgapierr = MERR_BADF;
            return FALSE;
        }

    if (read(HSqd->sfd, (char *)szCtrl, uMaxLen) != (int)uMaxLen)
    {
        *szCtrl = 0;
        msgapierr = MERR_BADF;
        return FALSE;
    }


static dword near _SquishReadTxt(HMSG hmsg, byte OS2FAR *szTxt, dword dwTxtLen, dword *pdwOfs)
{

    unsigned uMaxLen = (unsigned)(hmsg->sqhRead.msg_length - hmsg->sqhRead.clen - XMSG_SIZE);


    ofs += (long)hmsg->cur_pos;


    uMaxLen -= (unsigned)hmsg->cur_pos;
    uMaxLen = min(uMaxLen, (unsigned)dwTxtLen);


    hmsg->cur_pos += (dword)uMaxLen;

    return (dword)uMaxLen;
}



    if (!dwTxtLen)
        szTxt = NULL;

    if (!dwCtrlLen)
        szCtrl = NULL;


    if (pxm)
        fOkay = _SquishReadXmsg(hmsg, pxm, &dwSeekOfs);

    if (fOkay && szCtrl)
        fOkay = _SquishReadCtrl(hmsg, szCtrl, dwCtrlLen, &dwSeekOfs);

    if (fOkay && szTxt)
    {
        hmsg->cur_pos = dwOfs;

        if ((dwGot = _SquishReadTxt(hmsg, szTxt, dwTxtLen, &dwSeekOfs)) == (dword)-1L)
            fOkay = FALSE;
    }


    return fOkay ? dwGot : (dword)-1L;
}
