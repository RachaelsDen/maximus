// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mb_qwkup.c,v 1.2 2003/06/04 23:46:22 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_f_area
#define MAX_LANG_m_browse
#define MAX_LANG_max_chat
#define MAX_LANG_max_main

#include "mb_qwkup.h"
#include "arcmatch.h"
#include "max_file.h"
#include "max_msg.h"
#include "prog.h"
#include "qwk.h"
#include "trackc.h"
#include "trackm.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


                okay = TRUE;

                if (Decompress_REP(fname) == -1)
                {
                    Printf(err_decompr_rep, PRM(olr_name));
                    okay = FALSE;
                }
                else
                {
                    if (Toss_QWK_Packet(msg_name) == -1)
                    {
                        Printf(err_toss_qwk, msg_name);
                        okay = FALSE;
                    }

                    unlink(msg_name);
                }


                if (!local || okay)
                    unlink(fname);
            }

            Write_Kludge_File(&akh, &akd);
            free(akd);
        }

        free(msg_name);
    }

    Clean_QWK_Directory(TRUE);
    free(qwk_path);

    Free_Filenames_Buffer(0);
    restore_tag_list(NULL, FALSE);
}

static int near Receive_REP(char *name)
{
    char temp[PATHLEN];
    struct _css css;
    sword protocol;
    long ul_start_time;
    sword fn;

    if (!local && File_Get_Protocol(&protocol, FALSE, TRUE) == -1)
        return -1;

    ChatSaveStatus(&css);
    ChatSetStatus(FALSE, cs_file_xfer);


    ul_start_time = time(NULL);


        sf2 = prm.flags2;
        prm.flags2 &= ~(FLAG2_CHECKDUPE | FLAG2_CHECKEXT);

        Free_Filenames_Buffer(0);

        if (!IsBatch(protocol))
            AddFileEntry(temp, 0, 0);

        File_Get_Files(protocol, NULL, qwk_path);

        prm.flags2 = sf2;

        for (fn = 1; GetFileEntry(fn, &fent); fn++)
        {
            sprintf(name, ss, qwk_path, fent.szName);
            unlink(name);

#ifdef TEST_VER
            logit("@Deleting %s", name);
#endif
        }

        if (GetFileEntry(0, &fent))
        {
            strcpy(name, qwk_path);
            strcat(name, fent.szName);
        }
        else
            *name = '\0';
    }


    if ((fd = open(rep_name, O_RDONLY | O_BINARY | O_NOINHERIT)) == -1)
        return -1;

    for (ai = ari; ai; ai = ai->next)
        if (MatchArcType(fd, ai))
            break;

    close(fd);

    if (!ai)
        ai = ari;

    if (!ai)
    {
        Puts(unknown_compr);
        ret = -1;
    }
    else
    {
        Form_Archiver_Cmd(rep_name, msg_name, cmd, ai->extract);


            if ((fd = sopen(qwk_busy, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_DENYNO,
                            S_IREAD | S_IWRITE)) != -1)
                close(fd);

            ret = Outside(NULL, NULL, OUTSIDE_RUN, cmd, FALSE, CTL_NONE, 0, NULL);

            sprintf(temp, ss, qwk_path, msg_name);


static int near Toss_QWK_Packet(char *name)
{
    struct _qmhdr *qh;
    XMSG msg;

    char *block;

    word msgn;
    int qfd, ret;

    ret = 0;

    upper_fn(name);

    Printf(tossing_rep_packet, No_Path(name));


    if ((qfd = shopen(name, O_RDONLY | O_BINARY | O_NOINHERIT)) == -1)
    {
        free(block);
        return -1;
    }

    qh = (struct _qmhdr *)block;


        for (msgn = 1; read(qfd, (char *)block, QWK_RECSIZE) == QWK_RECSIZE; msgn++)
        {
            QWK_To_Xmsg(qh = (struct _qmhdr *)block, &msg, msgn);

            if (!Toss_QWK_Message(qh, &msg, qfd, block))
                lseek(qfd, (atoi(qh->len) - 1) * QWK_RECSIZE, SEEK_CUR);
        }
    }

    close(qfd);
    free(block);

    return ret;
}


