// SPDX-License-Identifier: GPL-2.0-or-later


#define N_INTRINFUNC (sizeof(_intrinfunc) / sizeof(_intrinfunc[0]))
#define StoreString(str, type, field, val) MexStoreStringAt(str + offsetof(type, field), val)

#define StoreByteString(str, type, field, val, size)                                               \
    MexStoreByteStringAt(str + offsetof(type, field), val, size)

#define REGS_ADDR regs_6
#define MAX_MEXFH 16

struct _mex_instance_stack // Instance info for this invocation of MEX
{
    VMADDR vmaLinebuf;
    VMADDR vmaUser;
    VMADDR vmaMarea;
    VMADDR vmaFarea;
    VMADDR vmaMsg;
    VMADDR vmaID;
    VMADDR vmaSys;
    struct mex_sys *pms;
    struct mex_msg *pmm;
    struct mex_usr *pmu;
    struct mex_instancedata *pmid;
    struct _mex_instance_stack *next;
    HAFF hafFile;
    HAFF hafMsg;
    word fht[MAX_MEXFH];
    word fhCallers;
    HUF huf;
    HUFF huff;
    long set_current;
    long set_last_msg;
    char szSetArea[MAX_ALEN];
#ifdef OBSOLETE
    word orig_timeremain;
    word orig_timeonline;
#endif
    sdword cbPriorMsg;
    sdword cbPriorFile;
};

