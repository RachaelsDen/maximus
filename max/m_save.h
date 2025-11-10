/*
 * Maximus Version 3.02
 * Copyright 1989, 2002 by Lanius Corporation.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef __M_SAVE_H_DEFINED
#define __M_SAVE_H_DEFINED

#include "prog.h"     /* For word type */
#include "msgapi.h"   /* For XMSG, UMSGID, HAREA types */
#include <stdio.h>    /* For FILE type */

/* Forward declarations */
typedef struct _mahandle *PMAH;

static void near CleanupAfterSave(int chg, XMSG *msg, long save_to, PMAH pmah, char *msgarea,
                                  char *kludge, HAREA ha);
static void near Check_For_Origin(word *found_tear, char *temp);
static int near WriteErr(int opened);
static int near ProcessCC(UMSGID uid, char *line, XMSG *msg, int first);
static void near Handle_Carbon_Copies(long msgn, FILE *upfile, XMSG *msg);

#endif /* __M_SAVE_H_DEFINED */
