// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef APIENTRY
#define INCL_DOS
#include <pos2.h>
#endif

typedef SHANDLE HCOMM;

#ifdef __FLAT__
#define COMMAPI pascal __far16
#else
#define COMMAPI pascal far
#endif

#if !defined(_QC)
#pragma comment(lib, "maxcomm.lib")
#endif

USHORT COMMAPI _loadds ComHRegister(HFILE hf,
USHORT COMMAPI ComClose(HCOMM hcomm);

USHORT COMMAPI ComIsOnline(HCOMM hcomm);


SHORT COMMAPI ComGetc(HCOMM hc);

SHORT COMMAPI ComPeek(HCOMM hc);

USHORT COMMAPI ComPutc(HCOMM hc, SHORT c);

USHORT COMMAPI ComRxWait(HCOMM hc, LONG lTimeOut);

USHORT COMMAPI ComTxWait(HCOMM hc, LONG lTimeOut);

USHORT COMMAPI ComInCount(HCOMM hc);

USHORT COMMAPI ComOutCount(HCOMM hc);

USHORT COMMAPI ComOutSpace(HCOMM hc);

#define COMM_PURGE_RX 1
#define COMM_PURGE_TX 2
#define COMM_PURGE_ALL (COMM_PURGE_RX | COMM_PURGE_TX)
USHORT COMMAPI ComPurge(HCOMM hc, SHORT fsWhich);

USHORT COMMAPI ComPause(HCOMM hc);

USHORT COMMAPI ComResume(HCOMM hc);

USHORT COMMAPI ComGetFH(HCOMM hc);

USHORT COMMAPI ComWatchDog(HCOMM hc, BOOL OnOff, USHORT Seconds);


#ifdef IOCTL_ASYNC
USHORT COMMAPI ComGetDCB(HCOMM hc, PDCBINFO pdbc);
USHORT COMMAPI ComSetDCB(HCOMM hc, PDCBINFO pdcb);
#endif

USHORT COMMAPI ComSetBaudRate(HCOMM hcomm, LONG bps, CHAR parity, USHORT databits, USHORT stopbits);
