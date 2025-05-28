// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __FFIND_H_DEFINED
#define __FFIND_H_DEFINED

#include "compiler.h"
#include "prog.h"
#include "stamp.h"
#include "typedefs.h"
#ifdef UNIX
#include <glob.h>
#endif

cpp_begin()

    struct _ffind;
typedef struct _ffind FFIND;

#if defined(__MSDOS__)


struct _ffind
{
    word usAttr;
    SCOMBO scCdate;
    SCOMBO scAdate;
    SCOMBO scWdate;
    dword ulSize;

#if defined(__MSDOS__)

    char szName[13];
    struct _dosdta __dta;

#elif defined(NT)

    char szName[PATHLEN];
    HANDLE hdir;
    unsigned long hdir;
#else
int _fast FindNext(FFIND *ff);

