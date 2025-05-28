// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_save.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)


#include "m_save.h"
#include "m_for.h"
#include "max_edit.h"
#include "max_msg.h"
#include "prog.h"
#include <ctype.h>
#include <io.h>
#include <mem.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef UNIX
#include <errno.h>
#endif

static void near SaveMsgFromUpfile(HMSG msgh, FILE *upfile, long total_len, int local_msg,
                                   PMAH pmah);
static void near SaveMsgFromEditor(HMSG msgh, long total_len, PMAH pmah);

int SaveMsg(XMSG *msg, FILE *upfile, int local_msg, long msgnum, int chg, PMAH pmah, char *msgarea,
            HAREA marea, char *ctrl_buf, char *orig_area, int fSkipCC)
{
    HMSG mh;

    UMSGID lastuid;

    long total_len, save_to, kludge_len;

    int ret, cnt, tlen;
    int fResetFile;
    word found_tear;
    word line;

    char temp[PATHLEN];
    char orig[MAX_OTEAR_LEN];
    char *kludge;

    ret = FALSE;


    lastuid = MsgMsgnToUid(sq, last_msg);



        fseek(upfile, 0L, SEEK_END);
        total_len = ftell(upfile) + 512;
    }
    else
    {
        total_len = 0L;
        found_tear = 0;

        for (line = 1; line <= num_lines; line++)
        {

            Check_For_Origin(&found_tear, screen[line] + 1);

            total_len += strlen(screen[line] + 1);

            if (screen[line][0] == HARD_CR)
                total_len++;
        }

        if (found_tear != 2 && (pmah->ma.attribs & MA_ECHO))
        {
            GenerateOriginLine(orig, pmah);
            total_len += strlen(orig);
        }

        total_len += 10;
    }

    kludge = GenerateMessageKludges(msg, pmah, ctrl_buf);

    if (!kludge)
        kludge_len = 0;
    else
    {

    if (!chg && (msg->attr & MSGFILE) && (pmah->ma.attribs & MA_ATTACH) &&
        AllowAttribute(pmah, MSGKEY_LATTACH))
    {
        msg->attr &= ~MSGFILE;
        fResetFile = TRUE;
    }

    if (MsgWriteMsg(mh, FALSE, msg, temp, tlen, total_len, kludge_len, kludge) != 0)
    {
        if (kludge)
            free(kludge);

        ret = WriteErr(FALSE);
        goto Done;
    }

    if (fResetFile)
        msg->attr |= MSGFILE;

    found_tear = 0;


    if (upfile)
        SaveMsgFromUpfile(mh, upfile, total_len, local_msg, pmah);
    else
        SaveMsgFromEditor(mh, total_len, pmah);


    CleanupAfterSave(chg, msg, save_to, pmah, msgarea, kludge, marea);

    if (kludge)
        free(kludge);

    if (!chg && (msg->attr & MSGFILE) && (pmah->ma.attribs & MA_ATTACH) &&
        AllowAttribute(pmah, MSGKEY_LATTACH))
    {
        Msg_AttachUpload(pmah, sq, msg, MsgMsgnToUid(sq, save_to));
    }

    if (!fSkipCC)
        Handle_Carbon_Copies(save_to, upfile, msg);


    if (upfile == NULL)
        Free_All();

    return ret;
}

static int near WriteErr(int opened)
{
    logit("!Msg%sMsg rc=%d, errno=%d", opened ? "Open" : "Write", msgapierr, errno);

    Printf(errwriting);
    return TRUE;
}

static void near SaveMsgFromUpfile(HMSG msgh, FILE *upfile, long total_len, int local_msg,
                                   PMAH pmah)
{
    char orig[MAX_OTEAR_LEN];
    char temp[PATHLEN * 2 + 5];
    byte *s;

    int first = TRUE;
    int line_len = 0;
    word found_tear = 0;
    int last_char = 0;
    int last_len = 0;
    int last_isblstr = FALSE;
    int was_trimmed = FALSE;
    int is_trimmed;
    unsigned char ch = HARD_CR;
    char c;

    fseek(upfile, 0L, SEEK_SET);

    while (fbgetsc(temp, PATHLEN, upfile, &is_trimmed))
    {
        size_t this_linelen;


        for (s = temp; *s; s++)
        {
                else

        if (first)
            first = FALSE;

            strocpy(temp + 1, temp);


            if (temp[1] > 32 && !last_isblstr && last_len >= 60)
            {

                ch = SOFT_CR;
            }
            else
            {
                *temp = HARD_CR;
                ch = HARD_CR;
            }
        }

        this_linelen = strlen(temp);

        MsgWriteMsg(msgh, TRUE, NULL, temp, this_linelen, total_len, 0L, NULL);

        if (*temp)
            last_char = temp[this_linelen - 1];
        else
            last_char = '\0';

        last_len = this_linelen;
        last_isblstr = isblstr(temp);
        if ((was_trimmed = is_trimmed) == 0)
            line_len = 0;
        else
            line_len += this_linelen;
    }


    strcat(temp, "\r");
    MsgWriteMsg(msgh, TRUE, NULL, temp, strlen(temp), total_len, 0L, NULL);


    c = '\0';
    MsgWriteMsg(msgh, TRUE, NULL, &c, sizeof(char), total_len, 0L, NULL);


        Check_For_Origin(&found_tear, screen[line] + 1);


    if (found_tear != 2 && (pmah->ma.attribs & MA_ECHO))
    {
        GenerateOriginLine(orig, pmah);
        MsgWriteMsg(msgh, TRUE, NULL, orig, strlen(orig), total_len, 0L, NULL);
    }


            while (*p == ' ' || *p == ',' || *p == ';')
                p++;

            if (*p == '\0')
                break;


            if (isdigit(*p) || *p == '.')
            {
                o = addr;

                while (o < addr + ADDR_LEN && (isdigit(*p) || *p == ':' || *p == '/' || *p == '.'))
                {
                    *o++ = *p++;
                }

                *o = '\0';
            }
            else
                *addr = '\0';

            fp->tosq = sq;
            fp->fh = NULL;
            CopyMsgArea(&fp->toar, &mah);
            fp->fmsg = *msg;
            fp->tmsg = *msg;
            *fp->toname = '\0';
            fp->msgnum = MsgUidToMsgn(sq, uid, UID_EXACT);
            fp->bomb = FALSE;
            fp->kill = FALSE;

            strnncpy(fp->tmsg.to, cfancy_str(name), sizeof(fp->tmsg.to) - 1);


            if (*addr == '\0' && (fp->toar.ma.attribs & MA_NET))
                Get_FidoList_Name(&fp->tmsg, addr, PRM(fidouser));


            Msg_Forward(fp);

            gotone = TRUE;
        } while (*p && *name);
    }

    free(fp);
    return (gotone);
}
