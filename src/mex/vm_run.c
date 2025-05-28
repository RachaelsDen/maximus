// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: vm_run.c,v 1.2 2003/06/05 01:10:36 wesgarland Exp $";
#pragma on(unreferenced)

#define VM_INIT
#define COMPILING_MEX_VM

#include "dv.h"
#include "mex.h"
#include "vm.h"
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void EXPENTRY (*pfnHookBefore)(void) = 0;
static void EXPENTRY (*pfnHookAfter)(void) = 0;


static struct _opproc opproc[] = {

void *EXPENTRY MexFetch(FORM form, IADDR *where) { return (fetch(form, where)); }


VMADDR EXPENTRY MexIaddrToVM(IADDR *pia)
{
    IADDR ia;

    ia = *pia;
    ia.indirect = FALSE;

    return MexPtrToVM(MexFetch(FormByte, pia));
}


void kill_str(IADDR *strptr, IADDR *ptrptr)
{
    IADDR new;

    if (strptr->segment != SEG_GLOBAL)
        vm_err("kill_str: non-global segment");


    hpfree(strptr->offset);


    new.segment = SEG_GLOBAL;
    new.offset = 0;
    new.indirect = FALSE;

    store(ptrptr, FormAddr, &new);
}


    pinCs = NULL;
    pbSp = pbBp = NULL;
    pdshDheap = NULL;
    vaIp = high_cs = 0;
    n_entry = 0;

    memset(regs_1, '\0', sizeof regs_1);
    memset(regs_2, '\0', sizeof regs_2);
    memset(regs_4, '\0', sizeof regs_4);
    memset(regs_6, '\0', sizeof regs_6);

    debheap = 0;

    return 0;
}

static int near vm_cleanup(void)
{
    struct _funcdef *fd, *fdnext;


    for (fd = fdlist; fd; fdnext = fd->next, free(fd), fd = fdnext)
        if (fd->name)
            free(fd->name);

    fdlist = NULL;


    if (pbDs)
    {
        free(pbDs);
        pbDs = NULL;
    }

    return 0;
}

void _stdc vm_err(char *format, ...)
{
    va_list varg;
    char err[MAXERRLEN];

    va_start(varg, format);
    vsprintf(err, format, varg);
    va_end(varg);

    (*pfnLogger)("!MEX:  fatal cs:%08lx: %s", vaIp - 1L, err);


void EXPENTRY MexRTError(char *szMsg) { vm_err("%s", szMsg); }


void *fetch(FORM form, IADDR *where)
{
    IADDR got;
    void *ret;

    got = *where;

    while (got.indirect)
    {
        got.indirect = FALSE;
        ret = fetch(FormAddr, &got);

        if (ret == NULL)
            vm_err(err_invalid_access, 0xffff, vaIp);

        got = *(IADDR *)ret;
    }

    switch (got.segment)
    {
    case SEG_AR:
        return (pbBp + got.offset);
    case SEG_GLOBAL:
        return (pbDs + got.offset);
    case SEG_TEMP:
        switch (form)
        {
        case FormByte:
            return ((void *)&regs_1[got.offset - 1000]);
        case FormWord:
            return ((void *)&regs_2[got.offset - 2000]);
        case FormDword:
            return ((void *)&regs_4[got.offset - 4000]);
        case FormAddr:
        case FormString:
            return ((void *)&regs_6[got.offset - 6000]);
        default:
            vm_err(err_invalid_reg);
        }
        break;
    }

    vm_err(err_invalid_access, got.segment, got.offset);
    return NULL;
}


int store(IADDR *dest, FORM form, void *val)
{
    void *dp;

    dp = fetch(form, dest);

    switch (form)
    {
    case FormByte:
        *(byte *)dp = *(byte *)val;
        break;
    case FormWord:
        *(word *)dp = *(word *)val;
        break;
    case FormDword:
        *(dword *)dp = *(dword *)val;
        break;
    case FormAddr:
        *(IADDR *)dp = *(IADDR *)val;
        break;
    default:
        vm_err(err_invalid_optype);
    }

    return 0;
}


    struct _funcdef *fdef;
    struct _usrfunc *uf;
    VMADDR i;
    int rc = TRUE;

    usrfn = puf;

    for (uf = usrfn, i = (VMADDR)-2L; uf < usrfn + uscIntrinsic; uf++, i--)
    {

        if ((fdef = malloc(sizeof(struct _funcdef))) == NULL)
        {
            rc = FALSE;
            break;
        }

        fdef->quad = uf->quad;

        fdef->next = fdlist;
        fdlist = fdef;

        if ((fdef->name = strdup(uf->name)) == NULL)
        {
            rc = FALSE;
            break;
        }
    }

    if (!rc)
    {
        struct _funcdef *fdNext;


        for (fdef = fdlist; fdef; fdNext = fdef->next, free(fdef), fdef = fdNext)
            if (fdef->name)
                free(fdef->name);

        fdlist = NULL;
    }

    return rc;
}


