// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

static void near StandardDate(union stamp_combo *d_written);

void _fast ASCII_Date_To_Binary(char *msgdate, union stamp_combo *d_written)
{
    char temp[80];

    int dd, yy, mo, hh, mm, ss, x;

    time_t timeval;
    struct tm *tim;

    timeval = time(NULL);
    tim = localtime(&timeval);

        strftime(msgdate, 19, "%d %b %y %H:%M:%S", tim);

        StandardDate(d_written);
        return;
    }

    if (sscanf(msgdate, "%d %s %d %d:%d:%d", &dd, temp, &yy, &hh, &mm, &ss) == 6)
        x = 1;
    else if (sscanf(msgdate, "%d %s %d %d:%d", &dd, temp, &yy, &hh, &mm) == 5)
    {
        ss = 0;
        x = 1;
    }
    else if (sscanf(msgdate, "%*s %d %s %d %d:%d", &dd, temp, &yy, &hh, &mm) == 5)
        x = 2;
    else if (sscanf(msgdate, "%d/%d/%d %d:%d:%d", &mo, &dd, &yy, &hh, &mm, &ss) == 6)
        x = 3;
    else
        x = 0;

    if (x == 0)
    {
        StandardDate(d_written);
        return;
    }

            d_written->msg_st.date.mo = 1;
    }
    else

static void near StandardDate(union stamp_combo *d_written)
{
    d_written->msg_st.date.yr = 0;
    d_written->msg_st.date.mo = 1;
    d_written->msg_st.date.da = 1;

    d_written->msg_st.time.hh = 0;
    d_written->msg_st.time.mm = 0;
    d_written->msg_st.time.ss = 0;
}
