// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: vm_opcvt.c,v 1.1.1.1 2002/10/01 17:54:12 sdudley Exp $";
#pragma on(unreferenced)

#define COMPILING_MEX_VM
#include "prog.h"
#include "vm.h"

int op_b2w(INST *inst, struct _args *arg)
{
    word w;

    NW(inst);

    if (inst->flag & FLAG_ARG1_SIGNED)
        w = (word)(sword)(sbyte)arg->b1;
    else
        w = (word)arg->b1;

    store(&inst->res.dest, FormWord, &w);
    return 0;
}

int op_b2dw(INST *inst, struct _args *arg)
{
    dword dw;

    NW(inst);

    if (inst->flag & FLAG_ARG1_SIGNED)
        dw = (dword)(sdword)(sbyte)arg->b1;
    else
        dw = (dword)arg->b1;

    store(&inst->res.dest, FormDword, &dw);
    return 0;
}

int op_w2b(INST *inst, struct _args *arg)
{
    byte b;

    NW(inst);

    if (inst->flag & FLAG_ARG1_SIGNED)
        b = (byte)(sbyte)(sword)arg->w1;
    else
        b = (byte)arg->w1;

    store(&inst->res.dest, FormByte, &b);
    return 0;
}

int op_w2dw(INST *inst, struct _args *arg)
{
    dword dw;

    NW(inst);

    if (inst->flag & FLAG_ARG1_SIGNED)
        dw = (dword)(sdword)(sword)arg->w1;
    else
        dw = (dword)arg->w1;

    store(&inst->res.dest, FormDword, &dw);
    return 0;
}

int op_dw2b(INST *inst, struct _args *arg)
{
    byte b;

    NW(inst);

    if (inst->flag & FLAG_ARG1_SIGNED)
        b = (byte)(sbyte)(sdword)arg->dw1;
    else
        b = (byte)arg->dw1;

    store(&inst->res.dest, FormByte, &b);
    return 0;
}

int op_dw2w(INST *inst, struct _args *arg)
{
    word w;

    NW(inst);

    if (inst->flag & FLAG_ARG1_SIGNED)
        w = (word)(sword)(sdword)arg->dw1;
    else
        w = (word)arg->dw1;

    store(&inst->res.dest, FormWord, &w);
    return 0;
}
