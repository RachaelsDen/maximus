// SPDX-License-Identifier: GPL-2.0-or-later


} DUPEID;

void UndoLastDupe(void);
void DupeFlushBuffer(void);
int IsADupe(struct _cfgarea *ar, XMSG *msg, char *ctrl, dword uid);
dword FindUpdateMessage(HAREA sq, struct _cfgarea *ar, dword msgid_hash, dword msgid_serial,
                        dword **ppmsgid_hash, dword **ppmsgid_serial);
void GetDidMsgid(DUPEID *pid, char *ctrl);
