// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef _MODEM_H_INCLUDED
#define _MODEM_H_INCLUDED

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

struct _fossil_info
{
    int size;
    byte majver;
    byte minver;
    byte far *id;
    sword input_size;
    sword input_free;
    sword output_size;
    sword output_free;
    byte width;
    byte height;
    byte baud;
};

void fossil_getxy(char *row, char *col);
int fossil_wherex(void);
int fossil_wherey(void);
void fossil_gotoxy(char row, char col);
int fossil_inf(struct _fossil_info far *finfo);
void _stdc fossil_putc(char chr);
void _stdc fossil_puts(char *str);
int mdm_baud(int bod);
void mdm_break(unsigned int hundredths);
int mdm_cmd(char *command);
int mdm_deinit(void);
char mdm_dump(char buffer);
int mdm_init(int prt);
void mdm_pputs(char *str);
int cdecl mdm_printf(char *format, ...);
void mdm_watchdog(int watch);
int mdm_blockread(int max_chars, char *offset);
int mdm_blockwrite(int max_chars, char *offset);

#define mdm_halt() mdm_ctrlc(1)

#define Mdm_Flow_On() Mdm_Flow(FLOW_ON)
#define Mdm_Flow_Off() Mdm_Flow(FLOW_PARTIAL_OFF)

#if defined(OS_2) || defined(NT) || defined(UNIX)

#ifdef OS_2
#ifndef COMMAPI
#include "comm.h"
#endif
#else
#include "ntcomm.h"
#endif


extern int cdecl port;

#define CallFossil(func, al) CallFos(port, func, al)

unsigned short CallFos(int dx, char func, char al);

#pragma aux CallFos = 0xcd 0x14 parm[dx][ah][al] value[ax];
#else
unsigned short far pascal CallFossil(int FOSSIL_function, int AL);
#endif

#define CallFossilNR CallFossil

#define mdm_pputc(chr) ((unsigned char)CallFossil(FOSSIL_xmit, chr))
#define mdm_pputcw(chr) CallFossilNR(FOSSIL_xmitw, chr)
#define mdm_ggetcw() (CallFossil(FOSSIL_recvw, 0) & 0xff)
#define mdm_status() CallFossil(FOSSIL_status, 0)
#define mdm_peek() ((int)CallFossil(FOSSIL_peek, 0))
#define mdm_break_on() CallFossil(FOSSIL_break, 1)
#define mdm_break_off() CallFossil(FOSSIL_break, 0)
#define mdm_fflush() CallFossil(FOSSIL_flushout, 0);
#define mdm_dtr(dtr) CallFossilNR(FOSSIL_dtr, dtr)
#define mdm_flow(flow) CallFossilNR(FOSSIL_flow, (flow) | 0xf0)
#define out_full() (local ? FALSE : !(mdm_status() & STATUS_ROOMAVAIL))

sword mdm_getc(void);
word mdm_ctrlc(word mask);
word out_empty(void);
word mdm_avail(void);
word carrier(void);
word real_carrier(void);

#define CARRIER() carrier()
#define OUT_EMPTY() out_empty()
#define OUT_FULL() out_full()
#define MDM_AVAIL() mdm_avail()
#define GetConnectionType() CTYPE_ASYNC
#endif


#define FOSSIL_baud 0x00
#define FOSSIL_xmitw 0x01
#define FOSSIL_recvw 0x02
#define FOSSIL_status 0x03
#define FOSSIL_init 0x04
#define FOSSIL_deinit 0x05
#define FOSSIL_dtr 0x06
#define FOSSIL_ttick 0x07
#define FOSSIL_flushout 0x08
#define FOSSIL_dumpout 0x09
#define FOSSIL_dumpin 0x0a
#define FOSSIL_xmit 0x0b
#define FOSSIL_peek 0x0c
#define FOSSIL_kpeek 0x0d
#define FOSSIL_getcw 0x0e
#define FOSSIL_flow 0x0f
#define FOSSIL_ctrlc 0x10
#define FOSSIL_gotoxy 0x11
#define FOSSIL_getxy 0x12
#define FOSSIL_putc 0x13
#define FOSSIL_watchdog 0x14
#define FOSSIL_bputc 0x15
#define FOSSIL_attfunc 0x16
#define FOSSIL_reboot 0x17
#define FOSSIL_blockread 0x18
#define FOSSIL_blockwrite 0x19
#define FOSSIL_break 0x1a
#define FOSSIL_info 0x1b
#define FOSSIL_extapp_inst 0x7e
#define FOSSIL_extapp_dest 0x7f

#define INIT_ok 0x00
#define INIT_OK 0x00
#define INIT_alreadyopen 0x01
#define INIT_ALREADYOPEN 0x01
#define INIT_nofossil 0x02
#define INIT_NOFOSSIL 0x02

#define BAUD300 0x43
#define BAUD600 0x63
#define BAUD1200 0x83
#define BAUD2400 0xa3
#define BAUD4800 0xc3
#define BAUD9600 0xe3
#define BAUD19200 0x03
#define BAUD38400 0x23
#ifndef __MSDOS__
#define BAUD115200 0xfe
#define BAUD57600 0xff
#endif

#define FLOW_TXOFF 0x01
#define FLOW_CTS 0x02
#define FLOW_DSR 0x04
#define FLOW_RXOFF 0x08

#define DUMP_OUTPUT 0x00
#define DUMP_INPUT 0x01
#define DUMP_ALL 0x02

#define DTR_DOWN 0x00
#define DTR_UP 0x01

#define FLOW_ON 0x00
#define FLOW_PARTIAL_OFF 0x01
#define FLOW_OFF 0x02
#define FLOW_NO_CCK 0x03

