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

#ifndef __M_ATTACH_H_DEFINED
#define __M_ATTACH_H_DEFINED

#include "compiler.h"  /* For near keyword */
#include "prog.h"      /* For dword type */
#include "msgapi.h"    /* For HAREA, XMSG, UMSGID types */
#include "arc_def.h"   /* For struct _arcinfo */

/* Forward declaration for PMAH */
typedef struct _mahandle *PMAH;

static int near Make_Attach_Directory(void);
static int near Receive_Attach(void);
static struct _arcinfo *near attach_archiver();
static int near Compress_Attach_Files(PMAH pmah, char *szAttachName, dword *pulFlags);
static int near Send_Attach(int fDelok);
static int near Decompress_Attach(char *szName);
static void near Update_Attach_Db(PMAH pmah, HAREA marea, XMSG *msg, UMSGID uid, char *szFileName,
                                  dword ulFlags);

#endif /* __M_ATTACH_H_DEFINED */
