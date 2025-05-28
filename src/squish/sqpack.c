// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sqpack.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#define MSGAPI_HANDLERS

#include "sqpack.h"
#include "api_sq.h"
#include "areaapi.h"
#include "areadat.h"
#include "ffind.h"
#include "max.h"
#include "msgapi.h"
#include "prog.h"
#include "sqver.h"
#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef DMALLOC
#include "dmalloc.h"
#endif

#if defined(__FARDATA__) && !defined(__FLAT__)
#if defined(__WATCOMC__) && !defined(OS_2)
#define myfarmalloc(p) halloc(p, 1)
#define myfarfree(p) hfree(p)
#else
#define myfarmalloc(p) h_malloc(p)
#define myfarfree(p) h_free(p)
#endif
#else
#define myfarmalloc(p) malloc(p)
#define myfarfree(p) free(p)
#endif

static void near error(void)
{
    printf("\a  Err!  Run SQINFO!");
    return;
}

static void near ErrOpening(byte *name) { printf("Error opening `%s'!\n", name); }

static word near kill_msg(sword usDays, union stamp_combo *pscDate)
{
    struct tm *ptm;
    time_t t;
    long long_t;
    union stamp_combo scToday;

    t = time(NULL);

    long_t = (long)t - 60L * 60L * 24L * (long)usDays;


    t = (long_t < 0 || long_t > t) ? 0 : long_t;

    ptm = localtime(&t);

    TmDate_to_DosDate(ptm, &scToday);

    return (!GEdate(pscDate, &scToday));
}

