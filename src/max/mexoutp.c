// SPDX-License-Identifier: GPL-2.0-or-later


#include "mexall.h"
#include "modem.h"

#ifdef MEX


word EXPENTRY intrin_printunsignedlong(void)
{
    MA ma;

    MexArgBegin(&ma);

    Printf("%lu", (unsigned long)(dword)MexArgGetDword(&ma));

    if (pmisThis->pmid->instant_video)
        vbuf_flush();

    return MexArgEnd(&ma);
}

word EXPENTRY intrin_printlong(void)
{
    MA ma;

    MexArgBegin(&ma);

    Printf("%ld", (long)(sdword)MexArgGetDword(&ma));

    if (pmisThis->pmid->instant_video)
        vbuf_flush();

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_printchar(void)
{
    MA ma;

    MexArgBegin(&ma);

    Printf("%c", MexArgGetByte(&ma));

    if (pmisThis->pmid->instant_video)
        vbuf_flush();

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_set_output(void)
{
    MA ma;
    word flag = 0;

    MexArgBegin(&ma);


    flag = MexArgGetWord(&ma);
    no_local_output = (flag & 1) ? 1 : 0;
    no_remote_output = (flag & 2) ? 1 : 0;

    return MexArgEnd(&ma);
}

