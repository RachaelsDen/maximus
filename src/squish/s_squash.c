// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_squash.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#define NOVARS

#include "s_squash.h"
#include "alc.h"
#include "max.h"
#include "msgapi.h"
#include "prog.h"
#include "squish.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <process.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef UNIX
#include <errno.h>
#endif


static struct _arcinfo *near Get_Archiver_Index(NETADDR *a)
{
    struct _arcinfo *ai;
    struct _sblist *pack;

    for (ai = config.arc; ai; ai = ai->next)
        for (pack = ai->nodes; pack; pack = pack->next)
            if (AddrMatchNS(a, pack))
                return ai;


    (void)strcpy(del, arcname);

    if ((dot = strrchr(del, '.')) != NULL)
    {
        for (x = 0; x < 7; x++)
        {

                    (void)strcpy(temp, del);

                    if (ff->ulSize == 0L && (p = strrchr(temp, PATH_DELIM)) != NULL)
                    {
                        (void)strcpy(p + 1, ff->szName);
                        (void)unlink(temp);
                    }
                } while (FindNext(ff) == 0);

                FindClose(ff);
            }
        }
    }

    if (via && !MatchNN(found, via, FALSE))
        (void)sprintf(temp, ", via %s", Address(via));
    else
        *temp = '\0';

    if ((config.flag & FLAG_QUIETARC) == 0)
        (void)printf("\n");

    (void)printf("Packet for %s%s (%ld bytes) - Method: %s\n", Address(found), temp, fsize(pktname),
                 ai->arcname);

    S_LogMsg(" %sing mail for %s (%ld bytes)%s", ai->arcname, Address(found), fsize(pktname), temp);

    arcret = CallExtern(cmd, TRUE);

    if (arcret == 0 && !fexist(arcname) && fexist(pktname))
    {
        arcret = -1;
        errno = 0;
        S_LogMsg("!Compressed bundle not found after calling archiver!");
        rc = FALSE;
    }

    if (arcret != 0)
    {
        HandleArcRet(arcret, cmd);

        (void)sprintf(temp, "%s%08lx.out", FixOutboundName(0xffff), get_unique_number());

        if (rename(pktname, temp) == 0)
            S_LogMsg("!Packet %s moved back to %s", pktname, temp);
        else
            S_LogMsg("!Couldn't rename %s back to %s", pktname, temp);

        rc = FALSE;
    }
    else
    {
        (void)unlink(pktname);
    }

    return rc;
}

int Merge_Pkts(byte *from, byte *to)
{
    byte *copybuf;

    int fromfile, tofile;
    unsigned got, dont_unlink;
    word tempint;

    if (eqstri(from, to))
        return 0;


    if (!fexist(to))
    {
        if (rename(from, to) == 0)
            return 0;
    }

    if ((fromfile = sopen(from, O_RDONLY | O_BINARY, SH_DENYNO, S_IREAD | S_IWRITE)) == -1)
        return -1;

    if ((tofile = open(to, O_RDWR | O_BINARY, SH_DENYNO, S_IREAD | S_IWRITE)) == -1 ||
        lseek(tofile, -(long)sizeof(word), SEEK_END) == -1 ||
        read(tofile, (char *)&tempint, (unsigned)sizeof(word)) != (int)sizeof(word) ||
        tempint != 0 || (copybuf = malloc(COPYSIZE)) == NULL)
    {
        if (tofile != -1)
            (void)close(tofile);

        (void)close(fromfile);
        return -1;
    }


    (void)lseek(tofile, -(long)sizeof(word), SEEK_END);
    (void)lseek(fromfile, (long)sizeof(struct _pkthdr), SEEK_SET);

    dont_unlink = FALSE;

    while ((got = (unsigned)fastread(fromfile, copybuf, (unsigned)COPYSIZE)) != 0 &&
           got != (unsigned)-1)
    {
        if (fastwrite(tofile, copybuf, got) != (int)got)
        {
            S_LogMsg("!Error copying %s to %s", from, to);
            dont_unlink = TRUE;
            break;
        }
    }


    free(copybuf);

    (void)close(tofile);
    (void)close(fromfile);

    if (!dont_unlink && unlink(from) == -1)
        return -1;

    return 0;
}

