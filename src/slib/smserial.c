// SPDX-License-Identifier: GPL-2.0-or-later


#include <stdlib.h>
#include <string.h>

#define INCL_VIO
#define INCL_DOS
#define INCL_DOSERRORS

#include "compiler.h"
#include "typedefs.h"
#include <pos2.h>


static void far pascal BbsSemTerminate(USHORT usTermCode)
{
    NW(usTermCode);

    DosSemClear(hssm);
    DosCloseSem(hssm);
    DosExitList(EXLST_EXIT, 0);
}

static void near BbsPuts(char *txt) { VioWrtTTY(txt, strlen(txt), 0); }

static void near BbsSemError(char *sem, int rc)
{
    char temp[5];

    BbsPuts("SYS");

    itoa(rc, temp, 10);
    BbsPuts(temp);

    BbsPuts(": Error in DosOpenSem(\"");
    BbsPuts(sem);
    BbsPuts("\")\r\n");
}

void EXPENTRY BbsSemSerialize(char *pszSemName, char *pszSemEnv)
{
    USHORT rc;
    char *pszOldSemName;


        if (DosScanEnv(pszSemEnv, &pszSemName) != 0)
            pszSemName = pszOldSemName;
    }

    if (!pszSemName)
        pszSemName = "/sem/squish/default";

    gpszSemName = pszSemName;

    if ((rc = DosCreateSem(CSEM_PUBLIC, &hssm, pszSemName)) == 0)
        DosSemRequest(hssm, SEM_INDEFINITE_WAIT);
    else if (rc != ERROR_ALREADY_EXISTS)
        BbsSemError(pszSemName, rc);
    else
    {
        if ((rc = DosOpenSem(&hssm, pszSemName)) != 0)
            BbsSemError(pszSemName, rc);
        else
        {
            BbsPuts("Serializing on semaphore ");
            BbsPuts(pszSemName);
            BbsPuts("\r\n");

            if ((rc = DosSemRequest(hssm, SEM_INDEFINITE_WAIT)) == ERROR_SEM_OWNER_DIED)
                rc = 0;
        }
    }

