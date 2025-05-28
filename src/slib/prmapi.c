// SPDX-License-Identifier: GPL-2.0-or-later


#include "prmapi.h"
#include "max.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stddef.h>
#include <string.h>

static void near PrmAbort(char *pszFile, int iReason, int iErrorlevel)
{
    printf("Error!  The Maximus parameter file, '%s', cannot be accessed\n"
           "because %s.\n",
           pszFile,
           iReason == 0   ? "there is not enough memory"
           : iReason == 1 ? "the file cannot be opened"
           : iReason == 2 ? "the file cannot be read"
           : iReason == 3 ? "the file is of an invalid type"
                          : "of an unknown error.");

    exit(iErrorlevel);
}

HPRM PrmFileOpen(char *pszFile, int iAbortOnError)
{
    char pszName[PATHLEN];

    if ((hp = malloc(sizeof *hp)) == NULL)
    {
        if (iAbortOnError)
            PrmAbort(pszFile, 0, iAbortOnError);
        else
            return NULL;
    }

    if ((fd = shopen(pszFile, O_RDONLY | O_BINARY)) == -1)
    {

    lSize = lseek(fd, 0L, SEEK_END);
    stHeap = (size_t)(lSize - (long)sizeof(struct m_pointers));
    lseek(fd, (long)sizeof(struct m_pointers), SEEK_SET);

    if ((hp->pszHeap = malloc(stHeap)) == NULL)
    {
        if (iAbortOnError)
            PrmAbort(pszFile, 0, iAbortOnError);
        else
        {
            close(fd);
            free(hp);
            return NULL;
        }
    }


char *PrmRelativeString(HPRM hp, char *pszIn, char *pszOut)
{
    char *pszSysPath = PrmFileString(hp, sys_path);


    if (pszIn[1] != ':' && pszIn[0] != '\\' && pszIn[0] != '/')
    {
        strcpy(pszOut, pszSysPath);
        strcat(pszOut, pszIn);
    }
    else
    {
        strcpy(pszOut, pszIn);
    }

    return pszOut;
}
