// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_main.c,v 1.2 2003/06/04 23:46:22 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_main
#define MAX_INCL_COMMS
#define INCL_NOPM
#define INCL_DOS

#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#ifdef UNIX
#include <sys/utsname.h>
#endif

#ifdef OS_2
#include <os2.h>
#endif

#include "alc.h"
#include "events.h"
#include "ffind.h"
#include "max_area.h"
#include "max_main.h"
#include "max_menu.h"
#include "mm.h"
#include "prog.h"
#include "userapi.h"

static void near Yell(void);
static void near Max_Version(void);
static void near Compilation_Data(void);
static void near Goodbye(void);

int Exec_Main(int type, char **result)
{
    *result = NULL;

    switch (type)
    {

static void near get_random_tune(char *file, char *tune)
{
    char *line;
    unsigned num_tune = 0;
    FILE *fp;


    if ((line = malloc(PATHLEN)) != NULL)
        while (fgets(line, PATHLEN, fp))
            if (*line == '*')
                num_tune++;

    fclose(fp);


static int near Yell_Beep(struct _event *e)
{
    if (*e->tune && *PRM(tune_file) && prm.noise_ok && (usr.bits & BITS_NERD) == 0)
    {
        char tune[32];

        strcpy(tune, e->tune);

        if (eqstri(tune, "random"))
            get_random_tune(PRM(tune_file), tune);

        play_tune(PRM(tune_file), tune, yellchk, multitasker == MULTITASKER_desqview);
    }
    else
    {
        if (loc_kbhit() || mdm_avail() || !chatreq)
            return -1;

        Mdm_putc('\x07');

        Delay(85);

        if (prm.noise_ok && (usr.bits & BITS_NERD) == 0)
            Local_Beep(1);
    }

    return 0;
}

static void near Yell(void)
{
    struct _event ye;
    char temp[PATHLEN];
    unsigned gotit;
    unsigned yells;

    chatreq = TRUE;
    ci_paged();

    logit(log_user_yelling, usr.name);


    gotit = GetEvent(EFLAG_YELL, 0, &ye, TRUE);


    if (gotit && ye.data2 && num_yells >= ye.data2)
    {
        ci_paged_ah();
        gotit = FALSE;
    }

    if (gotit)
    {

        if (!loc_kbhit() && chatreq)
        {
            sprintf(temp, "%sNOTIN.?BS", PRM(misc_path));

            if (fexist(temp))
            {
                *strrchr(temp, '.') = '\0';
                Display_File(0, NULL, temp);
            }
            else
            {
                Puts(il_nest_pas_ici);
                Press_ENTER();
            }
        }
    }

    Compilation_Data();

#ifdef HCC
    Printf(YELLOW "Licensed for use by members of the Dutch HCC.\n\n");
#endif

#if !defined(NT) && !defined(UNIX)
#if defined(OS_2)
#ifdef __FLAT__
    DosDevConfig(&id, DEVINFO_MODEL);
    DosDevConfig(&subid, DEVINFO_SUBMODEL);
#else
    DosDevConfig(&id, DEVINFO_MODEL, 0);
    DosDevConfig(&subid, DEVINFO_SUBMODEL, 0);
#endif
#elif defined(__MSDOS__)
    id = *(char far *)MK_FP(0xffffu, 0x000e);
    subid = 0;
#else
#error Unknown OS
#endif

    Puts(computer_type);

    switch (id)
    {
    case 0xff:
        Puts(class_pc);
        break;

    case 0xfe:
        Puts(class_xt);
        break;

    case 0xfd:
        Puts(class_pcjr);
        break;

    case 0xfc:
        switch (subid)
        {
        case 0x02:
            Puts(class_ps2_xt);
            break;

        case 0x04:
            Printf(class_ps2_mod, 50);
            break;

        case 0x05:
            Printf(class_ps2_mod, 60);
            break;

        int ver = GetVersion();

        Printf("Windows%s Version %u.%02u\n", (ver & 0xff) >= 4 ? "95" : " NT", ver & 0xff,
               (ver >> 8) & 0xff);
#else
        OSVERSIONINFO vi;
        int ver;

        GetVersionExA(&vi);

        Printf("Windows%s Version %u.%02u (build %d)\n",
               vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ? "95" : " NT", vi.dwMajorVersion,
               vi.dwMinorVersion, vi.dwBuildNumber);
#endif
    }
#elif defined(OS_2)
    {
        int osmajor = _osmajor;
        int osminor = _osminor;

        if (_osmajor == 20 && _osminor >= 30)
        {
            osmajor = 30;
            osminor = (_osminor - 30) * 10;
        }

        Printf(os2_ver, osmajor / 10, osminor);
    }
#elif defined(__MSDOS__)

    {
        struct _fossil_info finfo;

        if (_osmajor > 9)
            Printf(os2_dosbox, _osmajor / 10, _osminor);
        else
            Printf(dos_ver, _osmajor, _osminor);

        fossil_inf(&finfo);
        Printf(fossil_ver, finfo.id);
    }

#elif defined(UNIX)
    {
        struct utsname name;

        if (uname(&name) == 0)
            Printf("%s %s, running on %s hardware (%s)\n", name.sysname, name.release, name.machine,
                   name.nodename);
        else
            Printf("Unknown UNIX-type platform\n");
    }
#else
#error Unknown OS
#endif

    {
        char temp[40];
        Printf(heap_mem, commaize((long)coreleft(), temp));
    }

    Puts(WHITE);
    Press_ENTER();
}

static void near Compilation_Data(void)
{
#if defined(__WATCOMC__)
#ifdef __FLAT__
#define COMPILER "WATCOM C/32"
#else
#define COMPILER "WATCOM C/16"
#endif
#elif defined(__TURBOC__)
#define COMPILER "Turbo C"
#elif defined(_QC)
#define COMPILER "Microsoft Quick C"
#elif defined(__MSC__)
#define COMPILER "Microsoft C"
#elif defined(__ZTC__)
#define COMPILER "Zortech C"
#elif defined(__GNUC__)
#define COMPILER "GNU C"
#else
#error Unknown compiler type!
#endif

#if defined(_MSC_VER)
#if _MSC_VER > 0
#define COMPSTR " v%d.%d"
#define COMPVERMAJ (_MSC_VER / 100)
#define COMPVERMIN (_MSC_VER % 100)
#endif
#elif defined(__WATCOMC__)
#define COMPSTR " v%d.%d"
#define COMPVERMAJ (__WATCOMC__ / 100)
#define COMPVERMIN (__WATCOMC__ % 100)
#elif defined(__TURBOC__)
#define COMPSTR " v%d.%d"
#define COMPVERMAJ (__TURBOC__ / 0x100)
#define COMPVERMIN (__TURBOC__ % 0x100)
#else
#define COMPSTR
#define COMPVERMAJ 0
#define COMPVERMIN 0
#endif

    Printf(compiled_on, comp_date, comp_time);

    Printf(COMPILER COMPSTR ")\n", COMPVERMAJ, COMPVERMIN);
}

int UserList(void)
{
    HUF huf;
    HUFF huff;
    HUFFS huffs;

    char string[BUFLEN];
    char search[BUFLEN];

    int found, ret;
    int searchname, searchalias;
    int go;

    char nonstop;


    go = FALSE;

    if (*search)
    {
        if ((huffs = UserFileFindSeqOpen(huf)) != NULL)
            go = TRUE;
    }
    else
    {
        if ((huff = UserFileFindOpen(huf, NULL, NULL)) != NULL)
            go = TRUE;
    }

    if (go)
    {
        int showallusers = acsflag(CFLAGA_UHIDDEN);

        if (showallusers)
            searchname = searchalias = TRUE;
        else
        {
            searchname = (prm.flags & FLAG_alias) == 0;
            searchalias = (prm.flags & FLAG_alias);
        }

        do
        {
            struct _usr user;

            if (*search)
                user = huffs->usr;
            else
                user = huff->usr;

            if (halt())
            {
                ret = -1;
                break;
            }


void Statistics(void)
{
  char temp[PATHLEN];
  union stamp_combo stamp;

  Timestamp_Format(PRM(dateformat),Get_Dos_Date(&stamp),temp);
  Printf(ustat1,temp);

  Timestamp_Format(PRM(timeformat),&stamp,temp);
  Puts(temp);
  Putc('\n');
  Putc('\n');

  Puts(ustat2);
  Printf(ustat3,timeonline());
  Printf(ustat4,timeleft());

  if (usr.time)
    Printf(ustat5,usr.time);

  Printf(ustat6,usr.times);

  Puts(ustat7);
  Printf(ustat8,usr.up);
  Printf(ustat9,usr.down);

  if (usr.downtoday)
    Printf(ustat10,usr.downtoday);
  
  Printf(ustat10_5, prm.cls[cls].max_dl - usr.downtoday);

  if (usr.credit || usr.debit)
  {
    Puts(ustat11);
    Printf(ustat12,usr.credit);
    Printf(ustat13,usr.debit);
  }
  
  if (usr.xp_flag & (XFLAG_EXPDATE | XFLAG_EXPMINS))
  {
    Puts(ustat14);

    if (usr.xp_flag & XFLAG_EXPMINS)
      Printf(ustat15, (long)usr.xp_mins-(long)timeonline());

    if (usr.xp_flag & XFLAG_EXPDATE)
      Printf(ustat16, FileDateFormat(&usr.xp_date,temp));
  }

  Putc('\n');
}

#endif

static void near Goodbye(void)
{
    BARINFO bi;
    MAH ma;
    char *where;

    char string[PATHLEN];

    memset(&ma, 0, sizeof ma);

    if (!local)
    {
        WhiteN();

        sprintf(string, "%swhy_hu", PRM(misc_path));

        if (GetListAnswer(CYnq, string, useyforyes, 0, disconnect) == NO)
            return;

        WhiteN();

        where = *PRM(cmtarea) ? PRM(cmtarea) : zero;

        if (ReadMsgArea(ham, where, &ma) && ValidMsgArea(NULL, &ma, VA_VAL | VA_OVRPRIV, &bi) &&
            PushMsgArea(where, &bi))
        {
            sprintf(string, "%swhy_fb", PRM(misc_path));

            if (GetListAnswer(yCNq, string, useyforyes, 0, leave_msg, PRM(sysop)) == YES)
                Goodbye_Comment();

            PopMsgArea();
        }

        do_caller_vanished = FALSE;

        Display_File(0, NULL, PRM(byebye));

        Printf(bibi, usrname);
    }

    mdm_hangup();
}

#ifdef OS_2

    DosSleep(duration);
}
#endif

static void *near YellSblastInit(void)
{
#ifndef OS_2
    return 0;
#else
    struct _sbinfo *psb;
    HMODULE hmod;
    ULONG rc;

    if (getenv("OS2BLASTER") == NULL)
        return 0;


    if ((psb = malloc(sizeof(struct _sbinfo))) == NULL)
        return NULL;

    psb->hmod = hmod;

#ifdef __FLAT__
    if ((rc = DosQueryProcAddr(psb->hmod, 0L, "SBLASTINIT32", (PFN *)(void *)&psb->SblastInit)) !=
            0 ||
        (rc = DosQueryProcAddr(psb->hmod, 0L, "SBLASTTERM32", (PFN *)(void *)&psb->SblastTerm)) !=
            0 ||
        (rc = DosQueryProcAddr(psb->hmod, 0L, "SBLASTFMOUTALL32",
                               (PFN *)(void *)&psb->SblastFMOutAll)) != 0 ||
        (rc = DosQueryProcAddr(psb->hmod, 0L, "SBLASTFMNOTEALL32",
                               (PFN *)(void *)&psb->SblastFMNoteAll)) != 0)
#else
    if ((rc = DosGetProcAddr(psb->hmod, "SBLASTINIT", (PFN far *)(void far *)&psb->SblastInit)) !=
            0 ||
        (rc = DosGetProcAddr(psb->hmod, "SBLASTTERM", (PFN far *)(void far *)&psb->SblastTerm)) !=
            0 ||
        (rc = DosGetProcAddr(psb->hmod, "SBLASTFMOUTALL",
                             (PFN far *)(void far *)&psb->SblastFMOutAll)) != 0 ||
        (rc = DosGetProcAddr(psb->hmod, "SBLASTFMNOTEALL",
                             (PFN far *)(void far *)&psb->SblastFMNoteAll)) != 0)
#endif
    {
        logit("!QueryProcAddr returned %d", rc);
        psb->SblastInit = 0;
        psb->SblastTerm = 0;
        psb->SblastFMOutAll = 0;
        psb->SblastFMNoteAll = 0;
    }

    psb->use_sb = FALSE;

#ifdef __FLAT__
#define dothunk32to16(v) *(long *)&v = thunk32to16(*(long *)&v)

    dothunk32to16(psb->SblastInit);
    dothunk32to16(psb->SblastTerm);
    dothunk32to16(psb->SblastFMOutAll);
    dothunk32to16(psb->SblastFMNoteAll);
#endif

    if (psb->SblastInit && (*psb->SblastInit)(0x220, 7) == 0)
    {
        psb->use_sb = TRUE;


#ifndef __FLAT__
        DosGetPrty(PRTYS_PROCESS, &psb->usOldPrty, 0);
        DosSetPrty(PRTYS_PROCESS, PRTYC_FOREGROUNDSERVER, 0, 0);
#endif

        psb->pfnOldNoise = noisefunc;
        noisefunc = sbnoise;


        (*psb->SblastFMOutAll)(0xb0, 0);
        (*psb->SblastTerm)();


        noisefunc = psb->pfnOldNoise;
    }

    DosFreeModule(psb->hmod);
    free(psb);
    spsb = NULL;
#endif
}

