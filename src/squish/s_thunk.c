// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_thunk.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#include "msgapi.h"
#include "prog.h"
#include <stdlib.h>
#include <string.h>


void OS2FAR *EXPENTRY sq_palloc(size_t size) { return ((void OS2FAR *)malloc(size)); }

void EXPENTRY sq_pfree(void OS2FAR *ptr) { free((void *)ptr); }

void OS2FAR *EXPENTRY sq_repalloc(void OS2FAR *ptr, size_t size)
{
    return ((void OS2FAR *)realloc((void *)ptr, size));
}

void far *EXPENTRY sq_farpalloc(size_t size) { return ((void far *)farmalloc(size)); }

void EXPENTRY sq_farpfree(void far *ptr) { farfree(ptr); }

void far *EXPENTRY sq_farrepalloc(void far *ptr, size_t size)
{
    return ((void far *)farrealloc(ptr, size));
}
