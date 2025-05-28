// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: audit.c,v 1.1.1.1 2002/10/01 17:49:19 sdudley Exp $";
#pragma on(unreferenced)

#include "trackc.h"
#include <stdio.h>
#include <string.h>

#define AUDIT_TEST_FILE "audit.trk"

int c_main(void)
{
    TRK_MSG_NDX test1 = {"9306301200120000", "ADMN", {"MUFFIN", 9999L}, TS_NEW, TP_NORMAL};

    TRK_MSG_NDX test3 = {"9301012000100000",
                         "", // Default owner
                         {"BATH", 2L},
                         TS_NEW,
                         TP_NORMAL};

    TRK_MSG_NDX test2 = {"9307011902340000",
                         "DD", // Specify explicit owner
                         {"MUFFIN", 1235L},
                         TS_NEW,
                         TP_CRIT};

    TRK_MSG_NDX new;

    PALIST *ppl;
    TRK t = TrkOpen(AUDIT_TEST_FILE, 1);

    new = test1;

    TrkSetOwner(t, "ADMN", "Paul Ashmore");
    TrkSetOwner(t, "DD", "Tim Snape");
    TrkSetOwner(t, "SJD", "Scott Dudley");

    TrkSetDefaultOwner(t, "MUFFIN", "ADMN");
    TrkSetDefaultOwner(t, "BATH", "SJD");
    TrkSetDefaultOwner(t, "*", "SJD");

    TrkAddMsg(t, &test1);
    TrkAddMsg(t, &test2);
    TrkAddMsg(t, &test3);

    printf("\n*** Looking up second message\n\n");

    ppl = PalistNew();

    while (TrkLookupMsg(t, test2.szTrackID, NULL, NULL, ppl, &test2))
        TrkPrintMsg(t, &test2);

    printf("\n*** Looking up first message\n\n");

    PalistDestroy(ppl);
    ppl = PalistNew();

    while (TrkLookupMsg(t, test1.szTrackID, NULL, NULL, ppl, &test1))
        TrkPrintMsg(t, &test1);

    printf("\n*** Looking up DD messages\n\n");

    PalistDestroy(ppl);
    ppl = PalistNew();

    while (TrkLookupMsg(t, NULL, "DD", NULL, ppl, &test1))
        TrkPrintMsg(t, &test1);

    printf("\n*** Looking up all messages\n\n");

    PalistDestroy(ppl);
    ppl = PalistNew();

    while (TrkLookupMsg(t, NULL, NULL, NULL, ppl, &test1))
        TrkPrintMsg(t, &test1);

    PalistDestroy(ppl);
    ppl = PalistNew();

    printf("\n*** updating 1st msg (owner ADMN -> DD)!\n");

    test1 = new;
    strcpy(new.to, "DD");
    new.tl.uid = 666666L;
    TrkUpdateMsg(t, &test1, &new);

    printf("\n*** Looking up all messages\n\n");

    PalistDestroy(ppl);
    ppl = PalistNew();

    while (TrkLookupMsg(t, NULL, NULL, NULL, ppl, &test1))
        TrkPrintMsg(t, &test1);

    PalistDestroy(ppl);

    TrkClose(t);

    return 0;
}
