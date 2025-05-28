// SPDX-License-Identifier: GPL-2.0-or-later


#include "max_oldu.h"
#include "mm.h"
#include "prog.h"
#include <stdlib.h>

        return HIDDEN;
    else
    {
        int idx = ClassLevelIndex(usLevel);
        CLSREC *pcr = ClassRec(idx);

        static sword pequivs[] = {TWIT,    DISGRACE, LIMITED, NORMAL,    WORTHY, PRIVIL,
                                  FAVORED, EXTRA,    CLERK,   ASSTSYSOP, SYSOP};


        if (pcr->ulAccFlags & CFLAGA_HANGUP)
            return HIDDEN;
        if ((pcr->ulAccFlags & CFLAGA_NOLIMIT) && (pcr->ulMailFlags & CFLAGM_PVT) &&
            (pcr->ulMailFlags & CFLAGM_ATTRANY))
            return SYSOP;
        if ((pcr->ulMailFlags & (CFLAGM_LEDITOR | CFLAGM_RDONLYOK | CFLAGM_NOREALNM)) ||
            (pcr->ulAccFlags & (CFLAGA_ULBBSOK | CFLAGA_FLIST | CFLAGA_UHIDDEN)))
            return ASSTSYSOP;

