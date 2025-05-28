// SPDX-License-Identifier: GPL-2.0-or-later



#pragma off(unreferenced)
static char rcs_id[] = "$Id: ntcomm.c,v 1.1.1.1 2002/10/01 17:49:34 sdudley Exp $";
#pragma on(unreferenced)


// HJK 98/3/23 - Don't need this function anymore, seperate threads do their
// own cleanup now:
// int cdie(HCOMM hc)
//{
//    --hc->cThreads;
// printf("Thread dying!  Count is now %d\n", hc->cThreads);
//   return 0;
//}



    ol.hEvent = hc->hevTxDone;
    ol.Offset = ol.OffsetHigh = 0L;

#ifdef DEBUG_FILE
    if ((fp_out = fopen("\\ntcomm.out", "ab")) == NULL)
    {
        printf("Can't open \\ntcomm.out!\n");
        exit(1);
    }
#endif

    for (;;)
    {

            SetEvent(ol.hEvent);
            SetCommTimeouts(hc->h, &hc->ct);

            WaitForSingleObject(hc->hevTxPause, INFINITE);

            if (hc->fDie)
                break;

            if (!WriteFile(hc->h, hc->cqTx.pbHead, cChars, &dwBytesWritten, &ol))
            {
                if (GetLastError() == ERROR_IO_PENDING)
                    GetOverlappedResult(hc->h, &ol, &dwBytesWritten, TRUE);
                else
                {
#ifdef DEBUG_TX
                    printf("!!GetLastError is %d\n", GetLastError());
#endif
                }
            }

            if (hc->fDie)
                break;


            if (fTxPurged)
                break;


            if (dwBytesWritten > 0)
                QueueRemoveContig(&hc->cqTx, dwBytesWritten);
            else
            {
                DWORD dwStat;
                COMSTAT cs;

                ClearCommError(hc->h, &dwStat, &cs);

#ifdef DEBUG_TX
                printf("@Tx: GOT ZERO! (%d) - to write: %d\n", dwStat, pbTxBot - hc->pbTxHead);

                printf("(%d %d %d %d %d %d %d %d %d %d)\n", cs.fCtsHold, cs.fDsrHold, cs.fRlsdHold,
                       cs.fXoffHold, cs.fXoffSent, cs.fEof, cs.fTxim, cs.fReserved, cs.cbInQue,
                       cs.cbOutQue);

                fflush(stdout);
#endif
            }
        } while (hc->cqTx.pbHead != hc->cqTx.pbTail);

        if (hc->fDie)
            break;


DWORD __stdcall RxThread(LPVOID arg)
{
    ++hc->cThreads;

    {
        DWORD cChars;

        if (hc->fDie)
            break;

        cChars = QueueGetFreeContig(&hc->cqRx);

        if (cChars == 0)
        {
            QueueWrapPointersInsert(&hc->cqRx);
            cChars = QueueGetFreeContig(&hc->cqRx);
        }


                if (!rc)
                    GetOverlappedResult(hc->h, &ol, &dwBytesRead, TRUE);

                if (hc->fDie)
                    break;

#ifdef DEBUG_PIPE
#endif


        {
            Sleep(1);
        }

        if (hc->fDie)
            break;
    }

    // HJK 98/03/22 Thread exits now regularly, in stead of committing suicide :-)
    --hc->cThreads;
    ExitThread(1);
    return 0;
}


DWORD __stdcall MnThread(LPVOID arg)
{
    ++hc->cThreads;


    GetCommModemStatus(hc->h, &dwCond);
    hc->fDCD = !!(dwCond & MS_RLSD_ON);

    for (;;)
    {
            hc->fDCD = !hc->fDCD;

        {
#ifdef DEBUG_PIPE
            PDPrintf("@Mn: Got line error; dwErrors=%08lx\n", dwErrors);
#endif

            ClearCommError(hc->h, &dwErrors, NULL);
        }

            SetEvent(hc->hevRxWait);

        if (hc->fDie)
            break;
    }

    // HJK 98/03/22 Thread exits now regularly, in stead of committing suicide :-)
    --hc->cThreads;
    ExitThread(1);
    return 0;
}

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


