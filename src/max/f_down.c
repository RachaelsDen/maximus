// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_down.c,v 1.1.1.1 2002/10/01 17:51:03 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_chat
#define MAX_INCL_COMMS

#include "f_down.h"
#include "alc.h"
#include "dr.h"
#include "f_idx.h"
#include "ffind.h"
#include "max_file.h"
#include "pdata.h"
#include "prog.h"
#include "xmodem.h"
#include "zsjd.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>

static word fsent = 0;
static word near expd;

void File_Download(char *mname)
{
    struct _css css;

    for (fn = 0; GetFileEntry(fn, &fent); fn++)
        if (fent.fFlags & FFLAG_TAG)
            break;

    if (fn == FileEntries())
        Free_Filenames_Buffer(0);

    hangup = File_Get_Download_Names(TAG_NONE, protocol);


            if (hangup && Shall_We_Continue(10, file_hangup_text))
                mdm_hangup();
        }
    }

    ChatRestoreStatus(&css);
}

int File_Get_Download_Names(int do_tag, sword protocol)
{
    FFIND *ff;

    byte *fpath = NULL;

    byte *namebuf, *newfn = NULL, *no_path = NULL;
    byte *p;

    int fBreakLoop, ret;
    word notinlist, flag, fn;
    sword gotret;

    FENTRY fent;

    if (local)
        baud = 38400L;

#define NAMEBUFLEN 255

    if ((namebuf = malloc(NAMEBUFLEN)) == NULL || (newfn = malloc(NAMEBUFLEN)) == NULL ||
        (no_path = malloc(NAMEBUFLEN)) == NULL || (fpath = malloc(PATHLEN)) == NULL)
    {
        if (namebuf)
        {
            if (newfn)
            {
                if (no_path)
                    free(no_path);

                free(newfn);
            }

            free(namebuf);
        }

        logit(mem_none);
        return -1;
    }

    ret = FALSE;

    if (do_tag != TAG_ONELINE)
        Putc('\n');


    do
    {
        word breakout = FALSE;

            }
        }
        else
        {

            InputGetsLL(namebuf, NAMEBUFLEN - 1, IsBatch(protocol) ? file_dl : file1_dl,
                        FileEntries() + 1);
        }


            if (FileLimitsOkay(0L, 0, usr.def_proto, &realbytes, &realtime))
                break;
            else
            {
                Putc('\n');
                Puts(how_dl);
            }
        }


        fBreakLoop = FALSE;

        for (p = strtok(namebuf, dl_delim); p && !fBreakLoop; p = strtok(NULL, dl_delim))
        {
            char *cpnp;

            if (*p == '/')
            {
                p[1] = (byte)toupper(p[1]);

                {
                    ret = TRUE;
                    breakout = TRUE;
                    break;
                }

            strcpy(no_path, p);
            Strip_Path(no_path);


            cpnp = strdup(no_path);

            expd = EXP_NONE;
            flag = 0;
            notinlist = FALSE;



            if ((ff = FindOpen(newfn, 0)) == NULL && !strchr(no_path, '.'))
            {
                strcat(newfn, dot_star);
                strcat(no_path, dot_star);

                ff = FindOpen(newfn, 0);
            }

            if (ff == NULL)
            {
                if (InFileList(&fah, no_path, &flag, fpath) == DL_NOTFOUND)
                    notinlist = TRUE;
                else
                {
                    strcpy(newfn, fpath);
                    strcat(newfn, no_path);

                    ff = FindOpen(newfn, 0);
                }
            }

            if (ff)
            {
                do
                {

                if (cpnp == NULL)
                {

                    strcpy(no_path, cpnp);
                    free(cpnp);
                    cpnp = NULL;
                }

                IndexSearch(no_path, do_tag, protocol);


                if (expd == EXP_NONE && !strchr(no_path, '.'))
                {
                    strcat(no_path, ".*");

                    IndexSearch(no_path, do_tag, protocol);
                }


        if (!IsBatch(protocol) && FileEntries() > 1)
        {
            Puts(file_only1);
            Free_Filenames_Buffer(1);
        }

        for (fn = 0; GetFileEntry(fn, &fent); fn++)
        {
            if (fent.fFlags & FFLAG_THIS1)
            {
                fent.fFlags &= ~FFLAG_THIS1;
                UpdFileEntry(fn, &fent);
            }
        }

        if (breakout)
            break;


    free(fpath);
    free(no_path);
    free(newfn);
    free(namebuf);

    return ret;
}

static int near CanDownload(PFAH pfah, char *name, word *flag, char *path)
{
    int fex;


    if (fex && (*flag & FFLAG_NOLIST) && acsflag(CFLAGA_FLIST))
        *flag &= ~FFLAG_NOLIST;

    return (fex && (*flag & FFLAG_NOLIST) == 0);
}

static int near FileExist(char *path, char *name)
{
    char *t = malloc(NAMEBUFLEN);
    int ret;

    if (t == NULL)
    {
        logit(mem_none);
        return FALSE;
    }

    sprintf(t, ss, path, name);

    ret = fexist(t);

    free(t);
    return ret;
}

static int near InFileList(PFAH pfah, char *name, word *flag, char *pt)
{
    char *p = strrstr(name, pdel_only);


    if (p)
        p++;
    else
        p = name;


    if (p)
        p++;
    else
        p = name;

    if ((ix = IndexOpen(name)) == NULL)
        return -1;

    do
    {

static int near FindIndexFile(struct _fidx *fidx, int do_tag, sword protocol)
{
    FAH fa = {0};
    struct _fdat fdat;
    char areaname[MAX_ALEN];
    char apath[PATHLEN];
    char fname[PATHLEN];
    int rc = 0;
    int x;


    if (FidxIsOkay(fidx, &fdat, areaname, apath, FALSE, TRUE, &fa) &&
        !eqstri(areaname, FAS(fah, name)) &&
        ((fdat.flag & (FF_FILE | FF_OFFLINE | FF_DELETED | FF_COMMENT)) == FF_FILE))
    {
        strcpy(fname, apath);
        strcat(fname, fdat.name);

        if ((fa.fa.attribs & FA_SLOW) || fexist(fname))
        {
            dword size = -1L;
            word flags = FFLAG_OK | FFLAG_THIS1;


            x = GotFile(fname, size, do_tag, protocol, flags);

            if (x == -1 || (x == 0 && AddFileEntry(fname, flags, size) == -1))
                rc = -1;
        }
    }

    DisposeFah(&fa);
    return rc;
}

static int near GotFile(char *fname, long size, int do_tag, sword protocol, int flags)
{
    long this_time = XferTime(protocol, size);

    long realbytes, realtime;
    word thisfile;

    FENTRY fent;


    for (thisfile = 0; GetFileEntry(thisfile, &fent); thisfile++)
        if (fent.szName && eqstri(No_Path(fent.szName), No_Path(fname)))
        {

    if (FileLimitsOkay(size, flags, usr.def_proto, &realbytes, &realtime))
    {
        expd |= EXP_YES;
        return 0;
    }


void MaxSentFile(word fn, word log_it, long max_time)
{
    long fsz;
    long to_add;

    FENTRY fent;

    GetFileEntry(fn, &fent);

    fsent++;

    if (fent.fFlags & FFLAG_NOTIME)
    {
        to_add = XferTime(PROTOCOL_ZMODEM, fent.ulSize);


        if (max_time != -1L)
            to_add = min(to_add, max_time);

        logit(log_free_time_dl, Add_To_Time(to_add));
    }


    if (log_it)
        logit(log_dl, protocol_letter, fent.szName);
}


static void near StageFileGetName(char *szOriginal, char *szNew)
{
    StageFileGetDir(szNew);
    strcat(szNew, No_Path(szOriginal));
}


static int near StageFile(char *szOriginal, char *szNew, int fClean)
{
    char szPath[PATHLEN];
    char *szStagePath = PRM(stagepath);
    FFIND *ff;


    StageFileGetDir(szPath);

    if (!direxist(szPath))
        if (mkdirslash(szPath) != 0)
            return FALSE;


    strcat(szPath, WILDCARD_ALL);

    if (fClean && (ff = FindOpen(szPath, 0)) != NULL)
    {
        do
        {
            StageFileGetDir(szPath);
            strcat(szPath, ff->szName);
            unlink(szPath);
        } while (FindNext(ff) == 0);

        FindClose(ff);
    }

    if (lcopy(szOriginal, szNew) != 0)
    {
        unlink(szNew);
        return FALSE;
    }

    return TRUE;
}


    int result;

    FENTRY fent;

    fsent = 0;


    Mdm_flush();
    Mdm_Flow_Off();

    vbuf_flush();


        protocol_letter = *Protocol_Name(protocol, temp);


            if (FindProtocol(protocol, pro))
            {
                zstr old_uppath;
                char **ppszDupeNames;


                if ((ppszDupeNames = malloc(FileEntries() * sizeof(char *))) == NULL)
                    logit(mem_none);
                else
                {
                    int nostage = FALSE;
                    FENTRY fent;
                    int iToSend = FileEntries();

                    memset(ppszDupeNames, 0, iToSend * sizeof(char *));


                                    ppszDupeNames[fn] = strdup(fent.szName);
                                    fent.szName = temp;
                                }
                            }

                            UpdFileEntry(fn, &fent);
                        }
                    }


                    last_protocol = protocol;

                    if (pro->flag & P_ERL)
                        sprintf(cmd, "%d %s", prm.protoexit, pro->dlcmd);
                    else
                        strcpy(cmd, pro->dlcmd);


                    if (fah.heap)
                        strcpy(fah.heap + (fah.fa.uppath = fah.fa.cbHeap), newuppath);

                    Outside(NULL, NULL, (pro->flag & P_ERL) ? OUTSIDE_ERRORLEVEL : OUTSIDE_RUN, cmd,
                            FALSE, CTL_DOWNLOAD, RESTART_MENU, mname);


                    gotfile = MaxReadLog(pro, FALSE);


                    for (fn = 0; GetFileEntry(fn, &fent); fn++)
                    {
                        if (fent.fFlags & FFLAG_STAGE)
                            UnstageFile(fent.szName);


                        if (fn < iToSend && ppszDupeNames[fn])
                        {
                            fent.szName = ppszDupeNames[fn];
                            UpdFileEntry(fn, &fent);
                            free(ppszDupeNames[fn]);
                            ppszDupeNames[fn] = 0;
                        }
                    }

                    free(ppszDupeNames);
                }
            }

            free(pro);
        }

        for (fn = 0; GetFileEntry(fn, &fent); fn++)
            if (fent.fFlags & FFLAG_SENT)
                MaxSentFile(fn, TRUE, -1L);

        for (fn = 0; GetFileEntry(fn, &fent); fn++)
            if (fent.fFlags & FFLAG_GOT)
            {
                File_Process_Uploads(0L, protocol, FAS(fah, uppath));
                break;
            }


            XferWinOpen(protocol, TRUE);

            if (protocol == PROTOCOL_ZMODEM)
            {
                if (ZmodemSendFile(NULL, TRUE, (long)iFilesLeft, lBytesLeft) != OK)
                {
                    fn = FileEntries();
                    xferstatus = FALSE;
                }
            }


                if (!(fent.fFlags & FFLAG_NOTIME) && do_timecheck && !acsflag(CFLAGA_NOTIME) &&
                    (timeleft() - (int)(XferTime(protocol, fent.ulSize) / 60L)) <= 0)
                    break;


                if (flag && FileEntries() && !IsBatch(protocol))
                {
                    Puts(down_fnam);
                    Puts(No_Path(fent.szName));
                    Puts(GRAY "\n");
                }

                start = time(NULL);

                if (protocol == PROTOCOL_ZMODEM)
                {
#define SPEC_COND 0x4242u

                    int ch;


                    if (ch == -100)
                        result = -100;
                    else if (ch == ERROR)
                        result = FALSE;
                    else if (ch == ZSKIP)
                        result = SPEC_COND;
                    else
                        result = TRUE;

                    if (flag && result && result != SPEC_COND)
                    {
                        ThruLog(fent.ulSize);
                        logit(log_dl, 'Z', fent.szName);
                    }

                    XferWinClear();
                }
                else
                {
                    result = XmTx(temp, protocol, FileEntries() - fn, realbytes, fent.szName);
                    XferWinClear();
                }


                    xferstatus = FALSE;
                    if (flag)
                    {
                        Delay(50);
                        logit(lxferaborted);
                        Puts(xferaborted);
                    }
                    break;
                }


                if (flag && (protocol == PROTOCOL_ZMODEM && result != SPEC_COND) ||
                    protocol != PROTOCOL_ZMODEM)
                {
                    start = time(NULL) - start;

                    MaxSentFile(fn, FALSE, start);
                }


                if (--iFilesLeft < 0)
                    iFilesLeft = 0;

                if ((lBytesLeft -= fent.ulSize) < 0)
                    lBytesLeft = 0;
            }


                    if (fn == FileEntries() && protocol == PROTOCOL_ZMODEM)
                        ZmodemSendFile(NULL, FALSE, 0L, 0L);
                }
                else
                {
                    result = XmTx(NULL, protocol, 0, 0, NULL);
                }

                Delay(protocol == PROTOCOL_ZMODEM ? 150 : 50);

                if (flag)
                {
                    Puts(xfercomplete);

                    if (!last_bps)
                        Putc('\n');
                    else
                    {
                        Printf(cps_rating, (long)(last_bps / 10L), last_bps * 100L / (long)baud);
                    }
                }
            }

            XferWinClose();

            (free)(cr3tab);
            (free)(crctab);
            ZmDeinitStatics();
        }
    }


    Mdm_Flow_On();

    in_file_xfer = FALSE;
    return fsent;
}

