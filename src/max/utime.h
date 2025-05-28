// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __UTIME_H_DEFINED
#define __UTIME_H_DEFINED

#include <time.h>

#if defined(__TURBOC__)
struct utimbuf
{
};
#elif defined(__POSIX__)
#include <utime.h>
#else
#include <sys/utime.h>
#endif

#endif
