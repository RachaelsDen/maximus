// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_hole.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#define NOVARS

static void near SetHpktName(char *hpname, char *setname)
{
    char temp[PATHLEN];
    char *from;

    strcpy(temp, FixOutboundName(0xffff));

    from = setname + strlen(temp);


    upper_fn(hpname);
}


void HoleAddPacket(char *name, BLIST far *bl)
{
    struct _hpkt *hpkt;

    NW(config);

    if (n_hpkt >= config.maxpkt)
    {
        TooManyPkts();
        return;
    }

    hpkt = hpl + n_hpkt++;

    hpkt->to.zone = bl->zone;
    hpkt->to.net = bl->net;
    hpkt->to.node = bl->node;
    hpkt->to.point = bl->point;

    hpkt->from = bl->ar->primary;

    SetHpktName(hpkt->name, name);
}

void HoleScanHole(void)
{
    struct _pkthdr hdr;
    struct _hpkt *hpkt;

    char hpath[PATHLEN];
    char fname[PATHLEN];

    FFIND *ff;

    int pfd;
    unsigned bytes;

    (void)strcpy(hpath, FixOutboundName(0xffff));

    (void)printf("Checking %s...\n\n", hpath);

    (void)strcpy(fname, hpath);
    (void)strcat(fname, "*.?ut");


        if (bytes != sizeof(struct _pkthdr))
            continue;

        (void)Adjust_Pkt_Header(&hdr);

        if (n_hpkt >= config.maxpkt)
        {
            TooManyPkts();
            continue;
        }

        hpkt = hpl + n_hpkt++;

        hpkt->from.zone = hdr.orig_zone;
        hpkt->from.net = (word)hdr.orig_net;
        hpkt->from.node = (word)hdr.orig_node;
        hpkt->from.point = hdr.orig_point;

        hpkt->to.zone = hdr.dest_zone;
        hpkt->to.net = (word)hdr.dest_net;
        hpkt->to.node = (word)hdr.dest_node;
        hpkt->to.point = hdr.dest_point;

        SetHpktName(hpkt->name, fname);

        switch (toupper(ff->szName[9]))
        {
        case 'C':
            hpkt->attr = MSGCRASH;
            break;
        case 'H':
            hpkt->attr = MSGHOLD;
            break;
        case 'D':
            hpkt->attr = MSGCRASH | MSGHOLD;
            break;

#ifdef DEBUG_HOLE
        (void)printf("%s: %hu:%hu/%hu.%hu -> %hu:%hu/%hu.%hu\n", GetHpktName(hpkt->name),
                     hpkt->from.zone, hpkt->from.net, hpkt->from.node, hpkt->from.point,
                     hpkt->to.zone, hpkt->to.net, hpkt->to.node, hpkt->to.point);
#endif
    } while (FindNext(ff) == 0);
}

void Hole_Read_Netmail_Area(void)
{
    struct _netinf *nm;
    XMSG xmsg;

    HMSG msgh;
    dword mn;
    byte trunc, del;

    if ((config.flag & FLAG_FRODO) == 0)
        return;

    (void)printf("\nScanning attaches in netmail area...\n");

    if ((netmail = MsgOpenArea(config.netmail->path, MSGAREA_CRIFNEC, config.netmail->type)) ==
        NULL)
    {
        (void)printf("Invalid netmail area: `%s'!\n", config.netmail->path);
        exit(ERL_ERROR);
    }

    for (mn = 1; mn <= MsgHighMsg(netmail); mn++)
        if ((msgh = MsgOpenMsg(netmail, MOPEN_READ, mn)) != NULL)
        {
            dword clen;
            byte *ctrl;
            byte *flag;

            if ((ctrl = malloc((word)(clen = (dword)(word)MsgGetCtrlLen(msgh)))) == NULL)
                clen = 0L;
            else
                clen = (dword)(word)MsgGetCtrlLen(msgh);

            if (MsgReadMsg(msgh, &xmsg, 0L, 0L, NULL, clen, ctrl) != (dword)-1)
            {
                trunc = del = FALSE;

                if ((flag = GetCtrlToken(ctrl, "FLAGS")) != NULL)
                {
                    if (strstr(flag, "TFS"))
                        trunc = TRUE;

                    if (strstr(flag, "KFS"))
                        del = TRUE;

                    if (strstr(flag, "DIR"))
                        xmsg.attr |= MSGCRASH | MSGHOLD;

                    MsgFreeCtrlToken(flag);
                }

                if (ctrl)
                    free(ctrl);


                if ((xmsg.attr & (MSGSENT | MSGFILE)) == MSGFILE)
                {
                    if (n_netmsg >= config.maxattach)
                    {
                        TooManyNetmsgs();
                        continue;
                    }

                    nm = netmsg + n_netmsg++;

                    nm->attr = xmsg.attr;
                    (void)NetaddrToSblist(&xmsg.orig, &nm->from);
                    (void)NetaddrToSblist(&xmsg.dest, &nm->to);

                    nm->name = sstrdup(xmsg.subj);

                    nm->trunc = trunc;
                    nm->del = del;

#ifdef DEBUG_HOLE
                    (void)printf("Msg #%3ld: %s from %s to ", mn, nm->name, Address(&xmsg.orig));

                    (void)printf("%s\n", Address(&xmsg.dest));
#endif
                }
            }
            else
            {
                if (ctrl)
                    free(ctrl);
            }

            (void)MsgCloseMsg(msgh);
        }

#ifdef DEBUG_HOLE
    {
        struct _hpkt *nm, *end;

        (void)printf("To recap:\n\n");

        for (nm = netinf, end = netmsg + n_netmsg; nm < end; nm++)
            (void)printf("%hu:%hu/%hu.%hu, %s\n", nm->to.zone, nm->to.net, nm->to.node,
                         nm->to.point, nm->name);
    }
#endif
}

