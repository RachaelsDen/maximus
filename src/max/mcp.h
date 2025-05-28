// SPDX-License-Identifier: GPL-2.0-or-later


#ifdef __WATCOMC__
#ifdef __FLAT__
#pragma library("..\lib\mcp32.lib");
#else
#pragma library("..\lib\mcp.lib");
#endif
#endif


typedef struct
{
    USHORT dispatch_code;
    int(CALLBACK *f)(PVOID);
} DISPATCH;

typedef struct
{
    BYTE bHeight;
    BYTE bWidth;
    BYTE bCurRow;
    BYTE bCurCol;
    BYTE bCurAttr;
} VIO_DUMP_HDR;





int APIENTRY McpGetMsg(HPIPE hp, PVOID pv, USHORT *pusSize, USHORT usMaxSize);
int APIENTRY McpPeekMsg(HPIPE hp, PVOID pv, USHORT *pusSize, USHORT usMaxSize);
int APIENTRY McpDispatchMsg(PVOID pv, USHORT usSize, DISPATCH *dt, PVOID pvParm);
int APIENTRY McpSendMsg(HPIPE hp, USHORT usType, BYTE *pbMsg, USHORT cbMsg);
int APIENTRY McpOpenPipe(char *pszPipeName, HPIPE *php);
void APIENTRY McpClosePipe(HPIPE hp);
