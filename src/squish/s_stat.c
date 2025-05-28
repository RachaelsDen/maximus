// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_stat.c,v 1.1.1.1 2002/10/01 17:56:42 sdudley Exp $";
#pragma on(unreferenced)

#include "msgapi.h"
#include "prog.h"
#include "squish.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static int fd = -1;


    if ((fd = sopen(config.statfile, O_CREAT | O_WRONLY | O_BINARY | O_APPEND | O_NOINHERIT,
                    SH_DENYNO, S_IREAD | S_IWRITE)) == -1)
    {
        S_LogMsg(cantopen, config.statfile);
        return;
    }


    StatsWriteBlock(TYPE_BEGIN, sizeof(struct _tstamp), 0, NULL);
}



void StatsWriteBlock(word type, word len, word actual_len, void *data)
{
    struct _thdr th;
    struct _tstamp ts;

    if (actual_len == 0)
        actual_len = len;


    th.type = type;
    th.len = len;


void StatsClose(void)
{

void StatsWriteAreas(void)
{
    struct _statlist *sl;
    struct _cfgarea *ar;
    struct _tarea ta;
    struct _tnode tn;


            ar->flag &= ~AFLAG_STATDATA;


            for (sl = ar->statlist, ta.n_nodes = 0; sl; sl = sl->next)
                if (sl->out_msgs)
                    ta.n_nodes++;


            StatsWriteBlock(TYPE_AREA, (word)(sizeof(ta) + sizeof(tn) * ta.n_nodes), sizeof ta,
                            &ta);

                    continue;

                tn.node = sl->node;
                tn.out_msgs = sl->out_msgs;
                tn.out_bytes = sl->out_bytes;

                if (fastwrite(fd, (char *)&tn, sizeof tn) != (int)sizeof tn)
                    S_LogMsg("!Error writing to stats file");


        if (ar->dupes)
        {
            struct _tdupe td;

            (void)strncpy(td.tag, ar->name, AH_TAGLEN);
            td.n_dupes = ar->dupes;
            StatsWriteBlock(TYPE_DUPE, sizeof td, 0, &td);
        }
    }
}
