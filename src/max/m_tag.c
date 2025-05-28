// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_tag.c,v 1.1.1.1 2002/10/01 17:52:50 sdudley Exp $";
#pragma on(unreferenced)

#include "max_msg.h"
#include "prog.h"
#include <stdlib.h>
#include <string.h>

int Msg_Tag_Area(char *inp, int do_which)
{
    sword res = -1;
    BARINFO bi;
    char an[MAX_ALEN];

    SetAreaName(an, inp);

    if (!ValidMsgArea(an, NULL, VA_NOVAL | VA_PWD, &bi))
    {
        if (*PRM(areanotexist))
            Display_File(0, NULL, PRM(areanotexist));
        else
            Puts(areadoesntexist);
    }
    else
    {

        if (TagQueryTagList(&mtm, an))
            res = (do_which == TAG_ADD) ? TRUE : TagDeleteTagList(&mtm, an);
        else
            res = (do_which == TAG_DEL) ? TRUE : TagAddTagList(&mtm, an);

        if (res)
        {
            Printf(atag_done, an, TagQueryTagList(&mtm, an) ? blank_str : notag);
        }
        else
        {
            Puts(atag_cant);
        }
        vbuf_flush();
    }
    return res;
}

int TagMoreBreak(char *nonstop)
{
    if (display_line >= (byte)(TermLength() - 1) && (usr.bits2 & BITS2_MORE))
    {
        char inp[PATHLEN];

        for (;;)
        {
            if (*nonstop)
            {
                display_line = 1;
                vbuf_flush();
                return FALSE;
            }

            InputGets(inp, atag_questmore);

            if (*inp == '/' || *inp == '?')
            {
                display_line = 1;
                strcpy(linebuf, inp);
                return TRUE;
            }
            if (*inp == '-')
            {
                strcpy(mtm.pbAreas, "\x01");
                mtm.dwUsed = 0;
                Puts(done_ex);
                continue;
            }

            if (*inp == '=')
            {
                *nonstop = TRUE;
                continue;
            }

            if (*inp == '*')
            {
                strcpy(linebuf, "\r");
                display_line = 1;
                return TRUE;
            }

            if (!*inp)
            {
                display_line = 1;
                return FALSE;
            }

            Msg_Tag_Area(inp, TAG_TOGGLE);
        }
    }
    return FALSE;
}

void Msg_Tag(void)
{
    char inp[PATHLEN];

    RipClear();

    if (usr.help == NOVICE && !*linebuf)
        Puts(atag_help);

    do
    {
        InputGets(inp, atag_quest);

        if (*inp == '/' || *inp == '?')
        {
            ListMsgAreas(NULL, TRUE, FALSE);
            if (!*linebuf)
                Puts(at_equals_tagged);
            continue;
        }
        else if (*inp == '-')
        {
            strcpy(mtm.pbAreas, "\x01");
            mtm.dwUsed = 0;
            Puts(done_ex);
            continue;
        }

        if (!*inp)
            break;

        Msg_Tag_Area(inp, TAG_TOGGLE);
    } while (*inp);
}
