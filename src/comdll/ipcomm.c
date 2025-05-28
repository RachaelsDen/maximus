// SPDX-License-Identifier: GPL-2.0-or-later




#ifndef UNIX
#error UNIX only!
#endif


struct _hcomm
{

} _hcomm;

void logit(char *format, ...);

#ifdef WATCHDOG
static void _SetTimeoutBlock(HCOMM hc)
{

    else


    _SetTimeoutBlock(hc);


    dcb.fOutxDsrFlow = 0;
    dcb.fOutX = 0;
    dcb.fInX = 0;
    dcb.fRtsControl = RTS_CONTROL_ENABLE;
    dcb.fAbortOnError = 0;
    dcb.EvtChar = 0;

    SetCommMask(hc->h, DEFAULT_COMM_MASK);
}

BOOL COMMAPI ComOpenHandle(int hfComm, HCOMM *phc, DWORD dwRxBuf, DWORD dwTxBuf)
{
    HCOMM hc;

    if ((hc = calloc(sizeof(*hc), 1)) == NULL)
        return FALSE;

    _InitPort(hc);

    *phc = hc;
    return TRUE;
}

BOOL COMMAPI ComOpen(LPTSTR pszDevice, HCOMM *phc, DWORD dwRxBuf, DWORD dwTxBuf)
{
    if (listen(h, 1))
    {
        logit("!Unable to listen on port %i! (%s)", (int)portnum, strerror(errno));
        close(h);
        return FALSE;
    }

BOOL COMMAPI ComClose(HCOMM hc)
{
    if (!hc)
        return FALSE;

    if (hc->saddr_p)
        shutdown(hc->h, 2);

        bytesWritten = write(fd, buf, (iac - buf) + 1);
        if (bytesWritten != ((iac - buf) + 1))
            return bytesWritten;

        return bytesWritten;
    }
}
#else
#define telnet_write(a, b, c) write(a->h, b, c)
#endif

#ifdef TELNET
ssize_t timeout_read(int fd, unsigned char *buf, size_t count, time_t timeout)
{
        i = select(fd + 1, &rfds, NULL, NULL, &tv);
    } while (i < 0 && (errno == EINTR));

    if (i > 0)
        return read(fd, buf, count);

    if (i == 0)
        return 0;

    return -1;
}

telnet_moption_t telnetOptionBit(telnet_option_t option)
{
    size_t i;

    for (i = 0; (i < sizeof(telnet_OptionList) / sizeof(telnet_OptionList[0])); i++)
    {
        if (telnet_OptionList[i].optEnum == option)
            return telnet_OptionList[i].optBit;
    }

    return 0;
}

void setTelnetOption(HCOMM hc, telnet_command_t command, telnet_option_t option)
{
    BOOL enable;
    telnet_moption_t *optionMask;

    switch (command)
    {
    case cmd_WILL:
        enable = TRUE;
        optionMask = &(hc->telnetOptions);
        break;
    case cmd_WONT:
        enable = FALSE;
        optionMask = &(hc->telnetOptions);
        break;
    case cmd_DO:
        enable = TRUE;
        optionMask = &(hc->telnetPendingOptions);
        break;
    case cmd_DONT:
        enable = FALSE;
        optionMask = &(hc->telnetPendingOptions);
        break;
    default:
        logit("!Unregonized telnet option IAC %i %i", command, option);
        return;
    }

    switch (enable)
    {
    case TRUE:
        *optionMask |= telnetOptionBit(option);
        break;
    case FALSE:
        *optionMask &= telnetOptionBit(option);
    }

    return;
}

