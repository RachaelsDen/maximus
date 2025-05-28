// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_up.c,v 1.2 2003/06/04 23:20:16 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_f_area
#define MAX_LANG_max_chat
#define MAX_INCL_COMMS

#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "zsjd.h"

#ifdef BINK_PROTOCOLS
#include "zmodem.h"
#endif

#include "alc.h"
#include "ffind.h"
#include "max_file.h"
#include "prog.h"
#ifdef BINK_PROTOCOLS
#include "prototyp.h"
#endif
#include "f_idx.h"
#include "f_up.h"
#include "xmodem.h"

#ifndef BINK_PROTOCOLS
#include "pdata.h"
#include "zsjd.h"
#endif

static word near FileIsBad(char *name);
static int near Check_Filename(char *ulpath, char *fname);
static void near Add_Upload_Bytes(long fsize);
static void near ParseXferInfo(void);
static void near FBLog(void);

    getword(inp, testbuf, dot, 2);

    if (strlen(inp) > MAX_FN_LEN || strlen(testbuf) > 3 || strpbrk(inp, " |<>") != NULL)
    {
        Display_File(0, NULL, PRM(fname_format));
        return;
    }

    if ((prm.flags2 & FLAG2_CHECKDUPE) && FileIsDupe(inp))
    {
        Printf(dupe_file, upper_fn(inp));
        Press_ENTER();
        return;
    }

    if (!acsflag(CFLAGA_ULBBSOK) && FileIsBad(inp))
        return;

    if (*inp)
        AddFileEntry(inp, 0, 0);
}


word FileIsDupe(char *name)
{
    IDXF *ix;

    char newname[PATHLEN];
    char *p;

    FDAT fdat;
    word ret = FALSE;

    strcpy(newname, name);


        if ((p = strrchr(newname, '.')) != NULL)
            *p = '\0';

        strcat(newname, ".*");
    }

    if ((ix = IndexOpen(newname)) == NULL)
        return FALSE;

    if (FidxIsOkay(&ix->fidx, &fdat, NULL, NULL, TRUE, FALSE, NULL))
        ret = TRUE;

    IndexClose(ix);
    return ret;
}

    in_file_xfer = TRUE;

    filename = NULL;

    if (IsBatch(protocol))
        Free_Filenames_Buffer(0);

    logit(log_getting_from, usr.name, baud);


    Open_OpusXfer(&xferinfo);

    Mdm_flush();
    Mdm_Flow_Off();

    ul_no_space = FALSE;

    if (protocol >= 0)
    {
        struct _proto *pro;


        if ((pro = malloc(sizeof(struct _proto))) == NULL)
            logit(mem_none);
        else
        {
            char cmd[PATHLEN];
            zstr old_uppath;


                    sprintf(fname, ss, path, No_Path(fent.szName));
                    fent.szName = fname;
                    UpdFileEntry(0, &fent);
                }
                else
                {

                MaxWriteCtl(pro, TRUE);


                old_uppath = fah.fa.uppath;
                strcpy(fah.heap + fah.fa.cbHeap, path);
                fah.fa.uppath = fah.fa.cbHeap;

                Outside(NULL, NULL, (pro->flag & P_ERL) ? OUTSIDE_ERRORLEVEL : OUTSIDE_RUN, cmd,
                        FALSE, CTL_UPLOAD, RESTART_MENU, mname);

                Free_Filenames_Buffer(0);


            for (fn = 0; GetFileEntry(fn, &fent); fn++)
                if (fent.fFlags & FFLAG_SENT)
                    MaxSentFile(fn, TRUE, -1L);

            free(pro);
        }
    }
