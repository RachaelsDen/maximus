// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __MAXED_H_DEFINED
#define __MAXED_H_DEFINED

#define MAX_LANG_max_bor
#define MAX_LANG_m_area

#include "alc.h"
#include "max_area.h"
#include "max_edit.h"
#include "max_msg.h"
#include "mm.h"
#include "prog.h"
#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

#ifdef INIT_MAXED
#define med_extern
#define MIS(x) = x
#define MLEN(x) x
#else
#define med_extern extern
#define MIS(x)
#define MLEN(x)
#endif

#define linelen(x) strlen(screen[x] + 1)

med_extern XMSG *mmsg;

med_extern word cursor_x;
med_extern word cursor_y;
med_extern word offset;
med_extern byte usrlen;

med_extern byte *update_table;
med_extern char *quotebuf;
med_extern char last_msg_attr;
med_extern char insert;
med_extern char initials[MLEN(10)];
med_extern char pos_to_be_updated;
med_extern char skip_update;
med_extern char quoting;

med_extern HMSG qmh MIS(NULL);

med_extern long *quote_pos;

#include "maxedp.h"

