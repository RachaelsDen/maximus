// SPDX-License-Identifier: GPL-2.0-or-later



#include "max.h"
#include "prog.h"

#if defined(THIS_IS_NOW_DEFUNCT)

struct __priv _stdc _privs[] = {
    {"Twit", TWIT},     {"Disgrace", DISGRACE},   {"Limited", LIMITED}, {"Normal", NORMAL},
    {"Worthy", WORTHY}, {"Privil", PRIVIL},       {"Favored", FAVORED}, {"Extra", EXTRA},
    {"Clerk", CLERK},   {"AsstSysOp", ASSTSYSOP}, {"SysOp", SYSOP},     {"Hidden", HIDDEN},
    {NULL, -999}};

char *_fast Priv_Level(int priv)
{
    int x;

    for (x = 0; x < _PRIVS_NUM; x++)
        if (priv == _privs[x].priv)
            return _privs[x].name;

    return "";
}

#endif
