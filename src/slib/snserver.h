// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef APIENTRY
#include <os2def.h>
#endif

#ifndef CALLBACK
#ifdef __FLAT__
#define CALLBACK pascal __far16
#else
#include "os2fubar.h"
#endif
#endif

#if !defined(_QC)
#pragma comment(lib, "snserver.lib")
#endif

typedef SEL HSNOOP;
typedef PSEL PHSNOOP;
typedef int(pascal far *PFNSN)(int flag, char far *str);

USHORT CALLBACK SnoopOpen(PSZ pszPipeName, PHSNOOP phSnoop, PSZ pszAppName, PFNSN NotifyFunc);

USHORT CALLBACK SnoopWrite(HSNOOP hsn, PSZ pszMessage);

USHORT CALLBACK SnoopClose(HSNOOP hsn);
