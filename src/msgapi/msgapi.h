// SPDX-License-Identifier: GPL-2.0-or-later



#if !defined(MSGAPI_NO_OLD_TYPES) && !defined(_WINDOWS_)
typedef struct _msgapi MSG;
typedef struct _msgh MSGH;
#endif

#ifndef EXPENTRY
#define EXPENTRY _System
#endif

#define OS2LOADDS
#define OS2FAR

#ifndef MSGAPI_NO_OLD_TYPES
#define MSG MSG
#define MSGH MSGH
#endif
#else
#ifndef EXPENTRY
#define EXPENTRY pascal far _loadds
#endif

#define OS2LOADDS _loadds
#define OS2FAR far

#ifndef MSGAPI_NO_OLD_TYPES
#define MSG MSG far
#define MSGH MSGH far
#endif
#endif

#elif defined(NT)
#define OS2LOADDS
#define OS2FAR

#define EXPENTRY pascal
#else
#if !defined(UNIX)
#define EXPENTRY pascal
#else
#define EXPENTRY
#endif
#define OS2LOADDS
#define OS2FAR
#endif

#ifdef __WATCOMC__
#if defined(OS_2) && !defined(__FLAT__)

typedef struct _msgapi OS2FAR *HAREA;
typedef struct _msgh OS2FAR *HMSG;

typedef struct _xmsg XMSG;
typedef struct _xmsg OS2FAR *PXMSG;

typedef dword UMSGID;


#define MSGTYPE_SDM 0x01
#define MSGTYPE_SQUISH 0x02
#define MSGTYPE_ECHO 0x80


#define MOPEN_CREATE 0
#define MOPEN_READ 1
#define MOPEN_WRITE 2
#define MOPEN_RW 3



#define MSGPRIVATE 0x0001
#define MSGCRASH 0x0002
#define MSGREAD 0x0004
#define MSGSENT 0x0008
#define MSGFILE 0x0010
#define MSGFWD 0x0020
#define MSGORPHAN 0x0040
#define MSGKILL 0x0080
#define MSGLOCAL 0x0100
#define MSGHOLD 0x0200
#define MSGXX2 0x0400
#define MSGFRQ 0x0800
#define MSGRRQ 0x1000
#define MSGCPT 0x2000
#define MSGARQ 0x4000
#define MSGURQ 0x8000



#define MAX_REPLY 9

