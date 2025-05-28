// SPDX-License-Identifier: GPL-2.0-or-later



#include "alc.h"
#include "prog.h"
#include <dos.h>


#ifdef __FARDATA__
#if defined(OS_2)
#define INCL_DOS
#include <pos2.h>

#ifdef __FLAT__
unsigned long cdecl coreleft(void)
{
    ULONG ulMem;

    DosQuerySysInfo(QSV_TOTAVAILMEM, QSV_TOTAVAILMEM, &ulMem, sizeof ulMem);
    return ulMem;
}

    return (ul);
}

#endif

#elif defined(NT)

#include "pwin.h"

unsigned long cdecl coreleft(void)
{
    MEMORYSTATUS ms;


unsigned long cdecl coreleft(void)
{
    struct _dpmi_inf
    {
        int largest;
        int rsvd[3];
    } dinf;

    union REGS r;

    r.x.edi = (int)&dinf;
    r.w.ax = 0x0500;
    int386(0x31, &r, &r);

    return dinf.largest;
}
#else

    pageSize = 64 * 1024;
    pagesAvail = 42;
#else
    pageSize = sysconf(_SC_PAGE_SIZE);
    pagesAvail = sysconf(_SC_AVPHYS_PAGES);
#endif

    return pageSize * pagesAvail;
}
#else
#error unknown operating system
#endif

unsigned cdecl coreleft(void)
{
#ifdef __WATCOMC__

    struct _heapinfo entry;
    unsigned left;

    left = 0;
    entry._pentry = NULL;

    while (1)
    {
        if (_heapwalk(&entry) != _HEAPOK)
            break;

        if (entry._useflag == _FREEENTRY)
            left += entry._size;
    }

    return (left);
#else
    return (_memavl());
#endif
}

#ifdef TEST_HARNESS
#include <stdio.h>

int main(void)
{
    long ul = coreleft();

    printf("core=%ld\n", coreleft());
}
#endif
