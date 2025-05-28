// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __MB_QWK_H_DEFINED
#define __MB_QWK_H_DEFINED

#include "qwk.h"

static struct _len_ch
{
    long rec;
    int blocks;
} * len_chain;

static int near Create_Control_DAT(void);
static int near Create_Messages_DAT(void);
static int near QWK_Compress_Mail(BROWSE *b);
static void _stdc bprintf(char *dest, char *format, ...);
static void near Flush_Qidx(void);
static void near Flush_Len_Chain(void);
static void near Update_Length(long rec, int blocks);
static void near GenerateStupidFiles(void);
static void near FinishControlDAT(void);

