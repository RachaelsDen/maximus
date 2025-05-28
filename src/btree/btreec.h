// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __cplusplus
typedef char BTREE;
typedef char PALIST;
#endif

PALIST OS2FAR *BAPIENTRY PalistNew(void);
void BAPIENTRY PalistDelete(PALIST OS2FAR *ppl);

BTREE OS2FAR *BAPIENTRY BtreeNew(void);
void BAPIENTRY BtreeDelete(BTREE OS2FAR *pbt);

int BAPIENTRY BtOpen(BTREE OS2FAR *pbt, char OS2FAR *pszFile, keycomp_t kf_ins, keycomp_t kf_srch,
                     unsigned uiKeySz, unsigned new_file, unsigned uiOrd);
int BAPIENTRY BtClose(BTREE OS2FAR *pbt);
void *BAPIENTRY BtLookup(BTREE OS2FAR *pbt, void OS2FAR *key, PALIST OS2FAR *pl);
int BAPIENTRY BtInsert(BTREE OS2FAR *pbt, void OS2FAR *key, unsigned flags);
int BAPIENTRY BtValidate(BTREE OS2FAR *pbt);
int BAPIENTRY BtRemove(BTREE OS2FAR *pbt, void OS2FAR *key);
unsigned long BAPIENTRY BtSize(BTREE OS2FAR *pbt);
