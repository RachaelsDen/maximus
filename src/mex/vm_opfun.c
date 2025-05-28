// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: vm_opfun.c,v 1.2 2003/06/05 01:10:36 wesgarland Exp $";
#pragma on(unreferenced)

#define COMPILING_MEX_VM
#include "prog.h"
#include "vm.h"
#include <string.h>

int op_funcstart(INST *inst, struct _args *arg)
{
    NW(inst);
    NW(arg);

#ifdef DEBUGVM
    if (deb)
        printf("Beginning function.  Local AR = %d, SP=%p, BP=%p. ", inst->res.jump_label, pbSp,
               pbBp);
#endif


    pbBp = pbSp;

    pbSp -= inst->res.jump_label;

    memset(pbSp, '\0', inst->res.jump_label);

    return 0;
}

int op_funcret(INST *inst, struct _args *arg)
{
    NW(inst);
    NW(arg);

#ifdef DEBUGVM
    if (deb)
        printf("Ending fn: AR=%d, ", inst->res.jump_label);
#endif


    Pop(pbBp, byte *);


    pbSp += inst->arg1.litdword;

#ifdef DEBUGVM
    if (deb)
        printf("args=%" UINT32_FORMAT ", newIP = %08" UINT32_XFORMAT ", newSP=%p",
               inst->arg1.litdword, vaIp, pbSp);
#endif
    return 0;
}

int op_startcall(INST *inst, struct _args *arg)
{
    NW(inst);
    NW(arg);

#ifdef DEBUGVM
    if (deb)
        printf("Start call.  IP=%08" UINT32_XFORMAT ", SP=%p.  ", vaIp, pbSp);
#endif

    return 0;
}

int op_arg_val(INST *inst, struct _args *arg)
{
    IADDR a;

    if (inst->flag & FLAG_ARG1_ADDR)
    {

        if (a.indirect)
        {
            a.indirect = FALSE;
            a = *(IADDR *)fetch(FormAddr, &a);
        }


        Push(a, IADDR);
    }
    else
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
        case FormString:
            Push(arg->a1, IADDR);
            break;
        default:
            vm_err(err_invalid_form);
        }

    return 0;
}

int op_funcjump(INST *inst, struct _args *arg)
{
    NW(inst);
    NW(arg);

#ifdef DEBUGVM
    if (deb)
        printf("Calling function at %08" UINT32_XFORMAT ". IP=%08" UINT32_XFORMAT ", SP=%p",
               inst->res.jump_label, vaIp, pbSp);
#endif


    vaIp = inst->res.jump_label;
    return 0;
}
