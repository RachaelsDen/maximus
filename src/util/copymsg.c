// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: copymsg.c,v 1.3 2003/06/11 14:03:07 wesgarland Exp $";
#pragma on(unreferenced)

#include "dr.h"
#include "msgapi.h"
#include "old_msg.h"
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

static void *zalloc(size_t bytes)
{
    void *ret = malloc(bytes);
    if (!ret)
    {
        printf("Could not satisfy %u byte memory request\n", bytes);
        exit(3);
        return NULL;
    }
    else
        return (ret);
}

static char *_ctime(union _stampu *st)
{
    static char str[40] = "12/31/89 00:00";

    if (!st->date.da)
        return ("NULL");
    sprintf(str, "%02d/%02d/%02d %02d:%02d", st->date.mo, st->date.da, st->date.yr + 1980,
            st->time.hh, st->time.mm);
    return (str);
}

static struct _msg_attrib
{
    unsigned attrib;
    char *name;
} msg_attrib[] = {{MSGPRIVATE, "Priv "},
                  {MSGCRASH, "Crash "},
                  {MSGREAD, "Rcvd "},
                  {MSGSENT, "Sent "},
                  {MSGFILE, "File "},
                  {MSGFWD, "FWD "},
                  {MSGORPHAN, "ORPHAN "},
                  {MSGKILL, "Kill "},
                  {MSGLOCAL, "Local "},
                  {MSGHOLD, "HOLD "},
                  {MSGXX2, "XX2 "},
                  {MSGFRQ, "FREQ "},
                  {MSGRRQ, "RRQ "},
                  {MSGCPT, "CPT "},
                  {MSGARQ, "ARQ "},
                  {MSGURQ, "URQ "},
                  {0, NULL}};

#define MAXSIZ 0x8000

int copymsg(FILE *outfile, char *fname)
{
    word i, size;
    char *buf;
    int col = 0;
    char lastword[100];
    int j = 0;
    int first = TRUE;
    struct _omsg *msg;
    FILE *inf;

    fixPathMove(fname);
    inf = fopen(fname, "rb");
    if (!inf)
        return FALSE;

    buf = zalloc(MAXSIZ);
    size = fread(buf, 1, MAXSIZ, inf);
    fclose(inf);
    msg = (struct _omsg *)buf;

    *lastword = 0;
    i = 0;
    while (msg_attrib[i].name)
    {
        if (msg->attr & msg_attrib[i].attrib)
            strcat(lastword, msg_attrib[i].name);
        i++;
    }
    fprintf(outfile,
            "----------------------------------------------------------------------------\r\n");
    fprintf(outfile, "Msg : %04d %42s Prev: %04u  Next: %04u\r\n", atoi(fname), lastword,
            msg->reply, msg->up);
    sprintf(lastword, "%d/%d", msg->dest_net, msg->dest);
    fprintf(outfile, "To  : %-36s %9s  Written:%s\r\n", msg->to, lastword,
            _ctime(&msg->date_written));
    sprintf(lastword, "%d/%d", msg->orig_net, msg->orig);
    fprintf(outfile, "From: %-36s %9s  Arrived:%s\r\n", msg->from, lastword,
            _ctime(&msg->date_arrived));
    fprintf(outfile, "Subj: %s\r\n", msg->subj);

            }
            col = 0;
            j = 0;
            first = FALSE;
        }
        else if ((buf[i] & 0x7f) != '\n' && (buf[i] & 0x7f) != '\r')
        {
            lastword[j++] = buf[i];
            if (buf[i] == ' ' || j > 79)
            {
                lastword[j] = 0;
                if (first)
                {
                    first =
                fputs("\r\n", outfile);
                col = 0;
            }
        }
    }
    if (ferror(outfile))
    {
        printf("error %s", _strerror(NULL));
