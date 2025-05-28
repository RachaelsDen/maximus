// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include "progprot.h"

#define INCL_DOS
#include <os2.h>

int _fast lock(int fh, long offset, long len)
{
    FILELOCK fl;

    fl.lOffset = offset;
    fl.lRange = len;

    return (DosSetFileLocks((HFILE)fh, NULL, &fl, 0, 0) == 0 ? 0 : -1);
}

int _fast unlock(int fh, long offset, long len)
{
    FILELOCK fl;

    fl.lOffset = offset;
    fl.lRange = len;

    return (DosSetFileLocks((HFILE)fh, &fl, NULL, 0, 0) == 0 ? 0 : -1);
}
