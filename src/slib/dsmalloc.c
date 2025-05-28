// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#undef offsetof
#include "dmalloc.h"
#undef offsetof
#define offsetof(typename, var) (size_t)(&(((typename *)0)->var))
#include "dmpvt.h"
#include "fpseg.h"

#undef dmalloc
#undef dsmalloc

void _fast NoMem(void);

extern struct _ptab *_stdc table;
extern int _stdc nptr;
extern int _stdc atdone;
extern int _stdc shutup;
extern FILE *_stdc efile;

void *cdecl dsmalloc(size_t size)
{
    char *p;

#if defined(__MSC__) || defined(__WATCOMC__)
    if (table)
    {
        int h = _heapchk();
        if (h != _HEAPOK && h != _HEAPEMPTY)
        {
            fprintf(efile, "heap corrupted\n");
            exit(1);
        }
    }
#endif

    p = malloc(size + (table ? DBEXTRA : 0));

    if (table)
    {
        if (!shutup)
            fprintf(efile, "DSML SZ=%04lx FR=%04x:%04x MM=%04x:%04x FR=%6ld\n", (unsigned long)size,
                    FP_SEG(MAGICSTACK(size)), FP_OFF(MAGICSTACK(size)), FP_SEG(p), FP_OFF(p),
                    (long)coreleft());

        if (p == NULL || d_add_table(p, MAGICSTACK(size), size))
        {
            fprintf(efile, "dsmalloc ERROR: caller %p\n", MAGICSTACK(size));
            exit(1);
        }

