// SPDX-License-Identifier: GPL-2.0-or-later


#define MAX_DOSOS2_SIZE_S "6.0"

#define MAX_DOS_SIZE 3000000
#define MAX_DOS_SIZE_S "4.0"

#define MAX_OS2_SIZE 3000000
#define MAX_OS2_SIZE_S "4.0"

struct _tag
{
#define TID_1 251
#define TID_2 95
#define TID_3 93
#define TID_4 16

    unsigned char id1;
    unsigned char id2;
    unsigned char id3;
    unsigned char id4;
    char str[24];
};

static word dupe_file(char *full, char *path, char *name);
static word near do_file(char *name);



static char sysr_fiz[] = "sysr.fiz";
static char sysp_fiz[] = "sysp.fiz";
static char ctl_fiz[] = "ctl.fiz";
static char lang_fiz[] = "lang.fiz";
static char misc_fiz[] = "misc.fiz";
static char hlp_fiz[] = "hlp.fiz";
static char mex_fiz[] = "mex.fiz";
static char rip_fiz[] = "rip.fiz";

#ifdef COMMERCIAL
static char doc_fiz[] = "doc.fiz";
#endif

static char szCfgName[PATHLEN];
static char szCfgSysop[PATHLEN];
static word iCfgPort;
static word iCfgSpeed;
static char szFidoAddr[PATHLEN];
static char szFidoPath[PATHLEN];
static word iFidoNodeVer;

static struct _filetab
{
    char *szName;
    {"accem.exe", 20868Lu, 29270Lu, 20143Lu, 32660Lu, 29260Lu, 32656Lu, -1, -1, -1},
    {"ans2bbs.exe", 13122Lu, 11788Lu, 12041Lu, 12006Lu, 11778Lu, 12002Lu, -1, -1, -1},
    {"ans2mec.exe", 13896Lu, 12450Lu, 12815Lu, 12634Lu, 12440Lu, 12630Lu, -1, -1, -1},
    {"ansi2bbs.exe", 13122Lu, 11788Lu, 12041Lu, 12006Lu, 11778Lu, 12002Lu, -1, -1, -1},
    {"ansi2mec.exe", 13896Lu, 12450Lu, 12815Lu, 12634Lu, 12440Lu, 12630Lu, -1, -1, -1},
    {"cvtusr.exe", 24548Lu, 24438Lu, 23373Lu, 23908Lu, 24422Lu, 24914Lu, -1, -1, -1},
    {"editcall.exe", 8610Lu, 8814Lu, 7059Lu, 8938Lu, 8818Lu, 8948Lu, -1, -1, -1},
    {"editcal.exe", 8610Lu, 8814Lu, 7059Lu, 8938Lu, 8818Lu, 8948Lu, -1, -1, -1},
    {"fb.exe", 16966Lu, 23030Lu, 15921Lu, 22202Lu, 23052Lu, 22214Lu, -1, -1, -1},
    {"maid.exe", 17808Lu, 18026Lu, 16897Lu, 18134Lu, 18030Lu, 18144Lu, -1, -1, -1},
    {"max.exe", 98112Lu, 104032Lu, 0Lu, 0Lu, 104016, 0Lu, 252288, -1, -1},
    {"maxp.exe", 0Lu, 0Lu, 351449Lu, 362996Lu, 0Lu, 366812Lu, -1, 425038, -1},
    {"max.ovl", 219216Lu, 223488Lu, 0Lu, 0Lu, 226544Lu, 0Lu, 392272, -1, -1},
    {"maxpipe.exe", 0Lu, 0Lu, 11925Lu, 0Lu, 0Lu, 10385Lu, -1, -1, -1},
    {"mecca.exe", 29516Lu, 39746Lu, 33660Lu, 43276Lu, 39736Lu, 43272Lu, -1, -1, -1},
    {"mr.exe", 23728Lu, 24634Lu, 26819Lu, 23672Lu, 23666Lu, 23710Lu, -1, -1, -1},
    {"oracle.exe", 76684Lu, 67532Lu, 82714Lu, 65076Lu, 67740Lu, 65216Lu, -1, -1, -1},
    {"scanbld.exe", 20270Lu, 20246Lu, 18115Lu, 20626Lu, 20230Lu, 20632Lu, -1, -1, -1},
    {"silt.exe", 101806Lu, 90216Lu, 69249Lu, 61238Lu, 175580Lu, 77638Lu, -1, -1, -1},
    {"accemp.exe", 0Lu, 0Lu, 20143Lu, 32660Lu, 0Lu, 32656Lu, -1, -1, -1},
    {"ans2bbsp.exe", 0Lu, 0Lu, 12041Lu, 12006Lu, 0Lu, 12002Lu, -1, -1, -1},
    {"ans2mecp.exe", 0Lu, 0Lu, 12815Lu, 12634Lu, 0Lu, 12440Lu, -1, -1, -1},
    {"cvtusrp.exe", 0Lu, 0Lu, 23373Lu, 24908Lu, 0Lu, 24914Lu, -1, -1, -1},
    {"editcalp.exe", 0Lu, 0Lu, 7059Lu, 8938Lu, 0Lu, 8948Lu, -1, -1, -1},
    {"fbp.exe", 0Lu, 0Lu, 15921Lu, 22202Lu, 0Lu, 22214Lu, -1, -1, -1},
    {"maidp.exe", 0Lu, 0Lu, 16897Lu, 18134Lu, 0Lu, 18144Lu, -1, -1, -1},
    {"meccap.exe", 0Lu, 0Lu, 33660Lu, 43276Lu, 0Lu, 43272Lu, -1, -1, -1},
    {"mrp.exe", 0Lu, 0Lu, 26819Lu, 23672Lu, 0Lu, 23710Lu, -1, -1, -1},
    {"oraclep.exe", 0Lu, 0Lu, 82714Lu, 65076Lu, 0Lu, 65216Lu, -1, -1, -1},
    {"pmsnoop.exe", 0Lu, 0Lu, 18160Lu, 0Lu, 0Lu, 18160Lu, -1, -1, -1},
    {"scanbldp.exe", 0Lu, 0Lu, 18115Lu, 20626Lu, 0Lu, 20632Lu, -1, -1, -1},
    {"siltp.exe", 0Lu, 0Lu, 69249Lu, 61238Lu, 0Lu, 77638Lu, -1, -1, -1},
};

