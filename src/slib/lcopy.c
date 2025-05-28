// SPDX-License-Identifier: GPL-2.0-or-later



#include "alc.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

            break;
        }

        wbytes = write(file2, temp, rbytes);

    } while (rbytes == copy_size && rbytes == wbytes);

    if (rbytes == wbytes)
    {
        if (get_fdt(file1, &sc) == 0)
            set_fdt(file2, &sc);
    }

    close(file2);
    close(file1);

    free(temp);
    return ((rbytes == wbytes) ? 0 : -1);
}