word File_Send_Files(sword protocol, char *mname, char *newuppath, int flag)
{
    char pname[PATHLEN];
    char *s;
    long realbytes;

    FENTRY fent;

    fsent = 0;


    for (fn = 0; GetFileEntry(fn, &fent); fn++)
    {

        if (current_col + strlen(s) >= TermWidth())
            Puts("\n\x19 \x06");

        Printf("%s ", cstrupr(s));
    }

    Putc('\n');


    Printf(down_fsiz, realbytes, (realbytes / 128L) + 1);


    Printf(down_fmode, Protocol_Name(protocol, pname));


    Puts(start_receive);

    if (!local)
        fsent = File_Send_Files_Sub(protocol, mname, newuppath, realbytes, 1);
    else
        Free_Filenames_Buffer(0);

    return fsent;
}


static int near FileLimitsOkay(unsigned long ulSize, int flags, sword protocol, long *realbytes,
                               long *prtime)
{
    long fsz;
    long virtbytes;
    long virttbytes;
    long virtkbs;
    long pvtime;
    int fn;

    FENTRY fent;

    for (fn = 0, *realbytes = virtbytes = virttbytes = 0L;
         fn < FileEntries() && GetFileEntry(fn, &fent); fn++)
    {

        if (fent.fFlags & FFLAG_SLOW)
            fsz = fent.ulSize;
        else
            fsz = fsize(fent.szName);


        *realbytes += fsz;
    }


    virtkbs = virtbytes / 1024L;

    *prtime = XferTime(protocol, *realbytes);
    pvtime = XferTime(protocol, virttbytes);

    if (!acsflag(CFLAGA_NOLIMIT))
    {


        if (virtkbs && (dword)(usr.down + virtkbs) > (dword)ClassGetInfo(cls, CIT_FREE_RATIO) &&
            ClassGetInfo(cls, CIT_RATIO) &&
            (usr.down + virtkbs) > (dword)ClassGetInfo(cls, CIT_RATIO) * usr.up)
        {
            ci_dlexceed();
            logit(log_exc_ratio);
            Printf(exc_ratio, ClassGetInfo(cls, CIT_RATIO));
            Display_File(0, NULL, "%sexcratio", PRM(misc_path));
            return FALSE;
        }
    }

    if (!acsflag(CFLAGA_NOTIME))
    {

            Puts(exc_time_limit);
            Display_File(0, NULL, "%sexctime", PRM(misc_path));
            return FALSE;
        }
    }

    return TRUE;
}
