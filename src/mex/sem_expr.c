// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sem_expr.c,v 1.1.1.1 2002/10/01 17:54:01 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "mex.h"
#include "prog.h"
#include <string.h>

TLLIST *temp;

static QUADOP near SelectBinaryOperator(DATAOBJ **o1, word tok_op, DATAOBJ **o2, TYPEDESC **result);


DATAOBJ *idref(IDTYPE *id)
{
    ATTRIBUTES *at;
    DATAOBJ *dobj = NewDataObj();

    if ((at = st_find(symtab, id, FALSE)) == NULL)
    {
        error(MEXERR_UNDEFVARIABLE, id);

        at = st_enter(symtab, id, NULL);

        if (at == NULL)
            bug("idref: can't put name in table");

        at->class = ClassError;
    }

    if (at->class == ClassError)
        return NULL;

    if (at->class == ClassFunc)
    {
        error(MEXERR_CANTUSEFUNCASVAR);
        return NULL;
    }

    if (at->class == ClassStructName)
    {
        error(MEXERR_STRUCTMUSTBEDECL, at->name);
        return NULL;
    }

#ifdef EXPRDEBUG
    debug("Expr: Identifier '%s'", at->name);
#endif

    dobj->type = at->typedesc;

    if (at->class != ClassVariable && at->class != ClassArg)
        error(MEXERR_INVALIDIDENTTYPE);
    else
    {
        dobj->objform = ObjformAddress;
        dobj->form.addr = at->c.addr;


        if ((dobj->name = strdup(id)) == NULL)
            NoMem();
    }

    return dobj;
}


DATAOBJ *byteref(CONSTTYPE *ct)
{
    DATAOBJ *dobj = NewDataObj();

    dobj->type = &ByteType;
    dobj->objform = ObjformValue;
    dobj->form.val.valkind = ByteKind;
    dobj->form.val.kind.byteval = (byte)ct->val;

    if ((byte)ct->val >= (byte)128)
        dobj->type = &UnsignedByteType;

#ifdef EXPRDEBUG
    debug("Expr: ByteLiteral '%d'", ct->val);
#endif

    return dobj;
}


DATAOBJ *wordref(CONSTTYPE *ct)
{
    DATAOBJ *dobj = NewDataObj();

    dobj->type = &WordType;
    dobj->objform = ObjformValue;
    dobj->form.val.valkind = WordKind;
    dobj->form.val.kind.wordval = ct->val;

    if ((word)ct->val >= (word)32768u)
        dobj->type = &UnsignedWordType;

#ifdef EXPRDEBUG
    debug("Expr: WordLiteral '%d'", ct->val);
#endif

    return dobj;
}


DATAOBJ *dwordref(CONSTTYPE *ct)
{
    DATAOBJ *dobj = NewDataObj();

    dobj->type = &DwordType;
    dobj->objform = ObjformValue;
    dobj->form.val.valkind = DwordKind;
    dobj->form.val.kind.dwordval = ct->dwval;

    if ((dword)ct->val >= (dword)2147483648Lu)
        dobj->type = &UnsignedDwordType;

#ifdef EXPRDEBUG
    debug("Expr: DwordLiteral '%ld'", ct->dwval);
#endif

    return dobj;
}


DATAOBJ *stringref(CONSTTYPE *ct)
{
    struct _conval *cv;
    DATAOBJ *dobj = NewDataObj();
    byte *s = ct->lit;

    dobj->type = &StringType;
    dobj->objform = ObjformValue;
    dobj->form.val.valkind = StringKind;
    dobj->form.val.kind.str.segment = SEG_GLOBAL;
    dobj->form.val.kind.str.indirect = FALSE;

    cv = AddGlobalConst(strlen(s), s, dobj->type);

    dobj->form.val.kind.str.offset = cv->offset;

    dobj->init = cv;

#ifdef EXPRDEBUG
    debug("Expr: StringLiteral:  '%s'", ct->lit);
#endif

    free(ct->lit);
    return dobj;
}


    new->addr.segment = SEG_TEMP;
    new->addr.offset = 1 + (td->size * MAX_TEMP);
    new->addr.indirect = FALSE;
    new->addr.typedesc = td;
    new->next = NULL;


    for (t = temp; t; t = t->next)
    {

            for (reg = 1, last = NULL, tl = t->tlist;
                 tl && tl->addr.offset == reg + (td->size * MAX_TEMP);
                 last = tl, tl = tl->next, reg++)
                ;



    if ((t = malloc(sizeof(TLLIST))) == NULL)
        NoMem();

    t->next = temp;
    temp = t;

    t->size = td->size;
    t->tlist = new;

#ifdef DECLDEBUG
    debug("Allocated temporary at Temp:%d", new->addr.offset);
#endif

    return new->addr;
}


