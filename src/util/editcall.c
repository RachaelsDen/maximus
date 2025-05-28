// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: editcall.c,v 1.2 2003/06/05 23:27:31 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_INCL_VER

#include "max.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

int _stdc main(int argc, char *argv[])
{
    char temp[120];
    struct _bbs_stats bbstat;
    int bfile;

    Hello("EDITCALL", "Number-of-calls fudging utility", VERSION, "1990, " THIS_YEAR);

    if (argc < 2)
    {
        printf("Error!  Format is:\n\n");

        printf("EDITCALL <task_num> <num_calls>\n\n");

        printf("Use `0' for <task_num> if no task number.\n\n");
        printf("Omit <num_calls> to display the current value\n");

        return 1;
    }

    sprintf(temp, "etc/bbstat%02x.bbs", atoi(argv[1]));

    if ((bfile = open(temp, O_RDWR | O_BINARY)) == -1)
    {
        printf("Error!  `%s' does not exist.  Run Maximus once to generate\n", temp);
        printf("preliminary %s file (while using the appropriate task number),\n", temp);
        printf("and then re-run EDITCALL.\n");
        return 1;
    }

    read(bfile, (char *)&bbstat, sizeof(struct _bbs_stats));

    printf("Current value = %lu calls.\n", bbstat.num_callers);

    if (argc == 3)
    {
        bbstat.num_callers = atol(argv[2]);
        printf("New value     = %lu calls.\n", bbstat.num_callers);

        lseek(bfile, 0L, SEEK_SET);

        write(bfile, (char *)&bbstat, sizeof(struct _bbs_stats));
    }

    close(bfile);

    printf("Done!\n");

    return 0;
}
