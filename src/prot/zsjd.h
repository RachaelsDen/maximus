// SPDX-License-Identifier: GPL-2.0-or-later


#include "crc.h"
#include "mm.h"
#include "modem.h"


#define UPDC32(b, c) updcrc32(b, c)

#define zmdm_pputcw(c)                                                                             \
    {                                                                                              \
        if (iTxBufLeft-- == 0)                                                                     \
        {                                                                                          \
            sendmo();                                                                              \
            iTxBufLeft--;                                                                          \
        }                                                                                          \
        *szTxPtr++ = c;                                                                            \
    }

extern int iTxBufLeft;
extern unsigned char *szTxPtr;


#define ENQ 005
#define SOH 1
#define STX 2
#define EOT 4
#define ACK 6
#define NAK 025
#define CPMEOF 032


int ZmRzInitStatics(void);
void ZmRzDeinitStatics(void);
int ZmodemRecvFile(char *path, char *name, int fInit);
int readline(int timeout);


int mode(int m);
void sendbrk(void);

void sendmo(void);
void dumpmo(void);
void ZmVarsInit(void);
int ZmQueryLocalAbort(void);
int ZmDoLocalAbort(void);
void flushmo(void);
void zmputs(char *s);
void purgeline(void);
int readline(int timeout);
void canit(void);
void zsbhdr(int type, char *hdr);
void zshhdr(int type, char *hdr);
void zsdata(unsigned char *buf, int length, int frameend);
int zrdata(char *buf, int length);
int zgethdr(char *hdr, int eflag);
void stohdr(long pos);
long rclhdr(char *hdr);


extern int Rxtimeout;
extern int Rxframeind;
extern int Rxtype;
extern int Rxcount;
extern char Rxhdr[4];
extern char Txhdr[4];
extern long Rxpos;
extern long Txpos;
extern int Txfcs32;
extern int Crc32t;
extern int Crc32;
extern char *Attn;
extern int Verbose;
extern int Zctlesc;
extern int z_errors;
extern long Rxbytes;
extern int fSending;
