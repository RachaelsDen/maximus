// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <dos.h>
#include <io.h>

#if defined(OS_2)

#define INCL_NOPM
#define INCL_DOS
#include "pos2.h"

void pascal far flush_handle2(int fh)
{
#ifdef __FLAT__
    DosResetBuffer((HFILE)fh);
#else
    DosBufReset((HFILE)fh);
#endif
}

#elif defined(NT)
#include "pwin.h"

void pascal far flush_handle2(int fh) { FlushFileBuffers((HANDLE)fh); }

#elif defined(UNIX)
void flush_handle2(int fh) { fsync(fh); }

void _fast flush_handle(FILE *fp)
{

    fflush(fp);

#if defined(OS_2) || defined(NT) || defined(MSDOS) || defined(__MSDOS__) || defined(__TURBOC__)
    flush_handle2(fileno(fp));
#else
    {
        int nfd;

        if ((nfd = dup(fileno(fp))) != -1)
            close(nfd);
    }
#endif
}