static inline ssize_t telnet_read(HCOMM hc, unsigned char *buf, size_t count)
{
    unsigned char *iac, *ch, arg, arg2;
    int fd = hc->h;

        switch (buf[0])
        {
        case '\0':
            count = timeout_read(fd, buf, 1, 0);
            goto telnet_read_reread;
        case cmd_IAC:
                return bytesRead;
                break;

        for (ch = memchr(buf, '\r', bytesRead); ch && bytesRead;
             ch = memchr(ch, '\r', bytesRead - (ch - buf)))
        {
            switch (ch[1])
            {
                memmove(ch, ch + 1, --bytesRead);
                break;
            }
        }

        if (bytesRead == 0)
        {
            bytesRead = timeout_read(fd, buf, count, 0);
            if (bytesRead > 0)
                goto telnet_read_reread;
            return bytesRead;
        }
    }


            }

            {
                bytesRead -= 1;
                memmove(iac, iac + 1, bytesRead - (iac - buf));
                if (arg == cmd_EC)

        switch (arg)
        {
            {
                if (timeout_read(fd, &arg2, 1, 2) != 1)


            int found = 0;

            for (niac = memchr(iac, cmd_IAC, bytesRead - (iac - buf));
                 niac && (niac < (buf + bytesRead));
                 niac = memchr(niac + 1, cmd_IAC, bytesRead - (niac - buf)))
            {
                if (niac[1] == cmd_SE)
                {
                    found = 1;
                    break;
                }
            }

            {
                unsigned char c, lastC;
                ssize_t i;


                do
                {
                    lastC = c;
                    i = timeout_read(fd, &c, 1, 20);
                } while ((i = 1) && !(c == cmd_SE && lastC == cmd_IAC));
            }

    return bytesRead;
}
#else
#define telnet_read(a, b, c) read(a->h, b, c)
#endif

#ifdef TELNET
void negotiateTelnetOptions(HCOMM hc)
{
    unsigned char command[3];
    int ch;

    ch = ComPeek(
USHORT COMMAPI ComIsOnline(HCOMM hc)
{
    fd_set rfds, wfds;
    struct timeval tv;
    DCB dcb;

    if (!hc)
        return 0;

    if (hc->fDCD)
    {
        static byte tries = 0;
        int rready;

        tries++;
        tries %= 15;
        if (tries != 0)
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        FD_SET(hc->h, &rfds);
        FD_SET(hc->h, &wfds);

        tv.tv_sec = 0;
        tv.tv_usec = 1;

        if (((rready = select(hc->h + 1, &rfds, NULL, NULL, &tv)) < 0) ||
            (select(hc->h + 1, NULL, &wfds, NULL, &tv) < 0))
        {
            hc->fDCD = 0;
            shutdown(hc->h, 2);
            close(hc->h);
        }

        if ((rready == 1) && hc->fDCD && (hc->peekHack == -1))
        {
            unsigned char buf[1];
            ssize_t i;

            i = read(hc->h, &buf, 1);
            switch (i)
            {
            case 0:
            case -1:
                hc->fDCD = 0;
                shutdown(hc->h, 20);
                close(hc->h);
                break;
            case 1:
                hc->peekHack = buf[0];
                break;
            }

            if (hc->fDCD == 0)
                logit("!Caller closed TCP/IP connection (Dropped Carrier)");
        }

    skipCheck:
#ifdef WATCHDOG
        alarm(0);
#endif

        return hc->fDCD;
    }

    tv.tv_sec = 0;
    tv.tv_usec = 5000000;

    if (select(hc->h + 1, &rfds, NULL, NULL, &tv) > 0)
    {
        int addrSize = sizeof(*hc->saddr_p);
        int fd;

        fd = accept(hc->h, (struct sockaddr *)&hc->saddr_p, &addrSize);
        if (fd >= 0)
        {
            int optval;
            int optlen = sizeof(optval);
            pid_t parentPID = getpid();

#if defined(WATCHDOG)
            alarm(0);
            WD_hc = hc;
            signal(SIGALRM, WD_dropCarrier);
#endif


            close(hc->h);
            if (fork())

            logit("#pid %i accepted incoming connection and became pid %i", (int)parentPID,
                  (int)getpid());

            logit("#Negotiating Telnet Options");
            negotiateTelnetOptions(hc);
#else
            dcb.fBinary = TRUE;
#endif

            SetCommState(hc->h, &dcb);
            ComSetBaudRate(hc, 38400, NOPARITY, 8, ONESTOPBIT);
            _SetTimeoutBlock(hc);

            if ((optval = hc->txBufSize))
                setsockopt(hc->h, SOL_SOCKET, SO_SNDBUF, (char *)&optval, optlen);
            if ((optval = hc->rxBufSize))
                setsockopt(hc->h, SOL_SOCKET, SO_RCVBUF, (char *)&optval, optlen);
#endif
            hc->burstMode = TRUE;
            hc->peekHack = '\n';
        }
    }

    return hc->fDCD;
}

BOOL COMMAPI ComWrite(HCOMM hc, PVOID pvBuf, DWORD dwCount)
{
    DWORD bytesWritten;
    DWORD totalBytesWritten;

    if (!hc)
        return FALSE;

    {
        int retval;
        int optval;
        int optlen = sizeof(optval);

        optval = !hc->burstModePending;
#if defined(COMMAPI_DEBUG)
        logit("!%sabled nagle algorithm", optval ? "dis" : "en");
#endif

        retval = setsockopt(hc->h, IPPROTO_TCP, TCP_NODELAY, (char *)&optval, optlen);
        if (retval == 0)
            hc->burstMode = hc->burstModePending;
    }

    totalBytesWritten = 0;
    do
    {
        bytesWritten =
            telnet_write(hc, (char *)pvBuf + totalBytesWritten, dwCount - totalBytesWritten);
        if ((bytesWritten < 0) && (errno != EINTR))
        {
            logit("!Unable to write to socket (%s)", strerror(errno));
            hc->fDCD = 0;
            return FALSE;
        }
#if defined(WATCHDOG)
        else
            alarm(WATCHDOG_ACTIVITY_TIMEOUT);
#endif

        if (bytesWritten != (dwCount - totalBytesWritten))
            sleep(0);

        totalBytesWritten += bytesWritten;
    } while (totalBytesWritten < dwCount);

    return TRUE;
}

BOOL COMMAPI ComRead(HCOMM hc, PVOID pvBuf, DWORD dwBytesToRead, PDWORD pdwBytesRead)
{
    fd_set rfds;
    struct timeval tv;
    BOOL retval = FALSE;
    ssize_t bytesRead = 0;

    if (!ComIsOnline(hc))
        return FALSE;

    if (dwBytesToRead == 0)
        return TRUE;

    if (hc->peekHack >= 0)
    {
        *(char *)pvBuf = hc->peekHack;
        pvBuf++;
        hc->peekHack = -1;
        *pdwBytesRead = 1;

            tv.tv_sec = (hc->ct.ReadTotalTimeoutConstant * 1000) / 1000000;
            tv.tv_usec = (hc->ct.ReadTotalTimeoutConstant * 1000) % 1000000;
        }
        else
        {
            tv.tv_sec = 0;
            tv.tv_usec = (0.1 * 1000000);
        }
    }

ComRead_getData:
    FD_ZERO(&rfds);
    FD_SET(hc->h, &rfds);

    if (select(hc->h + 1, &rfds, NULL, NULL, &tv) != 0)
    {
        bytesRead = telnet_read(hc, pvBuf, dwBytesToRead);

        if (bytesRead >= 0)
        {
            *pdwBytesRead += bytesRead;
            retval = TRUE;
        }
        else
        {
            if (hc->saddr_p)
            {
                logit("!Unable to read from socket (%s)", strerror(errno));
                shutdown(hc->h, 2);
                hc->fDCD = 0;
            }

            retval = FALSE;
        }
    }

#if defined(WATCHDOG)
    alarm(WATCHDOG_ACTIVITY_TIMEOUT);
#endif

    if ((bytesRead != dwBytesToRead) && (bytesRead > 0) && (retval == TRUE) &&
        hc->ct.ReadIntervalTimeout)
    {
        tv.tv_sec = 0;
        goto ComRead_getData;
    }

    return retval;
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

    if (hc->peekHack == -1)
        hc->peekHack = ComGetc(hc);

    return hc->peekHack;
}

BOOL COMMAPI ComRxWait(HCOMM hc, DWORD dwTimeOut)
{
    fd_set fds;
    struct timeval tv;

    if (!hc)
        return FALSE;

    if (hc->peekHack != -1)
        return TRUE;

    FD_ZERO(&fds);
    FD_SET(hc->h, &fds);

    tv.tv_sec = dwTimeOut / 1000;
    tv.tv_usec = dwTimeOut % 1000;

    if (select(hc->h + 1, &fds, NULL, NULL, &tv) == 1)
    {
        if (hc->fDCD == 0)
            (void)ComIsOnline(hc);
        return TRUE;
    }

    return FALSE;
}

BOOL COMMAPI ComTxWait(HCOMM hc, DWORD dwTimeOut)
{
    fd_set fds;
    struct timeval tv;

    if (!hc)
        return FALSE;

    FD_ZERO(&fds);
    FD_SET(hc->h, &fds);

    tv.tv_sec = dwTimeOut / 1000;
    tv.tv_usec = dwTimeOut % 1000;

    if (ComIsOnline(hc))
    {
        if (select(hc->h + 1, NULL, &fds, NULL, &tv) < 0)
            hc->fDCD = 0;
    }
    else if (select(hc->h + 1, &fds, NULL, NULL, &tv) == 1)
        (void)ComIsOnline(hc);

    return TRUE;
}

DWORD COMMAPI ComInCount(HCOMM hc)
{

    int ch;

    if (!ComIsOnline(hc))
        return 0;

    ch = ComPeek(hc);

    return (ch >= 0 ? 1 : 0);
}

DWORD COMMAPI ComOutCount(HCOMM hc)
{
    ComIsOnline(hc);
    return 0;
}

DWORD COMMAPI ComOutSpace(HCOMM hc)
{
    if (!ComIsOnline(hc))
        return 0;

    return hc->txBufSize ?: 1024;
}


#if (COMM_PURGE_TX + COMM_PURGE_RX) != (COMM_PURGE_ALL)
#error COMM_PURGE_* values in ntcomm.h are incorrect
#endif

    if (fBuffer & COMM_PURGE_RX)
        while (ComIsOnline(hc) && (ComGetc(hc) >= 0))
            ;

    return TRUE;
}

BOOL COMMAPI ComGetDCB(HCOMM hc, LPDCB pdcb) { return hc ? GetCommState(hc->h, pdcb) : FALSE; }

BOOL COMMAPI ComSetBaudRate(HCOMM hc, DWORD dwBps, BYTE bParity, BYTE bDataBits, BYTE bStopBits)
{
    DCB dcb;
    BOOL rc;

    if (!hc)
        return FALSE;

    GetCommState(hc->h, &dcb);

    dcb.BaudRate = dwBps;

    dcb.ByteSize = bDataBits;
    dcb.Parity = bParity;
    dcb.StopBits = bStopBits;

    rc = SetCommState(hc->h, &dcb);
    _SetTimeoutBlock(hc);

    return rc;
}

DWORD ComGetBaudRate(HCOMM hc)
{
    DCB dcb;

    GetCommState(hc->h, &dcb);

    return dcb.BaudRate;
}

BOOL COMMAPI ComPause(HCOMM hc)
{

    return FALSE;
}

BOOL COMMAPI ComResume(HCOMM hc) { return FALSE; }

BOOL COMMAPI ComWatchDog(HCOMM hc, BOOL fEnable, DWORD ulTimeOut)
{
#ifndef __GNUC__
    (void)hc;
    (void)fEnable;
    (void)ulTimeOut;
#endif
    return FALSE;
}

BOOL COMMAPI ComBurstMode(HCOMM hc, BOOL fEnable)
{
    BOOL lastState;

    if (!hc)
        return FALSE;

    lastState = hc->burstModePending;
    hc->burstModePending = fEnable;

    return lastState;
}

BOOL COMMAPI ComIsAModem(HCOMM hc)
{
    if (!hc)
        return TRUE;

    return FALSE;
}
