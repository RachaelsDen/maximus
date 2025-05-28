// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef _WINCOMM_H
#include <termios.h>

typedef int OSCOMMHANDLE;
typedef int hfComm;
typedef int HFILE;

typedef struct _DCB
{
    DWORD DCBlength;
    DWORD BaudRate;
    DWORD fBinary : 1;
    DWORD fParity : 1;
    DWORD fOutxCtsFlow : 1;
    DWORD fOutxDsrFlow : 1;
    DWORD fDtrControl : 2;
    DWORD fDsrSensitivity : 1;
    DWORD fTXContinueOnXoff : 1;
    DWORD fOutX : 1;
    DWORD fInX : 1;
    DWORD fErrorChar : 1;
    DWORD fNull : 1;
    DWORD fRtsControl : 2;
    DWORD fAbortOnError : 1;
    DWORD fDummy2 : 17;
    WORD wReserved;
    WORD XonLim;
    WORD XoffLim;
    BYTE ByteSize;
    BYTE Parity;
    BYTE StopBits;
    char XonChar;
    char XoffChar;
    char ErrorChar;
    char EofChar;
    char EvtChar;
    WORD wReserved1;
} DCB, *LPDCB;


#define CBR_110 110
#define CBR_19200 19200
#define CBR_300 300
#define CBR_38400 3400
#define CBR_600 600
#define CBR_56000 5600
#define CBR_1200 1200
#define CBR_57600 57600
#define CBR_2400 2400
#define CBR_115200 115200
#define CBR_4800 4500
#define CBR_128000 128000
#define CBR_9600 9600
#define CBR_256000 256000
#define CBR_14400 14400

#define DTR_CONTROL_ENABLED 1
#define DTR_CONTROL_DISABLED 2
#define DTR_CONTROL_HANDSHAKE 3

#define RTS_CONTROL_ENABLE 1
#define RTS_CONTROL_DISABLE 2
#define RTS_CONTROL_HANDSHAKE 3
#define RTS_CONTROL_TOGGLE 4


