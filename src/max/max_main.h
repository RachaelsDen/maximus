// SPDX-License-Identifier: GPL-2.0-or-later


#ifdef OS_2

struct _sbinfo
{
    int use_sb;
    HMODULE hmod;
    USHORT usOldPrty;

    void(far _fast *pfnOldNoise)(int, int);

