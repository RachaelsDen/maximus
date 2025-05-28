// SPDX-License-Identifier: GPL-2.0-or-later


#include "areaapi.h"
#include "bfile.h"
#include "max.h"
#include "prog.h"
#include "uni.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


HAF _fast AreaFileOpen(char *name, int msg_area)
{
    char fname[PATHLEN];
    HAF haf = malloc(sizeof *haf);
    dword dwId;

    if (!haf)
        return NULL;


    strcpy(fname, name);
    strcat(fname, ".dat");

    if ((haf->dat = Bopen(fname, BO_RDONLY | BO_BINARY, BSH_DENYNO, sizeof(MAH) * 4)) == NULL)
    {
        free(haf);
        return NULL;
    }


    if (Bread(haf->dat, (char *)&dwId, sizeof dwId) != sizeof dwId ||
        (msg_area && dwId != MAREA_ID) || (!msg_area && dwId != FAREA_ID))
    {
        Bclose(haf->dat);
        free(haf);
        return NULL;
    }


    haf->idx = NULL;

    return haf;
}


HAFF _fast AreaFileFindOpen(HAF haf, char *name, int flags)
{
    HAFF haff;

    if ((haff = malloc(sizeof *haff)) == NULL)
        return NULL;

    haff->haf = haf;
    haff->name = name;
    haff->ofs = ADATA_START;
    haff->wrapped = FALSE;
    haff->start_ofs = ADATA_START;
    haff->flags = flags;
    return haff;
}


static int near _ReadArea(HAFF haff, int wrap)
{
    haff->start_ofs = haff->ofs;
    Bseek(haff->haf->dat, haff->ofs, BSEEK_SET);

    if (haff->haf->msg_area)
    {
        if (Bread(haff->haf->dat, (char *)&haff->ah.mah.ma, sizeof(MAREA)) != sizeof(MAREA))
        {
            if (!wrap || haff->wrapped)
                return -1;

            haff->wrapped = TRUE;

            Bseek(haff->haf->dat, haff->ofs = haff->start_ofs = ADATA_START, BSEEK_SET);

            if (Bread(haff->haf->dat, (char *)&haff->ah.mah.ma, sizeof(MAREA)) != sizeof(MAREA))
                return -1;
        }


        haff->ofs += (haff->ah.mah.ma.cbArea > 0) ? haff->ah.mah.ma.cbArea : sizeof(MAREA);

    {
        if (Bread(haff->haf->dat, (char *)&haff->ah.fah.fa, sizeof(FAREA)) != sizeof(FAREA))
        {
            if (!wrap || haff->wrapped)
                return -1;

            haff->wrapped = TRUE;

            Bseek(haff->haf->dat, haff->ofs = haff->start_ofs = ADATA_START, BSEEK_SET);

            if (Bread(haff->haf->dat, (char *)&haff->ah.fah.fa, sizeof(FAREA)) != sizeof(FAREA))
                return -1;
        }


        haff->ofs += (haff->ah.fah.fa.cbArea > 0) ? haff->ah.fah.fa.cbArea : sizeof(FAREA);


static int near _ReadOverrides(HAFF haff)
{
    unsigned size;
    OVERRIDE *pov;


    if (!size)
        return 0;


    if (Bread(haff->haf->dat, (char *)pov, size) != (signed)size)
        return -1;


    if (haff->haf->msg_area)
        haff->ah.mah.pov = pov;
    else
        haff->ah.fah.pov = pov;

    return 0;
}


    if ((heap = malloc(haff->heap_size + PATHLEN * 2)) == NULL)
        return -1;

    if (haff->heap_size)
        if (Bread(haff->haf->dat, (char *)heap, haff->heap_size) != (signed)haff->heap_size)
            return -1;

    haff->ofs += haff->heap_size;

    if (haff->haf->msg_area)
        haff->ah.mah.heap = heap;
    else
        haff->ah.fah.heap = heap;

    return 0;
}


static int near _AreaMatch(HAFF haff)
{
    char *name = haff->haf->msg_area ? MAS(haff->ah.mah, name) : FAS(haff->ah.fah, name);

    if (haff->haf->msg_area && (haff->ah.mah.ma.attribs & (MA_DIVBEGIN | MA_DIVEND)) &&
        (haff->flags & AFFO_DIV) == 0)
        return FALSE;

    if (!haff->haf->msg_area && (haff->ah.fah.fa.attribs & (FA_DIVBEGIN | FA_DIVEND)) &&
        (haff->flags & AFFO_DIV) == 0)
        return FALSE;


    return eqstri(haff->name, name);
}

static int _fast openIndex(HAF haf)
{
    if (haf->idx == NULL && (haf->idx = Bopen(haf->idxname, BO_RDONLY | BO_BINARY, BSH_DENYNO,
                                              sizeof(struct _mfidx) * MF_BUFFER)) == NULL)
        return FALSE;

    return TRUE;
}


static void near _TryIndexSearch(HAFF haff)
{
    MFIDX mfi;
    dword hash;

    if (!openIndex(haff->haf))
        return;

    hash = SquishHash(haff->name);


        if (mfi.name_hash == hash && strnicmp(mfi.name, haff->name, sizeof(mfi.name) - 1) == 0)
        {
            haff->ofs = mfi.ofs;
            break;
        }
    }
}


    if (forward && haff->name && haff->ofs == ADATA_START)
        _TryIndexSearch(haff);

    do
    {

                if (!wrap || haff->wrapped)
                    return -1;

                haff->wrapped = TRUE;
            }


            if (haff->haf->msg_area)
                haff->ofs = haff->start_ofs - haff->ah.mah.ma.cbPrior;
            else
                haff->ofs = haff->start_ofs - haff->ah.fah.fa.cbPrior;
        }

        if (haff->haf->msg_area)
            DisposeMah(&haff->ah.mah);
        else
            DisposeFah(&haff->ah.fah);

        if (_ReadArea(haff, wrap) != 0 || _ReadOverrides(haff) != 0 || _ReadHeap(haff) != 0)
        {
            return -1;
        }
    } while (!_AreaMatch(haff));


