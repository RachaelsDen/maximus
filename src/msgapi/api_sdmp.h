// SPDX-License-Identifier: GPL-2.0-or-later


static byte *sd_msg = "%s%u.msg";


#ifdef __TURBOC__
static struct _sdmdata *_junksqd;
#endif

static struct _apifuncs sdm_funcs = {
    SdmCloseArea,    SdmOpenMsg,      SdmCloseMsg,   SdmReadMsg,    SdmWriteMsg,  SdmKillMsg,
    SdmLock,         SdmUnlock,       SdmSetCurPos,  SdmGetCurPos,  SdmMsgnToUid, SdmUidToMsgn,
    SdmGetHighWater, SdmSetHighWater, SdmGetTextLen, SdmGetCtrlLen, SdmGetNextUid};