#define FTAB_SIZE (sizeof(ftab) / sizeof(ftab[0]))


MenuFunction(ValDir)
{
    NW(opt);

    fancy_str(opt->data);

    Add_Trailing(opt->data, '\\');
    _TuiMenuOptNormal(opt);

    return 0;
}

MenuFunction(ValLanguage)
{
    if (!fDoUpgrade)
    {
        char szNewLang[PATHLEN];

        strcpy(szNewLang, szDirBase);
        strcat(szNewLang, "Lang\\");

        if (!eqstri(szNewLang, szDirLang))
        {
            WinInfo(" The language directory cannot be changed for\r\n"
                    " a new install.");

            strcpy(szDirLang, szNewLang);
        }
    }

    return ValDir(opt);
}


static void near chpath(char *dir)
{
    char to[PATHLEN];

    strcpy(to, dir);

    if (strlen(to) != 3)
        Strip_Trailing(to, '\\');

    setdisk(toupper(*to) - 'A');
    chdir(to);
}


static void near EnumerateFiles(void)
{
    int i;
    FFIND *ff;


    for (i = 0; i < FTAB_SIZE; i++)
    {
        char szFile[PATHLEN];

        sprintf(szFile, "%s%s", szDirBase, ftab[i].szName);

        if ((ff = FindOpen(szFile, 0)) != NULL)
        {
            if (ff->ulSize == ftab[i].ul300dos)
                ftab[i].iType = EXE300DOS;
            else if (ff->ulSize == ftab[i].ul300os2)
                ftab[i].iType = EXE300OS2;
            else if (ff->ulSize == ftab[i].ul200dos)
                ftab[i].iType = EXE200DOS;
            else if (ff->ulSize == ftab[i].ul201dos)
                ftab[i].iType = EXE201DOS;
            else if (ff->ulSize == ftab[i].ul200os2)
                ftab[i].iType = EXE200OS2;
            else if (ff->ulSize == ftab[i].ul201os2)
                ftab[i].iType = EXE201OS2;
            else if (ff->ulSize == ftab[i].ul202dos)
                ftab[i].iType = EXE202DOS;
            else if (ff->ulSize == ftab[i].ul202os2)
                ftab[i].iType = EXE202OS2;
            else
            {
                int fd;

                ftab[i].iType = EXEUNKNOWN;

                if ((fd = open(szFile, O_RDONLY | O_BINARY)) != -1)
                {
                    struct _tag tag;
                    long ofs = lseek(fd, -(long)sizeof(struct _tag), SEEK_END);

                    if (ofs > 0L && read(fd, (char *)&tag, sizeof tag) == sizeof tag)
                    {
                        if (tag.id1 == TID_1 && tag.id2 == TID_2 && tag.id3 == TID_3 &&
                            tag.id4 == TID_4)
                        {
                            if (strncmp(tag.str, "Max30", 5) == 0)
                            {
    }



    sprintf(szFullFrom, "%s%s", szFromDir, szName);
    sprintf(szFullTo, "%s%s", szToDir, szName);

    if (ilog)
        fprintf(ilog, "Copying %s -> %s\n", szFullFrom, szFullTo);

    canon(szFullFrom, szFullFromCanon);
    canon(szFullTo, szFullToCanon);


static int near InstallCopy200One(char *szDir, char *szFrom, char *szTo)
{
    char szFullFrom[PATHLEN];
    char szFullTo[PATHLEN];


static int near InstallCopy200File(char *szDir, int iNewFile, int i200File)
{
    if (ftab[i200File].iType == EXE200OS2 || ftab[i200File].iType == EXE201OS2 ||
        ftab[i200File].iType == EXE202OS2)
    {
        return InstallCopy200One(szDir, ftab[iNewFile].szName, ftab[i200File].szName);
    }

    return TRUE;
}

#ifdef OS_2


static void near InstallReplaceDll(char *szName)
{
    char szTo[PATHLEN];
    char szFrom[PATHLEN];

    sprintf(szFrom, "%s%s", szDirBase, szName);

    sprintf(szTo, "%c:\\Os2\\Dll\\%s", (int)ulBootDrive + 'A' - 1, szName);

    if (fexist(szTo))
    {
        if (ilog)
            fprintf(ilog, "Copying %s -> %s\n", szFrom, szTo);

        lcopy(szFrom, szTo);
    }
}

#endif


static int near InstallCopyOver200(char *szDir, int iInstDos, int iInstOs2)
{

    if (iInstOs2)
    {
        struct _dllinfo *p;

        for (p = maxdll; p->szDllName; p++)
            InstallReplaceDll(p->szDllName);
    }
#endif


static word near do_file(char *name)
{
    NW(name);
    return TRUE;
}


static word dupe_file(char *full, char *path, char *name)
{
    int doRen = FALSE;
    char new[PATHLEN];
    char *p;

    NW(path);


    if (stristr(name, ".exe") || stristr(name, ".ovl") || stristr(name, ".dll") ||
        eqstri(name, "callinfo.mec") && fsize(full) == 2476 ||
        eqstri(name, "shellbye.mec") && fsize(full) == 65 ||
        eqstri(name, "wwiv.mec") && fsize(full) == 1650 ||
        eqstri(name, "filehelp.mec") && fsize(full) == 6324 ||
        eqstri(name, "olr.mec") && fsize(full) == 3004)
    {
        doRen = TRUE;
    }


    if ((stristr(name, "mcp32.dll") || stristr(name, "mcp.exe")) && f300Upgrade)
        doRen = FALSE;

    if (eqstri(name, "english.mad") && !f300Upgrade)
    {
        long size = fsize(full);

        if (size != 63620 && size != 67435 && size != 67603 && size != 67619)
        {
            WinInfo(" INSTALL needs to install a new\r\n"
                    " version of the system language\r\n"
                    " file.  The old version will be\r\n"
                    " renamed to ENGLISH.200.");
        }

        doRen = TRUE;
    }

    if (doRen)
    {
        strcpy(new, full);


static int InstallCheckExist(int fDos, int fOs2)
{
    struct _fiztab *pf;
    static char cant_find[] = "Fatal error!  Cannot find archive file %s";
    int rc = TRUE;


            if (

static int near InstallAssertDir(char *path)
{
    if (direxist(path))
        return TRUE;

    if (make_dir(path) == -1)
    {
        WinErr("Error creating %s", path);
        return FALSE;
    }

    return TRUE;
}


static int near InstallExtractFiles(int fDos, int fOs2)
{
    long lSpaceFree = zfree(szDirBase);
    struct _fiztab *pf;


    if ((fDos && fOs2 && lSpaceFree < MAX_DOSOS2_SIZE) || (fDos && lSpaceFree < MAX_DOS_SIZE) ||
        (fOs2 && lSpaceFree < MAX_OS2_SIZE))
    {
        int rc;

        rc = WinGetYN(" WARNING!  The install program needs at\r\n"
                      " least %s megabytes of free space to install\r\n"
                      " the Maximus configuration that you have\r\n"
                      " selected, but only %ld bytes are\r\n"
                      " available.\r\n\r\n"

                      " Continue installation anyway?",

                      fDos && fOs2 ? MAX_DOSOS2_SIZE_S
                      : fDos       ? MAX_DOS_SIZE_S
                                   : MAX_OS2_SIZE_S,
                      lSpaceFree);

        if (!rc)
            return FALSE;
    }

    if (!InstallCheckExist(fDos, fOs2))
        return FALSE;

    if (!InstallCheckDirs())
    {
        WinInfo(" The entire Maximus directory tree must\r\n"
                " be present for the INSTALL program to\r\n"
                " work correctly.  The installation is\r\n"
                " aborted.");
        return FALSE;
    }

    ArcWinOpen();

    for (pf = fizzes; pf->szName; pf++)
    {
        if (pf->iOS == FIZ_ALL || (pf->iOS == FIZ_DOS && fDos) || (pf->iOS == FIZ_OS2 && fOs2))
        {
            if (pf->fExtract)
            {
#ifdef COMMERCIAL
                while (!fexist(pf->szName))
                    WinInfo(" Please insert program disk #2.");
#endif

                dearcit(pf->szName, pf->szDir, pf->dupe_file, pf->doit);
            }
        }
    }

#ifndef COMMERCIAL

static void near UpdateCtl(char *from, char *to, struct _updtab *upd, struct _xlattab *xlat,
                           void (*endfn)(BFILE out))
{
    VWIN *ctlwin;
    BFILE in, out;
    struct _xlattab *x;
    struct _updtab *u;
    SCOMBO sc;

    char line[PATHLEN];
    char w1[PATHLEN];
    char w2[PATHLEN];
    char w3[PATHLEN];
    word lc = 0;
    word nochg = FALSE;

    static char *delim = "% \t\n";

#define CTL_IBUF 8192
#define CTL_OBUF 8192

    ctlwin = WinOpen(0, 0, 6, 40, BORDER_DOUBLE, CWHITE | _BLUE, CYELLOW | _BLUE,
                     WIN_CENTRE | WIN_NOCSYNC);

    WinCursorHide(ctlwin);

    if ((in = Bopen(from, BO_RDONLY, BSH_DENYNO, CTL_IBUF)) == NULL)
    {
        WinErr("Can't open control file `%s' for read! (%d)", from, errno);

        WinExit(1);
    }

    if ((out = Bopen(to, BO_WRONLY | BO_CREAT | BO_TRUNC, BSH_DENYNO, CTL_OBUF)) == NULL)
    {
        WinErr("Can't open scratch file `%s' for write! (%d)", to, errno);
        WinExit(1);
    }

    Get_Dos_Date(&sc);

    sprintf(w1,
            "%% Updated by INSTALL v" VERSION " on %02d-%02d-%02d.\r\n"
            "%%\r\n",
            sc.msg_st.date.mo, sc.msg_st.date.da, (sc.msg_st.date.yr + 80) % 100);

    Bwrite(out, w1, strlen(w1));

    if (ctlwin)
    {
        sprintf(w1, "Updating %s", from);

        WinCenter(ctlwin, 1, w1);
        WinSync(ctlwin, TRUE);
    }


            getword(line, w1, delim, 1);
            getword(line, w2, delim, 2);
            getword(line, w3, delim, 3);


                    if (u->flag & FLAG_CZ)
                        *line = (byte)((*u->replace == '\0') ? '%' : ' ');

                    if (u->flag & FLAG_UCOM)
                        *line = ' ';


            if (xlat)
                for (x = xlat; x->find; x++)
                {
                    char *fnd;

                    if ((fnd = strstr(line, x->find)) != NULL)
                    {
                        strocpy(fnd + strlen(x->replace), fnd + strlen(x->find));
                        memmove(fnd, x->replace, strlen(x->replace));
                    }
                }
        }

        strcat(line, "\r\n");
        Bwrite(out, line, strlen(line));
    }

    if (endfn)
        (*endfn)(out);

    Bclose(in);
    Bclose(out);

    if (ctlwin)
        WinClose(ctlwin);
}


    strcpy(szHlpRep, szDirHlp);
    strcpy(szMiscRep, szDirMisc);
    strcpy(szLangRep, szDirLang);

    slbase = strlen(szDirBase);

    if (strnicmp(szHlpRep, szDirBase, slbase) == 0)
        strocpy(szHlpRep, szHlpRep + slbase);

    if (strnicmp(szLangRep, szDirBase, slbase) == 0)
        strocpy(szLangRep, szLangRep + slbase);

    if (strnicmp(szMiscRep, szDirBase, slbase) == 0)
        strocpy(szMiscRep, szMiscRep + slbase);
}

#ifdef OS_2

static void near CopyDll(char *szName)
{
    char szFrom[PATHLEN];
    char szTo[PATHLEN];
    int rc;

    sprintf(szFrom, "%s%s", szDirBase, szName);
    sprintf(szTo, "%s%s", szDirDll, szName);

#ifdef __FLAT__
    rc = DosCopy(szFrom, szTo, DCPY_EXISTING);
#else
    rc = DosCopy(szFrom, szTo, DCPY_EXISTING, 0L);
#endif

    if (rc)
    {
        sprintf(szFrom,
                " Error!  INSTALL could not write to\r\n"
                " %s. (error %d)",
                szTo, (int)rc);
        WinInfo(szFrom);
    }
}


static int near CanFindDll(char *szModule)
{
    HMODULE hmod;

    if (DosLoadModule(NULL, 0, szModule, &hmod) == 0)
    {
        DosFreeModule(hmod);
        return TRUE;
    }

    return FALSE;
}

int CanFindDlls(void)
{
    int fFind = TRUE;
    struct _dllinfo *pd;

    for (pd = maxdll; pd->szDllName; pd++)
    {
        if (!CanFindDll(pd->szModName))
        {
            fFind = FALSE;
            break;
        }
    }

    return fFind;
}


        sprintf(szDirDll, "%c:\\Os2\\Dll\\", (int)ulBootDrive + 'A' - 1);

        hDlg = TuiRegisterMenu(dlgCopyPath);
        ok = TuiExecMenu(hDlg);
        TuiDestroyMenu(hDlg);

        if (!ok)
            return FALSE;

        wWorking = WinStatus("Copying .DLL files...");

        for (pd = maxdll; pd->szDllName; pd++)
            CopyDll(pd->szDllName);

        WinClose(wWorking);
    }

    return TRUE;
}

#endif


    InstallConfigUpdate();


    unlink(szFrom);
    rename(szTo, szFrom);


void recompile_system(void)
{
    char temp[PATHLEN];
    char szOptP[PATHLEN];
    char szConfigName[PATHLEN];


#ifdef OS_2
    if (iVerType & 2)
        strcpy(szOptP, "p");
    else
#endif
        strcpy(szOptP, "");

    WinInfo(" The install program will now compile:\r\n\r\n"

            "  - the Maximus language file,\r\n"
            "  - the MEX program source files,\r\n"
            "  - the MECCA script files, and\r\n"
            "  - the system control file.");


    MouseHide();
    VidCls(CGRAY);


    sprintf(temp, "%smaid%s %senglish", szDirBase, szOptP, szDirLang);
    printf("\n>>> %s\n", temp);
    system(temp);


    chpath(szDirMex);
    sprintf(temp, "for %%f in (*.mex) do %smex%s %s%%f", szDirBase, szOptP, szDirMex);
    printf("\n>>> %s\n", temp);
    system(temp);


    WinSyncAll();
    MouseShow();
}


    if (direxist(szDirBase))
    {
        if (!WinGetYN(" WARNING!  The directory:\r\n"
                      "    %s\r\n"
                      " already exists.  Installing to this directory will\r\n"
                      " destroy any existing Maximus configuration in that\r\n"
                      " existing Maximus configuration\r\n"
                      " location.\r\n\n"

                      " Are you sure that you want to install Maximus in the\r\n"
                      " specified directory?",
                      szDirBase))
        {
            return FALSE;
        }
    }

    do
    {
        if (iVerType == 0)
        {
            WinInfo(" Error!  INSTALL could not find the archives for\r\n"
                    " either the DOS or the OS/2 version of the program.\r\n"
                    " Please place either SYSP.FIZ or SYSR.FIZ in the\r\n"
                    " current directory before running INSTALL again.");
            return FALSE;
        }

#ifdef __MSDOS__

        if ((iVerType & 1) == 0)
        {
            WinInfo(" Error!  You need the DOS installation\r\n"
                    " file (SYSR.FIZ) to install Maximus\r\n"
                    " under DOS.");
            return FALSE;
        }
#endif


    strcpy(szCfgName, "New Maximus System");
    strcpy(szCfgSysop, "New Sysop");
    iCfgPort = 0;
    iCfgSpeed = 38400u;


    if (WinGetYN(" Are you a member of a FidoNet-technology\r\n"
                 "   network?  (Select \"no\" if unsure.)"))
    {
        hDlg = TuiRegisterMenu(dlgFido);
        ok = TuiExecMenu(hDlg);
        TuiDestroyMenu(hDlg);

        if (!ok)
            return FALSE;
    }
    else
    {
        strcpy(szFidoAddr, "0:0/0");
    }


    InstallDoControlFiles();

#ifdef OS_2


int DoUpgradeExtract(void)
{
    VWIN *wWorking;
    int iDosVer;
    int iOs2Ver;
    int ok;

    switch (ftab[MAXP_EXE].iType)
    {
    case EXE200OS2:
        iOs2Ver = 200;
        break;
    case EXE201OS2:
        iOs2Ver = 201;
        break;
    case EXE202OS2:
        iOs2Ver = 202;
        break;
    case EXE300OS2:
        iOs2Ver = 300;
        break;
    default:
        iOs2Ver = 0;
    }

    switch (ftab[MAX_EXE].iType)
    {
    case EXE200DOS:
        iDosVer = 200;
        break;
    case EXE201DOS:
        iDosVer = 201;
        break;
    case EXE202DOS:
        iDosVer = 202;
        break;
    case EXE300DOS:
        iDosVer = 300;
        break;
    default:
        iDosVer = 0;
    }

    if (!iDosVer && !iOs2Ver)
    {
        WinInfo(" Fatal error!  The install program examined\r\n"
                " the specified directory but could not locate\r\n"
                " a valid copy of Maximus (either MAX.EXE or\r\n"
                " MAXP.EXE).  Note that this program can only\r\n"
                " upgrade from Maximus 2.x or 3.x\r\n\r\n"

                " Please ensure that your existing Maximus\r\n"
                " installation is in the correct location and\r\n"
                " run the install program again.");

        return FALSE;
    }

    ok = WinGetYN(" The install program found the following\r\n"
                  " Maximus installation(s) in %s:\r\n\r\n"

                  " %s%s"
                  " %s%s\r\n"

                  " Is this correct?",

                  szDirBase, iDosVer ? "Maximus (DOS) " : "",
                  iDosVer == 200   ? "v2.00\r\n"
                  : iDosVer == 201 ? "v2.01wb\r\n"
                  : iDosVer == 202 ? "v2.02\r\n"
                  : iDosVer == 300 ? "v3.00\r\n"
                  : iDosVer == -1  ? " - unknown version!\r\n"
                                   : "",
                  iOs2Ver ? "Maximus (OS/2) " : "",
                  iOs2Ver == 200   ? "v2.00\r\n"
                  : iOs2Ver == 201 ? "v2.01wb\r\n"
                  : iOs2Ver == 202 ? "v2.02\r\n"
                  : iOs2Ver == 300 ? "v3.00\r\n"
                  : iOs2Ver == -1  ? "- unknown version!\r\n"
                                   : "");

    if (iOs2Ver && !fexist(sysp_fiz))
    {
        WinInfo(" Error!  You have instructed INSTALL to\r\n"
                " upgrade an existing Maximus-OS/2 system,\r\n"
                " but the new OS/2 executables could not be\r\n"
                " found.  Please obtain a copy of SYSP.FIZ\r\n"
                " (from " OS2ARCHIVE ") and run INSTALL again.");

        return FALSE;
    }

    if (iDosVer && !fexist(sysr_fiz))
    {
        WinInfo(" Error!  You have instructed INSTALL to\r\n"
                " upgrade an existing Maximus-DOS system,\r\n"
                " but the new DOS executables could not be\r\n"
                " found.  Please obtain a copy of SYSR.FIZ\r\n"
                " (from " DOSARCHIVE ") and run INSTALL again.");

        return FALSE;
    }

    if (!ok)
    {
        WinInfo(" The install program tries to identify your Maximus installation\r\n"
                " by checking the file sizes of MAX.EXE and MAXP.EXE.\r\n\r\n"

                " If these two files have been corrupted or modified, the install\r\n"
                " program cannot correctly identify your existing Maximus\r\n"
                " installation.\r\n\r\n"

                " Please reinstall the executables from your original Maximus\r\n"
                " distribution before continuing with the upgrade.  Note that\r\n"
                " users who are using Maximus 1.02 will need to upgrade to\r\n"
                " version 2.0 or above BEFORE running this install program.");

        return FALSE;
    }

    if (!InstallExtractFiles(iDosVer, iOs2Ver))
        return FALSE;

    wWorking = WinStatus("Updating existing Maximus executables...");

    InstallCopyOver200(szDirBase, iDosVer, iOs2Ver);

    WinClose(wWorking);

    return TRUE;
}


    strcpy(szStripLang, szDirBase);
    strcat(szStripLang, "Lang\\");

    if (!eqstri(szStripLang, szDirLang))
    {
        int rc;

        strcpy(szStripLang, szDirBase);
        strcat(szStripLang, "Lang\\");

        rc = WinGetYN(" WARNING!  The install program has detected that your language\r\n"
                      " file directory is not located in:\r\n\r\n"

                      "   %s\r\n\r\n"

                      " Although the upgrade can proceed, you must edit the following\r\n"
                      " files to reflect the correct paths before trying to recompile\r\n"
                      " your system control files:\r\n\r\n"

                      "   lang\\user.lh\r\n"
                      "   m\\language.mh\r\n\r\n"

                      " Do you wish to continue?",
                      szStripLang);

        if (!rc)
            return FALSE;
    }

    if (!WinGetYN(" Have you made a backup of your existing\r\n"
                  " Maximus installation?"))
    {
        WinInfo(" We suggest that you make a backup\r\n"
                " of your Maximus directory.  While\r\n"
                " this release has been extensively\r\n"
                " tested, there is a chance that the\r\n"
                " upgrade may not work smoothly.\r\n\r\n"

                " Please re-run the install program\r\n"
                " after you have backed up your system.");

        return FALSE;
    }


        fizzes[FIZ_MISC].fExtract = FALSE;
        fizzes[FIZ_HLP].fExtract = FALSE;
        fizzes[FIZ_MEX].fExtract = FALSE;
        fizzes[FIZ_RIP].fExtract = FALSE;

        if (!DoUpgradeExtract())
            WinExit(1);

        WinInfo(" Conversion complete.");
    }
    else
    {

        hDlg = TuiRegisterMenu(&dlgCvt);
        fOk = TuiExecMenu(hDlg);
        TuiDestroyMenu(hDlg);

        if (fOk)
            PerformConversion();
    }

    return TRUE;
}


static int near TestFiles(void)
{
#if !defined(OS_2) && !defined(COMMERCIAL)
#define MIN_FD 13

    char *name = "~~test.%d";
    char temp[PATHLEN];

    int fd[MIN_FD];
    int nf, i;

    for (nf = 0; nf < MIN_FD; nf++)
    {
        sprintf(temp, name, nf);

        if ((fd[nf] = sopen(temp, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_DENYNO,
                            S_IREAD | S_IWRITE)) == -1)
            break;
    }

    for (i = 0; i < nf; i++)
    {
        close(fd[i]);
        sprintf(temp, name, i);
        unlink(temp);
    }

    if (nf != MIN_FD)
    {
        WinInfo(" Error!  Not enough file handles available.\r\n\r\n"

                " INSTALL needs more free 'file handles' than are\r\n"
                " currently available.  You must change C:\\CONFIG.SYS\r\n"
                " to allocate more files; if you don't have a CONFIG.SYS,\r\n"
                " you should create one in the root directory of drive C.\r\n\r\n"

                " In CONFIG.SYS, there should be a line that says:\r\n\r\n"

                "     FILES=30\r\n\r\n"

                " If not, add that line to the end of the file.  If the\r\n"
                " number following `FILES=' is LESS than 30, it should\r\n"
                " be increased to 30 or more.");

        return FALSE;
    }
#endif

    return TRUE;
}


#ifdef __FLAT__
    rc = DosQuerySysInfo(QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, &ulBootDrive, sizeof ulBootDrive);
#else

    rc = DosQSysInfo(5, (PBYTE)&ulBootDrive, sizeof ulBootDrive);
#endif

    if (rc)
        ulBootDrive = 3;
#else
    ulBootDrive = 3;
#endif

    cBootDrive = (char)(ulBootDrive - 1 + 'A');

#ifndef COMMERCIAL
    ilog = fopen("install.log", "a");
#endif
}

    int ok;


    iCurDisk = get_disk();

#ifdef COMMERCIAL
    (void)argc;

    iCurDisk = 2;
#else
    (void)argc;
    (void)argv;
#endif

    cCurDisk = iCurDisk + 'A';

#ifdef __MSDOS__
    if (coreleft() < 304000Lu)
    {
        WinInfo(" Error!  The install program needs to compile\r\n"
                " a number of files, but there is not enough free\r\n"
                " conventional memory to do so.  Please ensure\r\n"
                " that there is at least 560,000 bytes of free\r\n"
                " conventional memory before running INSTALL.");
        WinExit(1);
    }
#endif

#ifndef COMMERCIAL
    if (!fexist(ctl_fiz))
    {
#ifdef COMMERCIAL
        WinInfo(" Error!  The Maximus installation files must\r\n"
                " be in the current directory.  Please set the\r\n"
                " current drive to the install disk and restart\r\n"
                " INSTALL.EXE.");
        WinExit(1);
#else
        WinInfo(" Error!  The Maximus installation files (*.FIZ) must\r\n"
                " exist in the current directory.  Please change to\r\n"
                " the directory where you extracted the Maximus\r\n"
                " archives.");
        WinExit(1);
#endif
    }
#endif


    if (TestFiles())
    {

            sprintf(szDirBase, "%c:\\Max\\", cCurDisk);
            sprintf(szDirMisc, "%c:\\Max\\Misc\\", cCurDisk);
            sprintf(szDirHlp, "%c:\\Max\\Hlp\\", cCurDisk);
            sprintf(szDirLang, "%c:\\Max\\Lang\\", cCurDisk);
            sprintf(szDirMex, "%c:\\Max\\M\\", cCurDisk);
            sprintf(szDirRip, "%c:\\Max\\Rip\\", cCurDisk);

            hDlg = TuiRegisterMenu(dlgUpDir);
            ok = TuiExecMenu(hDlg);
            TuiDestroyMenu(hDlg);

            if (ok)
            {
                if (fDoUpgrade)
                    ok = InstallUpgrade();
                else
                    ok = InstallNew();

                if (!ok)
                    WinInfo(" Installation aborted.  You must\r\n"
                            " run INSTALL again to install\r\n"
                            " Maximus on your system.");
            }
        }
    }

    InstallCleanup();

    return 0;
}
