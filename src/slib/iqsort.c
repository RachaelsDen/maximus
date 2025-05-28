// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"


static void cswap(char *, char *, unsigned);

#define SWAP(a, b) (cswap((a), (b), width))



        if ((unsigned)(limit - base) > thresh)
            for (;;)
                    i += width;
                while ((*comp)(i, base) < 0);
                    break;
            if (j - base > limit - i)
            }
            else
            }
            for (j = base, i = j + width; i < limit; j = i, i += width)
                for (; (*comp)(j, j + width) > 0; j -= width)
                {
                    SWAP(j, j + width);
                    if (j == base)
                        break;
                }
            if (sp != stack)
                base = sp[0];
                limit = sp[1];
            }
{
    char tmp;

    do
    {
        tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    } while (--k);
}
