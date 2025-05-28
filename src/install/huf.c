// SPDX-License-Identifier: GPL-2.0-or-later


#include "ar.h"
#include <stdlib.h>

#define NP (DICBIT + 1)
#define NTT (CODE_BIT + 3)
#if NTT > NP
#define NPT NTT
#else
#define NPT NP
#endif

ushort left[2 * NC - 1], right[2 * NC - 1];
static uchar *buf, c_len[NC], pt_len[NPT];
static uint bufsiz = 0, blocksize;
static ushort c_freq[2 * NC - 1], c_table[4096], c_code[NC], p_freq[2 * NP - 1], pt_table[256],
    pt_code[NPT], t_freq[2 * NTT - 1];

    }
}

