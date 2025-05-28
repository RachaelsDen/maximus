// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_updsf.c,v 1.1.1.1 2002/10/01 17:52:51 sdudley Exp $";
#pragma on(unreferenced)

#error This file is no longer used by Maximus


#include "max_msg.h"
#include "old_msg.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Update_Scanfile(int mode, int msgnum, int scanfile)
{
    struct _omsg msg2;
    long scan_pos;
    int sf;

    {
        if ((sf = shopen(scanfile_name, O_RDWR | O_BINARY)) == -1)
            return;
    }

    lseek(sf, (long)sizeof(struct _omsg), SEEK_SET);


            {
                *msg2.to = '\0';
                *msg2.from = '\0';
                *msg2.subj = '\0';
            }

            lseek(sf, -(long)sizeof(struct _omsg), SEEK_CUR);
            write(sf, (char *)&msg2, sizeof(struct _omsg));
            break;
        }
    }

