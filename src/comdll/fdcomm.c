// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef UNIX
#error UNIX only!
#endif

static char rcs_id[] = "$Id: fdcomm.c,v 1.2 2003/06/05 23:26:49 wesgarland Exp $";

#include "ntcomm.h"
#include "prog.h"
#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef DEBUG_FILE
static FILE *fp_out;
#endif

static void _SetTimeoutBlock(HCOMM hc)
{

    else


static void _InitPort(HCOMM hc)
{
    DCB dcb;


    GetCommState(hc->h, &dcb);


    dcb.fOutxDsrFlow = 0;
    dcb.fOutX = 0;
    dcb.fInX = 0;
    dcb.fRtsControl = RTS_CONTROL_ENABLE;
    dcb.fAbortOnError = 0;
    dcb.EvtChar = 0;

    SetCommMask(hc->h, DEFAULT_COMM_MASK);
}


    SetupComm(hc->h, dwRxBuf, dwTxBuf);


    hc->cqTx.pbHead = hc->cqTx.pbTail = hc->cqTx.pbBuf;
    hc->cqTx.pbEnd = hc->cqTx.pbBuf + dwTxBuf;


BOOL COMMAPI ComOpenHandle(int hfComm, HCOMM *phc, DWORD dwRxBuf, DWORD dwTxBuf)
{
    HCOMM hc;

    if ((hc = malloc(sizeof(*hc))) == NULL)
        return FALSE;


      (hc->hevTxDone=CreateEvent(NULL, FALSE, TRUE, NULL))==NULL ||
      (hc->hevRxDone=CreateEvent(NULL, FALSE, TRUE, NULL))==NULL ||
      (hc->hevMonDone=CreateEvent(NULL, FALSE, FALSE, NULL))==NULL ||
      (hc->hevTxWait=CreateEvent(NULL, FALSE, TRUE, NULL))==NULL ||
      (hc->hevRxWait=CreateEvent(NULL, FALSE, TRUE, NULL))==NULL ||
      (hc->hevTxPause=CreateEvent(NULL, TRUE, TRUE, NULL))==NULL ||
      (hc->hevRxPause=CreateEvent(NULL, TRUE, TRUE, NULL))==NULL)
  {
    return FALSE;
  }
#endif

    hc->cThreads = 0;
    hc->fDie = FALSE;


  if ((hc->hTx=CreateThread(NULL, 0, TxThread, (LPVOID)hc, CREATE_SUSPENDED, &dwJunk))==NULL ||
      (hc->hRx=CreateThread(NULL, 0, RxThread, (LPVOID)hc, CREATE_SUSPENDED, &dwJunk))==NULL ||
      (hc->hMn=CreateThread(NULL, 0, MnThread, (LPVOID)hc, CREATE_SUSPENDED, &dwJunk))==NULL)
  {
    free(hc);
    return FALSE;
  }



  ResumeThread(hc->hMn);
  ResumeThread(hc->hRx);
  ResumeThread(hc->hTx);
    *phc = hc;
    return TRUE;
}


BOOL COMMAPI ComOpen(LPTSTR pszDevice, HCOMM *phc, DWORD dwRxBuf, DWORD dwTxBuf)
{
    struct sockaddr_in serv_addr;

#if 0
        h = open(pszDevice, O_RDWR, 0666);
        if (h < 1)
            return FALSE;
    }
    else
    {
            h = STDIN_FILENO;
            serv_addr.sin_port = 0;
            goto openIt;
        }

        if (!port)
            port = 2001;

        if ((h = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            return FALSE;

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons((short)port);

        junk = AF_INET;
        setsockopt(h, SOL_SOCKET, SO_REUSEADDR, (char *)&junk, sizeof(junk));

        if (bind(h, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))
        {
            close(h);
            return FALSE;
        }

        if (listen(h, 1))
        {
            close(h);
            return FALSE;
        }
    }

openIt:


BOOL COMMAPI ComClose(HCOMM hc)
{
    hc->fDie = TRUE;


  CloseHandle(hc->hevTx);

    if (hc->saddr_p)
    {
        shutdown(hc->h, 2);
        hc->fDCD = 0;
    }

    close(hc->h);
    free((char *)hc->device);
    free(hc);

#ifdef DEBUG_PIPE
    PDDeinit();
#endif

    return TRUE;
}


    if (!hc)
        return 0;


        if (select(hc->h + 1, &rfds, NULL, NULL, &tv) > 0)
        {
            int addrSize = sizeof(*hc->saddr_p);
            int fd;

            fd = accept(hc->h, (struct sockaddr *)&hc->saddr_p, &addrSize);
            if (fd >= 0)
            {
                int optval;
                int optlen;

                hc->listenfd = hc->h;
                hc->h = fd;
                hc->fDCD = 1;


                optlen = sizeof(optval);
                optval = 1;

                setsockopt(hc->h, IPPROTO_TCP, TCP_NODELAY, (char *)&optval, optlen);
            }
        }
    }
    else
        hc->fDCD = 1;
    return hc->fDCD;
}

