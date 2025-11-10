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

#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_restr.c,v 1.1.1.1 2002/10/01 17:52:49 sdudley Exp $";
#pragma on(unreferenced)

/*# name=Set restrictions for QWK downloading
 */

#define MAX_LANG_m_browse


#define MAX_INCL_VARS     /* Include global variable declarations from max_v.h */
#define MAX_INCL_LANGUAGE /* Include language structures and definitions */
#define MAX_INCL_LANGLTH  /* Include english.lth language strings */
#define MAX_LANG_global   /* Global language strings */
#define MAX_LANG_m_area   /* Message area language strings */

#include "max_msg.h"
#include "mm.h"
#include "protod.h"  /* For function declarations */

void Msg_Restrict(void) { Get_New_Date(&scRestrict, &usr.ludate, restr_prompt); }