int _fast AreaFileFindPrior(HAFF haff, void *v, unsigned wrap)
{
    return _AreaFileFind(haff, v, wrap, FALSE);
}

int _fast AreaFileFindNext(HAFF haff, void *v, unsigned wrap)
{
    return _AreaFileFind(haff, v, wrap, TRUE);
}


int _fast AreaFileClose(HAF haf)
{
    if (haf)
    {
        if (haf->idx != NULL)
            Bclose(haf->idx);

        if (haf->dat != NULL)
            Bclose(haf->dat);

        if (haf->idxname)
            free(haf->idxname);

        haf->idxname = NULL;
        haf->idx = NULL;
        haf->dat = NULL;

        free(haf);
    }

    return 0;
}


void _fast DisposeFah(FAH *pfah)
{
    if (pfah->heap)
        free(pfah->heap);

    if (pfah->pov)
        free(pfah->pov);

    memset(pfah, 0, sizeof *pfah);
}

#ifdef TEST_HARNESS
main()
{
    MAH mah = {0};
    HAF haf = AreaFileOpen("marea.dat", "marea.idx", TRUE);
    HAFF haff;

    if (!haf)
    {
        printf("Can't open marea.dat\n");
        return 1;
    }

    if ((haff = AreaFileFindOpen(haf, NULL, 0)) == NULL)
    {
        printf("Can't search area file!\n");
        return 1;
    }

    while (AreaFileFindNext(haff, &mah, FALSE) == 0)
        printf("Found area %s (%s)\n", MAS(mah, name), MAS(mah, descript));

    AreaFileFindClose(haff);

    printf("---\n");

    if ((haff = AreaFileFindOpen(haf, "muf", 0)) == NULL)
    {
        printf("Can't search area file 2!\n");
        return 1;
    }

    if (AreaFileFindNext(haff, &mah, FALSE) != 0)
    {
        printf("can't find muf 2!\n");
        return 1;
    }

    printf("Found area %s (%s)\n", MAS(mah, name), MAS(mah, descript));

    AreaFileFindChange(haff, NULL, 0);

    while (AreaFileFindNext(haff, &mah, TRUE) == 0)
        printf("Found area %s (%s)\n", MAS(mah, name), MAS(mah, descript));

    AreaFileFindClose(haff);

    printf("---\n");

    if ((haff = AreaFileFindOpen(haf, "muf", 0)) == NULL)
    {
        printf("Can't search area file 2!\n");
        return 1;
    }

    if (AreaFileFindNext(haff, &mah, FALSE) != 0)
    {
        printf("can't find muf 2!\n");
        return 1;
    }

    printf("Found area %s (%s)\n", MAS(mah, name), MAS(mah, descript));

    AreaFileFindChange(haff, NULL, 0);

    while (AreaFileFindPrior(haff, &mah, TRUE) == 0)
        printf("Found area %s (%s)\n", MAS(mah, name), MAS(mah, descript));

    AreaFileFindClose(haff);
    AreaFileClose(haf);

    return 0;
}
#endif

int _fast CopyMsgArea(PMAH to, PMAH from)
{
    DisposeMah(to);

    if (!from->heap)
        return TRUE;

    *to = *from;

    if ((to->heap = malloc(from->ma.cbHeap + PATHLEN * 2)) == NULL)
        return FALSE;

    to->pov = NULL;

    if (from->ma.num_override &&
        (to->pov = malloc(from->ma.num_override * sizeof(OVERRIDE))) == NULL)
    {
        free(to->heap);
        to->heap = NULL;
        return FALSE;
    }


    memmove(to->heap, from->heap, from->fa.cbHeap + PATHLEN * 2);

    if (to->pov)
        memmove(to->pov, from->pov, from->fa.num_override * sizeof(OVERRIDE));

    return TRUE;
}
