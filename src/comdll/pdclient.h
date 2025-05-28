// SPDX-License-Identifier: GPL-2.0-or-later


BOOL PDInit(char *pipe);
int PDWrite(char *s);
void PDDeinit(void);
int PDPrintf(char *fmt, ...);
