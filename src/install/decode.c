// SPDX-License-Identifier: GPL-2.0-or-later


#include "ar.h"

{
    static uint i;
    uint r, c;

    r = 0;
    while (--j >= 0)
    {
        buffer[r] = buffer[i];
        i = (i + 1) & (DICSIZ - 1);
        if (++r == count)
            return;
    }
    for (;;)
    {
        c = decode_c();
        if (c <= UCHAR_MAX)
        {
            buffer[r] = (uchar)c;
            if (++r == count)
                return;
        }
        else
        {
            j = c - (UCHAR_MAX + 1 - THRESHOLD);
            i = (r - decode_p() - 1) & (DICSIZ - 1);
            while (--j >= 0)
            {
                buffer[r] = buffer[i];
                i = (i + 1) & (DICSIZ - 1);
                if (++r == count)
                    return;
            }
        }
    }
}
