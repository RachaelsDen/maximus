// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __BFILE_H_DEFINED
#define __BFILE_H_DEFINED

#ifndef __PROG_H_DEFINED
#include "prog.h"
#endif



typedef struct _bfile
{
#define BUF_ID 0x8152

} * BFILE;

#define Bgetc(b) ((b)->pcBufCur < (b)->pcBufEnd ? *(b)->pcBufCur++ : _Bgetc(b))

BFILE _fast Bopen(char *pszName, int fMode, int fShare, size_t stBufSize);
int _fast Bclose(BFILE b);
int _fast Bread(BFILE b, void *pvBuf, unsigned uiSize);
int _fast Bwrite(BFILE b, void *pvBuf, unsigned uiSize);
int _fast _Bgetc(BFILE b);
long _fast Bseek(BFILE b, long lRelPos, int fWhere);
int _fast Bfileno(BFILE b);
long _fast Btell(BFILE b);
char *_fast Bgets(char *pszOut, unsigned uiMaxLen, BFILE b);
int _fast Bputs(BFILE b, char *pszOut);
void _stdc Bprintf(BFILE bf, char *format, ...);

