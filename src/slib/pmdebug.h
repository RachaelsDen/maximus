// SPDX-License-Identifier: GPL-2.0-or-later


#define LB_ID 32800u

void DbgPrint(char *txt);
void _stdc DbgPrintf(char *format, ...);
void DbgBegin(HWND hwnd, HAB hab, USHORT usMaxItem, USHORT fMinimize);
void DbgEnd(void);
void DbgPrintp(char *txt);
void _stdc DbgPrintfp(char *format, ...);
