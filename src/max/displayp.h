// SPDX-License-Identifier: GPL-2.0-or-later


#include "display.h"

static void near DispReadline(DSTK *d, char *str, sword limit);
static DSTK *near DispNewDstk(char *fname);
static void DisplayCleanup(DSTK *d);
static void near DisplayInitDstk(DSTK *d, byte *nonstop);
static sword near DisplayOneFile(DSTK *d);
static sword near DisplayOpenFile(DSTK *d);
static void near DisplayFixFilename(DSTK *d);
static sword near DispCloseFiles(DSTK *d, sword ret);
static sword near DisplayNormal(DSTK *d);
static sword near DisplayHandleHotkey(DSTK *d);
static word near ProcessFBBSLine(DSTK *d, word ch);
word near DCNul(DSTK *d);
word near DCEnter(DSTK *d);
word near DCCKOff(DSTK *d);
word near DCCKOn(DSTK *d);
word near DCMore(DSTK *d);
word near DCMoreOn(DSTK *d);
word near DCParseData(DSTK *d);
word near DCBell(DSTK *d);
word near DCMoreOff(DSTK *d);
word near DCQuest(DSTK *d);
word near DCPriv(DSTK *d);
word near DCAvatar(DSTK *d);
word near DCMaximus(DSTK *d);
word near DCRLE(DSTK *d);
word near DCZ(DSTK *d);
word near DCCR(DSTK *d);
word near DCLF(DSTK *d);
word near DCNormal(DSTK *d, word ch);
word near DCCls(DSTK *d);
word near DC8(DSTK *d);
word near DC9(DSTK *d);
word near DCe(DSTK *d);
word near DC11(DSTK *d);
word near DC12(DSTK *d);
word near DC13(DSTK *d);
word near DC14(DSTK *d);
word near DC15(DSTK *d);
word near DC18(DSTK *d);

static word(near *dispfn[])(DSTK *d) = {


static sword nested = 0;

#if defined(__WATCOMC__)
#pragma check_stack(on)
#endif
