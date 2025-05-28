// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sem_vm.c,v 1.1.1.1 2002/10/01 17:54:06 sdudley Exp $";
#pragma on(unreferenced)

#include "bfile.h"
#include "prog.h"
#include "vm.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static BFILE bVm;
static struct _vmh vmh;


    slash = strrstr(outfile, "\\/");
    dot = strrchr(outfile, '.');


    strcat(outfile, ".vm");

    if ((bVm = Bopen(outfile, BO_CREAT | BO_TRUNC | BO_RDWR | BO_BINARY, BSH_DENYNO, VM_BUFSIZE)) ==
        NULL)
    {
        return -1;
    }

    memset(&vmh, '\0', sizeof(struct _vmh));


    memmove(vmh.vmtext, "MEX Virtual Machine\x1a", 20);

    if (Bwrite(bVm, (char *)&vmh, sizeof(struct _vmh)) != sizeof(struct _vmh))
        return -1;

    return 0;
}

int close_vm(void)
{
    struct _implist *gp;
    struct _ipatlist *pl;
    struct _funcdef *fd, *fdnext;
    struct _fcall *fc, *fcnext;
    int n_imp, n_fdef, n_fcall;


    for (gp = ilist, n_imp = 0; gp; gp = gp->next, n_imp++)
    {

        if (Bwrite(bVm, (char *)&gp->ref, sizeof(struct _imp)) != sizeof(struct _imp))
        {
            return -1;
        }


        for (pl = gp->pat; pl; pl = pl->next)
            Bwrite(bVm, (char *)&pl->pat, sizeof(struct _ipat));
    }


            n_fcall++;


            for (tfc = fc, this_n_fcall = 0; tfc; tfc = tfc->next)
                if (!tfc->written && eqstr(fc->name, tfc->name))
                    this_n_fcall++;

            dfc.n_quads = this_n_fcall;

            if (Bwrite(bVm, (char *)&dfc, sizeof(struct _dfcall)) != sizeof(struct _dfcall))
                return -1;


            for (tfc = fc; tfc && pvma < pvmaOrig + this_n_fcall; tfc = tfc->next)
                if (!tfc->written && eqstr(fc->name, tfc->name))
                {
                    *pvma++ = tfc->quad;
                    tfc->written = TRUE;
                }


        if (fc->name)
            free(fc->name);
    }

    Bseek(bVm, 0L, BSEEK_SET);


    if (Bwrite(bVm, (char *)&vmh, sizeof(struct _vmh)) != sizeof(struct _vmh))
        return -1;

    Bclose(bVm);

    return 0;
}