void Hole_Free_Netmail_Area(void)
{
    NW(config);

    (void)MsgCloseArea(netmail);
}

word Hole_Add_To_Net(NETADDR *to, char *txt, int flavour)
{
    HMSG msgh;
    long msgattr;
    int attr_dir;

    XMSG msg;
    struct _netinf *nm, *end;

    char nul;
    char ctxt[120];

    int delete_sent;
    int trunc_sent;

    if ((config.flag & FLAG_FRODO) == 0)
        return 0;

    delete_sent = trunc_sent = attr_dir = FALSE;

    if (*txt == '^')
    {
        txt++;
        delete_sent = TRUE;
    }

    if (*txt == '#')
    {
        txt++;
        trunc_sent = TRUE;
    }

    msgattr = 0L;

    switch (flavour)
    {
    case 'C':
        msgattr |= MSGCRASH;
        break;

    case 'H':
        msgattr |= MSGHOLD;
        break;

    case 'D':
        msgattr &= ~(MSGCRASH | MSGHOLD);
        attr_dir = TRUE;
        break;

    default:

    for (nm = netmsg, end = netmsg + n_netmsg; nm < end; nm++)
    {
        if (eqstri(txt, nm->name) && AddrMatchNS(to, &nm->to))
        {
#ifdef DEBUG_HOLE
            (void)printf("%s matched %s - no action necessary.\n", txt, nm->name);
#endif

            return 0;
        }
    }


    (void)memset(&msg, '\0', sizeof(XMSG));

    (void)strcpy(msg.from, msgfrom);
    (void)strcpy(msg.to, "SysOp");
    (void)strcpy(msg.subj, txt);

    msg.attr = MSGLOCAL | MSGPRIVATE | MSGKILL | MSGFILE | msgattr;

    (void)SblistToNetaddr(config.addr, &msg.orig);

    msg.dest = *to;

    (void)Get_Dos_Date((union stamp_combo *)&msg.date_arrived);
    (void)Get_Dos_Date((union stamp_combo *)&msg.date_written);

    if ((msgh = MsgOpenMsg(netmail, MOPEN_CREATE, 0L)) == NULL)
    {
        S_LogMsg("!Err creating attach for %s", Address(to));
        return 0;
    }

    nul = '\0';
    *ctxt = '\0';

    if (delete_sent || trunc_sent || attr_dir)
    {
        (void)strcpy(ctxt, "\x01"
                           "FLAGS");

        if (delete_sent)
            (void)strcat(ctxt, " KFS");

        if (trunc_sent)
            (void)strcat(ctxt, " TFS");

        if (attr_dir)
            (void)strcat(ctxt, " DIR");

        (void)strcat(ctxt, "\x01");
    }

    if (MsgWriteMsg(msgh, FALSE, &msg, &nul, (dword)1, (dword)1, (dword)strlen(ctxt) + (dword)1,
                    ctxt) != 0)
    {
        S_LogMsg("!Err writing attach msg for %s", Address(to));
    }

    (void)MsgCloseMsg(msgh);

#ifdef DEBUG_HOLE
    (void)printf("Generated attach to %s of file %s\n", Address(to), txt);
#endif

        {
            char hpname[PATHLEN];

            strcpy(hpname, GetHpktName(hp->name));

            last = strrchr(hpname, '\\');

            if (last == NULL)
                last = strrchr(hpname, '/');

            if (last == NULL)
            {
                S_LogMsg("!Internal error - last=null, hpname=%s", hpname);
                exit(ERL_ERROR);
            }

        *hp->name = 0;
    }
}

void HoleRemoveFromList(char *name)
{
    struct _hpkt *hp;

    for (hp = hpl; hp < hpl + n_hpkt; hp++)
    {

        (void)memmove(hp, hp + 1, (n_hpkt - (word)(hp - hpl) - 1) * sizeof(struct _hpkt));
        n_hpkt--;
    }
}


void HoleRename(char *from, char *to)
{
    struct _hpkt *hp;

    for (hp = hpl; hp < hpl + n_hpkt; hp++)
    {
        if (!eqstri(GetHpktName(hp->name), from))
            continue;

        SetHpktName(hp->name, to);
        break;
    }
}

void HoleInitHole(void)
{
    if (!hpl)
    {
        hpl = smalloc(config.maxpkt * sizeof(struct _hpkt));
        n_hpkt = 0;
    }

    if (!netmsg)
    {
        if (config.flag & FLAG_FRODO)
            netmsg = smalloc(config.maxattach * sizeof(struct _hpkt));

        n_netmsg = 0;
    }
}

void HoleDeinitHole(void)
{
    word n;

    if (hpl)
    {

        free(hpl);
        hpl = NULL;
    }

    if ((config.flag & FLAG_FRODO) == 0)
        return;

    if (netmsg)
    {
        for (n = 0; n < n_netmsg; n++)
            if (netmsg[n].name)
                free(netmsg[n].name);

        free(netmsg);

        n_netmsg = 0;
        netmsg = NULL;
    }
}


void Hole_Nuke_Bundles(void)
{
    char hpath[PATHLEN];
    char fname[PATHLEN];
    char full[PATHLEN];
    FFIND *ff;
    char *ext;

    if ((config.flag & FLAG_FRODO) == 0)
        return;

    (void)strcpy(hpath, FixOutboundName(0xffff));
    (void)strcpy(fname, hpath);
    (void)strcat(fname, "*.*");

    if ((ff = FindOpen(fname, 0)) != NULL)
    {
        do
        {
            struct _netinf *nm, *end;

            char *strs[] = {"mo", "tu", "we", "th", "fr", "sa", "su", NULL};
            char **p;

            (void)upper_fn(ff->szName);


            if (*ext++ != '.')
                continue;


            if (!*p)
                continue;


            for (nm = netmsg, end = netmsg + n_netmsg; nm < end; nm++)
                if (stristr(nm->name, ff->szName))
                    break;


    fp=strrchr(mo->name, '.');
      
    if (fp==NULL)
      flav='F';
    else flav=(byte)toupper(fp[1]);
      
    while (fgets(temp, PATHLEN, flo))
    {
      Strip_Trailing(temp, '\n');
      
      config.flag |= FLAG_FRODO;

      if (Hole_Add_To_Net(&mo->found, temp, flav))
        (void)printf("Sent %s to %s\n", temp, Address(&mo->found));

      config.flag &= ~FLAG_FRODO;
    }
    
    (void)fclose(flo);
  }
  while (MatchOutNext(mo));

  MatchOutClose(mo);

  config.flag=flag;
}


void ArcToFlo(void)
{
  struct _netinf *nm;
  NETADDR to;
  
  if ((config.flag & FLAG_FRODO)==0)
    return;
  
  for (nm=netmsg; nm < netmsg+n_netmsg; nm++)
  {
    byte temp[PATHLEN];
    byte name[PATHLEN];
    byte flav;
    
    flav=(byte)
          ((nm->attr & MSGCRASH) ? 'C' : (nm->attr & MSGHOLD) ? 'H' : 'F');
    
    config.flag &= ~FLAG_FRODO;
    FloName(temp, SblistToNetaddr(&nm->to, &to), flav, FALSE);

    if (nm->trunc || nm->del)
    {
      name[0]=(byte)(nm->trunc ? '#' : '^');
      (void)strcpy(name+1, nm->name);
    }
    else (void)strcpy(name, nm->name);

    (void)Add_To_FloFile(name, NULL, temp);
    config.flag |= ~FLAG_FRODO;

    (void)printf("Sending %s to %s\n", nm->name, Address(&to));
  }
}

void KillArc(void)
{
  HAREA sq;
  HMSG msgh;
  XMSG msg;
  UMSGID uid;
  struct _cfgarea *ar=config.netmail;
  dword mn;
  
  if ((sq=MsgOpenArea(ar->path, MSGAREA_NORMAL, ar->type))==NULL)
  {
    (void)printf("Error opening netmail area\n");
    return;
  }
  
  for (mn=1L; mn <= MsgHighMsg(sq); mn++)
  {
    if ((msgh=MsgOpenMsg(sq, MOPEN_READ, mn))==NULL)
      continue;

    MsgReadMsg(msgh, &msg, 0L, 0L, NULL, 0L, NULL);
    MsgCloseMsg(msgh);
    
    if (!eqstr(msg.from, "ARCmail"))
      continue;

    (void)printf("Nuked #%ld, to %s, re: %s\n", mn, Address(&msg.dest),
                 msg.subj);
    
    uid=MsgMsgnToUid(sq, mn);
    MsgKillMsg(sq, mn);
    mn=MsgUidToMsgn(sq, uid, UID_PREV);
  }
  
  MsgCloseArea(sq);
}

#endif
