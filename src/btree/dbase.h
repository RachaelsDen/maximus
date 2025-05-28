// SPDX-License-Identifier: GPL-2.0-or-later



    int CPPEXPORT update(void *pvRecOld, void *pvRecNew, int iLength = 0);
    int CPPEXPORT remove(void **ppvFields);
    int CPPEXPORT close();
    int CPPEXPORT obtain_lock(void);
    int CPPEXPORT release_lock(void);
    unsigned long CPPEXPORT size(void);

    // notused
    //  SEQFIND CPPEXPORT DBASE::findseq_open(void *pvRec);
    //  void * CPPEXPORT DBASE::findseq_next(SEQFIND sf);
    //  int CPPEXPORT DBASE::findseq_close(SEQFIND sf);

    // Functions to obtain internal access to the database B-trees.  Not
    // for use by standard funtions:

    BTREE *CPPEXPORT get_btrees();
};

#endif // __DBASE_H_DEFINED
