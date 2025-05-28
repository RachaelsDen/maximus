// SPDX-License-Identifier: GPL-2.0-or-later




#include "prog.h"


static unsigned months_to_days(unsigned month) { return ((month * 3057 - 3007) / 100); }


static long ymd_to_days(unsigned yr, unsigned mo, unsigned day)
{
    long days;

    days = day + months_to_days(mo);

    if (mo > 2)
        days -= (isleap(yr)) ? 1 : 2;

    yr--;
    days += years_to_days(yr);

    return (days);
}

time_t _stdc mktime(struct tm *tm_ptr)
{
    time_t scalar_time;

    scalar_time = ymd_to_days((tm_ptr->tm_year + 1900), (tm_ptr->tm_mon + 1), tm_ptr->tm_mday);
    scalar_time -= ymd_to_days(1970, 1, 1);

    scalar_time *= (24L * 3600L);
    scalar_time += (long)(tm_ptr->tm_sec + timezone + (tm_ptr->tm_min * 60L) +
                          (tm_ptr->tm_hour * 3600L) - 3600);

    return (scalar_time);
}

