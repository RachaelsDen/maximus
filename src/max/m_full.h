// SPDX-License-Identifier: GPL-2.0-or-later


#define GotoLocText() Puts(reader_pos_text)

void DisplayMessageHeader(XMSG *msg, word *msgoffset, long msgnum, long highmsg, PMAH pmah);
void DisplayMessageNumber(XMSG *msg, long msgnum, long highmsg);
void DisplayMessageAttributes(XMSG *msg, PMAH pmah);
void DisplayShowName(char *sho_name, char *who);
void DisplayShowDate(char *sho_date, union stamp_combo *sc);
void DisplayShowAddress(char *sho_addr, NETADDR *n, PMAH pmah);
void DisplayMessageSubj(XMSG *msg, PMAH pmah);
