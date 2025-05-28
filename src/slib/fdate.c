// SPDX-License-Identifier: GPL-2.0-or-later


#include "ffind.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <sys/stat.h>
#include <sys/types.h>

int _fast FileDate(char *name, union stamp_combo *sc)
{
    int fd;

    fd = shopen(name, O_RDONLY | O_BINARY);

    if (fd == -1)
    {
        sc->ldate = 0L;
        return -1;
    }

    get_fdt(fd, sc);
    close(fd);
    return 0;
}

int _fast SetFileDate(char *name, union stamp_combo *sc)
{
    int fd;

    fd = shopen(name, O_RDWR | O_BINARY);

    if (fd == -1)
        return -1;

    set_fdt(fd, sc);
    close(fd);
    return 0;
}