int WouldWeFreeTemporary(DATAOBJ *o, TLLIST **pptlT, TLIST **pptlTl, TLIST **pptlLast)
{
    TLLIST *t;
    TLIST *tl, *last, *next;

    if (o == NULL)
        return FALSE;


    for (t = temp; t; t = t->next)
    {
        for (tl = t->tlist, last = NULL; tl; tl = next)
        {
            next = tl->next;

            if (tl->addr.segment == o->form.addr.segment && tl->addr.offset == o->form.addr.offset)
            {
                if (pptlT)
                    *pptlT = t;

                if (pptlTl)
                    *pptlTl = tl;

                if (pptlLast)
                    *pptlLast = last;

                return TRUE;
            }
            else
            {
                last = tl;
            }
        }
    }

    return FALSE;
}


void MaybeFreeTemporary(DATAOBJ *o, word free_str)
{
    TLLIST *t;
    TLIST *tl;
    TLIST *last;

    if (WouldWeFreeTemporary(o, &t, &tl, &last))
    {

        if (last)
            last->next = tl->next;
        else
            t->tlist = tl->next;


        if (o->type == &StringType && free_str)
            if (!o->form.addr.indirect || o->form.addr.segment != SEG_TEMP)
                Generate(QOP_SKILL, o, NULL, NULL);

#ifdef EXPRDEBUG
        debug("Freed temporary %d", tl->addr.offset);
#endif

        free(tl);
    }
}


DATAOBJ *EvalSizeof(TYPEDESC *t)
{
    DATAOBJ *po = NewDataObj();

    if (t && t->form == FormArray && t->typeinfo.array.bounds.hi == (VMADDR)-1)
    {
        error(MEXERR_SIZEOFBOUNDLESSARRAY);
        return NULL;
    }

    po->type = &WordType;
    po->objform = ObjformValue;
    po->form.val.valkind = WordKind;
    po->form.val.kind.wordval = t ? t->size : 1;

    return po;
}


