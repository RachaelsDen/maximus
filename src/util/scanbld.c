// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: scanbld.c,v 1.2 2003/06/11 02:13:06 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_INCL_VER
#define SCANBLD_COMPILE

#include "scanbld.h"
#include "alc.h"
#include "areaapi.h"
#include "max.h"
#include "msgapi.h"
#include "newarea.h"
#include "prmapi.h"
#include "userapi.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


    dword far *hashes;


static dword near UserHash(byte OS2FAR *f)
{
    dword hash = 0, g;
    char OS2FAR *p;

    for (p = f; *p; p++)
    {
        hash = (hash << 4) + (dword)tolower(*p);

        if ((g = (hash & 0xf0000000L)) != 0L)
        {
            hash |= g >> 24;
            hash |= g;
        }
    }


static void near Format(void)
{
    static char *help[] = {
        "Error in command-line!  Format:\n\n",

        "SCANBLD [<area_name>...] [@<tosslog>] [[-x]...]\n\n",

        "[area_type] is an optional list of names or types of areas to be scanned.\n",
        "You may specify the names of one or more message areas on your system.  In\n",
        "addition, the following special keywords can be used to select sets of areas:\n\n",

        "   All - Scan all areas.\n",
        "  Echo - Scan only EchoMail areas.\n",
        "  Conf - Scan only Conference areas.\n",
        " Local - Scan only local message areas.\n",
        "Matrix - Scan only Matrix/NetMail areas.\n\n",

#ifdef OS_2
        "For normal operation, SCANBLD should be invoked as \"scanbldp all\".\n\n"
#else
        "For normal operation, SCANBLD should be invoked as \"scanbld all\".\n\n"
#endif

        "When using the special area types above, you may also exclude certain areas\n",
        "from the scan.  To do this, add a '!' in front of the area name.\n\n",

        "@",

        "For example, 'scanbld all !comments !foobar' would scan all message areas on\n"
        "the system except for 'comments' and 'foobar'.\n\n"

        "If specified, <tosslog> is a file containing a list of areas tags\n",
        "to be scanned, one per line.  Each line in the file will be compared\n",
        "with the 'tag' keyword for each area in MSGAREA.CTL.  Areas with tags\n",
        "listed in <tosslog> will be scanned, in addition to any areas specified\n",
        "on the command-line.\n\n",

        "You can also specify any of the following switches to change SCANBLD's\n",
        "operation:\n\n",

        "  -c       - Forced compile of all areas.  Instead of scan each area for\n",
        "             changes and conditionally compiling the area, using -c forces\n"
        "             SCANBLD to rebuild all areas.\n",
        "  -m<file> - Use msg area data from <file> instead of default from PRM file.\n"
        "  -nd      - Tells SCANBLD not to delete the @tosslog file after processing.\n",
        "  -p<file> - Use PRM file <file> instead of the MAXIMUS environment variable.\n",
        "  -q       - Forces quiet operation.  SCANBLD will display a `#' for each area\n",
        "             processed, instead of the usual area statistics.\n",
        "  -u<file> - Use user file <file> instead of the default from the PRM file.\n",
        NULL};

    char **pp;

    for (pp = help; *pp; pp++)
        if (eqstri(*pp, "@"))
            Scan_More();
        else
            printf("%s", *pp);

    exit(1);
}

static void near TooManyAreas(void)
{
    printf("Error!  Too many areas specified on command line!\n");
    exit(1);
}

static void near ScanOneMessage(struct _sbcfg *psc, int fd, HMSG hmsg, long mn)
{
    SBREC sr;
    dword OS2FAR *ph;
    dword OS2FAR *eh;
    dword hash;
    XMSG xmsg;

    if ((mn % 10) == 0 && (psc->flags & SFLAG_QUIET) == 0)
    {
        printf("\b\b\b\b%04d", mn);
        fflush(stdout);
    }

    MsgReadMsg(hmsg, &xmsg, 0L, 0L, NULL, 0L, NULL);

    hash = UserHash(xmsg.to);


            memset(&sr, 0, sizeof sr);
            sr.msgnum = mn;
            strcpy(sr.to, xmsg.to);
            sr.attr = (word)xmsg.attr;


    return;
}

static void near ScanOneArea(struct _sbcfg *psc, PMAH pmah)
{
    SBHDR sbhdr;
    char sfname[PATHLEN];
    char pszMsgpath[PATHLEN];
    int do_partial, do_full;
    long mn;
    HAREA ha;
    HMSG hmsg;
    int fd;


    if (read(fd, (char *)&sbhdr, sizeof sbhdr) != sizeof sbhdr)
        memset(&sbhdr, 0, sizeof sbhdr);


    if (sbhdr.num_msg && MsgGetNumMsg(ha) - sbhdr.num_msg == MsgGetHighMsg(ha) - sbhdr.high_msg &&
        MsgGetHighMsg(ha) >= sbhdr.high_msg)
        do_partial = TRUE;
    else
        do_full = TRUE;

    if (do_full)
    {

        mn = sbhdr.high_msg + 1L;
        lseek(fd, 0L, SEEK_END);

        if ((psc->flags & SFLAG_QUIET) == 0)
        {
            printf(" - Updating %04d", (int)sbhdr.high_msg);
            fflush(stdout);
        }
    }

    for (; mn <= MsgGetHighMsg(ha); mn++)
        if ((hmsg = MsgOpenMsg(ha, MOPEN_READ, mn)) != NULL)
        {
            ScanOneMessage(psc, fd, hmsg, mn);
            MsgCloseMsg(hmsg);
        }


static int near ProcessThisArea(struct _sbcfg *psc, PMAH pmah)
{
    int i;


    if ((pmah->ma.attribs & MA_ECHO) && (psc->flags & SFLAG_ECHO) == 0)
        return FALSE;

    if ((pmah->ma.attribs & MA_NET) && (psc->flags & SFLAG_NET) == 0)
        return FALSE;

    if ((pmah->ma.attribs & (MA_CONF | MA_NET | MA_ECHO)) == 0 && (psc->flags & SFLAG_LOCAL) == 0)
        return FALSE;

    if ((pmah->ma.attribs & MA_CONF) && (psc->flags & SFLAG_CONF) == 0)
        return FALSE;


    return TRUE;
}


static void near ParseArgs(int argc, char *argv[], struct _sbcfg *psc)
{
    int i;
    char *szTossName = NULL;
    int fGotArea = FALSE;

    if (argc < 2)
        Format();

    for (i = 1; i < argc; i++)
    {
        if (eqstri(argv[i], "echo"))
        {
            psc->flags |= SFLAG_ECHO;
            fGotArea = TRUE;
        }
        else if (eqstri(argv[i], "net") || eqstri(argv[i], "matrix"))
        {
            psc->flags |= SFLAG_NET;
            fGotArea = TRUE;
        }
        else if (eqstri(argv[i], "conf"))
        {
            psc->flags |= SFLAG_CONF;
            fGotArea = TRUE;
        }
        else if (eqstri(argv[i], "local"))
        {
            psc->flags |= SFLAG_LOCAL;
            fGotArea = TRUE;
        }
        else if (eqstri(argv[i], "all"))
        {
            psc->flags |= SFLAG_ALL;
            fGotArea = TRUE;
        }
        else if (*argv[i] == '-' || *argv[i] == '/')
        {
            switch (tolower(argv[i][1]))
            {

            case 'c':
                psc->flags |= SFLAG_FORCE;
                break;
            case 'q':
                psc->flags |= SFLAG_QUIET;
                break;
            case 'n':
                psc->flags |= SFLAG_NODEL;
                break;
            case 'u':
                strcpy(psc->userindex, argv[i] + 2);
                break;
            case 'm':
                strcpy(psc->mareafile, argv[i] + 2);
                break;
            case 'p':

    if (!fGotArea)
        psc->flags |= SFLAG_ALL;

    if (szTossName && (psc->flags & SFLAG_NODEL) == 0)
        unlink(szTossName);
}


    size = UserFileSize(huf) * sizeof(dword) * 2;

    if ((psc->hashes = farmalloc(size)) == NULL)
        NoMem();

    psc->num_hash = size / sizeof(dword);

    pdwHash = psc->hashes;
    pdwEnd = pdwHash + size;

    if ((huffs = UserFileFindSeqOpen(huf)) != NULL)
    {
        do
        {
            if (pdwHash < pdwEnd)
                *pdwHash++ = UserHash(huffs->usr.name);

            if (pdwHash < pdwEnd)
                *pdwHash++ = UserHash(huffs->usr.alias);
        } while (UserFileFindSeqNext(huffs));

        UserFileFindSeqClose(huffs);
    }

    UserFileClose(huf);

    printf("\r                   \r");
    fflush(stdout);
}


    PrmRelativeString(psc->hp, PrmFileString(psc->hp, user_file), psc->userindex);
    PrmRelativeString(psc->hp, PrmFileString(psc->hp, marea_name), psc->mareafile);
}

static void near Term(void) { MsgCloseApi(); }

int c_main(int argc, char *argv[])
{
    struct _sbcfg sc;

    Hello("SCANBLD", "Mail database update utility", VERSION, "1990, " THIS_YEAR);

    Init(&sc, argc, argv);
    ParseArgs(argc, argv, &sc);
    HashUserFile(&sc);
    ScanAreas(&sc);
    Term();

    printf("\nDone!\n");

    return 0;
}
