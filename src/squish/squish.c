// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: squish.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)


struct _config config;
word mode;

static time_t start;
static word old_emax;
static int fRunZCore = FALSE;

static struct _args ar = {"", "squish.cfg", "", "", "", TRUE, ACTION_NONE, FALSE, {NULL}, 0};

#ifdef __TURBOC__
unsigned int __stklen = 32767;
#endif

#ifdef DJ
FILE *dj;
#endif

int _stdc main(int argc, char *argv[])
{
    char *p;

    NW(__fd2n);

#if !defined(UNIX)
#if defined(__FLAT__)
    Hello("SQUISH/386", "SquishMail Conference Processor", version, "1990, " THIS_YEAR);
#else
    Hello("SQUISH", "SquishMail Conference Processor", version, "1990, " THIS_YEAR);
#endif
#else
    Hello("SQUISH/UNIX", "SquishMail Conference Processor", version, "1990, " THIS_YEAR);
#endif

#endif

#ifdef DJ
    dj = fopen("dj.log", "a");
#endif

    if (!fexist(ar.cfgname) && (p = getenv("SQUISH")) != NULL)
        (void)strcpy(ar.cfgname, p);

#if defined(__MSDOS__) && !defined(__FLAT__)
    install_24();
    (void)atexit(uninstall_24);
#endif

    if (argc < 2)
        usage();

    Initialize_Variables();

        (void)strcpy(ar.cfgname, p);



    Parse_Areas(*ar.areasbbs ? ar.areasbbs : config.areasbbs);


    if (ar.action == ACTION_GET || ar.action == ACTION_SEND || ar.action == ACTION_UPDATE ||
        ar.action == ACTION_POLL)
    {
        config.flag &= ~FLAG_ADDMODE;
        HandleAttReqPoll(ar.action, ar.toscan);
    }
    else
        SquishSquashCycle();

#ifdef DJ
    if (dj)
        fclose(dj);
#endif

    CleanupConfig();

    (void)printf("\n" SQNAME ": Done!\n");

    return (erl_max    ? ERL_MAXMSGS
            : erl_echo ? ERL_TOSS_ECHO
            : erl_net  ? ERL_TOSS_NET
            : erl_sent ? ERL_SENT_ECHO
                       : ERL_NONE);
}

static void near InitializeConfig(void)
{
    struct _minf minf;


    do
    {
        HoleDeinitHole();
        HoleInitHole();

        if (mode & (MODE_scan | MODE_pack))
            HoleScanHole();

        old_emax = erl_max;


        if (mode == 0 || (mode & MODE_toss))
            Toss_Messages(ar.echotoss, old_emax, start);


            cflag = config.flag;
            config.flag &= ~FLAG_ONEPASS;

            Scan_Messages(*ar.echotoss ? ar.echotoss : NULL,
                          ar.action == ACTION_RESCAN ? &ar.n : NULL, start);


            config.flag = cflag;
        }


        if (erl_max && (mode & MODE_sp) == MODE_sp)
        {
                (void)strcpy(ags->logfile, *arg + 2);
                break;

            case 's':
                (void)strcpy(ags->sched, *arg + 2);
                mode |= MODE_pack;
                break;

            case 't':
                config.flag ^= FLAG_SECURE;
                break;

            case 'u':
                config.flag ^= FLAG_TOSSBAD;
                break;

            case 'o':
                ags->do_pack = FALSE;
                break;

            case 'q':
                config.flag2 |= FLAG2_QUIET;
                break;

#if 0
      case 'x':
        mode=MODE_pack;

        switch(tolower((*arg)[2]))
        {
          case 'f':
            convert=CVT_FLO;
            break;
            
          case 'a':
            convert=CVT_ARC;
            break;
            
          case 'k':
            convert=CVT_KILL;
            break;

          case 's':
            convert=CVT_SFLO;
            break;
        }
        break;
#endif

            case 'v':
                config.flag ^= FLAG_STATS;
                break;

            case 'z':
                config.flag2 |= FLAG2_NPTHRU;
                break;

            default:
                (void)printf(unknown_opt, *arg);
                exit(ERL_ERROR);
            }
    }
}

#if 0

#define RDLEN 8192

