// SPDX-License-Identifier: GPL-2.0-or-later

#pragma off(unreferenced)
static char rcs_id[]="$Id: dbasec.cc,v 1.1.1.1 2002/10/01 17:49:28 sdudley Exp $";
#pragma on(unreferenced)

#include "dbase.h"

// C wrapper for DBASE class

extern "C"
{
  DBASE * BEXPENTRY DbOpen(char *szNam, FIELD *pf, unsigned uiNumFields, unsigned new_file, unsigned uiOrder)
  {
    DBASE *pdb=new DBASE;

    if (pdb->open(szNam, pf, uiNumFields, new_file, uiOrder) != 0)
    {
      delete pdb;
      return NULL;
    }

    return pdb;
  }

  int BEXPENTRY DbClose(DBASE *pdb)
  {
    if (pdb->close())
    {
      delete pdb;
      return TRUE;
    }

    return FALSE;
  }

  int BEXPENTRY DbInsert(DBASE *pdb, void *pvRecord)
  {
    return pdb->insert(pvRecord);
  }

  int BEXPENTRY DbLookup(DBASE *pdb, void **ppvFields, PALIST *ppl, void *pvFoundRec)
  {
    return pdb->lookup(ppvFields, ppl, pvFoundRec);
  }

//  int BEXPENTRY DbLookupR(DBASE *pdb, void **ppvFields, PALIST *ppl, void *pvFoundRec)
//  {
//    return pdb->lookupr(ppvFields, ppl, pvFoundRec);
//  }

  int BEXPENTRY DbLookupI(DBASE *pdb, void **ppvFields, PALIST *ppl, void *pvFoundRec, unsigned uiIdx)
  {
    return pdb->lookup(ppvFields, ppl, pvFoundRec, uiIdx);
  }

  int BEXPENTRY DbUpdate(DBASE *pdb, void *pvRecOld, void *pvRecNew)
  {
    return pdb->update(pvRecOld, pvRecNew);
  }

  int BEXPENTRY DbRemove(DBASE *pdb, void **ppvFields)
  {
    return pdb->remove(ppvFields);
  }

  int BEXPENTRY DbObtainLock(DBASE *pdb)
  {
    return pdb->obtain_lock();
  }

  int BEXPENTRY DbReleaseLock(DBASE *pdb)
  {
    return pdb->release_lock();
  }

  unsigned long BEXPENTRY DbSize(DBASE *pdb)
  {
    return pdb->size();
  }

//  SEQFIND BEXPENTRY DbFindSeqOpen(DBASE OS2FAR *pdb, void OS2FAR *pvRec)
//  {
//    return pdb->findseq_open(pvRec);
//  }
//
//  void OS2FAR * BEXPENTRY DbFindSeqNext(DBASE OS2FAR *pdb, SEQFIND sf)
//  {
//    return pdb->findseq_next(sf);
//  }
//
//  int BEXPENTRY DbFindSeqClose(DBASE OS2FAR *pdb, SEQFIND sf)
//  {
//    return pdb->findseq_close(sf);
//  }
};

