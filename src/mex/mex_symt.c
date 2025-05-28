// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mex_symt.c,v 1.1.1.1 2002/10/01 17:53:52 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "mex.h"
#include "prog.h"
#include <mem.h>
#include <string.h>

static VMADDR near _st_hash(SYMTAB *st, byte *name);
static void near _st_kill_attribute_rec(ATTRIBUTES *ap);


    if ((st->table = malloc(len * sizeof(ATTRIBUTES *))) == NULL)
    {
        free(st);
        return NULL;
    }


void st_destroy(SYMTAB *st)
{
    if (st)
    {
        free(st->table);
        st->table = NULL;
        free(st);
    }
}


ATTRIBUTES *st_enter(SYMTAB *st, byte *name, byte *present)
{
    ATTRIBUTES *ap, *last;
    unsigned pos;

    if (present)
        *present = FALSE;

    if (!st)
        bug("Garbled symbol table");

    pos = _st_hash(st, name);


    for (ap = st->table[pos]; ap && ap->scope == scope; ap = ap->_next)
    {

        if (ap->name && eqstr(ap->name, name))
        {
            if (present)
                *present = TRUE;

            return ap;
        }
    }


    last = st->table[pos];

    ap = st->table[pos] = smalloc(sizeof(ATTRIBUTES));


ATTRIBUTES *st_find(SYMTAB *st, byte *name, int search_parent)
{
    ATTRIBUTES *ap;
    unsigned pos;

    if (!st)
        return NULL;

    do
    {

        for (ap = st->table[pos]; ap; ap = ap->_next)
            if (ap->name && eqstr(name, ap->name))
                return ap;

    } while (search_parent && (st = st->parent) != NULL);

    return NULL;
}


VMADDR st_killscope(SYMTAB *st, VMADDR scope)
{
    ATTRIBUTES **chain, *last, *ap;
    VMADDR storage_freed = 0;

    for (chain = st->table; chain < st->table + st->len; chain++)
        for (ap = *chain, last = NULL; ap; ap = ap->_next)
        {


                    if (ap->name)
                        _st_kill_attribute_rec(ap);

                    last = ap;
                    continue;
                }
                else if (ap->class == ClassFunc)
                {

                _st_kill_attribute_rec(ap);


                if (!last)
                    *chain = ap->_next;
                else
                    last->_next = ap->_next;


static void near _st_kill_attribute_rec(ATTRIBUTES *ap)
{
    DATAOBJ *o;

    if (ap->typedesc == &StringType && ap->name && ap->class != ClassValidate && ap->ref == FALSE)
    {
        o = idref(ap->name);

