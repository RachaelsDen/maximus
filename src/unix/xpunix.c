// SPDX-License-Identifier: GPL-2.0-or-later

#include "share.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


static char rcs_id[] = "$Id: xpunix.c,v 1.1 2003/06/11 14:44:51 wesgarland Exp $";

#if defined(FLOCK_IS_FCNTL)

int flock(int fd, int lockmode)
{
    int cmd, result;
    struct flock fl;

    if (lockmode & LOCK_NB)
        cmd = F_SETLK;
    else
        cmd = F_SETLKW;

    memset(&fl, 0, sizeof(fl));

    switch (lockmode & ~LOCK_NB)
    {
    case LOCK_SH:
        fl.l_type = F_RDLCK;
        break;
    case LOCK_EX:
        fl.l_type = F_WRLCK;
        break;
    case LOCK_UN:
        fl.l_type = F_UNLCK;
        break;
    }

    fl.l_whence = SEEK_SET;

    result = fcntl(fd, cmd, &fl);
    return result;
}
