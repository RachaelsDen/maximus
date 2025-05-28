// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"


unsigned long _fast ieee_to_long(unsigned long f)
{
    unsigned long l;
    unsigned char exp;
    signed short bt;


    exp = (unsigned char)(((f & 0x3f800000L) >> 23) + 1);


    bt = 22;

    while (bt >= 0)
    {

        if (f & (1L << bt))
            l += 1L << (exp - (22 - bt) - 1);

        bt--;
    }

    return l;
}

#ifdef TEST_HARNESS

        {
            fprintf(stderr, "\aErr at %f!\n", f);
            exit(1);
        }
    }

    return 0;
}

#endif
