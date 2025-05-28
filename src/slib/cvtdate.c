// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <time.h>

static int is_dst = -1;


struct tm *_fast DosDate_to_TmDate(union stamp_combo *dosdateUA, struct tm *tmdate)
{
    union stamp_combo *dosdate = alignStatic(dosdateUA);

    if (is_dst == -1)
        InitCvt();

    tmdate->tm_mday = dosdate->msg_st.date.da;
    tmdate->tm_mon = dosdate->msg_st.date.mo - 1;
    tmdate->tm_year = dosdate->msg_st.date.yr + 80;

    tmdate->tm_hour = dosdate->msg_st.time.hh;
    tmdate->tm_min = dosdate->msg_st.time.mm;
    tmdate->tm_sec = dosdate->msg_st.time.ss << 1;

    tmdate->tm_isdst = is_dst;

    return tmdate;
}

