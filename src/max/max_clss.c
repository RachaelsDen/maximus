// SPDX-License-Identifier: GPL-2.0-or-later



#include "max_oldu.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <malloc.h>
#include <share.h>
#include <stdlib.h>
#include <string.h>


int ClassReadFile(char *pszName)
{
    int fd, sz, rc;
    CLSHDR chdr;

    rc = FALSE;
    fd = shopen(pszName, O_RDONLY | O_BINARY | O_NOINHERIT);

    if (fd != -1)
    {

        if (read(fd, &chdr, sizeof chdr) == sizeof chdr && chdr.ulclhid == CLS_ID &&
            chdr.ussize != 0 && chdr.usclfirst != 0 && chdr.usn != 0)
        {

            sz = sizeof(*pclh) + (chdr.usn * chdr.ussize) + chdr.usstr;
            pclh = malloc(sz);

            if (pclh != NULL)
            {


                if (read(fd, pclh->pcInfo, sz) == sz)
                    rc = TRUE;
                else
                {
                    free(pclh);
                    pclh = NULL;
                }
            }
        }

        close(fd);
    }
    return rc;
}


void ClassDispose()
{
    if (pclh)
        free(pclh);
}


CLSREC *ClassRec(int idx)
{
}

int ClassKeyIndex(word key)
{
    int i;

    for (i = 0; i < pclh->usn; ++i)
    {
        CLSREC *pc = ClassRec(i);
        if (pc->usKey == key)
            return i;
    }

    return -1;
}


word ClassKeyLevel(word key)
{
    int i = ClassKeyIndex(key);
    return (i == -1) ? (word)-1 : ClassRec(i)->usLevel;
}


int ClassAbbrevIndex(char *pszAbbrev)
{
    int i, n;

    if (isdigit(*pszAbbrev) || *pszAbbrev == '-')
    {
        word usn = (word)atol(pszAbbrev);


word ClassAbbrevLevel(char *pszAbbrev)
{
    int idx = ClassAbbrevIndex(pszAbbrev);

    return (idx == -1) ? (word)-1 : ClassRec(idx)->usLevel;
}


int ClassLevelIndex(word usLevel)
{
    int i, j = -1;

    for (i = 0; i < pclh->usn; i++)
    {
        CLSREC *pc = ClassRec(i);
        if (pc->usLevel > usLevel)
            break;
        j = i;
        if (pc->usLevel == usLevel)
            break;
    }

    return j;
}


dword ClassGetInfo(int idx, int itype)
{
    dword rc;
    if (itype == CIT_NUMCLASSES)
        rc = pclh->usn;
    else
    {
        CLSREC *pcr = ClassRec(idx);

        switch (itype)
        {
        case CIT_DAY_TIME:
            rc = pcr->usTimeDay;
            break;
        case CIT_CALL_TIME:
            rc = pcr->usTimeCall;
            break;
        case CIT_DL_LIMIT:
            rc = pcr->ulFileLimit;
            break;
        case CIT_RATIO:
            rc = pcr->usFileRatio;
            break;
        case CIT_MIN_BAUD:
            rc = (100L * pcr->usMinBaud);
            break;
        case CIT_MIN_XFER_BAUD:
            rc = (100L * pcr->usFileBaud);
            break;
        case CIT_MAX_CALLS:
            rc = pcr->usCallsDay;
            break;
        case CIT_FREE_RATIO:
            rc = pcr->usFreeRatio;
            break;
        case CIT_UPLOAD_REWARD:
            rc = pcr->usUploadReward;
            break;
        case CIT_ACCESSFLAGS:
            rc = pcr->ulAccFlags;
            break;
        case CIT_MAILFLAGS:
            rc = pcr->ulMailFlags;
            break;
        case CIT_USERFLAGS:
            rc = pcr->ulUsrFlags;
            break;
        case CIT_LEVEL:
            rc = pcr->usLevel;
            break;
        case CIT_KEY:
            rc = pcr->usKey;
            break;
        case CIT_INDEX:
            rc = idx;
            break;
        case CIT_OLDPRIV:
            rc = pcr->usOldPriv;
            break;
        default:

static void SZKeyMask(char *pszKeys, dword *maskon, dword *maskoff)
{
    char *p;

    *maskon = 0L;
    *maskoff = 0L;


        while (*++p)
        {
            unsigned char ch;
            dword *maskptr = maskon;


    equals = strchr(acstest, '=');

    if (equals)
    {


    if (*acstest == '>')
    {
        privop = privGT;
        if (*(++acstest) == '=')
        {
            privop = privGE;
            ++acstest;
        }
    }
    else if (*acstest == '<')
    {
        privop = privLT;
        if (*(++acstest) == '=')
        {
            privop = privLE;
            ++acstest;
        }
        else if (*acstest == '>')
        {
            privop = privNE;
            ++acstest;
        }
    }
    else if (*acstest == '!')
    {
        privop = privNE;
            ++acstest;
    }

    if (*acstest == '@')
    {
    {
        word compareto_priv = use_real_priv ? realpriv() : usr.priv;
        word compare_priv = ClassLevel(acstest);

        switch (privop)
        {
        default:
        case privGE:
            rc = (compareto_priv >= compare_priv);
            break;
        case privLE:
            rc = (compareto_priv <= compare_priv);
            break;
        case privGT:
            rc = (compareto_priv > compare_priv);
            break;
        case privLT:
            rc = (compareto_priv < compare_priv);
            break;
        case privEQ:
            rc = (compareto_priv == compare_priv);
            break;
        case privNE:
            rc = (compareto_priv != compare_priv);
            break;
        }
    }


int PrivOK(char *acstest, unsigned use_real_priv)
{
    char *acsdup;
    char *next;
    char *s;
    int rel = 0;

    int rc = TRUE;


    for (next = acsdup; next;)
    {
        char *p;

        s = next;

            *p = 0;
            next = p + 1;
        }

        if (!_PrivOK(s, use_real_priv))
        {
                break;
        }
        else
        {
                break;
        }
    }

    return rc;
}

void ClassFlag(int idx, int which, dword fSet, dword fReset)
{
    if (ValidClassIndex(idx))
    {
        CLSREC *pcr = ClassRec(idx);
        switch (which)
        {
        case CIT_ACCESSFLAGS:
            pcr->ulAccFlags |= fSet;
            pcr->ulAccFlags &= ~fReset;
            break;
        case CIT_MAILFLAGS:
            pcr->ulMailFlags |= fSet;
            pcr->ulMailFlags &= ~fReset;
            break;
        case CIT_USERFLAGS:
            pcr->ulUsrFlags |= fSet;
            pcr->ulUsrFlags &= ~fReset;
            break;
        }
    }
}

char *privstr(word priv, char *buf)
{
    int ucls;
    char *prv = buf;

    ucls = ClassLevelIndex(priv);
    if (ClassGetInfo(ucls, CIT_LEVEL) == priv)
        prv = ClassAbbrev(ucls);
    else
        sprintf(buf, "%u", priv);

    return prv;
}


            return pc->usLevel;