BOOL COMMAPI ComWrite(HCOMM hc, PVOID pvBuf, DWORD dwCount)
{

    DWORD bytesWritten;
    DWORD totalBytesWritten;

    if (!hc)
        return FALSE;

BOOL COMMAPI ComWrite(HCOMM hc, PVOID pvBuf, DWORD dwCount)
{
#endif


    if (dwMaxBytes > dwCount)
      dwMaxBytes = dwCount;


      memmove(hc->cqTx.pbTail, pvBuf, dwMaxBytes);
      QueueInsertContig(&hc->cqTx, dwMaxBytes);



      dwCount -= dwMaxBytes;
      pvBuf=(char *)pvBuf+dwMaxBytes;


#ifdef DEBUG_PIPE
      PDPrintf("@Waiting to insert in buffer: (%d)\n"
             "head=%08lx, tail=%08lx, start=%08lx, end=%08lx\n",
             dwCount,
             hc->pbTxHead, hc->pbTxTail, hc->pbTxBuf, hc->pbTxEnd);
#endif

      SetEvent(hc->hevTxWait);

      Sleep(1L);
    }
  }

  return TRUE;
}
            return TRUE;

        retval = TRUE;
    }
    else
        *pdwBytesRead = 0;

    FD_ZERO(&rfds);
    FD_SET(hc->h, &rfds);

    tv.tv_sec = 0;
BOOL COMMAPI ComRead(HCOMM hc, PVOID pvBuf, DWORD dwBytesToRead, PDWORD pdwBytesRead)
{

    if (dwMaxBytes > dwBytesToRead)
      dwMaxBytes=dwBytesToRead;



    pvBuf = (char *)pvBuf + dwMaxBytes;
    dwBytesToRead -= dwMaxBytes;
    dwBytesRead += dwMaxBytes;

  }

int COMMAPI ComGetc(HCOMM hc)
{
    DWORD dwBytesRead;
    BYTE b;

    if (!ComIsOnline(hc))
        return -1;

    return (ComRead(hc, &b, 1, &dwBytesRead) == 1) ? b : -1;
}

int COMMAPI ComPeek(HCOMM hc)
{

    if (!ComIsOnline(hc))
        return -1;

    peekHack = ComGetc(hc);

    return peekHack;
}


  return (*hc->cqRx.pbHead);
}
#endif

BOOL COMMAPI ComRxWait(HCOMM hc, DWORD dwTimeOut)
{
    if (!hc)
        return FALSE;

    if (dwTimeOut == -1)
    {
        while (!ComIsOnline(hc))
            sleep(0);
    }
    else
    {

  DWORD rc;


  if (QueueEmpty(&hc->cqRx))
  {
#ifdef DEBUG_PIPE
    PDPrintf("rx: wait\n");
#endif
    rc=WaitForSingleObject(hc->hevRxWait,
                           dwTimeOut==-1 ? INFINITE : dwTimeOut);
#ifdef DEBUG_PIPE
    PDPrintf("rx: end wait\n");
#endif
  }


    SetCommMask(hc->h, DEFAULT_COMM_MASK | EV_RXCHAR);
    return TRUE;
#endif
}

  DWORD rc;


  if (!QueueEmpty(&hc->cqTx))
  {
#ifdef DEBUG_PIPE
    PDPrintf("tx: wait\n");
#endif
    rc=WaitForSingleObject(hc->hevTxWait,
                           dwTimeOut==-1 ? INFINITE : dwTimeOut);
#ifdef DEBUG_PIPE
    PDPrintf("tx:endwait\n");
#endif
  }


    SetCommMask(hc->h, DEFAULT_COMM_MASK | EV_TXEMPTY);
    return TRUE;
#endif
}


    int ch;

    if (!ComIsOnline(hc))
        return 0;

    ch = ComPeek(hc);

    return (ch >= 0 ? 1 : 0);
#if 0
  return QueueGetSize(&hc->cqRx);
#endif
}


    ComIsOnline(hc);
    return 0;


DWORD COMMAPI ComOutSpace(HCOMM hc)
{
    ComIsOnline(hc);
    return QueueGetFree(&hc->cqTx);
}


#if (COMM_PURGE_TX + COMM_PURGE_RX) != (COMM_PURGE_ALL)
#error COMM_PURGE_* values in ntcomm.h are incorrect
#endif

    if (fBuffer & COMM_PURGE_RX)
        while (ComIsOnline(hc) && (ComGetc(hc) >= 0))
            ;


  ct=hc->ct;

  ct.ReadTotalTimeoutConstant=1;
  ct.WriteTotalTimeoutConstant=1;

  SetCommTimeouts(hc->h, &ct);
  SetCommTimeouts(hc->h, &hc->ct);

#endif
    return TRUE;
}


BOOL COMMAPI ComGetDCB(HCOMM hc, LPDCB pdcb) { return GetCommState(hc->h, pdcb); }


BOOL COMMAPI ComSetBaudRate(HCOMM hc, DWORD dwBps, BYTE bParity, BYTE bDataBits, BYTE bStopBits)
{
    DCB dcb;
    BOOL rc;

    GetCommState(hc->h, &dcb);

    dcb.BaudRate = dwBps;

    dcb.ByteSize = bDataBits;
    dcb.Parity = bParity;
    dcb.StopBits = bStopBits;

    rc = SetCommState(hc->h, &dcb);

    _SetTimeoutBlock(hc);

    return rc;
}

BOOL COMMAPI ComPause(HCOMM hc)
{

  SetEvent(hc->hevRxPause);
  SetEvent(hc->hevTxPause);
#endif
    return FALSE;
}

BOOL COMMAPI ComWatchDog(HCOMM hc, BOOL fEnable, DWORD ulTimeOut)
{
#ifndef __GNUC__
    (void)hc;
    (void)fEnable;
    (void)ulTimeOut;
#endif
    return FALSE;
}
