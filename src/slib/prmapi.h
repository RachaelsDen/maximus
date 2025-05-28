// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef PRMAPI_H_INCLUDED__
#define PRMAPI_H_INCLUDED__

typedef struct _hprm
{
    struct m_pointers mp;
    char *pszHeap;
} * HPRM;

HPRM PrmFileOpen(char *pszFile, int iAbortOnError);
char *PrmRelativeString(HPRM hp, char *pszIn, char *pszOut);
void PrmFileClose(HPRM hp);

#define PrmFileString(hp, field) ((hp)->pszHeap + (hp)->mp.field)
#define PrmFileValue(hp, field) ((hp)->mp.field)