void GenerateVM(QUADOP op, DATAOBJ *o1, DATAOBJ *o2, ADDRESS *dest)
{
    INST quad;


    memset(&quad, '\0', sizeof(INST));


    if (op != QOP_JMP && op != QOP_FUNCJUMP && op != QOP_FUNCJUMP && op != QOP_FUNCSTART &&
        op != QOP_FUNCRET && op != QOP_PUSH && op != QOP_POP)
    {
        if (o1 && o1->type)
        {
            if (o1->type->fSigned)
                quad.flag |= FLAG_ARG1_SIGNED;

            if (o1->type->form == FormAddr || o1->type->form == FormArray)
            {
                quad.flag |= FLAG_ARG1_ADDR;


                if (op != QOP_ARG_REF)
                {
                    if (o2)
                        quad.opform = o2->type->form;
                    else
                    {

                        quad.opform = o1->type->form;
                    }
                }
            }
            else
            {

                quad.opform = o1->type->form;
            }
        }

        if (o2 && o2->type && o2->type->fSigned)
            quad.flag |= FLAG_ARG2_SIGNED;


    if (op == QOP_JMP || op == QOP_JZ || op == QOP_JNZ)
        quad.res.jump_label = 0xffffu;
    else if (op == QOP_PUSH || op == QOP_POP)
    {
        ADDRESS *a = (ADDRESS *)o1;

    }
    else if (op == QOP_FUNCJUMP)
        add_funccall((ATTRIBUTES *)o1);
    else if (op == QOP_FUNCSTART)
        add_funcdef((ATTRIBUTES *)o1);
    else if (op == QOP_ARG_VAL || op == QOP_ARG_REF)
        handle_func_arg(&quad, op, o1, o2);
    else if (op == QOP_FUNCRET)
    {
        ATTRIBUTES *attr;
        PATCH p;


        quad.res.dest.segment = dest->segment;
        quad.res.dest.offset = dest->offset;
        quad.res.dest.indirect = dest->indirect;
    }


    if (op != QOP_PUSH && op != QOP_POP)
    {
        if (o1 && o1->objform == ObjformValue)
            quad.flag |= FLAG_ARG1_LIT;

        if (op != QOP_ARG_REF && o2 && o2->objform == ObjformValue)
            quad.flag |= FLAG_ARG2_LIT;
    }

    WriteQuad(&quad);
}


static int near copy_arg(union _lit_or_addr *arg, DATAOBJ *obj, word argn)
{

    if (obj->objform == ObjformValue)
    {
        switch (obj->form.val.valkind)
        {
        case ByteKind:
            arg->litbyte = obj->form.val.kind.byteval;
            break;
        case WordKind:
            arg->litword = obj->form.val.kind.wordval;
            break;
        case DwordKind:
            arg->litdword = obj->form.val.kind.dwordval;
            break;
        case StringKind:
            arg->litstr = obj->form.val.kind.str;


            if (obj->form.val.kind.str.segment == SEG_GLOBAL)
            {
                assert(obj->init != NULL);

                add_global(obj->name, obj->init->len, obj->init, argn);
            }
            break;

        default:
            bug("Invalid valkind in sem_vm");
        }

        return TRUE;
    }

static int near WriteQuad(INST *quad)
{
    if (Bwrite(bVm, (char *)quad, sizeof(INST)) != sizeof(INST))
        return -1;

#ifdef DEBUG
    printf("t=%d, %ld\n", this_quad, Btell(bVm));
#endif

    this_quad++;
    return 0;
}


int BackPatchVM(PATCH *pat, VMADDR to_where)
{
    INST inst;
    PATCH *p;


        Bseek(bVm, sizeof(struct _vmh) + (sizeof(INST) * (long)p->quad), BSEEK_SET);


        Bseek(bVm, -(long)sizeof(INST), BSEEK_CUR);

        inst.res.jump_label = to_where;

        if (Bwrite(bVm, (char *)&inst, sizeof(INST)) != sizeof(INST))
            return -1;
    }


    Bseek(bVm, 0L, BSEEK_END);
    return 0;
}


struct _implist *add_one_global(char *name, VMADDR size, struct _conval *init)
{
    struct _implist *gp;


    vmh.lGlobSize += gp->ref.size;

    return gp;
}


static void near add_global(char *name, VMADDR size, struct _conval *init, word argn)
{
    struct _implist *gp;
    struct _ipatlist *newpat;


    newpat->pat.argn = argn;
    newpat->pat.ip = this_quad;
    newpat->next = NULL;


                newpat->next = gp->pat;
                gp->pat = newpat;
                gp->ref.n_patch++;
                break;
            }
        }
    }


    if (!gp)
    {
        gp = add_one_global(name, size, init);
        gp->ref.n_patch++;
        gp->pat = newpat;
    }

    return;
}


    fd = smalloc(sizeof(struct _funcdef));

    fd->name = sstrdup(f->name);
    fd->quad = this_quad;

    fd->next = fdlist;
    fdlist = fd;
}

static void near handle_func_arg(INST *inst, QUADOP op, DATAOBJ *o, DATAOBJ *o2)
{

    inst->flag |= FLAG_ARG1_ADDR;

    if (o->objform == ObjformAddress &&
