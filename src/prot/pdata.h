// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __WIN_H_DEFINED
#include "win.h"
#endif

void ZmStatInit(void);
void ZmStatHdr(int fSend, int iHdr, char *szHdr, unsigned long ulHdr);
void ZmStatFile(char *szPath, unsigned long ulSize, unsigned fCrc32);
void ZmStatData(unsigned long ulPos, unsigned uiBlockLen, unsigned fCrc32);
unsigned XferWinOpen(sword protocol, unsigned doing_dl);
void XferWinClose(void);
void XferWinClear(void);
void XferTxtNewFile(byte *filename, long size, word protocol, unsigned doing_dl);
void XferWinNewFile(char *filename, long size);
void ZmStatus(unsigned crc32, unsigned block_size, long size, long sent, time_t start,
              char *status);
int mdm_getct(unsigned timeout);
void XmSendCAN(void);
void XmStatus(unsigned flag, unsigned do_crc, long sent, time_t start, sword protocol, long size,
              long last_ack, unsigned n_err, long block);
void unique_name(char *fname);
void ThruStart(void);
void ThruSetStartOffset(long lStartOfs);
void ThruLog(long lTotalBytes);

