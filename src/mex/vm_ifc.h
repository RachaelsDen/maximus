// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef VM_IFC_H_DEFINED__
#define VM_IFC_H_DEFINED__

#ifndef MEX_H_DEFINED__
#include "mex.h"
#endif

#ifndef vm_extern
#define vm_extern extern
#define VM_LEN(x)
#endif


int EXPENTRY MexExecute(char *pszFile, char *pszArgs, dword fFlag, unsigned short uscIntrinsic,
                        struct _usrfunc *puf, int(EXPENTRY *pfnSetup)(void),
                        void(EXPENTRY *pfnTerm)(short *psRet),
                        void(_stdc *pfnLog)(char *szStr, ...), void(EXPENTRY *pfnHookBefore)(void),
                        void(EXPENTRY *pfnHookAfter)(void));
void *EXPENTRY MexFetch(FORM form, IADDR *where);
void *EXPENTRY MexDSEG(VMADDR ofs);
VMADDR EXPENTRY MexEnterSymtab(char *name, word size);
VMADDR EXPENTRY MexStoreByte(char *name, byte b);
VMADDR EXPENTRY MexStoreWord(char *name, word w);
VMADDR EXPENTRY MexStoreDword(char *name, dword dw);
VMADDR EXPENTRY MexStoreString(char *name, char *str);
VMADDR EXPENTRY MexStoreStringAt(VMADDR vmaDesc, char *str);
void EXPENTRY MexKillString(IADDR *pwhere);
VMADDR EXPENTRY MexPtrToVM(void *ptr);
VMADDR EXPENTRY MexStoreByteStringAt(VMADDR vmaDesc, char *str, int len);
VMADDR EXPENTRY MexIaddrToVM(IADDR *pia);
IADDR EXPENTRY MexStoreHeapByteString(char *str, int len);
void EXPENTRY MexRTError(char *szMsg);

