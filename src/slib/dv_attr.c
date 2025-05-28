// SPDX-License-Identifier: GPL-2.0-or-later



#include "dv.h"
#include "prog.h"

#ifdef __MSDOS__

char _fast VidGetAttr(void) { return Vid_Attribute; }

void _fast VidSetAttr(char Attribute) { Vid_Attribute = Attribute; }

