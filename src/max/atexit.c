// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: atexit.c,v 1.1.1.1 2002/10/01 17:50:45 sdudley Exp $";
#pragma on(unreferenced)

#include "alc.h"
#include "mm.h"
#include "prog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _atexitstruct
{
    void (*exitFunc)(void);
    struct _atexitstruct *next;
} AtExitStruct;

AtExitStruct *paeExitList = 0;

int maximus_atexit(register void (*func)(void))
{
    AtExitStruct *pae;

    if ((pae = malloc(sizeof(*pae))) == NULL)
        exit(2);

    pae->exitFunc = func;
    pae->next = paeExitList;
    paeExitList = pae;
    return 0;
}

void maximus_exit(int status)
{
    AtExitStruct *pae, *paeNext;

    for (pae = paeExitList; pae; pae = paeNext)
    {
        (*pae->exitFunc)();
        paeNext = pae->next;
        free(pae);
    }

    exit(status);
}
