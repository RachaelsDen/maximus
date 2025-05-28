// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_rip.c,v 1.2 2003/06/04 23:46:22 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS

#include "max_file.h"
#include "mm.h"
#include "prog.h"
#include "strbuf.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_RIPSENDFAIL 3
#define RS_RETRIES_MAX 3

static strbuf *ripfilebuf = NULL;
static int ripsend_failcount = 0;

static int near ripfilesent(char *szFilename)
{
    return !(!ripfilebuf || sb_inbuf(ripfilebuf, szFilename, TRUE) == (word)-1);
}

static void near addripfile(char *szFilename)
{
    if (ripfilebuf || (ripfilebuf = sb_new(STRBUFSZ)) != NULL)
    {
        if (!ripfilesent(szFilename))
        {

        Printf("\r!|0\x1b"
               "070%c0000<>\n",
               (fDisplay) ? '5' : '4');


            for (fn = 0; GetFileEntry(fn, &fent); fn++)
                addripfile(fent.szName);
        }

        Free_Filenames_Buffer(0);
    }

    return rc;
}


#define SENDRIP_FILESENT 0
#define SENDRIP_ALREADYHAS 1
#define SENDRIP_FILENOTEXIST 2
#define SENDRIP_ERROR 3

static int near sendrip(char *pszFile, int fDisplay, int force)
{
    int sendit;
    long filesize;
    char temp[PATHLEN];

    if (!hasRIP())
        return SENDRIP_ERROR;

    logit("@sendrip(%s,%s,%d)", pszFile, fDisplay ? "true" : "false", force);


    if ((filesize = fsize(temp)) == -1L)
    {


            cant_open(temp);
            return SENDRIP_FILENOTEXIST;
        }
    }

    sendit = !ripfilesent(temp);


    if (force || sendit)
    {
        int hasit = RIP_HasFile(pszFile, &filesize);

        if (hasit == -1)

            addripfile(temp);
            sendit = FALSE;
        }
    }


    if (!sendit)
    {
        if (fDisplay)
        {


            if (!FileEntries() || (sendit = ripsendbatch(fDisplay)))
            {

    else
    {


    rc = strlen(linebuf);
    while (Mdm_keyp())
        linebuf[rc++] = (byte)Mdm_getcw();
    linebuf[rc] = '\0';

    if (rc)
    {
        stacked = strdup(linebuf);
        Clear_KBuffer();
    }

    rc = -1;
    for (retries = 0; rc == -1 && retries < RS_RETRIES_MAX; ++retries)
    {
        int x;

            Mdm_getcw();

        switch (x)
        {

            {
                rc = TRUE;
                break;
            }



                else
                    rc = (*plFilesize == fsize);
            }
            break;


    if (rc == -1)
    {
        logit(log_abort_ripsend);
        if (++ripsend_failcount >= MAX_RIPSENDFAIL)
        {


            Clear_KBuffer();
            mdm_dump(DUMP_INPUT);
            Press_ENTER();
        }
    }


    return rc;
}

int RIP_SendFile(char *pszFile, int fDisplay)
{
    int rc = TRUE;
    char *p2;

    if (!hasRIP())
        return SENDRIP_ERROR;

    logit("@rip_sendfile(%s,%s)", pszFile, fDisplay ? "true" : "false");

            break;

        for (;;)
        {

        if (!filegroup)
        {
            int send_rc = sendrip(p1, fDisplay, forcesend);
            rc = (send_rc == SENDRIP_FILESENT || send_rc == SENDRIP_ALREADYHAS);
        }
        else
        {

    if (rc)
        ripsendbatch(fDisplay);

