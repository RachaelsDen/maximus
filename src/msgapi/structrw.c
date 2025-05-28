// SPDX-License-Identifier: GPL-2.0-or-later

#include "msgapi.h"
#include "typedefs.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



#undef __LITTLE_ENDIAN__
#undef __BIG_ENDIAN__

#if defined(BIG_ENDIAN)
#define __BIG_ENDIAN__
#elif defined(LITTLE_ENDIAN)
#define __LITTLE_ENDIAN__
#endif

#include "putword.c"
#include "putword.h"

int read_xmsg(int handle, XMSG *pxmsg)
{
    byte buf[XMSG_SIZE], *pbuf = buf;
    word rawdate, rawtime;
    int i;

    if (farread(handle, (byte far *)buf, XMSG_SIZE) != XMSG_SIZE)
    {
        return 0;
    }

    memmove(pxmsg->from, pbuf, XMSG_FROM_SIZE);
    pbuf += XMSG_FROM_SIZE;

    memmove(pxmsg->subj, pbuf, XMSG_SUBJ_SIZE);
    pbuf += XMSG_SUBJ_SIZE;

    pxmsg->orig.zone = get_word(pbuf);
    pbuf += 2;
    pxmsg->orig.net = get_word(pbuf);
    pbuf += 2;
    pxmsg->orig.node = get_word(pbuf);
    pbuf += 2;
    pxmsg->orig.point = get_word(pbuf);
    pbuf += 2;

    rawdate = get_word(pbuf);
    pbuf += 2;
    rawtime = get_word(pbuf);
    pbuf += 2;
    pxmsg->date_written.date.da = rawdate & 31;
    pxmsg->date_written.date.mo = (rawdate >> 5) & 15;
    pxmsg->date_written.date.yr = (rawdate >> 9) & 127;
    pxmsg->date_written.time.ss = rawtime & 31;
    pxmsg->date_written.time.mm = (rawtime >> 5) & 63;
    pxmsg->date_written.time.hh = (rawtime >> 11) & 31;

    pxmsg->utc_ofs = get_word(pbuf);
    pbuf += 2;

    for (i = 0; i < MAX_REPLY; i++)
    {
        pxmsg->replies[i] = get_dword(pbuf);
        pbuf += 4;
    }

    memmove(pxmsg->__ftsc_date, pbuf, 20);
    pbuf += 20;

    assert(pbuf - buf == XMSG_SIZE);
    return 1;
}

int write_xmsg(int handle, XMSG *pxmsg)
{
    byte buf[XMSG_SIZE], *pbuf = buf;
    word rawdate, rawtime;
    int i;

    memmove(pbuf, pxmsg->from, XMSG_FROM_SIZE);
    pbuf += XMSG_FROM_SIZE;

    memmove(pbuf, pxmsg->subj, XMSG_SUBJ_SIZE);
    pbuf += XMSG_SUBJ_SIZE;

    put_word(pbuf, pxmsg->dest.zone);
    pbuf += 2;
    put_word(pbuf, pxmsg->dest.net);
    pbuf += 2;
    put_word(pbuf, pxmsg->dest.node);
    pbuf += 2;
    put_word(pbuf, pxmsg->dest.point);
    pbuf += 2;

    rawdate = rawtime = 0;

    rawdate |= (((word)pxmsg->date_arrived.date.da) & 31);
    rawdate |= (((word)pxmsg->date_arrived.date.mo) & 15) << 5;
    rawdate |= (((word)pxmsg->date_arrived.date.yr) & 127) << 9;

    rawtime |= (((word)pxmsg->date_arrived.time.ss) & 31);
    rawtime |= (((word)pxmsg->date_arrived.time.mm) & 63) << 5;
    rawtime |= (((word)pxmsg->date_arrived.time.hh) & 31) << 11;

    put_word(pbuf, rawdate);
    pbuf += 2;
    put_word(pbuf, rawtime);
    pbuf += 2;
    put_dword(pbuf, pxmsg->replyto);
    pbuf += 4;

    put_dword(pbuf, pxmsg->umsgid);
    pbuf += 4;

