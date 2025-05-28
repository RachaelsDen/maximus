// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_config.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#include "max.h"
#include "prog.h"
#include "s_dupe.h"
#include "squish.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGLEN 64
#define MAXARGS 128

static char *cfgdelim = " \t\n\b";

static void near ReportErr(char *s)
{
    (void)printf("\aError!  %s\n", s);
    exit(ERL_ERROR);
}

static void near BeforeCompress(char *place)
{
    S_LogMsg("!Definition of COMPRESS.CFG must come before %s", place);
}

static void near InvalStatement(char *where)
{
    (void)printf("Invalid %s statement in config file!\n", where);
}

#ifdef OS_2


    if ((rc = DosLoadModule(szFailName, PATHLEN, pf->pszDLLName, &pf->hmod)) != 0)
    {
        (void)printf("Could not load dynamic link library '%s'! (rc=%d)\n", szFailName, rc);
        exit(ERL_ERROR);
    }

#ifdef __FLAT__
    if (DosQueryProcAddr(pf->hmod, 0, "FEATUREINIT", (PFN *)&pf->pfnInit) != 0 ||
        DosQueryProcAddr(pf->hmod, 0, "FEATURECONFIG", (PFN *)&pf->pfnConfig) != 0 ||
        DosQueryProcAddr(pf->hmod, 0, "FEATURENETMSG", (PFN *)&pf->pfnNetMsg) != 0 ||
        DosQueryProcAddr(pf->hmod, 0, "FEATURETOSSMSG", (PFN *)&pf->pfnTossMsg) != 0 ||
        DosQueryProcAddr(pf->hmod, 0, "FEATURESCANMSG", (PFN *)&pf->pfnScanMsg) != 0 ||
        DosQueryProcAddr(pf->hmod, 0, "FEATURETERM", (PFN *)&pf->pfnTerm) != 0 ||
        DosQueryProcAddr(pf->hmod, 0, "FEATURE32BIT", (PFN *)&pfnTest) != 0)
#else
    if (DosGetProcAddr(pf->hmod, "FEATUREINIT", (PPFN)(void far *)&pf->pfnInit) != 0 ||
        DosGetProcAddr(pf->hmod, "FEATURECONFIG", (PPFN)(void far *)&pf->pfnConfig) != 0 ||
        DosGetProcAddr(pf->hmod, "FEATURENETMSG", (PPFN)(void far *)&pf->pfnNetMsg) != 0 ||
        DosGetProcAddr(pf->hmod, "FEATURETOSSMSG", (PPFN)(void far *)&pf->pfnTossMsg) != 0 ||
        DosGetProcAddr(pf->hmod, "FEATURESCANMSG", (PPFN)(void far *)&pf->pfnScanMsg) != 0 ||
        DosGetProcAddr(pf->hmod, "FEATURETERM", (PPFN)(void far *)&pf->pfnTerm) != 0 ||
        DosGetProcAddr(pf->hmod, "FEATURE16BIT", (PFN *)&pfnTest) != 0)
#endif
    {
        (void)printf("Incorrect format for dynamic link library '%s'!\n", pf->pszDLLName);
        exit(ERL_ERROR);
    }


    if ((*pf->pfnInit)(&fi))
        exit(ERL_ERROR);

    pf->pszConfigName = sstrdup(fi.szConfigName);
    pf->ulFlag = fi.ulFlag;
}


    config.flag ^= FLAG_STATS;


    pob->zone = *ag[2] ? (word)atoi(ag[2]) : 0;
    pob->dir = sstrdup(ag[1]);


    pob->next = config.outb;
    config.outb = pob;
}

static void near V_Duplicates(char *line, char *ag[])
{
    NW(line);

    config.dupe_msgs = (word)atoi(ag[1]);

#ifndef __FLAT__
    if (((long)config.dupe_msgs * (long)sizeof(DUPEID) + sizeof(DUPEHEAD)) > 65300L)
    {
        S_LogMsg("!`Duplicates' keyword set too high - Max: %u",
                 config.dupe_msgs = ((65300u - sizeof(DUPEHEAD)) / sizeof(DUPEID) - 1));
    }
#endif
}

static void near V_LogLevel(char *line, char *ag[])
{
    NW(line);
    config.loglevel = (byte)atoi(ag[1]);
}

#ifndef __FLAT__
static void near CheckBufSize(unsigned size)
{
    if (size >= 64)
        ReportErr("Buffers statement: each value must be less than 64K");
}
#endif

