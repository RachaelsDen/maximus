// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"

#if !defined(OS_2) && !defined(NT) && !defined(M_I86CM) && !defined(M_I86LM) &&                    \
    !defined(M_I86HM) && !defined(__FLAT__) && !defined(__TURBOC__)



    int oursum = 0;

    char *null = NULL;

    int i;

    if (FirstTime)
    {
        FirstTime = FALSE;

        for (i = 0; i < CHECK_SIZE; i++)
            checksum += null[i];

        return FALSE;
    }
    else
    {
        for (i = 0; i < CHECK_SIZE; i++)
            oursum += null[i];

        return (oursum != checksum);
    }
}

#else
int _fast nullptr(void) { return (FALSE); }
#endif
