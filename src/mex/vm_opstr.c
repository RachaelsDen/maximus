// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: vm_opstr.c,v 1.1.1.1 2002/10/01 17:54:16 sdudley Exp $";
#pragma on(unreferenced)

#define COMPILING_MEX_VM
#include "prog.h"
#include "vm.h"
#include <string.h>

int op_scopy(INST *inst, struct _args *arg)
{
    byte *s1, *s2;
    word s1len;
    IADDR new;


    s1len = *(word *)s1;


    new.segment = SEG_GLOBAL;


    s2 = pbDs + new.offset;


    memmove(s2 + sizeof(word), s1, s1len);



        kill_str(&arg->a2, &inst->arg2.addr);
    }


    store(&inst->arg2.addr, FormAddr, &new);
    return 0;
}

int op_scat(INST *inst, struct _args *arg)
{
    byte *s1, *s2, *sto;
    word s1len, s2len, maxlen;
    IADDR new;


    s1len = *(word *)s1;
    s2len = *(word *)s2;


    new.segment = SEG_GLOBAL;


    if ((new.offset = hpalloc(sizeof(word) + maxlen)) == END_HEAP)
        vm_err(err_no_ss);

    new.indirect = FALSE;


    *(word *)sto = maxlen;
    sto += sizeof(word);



    store(&inst->res.dest, FormAddr, &new);

    return 0;
}

int op_skill(INST *inst, struct _args *arg)
{
    kill_str(&arg->a1, &inst->arg1.addr);
    return 0;
}

int op_slval(INST *inst, struct _args *arg)
{
    byte *str, *chptr;
    word slen, oldslen;
    word index;
    IADDR addr;

    str = fetch(FormString, &arg->a1);
    slen = *(word *)str;
    str += sizeof(word);

    index = arg->w2;

    if (index > 65000u || index == 0)
        vm_err("string bounds exception");


    if (index > slen)
    {
        oldslen = slen;


        addr.segment = SEG_GLOBAL;
        addr.indirect = 0;

        if ((addr.offset = hpalloc(index + sizeof(word))) == END_HEAP)
            vm_err(err_no_ss);


        if (slen && arg->a1.offset != 0)
            hpfree(str - pbDs - 2);


        slen = index;
        *(word *)str = slen;


        memset(str + oldslen, ' ', slen - oldslen);


    chptr = &str[index - 1];
    addr.segment = SEG_GLOBAL;
    addr.offset = (VMADDR)(chptr - pbDs);
    addr.indirect = FALSE;

    store(&inst->res.dest, FormAddr, &addr);

    return 0;
}


    if (index > slen)
        ch = ' ';
    else
        ch = str[index - 1];

    store(&inst->res.dest, FormByte, &ch);

    return 0;
}

int op_slogical(INST *inst, struct _args *arg)
{
    byte *s1, *s2;
    word s1len, s2len, minlen;
    word res;
    sword cmp;

    s1 = fetch(FormString, &arg->a1);
    s2 = fetch(FormString, &arg->a2);

    s1len = *(word *)s1;
    s2len = *(word *)s2;
    minlen = min(s1len, s2len);

    s1 += sizeof(word);
    s2 += sizeof(word);

    cmp = strncmp(s1, s2, minlen);

    switch (inst->opcode)
    {
    case QOP_SGT:
        res = ((cmp == 0) ? (s1len > s2len) : (cmp > 0));
        break;
    case QOP_SGE:
        res = ((cmp == 0) ? (s1len >= s2len) : (cmp >= 0));
        break;
    case QOP_SEQ:
        res = (cmp == 0 && s1len == s2len);
        break;
    case QOP_SNE:
        res = (cmp != 0 || s1len != s2len);
        break;
    case QOP_SLE:
        res = ((cmp == 0) ? (s1len <= s2len) : (cmp <= 0));
        break;
    case QOP_SLT:
        res = ((cmp == 0) ? (s1len < s2len) : (cmp < 0));
        break;
    default:
        vm_err(err_invalid_opcode);
    }

    store(&inst->res.dest, FormWord, &res);
    return 0;
}
