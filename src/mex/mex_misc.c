// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mex_misc.c,v 1.1.1.1 2002/10/01 17:53:51 sdudley Exp $";
#pragma on(unreferenced)


#include "mex.h"
#include "prog.h"
#include <string.h>


int AddrEqual(ADDRESS *a1, ADDRESS *a2)
{
    return (a1->segment == a2->segment && a1->offset == a2->offset);
}