static void near QWK_To_Xmsg(struct _qmhdr *qh, XMSG *msg, word msgn)
{
    char date[40];
    SCOMBO now, *d;
    int year;

    Blank_Msg(msg);


    memmove(msg->subj, qh->subj, sizeof(qh->subj));
    msg->subj[sizeof(qh->subj) - 1] = '\0';

    if (all_caps(fix_basic_crap(msg->subj)))
        cfancy_str(msg->subj);

    if (isdigit(*qh->replyto))
        msg->replyto = atol(qh->replyto);

        d->msg_st.date.mo > 12 || d->msg_st.date.da > 31 || d->msg_st.time.ss > 59 ||
        d->msg_st.time.mm > 59 || d->msg_st.time.hh > 23)
    {
        char *lm = log_qwk_bad_date;



    msg->date_written.time.ss = ((msgn - 1) % 30);


    if (qh->status == '*' || qh->status == '+')
        msg->attr |= MSGPRIVATE;
}


    *reply_kludge = 0;


    if (!rep_mn || (hmsg = MsgOpenMsg(sq, MOPEN_RW, rep_mn)) == NULL)
        return;


        MsgReadMsg(hmsg, &xmsg, 0, 0, NULL, ctrl_len, ctrl_buf);


            strnncpy(reply_kludge, rep, PATHLEN);
            memmove(reply_kludge, "REPLY", 5);
            MsgFreeCtrlToken(rep);
        }

        free(ctrl_buf);
    }

    MsgCloseMsg(hmsg);
}


    if (mah.ma.type & MSGTYPE_SDM)
        return;


    MsgReadMsg(hmsg, &xmsg, 0, 0, NULL, 0L, NULL);


    if (i < MAX_REPLY)
        MsgWriteMsg(hmsg, FALSE, &xmsg, NULL, 0, 0, 0, NULL);

    MsgCloseMsg(hmsg);
}



    if (qh->conf == 0 || qh->conf == ' ')
        qh->conf = atoi(qh->msgn);


    tossto = qh->conf - 1;


    if (qh->msgstat == QWK_KILLED || eqstri(msg->to, cprog_name))
        return FALSE;


    strcpy(aname, (tossto >= akh.num_areas) ? qmark : (char *)(akd[tossto].name));

    *pwTossTo = tossto;
    return TRUE;
}


