// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_pack.c,v 1.3 2003/06/05 23:17:22 wesgarland Exp $";
#pragma on(unreferenced)

#define NOVARS

static char area_col[] = "AREA:";
static char file_delim[] = " ;,";

void Pack_Messages(struct _cfgarea *nets)
{
    struct _cfgarea *ar;


    if (config.flag & FLAG_FRODO)
        return;

    n_notsent = n_packed = 0L;

    Alloc_Outbuf();

    if (ar == NULL)
    {
        S_LogMsg("!No netmail path defined");
        Free_Outbuf();
        return;
    }

    if ((sq = MsgOpenArea(ar->path, MSGAREA_NORMAL, ar->type)) == NULL)
    {
        (void)printf("Invalid netmail area: `%s'\n", ar->name);
        Free_Outbuf();
        return;
    }

    (void)printf("\nSquashing messages in %s...\n", ar->path);

    S_LogMsg("#Packing from %s (%ld msgs)", ar->path, MsgNumMsg(sq));

    for (mn = 1L; mn <= MsgHighMsg(sq); mn++)
        if (!Pack_Netmail_Msg(sq, &mn, ar))
            break;

    (void)MsgCloseArea(sq);

    (void)printf("\r                                            \r");
    Flush_Outbuf();
    Free_Outbuf();

    if (n_notsent)
        S_LogMsg(":  Packed=%ld  NotSent=%ld", n_packed, n_notsent);
    else
        S_LogMsg(":  Packed=%ld", n_packed);
}

#ifdef OS_2


        if (pf->pfnNetMsg)
        {

            fn.ulAction = 0;


            if (fn.ulAction & FACT_KILL)
            {
                *dokill = TRUE;
                *logkill = FALSE;
            }


            if (fn.ulAction & FACT_RWMSG)
                *rewriteit = TRUE;

}
#endif

static char *front;

