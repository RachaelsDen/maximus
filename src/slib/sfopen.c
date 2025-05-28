// SPDX-License-Identifier: GPL-2.0-or-later



#include "compiler.h"
#include "prog.h"
#include <errno.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

FILE *_fast sfopen(char *name, char *fpmode, int fdmode, int access)
{
    FILE *fp;
    int fd;

    fd = sopen(name, fdmode, access, S_IREAD | S_IWRITE);

    if (fd == -1 && errno == ENOENT && (fdmode & (O_APPEND | O_WRONLY)))
        fd = sopen(name, fdmode | (O_WRONLY | O_CREAT | O_TRUNC), access, S_IREAD | S_IWRITE);

    if (fd == -1)
        return NULL;

    if ((fp = fdopen(fd, fpmode)) == NULL)
        close(fd);

    return fp;
}
