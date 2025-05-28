// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: bld.c,v 1.2 2003/06/05 03:31:41 wesgarland Exp $";
#pragma on(unreferenced)

#include "bld.h"
#include "prog.h"

#define stringize2(x) #x
#define stringize(x) stringize2(x)

char startup_txt[] = "MsgAPI 2.0." stringize(BUILD_NUM) " Startup\r\n";