BOOL COMMAPI ComOpenHandle(HANDLE hfComm, HCOMM *phc, DWORD dwRxBuf, DWORD dwTxBuf)
{
    COMMPROP cp;
    HCOMM hc;

    if (!GetCommProperties(hfComm, &cp))
        return FALSE;


    hc->h = hfComm;

        (hc->hevTxDone = CreateEvent(NULL, FALSE, TRUE, NULL)) == NULL ||
        (hc->hevRxDone = CreateEvent(NULL, FALSE, TRUE, NULL)) == NULL ||
        (hc->hevMonDone = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL ||
        (hc->hevTxWait = CreateEvent(NULL, FALSE, TRUE, NULL)) == NULL ||
        (hc->hevRxWait = CreateEvent(NULL, FALSE, TRUE, NULL)) == NULL ||
        (hc->hevTxPause = CreateEvent(NULL, TRUE, TRUE, NULL)) == NULL ||
        (hc->hevRxPause = CreateEvent(NULL, TRUE, TRUE, NULL)) == NULL)
    {
        return FALSE;
    }

    hc->cThreads = 0;
    hc->fDie = FALSE;



    ResumeThread(hc->hMn);
    ResumeThread(hc->hRx);
    ResumeThread(hc->hTx);


BOOL COMMAPI ComOpen(LPTSTR pszDevice, HCOMM *phc, DWORD dwRxBuf, DWORD dwTxBuf)
{
    SECURITY_ATTRIBUTES sa;
    HANDLE h;


    if ((h = CreateFile(pszDevice, GENERIC_READ | GENERIC_WRITE, 0, &sa, OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, (HANDLE)0)) ==
        INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }


BOOL COMMAPI ComClose(HCOMM hc)
{

    // HJK 98/3/23 : Bug in Windows95 can only fixed this way.
    // TerminateThreads is a rather obscure function and should not
    // be used, and not only because it does not work right under Win95.
    // Tried to fix instability problems under NT in threads.

    hc->fDie = TRUE;
    SetEvent(hc->hevTx);
    SetEvent(hc->hevTxPause);
    SetEvent(hc->hevTxDone);
    SetEvent(hc->hevTxWait);
    SetEvent(hc->hevRxPause);
    SetEvent(hc->hevRxDone);
    SetEvent(hc->hevRxWait);
    SetEvent(hc->hevMonDone);
    SetEvent(hc->h);

    while (hc->cThreads > 0)
        Sleep(10L);

    CloseHandle(hc->hevTxDone);
    CloseHandle(hc->hevRxDone);
    CloseHandle(hc->hevMonDone);
    CloseHandle(hc->hevTxWait);
    CloseHandle(hc->hevRxWait);
    CloseHandle(hc->hevTxPause);
    CloseHandle(hc->hevRxPause);
    CloseHandle(hc->h);


USHORT COMMAPI ComIsOnline(HCOMM hc)
{
#if 1

BOOL COMMAPI ComWrite(HCOMM hc, PVOID pvBuf, DWORD dwCount)
{
    DWORD dwMaxBytes;

#ifdef DEBUG_PIPE

    while (dwCount)
    {
        dwMaxBytes = QueueGetFreeContig(&hc->cqTx);

        if (dwMaxBytes == 0)
        {
            QueueWrapPointersInsert(&hc->cqTx);
            dwMaxBytes = QueueGetFreeContig(&hc->cqTx);
        }


        if (dwMaxBytes)
        {

            dwCount -= dwMaxBytes;
            pvBuf = (char *)pvBuf + dwMaxBytes;


#ifdef DEBUG_PIPE
            PDPrintf("@Waiting to insert in buffer: (%d)\n"
                     "head=%08lx, tail=%08lx, start=%08lx, end=%08lx\n",
                     dwCount, hc->pbTxHead, hc->pbTxTail, hc->pbTxBuf, hc->pbTxEnd);
#endif

            SetEvent(hc->hevTxWait);

            Sleep(1L);
        }
    }

    return TRUE;
}


        if (dwMaxBytes > dwBytesToRead)
            dwMaxBytes = dwBytesToRead;


        pvBuf = (char *)pvBuf + dwMaxBytes;
        dwBytesToRead -= dwMaxBytes;
        dwBytesRead += dwMaxBytes;


int COMMAPI ComGetc(HCOMM hc)
{
    DWORD dwBytesRead;
    BYTE b;

    return ComRead(hc, &b, 1, &dwBytesRead) ? b : -1;
}


    if (QueueEmpty(&hc->cqRx))
        return -1;

    QueueWrapPointersRemove(&hc->cqRx);


BOOL COMMAPI ComPutc(HCOMM hc, int c)
{
    BYTE b = (BYTE)c;

    return ComWrite(hc, &b, 1);
}


    ResetEvent(hc->hevRxWait);
    SetCommMask(hc->h, DEFAULT_COMM_MASK | EV_RXCHAR);


    SetCommMask(hc->h, DEFAULT_COMM_MASK);

    return (rc != WAIT_TIMEOUT);
}


    ResetEvent(hc->hevTxWait);
    SetCommMask(hc->h, DEFAULT_COMM_MASK | EV_TXEMPTY);


    SetCommMask(hc->h, DEFAULT_COMM_MASK);

    return (rc != WAIT_TIMEOUT);
}


DWORD COMMAPI ComOutCount(HCOMM hc) { return QueueGetSize(&hc->cqTx); }


BOOL COMMAPI ComPurge(HCOMM hc, DWORD fBuffer)
{
    COMMTIMEOUTS ct;

#ifdef DEBUG_PIPE
    PDPrintf("tx: purge\n");
#endif

    if (fBuffer & COMM_PURGE_RX)
    {
        fRxPurged = TRUE;
        QueuePurge(&hc->cqRx);
        PurgeComm(hc->h, PURGE_RXCLEAR);
    }

    if (fBuffer & COMM_PURGE_TX)
    {
        fTxPurged = TRUE;
        QueuePurge(&hc->cqTx);
        PurgeComm(hc->h, PURGE_TXCLEAR);
    }


    ct = hc->ct;

    ct.ReadTotalTimeoutConstant = 1;
    ct.WriteTotalTimeoutConstant = 1;

    SetCommTimeouts(hc->h, &ct);
    SetCommTimeouts(hc->h, &hc->ct);

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

    ResetEvent(hc->hevRxPause);
    ResetEvent(hc->hevTxPause);
    return FALSE;
}

BOOL COMMAPI ComResume(HCOMM hc)
{
    SetEvent(hc->hevRxPause);
    SetEvent(hc->hevTxPause);
    return FALSE;
}

BOOL COMMAPI ComWatchDog(HCOMM hc, BOOL fEnable, DWORD ulTimeOut)
{
    (void)hc;
    (void)fEnable;
    (void)ulTimeOut;
    return FALSE;
}

