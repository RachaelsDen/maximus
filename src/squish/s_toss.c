// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_toss.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#include "s_toss.h"
#include "arcmatch.h"
#include "max.h"
#include "msgapi.h"
#include "prog.h"
#include "s_dupe.h"
#include "squish.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#ifdef UNIX
#include <errno.h>
#endif

#ifndef __TURBOC__
#include <stddef.h>
#endif

static char msgs_name[] = "max_msgs.dat";
char t_area[] = "AREA";

static char comment[80] = "";
static char last_comment[80] = "";

static struct _partial part, resume;
static dword toss_cnt;
static long nmsg_skipped = 0L;

#ifdef DJ
extern FILE *dj;
#endif


    if (!last_max && (config.flag & FLAG_TOSSBAD))
        TossBadMsgs(config.badmsgs);


    if (*resume.pktname)
    {
        Zero_Statistics();
        S_LogMsg("#Tossing messages from resumed packet");
        Toss_Pkt(resume.pktname, resume.tflag);
    }


    for (tp = config.tpath; tp && !erl_max; tp = tp->next)
        if ((tp->flag & TFLAG_NOPKT) == 0)
            Toss_Packet_Sequence(tp->path, tp->flag);


    if (!erl_max)
        Toss_Packet_Sequence(".", 0);


    DupeFlushBuffer();

    secs = time(NULL) - start;

    if (secs == 0)
        secs = 1;

    if (!erl_max)
        ReportSpeed(secs);

    if (config.flag & FLAG_ONEPASS)
    {
        Flush_Outbuf();
        Free_Outbuf();
    }

    (void)printf("\n");

    Free_Buffer();
    Write_Echotoss(echotoss);
    free(talist);
}


static void near TossArchives(struct _tosspath *tp)
{
    struct _plist *plist, *pl, *plar, *plnext, *plp;
    extern char *arcm_exts[];
    char fname[PATHLEN];
    FFIND *ff;
    char **p;
    int n_pl;


    for (p = arcm_exts; *p; p++)
    {
        (void)sprintf(fname, "%s" PATH_DELIMS "*%s?", tp->path, *p);

        if ((ff = FindOpen(fname, 0)) != NULL)
        {
            do
            {
                pl = smalloc(sizeof(*pl));
                pl->name = sstrdup(ff->szName);
                pl->ldate = ff->scWdate;
                pl->next = plist;
                plist = pl;
                n_pl++;
            } while (FindNext(ff) == 0);

            FindClose(ff);
        }
    }


    plar = smalloc(sizeof(struct _plist) * n_pl);

    for (plp = plar, pl = plist; pl; plnext = pl->next, free(pl), pl = plnext)
        *plp++ = *pl;

    qsort(plar, n_pl, sizeof(struct _plist), plcomp);

    for (pl = plar; n_pl-- && !erl_max; pl++)
    {
        sprintf(fname, "%s" PATH_DELIMS "%s", tp->path, pl->name);

        if (Decompress_Archive(fname, "*.pkt") != 0)
        {
            char ren[PATHLEN];
            char final[PATHLEN];

            (void)unlink(fname);

            if ((config.flag & FLAG_BATCHXA) == 0)
                Toss_Packet_Sequence(".", tp->flag);
        }
    }

    free(plar);
}


