// SPDX-License-Identifier: GPL-2.0-or-later


#include "mexall.h"

#ifdef MEX

typedef struct _statdata
{
} STATDATA, *PSTATDATA;

static PSTATDATA sdList = NULL;
static PSTATDATA sdStringList = NULL;


    if (!pszName || !size)
        regs_2[0] = -2;
    else
    {

            if ((size_t)size != size || (psd = malloc(sizeof *psd)) == NULL)
                regs_2[0] = -1;
            else
            {
                psd->pszName = strdup(pszName);
                psd->pvData = malloc((size_t)size);
                psd->dwSize = (size_t)size;

                if (!psd->pvData || !psd->pszName)
                {
                    if (psd->pvData)
                        free(psd->pvData);

                    if (psd->pszName)
                        free(psd->pszName);

                    free(psd);

                    regs_2[0] = -1;
                }
                else
                {
                    memset(psd->pvData, 0, (size_t)size);


                    regs_2[0] = 0;
                }
            }
        }
    }

    if (pszName)
        free(pszName);

    return rc;
}


            if (psdLast)
                psdLast->next = psd->next;
            else
                sdList = psd->next;


word EXPENTRY intrin_get_static_data(void)
{
    MA ma;
    PSTATDATA psd;
    char *pszFindName;
    void *pvData;
    word rc;


        for (psd = sdList; psd; psd = psd->next)
            if (strcmp(psd->pszName, pszFindName) == 0)
                break;
    }

    free(pszFindName);


    MexArgBegin(&ma);
    pszFindName = MexArgGetString(&ma, FALSE);
    pvData = MexArgGetRef(&ma);
    rc = MexArgEnd(&ma);

    if (!pszFindName)
    {
        regs_2[0] = -1;
        psd = NULL;
    }
    else
    {

word EXPENTRY intrin_create_static_string(void)
{
    MA ma;
    PSTATDATA psd;
    char *pszName;
    word rc;

    MexArgBegin(&ma);
    pszName = MexArgGetString(&ma, FALSE);
    rc = MexArgEnd(&ma);


        for (psd = sdStringList; psd; psd = psd->next)
            if (strcmp(pszName, psd->pszName) == 0)
                break;

        if (psd)
            regs_2[0] = -3;
        else
        {

                    psd->next = sdStringList;
                    sdStringList = psd;


word EXPENTRY intrin_destroy_static_string(void)
{
    PSTATDATA psd, psdLast;
    MA ma;
    char *pszName;
    word rc;

    MexArgBegin(&ma);
    pszName = MexArgGetString(&ma, FALSE);
    rc = MexArgEnd(&ma);

    if (!pszName)
        regs_2[0] = -1;
    else
    {
        for (psd = sdStringList, psdLast = NULL; psd; psdLast = psd, psd = psd->next)
        {
            if (strcmp(psd->pszName, pszName) == 0)
                break;
        }

        if (!psd)
            regs_2[0] = -1;
        else
        {

            if (psd->pvData)
                free(psd->pvData);

            free(psd->pszName);
            free(psd);

            regs_2[0] = 0;
        }

        free(pszName);
    }

    return rc;
}


    MexArgBegin(&ma);
    pszFindName = MexArgGetString(&ma, FALSE);
    MexArgGetRefString(&ma, &where, &wLen);
    rc = MexArgEnd(&ma);

    if (!pszFindName)
        psd = NULL;
    else
    {

    if (!psd)
        regs_2[0] = -1;
    else
    {

    MexArgBegin(&ma);
    pszFindName = MexArgGetString(&ma, FALSE);
    pvData = MexArgGetNonRefString(&ma, &where, &wLen);
    rc = MexArgEnd(&ma);

    if (!pszFindName)
    {
        regs_2[0] = -1;
        psd = NULL;
    }
    else
    {

            if (psd->pvData)
                free(psd->pvData);

            psd->dwSize = 0;

            if ((psd->pvData = malloc(wLen + 1)) == NULL)
                regs_2[0] = -2;
            else
            {
                memcpy(psd->pvData, pvData, wLen);
                psd->dwSize = wLen;
                regs_2[0] = 0;
            }
        }
    }

    free(pszFindName);
    return rc;
}

