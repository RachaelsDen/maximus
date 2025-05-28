// SPDX-License-Identifier: GPL-2.0-or-later


#include "tui.h"
#include <stdarg.h>

        else
#endif

byte col(byte c)
{
    if (!Vid_MonoCard)
        return c;


    if (((c >> 4) & 0x07) != 7 || (c & 0x08))
        c &= 0x8f;

    if ((c & 0x07) != 7 && (c & 0x07) != 0)
    {
        c &= ~0x07;
        c |= 0x07;
    }

    if (c == 0x77)
        c = 0x0f;

    return c;
}
