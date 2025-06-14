/*
 * Maximus Version 3.02
 * Copyright 1989, 2002 by Lanius Corporation.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

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