int pack_base(struct _sqbase *isqb, int infd, int outfd, struct _sqbase *osqb, SQIDX huge *idx)
{
    SQHDR *frame;

    byte *sqbp;

    sdword b_left;

    FOFS new_frame, next_new_frame;
    FOFS lframeofs, loutfofs;

    long ofdpos;

    word mctr = 0;
    ptrdiff_t b_get;
    int got, do_bs;
    byte fKill = FALSE;
    long n_msg = 0;

    ofdpos = sizeof(struct _sqbase);


    if (new_frame == NULL_FRAME)
    {
        osqb->begin_frame = NULL_FRAME;
        printf(" - ");
        return 0;
    }

    lframeofs = loutfofs = NULL_FRAME;

    do
    {

        frame = (SQHDR *)sqbuf;


        if (lseek(infd, new_frame, SEEK_SET) != new_frame ||
            read(infd, (char *)frame, sizeof(SQHDR)) != sizeof(SQHDR) || frame->id != SQHDRID ||
            frame->prev_frame != lframeofs || new_frame >= isqb->end_frame ||
            new_frame == frame->next_frame)
        {
            error();
            break;
        }

        fKill = FALSE;


        if (isqb->max_msg &&
            (sdword)mctr < (sdword)isqb->num_msg - (sdword)isqb->max_msg + (sdword)isqb->skip_msg)
            fKill = TRUE;

        if (fKill && (sdword)mctr >= (sdword)isqb->skip_msg)
        {
            lframeofs = new_frame;
            new_frame = frame->next_frame;

            mctr++;

            if ((mctr % 10) == 0 && do_bs)
            {
                printf("\b\b\b\b\b%5u", mctr);
                fflush(stdout);
            }

#ifdef __FARDATA__
            h_memmove(idx + n_msg, idx + n_msg + 1L,
                      ((long)isqb->num_msg - (n_msg + 1L)) * (long)sizeof(SQIDX));
#else
            memmove(idx + n_msg, idx + n_msg + 1L,
                    ((word)isqb->num_msg - (n_msg + 1)) * sizeof(SQIDX));
#endif
            continue;
        }



        if ((dword)(mctr + 1) == isqb->num_msg)
            frame->next_frame = NULL_FRAME;
        else
            frame->next_frame = ofdpos + sizeof(SQHDR) + frame->msg_length;


        sqbp = sqbuf + sizeof(SQHDR);

        b_left = frame->msg_length;




            ofdpos += (long)b_get;


        if (b_left > 0)
            break;

        lframeofs = new_frame;
        new_frame = next_new_frame;


    if (n_msg == 0)
        osqb->begin_frame = osqb->last_frame = NULL_FRAME;


static int near pack_file(int sqd, int ifd, int newfd)
{
    SQIDX *idx = NULL;
    struct _sqbase isqb, osqb;
#ifdef __FARDATA__
    long bytes;
#else
    word bytes;
#endif
    int ret;


    osqb = isqb;

    osqb.len = sizeof(struct _sqbase);
    osqb.begin_frame = sizeof(struct _sqbase);
    osqb.last_frame = NULL_FRAME;
    osqb.free_frame = NULL_FRAME;
    osqb.last_free_frame = NULL_FRAME;
    osqb.end_frame = sizeof(struct _sqbase);

    lseek(newfd, 0L, SEEK_SET);

    if (write(newfd, (char *)&osqb, sizeof(osqb)) != sizeof(osqb))
    {
        printf("\a  Err!  Can't write to disk!");
        return 1;
    }


#ifdef __FARDATA__
        if (h_read(ifd, (char *)idx, bytes) != bytes)
#else
        if ((word)read(ifd, (char *)idx, bytes) != bytes)
#endif
        {
            printf("\a  Err!  Can't read index!");
            myfarfree(idx);
            return 1;
        }
    }


    lseek(ifd, 0L, SEEK_SET);

    if (bytes && ret == 0)
    {
#ifdef __FARDATA__
        if (h_write(ifd, (char *)idx, bytes) != (long)bytes)
#else
        if ((word)write(ifd, (char *)idx, bytes) != bytes)
#endif
        {
            printf("\a  Err!  Can't write to disk!");
            free(idx);
            return 1;
        }


    lseek(newfd, 0L, SEEK_SET);

    if (write(newfd, (char *)&osqb, sizeof(osqb)) != sizeof(osqb))
    {
        printf("\a  Err!  Can't write to disk!");
        return 1;
    }

    return ret;
}

static int near pack_squish_file(char *path)
{
    byte sqdname[PATHLEN];
    byte ifdname[PATHLEN];
    byte newname[PATHLEN];

    long oldsize, newsize;
    int sqd, ifd, newfd, ret;

    printf("Packing %-22s -      ", path);

    sprintf(sqdname, "%s.sqd", path);
    sprintf(ifdname, "%s.sqi", path);
    sprintf(newname, "%s.~~~", path);


    ret = pack_file(sqd, ifd, newfd);

    unlock(ifd, 0L, 1L);
    unlock(sqd, 0L, 1L);


        oldsize = fsize(sqdname);
        newsize = fsize(newname);

        if (oldsize == 0)
            oldsize = 1;

        printf("Old=%7ld; New=%7ld", oldsize, newsize);

        totold += oldsize;
        totnew += newsize;

        unlink(sqdname);
        rename(newname, sqdname);
    }

    printf("\n");

    return ret;
}


static int near process_sqd_wildcard(char *fspec)
{
    FFIND *ff;
    char *pth;
    struct _alist *alist = NULL;
    struct _alist *al, *alnext;
    char name[PATHLEN];
    int ret = 0;

    ff = FindOpen(fspec, 0);

    if (ff == NULL)
    {
        printf("Filename `%s' not found!\n", fspec);
        exit(0);
    }

    if ((pth = strrstr(fspec, "/\\:")) != NULL)
    {

        pth = fspec;
        *pth = '\0';
    }


    totold = totnew = 0L;

    do
    {
        strcpy(name, pth);
        strcat(name, ff->szName);

        al = smalloc(sizeof(struct _alist));
        al->name = sstrdup(name);

        al->next = alist;
        alist = al;
    } while (FindNext(ff) == 0);

    FindClose(ff);

    ret = 0;

    for (al = alist; al; alnext = al->next, free(al), al = alnext)
    {
        ret = pack_extension(al->name) || ret;
        free(al->name);
    }

    return ret;
}


int process_max2_areas(int fd, int all, int *piRet, char *argv[])
{
    static struct _area a;
    int ret = 0;


    if (read(fd, (char *)&a, sizeof a) != sizeof a || a.id != AREA_ID)
    {
        return FALSE;
    }

    do
    {
        if ((a.type & MSGTYPE_SQUISH) && (all || process_this_area(a.msgpath, argv)))
        {
            ret = pack_squish_file(a.msgpath) || ret;
        }
    } while (read(fd, (char *)&a, sizeof a) == sizeof a);

    *piRet = ret;
    return TRUE;
}


static int near process_area_dat(int argc, char *argv[])
{
    word all = TRUE;
    HAF haf;
    HAFF haff;
    MAH ma = {0};
    int ret = 0;
    int fd;

    if (argc > 2)
        all = FALSE;


    if (!strchr(name, '.'))
    {
        char temp[PATHLEN];

        strcpy(temp, name);
        strcat(temp, ".sqd");

        if (fexist(temp))
            strcpy(name, temp);
    }

    if (stristr(name, ".sqd"))
        ret = process_sqd_wildcard(name);
    else
        ret = process_area_dat(argc, argv);

    return ret;
}

int _stdc main(int argc, char *argv[])
{
    int ret;

    printf("\nSQPACK  Squish Database Pack Utility; Version " SQVERSION "\n"
           "Copyright 1991, " THIS_YEAR " by Lanius Corporation.  All rights reserved.\n\n");

    install_24();
    atexit(uninstall_24);

#ifdef DMALLOC
    dmalloc_on(1);
#endif

    ret = process_all_areas(argc, argv);

    printf("\nOriginal size=%ld.  Packed size=%ld.\n", totold, totnew);

    return ret;
}

void _fast NoMem(void)
{
    printf("\aRan out of memory!\n");
    exit(1);
}
