// SPDX-License-Identifier: GPL-2.0-or-later


#include "max_file.h"
#include "mexall.h"

#ifdef MEX


    regs_2[0] = FALSE;

    if (szFile)
    {
        long lSize = fsize(szFile);
        upper_fn(szFile);

        if (lSize != -1L && AddFileEntry(szFile, wFlags | FFLAG_OK | FFLAG_TAG, lSize) != -1)
        {
            regs_2[0] = TRUE;
        }

        free(szFile);
    }

    return MexArgEnd(&ma);
}


word EXPENTRY intrin_tag_queue_size(void)
{
    MA ma;

    MexArgBegin(&ma);

    regs_2[0] = FileEntries();

    return MexArgEnd(&ma);
}


    fn = MexArgGetWord(&ma);
    pw = (word *)MexArgGetRef(&ma);
    MexArgGetRefString(&ma, &ia, &wLen);

    if (GetFileEntry(fn, &fent))
    {
        str = fent.szName;
        *pw = fent.fFlags;
        regs_2[0] = TRUE;
    }
    else
    {
        str = blank_str;
        *pw = 0;
        regs_2[0] = FALSE;
    }

    MexKillString(&ia);
    MexStoreByteStringAt(MexIaddrToVM(&ia), str, strlen(str));

    return MexArgEnd(&ma);
}

