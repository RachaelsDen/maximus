// SPDX-License-Identifier: GPL-2.0-or-later



typedef char DBASE;

    keycomp_t kf_base;
} FIELD;

typedef struct _seqfind
{
    int foo;
} OS2FAR *SEQFIND;

DBASE OS2FAR *BAPIENTRY DbOpen(char OS2FAR *szNam, FIELD OS2FAR *pf, unsigned uiNumFields,
                               unsigned new_file, unsigned uiOrder);
int BAPIENTRY DbClose(DBASE OS2FAR *pdb);
int BAPIENTRY DbInsert(DBASE OS2FAR *pdb, void OS2FAR *pvRecord);
int BAPIENTRY DbLookup(DBASE OS2FAR *pdb, void OS2FAR *OS2FAR *ppvFields, PALIST OS2FAR *ppl,
                       void OS2FAR *pvFoundRec);
int BAPIENTRY DbLookupI(DBASE OS2FAR *pdb, void OS2FAR *OS2FAR *ppvFields, PALIST OS2FAR *ppl,
                        void OS2FAR *pvFoundRec, unsigned uiIdx);
// int BAPIENTRY DbLookupR(DBASE OS2FAR *pdb, void OS2FAR * OS2FAR *ppvFields, PALIST OS2FAR *ppl,
// void OS2FAR *pvFoundRec);
int BAPIENTRY DbUpdate(DBASE OS2FAR *pdb, void OS2FAR *pvRecOld, void OS2FAR *pvRecNew);
int BAPIENTRY DbRemove(DBASE OS2FAR *pdb, void OS2FAR *OS2FAR *ppvFields);
int BAPIENTRY DbObtainLock(DBASE OS2FAR *pdb);
int BAPIENTRY DbReleaseLock(DBASE OS2FAR *pdb);
unsigned long BAPIENTRY DbSize(DBASE OS2FAR *pdb);

SEQFIND BAPIENTRY DbFindSeqOpen(DBASE OS2FAR *pdb, void OS2FAR *pvRec);
void OS2FAR *BAPIENTRY DbFindSeqNext(DBASE OS2FAR *pdb, SEQFIND sf);
int BAPIENTRY DbFindSeqClose(DBASE OS2FAR *pdb, SEQFIND sf);

