// SPDX-License-Identifier: GPL-2.0-or-later


#include "max_msg.h"
#include "mexall.h"

#ifdef MEX


void EXPENTRY intrin_hook_before(void)
{

    pmisThis->set_last_msg = last_msg;
    strcpy(pmisThis->szSetArea, usr.msg);
    MexImportString(linebuf, pmisThis->vmaLinebuf, BUFLEN);
}


void EXPENTRY intrin_hook_after(void)
{

void MexImportString(char *szDest, VMADDR vma, int iMax)
{
    IADDR ia;
    IADDR *pia;


    MexStringCopy(szDest, pia, iMax);
}


void MexExportString(VMADDR vma, char *szSrc)
{
    IADDR ia;


    MexStoreStringAt(vma, szSrc);
}


void MexStringCopy(char *dest, IADDR *piSrc, int max_len)
{
    char *szSrc;
    int len;

    szSrc = MexFetch(FormString, piSrc);
    len = (int)*(word *)szSrc;
    szSrc += sizeof(word);

    len = min(len, max_len - 1);

    strncpy(dest, szSrc, len);
    dest[len] = 0;
}

