// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sem_decl.c,v 1.1.1.1 2002/10/01 17:53:59 sdudley Exp $";
#pragma on(unreferenced)


#include "mex.h"
#include "prog.h"
#include <string.h>


ATTRIBUTES *var_list(IDTYPE *id, ATTRIBUTES *next)
{
    ATTRIBUTES *attr, *a, *last;
    byte present;

    attr = st_enter(symtab, id, &present);

    if (present)
    {
        error(MEXERR_REDECLARATIONOF, id);
        return next;
    }

    for (a = next, last = NULL; a; last = a, a = a->next_decl)
        ;

    if (last)
    {
        last->next_decl = attr;
        attr->next_decl = NULL;
        return next;
    }
    else
    {
        attr->next_decl = next;
        return attr;
    }

}


VMADDR declare_vars(TYPEDESC *typedesc, ATTRIBUTES *attr)
{
    ATTRIBUTES *ap;


        ap->class = ClassVariable;
        ap->typedesc = typedesc;


        ap->c.addr.segment = (byte)(scope == 0 ? SEG_GLOBAL : SEG_AR);

        if (scope == 0 || iDeclaringStruct)


#ifdef DECLDEBUG
        debug("Allocating '%s' at %soffset %ld (size %ld)", ap->name, scope == 0 ? "GLOBAL " : "",
              scope == 0 ? (long)glob_offset : (long)offset, (long)typedesc->size);
#endif

        if (scope == 0)
        {

            ap->c.addr.offset = 0;


            glob_offset += typedesc->size;


            add_one_global(ap->name, typedesc->size, NULL);
        }
        else
            offset += typedesc->size;

        if (offset > maxoffset)
            maxoffset = offset;

        if (glob_offset > maxgloboffset)
            maxgloboffset = glob_offset;
    }

    return offset;
}


struct _conval *AddGlobalConst(VMADDR len, byte *buf, TYPEDESC *type)
{
    struct _conval *cv;

    if (type == &StringType)
        len += sizeof(word);

    cv = smalloc(sizeof(struct _conval));

    cv->buf = smalloc(len);


    if (type == &StringType)
    {
        *(word *)cv->buf = (word)len - sizeof(word);
        memmove(cv->buf + sizeof(word), buf, len - sizeof(word));
    }
    else
        memmove(cv->buf, buf, len);

#ifdef DECLDEBUG
    debug("Constant init at Glob:%04d (len %d)", glob_offset, len);
#endif

    cv->len = len;


    cv->offset = (vm_output ? 0 : glob_offset);
    glob_offset += len;

    cv->next = cvlist;
    cvlist = cv;

    return cv;
}

char *GlobGetString(VMADDR offset)
{
    struct _conval *cv;
    char *s;

    if (vm_output)
        bug("GlobGetString can't be used with -v, since cv->offset will always be zero");

    for (cv = cvlist; cv; cv = cv->next)
        if (cv->offset == offset)
        {
            s = smalloc(cv->len - 1);
            memmove(s, cv->buf + sizeof(word), cv->len - sizeof(word));
            s[cv->len - sizeof(word)] = '\0';
            return s;
        }

    bug("Invalid GlobGetString(%d)", offset);
    return NULL;
}


TYPEDESC *array_descriptor(RANGE *r, TYPEDESC *el_type)
{
    TYPEDESC *nt;

    if (!el_type)
        return NULL;

    if (el_type == &VoidType)
    {
        error(MEXERR_TYPEMUSTNOTBEVOID);
        return NULL;
    }

    nt = NewTypeDescriptor();
    nt->size = r->hi == (VMADDR)-1 ? -1 : (el_type->size * ((r->hi - r->lo) + 1));

#ifdef DECLDEBUG
    if (r->hi == (VMADDR)-1)
        debug("Array size is unknown");
    else
        debug("Array size is %d (%d els * %d bytes/el)", nt->size, (r->hi - r->lo) + 1,
              el_type->size);
#endif

    nt->form = FormArray;

    nt->typeinfo.array.bounds = *r;
    nt->typeinfo.array.el_type = el_type;

    return nt;
}


TYPEDESC *define_struct_id(IDTYPE *pidStruct)
{
    TYPEDESC *ptd;
    ATTRIBUTES *a;
    byte fPresent;

    a = st_enter(symtab, pidStruct, &fPresent);

    if (fPresent)
    {
        error(MEXERR_REDECLOFSTRUCT, a->name);
        return NULL;
    }


    a->class = ClassStructName;
    a->typedesc = ptd;


    ptd->typeinfo.struc.name = a->name;
    ptd->typeinfo.struc.post = symtab;
    ptd->typeinfo.struc.oscope = scope;
    ptd->typeinfo.struc.ooffset = offset;
    ptd->typeinfo.struc.omaxoffset = maxoffset;

    offset = 0;


void define_struct_body(TYPEDESC *ptd)
{
    ptd->size = offset;


    iDeclaringStruct--;

#ifdef DECLDEBUG
    debug("End declaration of structure '%s' (size=%d)", ptd->typeinfo.struc.name, ptd->size);
#endif
}


    if ((a = st_find(symtab, pidStructName, TRUE)) == NULL)
    {
        error(MEXERR_UNDEFSTRUCTNAME, pidStructName);
        return NULL;
    }

    if (a->class != ClassStructName || a->typedesc->form != FormStruct)
    {
        error(MEXERR_SYMISNOTSTRUCT, pidStructName);
        return NULL;
    }

    return a->typedesc;
}
