// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sem_goto.c,v 1.1.1.1 2002/10/01 17:54:04 sdudley Exp $";
#pragma on(unreferenced)


#include "mex.h"
#include "prog.h"
#include <stdlib.h>

void ProcessGoto(IDTYPE *id)
{
    GOTO *g;


    g->next = gstack;
    gstack = g;


    Generate(QOP_JMP, NULL, NULL, NULL);
}


        if (g->scope >= scope && ((attr = st_find(symtab, g->name, FALSE)) != NULL))
        {
            if (attr->class != ClassLabel)
                error(MEXERR_NOTAGOTOLABEL);
            else
            {

            if (last)
                last->next = g->next;
            else
                gstack = g->next;

            last = g;
            next = g->next;
        }
    }


    if (scope == 1)
    {
        for (g = gstack; g; g = next)
        {
            error(MEXERR_UNDEFLABEL, g->name);

            next = g->next;

            free(g->name);
            free(g);
        }

        gstack = NULL;
    }
}
