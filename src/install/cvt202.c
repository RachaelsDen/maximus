// SPDX-License-Identifier: GPL-2.0-or-later


#include "cvt202.h"
#include "ffind.h"
#include "install.h"
#include "prog.h"
#include "tagapi.h"
#include "tui.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef OS_2
#define INCL_DOS
#include "pos2.h"
#endif



static TRANSLATESTATE ptsTables[MAX_TRANSLATE_TABLES];


CVTSTATE HandleEventEvent(CVTPARM *pcp)
{
    char szOut[PATHLEN];
    int iWord;

    sprintf(szOut, "%s\t%s\t%s ", pcp->szWords[0], pcp->szWords[1], pcp->szWords[2]);

    for (iWord = 3; pcp->szWords[iWord]; iWord++)
    {
        switch (toupper(*pcp->szWords[iWord]))
        {
        case 'E':
            sprintf(szOut + strlen(szOut), "exit=%d ", atoi(pcp->szWords[iWord] + 1));
            break;

        case 'Y':
        {
            char *szSlash;

            int iBells = 1;
            int iMax = 1;
            int iTune = -1;
            char szTune[PATHLEN];

            iBells = atoi(pcp->szWords[iWord] + 1);

            if ((szSlash = strchr(pcp->szWords[iWord], '/')) != NULL)
            {
                iMax = atoi(szSlash + 1);

                if ((szSlash = strchr(szSlash + 1, '/')) != NULL)
                    iTune = atoi(szSlash + 1);
            }

            if (iTune == -1)
                strcpy(szTune, "Random");
            else
                sprintf(szTune, "Yell%d", iTune);

            sprintf(szOut + strlen(szOut), "bells=%d maxyell=%d tune=%s", iBells, iMax, szTune);
            break;
        }

        default:
            strcat(szOut, pcp->szWords[iWord]);
            strcat(szOut, " ");
        }
    }

    strcat(szOut, "\n");
    strcpy(pcp->szLine, szOut);

    return csState;
}

static TRANSLATOR ttEvent[] = {{"event", HandleEventEvent}, {NULL, 0}};

static XLATTABLE xtEvent[] = {{NULL, NULL, 0}};


CVTSTATE HandleSystemEnd(CVTPARM *pcp)
{

    strcpy(pcp->szLine, "Include Access.Ctl");

    (void)pcp;
    return CS_TOP;
}