static unsigned near Pack_Netmail_Msg(HAREA sq, dword *mn, struct _cfgarea *ar)
{
    HMSG mh, out_msg;
    NETADDR olddest, destnop;
    XMSG msg, original;
    char *ctrl, *ct, *buf;

    UMSGID this;
    dword bytes;
    dword killmsgn;
    dword offset;

    unsigned ctlen, got;
    int sentit = FALSE, rewriteit = FALSE, dokill = FALSE, logkill = FALSE;

    killmsgn = *mn;

    if ((mh = MsgOpenMsg(sq, MOPEN_RW, *mn)) == NULL)
    {
        if (msgapierr != MERR_NOENT)
            S_LogMsg("!Can't open netmail msg #%lu (err#%d)", *mn, msgapierr);

        return TRUE;
    }

    if (MsgGetTextLen(mh) >= maxmsglen)
    {
        S_LogMsg("!Message %lu too large to pack (%#lx)", *mn, (long)maxmsglen);
        (void)MsgCloseMsg(mh);
        return TRUE;
    }

    ctlen = (unsigned)MsgGetCtrlLen(mh);

    if ((ctrl = malloc(ctlen + 5)) == NULL ||
        (msgbuf = (char *)malloc(maxmsglen + ctlen + 180u)) == NULL)
    {
        S_LogMsg("!Not enough memory to pack msg %lu", *mn);

        if (ctrl)
            free(ctrl);

        (void)MsgCloseMsg(mh);
        return TRUE;
    }


    if (bytes != (dword)-1)
        msgbuf[(int)bytes] = '\0';


#ifdef OS_2
        (void)InvokeFeatures(sq, mh, &msg, ctrl, msgbuf, mn, &dokill, &logkill, &rewriteit);
#endif
    }
    else
    {
        char *i, *isave;


            RemoveFromCtrl(ctrl, "INTL");

            msg.dest = ndest;
            msg.orig = norig;
        }


            if (!DestIsHereA(&msg.dest))
            {
                if ((msg.attr & MSGLOCAL) == 0 && !OkToForward(&msg))
                {
                    if ((config.flag2 & FLAG2_QUIET) == 0)
                        (void)printf("Not forwarded: #%lu\n", *mn);

                    n_notsent++;
                }
                else
                {

                    if ((msg.attr & MSGLOCAL) && *msg.__ftsc_date && InvalidDate(msg.__ftsc_date))
                    {
                        S_LogMsg("!Grunged date in %s:%ld", ar->name, *mn);
                    }
                    else
                    {
                        if ((msg.attr & MSGLOCAL) == 0)
                        {
                            struct _sblist *sb, *sbe;


                                    for (sbe = config.stripattr_except; sbe; sbe = sbe->next)
                                        if (AddrMatchNS(&msg.orig, sbe))
                                            break;


                                    if (!sbe)
                                        msg.attr &= ~(MSGCRASH | MSGHOLD);
                                }
                            }

                            TrackMessage(&msg, ctrl);
                            AddViaLine(msgbuf, ctrl);

                        if (msg.attr & MSGLOCAL)
                            AddViaLine(msgbuf, ctrl);

                        front = msgbuf;

#ifdef NEVER
                        if (msgbuf[0] == 'A' && msgbuf[1] == 'R' && msgbuf[2] == 'E' &&
                            msgbuf[3] == 'A' && msgbuf[4] == ':')
                        {

                            while (*front == '\r' || *front == '\n')
                                front++;
                        }
#endif


                        if (!GateRouteMessage(&msg, *mn, &olddest))
                            (void)WriteZPInfo(&msg, AddToMsgBuf, ctrl);


                        if (Send_Message(mh, &msg, bytes, *mn, ar))
                        {
                            rewriteit = sentit = TRUE;

                            if (msg.attr & MSGKILL)
                                dokill = logkill = TRUE;

                            n_packed++;


    free(msgbuf);


        }
        else
        {
            dword oldmn;


            this = MsgMsgnToUid(sq, *mn);

            if ((out_msg = MsgOpenMsg(sq, MOPEN_CREATE, 0L)) != NULL)
            {
                if ((buf = malloc(REMAP_BUF_SIZE)) == NULL)
                    S_LogMsg("!No mem for point remap");
                else
                {

                if ((oldmn = MsgUidToMsgn(sq, this, UID_EXACT)) != 0)
                    (void)MsgKillMsg(sq, oldmn);

                *mn = MsgUidToMsgn(sq, this, UID_PREV);

  if (rewriteit)
  {
    if ((mh=MsgOpenMsg(sq, MOPEN_RW, *mn))==NULL)
      S_LogMsg("@Error re-opening message #%ld", (long)*mn);
    else
    {
      int rc;

      rc=MsgReadMsg(mh, &msg, 0L, 0L, NULL, 0L, NULL);

      S_LogMsg("@Verify: message #%ld has SENT bit set: %s (rc=%d)", (long)*mn,
               (msg.attr & MSGSENT) ? "yes" : "no!!!!!!!!!!!!!",
               rc);

      MsgCloseMsg(mh);
    }
  }
#endif


static void EXPENTRY AddToMsgBuf(byte OS2FAR *str)
{
    unsigned slen = strlen(str);
    char *where = (front ? front : msgbuf);

    (void)memmove(where + slen, where, strlen(where) + 1);
    (void)memmove(where, str, slen);
}


    if (!*config.tracklog)
        return;

    if (!trklog)
        if ((trklog = shfopen(config.tracklog, "a", O_CREAT | O_WRONLY | O_APPEND)) == NULL)
            ErrOpening("track log", config.tracklog);


static void near AddViaLine(byte *mbuf, byte *ctrl)
{
    NETADDR n;
    time_t gmt;
    struct tm *lt;
    byte temp[160], *s;
    char *artag;


    (void)sprintf(temp,
                  "\x01Via " SQNAME " %s %s, "
                  "%s %s %02d %d at %02d:%02d UTC\r",
                  version, Address(SblistToNetaddr(config.addr, &n)), weekday_ab[lt->tm_wday],
                  months_ab[lt->tm_mon], lt->tm_mday, lt->tm_year + 1900, lt->tm_hour, lt->tm_min);


    while (s >= mbuf && (*s == '\n' || *s == (byte)0x8d))
        s--;


    if (*s != '\r')
        (void)strcat(mbuf, "\r");

    (void)strcat(mbuf, temp);
}


    na = msg->dest;
    na.point = 0;

    if (DestIsHereA(&na))
    {
        (void)strcpy(sb1, soundex(msg->to));

        match = FALSE;

        for (re = config.remap; re; re = re->next)
        {
            if ((p = strchr(re->name, '*')) != NULL)
                comp_lim = (unsigned)(p - re->name);
            else
                comp_lim = 0;

            (void)strcpy(sb2, soundex(re->name));

            sdx = FALSE;

            if (eqstrin(msg->to, re->name, comp_lim ? comp_lim : strlen(msg->to)))
                match = TRUE;
            else if (eqstri(sb1, sb2) && (config.flag2 & FLAG2_NOSNDX) == 0)
            {
                sdx = TRUE;
                match = TRUE;
            }
            else if (eqstri(re->name, "*"))
                match = TRUE;

            if (match)
            {
                msg->dest.zone = re->node.zone;
                msg->dest.net = re->node.net;
                msg->dest.node = re->node.node;
                msg->dest.point = re->node.point;

                S_LogMsg("#  Msg#%ld remapped to %s%s", mn, Address(&msg->dest),
                         sdx ? " (soundex)" : "");

                return TRUE;
            }
        }
    }

    return FALSE;
}


    na = msg->dest;
    na.point = 0;

    if (DestIsHereA(&na))
    {
        if (msg->dest.point && config.pointnet)
        {
            msg->dest.net = config.pointnet;
            msg->dest.node = msg->dest.point;
            msg->dest.point = 0;
        }
    }
}

static void near Point_To_Fakenet_Orig(XMSG *msg)
{

    if ((msg->attr & (MSGCRASH | MSGHOLD)) != 0)
        return FALSE;


        for (sb = gr->except; sb; sb = sb->next)
            if (AddrMatchNS(&msg->dest, sb))
            {
                cont = TRUE;
                break;
            }

        if (cont)
            continue;

        for (sb = gr->nodes; sb; sb = sb->next)
            if (AddrMatchNS(&msg->dest, sb))
            {
                if ((config.flag2 & FLAG2_QUIET) == 0)
                {
                    (void)printf("GateRoute #%lu: %s -> ", mn, Address(&msg->dest));
                    (void)printf("%s\n", Address(SblistToNetaddr(&gr->host, &tempnet)));
                }


static int near Send_Message(HMSG mh, XMSG *msg, dword bytes, dword mn, struct _cfgarea *ar)
{
    struct _sblist scanto;
    char fname[PATHLEN];
    char *p;
    int okay_to_scan = TRUE;

    NW(bytes);
    NW(mh);

    if ((config.flag2 & FLAG2_QUIET) == 0)
        (void)printf("Sending (#%lu): %s", mn, Address(&msg->dest));

    (void)NetaddrToSblist(&msg->dest, &scanto);

    if (msg->attr & (MSGFILE | MSGFRQ | MSGURQ))
    {

        msg->attr &= (long)~(MSGSENT | MSGLOCAL | MSGXX2);

        Scan_To(&scanto, msg, msgbuf, msg->attr, ar, NULL);


    if (action != ACTION_POLL)
    {

        if (eqstri(*p, "to") || eqstri(*p, "from"))
            p++;
    }

    if (!*p)
        usage();


    if (*p)
        msg.attr |= (dword)FlavourToMsgAttr(**p);


    Process_AttReqUpd(&msg, msg.subj, TRUE);
}


    tflag = TFL_NONE;


        if (*filename == '^')
        {
            tflag = TFL_DEL;
            (void)strocpy(filename, filename + 1);
        }
        else if (*filename == '#')
        {
            tflag = TFL_TRUNC;
            (void)strocpy(filename, filename + 1);
        }
        else
            tflag = TFL_NONE;

            {
                struct _tosspath *tp, *lasttp;


                if (!tp)
                {
                    (void)sprintf(tname, "%s" PATH_DELIMS "%s", lasttp->path, filename);
                    filename = fixPath(tname);
                }
            }
        }


            if (msg->attr & MSGURQ)
            {
                SCOMBO sc;
                char szFname[PATHLEN];

                sc.ldate = 0;
                (void)strcpy(szFname, filename);

                do
                {
                    if (GEdate(&ff->scWdate, &sc))
                    {
                        (void)strcpy(szFname, ff->szName);
                        sc = ff->scWdate;
                    }
                } while (FindNext(ff) == 0);

                ExpandAndSend(msg, tflag, filename, pwd, szFname);
            }
            else
            {
                do
                {
                    ExpandAndSend(msg, tflag, filename, pwd, ff->szName);
                } while ((msg->attr & MSGFILE) && FindNext(ff) == 0);
            }

            FindClose(ff);
        }
    }
}


static void near ExpandAndSend(XMSG *msg, int tflag, char *szOrig, char *pwd, char *szNew)
{
    char *p;
    char temp[PATHLEN];


static void near Process_OneAttReqUpd(XMSG *msg, char *filename, int tflag, char *orig_fspec,
                                      char *pwd)
{
    FILE *updfile;
    struct stat statbuf;
    char fname[PATHLEN];
    char floname[PATHLEN];
    char temp[PATHLEN];
    char *p, *s;
    int fd;


    FloName(floname, &msg->dest, (byte)MsgAttrToFlavour(msg->attr), (config.flag & FLAG_ADDMODE));

    if (msg->attr & MSGFILE)
    {
        if (*filename)
        {
            if ((config.flag2 & FLAG2_QUIET) == 0)
                (void)printf(" (W/FILE %s%s)",
                             (tflag == TFL_DEL ? "DEL " : (tflag == TFL_TRUNC ? "TRUNC " : "")),
                             filename);

            if (!fexist(filename))
                S_LogMsg("!File attach `%s' does not exist!", filename);
        }


        if (tflag == TFL_DEL)
            *fname = '^';
        else if (tflag == TFL_TRUNC)
            *fname = '#';

        if (*pwd)
            sprintf(fname + strlen(fname), " !%s", pwd);
    }

        if ((fd = sopen(floname, O_CREAT | O_WRONLY | O_BINARY, SH_DENYNO, S_IREAD | S_IWRITE)) !=
            -1)
        {
            (void)close(fd);
        }


        if (msg->attr & MSGURQ)
        {
            if ((updfile = shfopen(filename, "r", O_RDONLY)) == NULL)
            {
                S_LogMsg("!Update file `%s' not found!", filename);
                statbuf.st_atime = 0L;
            }
            else
            {
                if (stat(filename, &statbuf) != 0)
                    (void)memset(&statbuf, '\0', sizeof(statbuf));

                (void)fclose(updfile);
            }


    (void)strcpy(temp, filename);

    if ((s = strrchr(temp, PATH_DELIM)) != NULL)
        (void)strocpy(temp, s + 1);


    if ((p = strpbrk(msg->subj, "?*:\\/")) != NULL)
        *p = '\0';
}


static word near FwdMatch(struct _fwdlist *fwd, NETADDR *o, XMSG *msg)
{
    if (!AddrMatchNS(o, &fwd->node))
        return FALSE;


        if (config.flag2 & FLAG2_KFFILE)
        {
            char temp[XMSG_SUBJ_SIZE + 80];
            char *p;

            *temp = '\0';


                if (*temp)
                    (void)strcat(temp, " ");


            (void)strncpy(msg->subj, temp, XMSG_SUBJ_SIZE - 1);
            msg->subj[XMSG_SUBJ_SIZE - 1] = '\0';
        }
    }

    return TRUE;
}

