// SPDX-License-Identifier: GPL-2.0-or-later

#include "process.h"
#include "io.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void noop(int sig) { ; }

int spawnvp(int mode, const char *Cfile, char *const argv[])
{
    pid_t pid;
    struct stat sb;
    char *file;

    signal(SIGCHLD, noop);

    file = fixPathDup(Cfile);



            if (WIFSIGNALED(status))
                fprintf(stderr, __FUNCTION__ ": Child (%s) exited due to signal %i!\n", Cfile,
                        WSTOPSIG(status));

            return -1;
        }
    }

    if (mode == P_NOWAITO)
    {
