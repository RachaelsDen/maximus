// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"

int _fast GEdate(union stamp_combo *s1, union stamp_combo *s2)
{
    union _stampu st1, st2;

    st1 = s1->msg_st;
    st2 = s2->msg_st;


    if (st1.date.yr >= st2.date.yr)
    {
        if (st1.date.yr > st2.date.yr)
            return TRUE;
        else if (st1.date.mo >= st2.date.mo)
        {
            if (st1.date.mo > st2.date.mo)
                return TRUE;
            else if (st1.date.da >= st2.date.da)
            {
                if (st1.date.da > st2.date.da)
                    return TRUE;
                else if (st1.time.hh >= st2.time.hh)
                {
                    if (st1.time.hh > st2.time.hh)
                        return TRUE;
                    else if (st1.time.mm >= st2.time.mm)
                    {
                        if (st1.time.mm > st2.time.mm)
                            return TRUE;
                        else if (st1.time.ss >= st2.time.ss)
                            return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

int _fast EQdate(union stamp_combo *s1, union stamp_combo *s2)
{
    union _stampu st1, st2;

    st1 = s1->msg_st;
    st2 = s2->msg_st;

