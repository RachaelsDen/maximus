// SPDX-License-Identifier: GPL-2.0-or-later



#define SF_NEW 0x0001
#define SF_OPEN 0x0002
#define SF_WORKING 0x0004
#define SF_CLOSED 0x0008


#define QF_DO_PACK 0x0001
#define QF_DONT_PACK 0x0002


typedef struct _trklist
{
    TRK_OWNER to;
    struct _trklist *next;
} * TRKLIST;

typedef struct _excludelist
{
    char *pszName;
    struct _excludelist *next;
} * EXCLIST;

int TrackAskOwner(TRK t, TRK_OWNER to);
int TrackAddRemoteMsgToDatabase(PMAH pmah, HAREA ha, dword msgnum, char *out_actkludge);
int TrackNeedToInsertRemoteMsg(PMAH pmah, XMSG *pxmsg, char *kludges);
TRKLIST GetTrkList(void);
int TrackInsertTracking(HAREA ha, dword msgnum, XMSG *pxmsg, int modify_actrack, int add_act,
                        char *actrack, int modify_audit, char *audit, int modify_comment,
                        char *comment);
int TrackMenuReport(void);
int TrackInsertMessage(HAREA ha, dword msgnum, TRK_OWNER to, char *out_actkludge);
void TrackMakeACAUDIT(char *out, char *fmt, ...);
int IsUserExcluded(char *szName);
TRK TrackGet(void);
void TrackRelease(TRK t);
int TrackAreWeOwnerOfActrack(char *actrack, TRK_MSG_NDX *ptmn, int *pupdate_status);

