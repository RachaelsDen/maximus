// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <ctype.h>
#include <stdio.h>

{

    int digit;

    *bufptr-- = '\0';

    do
    {
        digit = number % radix;
        number /= radix;
        *bufptr-- = (char)((digit < 10) ? (digit + '0') : (digit + 'A' - 10));
    } while (number);

    return (++bufptr);
}
