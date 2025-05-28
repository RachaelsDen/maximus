// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef VM_H_DEFINED__
#define VM_H_DEFINED__

#ifndef MEX_H_DEFINED__
#include "mex.h"
#endif



struct _vm_quad;
typedef struct _vm_quad INST;


#ifdef UNIX

#ifdef DEBUGSTACK
#define DebPush(val, t) printf("Ps(" #val ",%d) ", sizeof(t));
#define DebPop(val, t) printf("Po(" #val ",%d) ", sizeof(t));
#else
#define DebPush(val, t)
#define DebPop(val, t)
#endif

#define Push(val, t)                                                                               \
    do                                                                                             \
    {                                                                                              \
        pbSp -= sizeof(t);                                                                         \
        *(t *)pbSp = *(t *)&val;                                                                   \
        DebPush(val, t);                                                                           \
    } while (0)
#define Pop(val, t)                                                                                \
    do                                                                                             \
    {                                                                                              \
        val = *(t *)pbSp;                                                                          \
        pbSp += sizeof(t);                                                                         \
        DebPop(val, t);                                                                            \
    } while (0)



#define END_HEAP                                                                                   \





struct _opproc
{
    int (*op_proc)(INST *inst, struct _args *arg);
    word op_val;
#ifdef DEBUGVM
    char *lit;
#endif
};


struct _dsheap
{
#ifdef HEAP_SIGNATURE
#define DSHEAP_SIG 0x6566
    word sig;
#endif
    VMADDR size;
    VMADDR next;
    byte free;
    byte rsvd;
};


vm_extern struct _usrfunc
{
    char *name;
    word(EXPENTRY *fn)(void);
    VMADDR quad;
} * usrfn;




struct _vm_quad
{


    {
        VMADDR jump_label;
        IADDR dest;
    } res;
};


struct _dfuncdef
{
    char name[MAX_GLOB_LEN];
    VMADDR quad;
};

    dword n_quads;
};


struct _funcdef
{
    char *name;
    VMADDR quad;
    struct _funcdef *next;
};

    struct _fcall *next;
};




vm_extern char err_cdata_ovfl[] VM_IS("Stack/heap collision. (Constant data area too large!)");
vm_extern char err_divby0[] VM_IS("Division by zero");
vm_extern char err_invalid_opcode[] VM_IS("Invalid opcode");
vm_extern char err_invalid_reg[] VM_IS("Internal err: invalid register");
vm_extern char err_invalid_access[] VM_IS("Invalid data access: seg %x ofs %08lx");
vm_extern char err_invalid_optype[] VM_IS("Invalid optype");
vm_extern char err_invalid_form[] VM_IS("Invalid form");
vm_extern char err_too_many_rtsym[] VM_IS("Too many global variables");
vm_extern char err_patch_ofs[] VM_IS("Patch bounds exception");
vm_extern char err_cant_pass_reg_addr[] VM_IS("Cannot pass address of register");
vm_extern char err_no_ss[] VM_IS("Out of string space");
vm_extern char err_instr_too_big[] VM_IS("Cannot read .vm file larger than 64k");
#endif


#ifdef COMPILING_MEX_VM
int init_symtab(int cRtSym);
void hpinit(void);
VMADDR hpalloc(word len);
void hpfree(VMADDR ofs);
void hpdbug(void);
void *fetch(FORM form, IADDR *where);
int store(IADDR *dest, FORM form, void *val);
void _stdc vm_err(char *format, ...);
int VmRead(char *name);
void kill_str(IADDR *strptr, IADDR *ptrptr);
#endif


#include "vm_ifc.h"

#ifdef COMPILING_MEX_VM
#include "vm_op.h"
#endif

