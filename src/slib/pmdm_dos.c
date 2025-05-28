// SPDX-License-Identifier: GPL-2.0-or-later



#include "alc.h"
#include "dmpvt.h"
#include "prog.h"
#include <dos.h>
#include <stdlib.h>
#include <string.h>

#define INCL_DOS
#define INCL_NOPM
#include <os2.h>

#define malloc(p) realmalloc(p)
#define realloc(p, s) realrealloc(p, s)
#define free(p) realfree(p)

static void *realmalloc(int size)
{
    SEL sel;

    if (DosAllocSeg(size + 1, &sel, SEG_NONSHARED) == 0)
        return (MAKEP(sel, 0));
    else
        return NULL;
}

static void *realrealloc(void *p, int size)
{
    if (DosReallocSeg(size + 1, SELECTOROF(p)) == 0)
        return p;
    else
        return NULL;
}

static void realfree(void *p) { DosFreeSeg(SELECTOROF(p)); }

struct _ptab *_stdc table;
int _stdc nptr;
int _stdc atdone = FALSE;
int _stdc shutup = FALSE;

#ifdef __IBMC__
FILE *_stdc efile;
#else
FILE *_stdc efile = stderr;
#endif

#ifdef OS_2
#include <pos2.h>

#define coreleft() 0
#define tdelay(x) ;

#ifndef __FLAT__
static ULONG rsem = 0;
#endif
#endif

void dmsync(void)
{
#if defined(OS_2) && !defined(__FLAT__)
    DosSemRequest((HSEM)&rsem, SEM_INDEFINITE_WAIT);
#endif
}

void dmunsync(void)
{
#if defined(OS_2) && !defined(__FLAT__)
    DosSemClear((HSEM)&rsem);
#endif
}

void _stdc dptab(int show_nondelta)
{
    int x;

    if (!table || !efile)
        return;

    fprintf(efile, "--- pointers: %d (freemem=%ld)\n\n", nptr, (long)coreleft());

    for (x = 0; x < nptr; x++)
    {
        if (table[x].delta == TRUE || show_nondelta)
            fprintf(efile, "FR=" PTR_TEXT " AT=" PTR_TEXT " SZ=" PTR_SIZE "%s",
                    POINTER(table[x].aat), POINTER(table[x].p), (unsigned long)table[x].size,
                    (x & 1) == 1 ? "\n" : "\t");

        table[x].delta = FALSE;
    }
}

static void _stdc _dptabend(void) { dptab(TRUE); }

void _stdc dmalloc_on(int type)
{
#ifdef __IBMC__
    efile = stderr;
#endif

    if ((table = malloc(sizeof(struct _ptab) * MAX_PTR)) == NULL)
    {
        fprintf(efile, "not enough memory for dmalloc()\n");
        dptab(TRUE);
        flush_handle(efile);
        exit(1);
    }

    memset(table, '\0', sizeof(struct _ptab) * MAX_PTR);
    nptr = 0;

    if (!atdone)
    {
        atexit(_dptabend);
        atdone = TRUE;
    }

    if (type)
        shutup = TRUE;
}

int _stdc d_add_table(void *p, void MODTYPE *magic, int size)
{
    int x;

    for (x = 0; x < nptr; x++)
        if (p == table[x].p)
            return 1;

    if (nptr == MAX_PTR)
    {
        fprintf(efile, "ERROR!  Too many pointers allocated.\n");
        return 1;
    }

    memmove(table + 1, table, (nptr++) * sizeof(struct _ptab));
    table->p = p;
    table->aat = magic;
    table->delta = TRUE;
    table->size = size;
    return 0;
}

int _stdc d_remove_table(void *ptr)
{
    int x;
    char *p = ptr;

    for (x = 0; x < nptr; x++)
        if (p == table[x].p)
        {
            if ((*(int *)&p[0] != KEY1) || (*(int *)&p[sizeof(int)] != KEY2) ||
                (*(int *)&p[table[x].size + sizeof(int) * 2] != KEY1) ||
                (*(int *)&p[table[x].size + sizeof(int) * 3] != KEY2))
            {
                fprintf(efile, "d_remove_table - memory grunged!\n");
                return 1;
            }

            memmove(table + x, table + x + 1, ((nptr--) - x - 1) * sizeof(struct _ptab));
            return 0;
        }

    fprintf(efile, "d_remove_table - not found in table!\n");
    return 1;
}

void *cdecl dmalloc(size_t size)
{
    char *p;

    dmsync();

#if defined(__MSC__) || defined(__WATCOMC__)
    if (table)
    {
        int h = _heapchk();
        if (h != _HEAPOK && h != _HEAPEMPTY)
        {
            fprintf(efile, "heap corrupted\n");
            dptab(TRUE);
            table = NULL;
            flush_handle(efile);
            dmunsync();

            *(char far *)0 = 0;
            exit(1);
        }
    }
#endif

    p = malloc(size + (table ? DBEXTRA : 0));

    if (table)
    {
        if (!shutup)
            fprintf(efile, "DMAL SZ=" PTR_SIZE " FR=" PTR_TEXT " MM=" PTR_TEXT " SP=" SPC_TEXT "\n",
                    (unsigned long)size, POINTER(MAGICSTACK(size)), POINTER(p), (long)coreleft());

        if (p == NULL)
        {
            fprintf(efile, "dmalloc returned NULL: caller PTR_TEXT\n", POINTER(MAGICSTACK(size)));

            dptab(TRUE);
            table = NULL;
            flush_handle(efile);
            dmunsync();
            exit(1);
        }

        if (d_add_table(p, MAGICSTACK(size), size))
        {
            fprintf(efile, "dmalloc returned duplicate pointer: caller " PTR_TEXT "\n",
                    POINTER(MAGICSTACK(size)));
            dptab(TRUE);
            table = NULL;
            flush_handle(efile);
            dmunsync();
            exit(1);
        }


        *(int *)&p[0] = KEY1;
        *(int *)&p[sizeof(int)] = KEY2;
        p += sizeof(int) * 2;

        *(int *)&p[size] = KEY1;
        *(int *)&p[size + sizeof(int)] = KEY2;
    }

    strcpy(p, s);

    dmunsync();
    return p;
}

void *cdecl dcalloc(size_t numitems, size_t size)
{
    char *p;
    int sz = numitems * size;

    dmsync();

#if defined(__MSC__) || defined(__WATCOMC__)
    if (table)
    {
        int h = _heapchk();
        if (h != _HEAPOK && h != _HEAPEMPTY)
        {
            fprintf(efile, "heap corrupted\n");
            dptab(TRUE);
            table = NULL;
            flush_handle(efile);
            dmunsync();
            exit(1);
        }
    }
#endif

    p = malloc(sz + (table ? DBEXTRA : 0));

    if (p)
        memset(p, '\0', sz + (table ? DBEXTRA : 0));

    if (table)
    {
        if (!shutup)
            fprintf(efile, "DCAL SZ=" PTR_SIZE " FR=" PTR_TEXT " MM=" PTR_TEXT " SP=" SPC_TEXT "\n",
                    (unsigned long)sz, POINTER(MAGICSTACK(numitems)), POINTER(p), (long)coreleft());

        if (p == NULL || d_add_table(p, MAGICSTACK(numitems), sz))
        {
            fprintf(efile, "dcalloc ERROR: caller " PTR_TEXT "\n", POINTER(MAGICSTACK(size)));
            dptab(TRUE);
            table = NULL;
            flush_handle(efile);
            dmunsync();
            exit(1);
        }

