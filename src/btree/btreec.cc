// SPDX-License-Identifier: GPL-2.0-or-later

#pragma off(unreferenced)
static char rcs_id[]="$Id: btreec.cc,v 1.1.1.1 2002/10/01 17:49:22 sdudley Exp $";
#pragma on(unreferenced)

#include "btree.h"

// C wrapper for BTREE class

extern "C"
{
  BTREE *BEXPENTRY BtreeNew(void)
  {
    BTREE *pbt=new BTREE;
    return pbt;
  }

  void BEXPENTRY BtreeDelete(BTREE *pbt)
  {
    delete pbt;
  }

  int BEXPENTRY BtOpen(BTREE *pbt, char *pszFile, keycomp_t kf_ins, keycomp_t kf_srch, unsigned uiKeySz, unsigned new_file, unsigned uiOrd)
  {
    return pbt->open(pszFile, kf_ins, kf_srch, uiKeySz, new_file, uiOrd);
  }

  int BEXPENTRY BtClose(BTREE *pbt)
  {
    return pbt->close();
  }

  void * BEXPENTRY BtLookup(BTREE *pbt, void *key, PALIST *pl)
  {
    return pbt->lookup(key, pl);
  }

  int BEXPENTRY BtInsert(BTREE *pbt, void *key, unsigned flags)
  {
    return pbt->insert(key, flags);
  }

  int BEXPENTRY BtValidate(BTREE *pbt)
  {
    return pbt->validate();
  }

  int BEXPENTRY BtRemove(BTREE *pbt, void *key)
  {
    return pbt->remove(key);
  }

  unsigned long BEXPENTRY BtSize(BTREE *pbt)
  {
    return pbt->size();
  }

  BTERROR BEXPENTRY BtError(BTREE *pbt)
  {
    return pbt->error();
  }

  PALIST * BEXPENTRY PalistNew(void)
  {
    return new PALIST;
  }

  void BEXPENTRY PalistDelete(PALIST *ppl)
  {
    if (ppl)
      delete ppl;
  }
};