static void near ReadMaxMsgs(char *tosslog)
{
    int fd;
    FILE *tl;
    char temp[PATHLEN];


        (void)memset(&resume, '\0', sizeof(resume));
        return;
    }

    if ((fd = sopen(msgs_name, O_RDONLY | O_BINARY, SH_DENYNO, S_IREAD | S_IWRITE)) == -1)
        S_LogMsg(cantopen, msgs_name);
    else
    {
        if (read(fd, (char *)&resume, sizeof(part)) != (int)sizeof(part))
            S_LogMsg(cantread, msgs_name);

        (void)close(fd);
        (void)unlink(msgs_name);
    }


    if ((tl = shfopen(tosslog, "r", O_RDONLY)) == NULL)
        return;

    while (fgets(temp, PATHLEN, tl))
    {
        struct _cfgarea search, *found;

        (void)Strip_Trailing(temp, '\n');
        search.name = temp;

        if ((found = SkipSearchList(config.area, &search)) != NULL)
            found->flag |= AFLAG_TOSSEDTO;
    }

    (void)fclose(tl);
    (void)unlink(tosslog);
}


    part.long_packet = resume.long_packet;

    if ((fd = sopen(msgs_name, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_DENYNO,
                    S_IREAD | S_IWRITE)) == -1)
        S_LogMsg(cantopen, msgs_name);
    else
    {
        (void)write(fd, (char *)&part, sizeof(part));
        (void)close(fd);
    }
}


        for (ar = SkipFirst(config.area); ar; ar = SkipNext(config.area))
        {
            if ((ar->flag & AFLAG_TOSSEDTO) && *ar->name && !NetmailArea(ar) && !BadmsgsArea(ar) &&
                !DupesArea(ar))
            {
                (void)fprintf(etf, "%s\n", ar->name);
            }
        }

        (void)fclose(etf);

        if (fsize(echotoss) == 0)
            (void)unlink(echotoss);
    }
}

#endif

    if ((fd = sopen(arcname, O_RDONLY | O_BINARY, SH_DENYNO, S_IREAD | S_IWRITE)) == -1)
        return -1;

    (void)printf("\nDecompressing ");

    for (ai = config.arc; ai; ai = ai->next)
        if (MatchArcType(fd, ai))
        {
            (void)printf("%s ", ai->arcname);
            break;
        }

    if (ai == NULL)
    {
        (void)printf("unknown ");
        ai = config.arc;
    }

    (void)printf("bundle %s...\n\n", arcname);

    (void)close(fd);

    S_LogMsg("*Un%sing %s", ai->arcname, arcname);

#ifdef DJ
    fprintf(dj, "**** Decompressing %s\n", arcname);
