// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_scan.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#include "s_scan.h"
#include "alc.h"
#include "bfile.h"
#include "dr.h"
#include "max.h"
#include "msgapi.h"
#include "prog.h"
#include "s_dupe.h"
#include "s_hole.h"
#include "squish.h"
#include <ctype.h>
#include <dos.h>
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#ifdef DJ
extern FILE *dj;
#endif

static word full_scan = 0;
static dword scan_ctr;
#ifndef UNIX
static char maxmsgs_scan[] = "MAXMSGS2.DAT";
#else
static char maxmsgs_scan[] = "maxmsgs2.dat";
#endif

static void near cleanup_exit(int erl)
{
    MsgCloseApi();
    S_LogMsg("!Squish exiting abnormally");
    S_LogClose();
    exit(erl);
}

void Scan_Messages(char *etname, NETADDR *scan, time_t start)
{
    FILE *fp;
    char area[MAX_TAGLEN];
    time_t secs;


    DupeFlushBuffer();
}


    if (erl_max)
        return;


    if (full_scan && (config.flag2 & FLAG2_NPTHRU) && (ar->flag & AFLAG_PASSTHRU))
        return;

    if (!opensq)
        sq = MsgOpenArea(ar->path, MSGAREA_NORMAL, ar->type);
    else
        sq = opensq;

    if (!sq)
    {
        if (msgapierr != MERR_NOENT)
            (void)printf("Invalid area: `%s'\n", ar->name);

        return;
    }

    hwm = MsgGetHighWater(sq);
    hmsg = MsgHighMsg(sq);


            if (hwm == 1 && (ar->type & MSGTYPE_SDM))
                continue;

            if ((mh = MsgOpenMsg(sq, MOPEN_RW, hwm)) == NULL)
            {

                if (msgapierr != MERR_NOENT)
                {
                    S_LogMsg("!Can't read %s#%ld (err#%d)", ar->name, hwm, msgapierr);


            if (MsgGetTextLen(mh) >= maxmsglen - 256)
            {

            bytes = MsgReadMsg(mh, &msg, 0L, (dword)maxmsglen - 1, msgbuf, (dword)CTEXT_LEN, ctext);

            if (bytes != (dword)-1L && bytes != 0L)
                msgbuf[(int)bytes] = '\0';

            delete_me = FALSE;


            if (bytes != (dword)-1L && bytes != 0L && NeedToEcho(msgbuf) &&
                ((msg.attr & MSGSCANNED) == 0 || resc))
            {
                word scanit = TRUE;



                        if (sb == NULL || num_sb == 0)
                        {
                            S_LogMsg("!No SEEN-BYs in %s:%ld", ar->name, hwm);
                            scanit = FALSE;
                        }
                    }
                }

                if (scanit)
                {

                    sb = Sort_And_Flatten(sb, num_sb,
                                          ar->num_scan + config.num_ats + ar->num_add + !!resc + 1);


                    if ((added = Scan_To_All(ar, sb, num_sb, &msg, ctext, NULL,
                                             MsgMsgnToUid(sq, hwm), &delete_me, sq, &hwm)) != 0 &&
                        !resc)
                    {
                        msg.attr = old_attr | MSGSCANNED;

                        strlen_msgbuf = strlen(msgbuf + added - 1);

                        (void)MsgWriteMsg(
                            mh, FALSE, (ar->type & MSGTYPE_SDM) ? NULL : &msg,
                            (ar->type & MSGTYPE_SDM) ? msgbuf + added - 1 : NULL,
                            (dword)((ar->type & MSGTYPE_SDM) ? (unsigned)(strlen_msgbuf + 1)
                                                             : (unsigned)0),
                            (dword)((ar->type & MSGTYPE_SDM) ? (unsigned)(strlen_msgbuf + 1)
                                                             : (unsigned)0),
                            (dword)((unsigned)(strlen(ctext) + 1)), ctext);

                        scan_ctr++;
                    }


            if (!resc)
            {

                    uid = MsgMsgnToUid(sq, hwm);


                    hwm = MsgUidToMsgn(sq, uid, UID_PREV);


    if (dwNewHWM != (dword)-1)
        MsgSetHighWater(sq, dwNewHWM);

    if ((config.flag2 & FLAG2_QUIET) == 0)
        (void)printf("\b\b\b\b\b     \n");


            p++;

    }

    if (p[0] == 'N' && p[1] == 'O' && p[2] == 'E' && p[3] == 'C' && p[4] == 'H' && p[5] == 'O')
        return FALSE;
    else
        return TRUE;
}

struct _sblist *Digitize_Seenbys(struct _cfgarea *ar, byte *text, unsigned *sb_num)
{
    static struct _sblist sb, last;
    struct _sblist *fsb, *nextfsb, *nsb;

    unsigned num_sb, len;

    byte *endofline;
    byte *s, *ap, *csb;
    byte *next_sb;

    NW(ar);


    next_sb = GetNextToken(msgbuf, text, seen_by_str);

    nsb = &sb;
    num_sb = 0;
    begin_sb = next_sb;


        while (eqstrn(next_sb, seen_by_str, SEEN_BY_LEN))
        {

                len = (unsigned)(endofline - next_sb) + 1;

                csb = smalloc(len + 1);

                (void)strncpy(csb, next_sb, len);
                csb[len] = '\0';
            }

            (void)memset(nsb, '\0', sizeof(struct _sblist));


                *nsb = last;

                Parse_NetNode(ap, NULL, &nsb->net, &nsb->node, NULL);

                last = *nsb;

                    nsb->next = NULL;
                }
            }

            free(csb);


            while (*endofline == '\x0d' || *endofline == '\x0a' || *endofline == (byte)0x8d)
            {
                endofline++;
            }


        while (next_sb && *next_sb)
        {
            if (*next_sb < ' ')
            {
                break;
            }
        }


        if (next_sb && *next_sb == '\0')
            break;
        else
        {
            char *p;


            p = GetNextToken(msgbuf, next_sb, seen_by_str);

#if 0

            begin_sb = next_sb = p;


    if (nsb && nsb != &sb)
        free(nsb);

    *sb_num = num_sb;
static int _stdc sbl_comp(const void *s1, const void *s2)
{
  int x;

  if ((x=((int)(struct _sblist *)s1)->zone - (int)((struct _sblist *)s2)->zone) != 0)
    return x;
  else if ((x=(int)((struct _sblist *)s1)->net - (int)((struct _sblist *)s2)->net) != 0)
    return x;
  else if ((x=(int)((struct _sblist *)s1)->node - (int)((struct _sblist *)s2)->node) != 0)
    return x;
  else return ((int)((struct _sblist *)s1)->point - (int)((struct _sblist *)s2)->point);
}
#endif

static int _stdc sbl_comp_nz(const void *s1, const void *s2)
{
    int x;

    if ((x = (int)((struct _sblist *)s1)->net - (int)((struct _sblist *)s2)->net) != 0)
        return x;
    else
        return ((int)((struct _sblist *)s1)->node - (int)((struct _sblist *)s2)->node);
}

struct _sblist *Sort_And_Flatten(struct _sblist *sb, unsigned num_sb, unsigned additional)
{

    sbf = smalloc((num_sb + additional) * sizeof(struct _sblist));


    outoforder = FALSE;

    for (i = 0; sb && i < num_sb; i++)
    {
        sbf[i] = *sb;
        sbf[i].next = NULL;
        sbold = sb;
        sb = sb->next;


    if (outoforder)
        qsort(sbf, num_sb, sizeof(struct _sblist), sbl_comp_nz);

    return sbf;
}


        UMSGID uid_hwm;

        S_LogMsg("*  Remote delete: %s:%ld", ar->name, msgn);


        if (hwm)
            *hwm = MsgUidToMsgn(sq, uid_hwm, UID_PREV);

        return;
    }

    S_LogMsg("*  Remote modify: %s:%ld", ar->name, msgn);


int ProcessACUpdate(HAREA sq, struct _cfgarea *ar, XMSG *msg, char *ctrl, int *do_kill, UMSGID uid,
                    dword *hwm, unsigned added, int *pfSkipScan)
{
    char *ctrl_dup;
    struct _sblist *ps;
    dword msgid_hash, msgid_serial;
    static char acupdate[] = "ACUPDATE";
    dword *pNewHash, *pNewSerial;
    dword msgn;
    char *kludge;
    int do_modify;

    *do_kill = FALSE;



    for (ps = ar->update_ok; ps; ps = ps->next)
        if (AddrMatchNS(&msg->orig, ps))
            break;

    if (!ps)
    {
        static int logged_acupdate = FALSE;

        if (!logged_acupdate)
        {
            logged_acupdate = TRUE;
            S_LogMsg("!Insecure ACUPDATE message from %s!", Address(&msg->orig));
        }

        *pfSkipScan = TRUE;
        *do_kill = TRUE;
        MsgFreeCtrlToken(kludge);
        return TRUE;
    }


    if (ar->type & MSGTYPE_SDM)
        return TRUE;

    ctrl_dup = sstrdup(ctrl);


    if (msgid_hash &&
        (msgn = FindUpdateMessage(sq, ar, msgid_hash, msgid_serial, &pNewHash, &pNewSerial)) != 0L)
    {

    *do_kill = TRUE;

    MsgFreeCtrlToken(kludge);
    return TRUE;
}


    if (!ProcessACUpdate(sq, ar, msg, ctxt, do_kill, uid, hwm, needscan, &fSkipScan))
        return 0;

    scanto = smalloc(ar->num_scan);


        if ((config.flag & FLAG_ONEPASS) == 0)
            (void)IsADupe(ar, msg, ctxt, uid);


        Insert_Sb_Node(&ar->primary, sb, &num_sb);


        for (ats = config.ats; ats; ats = ats->next)
            Insert_Sb_Node(ats, sb, &num_sb);

        for (ats = ar->add; ats; ats = ats->next)
            Insert_Sb_Node(ats, sb, &num_sb);


        ct = CvtCtrlToKludge(ctxt);

        if (ct)
        {
            ctlen = strlen(ct);


        Fix_SeenBys(sb, num_sb, msgbuf, oldsmask = 0, ar);


        msg->orig.zone = ar->primary.zone;
        msg->orig.net = ar->primary.net;
        msg->orig.node = ar->primary.node;
        msg->orig.point = ar->primary.point;


        for (sbnode = ar->scan, sl = ar->statlist, nst = 0; sbnode; sbnode = sbnode->next, nst++)
        {
            if (scanto[nst])
            {
#ifdef DJ
                (void)fprintf(dj, " %d:%d/%d.%d", sbnode->zone, sbnode->net, sbnode->node,
                              sbnode->point);
#endif

                scanmask = 0;

                if (config.pointnet && sbnode->net != config.pointnet)
                    scanmask |= SCAN_NOPOINT;

                if (GetsTinySeenbys(sbnode))
                    scanmask |= SCAN_TINY;

                if (scanmask != oldsmask)
                    Fix_SeenBys(sb, num_sb, msgbuf, oldsmask = scanmask, ar);


                        zsb = smalloc(sizeof(struct _sblist) * zg->n_nodes);

                        for (zp = zsb, zgl = zg->nodes; zgl; zgl = zgl->next, zp++)
                        {
                            *zp = *zgl;
                            zp->next = NULL;
                        }


                        Fix_SeenBys(zsb, zg->n_nodes, msgbuf, 0, ar);

                        free(zsb);

                        scanmask = 0;
                        oldsmask = (unsigned)-1;
                        break;
                    }

                Scan_To(sbnode, msg, msgbuf, 0L, ar, sl);
                ar->sent++;
            }

            if (sl)
                sl = sl->next;
        }

#ifdef DJ
        (void)fprintf(dj, "\n");
#endif


        if (scanmask != 0 || oldsmask == (unsigned)-1)
            Fix_SeenBys(sb, num_sb, msgbuf, oldsmask = 0, ar);


    if (bsearch(&find, sb, *num_sb, sizeof(struct _sblist), sbl_comp_nz) == NULL)
    {

        for (s = sb, end = sb + *num_sb; s < end; s++)
            if (sbl_comp_nz(&find, s) < 0)
                break;



        *s = find;
        (*num_sb)++;
    }
}

static int near Need_To_Scan(struct _cfgarea *ar, struct _sblist *scanto, struct _sblist *sb,
                             unsigned num_sb, XMSG *msg)
{
    NETADDR dest;
    struct _sblist sbl;
    struct _perlist *pl;


    for (pl = ar->plist; pl; pl = pl->next)
        if (MatchSS(&pl->node, scanto, FALSE) && !eqstri(msg->to, pl->name))
            return FALSE;


    if (scanto->point)
    {

        if ((config.flag & FLAG_ONEPASS) || (msg->attr & MSGLOCAL) || (ar->type & MSGTYPE_SQUISH))
        {
            if (!MatchNS(&msg->orig, scanto, TRUE))
                return TRUE;
        }
        else
            return FALSE;
    }


    if (msg->orig.net == scanto->net && msg->orig.node == scanto->node &&
        msg->orig.point == scanto->point && (msg->attr & MSGLOCAL) == 0)
    {
        return FALSE;
    }


    return (bsearch(&sbl, sb, num_sb, sizeof(struct _sblist), sbl_comp_nz) == NULL);
}

static void near AddAreaTag(char *txt, struct _cfgarea *ar)
{
    char temp[PATHLEN];
    unsigned len;

    (void)sprintf(temp,
                  "\x01"
                  "AREA:%s",
                  ar->name);
    len = strlen(temp);

    (void)strocpy(txt + len, txt);
    (void)memmove(txt, temp, len);
}

void Scan_To(struct _sblist *scanto, XMSG *msg, char *text, dword attr, struct _cfgarea *ar,
             struct _statlist *sl)
{
    struct _pktprefix pp;
    dword len;
    int flavour;


    {
        pp.orig_net = (sword)msg->orig.net;
        pp.orig_node = (sword)msg->orig.node;
        pp.dest_net = (sword)scanto->net;
        pp.dest_node = (sword)scanto->node;
    }

    pp.attr = (word)msg->attr;
    pp.cost = 0;

    flavour = MsgAttrToFlavour(attr);

    len = (dword)strlen(text) + 1L;

    if ((config.flag & FLAG_STATS) && sl)
    {
        sl->out_msgs++;
        sl->out_bytes += (dword)(size_t)(p - lump) + len;
        ar->flag |= AFLAG_STATDATA;
    }

    Add_Outbuf(scanto, &pp, lump, (dword)(size_t)(p - lump), text, (dword)len, flavour, ar);
}

#ifdef NEVER


static int near Twiddle_Area_Tag(char *name, char *msgbuf)
{
    char temp[PATHLEN];
    int len;

    (void)sprintf(temp, "AREA:%s\r", name);
    len = strlen(temp);

    memmove(msgbuf - len, temp, len);
    return len;
}

#endif


    seenby = smalloc((num_sb + 20) * MAX_ADDRLEN);


    for (i = 0, len = 0, last_net = (word)-1, p = seenby; i < num_sb; i++)
    {

        if (sb[i].net == config.pointnet && (smask & SCAN_NOPOINT) &&
            ar->primary.net != config.pointnet)
            continue;


        if ((smask & SCAN_TINY) && !NodeInSlist(sb + i, ar->scan) &&
            !DestIsHereA(SblistToNetaddr(sb + i, &here)) && !NodeInSlist(sb + i, ar->add) &&
            !NodeInSlist(sb + i, config.ats))
        {
            continue;
        }

        if (sb[i].net == last_net)
            (void)sprintf(p, " %hu", sb[i].node);
        else
        {
            (void)sprintf(p, " %hu/%hu", sb[i].net, sb[i].node);
            last_net = sb[i].net;
        }

        cl = strlen(p);

    *p = '\0';

    new_len = strlen(seenby);
    endtear = NULL;
    tearpos = GetTearPos(mbuf, &endtear);

    if (GetNextToken(mbuf, tearpos, seen_by_str) == NULL)
        tearpos = mbuf;


    if (p)
    {
        do
        {
                s++;



        old_len = (unsigned)(s - p);


        (void)memmove(p, seenby, new_len);

    {
        if (!endtear || (endtear[-1] != '\x0d' && endtear[-1] != '\x0a'))
        {
            unsigned mlen;

            mlen = strlen(mbuf);

            endtear = mbuf + mlen;


        (void)memmove(endtear + new_len, endtear, strlen(endtear) + 1);


static void near Add_Us_To_Path(struct _cfgarea *ar, char *mbuf)
{
    unsigned len, i;
    word net = (word)-1;

    byte us[PATHLEN];
    byte pathline[PATHLEN];
    byte temp[PATHLEN];

    byte *s, *p, *s2, *pp, *end;


    (void)sprintf(us, "%hu/%hu", ar->primary.net, ar->primary.node);


        p = s++;
    }


        for (end = p; *end != '\x0d' && *end;)
            end++;


        if (len >= PATHLEN)
            len = PATHLEN - 2;


        i = len;

        while (i && (pathline[i - 1] == '\x0d' || pathline[i - 1] == ' '))
            pathline[--i] = '\0';


        s2 = strrchr(pathline, '/');

                ;

            s2++;


        if (s2 && net == ar->primary.net)
            (void)sprintf(temp, " %hu", ar->primary.node);
        else
            (void)sprintf(temp, " %s", us);


        if (pp && (eqstri(pp, temp) || eqstri(pp + 1, us)))
            return;

            (void)sprintf(temp, "\r\x01PATH: %s\r", us);
            (void)strcat(pathline, temp);
        }


        (void)memmove(p, pathline, strlen(pathline));
    }

        if (!p)
            p = mbuf + strlen_msgbuf - 1;
        else
        {
            p = strchr(p, '\x0d');

            if (!p)
                p = mbuf + strlen_msgbuf - 1;

            {
                while (*p == '\x0a' || *p == (byte)0x8d || *p == '\x0d')
                    p++;
            }
        }


static void near Add_Tear_Line(char *mbuf, struct _cfgarea *ar, XMSG *msg)
{
    FILE *corig;
    NETADDR n;

    byte temp[PATHLEN];
    byte area_origin[PATHLEN];
    byte *addrstr;


    if (GetTearPos(mbuf, NULL) || (msg->attr & MSGLOCAL) == 0 || begin_sb)
        return;

    (void)sprintf(temp, (ar->type & MSGTYPE_SQUISH) ? "%s.sqo" : "%s\\origin", ar->path);

    (void)strcpy(area_origin, config.origin);

    if ((corig = shfopen(temp, "r", O_RDONLY)) != NULL)
    {
        if (fgets(area_origin, PATHLEN, corig) == NULL)
        {

        (void)Strip_Trailing(area_origin, '\n');
    }



    BLIST *bl, *blnew;


    bl = (BLIST *)cur_ob;


  if (DestIsHereA(config,&na))
  {
    
  }
#endif


    *(struct _pktprefix *)cur_ob = *pp;
    cur_ob += sizeof(struct _pktprefix);

    (void)memmove(cur_ob, lump, (unsigned)lumplen);
    cur_ob += (unsigned)lumplen;

    (void)memmove(cur_ob, text, (unsigned)textlen);
    cur_ob += (unsigned)textlen;

    bl->next = (BLIST *)cur_ob;
    bl->len = (long)((byte *)cur_ob - (byte *)bl) - sizeof(BLIST);


    blnew = (BLIST *)cur_ob;
    blnew->len = 0L;

    nmsg_sent++;
}

void Alloc_Outbuf(void)
{
    BLIST *bl;
    unsigned oblen = outbufmax;


    while (oblen >= 16384 && (outbuf = malloc(oblen)) == NULL)
        oblen -= 4096;

    if (oblen < 16384)
        NoMem();

    cur_ob = outbuf;

    end_ob = (byte far *)(outbuf + oblen);

    bl = (BLIST *)cur_ob;
    bl->len = 0;
}

void Free_Outbuf(void)
{
    free(outbuf);
    outbuf = NULL;
}

    BFILE bf;

    struct _pkthdr pkthdr;

    char addr[MAX_ADDRLEN];
    char pktname[PATHLEN];

    BLIST *bl;
    BLIST *bn;

    unsigned i;

#ifdef DCORE
    printf("\n*** CORE begin=%ld\n", (long)coreleft());
#endif

    for (bl = (BLIST *)outbuf; bl->len; bl = bl->next)
    {
        if (bl->id != BL_ID)
        {
            S_LogMsg("!Internal error: garbled outbuf[].");
            cleanup_exit(ERL_ERROR);
        }


                (void)Bseek(bf, -(long)sizeof(word), BSEEK_END);
            }

                HoleAddPacket(pktname, bl);

#ifdef DCORE
                printf("\n--- CORE wmix=%ld\n", (long)coreleft());
#endif

                if ((bf = Bopen(pktname, BO_CREAT | BO_TRUNC | BO_WRONLY | BO_BINARY, BSH_DENYWR,
                                writebufmax)) == NULL)
                {

                        if (fexist(pktname))
                            unlink(pktname);

                        continue;
                    }
                }

#ifdef DCORE
                printf("\n--- CORE wmuf=%ld\n", (long)coreleft());
#endif

                Fill_Out_Pkthdr(&pkthdr, &bl->ar->primary, bl->zone, bl->net, bl->node, bl->point);

                if (Bwrite(bf, &pkthdr, sizeof pkthdr) != sizeof pkthdr)
                    ScanDiskFull();
            }

#ifdef DCORE
            printf("\n--- CORE wmit=%ld\n", (long)coreleft());
#endif


            for (bn = bl->next; bn->len && bn->id == BL_ID; bn = bn->next)
            {
                if (!bn->done && bn->zone == bl->zone && bn->net == bl->net &&
                    bn->node == bl->node && bn->point == bl->point && bl->flavour == bn->flavour &&
                    AddrMatchS(&bl->ar->primary, &bn->ar->primary))
                {
                    (void)printf("\b \b");
        }
    }


static int near GetsTinySeenbys(struct _sblist *node)
{
    struct _sblist *sb;

    for (sb = config.tiny_except; sb; sb = sb->next)
        if (AddrMatchS(node, sb))
            return FALSE;

    for (sb = config.tiny; sb; sb = sb->next)
        if (AddrMatchS(node, sb))
            return TRUE;

    return FALSE;
}