CVTSTATE HandleSystemFile(CVTPARM *pcp)
{

CVTSTATE HandleMatrixEnd(CVTPARM *pcp)
{
    (void)pcp;
    fprintf(pfsCur->fpOut, "\tMessage Edit Ask\tLocalAttach\tNormal\n");

    return CS_TOP;
}

static TRANSLATOR ttMatrix[] = {{"end", HandleMatrixEnd}, {NULL, 0}};

static XLATTABLE xtMatrix[] = {{NULL, NULL, 0}};


CVTSTATE HandleMenuHeader(CVTPARM *pcp)
{
    if (eqstri(pcp->szWords[1], "message"))
        strcpy(pcp->szLine, "\tHeaderFile\t:M\\HeadMsg\n");
    else if (eqstri(pcp->szWords[1], "file"))
        strcpy(pcp->szLine, "\tHeaderFile\t:M\\HeadFile\n");
    else if (eqstri(pcp->szWords[1], "chat"))
        strcpy(pcp->szLine, "\tHeaderFile\t:M\\HeadChat\n");
    else if (eqstri(pcp->szWords[1], "change"))
        strcpy(pcp->szLine, "\tHeaderFile\t:M\\HeadChg\n");
    else if (eqstri(pcp->szWords[1], "none"))
        *pcp->szLine = 0;
    else
        Unknown("MenuHeader", pcp->szWords[1]);

    return csState;
}

CVTSTATE HandleHeaderFile(CVTPARM *pcp)
{
    if (!eqstri(md.szName, "reader"))
    {

        strocpy(pcp->szLine + 1, pcp->szLine);
        *pcp->szLine = '%';
    }

    return csState;
}

CVTSTATE HandleMenuDefault(CVTPARM *pcp)
{
    char *szName = NULL;
    int iWord;

    if (stristr(pcp->szStrippedLine, "area_change"))
    {
        int fGotArea = FALSE;

        for (iWord = 0; pcp->szWords[iWord]; iWord++)
        {
            if (fGotArea)
            {
                if (eqstri(pcp->szWords[iWord], "file"))
                {
                    szName = "File_Area";
                    break;
                }
                else if (eqstri(pcp->szWords[iWord], "message"))
                {
                    szName = "Msg_Area";
                    break;
                }
            }
            else if (eqstri(pcp->szWords[iWord], "area_change"))
                fGotArea = TRUE;
        }
    }


    if (eqstri(md.szName, "message"))
    {
        fprintf(pfsCur->fpOut,
                "NoDsp   Msg_Change                             Disgrace \"`46\"   ; Alt-C\n"
                "NoDsp   Read_Previous                          Disgrace \"`75\"   ; Left\n"
                "NoDsp   Read_Original                          Disgrace \"`115\"  ; Ctrl-Left\n"
                "NoDsp   Read_Next                              Disgrace \"`77\"   ; Right\n"
                "NoDsp   Read_Reply                             Disgrace \"`116\"  ; Ctrl-Right\n"
                "NoDsp   Msg_Reply                              Disgrace \"`16\"   ; Alt-Q\n"
                "NoDsp   Msg_Reply                              Disgrace \"`19\"   ; Alt-R\n"
                "NoDsp   Msg_Kill                               Disgrace \"`37\" \"=\"; Alt-K\n");

        fprintf(pfsCur->fpOut,
                "%%%%      Msg_Download_Attach                    Disgrace \"^Download Attaches\"\n"
                "%%%%      Msg_Reply_Area         .               Disgrace \"$Reply Elsewhere\"\n");
    }
    else if (eqstri(md.szName, "reader"))
    {
        fprintf(pfsCur->fpOut,
                "%%       Msg_Restrict                           Disgrace \"Restrict Date\"\n");
    }

    if (md.szName)
        free(md.szName);

    return CS_TOP;
}

static TRANSLATOR ttMenu[] = {{"headerfile", HandleHeaderFile},
                              {"menuheader", HandleMenuHeader},
                              {"end", HandleMenuEnd},
                              {"*", HandleMenuDefault},
                              {NULL, 0}};

static XLATTABLE xtMenu[] = {{"contents", "File_Contents", 0},
                             {"download", "File_Download", 0},
                             {"locate", "File_Locate", 0},
                             {"newfiles", "File_NewFiles", 0},
                             {"upload", "File_Upload", 0},
                             {"type", "File_View", 0},
                             {"raw", "File_Raw", 0},
                             {"override_path", "File_Override", 0},
                             {"enter_message", "Msg_Enter", 0},
                             {"forward", "Msg_Forward", 0},
                             {"xport", "Msg_Xport", 0},
                             {"statistics", "MEX\t\tM\\Stats", 0},
                             {NULL, NULL, 0}};


CVTSTATE HandleColourStrip(CVTPARM *pcp)
{

CVTSTATE HandleLanguageStrip(CVTPARM *pcp)
{

    fprintf(pfsCur->fpOut, "        Language English\n");
    return CS_TOP;
}

static TRANSLATOR ttLanguage[] = {
    {"language", HandleLanguageStrip}, {"end", HandleLanguageEnd}, {NULL, 0}};

static XLATTABLE xtLanguage[] = {{NULL, NULL, 0}};


CVTSTATE HandleSessionUpload(CVTPARM *pcp)
{

    if (eqstri(pcp->szWords[1], "MsgFormat") || eqstri(pcp->szWords[1], "FileFormat"))
    {
        char *psz;
        static char szReplace[] = "%-20";

        while ((psz = strstr(pcp->szLine, "%-9.9")) != NULL)
        {
            strocpy(psz + 4, psz + 5);
            memmove(psz, szReplace, strlen(szReplace));
        }
    }

    return csState;
}

CVTSTATE HandleSessionArea(CVTPARM *pcp)
{
    if (eqstri(pcp->szWords[1], "data"))
    {
        sd.fWroteMarea = TRUE;
        strcpy(pcp->szLine, "\tMessageData\tMarea\n");
    }
    else if (eqstri(pcp->szWords[1], "index"))
    {
        sd.fWroteFarea = TRUE;
        strcpy(pcp->szLine, "\tFileData\tFarea\n");
    }
    else if (!eqstri(pcp->szWords[1], "change"))
        Unknown("area type", pcp->szWords[1]);

    return csState;
}

CVTSTATE HandleSessionBegin(CVTPARM *pcp)
{
    (void)pcp;

    fputs(pcp->szLine, pfsCur->fpOut);


    if (!sd.fWroteMarea)
        fprintf(pfsCur->fpOut, "\tMessageData\tMarea\n");

    if (!sd.fWroteFarea)
        fprintf(pfsCur->fpOut, "\tFileData\tFarea\n");

    fprintf(pfsCur->fpOut, "\n");
    return CS_TOP;
}

static TRANSLATOR ttSession[] = {{"no", HandleSessionNo},
                                 {"upload", HandleSessionUpload},
                                 {"ratio", HandleSessionStrip},
                                 {"userlist", HandleSessionStrip},
                                 {"define", HandleSessionStrip},
                                 {"format", HandleSessionFormat},
                                 {"area", HandleSessionArea},
                                 {"end", HandleSessionEnd},
                                 {NULL, 0}};

static XLATTABLE xtSession[] = {{NULL, NULL, 0}};


CVTSTATE HandleAreaEnd(CVTPARM *pcp)
{
    (void)pcp;

    if (ad.fMsg)
    {
        fprintf(pfsCur->fpOut, "MsgArea %s\n", ad.szName);
        fprintf(pfsCur->fpOut, "\tACS\t\t%s\n", ad.szMsgAccess ? ad.szMsgAccess : "Hidden");

        if (ad.szMsgInfo)
            fprintf(pfsCur->fpOut, "\tDesc\t\t%s\n", ad.szMsgInfo);

        if (ad.szMsgMenuName)
            fprintf(pfsCur->fpOut, "\tMenuName\tMESSAGE %s\n", ad.szMsgMenuName);

        if (ad.szPath)
            fprintf(pfsCur->fpOut, "\tPath\t\t%s\n", ad.szPath);

        if (ad.szMsgOverride)
        {
            fprintf(pfsCur->fpOut, "\t%%Override\t\t<menu_name> <option_type> <acs> [<key>]\n");
            fprintf(pfsCur->fpOut,
                    "\t%% CONVERT WARNING!  The above line must be converted manually,\n");
            fprintf(pfsCur->fpOut, "\t%% Original: 'MsgOverride %s'\n\n", ad.szMsgOverride);
        }

        if (ad.szOrigin)
        {
            fprintf(pfsCur->fpOut, "\tOrigin\t\t. . %s\n", ad.szOrigin);
            fprintf(pfsCur->fpOut, "\t%% CONVERT WARNING!  The above line may have to be manually\n"
                                   "\t%% modified to use the correct origination address.\n\n");
        }

        if (ad.szMsgBarricade)
            fprintf(pfsCur->fpOut, "\tBarricade\tMESSAGE %s\n", ad.szMsgBarricade);

        if (ad.szMsgName)
            fprintf(pfsCur->fpOut, "\tTag\t\t%s\n", ad.szMsgName);

        if (ad.iRenumDays)
            fprintf(pfsCur->fpOut, "\tRenum Days\t%d\n", ad.iRenumDays);

        if (ad.iRenumMax)
            fprintf(pfsCur->fpOut, "\tRenum Max\t%d\n", ad.iRenumMax);


    fprintf(pfsCur->fpOut, pcp->szLine);
    return csState;
}

CVTSTATE HandleAreaPrivRelated(CVTPARM *pcp)
{
    *pcp->szLine = '%';
    fputs(pcp->szLine, pfsCur->fpOut);

    fprintf(pfsCur->fpOut, "%% Warning!  The above line contains a keyword which is not\n"
                           "%% directly supported by Maximus version 3.  Instead, use the\n"
                           "%% expanded power of the new Override statement to achieve the\n"
                           "%% same functionality.\n");

    return csState;
}

static TRANSLATOR ttArea[] = {{"msginfo", HandleAreaMsgInfo},
                              {"msgaccess", HandleAreaMsgAccess},
                              {"type", HandleAreaType},
                              {"renum", HandleAreaRenum},
                              {"msgmenuname", HandleAreaMsgMenuName},
                              {"msgname", HandleAreaMsgName},
                              {"matrix", HandleAreaMatrix},
                              {"netmail", HandleAreaMatrix},
                              {"echomail", HandleAreaEcho},
                              {"echo", HandleAreaEcho},
                              {"conf", HandleAreaConf},
                              {"conference", HandleAreaConf},
                              {"local", HandleAreaLocal},
                              {"public", HandleAreaPublic},
                              {"private", HandleAreaPrivate},
                              {"alias", HandleAreaAlias},
                              {"read-only", HandleAreaReadOnly},
                              {"anonymous", HandleAreaAnonymous},
                              {"high", HandleAreaHigh},
                              {"no", HandleAreaNoNameKludge},
                              {"use", HandleAreaUseRealname},
                              {"origin", HandleAreaOrigin},
                              {"msgoverride", HandleAreaMsgOverride},
                              {"msgbarricade", HandleAreaMsgBarricade},

                              {"download", HandleAreaDownload},
                              {"upload", HandleAreaUpload},

                              {"filelist", HandleAreaFileList},
                              {"fileinfo", HandleAreaFileInfo},
                              {"fileaccess", HandleAreaFileAccess},
                              {"filemenuname", HandleAreaFileMenuName},
                              {"fileoverride", HandleAreaFileOverride},
                              {"filebarricade", HandleAreaFileBarricade},

                              {"override", HandleAreaObsolete},
                              {"access", HandleAreaObsolete},
                              {"menupath", HandleAreaObsolete},

                              {"app", HandleAreaApp},
                              {"application", HandleAreaApp},

                              {"twit", HandleAreaPrivRelated},
                              {"disgrace", HandleAreaPrivRelated},
                              {"limited", HandleAreaPrivRelated},
                              {"normal", HandleAreaPrivRelated},
                              {"worthy", HandleAreaPrivRelated},
                              {"privil", HandleAreaPrivRelated},
                              {"privel", HandleAreaPrivRelated},
                              {"favored", HandleAreaPrivRelated},
                              {"extra", HandleAreaPrivRelated},
                              {"clerk", HandleAreaPrivRelated},
                              {"asstsysop", HandleAreaPrivRelated},
                              {"sysop", HandleAreaPrivRelated},

                              {"end", HandleAreaEnd},
                              {NULL, 0}};

static XLATTABLE xtArea[] = {{NULL, NULL, 0}};


CVTSTATE HandleTopSystem(CVTPARM *pcp)
{
    (void)pcp;
    return CS_SYSTEM;
}

CVTSTATE HandleTopMatrix(CVTPARM *pcp)
{
    (void)pcp;
    return CS_MATRIX;
}

CVTSTATE HandleTopColour(CVTPARM *pcp)
{
    (void)pcp;
    return CS_COLOUR;
}

CVTSTATE HandleTopLanguage(CVTPARM *pcp)
{
    (void)pcp;
    return CS_LANGUAGE;
}

CVTSTATE HandleTopSession(CVTPARM *pcp)
{
    (void)pcp;
    return HandleSessionBegin(pcp);
}


CVTSTATE HandleTopMenu(CVTPARM *pcp)
{
    memset(&md, 0, sizeof md);
    md.szName = sstrdup(pcp->szWords[1]);
    return CS_MENU;
}


CVTSTATE HandleTopArea(CVTPARM *pcp)
{
    memset(&ad, 0, sizeof ad);
    ad.szName = sstrdup(pcp->szWords[1]);
    *pcp->szLine = 0;
    return CS_AREA;
}


CVTSTATE HandleTopInclude(CVTPARM *pcp)
{
    char *szFile;

    //  printf("Handling include: 0=%s, 1=%s\n", pcp->szWords[0], pcp->szWords[1]);

    if (pfsCur + 1 == afsStack + MAX_FILE_STACK)
    {
        printf("Error!  Too many nested includes.  (Tried to include '%s'.)\n", pcp->szWords[1]);
        return csState;
    }


static XLATTABLE xtTop[] = {{"Enter_Msg", "Msg_Enter", 0}, {NULL, NULL, 0}};


dword SqHash(byte *f)
{
    dword hash = 0, g;
    char *p;

    for (p = f; *p; p++)
    {
        hash = (hash << 4) + (dword)tolower(*p);

        if ((g = (hash & 0xf0000000L)) != 0L)
        {
            hash |= g >> 24;
            hash |= g;
        }
    }


static void set_status(char *pszName)
{
    char szMsg[PATHLEN];

    if (wWorking)
        WinClose(wWorking);

    sprintf(szMsg, "Converting file %s...", pszName);
    wWorking = WinStatus(szMsg);
}

void Unknown(char *szWhat, char *szValue)
{
    char msg[256];

    sprintf(msg, "Unknown %s on line %d of %s:\n'%s'", szWhat, pfsCur->iLine, pfsCur->szInName,
            szValue);

    WinInfo(msg);
}

char *fchar(char *str, char *delim, int wordno)
{
    char *s;

    if ((s = firstchar(str, delim, wordno)) == NULL)
        return str + strlen(str);

    return s;
}


static void CvtInit(void)
{

    memset(ptsTables, 0, sizeof ptsTables);
    ptsTables[CS_TOP].ptt = ttTop;
    ptsTables[CS_TOP].pxt = xtTop;
    ptsTables[CS_TOP].fHaltOutput = FALSE;
    ptsTables[CS_SYSTEM].ptt = ttSystem;
    ptsTables[CS_SYSTEM].pxt = xtSystem;
    ptsTables[CS_SYSTEM].fHaltOutput = FALSE;
    ptsTables[CS_MATRIX].ptt = ttMatrix;
    ptsTables[CS_MATRIX].pxt = xtMatrix;
    ptsTables[CS_MATRIX].fHaltOutput = FALSE;
    ptsTables[CS_MENU].ptt = ttMenu;
    ptsTables[CS_MENU].pxt = xtMenu;
    ptsTables[CS_MENU].fHaltOutput = FALSE;
    ptsTables[CS_AREA].ptt = ttArea;
    ptsTables[CS_AREA].pxt = xtArea;
    ptsTables[CS_AREA].fHaltOutput = TRUE;
    ptsTables[CS_COLOUR].ptt = ttColour;
    ptsTables[CS_COLOUR].pxt = xtColour;
    ptsTables[CS_COLOUR].fHaltOutput = FALSE;
    ptsTables[CS_SESSION].ptt = ttSession;
    ptsTables[CS_SESSION].pxt = xtSession;
    ptsTables[CS_SESSION].fHaltOutput = FALSE;
    ptsTables[CS_EVENT].ptt = ttEvent;
    ptsTables[CS_EVENT].pxt = xtEvent;
    ptsTables[CS_EVENT].fHaltOutput = FALSE;
    ptsTables[CS_LANGUAGE].ptt = ttLanguage;
    ptsTables[CS_LANGUAGE].pxt = xtLanguage;
    ptsTables[CS_LANGUAGE].fHaltOutput = FALSE;
}


static void near set_extension(char *szName, char *szNewExt)
{
    char *szLastDot;
    char *szLastPath;

    szLastDot = strrchr(szName, '.');
    szLastPath = strrstr(szName, "\\/:");

    if (szLastDot && (!szLastPath || (szLastPath && szLastPath < szLastDot)))
        szLastDot[1] = '\0';

    if (!szLastDot)
        strcat(szName, ".");

    strcat(szName, szNewExt);
}


static void fatal_file_err(char *szErrFmt, char *szName)
{
    char szMsg[PATHLEN];
    strcpy(szMsg, " Fatal error ");
    sprintf(szMsg + strlen(szMsg), szErrFmt, szName);
    strcat(szMsg, ".");

    WinInfo(szMsg);
    WinExit(1);
}


void StripComment(char *szLine)
{
    char *p;

    p = strchr(szLine, '\n');

    if (p)
        *p = 0;

    while (*szLine)
    {
        if (isalpha(*szLine))
            break;
        else if (ispunct(*szLine))
        {
            *szLine = '\0';
            break;
        }

        szLine++;
    }
}


static void do_xlat(CVTPARM *pcp, XLATTABLE *pxt)
{

            if ((psz == pcp->szLine || strchr(szCtlDelim, psz[-1]) || !psz[-1]) &&
                (strchr(szCtlDelim, psz[iLen]) || !psz[iLen]))
            {
                int iDiff = strlen(pxt->szTo) - strlen(pxt->szFrom);

            }
        }

        pxt++;
    }
}


static void handle_keyword(CVTPARM *pcp, TRANSLATOR *pttTable)
{
    TRANSLATOR *ptt;

    for (ptt = pttTable; ptt->szKeyword; ptt++)
    {
        if (eqstri(pcp->szKeyword, ptt->szKeyword) || *ptt->szKeyword == '*')
        {

static void CvtParse(void)
{
    char szTemp[MAX_CTL_LINE];
    char szLine[MAX_CTL_LINE];
    char szStrippedLine[MAX_CTL_LINE];
    char szKeyword[MAX_CTL_LINE];
    int iWord;
    CVTPARM cp;
    CVTSTATE csOld;

    while (fgets(szLine, MAX_CTL_LINE, pfsCur->fpIn))
    {
        pfsCur->iLine++;

        strcpy(szStrippedLine, szLine);
        StripComment(szStrippedLine);


        cp.szLine = szLine;
        cp.szStrippedLine = szStrippedLine;
        cp.szKeyword = szKeyword;


        do_xlat(&cp, xtTop);

        if (ptsTables[csState].pxt)
            do_xlat(&cp, ptsTables[csState].pxt);


        for (iWord = 0; cp.szWords[iWord]; iWord++)
            free(cp.szWords[iWord]);


static void CvtFile(char *pszName)
{
    char szOldName[PATHLEN];
    set_status(pszName);

    strcpy(pfsCur->szInName, pszName);
    strcpy(pfsCur->szOutName, pszName);
    set_extension(pfsCur->szOutName, "$3$");

    if (fexist(pfsCur->szOutName) && !query_overwrite(pfsCur->szOutName))
    {
        WinInfo(" Conversion aborted! ");
        WinExit(1);
    }

    pfsCur->fpIn = fopen(pfsCur->szInName, "r");
    pfsCur->fpOut = fopen(pfsCur->szOutName, "w");
    pfsCur->iLine = 0;

    if (!pfsCur->fpIn)
        fatal_file_err("opening %s for read", pfsCur->szInName);

    if (!pfsCur->fpOut)
        fatal_file_err("opening %s for write", pfsCur->szOutName);

    CvtParse();

    fclose(pfsCur->fpOut);
    fclose(pfsCur->fpIn);


    strcpy(szOldName, pfsCur->szInName);
    set_extension(szOldName, "v2");
    unlink(szOldName);
    rename(pfsCur->szInName, szOldName);
    rename(pfsCur->szOutName, pfsCur->szInName);
}

void CvtConfig(char *szCfg, char *szPrm)
{
    FILE *fp;

    set_status(szCfg);

    if ((fp = fopen(szCfg, "a")) == NULL)
        fatal_file_err("opening %s for append", szCfg);

    fprintf(fp, "\nSET MAXIMUS=%s\n", szPrm);

static void CvtTag(char *szTag)
{
    struct _mtagidx mti;
    struct _tagdata td;
    char szOutIdx[PATHLEN];
    char szOutDat[PATHLEN];
    int fdBbs, fdIdx, fdDat;

    set_status(szTag);

    strcpy(szOutIdx, szTag);
    strcpy(szOutDat, szTag);

    set_extension(szOutIdx, "idx");
    set_extension(szOutDat, "dat");


        memset(buf, 0, sizeof buf);
        strcpy(buf, td.areas);

        if (*buf != 1)
        {
            memmove(buf + 1, buf, strlen(buf) + 1);
            *buf = 1;
        }

        if (buf[strlen(buf) - 1] != 1)
            strcat(buf, "\x01");

        mti.dwUserHash = SqHash(td.name);

        if (strlen(buf) == 1)
            memset(&mti, 0, sizeof mti);
        else
        {
            mti.dwOffset = tell(fdDat);
            mti.dwUsed = strlen(buf);


static void CvtEvents(char *szFilespec)
{
    struct _evtlist
    {
        struct _evtlist *next;
        char *szName;
    };

    struct _evtlist *pevList;
    struct _evtlist *pevNext;
    struct _evtlist *pev;
    FFIND *ff;
    char *pszSlash;
    char szName[PATHLEN];

    ff = FindOpen(szFilespec, 0);

    pszSlash = strrstr(szFilespec, ":\\/");

    if (pszSlash)
        pszSlash[1] = 0;

    csState = CS_EVENT;

    pevList = NULL;


    for (pev = pevList; pev; pevNext = pev->next, free(pev), pev = pevNext)
    {
        if (pev->szName)
        {
            CvtFile(pev->szName);
            free(pev->szName);
        }
    }
}


void set_files_base(char *szBase)
{
    sprintf(szEventName, "%sEvent*.Bbs", szBase);
    sprintf(szTagName, "%sMtag.Bbs", szBase);
    sprintf(szUserName, "%sUser.Bbs", szBase);
#ifdef OS_2
    sprintf(szConfigName, "%c:\\Config.Sys", (char)cBootDrive);
#else
    sprintf(szConfigName, "%c:\\Autoexec.Bat", (char)cBootDrive);
#endif
}


MenuFunction(ValFile)
{
    NW(opt);

    fancy_str(opt->data);
    _TuiMenuOptNormal(opt);

    return 0;
}


TIT_DIALOG(dlgCvt, -1, -1, BORDER_SINGLE, 0, 58, 17, "´ Maximus 2.0 to Maximus 3.0 Conversion Ã")
DLG_INF("Please select the operations that you wish to perform:", 0, 1)

DLG_CHK("1; Extract " VERSION " ~files", 1, 3, &fExtractFiles)
DLG_CHK("1; Convert c~ontrol files", 1, 4, &fCvtCtl)
DLG_CHK("1; Convert ~event files", 1, 5, &fCvtEvt)
DLG_CHK("1; Convert ~tag file", 1, 6, &fCvtTag)
#ifdef OS_2
DLG_CHK("1; Add to CONFIG.~SYS", 1, 7, &fCvtConfig)
#else
DLG_CHK("1; Add to AUTOEXEC.~BAT", 1, 7, &fCvtConfig)
#endif
DLG_CHK("1; ~Recompile CTL/MEC/MEX/MAD", 1, 8, &fRecompile)

DLG_STV("24:60;", 31, 4, szCtlName, ValFile)
DLG_STV("24:60;", 31, 5, szEventName, ValFile)
DLG_STV("24:60;", 31, 6, szTagName, ValFile)
DLG_STV("24:60;", 31, 7, szConfigName, ValFile)

DLG_OK(";  ~OK  ", 13, 11)
DLG_CAN(";~Cancel", 26, 11)
END_MENU


void PerformConversion(void)
{
    static char szTemp[512];
    char *p;

    CvtInit();

    strcpy(szNewPrm, szCtlName);

    p = stristr(szNewPrm, ".ctl");

    if (p)
        strcpy(p, ".prm");
    else
        strcat(p, ".prm");

    if (fExtractFiles)
    {
        if (!DoUpgradeExtract())
            WinExit(1);
    }

    if (fCvtConfig)
        CvtConfig(szConfigName, szNewPrm);
    else
    {
        sprintf(szTemp,
                " WARNING!  You have selected to continue\r\n"
#ifdef OS_2
                " without updating your CONFIG.SYS for the\r\n"
#else
                " without updating your AUTOEXEC.BAT for the\r\n"
#endif
                " new version of Maximus.  You must add the\r\n"
                " following line manually:\r\n\r\n"

                "     SET MAXIMUS=%s",
                szNewPrm);

        WinInfo(szTemp);
    }

    if (fCvtCtl)
        CvtFile(szCtlName);

    if (fCvtEvt)
        CvtEvents(szEventName);

    if (fCvtTag)
        CvtTag(szTagName);

    if (fRecompile)
        recompile_system();

    if (wWorking)
    {
        WinClose(wWorking);
        wWorking = 0;
    }

    if (fCvtConfig)
    {
        WinInfo(" Conversion complete!  You must now\r\n"
                " reboot your system before running\r\n"
                " Maximus.\r\n\r\n"
#ifdef OS_2
                " You must also run \"CVTUSRP -P\" to convert\r\n"
#else
                " You must also run \"CVTUSR -P\" to convert\r\n"
#endif
                " your Maximus user file.\r\n\r\n"

                " Please read the README file for other\r\n"
                " important information on completing\r\n"
                " the conversion!");
    }
    else
    {
        WinInfo(" Conversion complete!");
    }
}