#endif

    Form_Archiver_Cmd(arcname, get, cmd, ai->extract);

    arcret = CallExtern(cmd, TRUE);

    if (arcret == 0 && !fexist("*.pkt"))
    {
        S_LogMsg("!No packets found after calling archiver!");
        arcret = -1;
        errno = 0;
    }

    if (arcret == 0)
        err = 0;
    else
    {
        HandleArcRet(arcret, cmd);
        err = -1;
    }

    return err;
}


    for (ret = 0, n_pl = 0, plist = NULL; ret == 0; ret = FindNext(ff))
    {
        pl = smalloc(sizeof(struct _plist));


        pl->ldate = ff->scWdate;


    plar = smalloc(sizeof(struct _plist) * n_pl);


    qsort(plar, n_pl, sizeof(struct _plist), plcomp);


static void near RenamePkt(char *pktname, char *ext, char *out)
{
    char *s;


static void near BadPacket(char *pktname)
{
    char szFinal[PATHLEN];

#ifndef UNIX
    RenamePkt(pktname, ".BAD", szFinal);
#else
    RenamePkt(pktname, ".bad", szFinal);
#endif

    S_LogMsg("!Bad packet:  renamed to %s", szFinal);
}


static void near Tossing_It(char *name)
{
    char *p;

    if ((p = strrchr(name, '/')) != NULL)
        name = p + 1;

    if ((p = strrchr(name, '\\')) != NULL)
        name = p + 1;

    if ((p = strrchr(name, ':')) != NULL)
        name = p + 1;

    (void)printf("Toss %12.12s: ", name);
}


    (void)sprintf(temp, "(%hu:%hd/%hd", zone, net, node);

    if (point)
        (void)sprintf(temp + strlen(temp), ".%hu", point);

    (void)strcat(temp, ")");

    (void)printf("%-22s", temp);
}

#define NUMPROD (sizeof(products) / sizeof(products[0]))


static char *near ProdCode(byte prod)
{
    static char pnum[3];

    if (prod < NUMPROD && products[prod])
        return products[prod];
    else
    {
        (void)sprintf(pnum, "%02hx", (word)prod);
        return pnum;
    }
}


static word near PktNameEqual(char *p1, char *p2)
{
    char *n1, *n2;

    n1 = strrstr(p1, "/\\:");

    if (n1)
        n1++;
    else
        n1 = p1;

    n2 = strrstr(p2, "/\\:");

    if (n2)
        n2++;
    else
        n2 = p2;

    return (eqstri(n1, n2));
}


    (void)strcpy(part.pktname, in.pktname);
    part.tflag = tflag;

    if ((size = (unsigned long)lseek(in.pktfile, 0L, SEEK_END)) == 0L)
        (void)printf("Deleting null packet %s", in.pktname);
    else
    {
        (void)lseek(in.pktfile, 0L, SEEK_SET);

        Tossing_It(fancy_fn(in.pktname));

        if (fastread(in.pktfile, (char *)&in.pkt, (unsigned)sizeof(struct _pkthdr)) !=
                (int)sizeof(struct _pkthdr) ||
            in.pkt.ver != PKTVER)
        {
            S_LogMsg("!Invalid packet: %s", in.pktname);
            bad_packet = TRUE;
        }

        s = strrchr(in.pktname, PATH_DELIM);

        if (s)
            s++;
        else
            s = in.pktname;

        if (!bad_packet)
        {
            (void)Adjust_Pkt_Header(&in.pkt);


            WhoFrom(s, &in);

            if (!PktNameEqual(in.pktname, resume.pktname))
                SetPktOfs((long)sizeof(struct _pkthdr));
            else
            {

            if (config.flag & FLAG_STATS)
            {
                struct _tpkt tp;
                char *p;


                if ((p = strrstr(in.pktname, "/\\")) != NULL)
                    p++;
                else
                    p = in.pktname;

                (void)strncpy(tp.pktname, p, 13);
                tp.pktname[13] = '\0';

                tp.size = size;
                (void)Get_Dos_Date(&tp.proc_time);


                    if (got == 0 && !TossOneMsg(&in, FALSE, tflag))
                    {
                        bad_packet = TRUE;
                        break;
                    }

                    if (config.max_msgs && toss_cnt >= config.max_msgs)
                        break;
                }

                if (config.max_msgs && toss_cnt >= config.max_msgs)
                    erl_max = TRUE;
            }
        }
    }

    (void)close(in.pktfile);

    NW(tossed);

    (void)printf("\n");

    if (bad_packet)
        BadPacket(in.pktname);
    else if (erl_max)
    {

        WriteMaxMsgs();
    }
    else if (resume.long_packet)
        LongPacket(in.pktname);
    else
    {
        if (unlink(in.pktname) != 0)
            S_LogMsg("!Can't delete %s", in.pktname);
    }

    StatsWriteAreas();
    Report_Statistics();
}


    if (((pkt->cw >> 8) | (pkt->cw << 8)) != pkt->cw_validation)
        pkt->cw = cREV2;

    if (pkt->cw & cREV2P)
    {


        pkt->cw = type = cREV2P;
    }

        pkt->orig_zone = pkt->qm_orig_zone;
        pkt->dest_zone = pkt->qm_dest_zone;
        pkt->orig_point = 0;
        pkt->dest_point = 0;

        pkt->cw = type = cREV2;
        pkt->rev_min = 0;
    }

    if (pkt->orig_zone == 0)
        pkt->orig_zone = config.addr->zone;

    if (pkt->dest_zone == 0)
        pkt->dest_zone = config.addr->zone;

    return type;
}



    if (!in->ctrl)
        return -1;

    Copy_To_Header(in);