static void near Add_To_Flo(FILE *flo, byte *txt)
{
    char temp[PATHLEN];
    char wrd[PATHLEN];
    byte *p;


    while (fgets(temp, PATHLEN, flo) != NULL)
    {
        (void)Strip_Trailing(temp, '\n');


        if (!*temp)
            continue;


        (void)getword(p, wrd, " ,;\t\n!", 1);

        if (eqstri(wrd, txt + ((*txt == '#' || *txt == '^') ? 1 : 0)))
            return;
    }


    (void)fseek(flo, 0L, SEEK_END);


    if (*txt)
        (void)fprintf(flo, "%s\n", txt);
}

int Add_To_FloFile(byte *fmtxt, byte *from, byte *to)
{
    char temp[PATHLEN];
    FILE *fromfile = NULL;
    FILE *tofile;
    byte *mode, *p;
    long fs_to;

    fs_to = fsize(to);

    if (from && (fromfile = shfopen(from, "r", O_RDONLY | O_NOINHERIT)) == NULL)
    {
        S_LogMsg("!Can't open %s", from);
        return -1;
    }

    if (fexist(to))
        mode = "r+";
    else
        mode = "w+";

    if ((tofile = shfopen(to, mode, O_RDWR | O_CREAT | O_NOINHERIT)) == NULL)
    {
        if (fromfile)
            (void)fclose(fromfile);

        S_LogMsg("!Can't write to %s", to);
        return -1;
    }


    if (fs_to > 0L)
    {

    if (!from)
        Add_To_Flo(tofile, fmtxt);
    else
    {
        while (fgets(temp, sizeof(temp), fromfile))
        {
            (void)Strip_Trailing(temp, '\n');


            if (!*temp)
                continue;

            Add_To_Flo(tofile, temp);
        }
    }

    (void)fclose(tofile);

    if (!from)
        return 0;

    (void)fclose(fromfile);

    if (unlink(from) == 0)
        return 0;

    S_LogMsg("!Err merging `%s' into `%s'", from ? from : fmtxt, to);
    return -1;
}

void FloName(byte *out, NETADDR *n, byte flavour, word addmode)
{
    FFIND *ff;
    byte *flavptr;
    byte flav, foundflav;

    NW(config);

    flav = (flavour == 'O' ? (byte)'F' : flavour);

    MakeOutboundName(n, out);
    flavptr = out + strlen(out);

    flavptr[0] = (byte)(addmode ? '?' : flav);
    flavptr[1] = 'l';
    flavptr[2] = 'o';
    flavptr[3] = '\0';


    if (addmode)
    {
        if ((ff = FindOpen(out, 0)) != NULL)
        {

            *flavptr = flav;


            do
            {
                foundflav = (byte)toupper(ff->szName[strlen(ff->szName) - 3]);


            *flavptr = flav;
        }
    }
}

static void near OutName(byte *out, NETADDR *n, byte flavour)
{
    MakeOutboundName(n, out);
    out += strlen(out);

    *out++ = flavour;
    *out++ = 'u';
    *out++ = 't';
    *out = '\0';
}


static void near Change_Style(NETADDR nn[], unsigned num, byte from, byte to)
{
    MATCHOUT *mo;

    char temp[PATHLEN];
    byte *p;

    unsigned i;

    for (i = 0; i < num; i++)
    {
        if (from == 'L' || from == 'U')
            mo = MatchOutOpen(&nn[i], MATCH_ALL, from);
        else
            mo = MatchOutOpen(&nn[i], MATCH_FLO | MATCH_OUT, from);

        if (!mo)
            continue;

        do
        {

            if ((p = strrchr(temp, '.')) != NULL)
            {
                switch (to)
                {

                    if (p[1] == 'P')
                        break;

                case 'D':
                case 'H':
                case 'F':
                case 'O':

                    if (toupper(p[2]) == 'U' && p[1] == 'F')
                        p[1] = 'O';
                    break;

                default:

                    HoleRename(mo->name, temp);
                }
            }

            BusyFileClose(mo->name);
        } while (MatchOutNext(mo));

        MatchOutClose(mo);
    }
}

static void near RV_Leave(byte *line, byte *ag[], NETADDR nn[], word num)
{
    NW(ag);
    NW(line);

    if (config.flag & FLAG_FRODO)
    {
        NotForFrodo("Leave");
        return;
    }

    Change_Style(nn, num, (byte)'U', (byte)'L');
}

static void near RV_Unleave(byte *line, byte *ag[], NETADDR nn[], word num)
{
    NW(ag);
    NW(line);

    if (config.flag & FLAG_FRODO)
    {
        NotForFrodo("Unleave");
        return;
    }

    Change_Style(nn, num, (byte)'L', (byte)'U');
}

static void near RV_Change(byte *line, byte *ag[], NETADDR nn[], word num)
{
    NW(line);

    if (config.flag & FLAG_FRODO)
    {
        NotForFrodo("Change");
        return;
    }

    if (!*ag[2])
    {
        S_LogMsg("!Line %d of route cfg: need 2 flavours and at least 1 node", linenum);
        return;
    }

    Change_Style(nn, num, Get_Routing_Flavour(ag, 1, TRUE), Get_Routing_Flavour(ag, 2, TRUE));
}


        if (fexist(scratch))
        {
#ifdef DEBUG_ROUTE
            S_LogMsg("@%s exists: no PollGen", scratch);
#endif
        }
        else
        {
            if ((fd = sopen(scratch, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_DENYNONE,
                            S_IREAD | S_IWRITE)) == -1)
            {
                S_LogMsg("!Err creating `%s'", scratch);
                continue;
            }

            if (express)
                Generate_Dummy_Pkt(fd, config.addr, &nn[node]);

            (void)close(fd);
        }
    }
}


