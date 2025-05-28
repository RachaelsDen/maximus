// SPDX-License-Identifier: GPL-2.0-or-later



#define ID_LISTBOX 512

typedef struct
{
    char curattr;
    int last_cc;
    char str2[25];
    char state;
    char newattr;

    word s2, s3;

    byte uch;
    byte save_cx;

    word x, y, z, a;
} AVP;



#define LB_COL1 8
#define LB_COL2 20
#define LB_COL3 32
#define LB_COL4 8

#define LB_SUM (LB_COL1 + LB_COL2 + LB_COL3 + LB_COL4 + 3)