static void near test_harness(char *name)
{
  MSGH *msgh;
  long tl;

  char lastfrom[36]="";
  static char temp[100];
  static char ctext[1000];
  char *p;

  MSG *sq;

  XMSG msg,
       msg2,
       rmsg;

  char *rd;

  if ((rd=malloc(RDLEN))==NULL)
  {
    printf("no memory.\n");
    exit(ERL_ERROR);
  }

  memset(&msg,'\0',sizeof(XMSG));
  memset(&msg2,'\0',sizeof(XMSG));

  Get_Dos_Date((union stamp_combo *)&msg.date_arrived);
  Get_Dos_Date((union stamp_combo *)&msg.date_written);

  strcpy(msg.from,"Scott Dudley");
  strcpy(msg.to,"Test");
  strcpy(msg.subj,"This is a test!");

  strcpy(msg2.from,"Maximus-CBCS");
  strcpy(msg2.to,"Fido");
  strcpy(msg2.subj,"Bad dog!");

  msg.attr=MSGLOCAL;
  msg2.attr=MSGLOCAL;

  if ((sq=MsgOpenArea(*name=='!' ? name+1 : name,
                      MSGAREA_NORMAL,
                      *name=='!' ? MSGTYPE_SDM : MSGTYPE_SQUISH))==NULL)
  {
    printf("\aError opening SquishFile!\n");

    printf("Create? ");

    fgets(temp, 100, stdin);

    if (*temp=='Y' || *temp=='y')
    {
      if ((sq=MsgOpenArea(*name=='!' ? name+1 : name,
                      MSGAREA_CRIFNEC,
                      *name=='!' ? MSGTYPE_SDM : MSGTYPE_SQUISH))==NULL)
      {
        printf("\aError opening SquishFile!\n");
        exit(ERL_ERROR);
      }
    }
    else exit(ERL_ERROR);
  }

  MsgLock(sq);

  for (;;)
  {
    printf("SQ> ");

    fgets(temp,100,stdin);

    switch (tolower(*temp))
    {
      case 'r':
        if (temp[1]=='e')
          goto ReplyMsg;
        else if (temp[1]=='n')
          tl=MSGNUM_next;
        else tl=MSGNUM_previous;

        if ((msgh=MsgOpenMsg(sq,MOPEN_READ,tl))==NULL)
        {
          printf("Not found.\n");
          break;
        }

ReadText:
        if (MsgReadMsg(msgh,&rmsg,0L,RDLEN,rd,999L,ctext)==-1)
          printf("Error reading message.\n");
        else
        {
          printf("From: %-20s (%u:%d/%d.%u)  Date: %s\n"
                 "  To: %-20s (%u:%d/%d.%u)\n"
                 "Subj: %s\n"
                 "This: %ld (uid=%ld), Down: %ld (uid=%ld), Up: %ld (uid=%ld)\n\n",
                 rmsg.from,
                 rmsg.orig.zone,
                 rmsg.orig.net,
                 rmsg.orig.node,
                 rmsg.orig.point,
                 sc_time((union stamp_combo *)&rmsg.date_written,temp),
                 rmsg.to,
                 rmsg.dest.zone,
                 rmsg.dest.net,
                 rmsg.dest.node,
                 rmsg.dest.point,
                 rmsg.subj,
                 MsgCurMsg(sq),
                 MsgMsgnToUid(sq,MsgCurMsg(sq)),
                 MsgUidToMsgn(sq,rmsg.replyto,UID_EXACT),
                 rmsg.replyto,
                 MsgUidToMsgn(sq,rmsg.replies[0],UID_EXACT),
                 rmsg.replies[0]);

          strcpy(lastfrom,rmsg.from);
          p=rd;

          while ((p=strchr(p,'\r')) != NULL)
          {
            memmove(p+2,p+1,strlen(p+1)+1);
            p[1]='\n';

            p += 2;
          }

          fprintf(stdout, "%s", rd);

          printf("\n");
          
          printf("ctext:\n---%s---\n",ctext);
        }

        MsgCloseMsg(msgh);
        break;

ReplyMsg:
        msg.replyto=MsgMsgnToUid(sq,MsgCurMsg(sq));
        strcpy(msg.to,lastfrom);

        if ((msgh=MsgOpenMsg(sq,MOPEN_RW,MsgCurMsg(sq)))==NULL)
          printf("Can't open message!\n");
        else
        {
           if (MsgReadMsg(msgh,&rmsg,0L,0L,NULL,0L,NULL) != -1)
           {
             rmsg.attr &= ~(MSGPRIVATE|MSGREAD);

             if (MsgWriteMsg(msgh,FALSE,&rmsg,NULL,0L,0L,0L,NULL)==-1)
               printf("Can't write message!\n");
             else printf("Done.\n",MsgHighMsg(sq));
           }

          MsgCloseMsg(msgh);
        }
       break;

     case 's':
        printf("Curmsg=%ld, Nummsg=%ld\n",MsgCurMsg(sq),MsgNumMsg(sq));
        break;

      case 'k':
        printf("Message #%d was %skilled okay.\n",atoi(temp+1),
               MsgKillMsg(sq,atoi(temp+1))==0 ? "" : "NOT ");
        break;

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        if ((msgh=MsgOpenMsg(sq,MOPEN_READ,atol(temp)))==NULL)
        {
          printf("Goto was unsuccessful.\n");
          break;
        }
        goto ReadText;

      case 'q':
        goto done;

      case 'l':
        while ((msgh=MsgOpenMsg(sq,MOPEN_READ,MSGNUM_next)) != NULL)
        {
          if (MsgReadMsg(msgh,&msg,0L,0L,NULL,0L,NULL)==-1)
            printf("Error reading message.\n");
          else printf("#%-3ld Fm: %-15.15s  To: %-15.15s  Subj: %-25.25s\r\n",
                      MsgCurMsg(sq),msg.from,msg.to,msg.subj);

          MsgCloseMsg(msgh);
        }
        break;
    }
  }

done:

  MsgUnlock(sq);

  MsgCloseArea(sq);
  free(rd);
}

#ifdef DMALLOC
long core(void)
{
#ifdef __WATCOMC__
  unsigned long cdecl coreleft(void);
  printf("\r%ld\n",(long)coreleft());
  return ((long)coreleft());
#else
  return 0L;
#endif
}
#endif

