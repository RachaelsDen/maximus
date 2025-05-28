// SPDX-License-Identifier: GPL-2.0-or-later

#pragma off(unreferenced)
static char rcs_id[] = "$Id: dllc.c,v 1.1.1.1 2002/10/01 17:49:28 sdudley Exp $";
#pragma on(unreferenced)

#include "prog.h"
#include <stdio.h>

int __dll_initialize(void)
{
    grow_handles(40);
    return 1;
}
