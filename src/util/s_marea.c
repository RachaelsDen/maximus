// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_marea.c,v 1.1.1.1 2002/10/01 17:57:46 sdudley Exp $";
#pragma on(unreferenced)


#define SILT
#define NOVARS
#define NOINIT
#define NO_MSGH_DEF

#include "s_marea.h"
#include "max.h"
#include "prog.h"
#include "s_heap.h"
#include "silt.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static long cbLast = 0;
static word division = 0;
static char prefix[PATHLEN] = "";

#ifdef MAX_TRACKER

#include "trackc.h"
#include "trackp.h"

static TRK_OWNER toNewOwner;


static void near FiltOrigin(void *v, char *words[], char *line)
{
    char *txt = fchar(line, ctl_delim, 3);

    if (*words[1] != '.')
    {
        if (!isdigit(*words[1]))
        {
            printf(
                "\a\nWarning!  First word after 'Origin' on line %d must be a network address.\n",
                linenum);
            Compiling(-1, NULL, NULL);
        }

        ParseNNN(words[1], &PMI(v)->ma.primary, FALSE);
    }

    if (*words[2] != '.')
    {
        if (!isdigit(*words[2]))
        {
            printf(
                "\a\nWarning!  Second word after 'Origin' on line %d must be a network address.\n",
                linenum);
            Compiling(-1, NULL, NULL);
        }

        ParseNNN(words[2], &PMI(v)->ma.seenby, FALSE);
    }

    strocpy(line, txt);
}


    static struct
    {
        char *name;
        word mask1;
        word mask2;
    } * pst, style_tab[] = {{"Pvt", MA_PVT, 0},
                            {"Private", MA_PVT, 0},
                            {"Pub", MA_PUB, 0},
                            {"Public", MA_PUB, 0},
                            {"ReadOnly", MA_READONLY, 0},
                            {"HiBit", MA_HIBIT, 0},
                            {"HighBit", MA_HIBIT, 0},
                            {"Net", MA_NET, 0},
                            {"Matrix", MA_NET, 0},
                            {"Echo", MA_ECHO, 0},
                            {"EchoMail", MA_ECHO, 0},
                            {"Conf", MA_CONF, 0},
                            {"Conference", MA_CONF, 0},
                            {"Loc", 0, 0},
                            {"Local", 0, 0},
                            {"Anon", MA_ANON, 0},
                            {"Anonymous", MA_ANON, 0},
                            {"NoNameKludge", MA_NORNK, 0},
                            {"RealName", MA_REAL, 0},
                            {"Alias", MA_ALIAS, 0},
                            {"Audit", MA_AUDIT, 0},
                            {"Hidden", MA_HIDDN, 0},
                            {"Attach", MA_ATTACH, 0},
                            {"NoMailCheck", 0, MA2_NOMCHK},
                            {NULL, 0}};

    NW(line);


            if (eqstri(words[w], "squish"))
                PMI(v)->ma.type = MSGTYPE_SQUISH;
            else if (eqstri(words[w], "*.msg") || eqstri(words[w], "sdm"))
                PMI(v)->ma.type = MSGTYPE_SDM;
            else
                Unknown_Ctl(linenum, words[w]);
        }
    }
}


static void near assert_msgarea(char *path, word type, word killbyage, word killbynum,
                                word killskip)
{
    HAREA ha;
    char szPath[PATHLEN];
    char szUp[PATHLEN];

    dword dwKillByNum = killbynum ? (dword)killbynum : (dword)-1L;
    dword dwKillSkip = killskip ? (dword)killskip : (dword)-1L;
    dword dwKillByAge = killbyage ? (dword)killbyage : (dword)-1L;

    strcpy(szPath, path);


    if (type & MSGTYPE_SQUISH)
        SquishSetMaxMsg(ha, dwKillByNum, dwKillSkip, dwKillByAge);

    MsgCloseArea(ha);
}

