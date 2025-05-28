// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_editor.c,v 1.1.1.1 2002/10/01 17:52:39 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_chat
#define MAX_LANG_max_bor

#include "m_reply.h"
#include "max_edit.h"
#include "max_msg.h"
#include "prog.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Editor(XMSG *msg, HMSG msgh, long msgnum, char *ctrl_buf, struct _replyp *pr)
{
    struct _css css;

    int ret, useext = FALSE;

    last_maxed = FALSE;

    ChatSaveStatus(&css);
    ChatSetStatus(FALSE, cs_enter_msg);

    logit(usingeditor);

    Puts(GRAY "\n");


    if (prm.hlp_msgentry)
        Display_File(0, NULL, PRM(hlp_msgentry));

    if (*PRM(local_editor))
    {
        if (local || *PRM(local_editor) == '@')
        {
            if (local && mailflag(CFLAGM_LEDITOR))
                useext = TRUE;

            if (!local && mailflag(CFLAGM_EDITOR))
                useext = TRUE;
        }
    }

    if (useext)
        ret = Local_Editor(msg, msgh, msgnum, ctrl_buf, pr);
    else if ((usr.bits2 & BITS2_BORED) || (prm.flags & FLAG_no_magnet))
    {
        Puts(CLEOS);
        ret = Bored(msg, msgh, pr);
    }
    else if ((usr.bits2 & BITS2_BORED) == 0 &&
             (usr.video == GRAPH_TTY || TermWidth() < 79 || TermLength() < 24))
    {
        Puts(CLEOS);
        Puts(req_graph);
        ret = Bored(msg, msgh, pr);
    }
    else
    {
        Puts(CLS);

        inmagnet = last_maxed = TRUE;
        ret = MagnEt(msg, msgh, pr);
        inmagnet = FALSE;
    }

    ChatRestoreStatus(&css);
    logit(outofeditor);

    return ret;
}
