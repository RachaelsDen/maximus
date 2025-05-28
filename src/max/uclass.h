// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __UCLASS_H_DEFINED
#define __UCLASS_H_DEFINED

cpp_begin()

#define CLS_ID 0x8f7c9321L

} CLSHDR;


typedef struct _clsrec
{






#define mailflag(b) (!!(ClassGetInfo(cls, CIT_MAILFLAGS) & (b)))
#define acsflag(b) (!!(ClassGetInfo(cls, CIT_ACCESSFLAGS) & (b)))


#define CIT_NUMCLASSES -1
#define CIT_DAY_TIME 0
#define CIT_CALL_TIME 1
#define CIT_DL_LIMIT 2
#define CIT_RATIO 3
#define CIT_MIN_BAUD 4
#define CIT_MIN_XFER_BAUD 5
#define CIT_MAX_CALLS 6
#define CIT_FREE_RATIO 7
#define CIT_UPLOAD_REWARD 8
#define CIT_ACCESSFLAGS 9
#define CIT_MAILFLAGS 10
#define CIT_USERFLAGS 11
#define CIT_LEVEL 12
#define CIT_KEY 13
#define CIT_INDEX 14
#define CIT_OLDPRIV 15


typedef struct _uclassh
{
} CLH, *PCLH;


void ClassFlag(int idx, int which, dword fSet, dword fReset);
char *privstr(word priv, char *buf);

#define ClassSetMailFlag(i, f) ClassFlag(i, CIT_MAILFLAGS, f, 0)
#define ClassResetMailFlag(i, f) ClassFlag(i, CIT_MAILFLAGS, 0, f)
#define ClassSetAcsFlag(i, f) ClassFlag(i, CIT_ACCESSFLAGS, f, 0)
#define ClassResetAcsFlag(i, f) ClassFlag(i, CIT_ACCESSFLAGS, 0, f)

#define Priv_Level(l) ClassDesc(ClassLevelIndex(l))

int max2priv(word usLevel);
word max3priv(int iPriv);

cpp_end()

#endif
