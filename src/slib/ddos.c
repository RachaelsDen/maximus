// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"

#ifdef __MSDOS__

#ifdef __TURBOC__

    long tim;

    tim = timerset(duration);

    while (!timeup(tim))
        geninterrupt(0xf4);
}

    _AH = 0xe9;
    _AL = priority;
    geninterrupt(0x21);
}

{
    _AH = 0xe0;
    _AL = 0x75;

    geninterrupt(0x21);
}

{
    _AH = 0xe0;
    _AL = 0x74;

    geninterrupt(0x21);
}

{
    _AH = 0xe3;
    _AL = ch;

    geninterrupt(0x21);
}

{
    _AH = 0xe8;
    _AL = 0;
    _DX = 16383;

    geninterrupt(0x21);
}

{
    char temp;

    _AH = 0xe5;

    geninterrupt(0x21);

    temp = _AL;

    switch (temp)
    {
    case 1:
    case 2:
        return temp;

    default:
        return 0;
    }
}


    geninterrupt(0x21);
}

}

