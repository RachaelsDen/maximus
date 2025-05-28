// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sqfix.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#define NOVARS
#define NOVER
#define MSGAPI_HANDLERS

#include "sqfix.h"
#include "api_sq.h"
#include "msgapi.h"
#include "prog.h"
#include "sqver.h"
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define VERSION SQVERSION
#define BSIZ 32767u

static int free_frames = 0;
static int damaged_frames = 0;
static int ok_frames = 0;

static char *begin, *here;

static char *fixname = "$SQFIXED";
static char *sqd_name = "%s.sqd";
static char *sqi_name = "%s.sqi";

static int near snuggle_up(char *bufr, ptrdiff_t need_len, int *got, int old_sqd)
{
    word len, shift;


    sprintf(name, sqi_name, origname);

    if ((sqi = sopen(name, O_CREAT | O_TRUNC | O_RDWR | O_BINARY, SH_DENYRW, S_IREAD | S_IWRITE)) ==
        -1)
        ErrOpen(name);

    sprintf(name, sqd_name, origname);

    if ((sqd = sopen(name, O_RDWR | O_BINARY, SH_DENYRW, S_IREAD | S_IWRITE)) == -1)
        ErrOpen(name);

    if (read(sqd, (char *)&sqb, sizeof(sqb)) != sizeof(sqb))
        ErrRead(name);

    if (sqb.num_msg == 0)
    {
        close(sqd);
        return;
    }

#if defined(__MSDOS__) || defined(OS_2)
    if (sqb.num_msg * (long)sizeof(RLNK) > 65000L)
        NoMem();
#endif


    for (pos = sqb.begin_frame, mn = 0;
         mn < (long)sqb.num_msg && lseek(sqd, pos, SEEK_SET) == pos &&
         read(sqd, (char *)&hdr, sizeof(hdr)) == sizeof(hdr);
         pos = hdr.next_frame, mn++)
    {
        if (read(sqd, (char *)&msg, sizeof(XMSG)) != sizeof(XMSG))
            ErrRead(name);

        rl[(size_t)mn].date.msg_st =
            ((union stamp_combo *)&msg.date_arrived)->ldate ? msg.date_arrived : msg.date_written;
        rl[(size_t)mn].pos = pos;

        if ((mn % 5) == 0)
            printf("%ld\r", mn);
    }

    max = mn;

    printf("          \rSorting...\n");


        hdr.prev_frame = (rp == rl ? NULL_FRAME : rp[-1].pos);
        hdr.next_frame = (rp == re - 1 ? NULL_FRAME : rp[1].pos);


        if (read(sqd, (char *)&msg, sizeof(msg)) != sizeof(msg))
            ErrRead(name);


        if (write(sqi, (char *)&ix, sizeof(ix)) != sizeof(ix))
            ErrWrite(name);

        if ((++mn % 5) == 0)
            printf("%ld\r", mn);
    }

    lseek(sqd, 0L, SEEK_SET);

    if (write(sqd, (char *)&sqb, sizeof(sqb)) != sizeof(sqb))
        ErrWrite(name);

    printf("\r         \r");

    free(rl);

    close(sqi);
    close(sqd);
}

static void near rename_base(char *origname, char *toname)
{
    char from[PATHLEN];
    char to[PATHLEN];

    sprintf(from, sqd_name, origname);
    sprintf(to, "%s.xxd", origname);

    if (rename(from, to) != 0)
    {
        unlink(to);
        rename(from, to);
        unlink(from);
    }

    sprintf(from, sqi_name, origname);
    sprintf(to, "%s.xxi", origname);

    if (rename(from, to) != 0)
    {
        unlink(to);
        rename(from, to);
        unlink(from);
    }


        begin = bufr;

        while ((here = memstr(begin, search, got - (word)(begin - bufr), lens)) != NULL)
        {

            memmove(&hdr, here, sizeof(SQHDR));


                begin = here + 1;
                continue;
            }

            here += sizeof(SQHDR);


            memmove(&msg, here, sizeof(XMSG));


            if (hdr.clen)
                hdr.clen = min(hdr.clen, (unsigned long)strlen(here) + 1L);

            txt = here + (word)hdr.clen;


            if ((msgh = MsgOpenMsg(new, MOPEN_CREATE, 0L)) == NULL)
            {
                printf("Error opening message for write!  Aborting...\n");
                exit(1);
            }

            msg.replyto = 0L;
            memset(msg.replies, '\0', sizeof(UMSGID) * MAX_REPLY);


            msg.attr |= MSGSCANNED;

            if (MsgWriteMsg(msgh, FALSE, &msg, txt, hdr.msg_length, hdr.msg_length, hdr.clen,
                            here) == -1)
            {
                printf("Error writing message!  (Out of disk space?)\n");
                exit(1);
            }

            MsgCloseMsg(msgh);

            if ((++msgn % 5) == 0)
            {
                printf("%ld\r", msgn);
                fflush(stdout);
            }

            ok_frames++;

            begin = here + (size_t)hdr.msg_length;

            if ((word)(begin - bufr) > got)
                break;
        }

}


    sprintf(from, "%s.sql", base_name);
    sprintf(to, "%s.xxl", base_name);
    unlink(to);
    rename(from, to);

    if (!pmsg)
        return;

    strcpy(sql_name, base_name);
    strcat(sql_name, ".sql");

    printf("Rewriting lastread pointers...\n");

    if ((fd = sopen(sql_name, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_DENYRW,
                    S_IREAD | S_IWRITE)) == -1)
    {
        printf("Error opening %s for write!\n", sql_name);
        return;
    }

    if (h_write(fd, (char huge *)pmsg, size) != size)
    {
        printf("Error writing to %s!\n", sql_name);
        return;
    }

    close(fd);
}


static void near bitch_memory(char *where)
{
    printf("Error!  Not enough memory to read in %s file.  Lastread\n"
           "pointers will not be corrected.  (Try using SQFIX32 if you have\n"
           "a very large %s file.)\n",
           where, where);
}


    if ((p = strrchr(sqd_name, '.')) != NULL)
        *p = 0;

    strcpy(sqi_name, sqd_name);
    strcat(sqi_name, ".sqi");

    printf("Reading lastread pointers...\n");


    if ((pi = h_malloc(size)) == NULL)
    {
        bitch_memory("index");
        close(fd);
        return NULL;
    }

    if (h_read(fd, (char huge *)pi, size) != size)
    {
        h_free(pi);
        close(fd);
        return NULL;
    }

    close(fd);

    strcpy(sql_name, sqd_name);
    strcat(sql_name, ".sql");

    if ((fp = fopen(sql_name, "rb")) == NULL)
    {
        h_free(pi);
        return NULL;
    }

    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

#if !defined(__FLAT__) && !defined(OS_2)
    if (bitch_size("Lastread", size))
    {
        close(fd);
        return NULL;
    }
#endif


    while (fread((void *)&uid, sizeof(UMSGID), 1, fp) == 1)
    {
        dword lr = find_idx_uid(pi, num_sqi, uid);

    return plr;
}

static void near fix_base(char *name)
{
    dword num_lastread;
    dword huge *pLastRead;
    static char old_name[PATHLEN];
    char fixbase[PATHLEN];
    char *bufr, *p, *s;

    MSG *new;

    int old_sqd;

