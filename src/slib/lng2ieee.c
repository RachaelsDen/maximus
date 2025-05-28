// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"


unsigned long _fast long_to_ieee(unsigned long l)
{
    unsigned long origtest, test, f;


    for (test = 31L;; test--)
    {
        if (l >= (unsigned long)(1L << test))
        {

            f = (0x40000000L | (test << 23));


                if (test == 0)
                    break;
            }

            return f;
        }

        if (test == 0)
            break;
    }

    return 0L;
}
