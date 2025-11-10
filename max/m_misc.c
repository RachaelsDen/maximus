/*
 * Maximus Version 3.02
 * Copyright 1989, 2002 by Lanius Corporation.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_misc.c,v 1.1.1.1 2002/10/01 17:52:46 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_INCL_VARS     /* Include global variable declarations from max_v.h */
#define MAX_INCL_LANGUAGE /* Include language structures and definitions */
#define MAX_INCL_LANGLTH  /* Include english.lth language strings */
#define MAX_LANG_global   /* Global language strings */

#include "max_msg.h"
#include "prog.h"
#include "protod.h"  /* For function declarations */
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

/* Toggle kludge lines on/off */

void Msg_Toggle_Kludges(void)
{
    if (GEPriv(usr.priv, prm.ctla_priv))
        prm.ctla_priv = prm.seenby_priv = (sword)-1;
    else
        prm.ctla_priv = prm.seenby_priv = usr.priv;

    Puts(WHITE);
    Puts(done_ex);
}

/* Mark a message as unreceived */

void Msg_Unreceive(dword last_msg, HMSG hm)
{
    HMSG hmsg;
    XMSG msg;

    if (hm)
        hmsg = hm;
    else if ((hmsg = MsgOpenMsg(sq, MOPEN_RW, last_msg)) == NULL)
    {
        Puts(msgnotavail);
        return;
    }

    if (MsgReadMsg(hmsg, &msg, 0L, 0L, NULL, 0L, NULL) == 0)
    {
        if (!CanSeeMsg(&msg))
        {
            Puts(msgnotavail);
            MsgCloseMsg(hmsg);
            return;
        }

        msg.attr &= ~MSGREAD;
        MsgWriteMsg(hmsg, TRUE, &msg, NULL, 0L, 0L, 0L, NULL);
    }

    if (!hm)
        MsgCloseMsg(hmsg);

    Puts(WHITE);
    Puts(done_ex);
}
