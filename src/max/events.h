// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __EVENTS_H_DEFINED
#define __EVENTS_H_DEFINED

#define EFLAG_DONE 0x01
#define EFLAG_YELL 0x02
#define EFLAG_ERLVL 0x04

#define DAY_SUN 0x01
#define DAY_MON 0x02
#define DAY_TUE 0x04
#define DAY_WED 0x08
#define DAY_THU 0x10
#define DAY_FRI 0x20
#define DAY_SAT 0x40

struct _etime
{
    word hour;
    word min;
};





struct _diskevent
{


