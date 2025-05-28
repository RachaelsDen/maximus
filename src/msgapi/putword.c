// SPDX-License-Identifier: GPL-2.0-or-later

#include "compiler_details.h"
#ifndef PROJECT_LITTLE_ENDIAN

#include "putword.h"


void put_dword(byte *ptr, dword value)
{
    ptr[0] = (byte)(value & 0xff);
    ptr[1] = (byte)((value >> 8) & 0xff);
    ptr[2] = (byte)((value >> 16) & 0xff);
    ptr[3] = (byte)((value >> 24) & 0xff);
}


void put_word(byte *ptr, word value)
{
    ptr[0] = (byte)(value & 0xff);
    ptr[1] = (byte)((value >> 8) & 0xff);
}

#endif
