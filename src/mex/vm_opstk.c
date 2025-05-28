// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: vm_opstk.c,v 1.1.1.1 2002/10/01 17:54:16 sdudley Exp $";
#pragma on(unreferenced)

#define COMPILING_MEX_VM
#include "prog.h"
#include "vm.h"

int op_push(INST *inst, struct _args *arg)
{
    switch (inst->opform)
    {
    case FormByte:
        Push(arg->b1, byte);
        break;
    case FormWord:
        Push(arg->w1, word);
        break;
    case FormDword:
        Push(arg->dw1, dword);
        break;
    case FormAddr:
        Push(arg->a1, IADDR);
        break;
    case FormString:
        Push(arg->a1, IADDR);
        break;
    default:
        vm_err(err_invalid_form);
    }

    return 0;
}

int op_pop(INST *inst, struct _args *arg)
{
    byte b1;
    word w1;
    dword dw1;
    IADDR a1;

    NW(arg);

    switch (inst->opform)
    {
    case FormByte:
        Pop(b1, byte);
        store(&inst->arg1.addr, FormByte, &b1);
        break;
    case FormWord:
        Pop(w1, word);
        store(&inst->arg1.addr, FormWord, &w1);
        break;
    case FormDword:
        Pop(dw1, dword);
        store(&inst->arg1.addr, FormDword, &dw1);
        break;
    case FormAddr:
        Pop(a1, IADDR);
        store(&inst->arg1.addr, FormAddr, &a1);
        break;
    case FormString:
        Pop(a1, IADDR);
        store(&inst->arg1.addr, FormAddr, &a1);
        break;
    default:
        vm_err(err_invalid_form);
    }

    return 0;
}
