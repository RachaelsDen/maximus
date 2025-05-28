// SPDX-License-Identifier: GPL-2.0-or-later



#if defined(__MSC__)
#pragma comment(lib, "pmtkt.lib")
#elif defined(__WATCOMC__)
#pragma library("pmtkt.lib")
#endif


#define TDF_ERRMEM 0
#define TDF_INVALID 1
#define TDF_NOOPEN 2
#define TDF_NEWOPEN 3
#define TDF_OLDOPEN 4
#define TDF_NOSAVE 5
#define TDF_NEWSAVE 6
#define TDF_OLDSAVE 7
#define OF_REOPEN 0x8000
#define OF_EXIST 0x4000
#define OF_CREATE 0x1000
#define OF_PARSE 0x0100
#define OF_READ 0x0080
#define OF_WRITE 0x0040
#define OF_READWRITE 0x0020
typedef struct _DLF
{


extern BOOL APIENTRY WtiMergeStrings(PSZ pszSrc, PSZ pszMerge, PSZ pszDst);

extern USHORT APIENTRY WtiDlgFile(HWND hwnd, PDLF pdlf);

extern VOID APIENTRY WtiLFillStruct(PVOID pSrc, USHORT cb, BYTE fillByte);

extern VOID APIENTRY WtiLCopyStruct(PVOID pSrc, PVOID pDst, USHORT cb);

extern int APIENTRY WtiLStrLen(PSZ pszStr);

extern VOID APIENTRY WtiLStrCat(PSZ pszDst, PSZ pszSrc);

extern int APIENTRY WtiLStrCmp(PSZ pszStr1, PSZ pszStr2);

extern VOID APIENTRY WtiLStrCpy(PSZ pszDst, PSZ pszSrc);

extern VOID APIENTRY WtiAddExt(PSZ pszDst, PSZ pszExt);

extern PSZ APIENTRY WtiFileInPath(PSZ pszPath);

extern BOOL APIENTRY WtiOpenFile(PSZ pszFile, PHFILE phFile, PSZ pszOpenFile, USHORT wMode);

extern ULONG APIENTRY WtiGetTextExtent(HPS hps, PCH pchStr, USHORT cch);