static void near MsgAreaWrite(MAINFO *pmi, int closeit)
{
    static int mai_fd = -1;
    static int ma_fd = -1;
    unsigned size;
    OVRLIST ol;
    struct _mfidx mfi;

    if (!do_marea)
        return;

    if (!pmi && ma_fd != -1 && closeit)
    {
        MAREA ma;
        long pos = lseek(ma_fd, 0L, SEEK_END);


        pos -= cbLast + ADATA_START;

        lseek(ma_fd, ADATA_START, SEEK_SET);

        if (read(ma_fd, (char *)&ma, sizeof ma) != sizeof ma)
        {
            printf("Error reading final msg area data!\n");
            exit(1);
        }

        lseek(ma_fd, ADATA_START, SEEK_SET);

        ma.cbPrior = -pos;

        if (write(ma_fd, (char *)&ma, sizeof ma) != sizeof ma)
        {
            printf("Error writing final msg area data!\n");
            exit(1);
        }

        close(ma_fd);
        close(mai_fd);
        ma_fd = -1;
        return;
    }

    if (ma_fd == -1 && !closeit)
    {
        char fname[PATHLEN];
        dword dwId = MAREA_ID;

        if (strings[prm.marea_name] == 0)
        {
            printf("Error!  MSGAREA.CTL cannot be SILTed separately.  Use\n"
                   "\"SILT MAX\" and ensure that you have a \"Messages marea\"\n"
                   "keyword in the Session Section.\n");
            exit(1);
        }

        strcpy(fname, strings + prm.marea_name);
        strcat(fname, ".dat");

        if ((ma_fd = sopen(fname, O_CREAT | O_TRUNC | O_RDWR | O_BINARY, SH_DENYNO,
                           S_IREAD | S_IWRITE)) == -1)
        {
            printf("\nCan't open msg area data file %s!\n", fname);
            exit(1);
        }

        if (write(ma_fd, (char *)&dwId, sizeof dwId) != sizeof dwId)
        {
            printf("\aError writing key to msg data file %s\n", fname);
            exit(1);
        }

        strcpy(fname, strings + prm.marea_name);
        strcat(fname, ".idx");

        if ((mai_fd = sopen(fname, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_DENYNO,
                            S_IREAD | S_IWRITE)) == -1)
        {
            printf("\nCan't open msg area index file %s!\n", fname);
            exit(1);
        }
    }

    if (pmi)
    {

        cbLast = pmi->ma.cbArea + pmi->ma.cbHeap + pmi->ma.num_override * sizeof(OVERRIDE);


        if (pmi->ma.type & MSGTYPE_SQUISH)
        {
            char *p = pmi->h.heap + pmi->ma.path;
            int len;

            if (p[len = strlen(p) - 1] == PATH_DELIM)
                p[len] = 0;
        }


        if ((pmi->ma.attribs & (MA_DIVBEGIN | MA_DIVEND)) == 0)
            assert_msgarea(pmi->h.heap + pmi->ma.path, pmi->ma.type, pmi->ma.killbyage,
                           pmi->ma.killbynum, pmi->ma.killskip);


        if (write(mai_fd, (char *)&mfi, sizeof mfi) != sizeof mfi)
            ErrWrite();


        for (ol = pmi->ol; ol; ol = ol->next)
            if (write(ma_fd, (char *)&ol->or, sizeof ol->or) != sizeof ol->or)
                ErrWrite();


        MsgAreaWrite(NULL, FALSE);

        memset(&mi, 0, sizeof mi);
        mi.marea = TRUE;
        mi.ma.division = division;

        mi.ma.primary = prm.address[0];
        mi.ma.seenby = prm.address[!!prm.address[0].point && prm.address[1].zone];

        HeapNew(&mi.h, MAX_MSG_HEAP);

        strcpy(fullname, prefix);
        strcat(fullname, name);

        HeapAdd(&mi.h, &mi.ma.name, fullname);

        *toNewOwner = 0;
    }

    while (fgets(line, PATHLEN, ctlfile))
        if (VerbParse(&mi, do_marea ? verbs : NULL, line))
            break;

    if (do_marea)
    {
        MsgAreaWrite(&mi, FALSE);

        for (ol = mi.ol; ol; ol = ol->next)
            free(ol);

        HeapDelete(&mi.h);
    }

    return 0;
}

void ParseMsgDivisionBegin(char *name, char *acs, char *displayfile, char *descript)
{
    MAINFO mi;
    char fullname[PATHLEN];

    if (!do_marea)
        return;

    if (strchr(name, '.'))
        BadDivisionName();

    strcpy(fullname, prefix);
    strcat(fullname, name);

    strcat(prefix, name);
    strcat(prefix, ".");

    MsgAreaWrite(NULL, FALSE);

    memset(&mi, 0, sizeof mi);
    mi.marea = TRUE;

    HeapNew(&mi.h, MAX_MSG_HEAP);

    HeapAdd(&mi.h, &mi.ma.name, fullname);
    HeapAdd(&mi.h, &mi.ma.descript, descript);
    HeapAdd(&mi.h, &mi.ma.acs, acs);
    HeapAdd(&mi.h, &mi.ma.path, displayfile);

    mi.ma.attribs = MA_DIVBEGIN;
    mi.ma.division = division++;

    MsgAreaWrite(&mi, FALSE);
    HeapDelete(&mi.h);
}

void ParseMsgDivisionEnd(void)
{
    MAINFO mi;
    char *p;

    if (!do_marea)
        return;

    if (!*prefix)
    {
        printf("\n\aError!  MsgDivisionEnd on line %d has no correspondig MsgDivisionBegin!\n",
               linenum);
        Compiling(-1, NULL, NULL);
        return;
    }


    if ((p = strrchr(prefix, '.')) != NULL)
        p[1] = 0;
    else
        *prefix = 0;

    MsgAreaWrite(NULL, FALSE);

    memset(&mi, 0, sizeof mi);
    mi.marea = TRUE;

    HeapNew(&mi.h, MAX_MSG_HEAP);

    mi.ma.attribs = MA_DIVEND;
    mi.ma.division = --division;
    HeapAdd(&mi.h, &mi.ma.acs, "");

    MsgAreaWrite(&mi, FALSE);
    HeapDelete(&mi.h);
}