static void near Get_TFS(struct _inmsg *in)
{
    (void)memset(&in->msg, '\0', sizeof(XMSG));

    (void)strncpy(in->msg.__ftsc_date, Get_To_Nul(NULL, NULL, in->pktfile, 0),
                  sizeof(in->msg.__ftsc_date));

    (void)strncpy(in->msg.to, Get_To_Nul(NULL, NULL, in->pktfile, 0), sizeof(in->msg.to));

    (void)strncpy(in->msg.from, Get_To_Nul(NULL, NULL, in->pktfile, 0), sizeof(in->msg.from));

    (void)strncpy(in->msg.subj, Get_To_Nul(NULL, NULL, in->pktfile, 0), sizeof(in->msg.subj));


static void near Copy_To_Header(struct _inmsg *in)
{
    NETADDR *orig, *dest;


    orig->zone = (in->pkt.orig_zone ? in->pkt.orig_zone : config.addr->zone);
    dest->zone = (in->pkt.dest_zone ? in->pkt.dest_zone : config.addr->zone);


    if (!strstr(in->ctrl, "\x01"
                          "AREA"))
        ConvertControlInfo(in->ctrl, orig, dest);


static char *near AllocBigBuf(byte *txtp, byte *ctrl, unsigned num_sb)
{
    if (!msgb)
    {
        int size = sizeof(XMSG) + strlen(ctrl) + NumKludges(ctrl) + strlen(txtp) + (num_sb * 25) +
                   60 + MAX_TAGLEN;

        if ((msgb = malloc(size)) == NULL)
        {
            S_LogMsg("!Not enough mem to toss/scan message!");


            (void)printf("Ran out of memory!\n");
            return NULL;
        }
    }

    msgbuf = msgb + MAX_TAGLEN;
    (void)memmove(msgbuf, txtp, strlen(txtp) + 1);

    if (begin_sb)
        begin_sb = msgbuf + (unsigned)(ptrdiff_t)(begin_sb - txtp);

    if (end_sb)
        end_sb = msgbuf + (unsigned)(end_sb - txtp);

    return msgb;
}


static void near InvokeTossFeatures(struct _inmsg *in, struct _cfgarea **ar, int *dokill,
                                    int *noscan, char *txtp)
{
    char tag[MAX_TAGLEN];
    struct _feat_toss ft;
    struct _feature *pf;

    (void)strcpy(ft.szPktName, in->pktname);

    ft.pMsg = &in->msg;
    ft.pszCtrl = in->ctrl;
    ft.pszMsgTxt = txtp;



    if (!eqstri((*ar)->name, tag))
    {
        struct _cfgarea arname, *newar;


        if ((newar = SkipSearchList(config.area, &arname)) != NULL)
            *ar = newar;
    }
}

#endif


static int near AttachedFileExists(char *pszFile)
{
    struct _tosspath *ptp;
    char path[PATHLEN];
    char *p;
    int i;


        if (path[i = strlen(path) - 1] != '\\' && path[i] != '/')
            strcat(path, PATH_DELIMS);


        if (fexist(path))
            return TRUE;
    }

    return FALSE;
}




            if (sb == NULL)
                insecure = TRUE;
        }

        if (insecure)
            (void)sprintf(comment, "Insec %s", ar ? ar->name : (byte *)"");
    }

    return insecure;
}


    DeallocBigBuf();

    txtp = in->txt;


    *area_tag = '\0';
    *comment = '\0';

    ar = GetNetArea(&in->msg);

    if (!DestIsHere(&in->pktprefix))
    {
        if (!Process_Transient_Mail(in))
        {
            ret = FALSE;
            goto Done;
        }


        if (msgb)
            txtp = msgb + MAX_TAGLEN;
    }
    else
    {
        char *p;

            {
                ret = FALSE;
                goto Done;
            }
        }
        else
        {
            ar = Get_Area_Tag(in, p);
            MsgFreeCtrlToken(p);
        }
    }


        for (p = txtp; *p == '\n' || *p == '\r' || *p == (byte)0x8d;)
            p++;

        if (*p == 0)
        {

            if ((in->pktprefix.attr & MSGFILE) == 0 || !AttachedFileExists(in->msg.subj) ||
                DestIsHereA(&in->msg.dest))
            {
                ret = TRUE;
                goto Done;
            }
        }
    }


    dupe = FALSE;


        if (tflag & TFLAG_NOECHO)
        {
            S_LogMsg("!EchoMail message found in a NoEcho NetFile");
            NewArea("*NoEcho*");
            bad_packet = TRUE;
            ret = !badmsg;
            goto Done;
        }


        if (IsADupe(ar, &in->msg, in->ctrl, sq ? MsgGetNextUid(sq) : 0L))
        {
            Handle_Dupe(ar);

            dupe = TRUE;


            if ((config.flag & FLAG_KILLDUPE) == 0 && !badmsg)
                ar = GetDupesArea(in);
            else
            {

                if (!badmsg)
                    NewArea("*KILL*");


                ret = !badmsg || (config.flag & FLAG_KILLDUPE);
                goto Done;
            }
        }
    }

    if (ar == NULL)
    {
        ret = TRUE;
        goto Done;
    }


    if ((config.flag & FLAG_ONEPASS) == 0 || (ar->flag & AFLAG_PASSTHRU) == 0)
    {
        if (NetmailArea(ar))
            erl_net = TRUE;
        else
            erl_echo = TRUE;

        if (!Open_Area(ar))
        {
            UndoLastDupe();
            ret = FALSE;
            goto Done;
        }
    }
    else
        NewArea(ar->name);

    msglen = (dword)strlen(txtp) + 1;

                                 (dword)strlen(in->ctrl) + msglen;

        ar->flag |= AFLAG_STATDATA;
    }


        if ((ar->flag & AFLAG_PASSTHRU) == 0)
        {
            if (MsgGetHighWater(sq) != MsgHighMsg(sq))
            {
                if ((config.flag2 & FLAG2_QUIET) == 0)
                    (void)printf("\n");

                savemb = msgbuf;

                realstart = msgbuf = smalloc(maxmsglen + (unsigned)sizeof(XMSG));


        if ((ar->scan && ar->scan->next) || !AddrMatchNS(&in->msg.orig, ar->scan))
        {

            if (sb == NULL || num_sb == 0)
            {
                ar = config.badmsgs;

                (void)strcpy(comment, "No SEEN-BYs");


                UndoLastDupe();

                insecure = TRUE;

                if (badmsg)
                {
                    ret = FALSE;
                    goto Done;
                }

                if (ar == NULL || !Open_Area(ar))
                {
                    ret = TRUE;
                    goto Done;
                }
            }
            else
            {

                    toss_cnt++;
                }


                msglen = (dword)strlen(txtp) + 1;
            }
        }
        else
        {
            int fSkipScan = FALSE;

            if (AllocBigBuf(txtp, in->ctrl, 0))
                ProcessACUpdate(sq, ar, &in->msg, in->ctrl, &dokill, 0L, NULL, 0, &fSkipScan);
        }
    }


        if (ar->flag & AFLAG_HIDEMSG)
            in->msg.attr |= MSGPRIVATE;


        if (dupe || insecure)
        {
            unsigned len;

            (void)sprintf(temp,
                          "\x01"
                          "AREA:%s",
                          area_tag);
            len = strlen(temp);


    NW(config);

    in->msg.attr |= MSGFWD;

#if 1

    (void)sprintf(comment, "Fwd %hd/%hd", in->pktprefix.dest_net, in->pktprefix.dest_node);

#else

    (void)sprintf(temp, "%s (Fwd %hd/%hd)", *last_area ? "" : "       ", in->pktprefix.dest_net,
                  in->pktprefix.dest_node);

    if ((config.flag2 & FLAG2_QUIET) == 0)
    {
        (void)printf(temp);

        for (x = strlen(temp); x--;)
            (void)printf("\b");
    }
#endif

#ifdef NEVER

    if (!AllocBigBuf(in->txt, 1))
    {
        S_LogMsg("#Warning: Not enough mem to tag");
        return FALSE;
    }
#endif

    return TRUE;
}


    for (p = txt + 5, o = area_tag; *p && o < area_tag + MAX_TAGLEN - 1; p++)
        if (*p != ' ')
            *o++ = *p;

    *o = '\0';


    if ((ar = SkipSearchList(config.area, &arname)) == NULL ||
        (ar->flag & (AFLAG_BAD | AFLAG_DUPES | AFLAG_NET)))
    {
        if ((config.flag2 & FLAG2_QUIET) == 0)
        {
            (void)sprintf(comment, "Unknown %s", area_tag);
        }

        return config.badmsgs;
    }


