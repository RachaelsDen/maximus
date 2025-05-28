// SPDX-License-Identifier: GPL-2.0-or-later


sword _fast MouseOpen(void);
void _fast MouseShow(void);
void _fast MouseHide(void);
void _fast MouseStatus(word *button, word *col, word *row);
void _fast MouseSetPos(word col, word row);
void _fast MouseGetPress(word button, word *state, word *count, word *col, word *row);
void _fast MouseGetRelease(word button, word *state, word *count, word *col, word *row);
void _fast MouseSetRange(word col, word row, word n_col, word n_row);
void _fast MouseSetSoftCursor(word scrmask, word curmask);
void _fast MouseSetEvent(word evtmask, void(far *evtproc)(void));
void _fast MouseClose(void);
void _fast MouseSetMickey(word xmickey, word ymickey);
void _fast MouseFlush(void);

extern word has_mouse;

