// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$id";
#pragma on(unreferenced)


#include "alc.h"
#include "ffind.h"
#include "max_file.h"
#include "prog.h"
#include "strbuf.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>

}

int relocnm(char *fold, char *fnew)
{
    int i;
    FENTRY *f = filebuf;

    for (i = 0; i++ < fnames; ++i, ++f)
    {
        if (fold == f->szName)
            f->szName = fnew;
        else if (fold == f->szDesc)
            f->szDesc = fnew;
        else
            continue;
        return TRUE;
    }
    return FALSE;
}

static char *allocstr(char *s)
{
    char *p = sb_alloc(filestr, s);

    if (p == NULL)
    {
        strbuf *b = sb_realloc(filestr, sbsize(filestr) + 1024, relocnm);
        if (b == NULL || (p = sb_alloc(b, s)) == NULL)
        {
#ifdef CAN_DO_EXPAND
            canexpand = 0;
#endif
            logit(mem_none);
            return NULL;
        }
        filestr = b;
    }
    return p;
}

static void freestr(char *s)
{
    if (s)
        sb_free(filestr, s);
}

void Free_Filenames_Buffer(word usLeave)
{

    if (usLeave == 0)
    {

        word n;
        FENTRY *f = filebuf;

        for (n = usLeave; n < fnames; n++, f++)
        {
            freestr(f->szName);
            freestr(f->szDesc);
            memset(f, 0, sizeof(FENTRY));
        }

        f = filebuf;
        for (n = 0; n < fnames && f->szName; n++, ++f)
            ;
        fnames = n;
    }
}

word FileEntries(void) { return fnames; }

int RemoveFileEntry(word n)
{
    word k;

    if (n < fnames)
    {
        FENTRY *f = filebuf + n;

#ifdef CAN_DO_EXPAND
        if (canexpand)
        {
            word newmax = maxnames + 16;
            FENTRY *newfilebuf = realloc(filebuf, newmax * sizeof(FENTRY));
            if (!newfilebuf)
                canexpand = 0;
            else
            {
                filebuf = newfilebuf;
                memset(filebuf + maxnames, 0, 16 * sizeof(FENTRY));
                maxnames = newmax;
            }
        }
#endif
    }
    if (CanAddFileEntry())
    {
        FENTRY *f = filebuf + fnames;

        if ((f->szName = allocstr(fname)) != NULL)
        {
            f->fFlags = flags;
            f->szDesc = NULL;
            f->ulSize = (size >= 0L) ? size : fsize(fname);
            if (f->ulSize == (unsigned long)-1L)
                f->fFlags |= FFLAG_NOENT;
            return fnames++;
        }
    }
    return -1;
}

int GetFileEntry(word n, FENTRY *fent)
{
    if (n < fnames)
    {
        *fent = filebuf[n];
        return TRUE;
    }
    return FALSE;
}

int UpdFileEntry(word n, FENTRY *fent)
{
    int rc = TRUE;

    if (n < fnames)
    {
        FENTRY *f = filebuf + n;

        if (fent->szName != f->szName && strcmp(fent->szName, f->szName) != 0)
        {
            char *p = allocstr(fent->szName);

            if (!p)
                return FALSE;
            freestr(f->szName);
            f->szName = p;
        }

        if (fent->szDesc != f->szDesc &&
            !(fent->szDesc && f->szDesc && strcmp(fent->szDesc, f->szDesc) != 0))
        {
            freestr(f->szDesc);
            if (fent->szDesc)
                f->szDesc = allocstr(fent->szDesc);
            else
                f->szDesc = NULL;
        }
        f->ulSize = fent->ulSize;
        f->fFlags = fent->fFlags;
    }
    else if (AddFileEntry(fent->szName, fent->fFlags, fent->ulSize) != -1)
    {
        if (fent->szDesc)
            filebuf[fnames - 1].szDesc = allocstr(fent->szDesc);
    }
    else
        rc = FALSE;

    return rc;
}
