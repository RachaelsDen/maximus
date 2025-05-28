// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"


    first = *sourceint++;
    second = *sourceint;

        second_hi = second_lo = 0;
        first = 0;
    }
    else
    {
        second_hi += 0xfe;
        second_lo <<= 1;
    }


    *destint++ = first;
    *destint = second;

    return 0;
}
