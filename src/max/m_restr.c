// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_restr.c,v 1.1.1.1 2002/10/01 17:52:49 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_m_browse

#include "max_msg.h"
#include "mm.h"

void Msg_Restrict(void) { Get_New_Date(&scRestrict, &usr.ludate, restr_prompt); }
