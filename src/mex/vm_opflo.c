// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: vm_opflo.c,v 1.2 2003/06/05 01:10:36 wesgarland Exp $";
#pragma on(unreferenced)

#define COMPILING_MEX_VM
#include "prog.h"
#include "vm.h"

int op_jmp(INST *inst, struct _args *arg)
{
#ifdef DEBUGVM
    VMADDR oldip = vaIp;
#endif


            if ((inst->opcode == QOP_JZ) == (arg->b1 == 0))
                vaIp = inst->res.jump_label;
            break;

        case FormWord:
            if ((inst->opcode == QOP_JZ) == (arg->w1 == 0))
                vaIp = inst->res.jump_label;
            break;

        case FormDword:
            if ((inst->opcode == QOP_JZ) == (arg->dw1 == 0))
                vaIp = inst->res.jump_label;
            break;

        default:
            vm_err(err_invalid_form);
        }

#ifdef DEBUGVM
    if (deb)
        if (vaIp != oldip)
            printf("jump to cs%08" UINT32_XFORMAT ". ", vaIp);
#endif

    return 0;
}

int op_logical(INST *inst, struct _args *arg)
{
    word res;

    switch (inst->opform)
    {
    case FormByte:
        if (inst->flag & (FLAG_ARG1_SIGNED | FLAG_ARG2_SIGNED))
        {
            switch (inst->opcode)
            {
            case QOP_GT:
                res = ((sbyte)arg->b1 > (sbyte)arg->b2);
                break;
            case QOP_GE:
                res = ((sbyte)arg->b1 >= (sbyte)arg->b2);
                break;
            case QOP_EQ:
                res = ((sbyte)arg->b1 == (sbyte)arg->b2);
                break;
            case QOP_NE:
                res = ((sbyte)arg->b1 != (sbyte)arg->b2);
                break;
            case QOP_LE:
                res = ((sbyte)arg->b1 <= (sbyte)arg->b2);
                break;
            case QOP_LT:
                res = ((sbyte)arg->b1 < (sbyte)arg->b2);
                break;
            case QOP_LAND:
                res = ((sbyte)arg->b1 && (sbyte)arg->b2);
                break;
            case QOP_LOR:
                res = ((sbyte)arg->b1 || (sbyte)arg->b2);
                break;
            default:
                vm_err(err_invalid_opcode);
            }
        }
        else
        {
            switch (inst->opcode)
            {
            case QOP_GT:
                res = (arg->b1 > arg->b2);
                break;
            case QOP_GE:
                res = (arg->b1 >= arg->b2);
                break;
            case QOP_EQ:
                res = (arg->b1 == arg->b2);
                break;
            case QOP_NE:
                res = (arg->b1 != arg->b2);
                break;
            case QOP_LE:
                res = (arg->b1 <= arg->b2);
                break;
            case QOP_LT:
                res = (arg->b1 < arg->b2);
                break;
            case QOP_LAND:
                res = (arg->b1 && arg->b2);
                break;
            case QOP_LOR:
                res = (arg->b1 || arg->b2);
                break;
            default:
                vm_err(err_invalid_opcode);
            }
        }
        break;

    case FormWord:
        if (inst->flag & (FLAG_ARG1_SIGNED | FLAG_ARG2_SIGNED))
        {
            switch (inst->opcode)
            {
            case QOP_GT:
                res = ((sword)arg->w1 > (sword)arg->w2);
                break;
            case QOP_GE:
                res = ((sword)arg->w1 >= (sword)arg->w2);
                break;
            case QOP_EQ:
                res = ((sword)arg->w1 == (sword)arg->w2);
                break;
            case QOP_NE:
                res = ((sword)arg->w1 != (sword)arg->w2);
                break;
            case QOP_LE:
                res = ((sword)arg->w1 <= (sword)arg->w2);
                break;
            case QOP_LT:
                res = ((sword)arg->w1 < (sword)arg->w2);
                break;
            case QOP_LAND:
                res = ((sword)arg->w1 && (sword)arg->w2);
                break;
            case QOP_LOR:
                res = ((sword)arg->w1 || (sword)arg->w2);
                break;
            default:
                vm_err(err_invalid_opcode);
            }
        }
        else
        {
            switch (inst->opcode)
            {
            case QOP_GT:
                res = (arg->w1 > arg->w2);
                break;
            case QOP_GE:
                res = (arg->w1 >= arg->w2);
                break;
            case QOP_EQ:
                res = (arg->w1 == arg->w2);
                break;
            case QOP_NE:
                res = (arg->w1 != arg->w2);
                break;
            case QOP_LE:
                res = (arg->w1 <= arg->w2);
                break;
            case QOP_LT:
                res = (arg->w1 < arg->w2);
                break;
            case QOP_LAND:
                res = (arg->w1 && arg->w2);
                break;
            case QOP_LOR:
                res = (arg->w1 || arg->w2);
                break;
            default:
                vm_err(err_invalid_opcode);
            }
        }

        break;

    case FormDword:
        if (inst->flag & (FLAG_ARG1_SIGNED | FLAG_ARG2_SIGNED))
        {
            switch (inst->opcode)
            {
            case QOP_GT:
                res = ((sdword)arg->dw1 > (sdword)arg->dw2);
                break;
            case QOP_GE:
                res = ((sdword)arg->dw1 >= (sdword)arg->dw2);
                break;
            case QOP_EQ:
                res = ((sdword)arg->dw1 == (sdword)arg->dw2);
                break;
            case QOP_NE:
                res = ((sdword)arg->dw1 != (sdword)arg->dw2);
                break;
            case QOP_LE:
                res = ((sdword)arg->dw1 <= (sdword)arg->dw2);
                break;
            case QOP_LT:
                res = ((sdword)arg->dw1 < (sdword)arg->dw2);
                break;
            case QOP_LAND:
                res = ((sdword)arg->dw1 && (sdword)arg->dw2);
                break;
            case QOP_LOR:
                res = ((sdword)arg->dw1 || (sdword)arg->dw2);
                break;
            default:
                vm_err(err_invalid_opcode);
            }
        }
        else
        {
            switch (inst->opcode)
            {
            case QOP_GT:
                res = (arg->dw1 > arg->dw2);
                break;
            case QOP_GE:
                res = (arg->dw1 >= arg->dw2);
                break;
            case QOP_EQ:
                res = (arg->dw1 == arg->dw2);
                break;
            case QOP_NE:
                res = (arg->dw1 != arg->dw2);
                break;
            case QOP_LE:
                res = (arg->dw1 <= arg->dw2);
                break;
            case QOP_LT:
                res = (arg->dw1 < arg->dw2);
                break;
            case QOP_LAND:
                res = (arg->dw1 && arg->dw2);
                break;
            case QOP_LOR:
                res = (arg->dw1 || arg->dw2);
                break;
            default:
                vm_err(err_invalid_opcode);
            }
        }
        break;

    default:
        vm_err(err_invalid_form);
    }

    store(&inst->res.dest, FormWord, &res);
    return 0;
}
