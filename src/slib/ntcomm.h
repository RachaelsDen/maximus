// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __NTCOMM_H_DEFINED
#define __NTCOMM_H_DEFINED

#include "compiler.h"
#include "comqueue.h"
#include "pwin.h"
#ifdef UNIX
#include "wincomm.h"
#endif

#ifndef UNIX
#define DEFAULT_COMM_MASK (EV_ERR | EV_RLSD)

#ifndef UNIX
#define COMMAPI_VER 1
typedef struct
{


struct _hcomm;
typedef struct _hcomm *HCOMM;
#endif

#define COMM_PURGE_RX 1
#define COMM_PURGE_TX 2
#define COMM_PURGE_ALL (COMM_PURGE_RX | COMM_PURGE_TX)

BOOL COMMAPI ComOpenHandle(OSCOMMHANDLE hfComm, HCOMM *phc, DWORD dwRxBuf, DWORD dwTxBuf);
BOOL COMMAPI ComOpen(LPTSTR pszDevice, HCOMM *phc, DWORD dwRxBuf, DWORD dwTxBuf);
BOOL COMMAPI ComClose(HCOMM hc);
USHORT COMMAPI ComIsOnline(HCOMM hc);
BOOL COMMAPI ComWrite(HCOMM hc, PVOID pvBuf, DWORD dwCount);
BOOL COMMAPI ComRead(HCOMM hc, PVOID pvBuf, DWORD dwBytesToRead, PDWORD pdwBytesRead);
int COMMAPI ComGetc(HCOMM hc);
int COMMAPI ComPeek(HCOMM hc);
BOOL COMMAPI ComPutc(HCOMM hc, int c);
BOOL COMMAPI ComRxWait(HCOMM hc, DWORD dwTimeOut);
BOOL COMMAPI ComTxWait(HCOMM hc, DWORD dwTimeOut);
DWORD COMMAPI ComInCount(HCOMM hc);
DWORD COMMAPI ComOutCount(HCOMM hc);
DWORD COMMAPI ComOutSpace(HCOMM hc);
BOOL COMMAPI ComPurge(HCOMM hc, DWORD fBuffer);
OSCOMMHANDLE COMMAPI ComGetHandle(HCOMM hc);
BOOL COMMAPI ComGetDCB(HCOMM hc, LPDCB pdcb);
USHORT COMMAPI ComSetDCB(HCOMM hc, LPDCB pdcb);
BOOL COMMAPI ComSetBaudRate(HCOMM hc, DWORD dwBps, BYTE bParity, BYTE bDataBits, BYTE bStopBits);
BOOL COMMAPI ComPause(HCOMM hc);
BOOL COMMAPI ComResume(HCOMM hc);
BOOL COMMAPI ComWatchDog(HCOMM hc, BOOL fEnable, DWORD ulTimeOut);

#if (COMMAPI_VER > 1)
BOOL COMMAPI ComIsAModem(HCOMM hc);
BOOL COMMAPI ComBurstMode(HCOMM hc, BOOL fEnable);
#endif
