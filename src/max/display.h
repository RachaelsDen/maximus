// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __DISPLAY_H_DEFINED
#define __DISPLAY_H_DEFINED


    FILE *questfile;

    byte skipcr;
    byte recd_chars;
    byte automore;
    byte ck_abort;
    byte doing_filesbbs;
    byte allanswers;
    byte break_loop;

    byte scratch[MAX_FBBS_ENTRY + 10];
    byte temp[PATHLEN * 2];


} DSTK;

word _DispGetChar(DSTK *d, word inc);
void Add_Full_Path(char *src, char *dest);
word DisplayDatacode(DSTK *d);
word DisplayQuestionnaire(DSTK *d);
word DisplayMaxCode(DSTK *d);
void DispSkipLine(DSTK *d);
word Priv_Code(int ch, int action);
char *DispGetString(DSTK *d, char *str, word maxlen);
void DispGetToBlank(DSTK *d, char *str);
int Process_Files_Entry(DSTK *d, char *orig_entry);
word DispSlowGetChar(DSTK *d);

