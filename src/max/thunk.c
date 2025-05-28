// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: thunk.c,v 1.2 2003/06/04 23:46:22 wesgarland Exp $";
#pragma on(unreferenced)

#include "alc.h"
#include "msgapi.h"
#include "prog.h"
#include <stdlib.h>
#include <string.h>


void OS2FAR *MAPIENTRY max_palloc(size_t size) { return ((void OS2FAR *)malloc(size)); }

void MAPIENTRY max_pfree(void OS2FAR *ptr) { free((void *)ptr); }

void OS2FAR *MAPIENTRY max_repalloc(void OS2FAR *ptr, size_t size)
{
    return ((void OS2FAR *)realloc((void *)ptr, size));
}

void far *MAPIENTRY max_farpalloc(size_t size) { return ((void far *)farmalloc(size)); }

void MAPIENTRY max_farpfree(void far *ptr) { farfree(ptr); }

void far *MAPIENTRY max_farrepalloc(void far *ptr, size_t size)
{
    return ((void far *)farrealloc(ptr, size));
}