static void near PushArgv(char *pszArgs)
{
    if (!pszArgs)
        pszArgs = "";

    pbSp -= sizeof(IADDR);
    MexStoreStringAt(pbSp - pbDs, pszArgs);
}

    return 0;
}


    if (inst->opcode != QOP_FUNCRET)
    {
        if (inst->flag & FLAG_ARG1_ADDR)
        {
            if (inst->arg1.addr.indirect && inst->opcode != QOP_ARG_VAL &&
                inst->opcode != QOP_ARG_REF)
            {
                got = inst->arg1.addr;
                got.indirect = FALSE;

                arg.a1 = *(IADDR *)fetch(FormAddr, &got);
            }
            else
                arg.a1 = inst->arg1.addr;
        }
        else
            switch (opform)
            {
            case FormByte:
                if (inst->flag & FLAG_ARG1_LIT)
                    arg.b1 = inst->arg1.litbyte;
                else
                    arg.b1 = *(byte *)fetch(FormByte, &inst->arg1.addr);
                break;

            case FormWord:
                if (inst->flag & FLAG_ARG1_LIT)
                    arg.w1 = inst->arg1.litword;
                else
                    arg.w1 = *(word *)fetch(FormWord, &inst->arg1.addr);
                break;

            case FormDword:
                if (inst->flag & FLAG_ARG1_LIT)
                    arg.dw1 = inst->arg1.litdword;
                else
                    arg.dw1 = *(dword *)fetch(FormDword, &inst->arg1.addr);
                break;

            case FormString:
                if (inst->flag & FLAG_ARG1_LIT)
                    arg.a1 = inst->arg1.litstr;
                else
                    arg.a1 = *(IADDR *)fetch(FormString, &inst->arg1.addr);
            }


        if (inst->opcode == QOP_SLVAL || inst->opcode == QOP_SRVAL)
            opform = FormWord;


    if (inst->opcode < QOP_QUAD_LAST)
    {
#ifdef DEBUGVM
        if (deb)
            printf("%-10s: ", opproc[inst->opcode].lit);
#endif

        (*opproc[inst->opcode].op_proc)(inst, &arg);
    }
    else
    {
        vm_err(err_invalid_opcode);
    }

    return ret;
}


    for (fd = fdlist; fd; fd = fd->next)
        if (eqstr(fd->name, "main"))
        {
            vaIp = fd->quad;
            break;
        }

    if (fd == NULL)
        vm_err("no main() function");


    pbBp = pbSp = pbDs + vmh.lGlobSize + vmh.lStackSize;

    PushArgv(pszArgs);


    start_addr = (VMADDR)-1;
    Push(start_addr, VMADDR);

    do
    {
        while (vaIp < high_cs)
        {
#ifdef DEBUGVM
            if (deb)
            {
                printf("cs%08" UINT32_XFORMAT ": ", vaIp);
                fflush(stdout);
            }
#endif

            proc_instruction(pinCs + vaIp++);

#ifdef DEBUGVM
            if (deb)
                printf("\n");
#endif
        }

        for (uf = usrfn; uf->name; uf++)
            if (vaIp == uf->quad)
            {
                Push(pbBp, byte *);

                pbBp = pbSp;

                if (pfnHookBefore)
                    (*pfnHookBefore)();

                pop_size = (*uf->fn)();

                if (pfnHookAfter)
                    (*pfnHookAfter)();

                Pop(pbBp, byte *);
                Pop(vaIp, VMADDR);

                pbSp += pop_size;

                break;
            }

        if (uf->name == NULL && vaIp != (VMADDR)-1L)
            vm_err("abnormal program termination");
    } while (vaIp != (VMADDR)-1L);

#ifdef DEBUGVM
    if (debheap)
        hpdbug();
#endif


int EXPENTRY MexExecute(char *pszFile, char *pszArgs, dword fFlag, unsigned short uscIntrinsic,
                        struct _usrfunc *puf, int(EXPENTRY *pfnSetup)(void),
                        void(EXPENTRY *pfnTerm)(short *psRet),
                        void(_stdc *pfnLog)(char *szStr, ...), void(EXPENTRY *pfnHkBefore)(void),
                        void(EXPENTRY *pfnHkAfter)(void))
{
    short ret;

    pfnLogger = pfnLog ? pfnLog : NullLogger;
    pfnHookBefore = pfnHkBefore;
    pfnHookAfter = pfnHkAfter;


        if (fFlag & VMF_DEBEXE)
            deb = TRUE;

        if (fFlag & VMF_DEBHEAP)
            debheap = TRUE;


            if (VmRead(pszFile) == -1)
            {
                ret = 1;
            }
            else
            {

                if (!pfnSetup || (ret = (*pfnSetup)()) == 0)
                {
                    ret = VmRun(pszArgs);

                    if (pfnTerm)
                        (*pfnTerm)(&ret);
                }
            }
        }
    }

    vm_cleanup();
    return ret;
}
