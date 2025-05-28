// SPDX-License-Identifier: GPL-2.0-or-later



#include "alc.h"
#include "prog.h"
#include <dos.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#if defined(__FLAT__)

#define MAX_DPTR 8192
#define FIRST_KEY 0x12345678L
#define LAST_KEY 0x87654321L
#define KEY_SIZES (sizeof(unsigned long) * 2)

int shutup =

        *(unsigned long *)p = FIRST_KEY;
        p += sizeof(unsigned long);

        *(unsigned long *)(p + size) = LAST_KEY;
    }

    return (void *)p;
}

void *cdecl dmalloc(size_t size) { return dmalloc_int(size, get_caller()); }

static char *dstrdup_int(char *s, unsigned long ulCaller)
{
    char *p;

    p = dmalloc_int(strlen(s) + 1, ulCaller);
    strcpy(p, s);
    return p;
}

char *cdecl dstrdup(char *s) { return dstrdup_int(s, get_caller()); }

static void *dcalloc_int(size_t numitems, size_t size, unsigned long ulCaller)
{
    char *p;
    int sz = numitems * size;

    p = dmalloc_int(sz, ulCaller);
    memset(p, 0, sz);

    return (void *)p;
}

void *cdecl dcalloc(size_t numitems, size_t size)
{
    return dcalloc_int(numitems, size, get_caller());
}

void cdecl dfree(void *b)
{
    char *block = b;

    if (ptab)
    {
        block -= sizeof(unsigned long);

        check_heap();
        remove_table(block);
    }

    free(block);
}

static void *drealloc_int(void *b, size_t size, unsigned long ulCaller)
{
    char *new;

    new = dmalloc_int(size, ulCaller);

    if (!new)
        return NULL;

    memcpy(new, b, size);
    dfree(b);
    return new;
}

void *cdecl drealloc(void *b, size_t size) { return drealloc_int(b, size, get_caller()); }

#ifdef TEST
#include "dmalloc.h"

main()
{
    char *p1, *p2, *p3;

    dmalloc_on(0);

    p1 = malloc(5);
    p2 = malloc(5);
    p3 = malloc(5);

    free(p1);
    free(p3);

    p1 = realloc(p2, 10);
    free(p1);

    p3 = malloc(5);
    p2 = malloc(100);
    p1 = malloc(5);

    free(p1);
    free(p2);

    p2 = strdup("asdfasdf");
    *p2 = 1;
    free(p2);

    return 0;
}
