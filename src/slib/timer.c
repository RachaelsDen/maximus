// SPDX-License-Identifier: GPL-2.0-or-later



#ifdef OS_2
#define INCL_NOPM
#include <os2.h>
#endif

#include "prog.h"
#include <dos.h>
#include <time.h>

#if defined(OS_2)

long _stdc timerset(unsigned int duration)
{
    DATETIME dt;
    DosGetDateTime(&dt);
    return (((dt.minutes % 60) * 6000L) + ((dt.seconds % 60) * 100L) + dt.hundredths +
            (long)duration);
}

#elif defined(NT)

#include "pwin.h"

long _stdc timerset(unsigned int duration)
{
    SYSTEMTIME st;

    GetLocalTime(&st);

    return ((st.wMinute % 60) * 6000L + (st.wSecond % 60) * 100L + st.wMilliseconds / 10L +
            (long)duration);
}

#elif defined(__MSDOS__)

long _stdc timerset(unsigned int duration)
{
#ifdef __MSC__
    struct dostime_t dt;
    _dos_gettime(&dt);
    return (((dt.minute % 60) * 6000L) + ((dt.second % 60) * 100L) + dt.hsecond + (long)duration);
