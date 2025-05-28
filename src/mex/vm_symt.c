// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: vm_symt.c,v 1.1.1.1 2002/10/01 17:54:19 sdudley Exp $";
#pragma on(unreferenced)

#define COMPILING_MEX_VM

#include "prog.h"
#include "vm.h"
#include <stdio.h>
#include <string.h>

static VMADDR vaLastAssigned = 0;


VMADDR EXPENTRY MexEnterSymtab(char *name, word size)
{
    struct _rtsym *rt, *end;
    VMADDR thisofs;


    if (n_entry >= n_rtsym)
        vm_err(err_too_many_rtsym);

    thisofs = vaLastAssigned;
    vaLastAssigned += size;


VMADDR EXPENTRY MexStoreByte(char *name, byte b)
{
    VMADDR ofs;

    ofs = MexEnterSymtab(name, sizeof(byte));
    *(byte *)DSEG(ofs) = b;

    return ofs;
}


VMADDR EXPENTRY MexStoreWord(char *name, word w)
{
    VMADDR ofs;

    ofs = MexEnterSymtab(name, sizeof(word));
    *(word *)DSEG(ofs) = w;

    return ofs;
}


VMADDR EXPENTRY MexStoreDword(char *name, dword dw)
{
    VMADDR ofs;

    ofs = MexEnterSymtab(name, sizeof(dword));
    *(dword *)DSEG(ofs) = dw;

    return ofs;
}


VMADDR EXPENTRY MexStoreString(char *name, char *str)
{
    word len;
    VMADDR vmaDesc, vmaStr;
    IADDR ia;


    vmaDesc = MexEnterSymtab(name, sizeof(IADDR));


    ia.segment = SEG_GLOBAL;
    ia.offset = vmaStr;
    ia.indirect = FALSE;


    *(word *)DSEG(vmaStr) = len;
    memmove(DSEG(vmaStr + 2), str, len);

    return vmaDesc;
}


IADDR EXPENTRY MexStoreHeapByteString(char *str, int len)
{
    VMADDR vmaStr;
    IADDR ia;


    ia.segment = SEG_GLOBAL;
    ia.offset = vmaStr;
    ia.indirect = FALSE;


    *(word *)DSEG(vmaStr) = len;
    memmove(DSEG(vmaStr + 2), str, len);

    return ia;
}


VMADDR EXPENTRY MexStoreStringAt(VMADDR vmaDesc, char *str)
{
    word len;
    VMADDR vmaStr;
    IADDR ia;


    if ((vmaStr = hpalloc(len + 2)) == END_HEAP)
        vm_err(err_no_ss);


    *(IADDR *)DSEG(vmaDesc) = ia;


    *(word *)DSEG(vmaStr) = len;
    memmove(DSEG(vmaStr + 2), str, len);

    return vmaDesc;
}


VMADDR EXPENTRY MexStoreByteStringAt(VMADDR vmaDesc, char *str, int len)
{
    VMADDR vmaStr;
    IADDR ia;


    ia.segment = SEG_GLOBAL;
    ia.offset = vmaStr;
    ia.indirect = FALSE;


    *(word *)DSEG(vmaStr) = len;
    memmove(DSEG(vmaStr + 2), str, len);

    return vmaDesc;
}
