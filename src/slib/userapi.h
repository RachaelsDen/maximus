// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __USERAPI_H_DEFINED
#define __USERAPI_H_DEFINED


#define ID_HUF 0x89098faeL
#define ID_HUFF 0x8520aed2L

typedef struct _huf
{



} * HUFF;

typedef HUFF HUFFS;

HUF _fast UserFileOpen(char *name, int mode);
long _fast UserFileSize(HUF huf);
int _fast UserFileFind(HUF huf, char *name, char *alias, struct _usr *pusr);
HUFF _fast UserFileFindOpen(HUF huf, char *name, char *alias);
int _fast UserFileFindNext(HUFF huff, char *name, char *alias);
int _fast UserFileFindPrior(HUFF huff, char *name, char *alias);
int _fast UserFileFindClose(HUFF huff);
int _fast UserFileSeek(HUF huf, long rec, struct _usr *pusr, int sz);
int _fast UserFileUpdate(HUF huf, char *name, char *alias, struct _usr *pusr);
int _fast UserFileCreateRecord(HUF huf, struct _usr *pusr, int fCheckUnique);
int _fast UserFileRemove(HUF huf, struct _usr *pusr);
int _fast UserFileClose(HUF huf);

#define UserFileFindOpenR(huf, n, a) UserFileFindOpen(huf, n, a)
#define UserFileFindSeqOpen(huf) UserFileFindOpen(huf, NULL, NULL)
#define UserFileFindSeqNext(huffs) UserFileFindNext(huffs, NULL, NULL)
#define UserFileFindSeqClose(huffs) UserFileFindClose(huffs)

