// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __HNTYPES_H_DEFINED
#define __HNTYPES_H_DEFINED

typedef ushort USHORT;
typedef sshort SHORT;
typedef ulong ULONG;
typedef slong LONG;
typedef ushort BOOL;
typedef uint8 BYTE;

typedef ushort *PUSHORT;
typedef sshort *PSHORT;
typedef ulong *PULONG;
typedef slong *PLONG;
typedef ushort *PBOOL;
typedef uint8 *PBYTE;

typedef dword DWORD;
typedef sword SWORD;
typedef word WORD;
typedef void VOID;

typedef dword *PDWORD;
typedef sword *PSWORD;
typedef word *PWORD;

#ifdef __GNUC__
typedef void *PVOID;
#else
typedef char *PVOID;
#endif

typedef char *LPTSTR;
typedef const char *LPCSTR;
#endif
