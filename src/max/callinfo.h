// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef CALLINFO_H_DEFINED
#define CALLINFO_H_DEFINED


#ifdef ORCACLE

#define ci_init()
#define ci_save()
#define ci_login() ;
#define ci_filename(b) (*(b) = '\0')

#define ci_paged()
#define ci_read()
#define ci_posted()
#define ci_upload(szk)
#define ci_dnload(szk)
#define ci_timeadd(m)

#define ci_carrier()
#define ci_ejectuser()
#define ci_barricade()
#define ci_paged_ah()
#define ci_dlexceed()
#define ci_expired()
#define ci_timelimit()
#define ci_nerd()

#else

extern struct callinfo sci;

void ci_init(void);
void ci_save(void);
void ci_login(void);
void ci_filename(char *buf);

#define ci_paged() (sci.paged++)
#define ci_read() (sci.read++)
#define ci_posted() (sci.posted++)
#define ci_upload(szk) (sci.filesup++, sci.kbup += (szk))
#define ci_dnload(szk) (sci.filesdn++, sci.kbdn += (szk))
#define ci_timeadd(m) (sci.added += (m))

#define ci_loggedon() (sci.flags |= CALL_LOGON)
#define ci_carrier() (sci.flags |= CALL_CARRIER)
#define ci_ejectuser() (sci.flags |= CALL_EJECTED)
#define ci_barricade() (sci.flags |= CALL_BARRPWD)
#define ci_paged_ah() (sci.flags |= CALL_PAGED_AH)
#define ci_dlexceed() (sci.flags |= CALL_DLEXCEED)
#define ci_expired() (sci.flags |= CALL_EXPIRED)
#define ci_timelimit() (sci.flags |= CALL_TIMELIMIT)
#define ci_nerd() (sci.flags |= CALL_NERD)

#endif

#endif
