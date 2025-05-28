// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: rz.c,v 1.1.1.1 2002/10/01 17:54:41 sdudley Exp $";
#pragma on(unreferenced)

#define MAX_LANG_protocols

#include "f_up.h"
#include "pdata.h"
#include "zmodem.h"
#include "zsjd.h"
#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <stdio.h>
#include <string.h>

static FILE *fout = NULL;

int ZmRzInitStatics(void)
{
    secbuf = malloc(1025);
    Pathname = malloc(PATHLEN);

    return secbuf && Pathname;
}


static long near getfree(char *path) { return zfree(path); }


static int near procheader(char *path, char *name)
{
    char *openmode, *p;
    char szShortName[PATHLEN];


    for (p = name; *p; p++)
        if (*p == ' ')
            *p = '_';


        Thisbinary = TRUE;
    else if (zmanag == ZMAPND)
        openmode = fopen_append;

    if (Thisbinary)
        openmode = zmanag == ZMAPND ? "ab" : fopen_writeb;


    if ((prm.flags2 & FLAG2_CHECKDUPE) && FileIsDupe(No_Path(szShortName)))
    {
        logit(log_dupe_file_recd, szShortName);


        strcpy(Pathname, "*");
        strcat(Pathname, szShortName);
        return ERROR;
    }


    if (fexist(Pathname))
        unique_name(Pathname);

    Bytesleft = DEFBYTL;
    Filemode = 0;
    Modtime = 0L;

    p = name + strlen(name) + 1;

    if (*p)

    ZmStatFile(Pathname, Bytesleft, Crc32);

    dlogit(("@Opening file '%s'", Pathname));
    fout = fopen(Pathname, openmode);

    if (!fout)
    {
        logit(cantopen, Pathname);
        *Pathname = 0;
        return ERROR;
    }

    return OK;
}


static int near putsec(char *buf, int n)
{
    char *p;

    if (n == 0)
        return OK;

    if (Thisbinary)
    {
        if (fwrite(buf, 1, n, fout) != n)
        {
            logit(log_no_space, errno);
            return ERROR;
        }
    }
    else
    {
        if (Eofseen)
            return OK;

        for (p = buf; --n >= 0; ++p)
        {
            if (*p == '\r')
                continue;

            if (*p == CPMEOF)
            {
                Eofseen = TRUE;
                return OK;
            }


int
IsAnyLower(char *s)
{
  for (; *s; ++s)
    if (islower(*s))
      return TRUE;

  return FALSE;
}
#endif


static int near closeit(void)
{
    time_t time();
    int rc = 0;

    if (fout)
    {
        dlogit(("@Closing receive file"));
        rc = fclose(fout);
        fout = NULL;
    }

    if (rc != 0)
        return ERROR;

    if (Modtime)
    {
        SCOMBO sc;
        time_t t = Modtime;
        struct tm *ptm;

        ptm = localtime(&t);
        TmDate_to_DosDate(ptm, &sc);
        SetFileDate(Pathname, &sc);
    }

    return OK;
}


static void near ackbibi(void)
{
    int n;

    dlogit(("@ackbibi:"));

    stohdr(0L);

    for (n = 3; --n >= 0;)
    {
        purgeline();
        zshhdr(ZFIN, Txhdr);

        switch (readline(100))
        {
        case 'O':

static int near rzfile(char *path)
{
    int c, n;

    Eofseen = FALSE;

    if (procheader(path, secbuf) == ERROR)
        return (tryzhdrtype = ZSKIP);

    n = 20;
    Rxbytes = 0L;

    for (;;)
    {
        stohdr(Rxbytes);
        dlogit(("@rzfile1: sending zrpos %lx", rclhdr(Txhdr)));
        zshhdr(ZRPOS, Txhdr);

    nxthdr:


        switch (c = zgethdr(Rxhdr, 0))
        {
        default:
            dlogit(("@rzfile1: zgethdr returned %d", c));
            return ERROR;

        case ZNAK:
        case TIMEOUT:
            dlogit(("@rzfile2: zgethdr returned %d", c));

            if (--n < 0)
                return ERROR;

            continue;

        case ZFILE:
        {
            int temp;

            temp = zrdata(secbuf, 1024);

            dlogit(("@rzfile - zfile(zrdata)=%d", temp));
            continue;
        }

        case ZEOF:
            if (rclhdr(Rxhdr) != Rxbytes)
            {
                z_errors = 0;
                goto nxthdr;
            }

            if (closeit())
            {
                tryzhdrtype = ZFERR;
                dlogit(("@rzfile: closeit returned <> 0"));
                return ERROR;
            }

            dlogit(("@rzfile: normal EOF"));
            return c;


            switch (c = zrdata(secbuf, 1024))
            {
            case ZCAN:
                dlogit(("@rzfile4: zgethdr returned %d", c));
                return ERROR;


static int near tryz(char *path)
{
    int c, n;
    int cmdzack1flg;
    int hdr;

    for (n = 15; --n >= 0;)
    {

        if (ZmDoLocalAbort())
            return ERROR;

        hdr = zgethdr(Rxhdr, 0);
        dlogit(("@got tryz response %d", hdr));

        switch (hdr)
        {
        case ZRQINIT:
            continue;

        case ZEOF:
            continue;

        case TIMEOUT:
            continue;

        case ZFILE:
            zconv = Rxhdr[ZF0];
            zmanag = Rxhdr[ZF1];

                do
                {
                    zshhdr(ZCOMPL, Txhdr);
                } while (++z_errors < 20 && zgethdr(Rxhdr, 1) != ZFIN);

                ackbibi();
                return ZCOMPL;
            }

            zshhdr(ZNAK, Txhdr);
            goto again;

        case ZCOMPL:
            goto again;

        default:
            continue;

        case ZFIN:
            ackbibi();
            return ZCOMPL;

        case ZCAN:
            return ERROR;
        }
    }

    return 0;
}


int ZmodemRecvFile(char *path, char *name, int fInit)
{
    int c;

    fSending = FALSE;

    ThruStart();

