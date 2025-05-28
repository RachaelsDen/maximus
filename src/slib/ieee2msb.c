// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"


int _fast ieee_to_msbin(void *source, void *dest)
{
    unsigned int second, first;
#if 0
  unsigned char second_high, second_lo;
#endif
    unsigned short *sourceint = (unsigned short *)source;
    unsigned short *destint = (unsigned short *)dest;

    first = *sourceint++;

    second = *sourceint;

#if 0

  second_high &= 0x7f;


    if (second == 0x7f00)
        return 1;


    second_high=(unsigned char)(second >> 8);
    second_lo=(unsigned char)(second & 0xff);

    second_lo >>= 1;


    *destint++ = first;
    *destint = second;
    return 0;
}
