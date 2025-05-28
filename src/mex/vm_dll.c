// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: vm_dll.c,v 1.1.1.1 2002/10/01 17:54:12 sdudley Exp $";
#pragma on(unreferenced)

#include "prog.h"
#include "vm.h"
#include <stdlib.h>

#if defined(__WATCOMC__) && defined(OS_2)

int __dll_initialize(void)
{
    grow_handles(40);
    return 1;
}

#endif