static int near QWKGetValidArea(PXMSG msg, char *aname, word tossto)
{
    BARINFO bi;
    MAH ma;
    int rc = TRUE;

    memset(&ma, 0, sizeof ma);

    while (eqstri(aname, qmark) || !ReadMsgArea(ham, aname, &ma) ||
           !ValidMsgArea(NULL, &ma, VA_VAL | VA_PWD, &bi) || !PopPushMsgArea(aname, &bi) ||
           ((mah.ma.attribs & MA_READONLY) && !mailflag(CFLAGM_RDONLYOK)) ||
           !CanAccessMsgCommand(&mah, msg_upload, 0))
    {
        Printf(qwk_invalid_area, msg->to, msg->subj);

        InputGets(aname, which_area);

    }


static void near QWKFixHeader(PXMSG msg, struct _qmhdr *qh)
{

    if (mah.ma.attribs & MA_REAL)
        strcpy(msg->from, usr.name);
    else if ((mah.ma.attribs & MA_ALIAS) && *usr.alias)
        strcpy(msg->from, usr.alias);
    else
        strcpy(msg->from, usrname);

    if ((mah.ma.attribs & MA_ANON) && *qh->from != ' ')
    {
        memmove(msg->from, qh->from, sizeof(qh->from));
        msg->from[sizeof(qh->from) - 1] = '\0';

        if (all_caps(fix_basic_crap(msg->from)))
            cfancy_str(msg->from);
    }

    msg->orig = mah.ma.primary;


    Printf(qwk_max_area, MAS(mah, name));
    vbuf_flush();
}



    QWKFixHeader(msg, qh);


    tlen = (msg_blocks + 1) * QWK_RECSIZE + strlen(orig) + 1;


    QWKGetMsgid(sq, msg->replyto, reply_kludge);
    *orig_msgid = '\0';
    kludge = GenerateMessageKludges(msg, &mah, *reply_kludge ? reply_kludge : NULL);


        if (bytes_remain)
        {
            if ((got = read(qfd, (char *)endblock, min(endbuf - endblock, bytes_remain))) > 0)
            {
                endblock += got;
                bytes_remain -= got;
            }
        }

        end1buf = block + QWK_RECSIZE;


            for (p = (byte *)block; p < (byte *)endblock; p++)
                if (*p == '\0')
                    *p = ' ';


            if (!bytes_remain)
                for (p = (byte *)endblock - 1; p >= (byte *)block && *p == ' '; p--)
                    *p = '\0';


            for (p = (byte *)block; *p && p < (byte *)endblock; p++)
            {
                if (*p == 0x0d)
                    continue;
                else if (*p == QWK_EOL)
                    *p = 0x0d;
                else if (*p < ' ')
                    *p = ' ';
                else
                {
                    if ((mah.ma.attribs & MA_HIBIT) == 0)
                        *p = nohibit[*p];
                }
            }


            p = block;


                if ((mah.ma.attribs & MA_NET) && tolower(p[0]) == 't' && tolower(p[1]) == 'o' &&
                    tolower(p[2]) == ':')
                {

                    while (p < (byte *)(block + QWK_RECSIZE) && *p == ' ')
                        p++;

                    if (isdigit(*p))
                        MaxParseNN(p, &msg->dest);

                    while (p < (byte *)(block + QWK_RECSIZE) && *p != '\r')
                        p++;


                if (MsgWriteMsg(msgh, FALSE, msg, NULL, 0L, tlen, strlen(kludge) + 1, kludge) < 0)
                {
                    rc = FALSE;
                    break;
                }
            }


            len_p = strlen(p);
            end = p + len_p;


            while ((actinfo = strstr(actinfo, "^!> ")) != NULL && actinfo < end1buf)
            {
                char *lastr, *nextr;


                TrackProcessACInfo(actinfo, &qti);

                *actinfo = 0;


                if ((nextr = strchr(actinfo + 1, '\r')) != NULL)
                {
                    int len;


                    len = ++nextr - lastr;
                    memmove(lastr, nextr, endblock - nextr + 1);

                    endblock -= len;
                    end -= len;
                    len_p -= len;
                    end1buf -= len;
                }
            }
#endif


    MsgWriteMsg(msgh, TRUE, NULL, orig, strlen(orig) + 1, tlen, 0L, NULL);
    MsgCloseMsg(msgh);


    QWKFixLinks(sq, MsgGetHighMsg(sq), msg->replyto);

#ifdef MAX_TRACKER

    if (TrackQWKUpdateTracking(&qti))
    {
        MsgKillMsg(sq, MsgGetHighMsg(sq));
        *pfUpdateStatus = TRUE;
    }

    vbuf_flush();

#endif

    *pkludge = kludge;

    return rc;
}


    msg_blocks = atoi(qh->len);


    if (!QWKRetrieveAreaFromPkt(msg, qh, aname, &tossto))
        return FALSE;


    if (!PushMsgArea(usr.msg, 0))
    {
        AreaError(msgapierr);
        Puts(inval_cur_msg);
        return FALSE;
    }

    if (!QWKGetValidArea(msg, aname, tossto) ||
        !QWKTossMsgBody(msg, qh, msg_blocks, qfd, block, &kludges, &fUpdateStatus))
    {
        if (kludges)
            free(kludges);


    if (!fUpdateStatus)
    {
        logit(log_qwk_msg_to, msg->to, MAS(mah, name), (long)MsgGetHighMsg(sq));


    PopMsgArea();
    return TRUE;
}


static char *near fix_basic_crap(char *str)
{
    char *s = str + strlen(str) - 1;

    while (s >= str && *s == ' ')
        *s-- = '\0';

    return str;
}

static int near all_caps(char *s)
{
    char *p;

    for (p = s; *p;)
        if (islower(*p++))
            return FALSE;

    return TRUE;
}
