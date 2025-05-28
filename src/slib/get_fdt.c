// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <dos.h>
#include <io.h>


#define INCL_NOPM
#define INCL_DOS
#include <os2.h>

struct FileInfoBuf
{

#include <sys/stat.h>

int get_fdt(int fd, union stamp_combo *psc)
{
    struct stat sb;
    struct tm timebuf;

    if (fstat(fd, &sb))
        return 1;

    if (TmDate_to_DosDate(localtime_r(&sb.st_mtime, &timebuf), psc))
        return 1;

    return 0;
}
#else
#error Unknown OS
#endif
