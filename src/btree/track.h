// SPDX-License-Identifier: GPL-2.0-or-later

// Include the common structures

#include "trackcom.h"

// Class for the message-tracking subsystem.

class TRACKER
{
    DBASE dbMsg;   // Database containing main msg info
    BTREE btOwner; // B-tree containing msg owner info
    BTREE btArea;  // B-tree containing area info

    char *GetOwnerName(TRK_OWNER to); // Get the name of a msg owner

    unsigned fOpen; // Is the tracking database open?

  public:
    CPPEXPORT TRACKER();  // Constructor
    CPPEXPORT ~TRACKER(); // Desctructor

    int CPPEXPORT open(char *szName, unsigned fNewFile);
    int CPPEXPORT close(void);

    int CPPEXPORT AddMsg(TRK_MSG_NDX *ptmn);
    int CPPEXPORT UpdateMsg(TRK_MSG_NDX *ptmn, TRK_MSG_NDX *ptmnOld);
    int CPPEXPORT DeleteMsg(TRK_MSG_NDX *ptmn);
    static char *CPPEXPORT GetStatus(TRK_MSG_NDX *ptmn);
    static char *CPPEXPORT GetPriority(TRK_MSG_NDX *ptmn);
    char *CPPEXPORT GetAreaOwner(char *szArea); // Get owner from an area name

    int CPPEXPORT LookupMsg(char *szTrackID, char *szOwner, char *szLocation, PALIST *ppl,
                            TRK_MSG_NDX *ptmn, unsigned uiIdx = 0);
    int CPPEXPORT SetOwner(TRK_OWNER to, char *szOwner);
    int CPPEXPORT GetOwner(TRK_OWNER to, char *szOwner);

    int CPPEXPORT GetDefaultOwner(char *szArea, TRK_OWNER to);
    int CPPEXPORT SetDefaultOwner(char *szArea, TRK_OWNER to);

    BTREE *CPPEXPORT GetOwnerBtree(void);
    BTREE *CPPEXPORT GetAreaBtree(void);
    DBASE *CPPEXPORT GetMsgDbase(void);
};