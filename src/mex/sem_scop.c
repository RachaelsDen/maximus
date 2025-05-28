// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sem_scop.c,v 1.1.1.1 2002/10/01 17:54:04 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "mex.h"
#include "prog.h"
#include <stdlib.h>
#include <string.h>

void scope_open(void)
{
    scope++;

#ifdef SCOPEDEBUG
    debug("Opening scope %d (offset=%d)", scope, offset);
#endif
}

void scope_close(void)
{
    VMADDR freed;

    patch_gotos();

    freed = st_killscope(symtab, scope--);

#ifdef SCOPEDEBUG
    debug("Closing scope %d (freed %d in AR, now offset=%d)", scope + 1, freed, offset);
#endif
}


TYPEDESC *NewTypeDescriptor(void)
{
    TYPEDESC *nt;

    if ((nt = malloc(sizeof(TYPEDESC))) == NULL)
        NoMem();

    memset(nt, '\0', sizeof(TYPEDESC));
    return nt;
}

DATAOBJ *NewDataObj(void)
{
    DATAOBJ *nd;

    if ((nd = malloc(sizeof(DATAOBJ))) == NULL)
        NoMem();

    memset(nd, '\0', sizeof(DATAOBJ));

    return nd;
}
