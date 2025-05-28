// SPDX-License-Identifier: GPL-2.0-or-later


#include "max_file.h"
#include "mexall.h"

#ifdef MEX

            AreaFileFindChange(pmisThis->hafFile, NULL, flags);
        }
    }
    if (psz)
        free(psz);
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_fileareafindnext(void)
{
    MA ma;
    struct mex_farea *pfa;

    MexArgBegin(&ma);
    pfa = MexArgGetRef(&ma);
    if (!pmisThis->hafFile)
        regs_2[0] = FALSE;
    else
        regs_2[0] = findfilearea(pfa, TRUE);
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_fileareafindprev(void)
{
    MA ma;
    struct mex_farea *pfa;

    MexArgBegin(&ma);
    pfa = MexArgGetRef(&ma);
    if (!pmisThis->hafFile)
        regs_2[0] = FALSE;
    else
        regs_2[0] = findfilearea(pfa, FALSE);
    return MexArgEnd(&ma);
}

word EXPENTRY intrin_fileareafindclose(void)
{
    if (pmisThis->hafFile)
    {
        AreaFileFindClose(pmisThis->hafFile);
        pmisThis->hafFile = 0;
    }
    return regs_2[0] = 0;
}

word EXPENTRY intrin_file_area(void)
{
    File_Area();
    if (fah.heap)
    {
        fileareaexport(MexDSEG(pmisThis->vmaFarea), &fah);
        SetAreaName(usr.files, FAS(fah, name));
        MexKillStructString(mex_usr, pmisThis->pmu, files);
        StoreString(MexPtrToVM(pmisThis->pmu), struct mex_usr, files, FAS(fah, name));
    }
    return 0;
}

word EXPENTRY intrin_fileareaselect(void)
{
    MA ma;
    FAH myfah;
    char *psz;
    BARINFO bi;

    memset(&myfah, 0, sizeof myfah);

    if (pmisThis->hafFile)
    {
        AreaFileFindClose(pmisThis->hafFile);
        pmisThis->hafFile = 0;
    }
    MexArgBegin(&ma);
    psz = MexArgGetString(&ma, FALSE);
    regs_2[0] = FALSE;
    if (psz && *psz)
    {
        char temp[MAX_ALEN];

        strcpy(temp, psz);
        pmisThis->hafFile = AreaFileFindOpen(haf, temp, 0);
        if (pmisThis->hafFile == NULL)
            regs_2[0] = FALSE;
        else
        {
            int rc = AreaFileFindNext(pmisThis->hafFile, &myfah, FALSE);
            if (rc != 0)
            {
                char *p;

                strcpy(temp, usr.files);
                p = strrchr(temp, '.');
                if (p)
                {
                    strcpy(p + 1, psz);
                    AreaFileFindReset(pmisThis->hafFile);
                    AreaFileFindChange(pmisThis->hafFile, temp, 0);
                    rc = AreaFileFindNext(pmisThis->hafFile, &myfah, FALSE);
                }
            }
            if (rc == 0 && !(myfah.fa.attribs & FA_HIDDN) &&
                ValidFileArea(NULL, &myfah, VA_VAL | VA_PWD | VA_EXTONLY, &bi) &&
                PopPushFileAreaSt(&myfah, &bi))
            {
                SetAreaName(usr.files, FAS(myfah, name));
                fileareaexport(MexDSEG(pmisThis->vmaFarea), &myfah);
                strcpy(usr.files, FAS(myfah, name));
                regs_2[0] = TRUE;
                MexKillStructString(mex_usr, pmisThis->pmu, files);
                StoreString(MexPtrToVM(pmisThis->pmu), struct mex_usr, files, FAS(myfah, name));
            }
            AreaFileFindClose(pmisThis->hafFile);
            pmisThis->hafFile = 0;
            DisposeFah(&myfah);
        }
    }
    if (psz)
        free(psz);
    return MexArgEnd(&ma);
}

