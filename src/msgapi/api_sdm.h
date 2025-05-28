// SPDX-License-Identifier: GPL-2.0-or-later



struct _msgh
{
    HAREA ha;

    sdword clen;
    byte *ctrl;
    dword msg_len;
    dword msgtxt_start;
    word zplen;
    int fd;
};

    unsigned msgnum_len;

    dword hwm;
    word hwm_chgd;

    unsigned msgs_open;
};

