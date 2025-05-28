// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sem_func.c,v 1.2 2003/06/05 01:10:36 wesgarland Exp $";
#pragma on(unreferenced)


#include "mex.h"
#include "prog.h"
#include <stdlib.h>
#include <string.h>

static PATCH *fr_patch;

static char *MungeTypeName(TYPEDESC *t);


ATTRIBUTES *function_begin(TYPEDESC *t, IDTYPE *id)
{
    ATTRIBUTES *f;
    byte present;


void function_args(ATTRIBUTES *func, FUNCARGS *a)
{
    ATTRIBUTES *attr, *lastarg, *firstarg, *protoarg;
    char temp[PATHLEN];
    char temp2[PATHLEN];
    byte present;
    sword ar_ofs = (sword)AR_CONTROL_DATA;
    word size = 0;
    int have_prototype;

    have_prototype = !!func->c.f.param;

    for (firstarg = lastarg = NULL, protoarg = func->c.f.param; a; a = a->next)
    {
        if (a->type == &VoidType && !a->ref)
        {
            error(MEXERR_TYPEMUSTNOTBEVOID);
            continue;
        }

        attr = st_enter(symtab, a->name, &present);

        if (present)
        {
            error(MEXERR_REDECLOFARG, a->name);
            continue;
        }

        if (!firstarg)
            firstarg = attr;

        if (lastarg)
            lastarg->next_decl = attr;

        lastarg = attr;

        attr->class = ClassValidate;
        attr->typedesc = a->type;

        attr->c.addr.segment = SEG_AR;
        attr->c.addr.indirect = FALSE;
        attr->c.addr.typedesc = a->type;

        attr->ref = a->ref;


        if (have_prototype)
        {
            if (protoarg)
            {
                if (!StructEquiv(attr->typedesc, protoarg->typedesc) || attr->ref != protoarg->ref)
                {
                    error(MEXERR_ARGMISMATCH, attr->ref ? "ref " : "",
                          TypeName(attr->typedesc, temp), protoarg->ref ? "ref " : "",
                          TypeName(protoarg->typedesc, temp2));
                }

                protoarg = protoarg->next_decl;
            }
            else
            {
                error(MEXERR_TOOMANYARGSINDECL);
            }
        }


        attr->c.addr.offset = ar_ofs;

        if (attr->typedesc)
        {
            if (attr->ref || PassByRef(attr->typedesc))
            {
                attr->c.addr.indirect = TRUE;
                ar_ofs += sizeof(IADDR);
                size += sizeof(IADDR);
            }
            else
            {
                ar_ofs += a->type->size;
                size += a->type->size;
            }
        }

#ifdef FUNCDEBUG
        debug("Argument %s (%s) at AR ofs=%d", a->name, TypeName(a->type, temp), ar_ofs);
#endif
    }

    if (have_prototype && protoarg)
        error(MEXERR_TOOFEWARGSINDECL);

    func->c.f.param = firstarg;
    func->c.f.arg_size = size;
}

void function_end(ATTRIBUTES *f, int body, VMADDR end_quad)
{
    PATCH *p, *next;

    if (!body)
    {
        FuncValidateArgs(f);
        debug("Prototype for %s", f->name);
    }
    else
    {
        if (f->c.f.declared)
            error(MEXERR_REDECLOFFUNCBODY, f->name);

        f->c.f.declared = TRUE;
        f->c.f.ar_size = maxoffset;

#ifdef FUNCDEBUG
        debug("Function %s needs AR of %d bytes", f->name, maxoffset);
#endif


        for (p = fr_patch; p; next = p->next, free(p), p = next)
            ;

        fr_patch = NULL;

        Generate(QOP_FUNCRET, (DATAOBJ *)f, NULL, NULL);
    }
}


    if (!obj)
    {
        if (f->c.f.ret_type != &VoidType)
            error(MEXERR_FUNCMUSTRETURNVALUE);
    }
    else
    {

        if (!StructEquiv(o->type, f->c.f.ret_type))
        {
            obj = NewDataObj();

            if (f->c.f.ret_type == &VoidType)
                error(MEXERR_CANTRETURNVOID);
            else
            {
                if (ConvertTypes(o, o->type, obj, f->c.f.ret_type))
                    MaybeFreeTemporary(o, TRUE);
            }
        }

        fret = NewDataObj();

        fret->type = f->c.f.ret_type;
        fret->objform = ObjformAddress;

        fret->form.addr.segment = SEG_TEMP;
        fret->form.addr.offset = fret->type->size * 1000;
        fret->form.addr.indirect = FALSE;

        Generate(fret->type == &StringType ? QOP_SCOPY : QOP_ASSIGN, obj, fret, NULL);
        MaybeFreeTemporary(obj, TRUE);
    }


    Generate(QOP_JMP, NULL, NULL, NULL);


FUNCCALL StartFuncCall(IDTYPE *id)
{
    FUNCCALL f;

    memset(&f, '\0', sizeof(FUNCCALL));

    if ((f.func = st_find(symtab, id, FALSE)) == NULL)
    {
        error(MEXERR_CALLTOFUNCWITHNOPROTO, id);
        return f;
    }

    if (f.func->class != ClassFunc)
    {
        error(MEXERR_VARIABLENOTFUNCTION, id);
        return f;
    }

    f.arg = f.func->c.f.param;

    Generate(QOP_STARTCALL, (DATAOBJ *)id, NULL, NULL);
    return f;
}


static ATTRIBUTES *near GenVarArgName(FUNCCALL *f, DATAOBJ *this, char *name)
{
    ATTRIBUTES attr, *found;

    if (!this->type)
    {
        strcpy(name, f->func->name);
        return NULL;
    }


    if ((found = st_find(symtab, name, FALSE)) == NULL)
    {
#ifdef WES_HACK
        if (name[0] == '_' && name[1] == '_' && (found = st_find(symtab, name + 2, FALSE)))
        {
            name += 2;
            attr.name += 2;
        }
        else
#endif
        {
            error(MEXERR_CALLTOFUNCWITHNOPROTO, name);
            return NULL;
        }
    }

    return found;
}


DATAOBJ *EndFuncCall(FUNCCALL *f, DATAOBJ *args)
{
    ATTRIBUTES *paVarArg = NULL;
    DATAOBJ *this, *last, *ret, *res, *obj, *oldobj;
    int varargs, argno;

    if (f->func == NULL || f->func->name == NULL)
        return NULL;


    if (!varargs)
    {
        for (argno = 1, this = args; f->arg && this;
             this = this->next_arg, f->arg = f->arg->next_decl, argno++)
        {
            this->argtype = f->arg->typedesc;
            this->ref = f->arg->ref;


            if (this->ref && this->type)
            {

                if (this->objform == ObjformValue ||
                    (this->objform == ObjformAddress && this->form.addr.segment == SEG_TEMP &&
                     !this->form.addr.indirect))
                {
                    error(MEXERR_LVALUEREQDARG, argno, f->func->name);
                }
            }
        }

        if (f->arg)
        {
            error(MEXERR_TOOFEWARGSINCALL, f->func->name);
            return NULL;
        }

        if (this)
        {
            error(MEXERR_TOOMANYARGSINCALL, f->func->name);
            return NULL;
        }
    }

    GenPushQuads();


    for (this = args, last = NULL; this;)
    {
        if (varargs ? (this != NULL) : (this->next_arg == last))
        {
            last = this;


            obj = this;


            if (varargs)
            {
                char temp[120];

                paVarArg = GenVarArgName(f, this, temp);

                if (paVarArg && paVarArg->c.f.param->ref)
                    this->ref = TRUE;
            }


            if (!varargs && (!StructEquiv(this->type, this->argtype) && this->argtype != &VoidType))
            {
                DATAOBJ *oldthis;


                    oldthis = this;
                    obj = oldobj = NewDataObj();
                    obj->type = this->argtype;

                    CoerceTypes(&this, T_ASSIGN, &obj);


            if (obj->type)
            {
                if (this->ref || PassByRef(obj->type))
                {

                    DATAOBJ *dataObjPtr =
                        (varargs && this->ref && this->type == &StringType) ? (DATAOBJ *)1 : NULL;
                    Generate(QOP_ARG_REF, obj, dataObjPtr, NULL);
#if 0
          Generate(QOP_ARG_REF, obj,
                   (DATAOBJ *)(varargs && this->ref && this->type==&StringType),
                   NULL);
#endif
                }
                else
                {
                    ADDRESS tstr;
                    DATAOBJ *tdo = NULL;
                    word is_str = FALSE;



                        obj = tdo;

                        is_str = TRUE;
                    }


                    if (is_str)
                        MaybeFreeTemporary(tdo, FALSE);
                }
            }

            if (varargs)
            {
                Generate(QOP_FUNCJUMP, (DATAOBJ *)paVarArg, NULL, NULL);
                GenPopQuads();

                if (this->next_arg)
                {
                    Generate(QOP_STARTCALL, (DATAOBJ *)f->func->name, NULL, NULL);
                    GenPushQuads();
                }
            }

        if (this == last)
            break;

        this = this->next_arg;
    }


    if (!varargs)
        Generate(QOP_FUNCJUMP, (DATAOBJ *)f->func, NULL, NULL);

    GenPopQuads();


    ret = NewDataObj();
    ret->type = f->func->c.f.ret_type;

    if (f->func->c.f.ret_type == &VoidType)
    {
        ret->objform = ObjformAddress;
        ret->form.addr.typedesc = &VoidType;
        return ret;
    }
    else
    {

        ret->objform = ObjformAddress;
        ret->form.addr.segment = SEG_TEMP;
        ret->form.addr.offset = f->func->c.f.ret_type->size * 1000;
        ret->form.addr.indirect = FALSE;
        ret->form.addr.typedesc = f->func->c.f.ret_type;


        res = NewDataObj();
        res->type = ret->type;
        res->objform = ObjformAddress;
        res->form.addr = GetTemporary(res->type);

        Generate(QOP_ASSIGN, ret, res, NULL);


        return res;
    }
}


void GenFuncStartQuad(ATTRIBUTES *f)
{
    FuncValidateArgs(f);
    Generate(QOP_FUNCSTART, (DATAOBJ *)f, NULL, NULL);
}

struct _poplist
{
    ADDRESS a;
    struct _poplist *next;
};

static struct _poplist *poplist = NULL;


void GenPushQuads(void)
{
    extern TLLIST *temp;
    struct _poplist *pl;
    TLLIST *t;
    TLIST *tl;

    for (t = temp; t; t = t->next)
        for (tl = t->tlist; tl; tl = tl->next)
        {
            Generate(QOP_PUSH, (DATAOBJ *)&tl->addr, NULL, NULL);

            pl = smalloc(sizeof(struct _poplist));