#ifndef cpp_begin
#ifdef __cplusplus
#define cpp_begin()                                                                                \
    extern "C"                                                                                     \
    {
#define cpp_end() }
#else
#define cpp_begin()
#define cpp_end()
#endif
#endif




#ifndef __netaddr_defined
#define __netaddr_defined
    struct _netaddr;
typedef struct _netaddr NETADDR;

struct _netaddr
{
    word zone;
    word net;
    word node;
    word point;
};

struct _xmsg
{
    dword attr;

    byte from[XMSG_FROM_SIZE];
    byte to[XMSG_TO_SIZE];
    byte subj[XMSG_SUBJ_SIZE];



};


cpp_begin() struct _msgapi
{
#define MSGAPI_ID 0x0201414dL




    void *apidata;
};
cpp_end()


#define MSGH_ID 0x0302484dL

#if !defined(MSGAPI_HANDLERS) && !defined(NO_MSGH_DEF)
    struct _msgh
{
    HAREA ha;
    dword id;

    dword bytes_written;
    dword cur_pos;
};
#endif

#include "api_brow.h"



#define MsgCloseArea(mh) (*(mh)->api->CloseArea)(mh)
#define MsgOpenMsg(mh, mode, n) (*(mh)->api->OpenMsg)(mh, mode, n)
#define MsgCloseMsg(msgh) ((*(((HMSG)msgh)->ha->api->CloseMsg))(msgh))
#define MsgReadMsg(msgh, msg, ofs, b, t, cl, ct)                                                   \
    (*(((HMSG)msgh)->ha->api->ReadMsg))(msgh, msg, ofs, b, t, cl, ct)
#define MsgWriteMsg(gh, a, m, t, tl, ttl, cl, ct)                                                  \
    (*(((HMSG)gh)->ha->api->WriteMsg))(gh, a, m, t, tl, ttl, cl, ct)
#define MsgKillMsg(mh, msgnum) (*(mh)->api->KillMsg)(mh, msgnum)
#define MsgLock(mh) (*(mh)->api->Lock)(mh)
#define MsgUnlock(mh) (*(mh)->api->Unlock)(mh)
#define MsgGetCurPos(msgh) (*(((HMSG)msgh)->ha->api->GetCurPos))(msgh)
#define MsgSetCurPos(msgh, pos) (*(((HMSG)msgh)->ha->api->SetCurPos))(msgh, pos)
#define MsgMsgnToUid(mh, msgn) (*(mh)->api->MsgnToUid)(mh, msgn)
#define MsgUidToMsgn(mh, umsgid, t) (*(mh)->api->UidToMsgn)(mh, umsgid, t)
#define MsgGetHighWater(mh) (*(mh)->api->GetHighWater)(mh)
#define MsgSetHighWater(mh, n) (*(mh)->api->SetHighWater)(mh, n)
#define MsgGetTextLen(msgh) (*(((HMSG)msgh)->ha->api->GetTextLen))(msgh)
#define MsgGetCtrlLen(msgh) (*(((HMSG)msgh)->ha->api->GetCtrlLen))(msgh)
#define MsgGetNextUid(ha) (*(ha)->api->GetNextUid)(ha)


#define MsgCurMsg(mh) ((mh)->cur_msg)
#define MsgNumMsg(mh) ((mh)->num_msg)
#define MsgHighMsg(mh) ((mh)->high_msg)

#define MsgGetCurMsg(mh) ((mh)->cur_msg)
#define MsgGetNumMsg(mh) ((mh)->num_msg)
#define MsgGetHighMsg(mh) ((mh)->high_msg)

#define MsgStripDebris(str) StripNasties(str)
#define MsgCreateCtrlBuf(t, n, l) CopyToControlBuf(t, n, l)
#define MsgGetCtrlToken(where, what) GetCtrlToken(where, what)
#define MsgCvt4D(c, o, d) ConvertControlInfo(c, o, d)
#define MsgCvtCtrlToKludge(ctrl) CvtCtrlToKludge(ctrl)
#define MsgRemoveToken(c, w) RemoveFromCtrl(c, w)
#define MsgGetNumKludges(txt) NumKludges(txt)
#define MsgWrite4D(msg, wf, ctrl) WriteZPInfo(msg, wf, ctrl)
#define MsgInvalidHmsg(mh) InvalidMsgh(mh)
#define MsgInvalidHarea(mh) InvalidMh(mh)

cpp_begin() sword MAPIENTRY MsgOpenApi(struct _minf OS2FAR *minf);
sword MAPIENTRY MsgCloseApi(void);

HAREA MAPIENTRY MsgOpenArea(byte OS2FAR *name, word mode, word type);
sword MAPIENTRY MsgValidate(word type, byte OS2FAR *name);
sword MAPIENTRY MsgBrowseArea(BROWSE *b);

void MAPIENTRY MsgFreeCtrlBuf(char *cbuf);
void MAPIENTRY MsgFreeCtrlToken(char *cbuf);

byte *MAPIENTRY StripNasties(byte *str);
byte OS2FAR *MAPIENTRY CopyToControlBuf(byte OS2FAR *txt, byte OS2FAR *OS2FAR *newtext,
                                        unsigned OS2FAR *length);
byte OS2FAR *MAPIENTRY GetCtrlToken(byte OS2FAR *where, byte OS2FAR *what);
void MAPIENTRY ConvertControlInfo(byte OS2FAR *ctrl, PNETADDR orig, PNETADDR dest);
byte OS2FAR *MAPIENTRY CvtCtrlToKludge(byte OS2FAR *ctrl);
void MAPIENTRY RemoveFromCtrl(byte OS2FAR *ctrl, byte OS2FAR *what);
word MAPIENTRY NumKludges(char OS2FAR *txt);
int MAPIENTRY WriteZPInfo(PXMSG msg, void(MAPIENTRY *wfunc)(byte OS2FAR *str),
                          byte OS2FAR *kludges);

void MAPIENTRY SquishSetMaxMsg(HAREA sq, dword max_msgs, dword skip_msgs, dword age);
dword MAPIENTRY SquishHash(byte OS2FAR *f);

HAREA MSGAPI SdmOpenArea(byte OS2FAR *name, word mode, word type);
sword MSGAPI SdmValidate(byte OS2FAR *name);

HAREA MSGAPI SquishOpenArea(byte OS2FAR *name, word mode, word type);
sword MSGAPI SquishValidate(byte OS2FAR *name);

sword MAPIENTRY InvalidMsgh(HMSG msgh);
sword MAPIENTRY InvalidMh(HAREA mh);

void _fast ParseNNN(char *netnode, NETADDR *pn, word all);


int far pascal farread(int handle, byte far *buf, unsigned len);
int far pascal farwrite(int handle, byte far *buf, unsigned len);

byte *_fast Address(NETADDR *a);

#ifndef MSGAPI_INIT
extern void OS2FAR *(MAPIENTRY *palloc)(size_t size);
extern void(MAPIENTRY *pfree)(void OS2FAR *ptr);
extern void OS2FAR *(MAPIENTRY *repalloc)(void OS2FAR *ptr, size_t size);

extern void far *(MAPIENTRY *farpalloc)(size_t size);
extern void(MAPIENTRY *farpfree)(void far *ptr);
extern void far *(MAPIENTRY *farrepalloc)(void far *ptr, size_t size);
#endif

cpp_end()

#endif