static void near Unique_ArcName(byte *base, byte *arcname)
{
    char temp[PATHLEN];
    char tmpname[PATHLEN];
    static byte pspspc[] = "%s%s%c";
    byte *ext;

    FFIND *ff;

    struct tm *lt;
    SCOMBO fdate, today;
    time_t longt;
    unsigned long fsiz;
    int high, add, i;

#if 0
  int arcm_num = 10;
  char arcm_letters[]="0123456789";
#else
    int arcm_num = 36;
    char arcm_letters[] = "0123456789abcdefghijklmnopqrstuvwxyz";
#endif



        (void)sprintf(temp, pspspc, base, ext, arcm_letters[add]);

            fdate.ldate = 0L;
        }
        else
        {

        if (fsiz != (dword)-1 && add > high)
            high = add;


        if (fsiz > 0L && fdate.dos_st.date == today.dos_st.date)
        {

            if (config.max_archive == 0 || fsiz / 1000 <= config.max_archive)
            {
                (void)strcpy(arcname, temp);
                return;
            }
        }
    }


    if (high != -1 && high < arcm_num - 1)
    {
        (void)sprintf(arcname, pspspc, base, ext, arcm_letters[high + 1]);
        return;
    }


    (void)sprintf(temp, "%s%s%c", base, ext, '?');

    if ((ff = FindOpen(temp, 0)) != NULL)
    {
        do
        {
            (void)sprintf(tmpname, "%s%s%c", base, ext, ff->szName[strlen(ff->szName) - 1]);

            if (fsize(tmpname) == 0L)
                (void)unlink(tmpname);
        } while (FindNext(ff) == 0);

        FindClose(ff);
    }


    for (i = 0; i < arcm_num; i++)
    {
        (void)sprintf(arcname, pspspc, base, ext, arcm_letters[i]);

        if (!fexist(arcname))
            break;
    }
}

unsigned long get_unique_number(void)
{
    static time_t last_time = 0L;
    static unsigned ctr = 0;
    time_t now;

    now = time(NULL);


        if (ctr++ == 15)
        {
            while (last_time == time(NULL))
                ;

            now = time(NULL);
            ctr = 0;
        }
    }

    last_time = now;
    now = (now << 4) + (time_t)ctr;
    return now;
}


