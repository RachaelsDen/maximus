// SPDX-License-Identifier: GPL-2.0-or-later


#include "mexall.h"

#ifdef MEX


    where.indirect = FALSE;
    MexKillString(&where);

    return sizeof(IADDR);
}


    if (pad > 32768u)
        pad = 0;


        where = MexStoreHeapByteString(buf, pad);


    MexKillString(&arg);

    return MexArgEnd(&ma);
}

word EXPENTRY intrin_strpad(void) { return strpadsub(FALSE); }

word EXPENTRY intrin_strpadlf(void) { return strpadsub(TRUE); }


word EXPENTRY intrin_substr(void)
{
    char szMsg[PATHLEN];
    MA ma;
    IADDR where;
    char *str;
    int pos, len;
    word wLen;

    MexArgBegin(&ma);

    str = MexArgGetNonRefString(&ma, &where, &wLen);
    pos = MexArgGetWord(&ma);
    len = MexArgGetWord(&ma);


        if (len < 0)
            len = 0;

        if (pos > wLen)
            pos = wLen + 1;
        else if (pos < 1)
            pos = 1;

        if (pos + len > wLen + 1)
            len = wLen + 1 - pos;

        MexReturnStringBytes(str + (pos - 1), len);
    }

    MexKillString(&where);

    return MexArgEnd(&ma);
}

word EXPENTRY intrin_strtok(void)
{
    MA ma;
    char *psz, *tok;
    word *ppos, pos, len;

    static char blank[] = "";

    MexArgBegin(&ma);

            pos = pos - 1;

        }
    }


    MexReturnStringBytes(psz + pos, len);

    if (psz && psz != blank)
        free(psz);

    return MexArgEnd(&ma);
}

static word near struprlwr(int upper)
{
    MA ma;
    char *psz;

    MexArgBegin(&ma);
    psz = MexArgGetString(&ma, FALSE);
    if (!psz)
        MexReturnStringBytes("", 0);
    else
    {
        MexReturnString(upper ? strupr(psz) : strlwr(psz));
        free(psz);
    }

    return MexArgEnd(&ma);
}

word EXPENTRY intrin_strupper(void) { return struprlwr(TRUE); }

word EXPENTRY intrin_strlower(void) { return struprlwr(FALSE); }

word EXPENTRY intrin_trim(void)
{
    MA ma;
    char *psz, *tok;

    MexArgBegin(&ma);


        while (l && strchr(tok, newstart[l - 1]))
            l--;

        MexReturnStringBytes(newstart, l);
    }

    if (psz)
        free(psz);

    if (tok)
        free(tok);

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_uitostr(void)
{
    MA ma;
    char buf[10];
    word i;

    MexArgBegin(&ma);

    i = MexArgGetWord(&ma);
    sprintf(buf, "%u", i);
    MexReturnString(buf);

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_ultostr(void)
{
    MA ma;
    char buf[30];
    long l;

    MexArgBegin(&ma);

    l = MexArgGetDword(&ma);

    sprintf(buf, "%lu", l);
    MexReturnString(buf);

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_strtol(void)
{
    MA ma;
    char *s;

    MexArgBegin(&ma);

    s = MexArgGetString(&ma, FALSE);
    if (!s)
        regs_4[0] = 0;
    else
    {
        regs_4[0] = atol(s);
        free(s);
    }

    return MexArgEnd(&ma);
}

