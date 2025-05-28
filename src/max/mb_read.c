// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mb_read.c,v 1.1.1.1 2002/10/01 17:52:17 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_m_browse

#include "m_browse.h"
#include "max_msg.h"
#include "prog.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static int near Read_Get_Option(BROWSE *b);

int Read_Begin(BROWSE *b)
{
    NW(b);
    return 0;
}

int Read_Display(BROWSE *b)
{
    char savearea[MAX_ALEN];
    char *ctrl;

    long clen;

    int save_mlines;
    int ret;

    strcpy(savearea, usr.msg);
    strcpy(usr.msg, MAS(mah, name));

    do
    {
        byte was_no_remote_output = no_remote_output;

        if (hasRIP())
            no_remote_output = TRUE;

        if (hasRIP() || !usr.video || (usr.bits & BITS_FSR) == 0)
        {
            Puts(CLS);
            Printf(br_area_banner, MAS(mah, name), MAS(mah, descript));
        }

        no_remote_output = was_no_remote_output;

        MsgSetCurPos(b->m, 0L);

        save_mlines = menu_lines;
        menu_lines = 1;

        clen = MsgGetCtrlLen(b->m);

        if (clen <= 0)
            ctrl = NULL;
        else if ((ctrl = malloc((int)clen + 5)) != NULL)
        {
            MsgReadMsg(b->m, NULL, 0L, 0L, NULL, clen, ctrl);
            ctrl[(int)clen] = '\0';
        }

        Msg_Display(b->m, &b->msg, usr.bits2 & BITS2_MORE, MAS(mah, name), b->msgn, 1, ctrl, TRUE);

        if (ctrl)
            free(ctrl);

        menu_lines = save_mlines;

        Recd_Msg(b->m, &b->msg, TRUE);


        if (OkToFixLastread(b))
            Lmsg_Set(b, b->msgn);
    } while ((ret = Read_Get_Option(b)) == 2);

    strcpy(usr.msg, savearea);

    return ret;
}

int Read_After(BROWSE *b)
{
    NW(b);
    return 0;
}


static int near MsgIsUnreceivedAttach(BROWSE *b)
{
    int rc;
    long clen;
    char *ctrl;

    rc = 0;

    if ((b->msg.attr & MSGFILE) != 0)
    {
        clen = MsgGetCtrlLen(b->m);

        if (clen <= 0)
            ctrl = NULL;
        else if ((ctrl = malloc((int)clen + 5)) != NULL)
        {
            MsgReadMsg(b->m, NULL, 0L, 0L, NULL, clen, ctrl);
            ctrl[(size_t)clen] = '\0';
        }

        if (Msg_UnreceivedAttach(&b->msg, ctrl, !!(mah.ma.attribs & MA_NET)))
            rc = 1;

        if (ctrl)
            free(ctrl);
    }

    return rc;
}


static void near MsgAttachDownload(BROWSE *b)
{
    long clen;
    char *ctrl;

    clen = MsgGetCtrlLen(b->m);

    if ((clen > 0) && (ctrl = malloc((int)clen + 5)) != NULL)
    {
        int isnetmsg = !!(mah.ma.attribs & MA_NET);

        MsgReadMsg(b->m, NULL, 0L, 0L, NULL, clen, ctrl);
        ctrl[(size_t)clen] = '\0';

        Msg_AttachDownload(&b->msg, ctrl, isnetmsg);

        if (Ask_KillAttach())
            Msg_AttachKill(&b->msg, ctrl, isnetmsg);

        free(ctrl);
    }
}

static int near Read_Get_Option(BROWSE *b)
{
    UMSGID here;
    long savelast, new;
    char msginf[32];
    char temp[32];
    char prompt[PATHLEN * 4];
    char *mkeys = mchk_keys;
    char *nkeys = mchk_nmsgk;
    int ch;

    for (;;)
    {
        WhiteN();

        display_line = display_col = 1;


        if (MsgToThisUser(b->msg.to) && CanAccessMsgCommand(&mah, msg_unreceive, 0))
        {
            strcat(prompt, mchk_unreceive);

            temp[0] = mkeys[4];
            temp[1] = '\0';

            strcat(msginf, temp);
        }


        if ((b->bflag & BROWSE_ACUR) == 0)
        {
            temp[0] = mkeys[2];
            temp[1] = 0;

            strcat(prompt, mchk_nextar);
            strcat(msginf, temp);
        }

        strcat(prompt, mchk_end_prompt);

        ch = toupper(GetListAnswer(msginf, NULL, mchk_nunder, CINPUT_FULLPROMPT, prompt));

        if (ch == toupper(nkeys[0]))
            return 0;
        else if (ch == toupper(nkeys[1]))
            return -1;
        else if (ch == toupper(nkeys[2]))
            return 2;
        else if (ch == toupper(mkeys[2]))
            return 3;
        else if (ch == toupper(mkeys[1]))
        {
            MsgCloseMsg(b->m);
            b->m = NULL;


            if (OkToFixLastread(b))
                Lmsg_Set(b, b->msgn);

            return 0;
        }
        else if (ch == toupper(mkeys[0]))
        {
            chkmail_reply = TRUE;
            savelast = last_msg;
            last_msg = b->msgn;

            here = MsgMsgnToUid(sq, b->msgn);
            Msg_Reply();
            new = MsgUidToMsgn(sq, here, UID_PREV);

            if (new > 0)
                b->msgn = new;

            last_msg = savelast;
            chkmail_reply = FALSE;
        }
        else if (ch == toupper(mkeys[3]))
        {
            Msg_Toggle_Kludges();
            return 2;
        }
        else if (ch == toupper(mkeys[4]))
        {
            Msg_Unreceive(0L, b->m);
            b->msg.attr &= ~MSGREAD;
        }
        else if (ch == toupper(mkeys[5]))
            MsgAttachDownload(b);
    }
}

int Read_End(BROWSE *b)
{
    Lmsg_Update(b);
    return List_End(b);
}
