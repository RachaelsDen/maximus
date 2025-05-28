// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_lread.c,v 1.1.1.1 2002/10/01 17:52:46 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "max_msg.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <share.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


void FixLastread(HAREA lsq, word type, dword lastmsg, char *path)
{
    void *where;
    char temp[PATHLEN];

    UMSGID uid;

    int lrfile, size;
    word tempword;

    dword tdword;
    long offset;

    if (!lsq || chkmail_reply)
        return;

    uid = MsgMsgnToUid(lsq, lastmsg);


    if ((lrfile = sopen(temp, O_CREAT | O_RDWR | O_BINARY | O_NOINHERIT, SH_DENYNONE,
                        S_IREAD | S_IWRITE)) == -1)
    {
        cant_open(temp);
        return;
    }

    lseek(lrfile, 0L, SEEK_END);

            if (write(lrfile, (char *)&tdword, size) != size)
            {
                logit(cantwrite, temp);
                close(lrfile);
                return;
            }
    }

    lseek(lrfile, offset, SEEK_SET);


void ScanLastreadPointer(dword *lastmsg)
{
    void *where;
    char temp[PATHLEN];

    UMSGID uid;

    word tempword, size;
    int lrfile;

    if (mah.ma.type & MSGTYPE_SDM)
    {
        sprintf(temp, usr.lastread_ptr ? ps_lastread : ps_lastread_single, MAS(mah, path));

        size = sizeof(word);
        where = &tempword;
    }
    else
    {
        sprintf(temp, sq_lastread, MAS(mah, path));
        size = sizeof(UMSGID);
        where = &uid;
    }