static void near V_Buffers(char *line, char *ag[])
{
    NW(config);
    NW(line);

    if (eqstri(ag[1], "small"))
    {
        writebufmax = WRITEBUF_SMALL;
        outbufmax = OUTBUF_SMALL;
        maxmsglen = MAXMSGLEN_SMA;
    }
    else if (eqstri(ag[1], "medium"))
    {
        writebufmax = WRITEBUF_MEDIUM;
        outbufmax = OUTBUF_MEDIUM;
        maxmsglen = MAXMSGLEN_MED;
    }
    else if (eqstri(ag[1], "large"))
    {
        writebufmax = WRITEBUF_LARGE;
        outbufmax = OUTBUF_LARGE;
        maxmsglen = MAXMSGLEN_LAR;
    }
    else if (isdigit(*ag[1]))
    {
        writebufmax = (unsigned)atoi(ag[1]);
        outbufmax = (unsigned)atoi(ag[2]);
        maxmsglen = (unsigned)atoi(ag[3]);

#ifndef __FLAT__
        CheckBufSize(writebufmax);
        CheckBufSize(outbufmax);
        CheckBufSize(maxmsglen);
#endif


static void near V_Handles(struct _config *config, char *line, char *ag[])
{
    int handles;

    NW(line);

    handles = atoi(ag[1]);

    if (handles < 20 || handles > 250)
    {
        printf("Error!  Invalid number of file handles specified!");
        return;
    }

    config.max_handles = handles;
    config.max_talist = (handles - 12) / 2;
}

#endif

static void near V_MaxMsgs(char *line, char *ag[])
{
    NW(line);

    config.max_msgs = (word)atoi(ag[1]);
}

static void near V_MaxArchive(char *line, char *ag[])
{
    NW(line);

    config.max_archive = (word)atoi(ag[1]);
}

static void near V_Area(char *line, char *ag[])
{

    struct _cfgarea *ar, *testar;
    char *p = firstchar(line, cfgdelim, 4);

    if (!p)
        p = "";

    ar = Declare_Area(ag[2], ag[1], p, 0, 0);

    if (!ar)
        return;

    if (eqstri(ag[0], "badarea"))
    {
        ar->flag |= AFLAG_BAD;


        if (!testar)
        {
            ar->next_type = config.badmsgs;
            config.badmsgs = ar;
        }
    }
    else if (eqstri(ag[0], "dupearea"))
    {
        ar->flag |= AFLAG_DUPES;


        if (!testar)
        {
            ar->next_type = config.dupes;
            config.dupes = ar;
        }
    }
    else if (eqstri(ag[0], "netarea"))
    {
        struct _cfgarea *last_ar, *net_ar;

        ar->flag |= AFLAG_NET;

        for (last_ar = NULL, net_ar = config.netmail; net_ar && ar != net_ar;
             last_ar = net_ar, net_ar = net_ar->next_type)
            ;

    {
        ar->type |= MSGTYPE_ECHO;
    }
}

static void near V_Netfile(char *line, char *ag[])
{
    struct _tosspath *tp;
    int x;

    NW(line);

    tp = smalloc(sizeof(struct _tosspath));
    tp->flag = 0;
    tp->next = config.tpath;
    config.tpath = tp;

    for (x = 1; x < MAXARGS; x++)
    {
        if (eqstri(ag[x], "nopkt"))
            tp->flag |= TFLAG_NOPKT;
        else if (eqstri(ag[x], "noarc"))
            tp->flag |= TFLAG_NOARC;
        else if (eqstri(ag[x], "noecho"))
            tp->flag |= TFLAG_NOECHO;
        else
        {
            (void)Strip_Trailing(ag[x], '\\');
#ifdef UNIX
            (void)Strip_Trailing(ag[x], '/');
#endif

            tp->path = sstrdup(ag[x]);
            break;
        }
    }

    return;
}

static void near HandleGZRoute(char *ag[], struct _groute **begin, word gateroute)
{
    struct _groute *gr;
    struct _sblist *sb, last;
    word except;
    word nn;

    gr = smalloc(sizeof(struct _groute));


    nn = 1;

    if (gateroute)
    {
        struct _flotype *f;

        for (f = flo_str; f->name; f++)
            if (eqstri(ag[1], f->name))
                break;

        if (f->name)
            gr->flavour = f->flavour;
        else
        {
            S_LogMsg("!Invalid GateRoute flavour");
            gr->flavour = 'F';
        }


    gr->host = config.def;

    ParseNN(ag[nn++], &gr->host.zone, &gr->host.net, &gr->host.node, &gr->host.point, FALSE);


        *sb = last;

        ParseNN(ag[nn], &sb->zone, &sb->net, &sb->node, &sb->point, TRUE);

        last = *sb;
        last.point = 0;


        if (except)
        {
            tiny->next = config.tiny_except;
            config.tiny_except = tiny;
        }
        else
        {
            tiny->next = config.tiny;
            config.tiny = tiny;
        }
    }
}

static void near V_StripAttributes(char *line, char *ag[])
{
    unsigned except;
    struct _sblist *sa, last;
    unsigned i;

    NW(line);


        if (except)
        {
            sa->next = config.stripattr_except;
            config.stripattr_except = sa;
        }
        else
        {
            sa->next = config.stripattr;
            config.stripattr = sa;
        }
    }
}

static void near V_Remap(char *line, char *ag[])
{
    struct _remap *rem, *last;
    char *p;

    NW(line);

    if (!*ag[2])
    {
        InvalStatement("Remap");
        return;
    }

    rem = smalloc(sizeof(struct _remap));

    rem->node = config.def;

    ParseNN(ag[1], &rem->node.zone, &rem->node.net, &rem->node.node, &rem->node.point, FALSE);

    p = firstchar(line, cfgdelim, 3);

    if (!p)
        p = "";

    rem->name = sstrdup(p);
    rem->next = NULL;


    for (last = config.remap; last && last->next; last = last->next)
        ;

    if (last)
        last->next = rem;
    else
        config.remap = rem;
}

static void near V_Compress(char *line, char *ag[])
{
    struct _arcinfo *ai;

    NW(line);
    NW(ag);

    if ((config.arc = Parse_Arc_Control_File(config.compress_cfg)) == NULL)
        ErrOpening("archiver config", config.compress_cfg);


        *ats = last;

        ParseNN(ag[y], &ats->zone, &ats->net, &ats->node, &ats->point, FALSE);

        last = *ats;
        last.point = 0;

        if (!ats->zone)
        {
            ReportErr("Zone number is missing from \"Address\" statement, or\n"
                      "a zone of 0 was supplied.\n");
        }


static void near V_DefaultPack(char *line, char *ag[])
{
    struct _arcinfo *ai;

    NW(line);

    if (config.arc == NULL)
    {
        BeforeCompress("DefaultPacker");
        return;
    }

    for (ai = config.arc; ai; ai = ai->next)
        if (eqstri(ai->arcname, ag[1]))
        {
            config.def_arc = ai;
            return;
        }

    (void)printf("Unknown archiving method: `%s'\n", ag[1]);
}

static void near V_Pack(char *line, char *ag[])
{
    struct _arcinfo *ai;
    struct _sblist *node, last;
    int y;

    NW(line);

    if (config.arc == NULL)
    {
        BeforeCompress("Pack statement");
        return;
    }

    for (ai = config.arc; ai; ai = ai->next)
        if (eqstri(ai->arcname, ag[1]))
            break;

    if (!ai)
    {
        (void)printf("Unknown archiving method: `%s'\n", ag[1]);
        return;
    }

    last = config.def;

    for (y = 2; y < MAXARGS && *ag[y]; y++)
    {
        node = smalloc(sizeof(struct _sblist));
        *node = last;

        ParseNN(ag[y], &node->zone, &node->net, &node->node, &node->point, TRUE);

        last = *node;
        last.point = 0;

        node->next = ai->nodes;
        ai->nodes = node;
    }
}

static void near V_Password(char *line, char *ag[])
{
    struct _nodepwd *pwd;

    NW(line);

    pwd = smalloc(sizeof(struct _nodepwd));

    pwd->addr = config.def;

    ParseNN(ag[1], &pwd->addr.zone, &pwd->addr.net, &pwd->addr.node, &pwd->addr.point, FALSE);

    (void)strcpy(pwd->pwd, ag[2]);


        for (ad = config.addr, adlast = NULL; ad; adlast = ad, ad = ad->next)
            ;

        if (adlast)
            adlast->next = addr;
        else
        {
            config.addr = addr;
            config.def = *addr;
            config.def.point = 0;
        }
    }
}

static void near Fwd(char *line, char *ag[], int ff)
{
    struct _fwdlist *fwd;
    struct _sblist last;
    word fil;
    int i;

    NW(line);

    fil = FALSE;

    last = config.def;

    for (i = 1; i < MAXARGS && *ag[i]; i++)
    {
        if (eqstri(ag[i], "file"))
        {
            fil = TRUE;
            continue;
        }

        fwd = smalloc(sizeof(struct _fwdlist));
        fwd->file = fil;

        fwd->node = last;

        ParseNN(ag[i], &fwd->node.zone, &fwd->node.net, &fwd->node.node, &fwd->node.point, TRUE);

        last = fwd->node;
        last.point = 0;

    {"stripattributes", V_StripAttributes, VB_FUNC, NULL, 0},
    {"statistics", V_Statistics, VB_FUNC, NULL, 0},
    {"batchunarc", NULL, VB_FLAG, NULL, FLAG_BATCHXA},
    {"tossbadmsgs", NULL, VB_FLGT, NULL, FLAG_TOSSBAD},
    {"checkzones", NULL, VB_FLAG, NULL, FLAG_CHECKZ},
    {"arcmailattach", NULL, VB_FLAG, NULL, FLAG_FRODO},
    {"busyflags", NULL, VB_FLAG, NULL, FLAG_BSY},
    {"killblank", NULL, VB_FLAG, NULL, FLAG_KILLZ},
    {"killintransit", NULL, VB_FLAG, NULL, FLAG_KILLFWD},
    {"killdupes", NULL, VB_FLAG, NULL, FLAG_KILLDUPE},
    {"savecontrolinfo", NULL, VB_FLAG, NULL, FLAG_SAVECTRL},
    {"oldarcmailexts", NULL, VB_FLAG, NULL, FLAG_OLDARCM},
    {"quietarc", NULL, VB_FLAG, NULL, FLAG_QUIETARC},
    {"secure", NULL, VB_FLGT, NULL, FLAG_SECURE},
    {"binkpoint", NULL, VB_FLG2, NULL, FLAG2_BINKPT},
    {"nuke", NULL, VB_FLG2, NULL, FLAG2_NUKE},
    {"nosoundex", NULL, VB_FLG2, NULL, FLAG2_NOSNDX},
    {"nostomp", NULL, VB_FLG2, NULL, FLAG2_NOSTOMP},
    {"killintransitfile", NULL, VB_FLG2, NULL, FLAG2_KFFILE},
    {"linkmsgid", NULL, VB_FLG2, NULL, FLAG2_LMSGID},
    {"dupelongheader", NULL, VB_FLG2, NULL, FLAG2_LONGHDR},
    {"netfile", V_Netfile, VB_FUNC, NULL, 0},
    {"outbound", V_Outbound, VB_FUNC, NULL, 0},
    {"swap", V_Swap, VB_STR, &config.swappath, 0},
    {"compress", V_Compress, VB_FILE, &config.compress_cfg, 0},
    {"areasbbs", NULL, VB_FILE, &config.areasbbs, 0},
    {"routing", V_Routing, VB_FILE, &config.routing, 0},
    {"logfile", NULL, VB_FILE, &config.logfile, 0},
#ifdef OS_2
#ifdef __FLAT__
    {"feature", NULL, VB_FUNC, NULL, 0},
    {"feature32", V_Feature, VB_FUNC, NULL, 0},
#else
    {"feature", V_Feature, VB_FUNC, NULL, 0},
    {"feature32", NULL, VB_FUNC, NULL, 0},
#endif
#endif
    {"track", NULL, VB_FILE, &config.tracklog, 0}};

#define vtlen (unsigned)(sizeof(vt) / sizeof(vt[0]))


                        p = firstchar(in, cfgdelim, 2);

                        if (!p)
                            p = "";
                    }
        {
            struct _feature *pf;
            struct _feat_config fc;

            fc.struct_len = sizeof fc;
            (void)strcpy(fc.szConfigLine, in);
            fc.ppszArgs = args;


                for (p = pf->pszConfigName; p; p = strchr(p, '\r'))
                {

                    if ((s = strchr(p, '\r')) == NULL)
                        s = p + strlen(p);



                long pos = ftell(cfgfile);
                (void)fclose(cfgfile);


                Parse1Config(fname, args, in, line);



    in = smalloc(CFGLEN);
    line = smalloc(CFGLEN);

    for (i = 0; i < MAXARGS; i++)
        args[i] = smalloc(ARGLEN);


    for (i = 0; i < MAXARGS; i++)
        free(args[i]);

    free(line);
    free(in);