DATAOBJ *EvalBinary(DATAOBJ *o1, word operator, DATAOBJ * o2)
{
    DATAOBJ *dobj;
    TYPEDESC *result;
    QUADOP top;
    ADDRESS t;

    if (!o1 || !o2)
        return NULL;


            top = QOP_ASSIGN;
        }
    }
    else
    {

    if (top == QOP_ASSIGN || top == QOP_SCOPY)
    {
        if (o2->objform == ObjformValue)
        {
            error(MEXERR_LVALUEREQUIRED);
            return NULL;
        }

        if (o2->type && o2->type->form == FormStruct)
        {
            error(MEXERR_CANTASSIGNSTRUCT);
            return NULL;
        }

        memset(&t, '\0', sizeof(t));
    }
    else
        t = GetTemporary(result);


    MaybeFreeTemporary(o1, TRUE);
    MaybeFreeTemporary(o2, TRUE);


DATAOBJ *EvalUnary(DATAOBJ *o, word operator)
{
    DATAOBJ *res, zero;
    TYPEDESC *typ;
    ADDRESS t;

    char name[MAX_TN_LEN];

    if (o == NULL)
        return NULL;

    if (o->type == &VoidType)
    {
        error(MEXERR_TYPEMUSTNOTBEVOID);
        return NULL;
    }

    if (operator!= T_MINUS)
        bug("Invalid operator for EvalUnary");

    typ = o->type;

    if (typ->form != FormByte && typ->form != FormWord && typ->form != FormDword)
    {
        error(MEXERR_CANNOTAPPLYUNARY, TypeName(typ, name));
        return NULL;
    }

    res = NewDataObj();


    if (o->objform == ObjformValue)
    {
        *res = *o;
        res->name = NULL;

        switch (o->form.val.valkind)
        {
        case ByteKind:
            res->form.val.kind.byteval = (byte) - (sbyte)o->form.val.kind.byteval;
            break;

        case DwordKind:
            res->form.val.kind.dwordval = (dword) - (sdword)o->form.val.kind.dwordval;

    t = GetTemporary(o->type);

    res->objform = ObjformAddress;
    res->form.addr = t;


    zero.name = NULL;
    zero.type = o->type;
    zero.objform = ObjformValue;
    zero.form.val.valkind = o->form.val.valkind;


    Generate(QOP_SUBTRACT, &zero, o, &t);


    return res;
}


static QUADOP near SelectBinaryOperator(DATAOBJ **op1, word tok_op, DATAOBJ **op2,
                                        TYPEDESC **result)
{
    DATAOBJ *o1, *o2;
    struct _optable *ot;
    QUADOP ret;

    o1 = *op1;
    o2 = *op2;


    if (!StructEquiv(o1->type, o2->type))
        if (!CoerceTypes(op1, tok_op, op2))
            return QOP_NOP;


            if ((*op1)->type->fSigned || (*op2)->type->fSigned)
            {
                if ((*result)->form == FormByte)
                    *result = &ByteType;

                if ((*result)->form == FormWord)
                    *result = &WordType;

                if ((*result)->form == FormDword)
                    *result = &DwordType;
            }

            ret = ((*result == &StringType) ? ot->strop : ot->op);


    return QOP_NOP;
}


    if (!t1 || !t2)
        return FALSE;


    if (!t1 || !t2)
        return FALSE;

    if (t1->size != t2->size && t2->size != -1)
        return FALSE;


    if ((t1->form == FormByte || t1->form == FormWord || t1->form == FormDword ||
         t1->form == FormString) &&
        t2->form == t1->form && !!t1->fSigned == !!t2->fSigned)
    {
        return TRUE;
    }


    if (t1->form == FormArray && t2->form == FormArray &&
        StructEquiv(t1->typeinfo.array.el_type, t2->typeinfo.array.el_type) &&
        t1->typeinfo.array.bounds.lo == t2->typeinfo.array.bounds.lo &&
        (t1->typeinfo.array.bounds.hi == t2->typeinfo.array.bounds.hi ||
         t2->typeinfo.array.bounds.hi == (VMADDR)-1L))
    {
        return TRUE;
    }


int CoerceTypes(DATAOBJ **o1, int tok_op, DATAOBJ **o2)
{
    DATAOBJ *fromobj, *result;
    TYPEDESC *t1, *t2, *fromtype, *totype;
    int fDoFree;


    t1 = (*o1)->type;
    t2 = (*o2)->type;

    if (t1 == NULL || t2 == NULL)
        return FALSE;


    if (!(IsIntegral(t1) && IsIntegral(t2)))
    {
        bad_conversion(t1, t2);
        return FALSE;
    }


    if (tok_op == T_ASSIGN)
    {
        fromobj = *o1;
        fromtype = t1;
        totype = t2;
    }
    else if (t1->size > t2->size)
    {

        fromobj = *o1;
        fromtype = t1;
        totype = t2;
    }
    else
    {

    result = NewDataObj();
    result->type = totype;


    if (*o1 == fromobj)
    {
        if (fDoFree)
            MaybeFreeTemporary(*o1, TRUE);

        *o1 = result;
    }
    else
    {
        if (fDoFree)
            MaybeFreeTemporary(*o2, TRUE);

        *o2 = result;
    }

    return TRUE;
}


DATAOBJ *TypeCast(DATAOBJ *o, TYPEDESC *t)
{
    DATAOBJ *toobj = NewDataObj();

    if (t == &VoidType)
    {
        error(MEXERR_TYPEMUSTNOTBEVOID);
        return NULL;
    }

    if (!o || StructEquiv(o->type, t))
    {
        debug("Unnecessary typecast - ignored");
        return o;
    }

    if (!(IsIntegral(o->type) && IsIntegral(t)))
    {
        bad_conversion(o->type, t);
        return NULL;
    }

    if (ConvertTypes(o, o->type, toobj, t))
        MaybeFreeTemporary(o, TRUE);

    return toobj;
}


int ConvertTypes(DATAOBJ *fromobj, TYPEDESC *fromtype, DATAOBJ *toobj, TYPEDESC *totype)
{
    ADDRESS t;

#ifdef EXPRDEBUG
    byte name1[MAX_TN_LEN];
    byte name2[MAX_TN_LEN];
#endif

    byte byteval;
    word wordval;
    dword dwordval;


    if ((fromtype->form == totype->form && !!totype->fSigned == !!fromtype->fSigned) ||
        StructEquiv(fromtype, totype))
    {
        bug("Cannot coerce value to same type");
    }

    toobj->type = totype;


    if (fromobj->objform == ObjformValue)
    {

        if (totype->form == FormByte)
            toobj->form.val.valkind = ByteKind;
        else if (totype->form == FormWord)
            toobj->form.val.valkind = WordKind;
        else if (totype->form == FormDword)
            toobj->form.val.valkind = DwordKind;
        else if (totype->form == FormVoid)
        {
            error(MEXERR_VOIDCANTHAVEVALUE);
            return TRUE;
        }
        else
            bug("Unknown coercion 'to' type");

#ifdef EXPRDEBUG
        debug("Coerce literal from %s to %s", TypeName(fromtype, name1), TypeName(totype, name2));
#endif
    }
    else
    {

        t = GetTemporary(totype);

        toobj->objform = ObjformAddress;
        toobj->form.addr = t;

        do_static = FALSE;

#ifdef EXPRDEBUG
        debug("Coerce object from %s to %s", TypeName(fromtype, name1), TypeName(totype, name2));
#endif
    }

    if (fromtype->form == totype->form)
    {

        MaybeFreeTemporary(toobj, FALSE);
        toobj->form = fromobj->form;
        toobj->name = fromobj->name ? strdup(fromobj->name) : NULL;

        return FALSE;
    }
    else
        switch (fromtype->form)
        {

            if (do_static)
                byteval = fromobj->form.val.kind.byteval;
            else
                byteval = 0;

            switch (totype->form)
            {
                if (do_static)
                {
                    if (fromtype->fSigned)
                        toobj->form.val.kind.wordval = (word)(sword)(sbyte)byteval;
                    else
                        toobj->form.val.kind.wordval = (word)byteval;
                }
                else
                {
                    Generate(QOP_BYTE2WORD, fromobj, toobj, &t);
                }
                break;


            if (do_static)
                wordval = fromobj->form.val.kind.wordval;
            else
                wordval = 0;

            switch (totype->form)
            {
                break;


            if (do_static)
                dwordval = fromobj->form.val.kind.dwordval;
            else
                dwordval = 0;

            switch (totype->form)
            {
                if (do_static)
                {
                    if (fromtype->fSigned)
                        toobj->form.val.kind.wordval = (word)(sword)(sdword)dwordval;
                    else
                        toobj->form.val.kind.wordval = (word)dwordval;
                }
                else
                {
                    Generate(QOP_DWORD2WORD, fromobj, toobj, &t);
                }
                break;


DATAOBJ *ProcessStringChar(DATAOBJ *str, DATAOBJ *index, int fLvalue)
{
    DATAOBJ *ret;
    ADDRESS t;


    ret = NewDataObj();

    if (fLvalue)
    {
        t = GetTemporary(&AddrType);

        ret->type = &ByteType;
        ret->objform = ObjformAddress;
        ret->form.addr = t;

        Generate(QOP_SLVAL, str, index, &t);


        ret->form.addr.indirect = TRUE;
    }
    else
    {
        t = GetTemporary(&ByteType);

        ret->type = &ByteType;
        ret->objform = ObjformAddress;
        ret->form.addr = t;

        Generate(QOP_SRVAL, str, index, &t);
    }

    MaybeFreeTemporary(str, FALSE);
    MaybeFreeTemporary(index, TRUE);

    return ret;
}


    if (array->type->form == FormString)
        return (ProcessStringChar(array, index, fLvalue));

    if (array->type->form != FormArray)
    {
        if (array->name)
            error(MEXERR_VARMUSTBEARRAY, array->name);
        else
            error(MEXERR_CANTINDEXNONARRAY);

        return NULL;
    }

    if (index->type->form != FormByte && index->type->form != FormWord &&
        index->type->form != FormDword)
    {
        error(MEXERR_INVALIDIDXTYPE, array->name);
        return NULL;
    }


    if (check_subs && array->type->typeinfo.array.bounds.hi != (VMADDR)-1L)
    {
        range.lo = array->type->typeinfo.array.bounds.lo;
        range.hi = array->type->typeinfo.array.bounds.hi;
        range.obj = index;


            if (index->form.val.kind.wordval < range.lo || index->form.val.kind.wordval > range.hi)
            {
                error(MEXERR_OUTOFRANGESUBSCRIPT, index->form.val.kind.wordval, array->name);

                return NULL;
            }
        }
    }

    el_size.name = NULL;
    el_size.type = &WordType;
    el_size.objform = ObjformValue;
    el_size.form.val.valkind = WordKind;
    el_size.form.val.kind.wordval = array->type->typeinfo.array.el_type->size;


    if (array->form.addr.indirect)
    {
        DATAOBJ idx;


        add.name = NULL;
        add.type = &WordType;
        add.objform = ObjformValue;
        add.form.val.valkind = WordKind;
        add.form.val.kind.wordval = conpart;


        Generate(QOP_SUBTRACT, &idx, &add, &t);

        MaybeFreeTemporary(index, TRUE);
        MaybeFreeTemporary(&idx, TRUE);
    }
    else
    {
        Generate(QOP_MULTIPLY, index, &el_size, &t);

    idx.objform = ObjformAddress;
    idx.form.addr = t;

    res = NewDataObj();

    add.name = array->name;
    add.type = &AddrType;
    add.form.addr = array->form.addr;
    add.objform = ObjformAddress;

    if (array->form.addr.indirect)
    {
        add.form.addr.indirect = TRUE;
        add.form.addr.typedesc = &AddrType;
    }
    else
    {
        add.form.addr.indirect = FALSE;
        add.form.addr.typedesc = &AddrType;


    res->form.addr.indirect = TRUE;
    res->form.addr.typedesc = res->type;

    MaybeFreeTemporary(array, TRUE);


    pst = struc->type->typeinfo.struc.pst;


    res = NewDataObj();
    res->name = struc->name;
    res->type = pa->typedesc;


    if (!struc->form.addr.indirect || pa->c.addr.offset == 0)
    {
        res->objform = ObjformAddress;
        res->form.addr = struc->form.addr;
        res->form.addr.offset += pa->c.addr.offset;
        res->form.addr.typedesc = res->type;

#ifdef EXPRDEBUG
        debug("Dereference struct member '%s.%s' - at offset %d", struc->name ? struc->name : "??",
              pid, res->form.addr.offset);

#endif
    }

        base.name = struc->name;
        base.type = &AddrType;
        base.form.addr = struc->form.addr;
        base.objform = ObjformAddress;
        base.form.addr.typedesc = &AddrType;


        add.name = NULL;
        add.type = &WordType;
        add.objform = ObjformValue;
        add.form.val.valkind = WordKind;
        add.form.val.kind.wordval = pa->c.addr.offset;


        outaddr = GetTemporary(&AddrType);
        Generate(QOP_ADD, &base, &add, &outaddr);

        res->form.addr.typedesc = res->type;
        res->form.addr.indirect = TRUE;

        MaybeFreeTemporary(struc, TRUE);
    }

    return res;
}
