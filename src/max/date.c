// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: date.c,v 1.1.1.1 2002/10/01 17:50:46 sdudley Exp $";
#pragma on(unreferenced)

char comp_date[] = __DATE__;
char comp_time[] = __TIME__;

#define MAX_INCL_VER
#define MAX_DEFINE_VERSION
#include "max_vr.h"