static void near Handle_Dupe(struct _cfgarea *ar)
{
    ar->dupes++;

    if (ar->name)
        (void)sprintf(comment, "Dupe %s", ar->name);
    else
        (void)strcpy(comment, "Dupe");
}


    if (!eqstri(last_area, name) || !eqstri(last_comment, comment))
    {
        len = strlen(last_area) + strlen(last_comment) + (*last_comment ? 3 : 0);

                (void)printf("\b \b");

            (void)strcpy(last_area, name);
            (void)strcpy(last_comment, comment);

            if (*comment)
                (void)printf("%s (%s): -----", name, comment);
            else
                (void)printf("%s: -----", name);
        }
    }
}


    if (!talist_init)
    {
        talist_init = TRUE;

        for (an = 0; an < config.max_talist; an++)
        {
            talist[an].sq = NULL;
            talist[an].ar = NULL;
        }
    }


        for (an = 0; an < config.max_talist; an++)
            if (ar == talist[an].ar)
            {
                savetl = talist[an];
                break;
            }

        {

            (void)memmove(talist + 1, talist, (config.max_talist - 1) * sizeof(struct _talist));


            if (savetl.sq)
            {
                (void)MsgUnlock(savetl.sq);
                (void)MsgCloseArea(savetl.sq);

                savetl.sq = NULL;
                savetl.ar = NULL;
            }


static void near Close_Area(void)
{
    word an;

    for (an = 0; an < config.max_talist; an++)
        if (talist[an].sq)
            (void)MsgCloseArea(talist[an].sq);

    sq = NULL;
}


void Report_Statistics(void)
{
    struct _cfgarea *ar;
    char logfmt[PATHLEN];

    for (ar = SkipFirst(config.area); ar; ar = SkipNext(config.area))
        if (ar->dupes || ar->tossed || ar->sent)
        {
            (void)strcpy(logfmt, ":   %-14s (Toss=%04hu");

            if (ar->dupes || ar->sent)
                (void)strcat(logfmt, "  Sent=%04hu");

            if (ar->dupes)
                (void)strcat(logfmt, "  Dupe=%04hu");

            (void)strcat(logfmt, ")");

            S_LogMsg(logfmt, ar->name, ar->tossed, ar->sent, ar->dupes);
        }
}

        if (MatchSS(&fr, &np->addr, ((config.flag & FLAG_CHECKZ) == 0) ? 1 : 0))
        {
            (void)memmove(pktpwd, in->pkt.password, 8);
            pktpwd[8] = '\0';

            if (!eqstri(pktpwd, np->pwd))
            {
                S_LogMsg("!Bad pwd in packet: got=`%s', expected=`%s'", pktpwd, np->pwd);

                return FALSE;
            }

            break;
        }

    return TRUE;
}


static struct _cfgarea *GetDupesArea(struct _inmsg *in)
{
    NW(in);
    return config.dupes;
}


            StatsWriteBlock(TYPE_BTOSS, 0, 0, NULL);



                        if (tossed)
                        {
                            (void)MsgCloseMsg(hmsg);
                            hmsg = NULL;

                            uid = MsgMsgnToUid(harea, mn);
                            (void)MsgKillMsg(harea, mn);
                            mn = MsgUidToMsgn(harea, uid, UID_PREV);
                        }
                    }
                    else
                    {