static sword near Unique_Pktname(byte *outname, byte *pktname, NETADDR *found)
{
    NW(found);


static void near MustSpecOne(void)
{
    S_LogMsg("!Err line %d of route file:  Must specify at least 1 node", linenum);
}


    if (config.flag2 & FLAG2_NOSTOMP)
        return;


    if (read(fd, (char *)&phold, sizeof phold) == (int)sizeof(phold))
    {

        ph.orig_zone = ph.qm_orig_zone = phold.orig_zone;

        if (*ph.password || (phold.dest_zone == ph.dest_zone &&
                             (!check_point || phold.dest_point == ph.dest_point) &&
                             phold.dest_zone == ph.dest_zone && *phold.password == '\0'))
        {
    word nod, an;

    byte flavour;

    NW(line);

        else if (eqstri(ag[an], "noarc"))
            noarc = TRUE;
        else
            break;

    flavour = Get_Routing_Flavour(ag, 1, TRUE);

    if (!*ag[an])
    {
        MustSpecOne();
        return;
    }

    for (nod = 0; nod < num; nod++)
    {
        NETADDR nop;

        mo = MatchOutOpen(&nn[nod], MATCH_OUT | MATCH_FLO, 'F');

        if (!mo)
            continue;

        do
        {
            nop = mo->found;
            nop.point = 0;

            if (mo->found.point != 0 && nn[nod].point == POINT_ALL && !DestIsHereA(&nop) &&
                (config.flag2 & FLAG2_BINKPT))
            {

                mo->found.point = 0;


            if (BusyFileOpenNN(&mo->found, FALSE) == -1)
            {

                S_LogMsg(bsy_pkt_queued, mo->name);
                HoleRemoveFromList(mo->name);
                continue;
            }


                    if (mo->fFromHole)
                        mo->hpkt++;
                }
                else
                {

                MakeArcBase(temp, &mo->found);


                if (Unique_Pktname(mo->name, temp, &mo->found) != -1)
                {
                    HoleRemoveFromList(mo->name);

                    if (Add_To_Archive(arcname, &mo->found, temp, NULL))
                    {

                        (void)strocpy(arcname + 1, arcname);
                        *arcname = '#';


    flavour = Get_Routing_Flavour(ag, 1, TRUE);


    host = nn[0];

    if (host.zone == ZONE_ALL)
        host.zone = config.def.zone;

    if (host.net == NET_ALL)
        host.net = config.def.net;

    if (host.node == NODE_ALL)
        host.node = config.def.node;

    if (host.point == POINT_ALL)
        host.point = 0;

    for (nod = 0; nod < num; nod++)
    {
        mo = MatchOutOpen(&nn[nod], MATCH_OUT | MATCH_FLO, 'F');


            if (BusyFileOpenNN(&host, FALSE) == -1)
            {
                S_LogMsg(bsy_pkt_queued, mo->name);
                HoleRemoveFromList(mo->name);
                continue;
            }


                BusyFileCloseNN(&host);

                S_LogMsg(bsy_pkt_queued, mo->name);
                HoleRemoveFromList(mo->name);
                continue;
            }

            if (!hostroute)
                dest = host;
            else
            {
                dest.zone = mo->found.zone;
                dest.net = mo->found.net;
                dest.node = 0;
                dest.point = 0;
            }


                if ((AddrMatch(&host, &mo->found) || fil) && (config.flag & FLAG_FRODO) == 0)
                {

                    if (AddrMatch(&host, &mo->found) && (flavour == 'F' || flavour == 'O'))
                        ;
                    else
                    {
                        FloName(temp, &dest, flavour, config.flag & FLAG_ADDMODE);

                        (void)Add_To_FloFile(NULL, mo->name, temp);
                    }
                }
            }
            else if (noarc)
            {

                StompPacketHeader(mo->name, &host, FALSE);

                if (!eqstri(mo->name, temp))
                {
                    (void)Merge_Pkts(mo->name, temp);
                    HoleRemoveFromList(mo->name);
                }
            }

                MakeArcBase(temp, &dest);


                StompPacketHeader(mo->name, &host, FALSE);


                        if ((config.flag & FLAG_FRODO) == 0)
                            FloName(temp, &dest, flavour, (config.flag & FLAG_ADDMODE));


                        if (config.flag & FLAG_FRODO)
                            (void)Hole_Add_To_Net(&dest, arcname, flavour);
                        else
                            (void)Add_To_FloFile(arcname, NULL, temp);
                    }
                }
            }


            BusyFileCloseNN(&host);

        } while (MatchOutNext(mo));

        MatchOutClose(mo);
    }
}


static void near RV_GateRoute(byte *line, byte *ag[], NETADDR nn[], word num)
{
    MATCHOUT *mo;

    struct _pktprefix pp;
    struct _pkthdr ph;

    char intlstr[PATHLEN];
    char outfn[PATHLEN];
    byte *orig, *buf, *p;

    int infile = -1, outfile = -1;
    int first, got, intllen, num_str, flavour, x;

#define RDBUFSIZE 2048

    NW(line);

    if (!*ag[1])
    {
        S_LogMsg("!Line %d of route file: must specify at least 1 node", linenum);
        return;
    }

    flavour = Get_Routing_Flavour(ag, 1, TRUE);


        mo = MatchOutOpen(&nn[x], MATCH_OUT, 'F');

        while (mo)
        {

            if (tell(outfile) != 0L)
                lseek(outfile, -2L, SEEK_END);
            else
            {
                Fill_Out_Pkthdr(&ph, config.addr, nn[0].zone, nn[0].net, nn[0].node, nn[0].point);

                fastwrite(outfile, (char *)&ph, sizeof(struct _pkthdr));
            }


                fastwrite(outfile, (char *)&pp, sizeof(struct _pktprefix));

                num_str = 0;

                if ((orig = malloc(RDBUFSIZE + intllen + intllen)) == NULL)
                    break;

                first = TRUE;

                while ((got = fastread(infile, orig, RDBUFSIZE)) > 0 && num_str <= 4)
                {
                    buf = orig;

                    if (num_str == 4 && first)
                    {
                        if (!memstr(buf, intlstr, got, intllen))
                        {
                            (void)memmove(buf + intllen + 1, buf, got);
                            (void)memmove(buf, intlstr, intllen);
                            buf[intllen] = '\r';

                            buf += intllen + 1;
                        }

                        first = FALSE;
                    }

                    if ((p = memchr(buf, '\0', got)) != NULL)
                    {
                        num_str++;
                        p++;
                    }
                    else
                        p = buf + got;

                    fastwrite(outfile, orig, (int)(p - orig));


            x = 0;
            fastwrite(outfile, (char *)&x, 2);
            close(outfile);

            close(infile);


            unlink(mo->name);

            BusyFileClose(mo->name);



    if (tag && *tag)
    {
        if (eqstri(args[1], tag))
            Exec_Sched(args[1]);
        else
        {
#ifdef DEBUG_ROUTE
            (void)printf("@Skipping schedule %s due to cmd-line override.\n", args[1]);
#endif

            Skip_To_Next_Sched(in);
        }

        return;
    }

    for (s = strtok(args[2], "|"); s; s = strtok(NULL, "|"))
    {
    {
#ifdef DEBUG_ROUTE
        (void)printf("@Skipping schedule %s due to day-of-week.\n", args[1]);
#endif

        Skip_To_Next_Sched(in);
        return;
    }


    if (*args[3] == '\0' || *args[4] == '\0')
        doit = TRUE;
    else
        doit = FALSE;


    if (etime < btime)
    {
        if (ctime < etime || ctime >= btime)
            doit = TRUE;
    }
    else
    {
        if (ctime >= btime && ctime < etime)
            doit = TRUE;
    }

    if (doit)
        Exec_Sched(args[1]);
    else
    {
#ifdef DEBUG_ROUTE
        (void)printf("@Skipping schedule %s due to time.\n", args[1]);
#endif

        Skip_To_Next_Sched(in);
    }
}

static word near TokDelim(byte ch)
{
    return (ch == ' ' || ch == '\t' || ch == ',' || ch == '\\' || ch == '/' || ch == ':' ||
            ch == '\0' || ch == '.' || ch == '\r' || ch == '\n');
}

static void near ProcessDefToken(byte *str, struct _defn *def)
{
    byte *s;
    unsigned toklen = strlen(def->name);
    unsigned replen = strlen(def->xlat);

    while ((s = stristr(str, def->name)) != NULL)
    {

            if (strlen(s) + replen - toklen >= MAX_ROUTE_LINELEN - 5)
            {
                S_LogMsg("!Define macro expansion is too long");
                break;
            }

            (void)memmove(s + replen, s + toklen, strlen(s + toklen) + 1);
            (void)memmove(s, def->xlat, strlen(def->xlat));
        }
            str = s + 1;
        }
    }
}

static void near ProcessDefines(byte *s)
{
    struct _defn *def;

    for (def = defns; def; def = def->next)
        ProcessDefToken(s, def);
}

void Munge_Outbound_Area(byte *cfgname, byte *tag)
{
    static struct _verbtable
    {

        void(near *vp)(byte *line, byte *ag[], NETADDR n[], word num);


        sword slush_at;

    } cv[] = {{"send", RV_Send, 2, 3},
              {"route", RV_Route, 2, 3},
              {"leave", RV_Leave, 2, 2},
              {"unleave", RV_Unleave, 2, 2},
              {"change", RV_Change, 4, 4},
              {"poll", RV_Poll, 2, -1},
              {"hostroute", RV_Route, 2, 3},
              {"define", RV_Define, (unsigned)-1, -1}};

    static byte *args[MAX_ROUTE_ARGS];

    static NETADDR n[MAX_ROUTE_NODES];
    NETADDR d;

    FILE *cfgfile;

    byte in[MAX_ROUTE_LINELEN];
    byte temp[MAX_ROUTE_LINELEN];
    byte *p;

    word num;
    unsigned i, arg, v;

    defns = NULL;

    if (config.flag & FLAG_FRODO)
        Hole_Read_Netmail_Area();

    if (config.flag2 & FLAG2_NUKE)
        Hole_Nuke_Bundles();

    (void)printf("\nScanning outbound areas...\n\n");

    Check_Outbound_Areas();

#if 0
  if (convert)
  {
    switch(convert)
    {
      case CVT_FLO:   FloToArc();   break;
      case CVT_ARC:   ArcToFlo();   break;
      case CVT_KILL:  KillArc();    break;
      case CVT_SFLO:  OutToSflo();  break;
    }

    return;
  }
#endif

    if ((cfgfile = shfopen(cfgname, "rb", O_RDONLY | O_BINARY | O_NOINHERIT)) == NULL)
        ErrOpening("config", cfgname);

    for (i = 0; i < MAX_ROUTE_ARGS; i++)
        if ((args[i] = malloc(MAX_ROUTE_LEN)) == NULL)
            NoMem();

    for (linenum = 1; fgets(in, MAX_ROUTE_LINELEN, cfgfile); linenum++)
    {
        if (*in == '\x1a')
            break;

        (void)Strip_Trailing(in, '\r');
        (void)Strip_Trailing(in, '\n');
        (void)Strip_Trailing(in, '\r');
        (void)Strip_Trailing(in, '\x1a');

        if ((p = strchr(in, ';')) != NULL || (p = strchr(in, '%')) != NULL)
            *p = '\0';

        ProcessDefines(in);

        for (arg = 0; arg < MAX_ROUTE_ARGS; arg++)
        {
            (void)getword(in, args[arg], routedelim, (int)(arg + 1u));

            if (!*args[arg])
                break;
        }

        if (!*args[0] || *args[0] == '\x1a')
            continue;

        for (v = 0; v < cvlen; v++)
            if (eqstri(args[0], cv[v].verb))
            {

                    d.zone = config.addr->zone;
                    d.net = config.addr->net;
                    d.node = config.addr->node;
                    d.point = 0;

                    for (i = cv[v].np_at; i < MAX_ROUTE_ARGS; i++)
                    {

                        if (!*temp)
                            break;
                        else if (isdigit(*temp) || *temp == '.' ||
                                 strnicmp(temp, "world", 5) == 0 || strnicmp(temp, "all", 3) == 0)
                        {


    {
        struct _defn *def, *next;

        for (def = defns; def; next = def->next, free(def), def = next)
        {
            free(def->xlat);
            free(def->name);
        }
    }

    for (i = 0; i < MAX_ROUTE_ARGS; i++)
        free(args[i]);

    (void)fclose(cfgfile);

    if (config.flag & FLAG_FRODO)
        Hole_Free_Netmail_Area();

    (void)printf("\n");
}


    for (pob = config.outb; pob; pob = pob->next)
    {
        (void)sprintf(scratch, "%s.*", pob->dir);

        ff = FindOpen(scratch, ATTR_SUBDIR | ATTR_HIDDEN | ATTR_READONLY | ATTR_SYSTEM);

        if (ff)
        {
            do
            {
                p = strchr(ff->szName, '.');

                if (p && sscanf(p + 1, "%hx", &config.ob[config.num_ob]) == 1)
                    config.num_ob++;
            } while (FindNext(ff) == 0);
        }

        FindClose(ff);
    }
}


static void near MakeArcBase(char *where, NETADDR *dest)
{
    char *fake;

    fake = FixOutboundName(dest->zone);


        (void)sprintf(where, "%s%04hx%04hx.pnt", fake, (unsigned)dest->net, (unsigned)dest->node);

        if (!direxist(where))
            (void)make_dir(where);

        (void)sprintf(where + strlen(where), PATH_DELIMS "%08hx", config.addr->point - dest->point);
    }
    else
    {