#ifdef BINK_PROTOCOLS
    else if ((Txbuf = Secbuf = zalloc()) == NULL || (cr3tab = mkcrc32tab()) == NULL ||
             (crctab = mkcrc16tab()) == NULL)
    {
        if (Txbuf)
        {
            if (cr3tab)
                (free)(cr3tab);

            free(Txbuf);
        }
    }

                int fNoSpace = (ch == ZSKIP && *temp != '*');

                fFirst = FALSE;

                if (!fNoSpace && *temp)
                {
                    if (*temp == '*')
                        AddFileEntry(temp + 1, FFLAG_GOT | FFLAG_DUPE, -1);
                    else
                    {
                        AddFileEntry(temp, FFLAG_GOT, -1);
                        ThruLog(fsize(temp));
                        logit(log_ul, 'Z', blank_str, temp);
                    }
                }

                XferWinClear();
            }


                *temp = '\0';
                if (protocol == PROTOCOL_XMODEM || protocol == PROTOCOL_XMODEM1K)
                {
                    if (GetFileEntry(0, &fent))
                        strcpy(temp, fent.szName);
                }

                XferWinClear();
                ok = XmRx(path, temp, protocol, &eob);

                if (ok && *temp)
                {
                    int iFlag = FFLAG_GOT;
                    char *psz = temp;

                    if (*temp == '*')
                    {
                        psz++;
                        iFlag |= FFLAG_DUPE;
                    }

                    if (IsBatch(protocol))
                        AddFileEntry(psz, iFlag, -1);
                    else
                    {
                        if (GetFileEntry(0, &fent))
                        {
                            fent.fFlags |= iFlag;
                            UpdFileEntry(0, &fent);
                        }
                    }

                    if (*temp == '*')
                        break;
                }

    for (fn = 0; GetFileEntry(fn, &fent); fn++)
    {
        if (!(fent.fFlags & FFLAG_DUPE))
        {
            strcpy(temp, No_Path(fent.szName));
            fent.szName = temp;
            UpdFileEntry(fn, &fent);
        }
    }


    Mdm_Flow_On();

    in_file_xfer = FALSE;

    Close_OpusXfer(&xferinfo);


        if (*temp == '*')
        {
            Printf(dupe_file, upper_fn(temp + 1));
            Press_ENTER();
            continue;
        }


    if (fn2 || dupes)
    {

        if (carrier())
        {
            Delay(50);

            Puts(xfercomplete);

            if (last_bps)
                Printf(cps_rating, (long)(last_bps / 10L), (long)(last_bps * 100L / (long)baud));
            else
                Putc('\n');

            if (fn2 && (fn2 != dupes))
                Printf(tnx4ul, firstname);
        }


        for (fn = 0; GetFileEntry(fn, &fent); fn++)
        {
            if (fent.fFlags & FFLAG_GOT)
            {
                if (fent.fFlags & FFLAG_DUPE)
                {
                    Printf(dupe_file, upper_fn(fent.szName));
                    Press_ENTER();
                }
                else
                {
                    if (!acsflag(CFLAGA_ULBBSOK) && FileIsBad(fent.szName))
                    {


                        fent.fFlags &= ~FFLAG_GOT;
                        UpdFileEntry(fn, &fent);
                    }
                    else if (Check_Filename(path, fent.szName))
                        UpdFileEntry(fn, &fent);
                }
            }
        }


        if (carrier() && ul_start_time)
        {

            if (temp_long != 0)
            {
                long lReward = ClassGetInfo(cls, CIT_UPLOAD_REWARD);


        for (fn = 0; GetFileEntry(fn, &fent); fn++)
        {
            if ((fent.fFlags & FFLAG_GOT) && !(fent.fFlags & FFLAG_DUPE))
            {
                uploads = TRUE;

                sprintf(temp, ss, path, fent.szName);


        sprintf(from, ss, ulpath, fname);


        sprintf(to, ss, ulpath, No_Path(fname));


        move_file(from, to);


static void near FBLog(void)
{
    char temp[PATHLEN];

#if defined(__MSDOS__) || defined(NT)
    sprintf(temp, "%srunfb.bat", original_path);
#elif defined(OS_2)
    sprintf(temp, "%srunfb.cmd", original_path);
#elif defined(UNIX)
    sprintf(temp, "%srunfb.sh", original_path);
#else
#error Unknown batch file extension!
#endif

    if (fexist(temp))
    {
        Puts(please_wait);

        sprintf(temp, "runfb %s %s -u", PRM(farea_name), FAS(fah, name));
        Outside(NULL, NULL, OUTSIDE_DOS, temp, FALSE, CTL_NONE, 0, NULL);

        Puts(YELLOW);
        Putc(' ');
        Puts(done_ex);
    }
}

#if 0
static char * near comma_number(dword n)
{
  static char cbuf[20];
  char *s;
  char ch;

  sprintf(cbuf, "%lu", n);

  if (strlen(cbuf) <= 3)
    return cbuf;

  for (s=cbuf+strlen(cbuf)-3; s > cbuf; s -= 3)
  {
    strocpy(s+1, s);

    ch=*number_comma;
    *s=ch ? ch : ',';
  }

  return cbuf;
}
#endif
