// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <stdio.h>
#include <time.h>

union stamp_combo *_fast Get_Dos_Date(union stamp_combo *st)
{
    time_t timeval;
    struct tm *tim;

    timeval = time(NULL);
    tim = localtime(&timeval);

    return (TmDate_to_DosDate(tim, st));
}
