// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mr.c,v 1.1.1.1 2002/10/01 17:57:32 sdudley Exp $";
#pragma on(unreferenced)

#define MAX_INCL_VER

#define INCL_DOS
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef OS_2
#include <os2.h>
#endif
#include "dr.h"
#include "prog.h"
#ifdef DMALLOC
#include "dmalloc.h"
#endif
#include "areaapi.h"
#include "bfile.h"
#include "max.h"
#include "mr.h"
#include "old_msg.h"
#include "prmapi.h"

char *orig_path[MAX_DRIVES];
char orig_disk;

extrn int _stdc brk_trapped;
static long total = 0L;

#ifdef COPY
int copymsg(FILE *outfile, char *fname);
static FILE *outf = NULL;
#endif

static char *pu_msg = "%u.msg";

static void _stdc restore_dirs(void)
{

static int _stdc msgcomp(const void *i1, const void *i2)
{
    return (((REN *)i1)->old - ((REN *)i2)->old);
}

static REN *near scan_area(word *nummsg)
{
    FFIND *ff;
    REN *ren;
    RNUM *ra = NULL, *rp, *rpnext;
    word num_msg = 0;
    word i;

    if ((ff = FindOpen("*.msg", 0)) == NULL)
    {
        printf("No messages ");
        return NULL;
    }

    printf("- Scan ");
    fflush(stdout);


            rp->next = ra;
            ra = rp;

            num_msg++;
        }
    } while (FindNext(ff) == 0);

    FindClose(ff);

    if (num_msg == 0)
    {
        printf("- Nothing to process ");
        fflush(stdout);
        return NULL;
    }

    *nummsg = num_msg;

    if ((ren = malloc(num_msg * sizeof(REN))) == NULL)
        NoMem();

    memset(ren, '\0', num_msg * sizeof(REN));


    qsort(ren, *nummsg, sizeof(REN), msgcomp);


                if (omsg.date_arrived.date.da == 0 || omsg.date_arrived.date.da > 31 ||
                    omsg.date_arrived.date.yr > 50 || omsg.date_arrived.time.hh > 23 ||
                    omsg.date_arrived.time.mm > 59 || omsg.date_arrived.time.ss > 59)
                {
                    Get_Dos_Date(&ren[i].date);
                    get_fdt(fd, &ren[i].date);
                }

                ren[i].up = omsg.reply;
                ren[i].down = omsg.up;
            }

            close(fd);
        }
    }

    return ren;
}

static void near delete_msgs(PMAH pmah, REN *ren, word num_msg)
{
    word i;
    word gone = 0;

    if (pmah->ma.killbyage || pmah->ma.killbynum)
    {
        printf("- Delete ");
        fflush(stdout);
    }
    else
        return;

    if (pmah->ma.killbynum)
    {
        sword j;

        j = (sword)num_msg - (sword)pmah->ma.killbynum - !(pmah->ma.attribs & MA_ECHO);

        while (j >= 0)
        {
            if (ren[j].old == 1 && (pmah->ma.attribs & MA_ECHO))
                j--;
            else
                ren[j--].flag |= REN_DELETE;
        }
    }


        Get_Dos_Date(&today);

        dd = today.msg_st.date.da;
        mm = today.msg_st.date.mo;
        yy = today.msg_st.date.yr;

        dd -= pmah->ma.killbyage;

        while (dd < 1)
        {
            dd += 31;
            mm--;
        }

        while (mm < 1)
        {
            mm += 12;
            yy--;
        }

        if (yy < 0)
            yy = 0;

        today.msg_st.date.da = dd;
        today.msg_st.date.mo = mm;
        today.msg_st.date.yr = yy;


    for (i = 0; i < num_msg; i++)
    {
        char msgname[PATHLEN];


    strcpy(temp, path);
    strcat(temp, file);


    for (i = 0; i < max; i++)
    {
        word j;

        if (!lr[i])
            continue;


        if (j == num_msg)
            lr[i] = 0;
    }

    lseek(fd, 0L, SEEK_SET);
    write(fd, (char *)lr, size);

    free(lr);

    close(fd);
}

static void near renumber_msgs(REN *ren, word num_msg)
{
    word new_num = 1;
    word i;

    printf("- Renum ");
    fflush(stdout);

    for (i = 0; i < num_msg; i++)
    {
        char from[PATHLEN];
        char to[PATHLEN];

        if (ren[i].flag & REN_DELETE)
        {
            ren[i].new = -1;
            continue;
        }

        ren[i].new = new_num++;

        if (ren[i].old != ren[i].new)
        {
            sprintf(from, pu_msg, ren[i].old);
            sprintf(to, pu_msg, ren[i].new);

            if (rename(from, to) != 0)
                printf("\nCan't rename %s to %s", from, to);
        }
    }

    printf("- Link ");
    fflush(stdout);


        if (ren[i].up)
        {
            REN *f;

            this.old = ren[i].up;

            f = bsearch(&this, ren, num_msg, sizeof(REN), msgcomp);

            if (f == NULL)
            {
                ren[i].up = 0;
                ren[i].flag |= REN_DELTA;
            }
            else if (ren[i].up != f->new)
            {
                ren[i].flag |= REN_DELTA;

                ren[i].up = f->new;
            }
        }


    for (i = 0; i < num_msg; i++)
    {
        char msgname[PATHLEN];
        int fd;


static void near renumber_area(HPRM hp, PMAH pmah)
{
    char path[PATHLEN];
    word num_msg;
    REN *ren;

    PrmRelativeString(hp, PMAS(pmah, path), path);

    if ((pmah->ma.type & MSGTYPE_SDM) == 0 || *path == 0)
        return;

    if (Save_Dir(&orig_disk, orig_path, path) == -1)
    {
        printf("Can't access area '%s'\n", path);
        return;
    }

    printf("Area %-27s ", path);
    fflush(stdout);

    if ((ren = scan_area(&num_msg)) != NULL)
    {
        if (brk_trapped)
            return;

        delete_msgs(pmah, ren, num_msg);

        if (brk_trapped)
            return;

        renumber_msgs(ren, num_msg);

        if (brk_trapped)
            return;

        lastread(path, "lastread", ren, num_msg);
        lastread(path, "lastread.bbs", ren, num_msg);
        free(ren);
    }

    printf("- Done\n");
    fflush(stdout);
}

static int near scan_adat(char *adat, char **astart, HPRM hp)
{
    HAF haf;
    HAFF haff;
    MAH mah = {0};
    word fAll = FALSE;
    char **ap;
    char **aend;


            if (fAll)
                renumber_area(hp, &mah);
            else
            {
                for (ap = astart; ap < aend; ap++)
                    if (*ap && eqstri(*ap, MAS(mah, name)))
                    {
                        renumber_area(hp, &mah);
                        *ap = NULL;
                        break;
                    }
            }

            if (brk_trapped)
                break;
        }

        AreaFileFindClose(haff);
    }

    DisposeMah(&mah);
    AreaFileClose(haf);

        outf = fopen(argv[1] + 2, "ab");
        if (!outf)
        {
            perror(argv[1] + 2);
            return 1;
        }
        argc--;
        argv++;
    }
#endif

    for (ap = argv + 1; *ap; ap++)
    {
        if (**ap == '-')
        {
            switch ((*ap)[1])
            {
            case 'm':
                strcpy(adat, *ap + 2);
                break;
            case 'p':
