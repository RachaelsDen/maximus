// SPDX-License-Identifier: GPL-2.0-or-later



#include "dv.h"
#include "prog.h"

#ifdef __MSDOS__

int _fast VidNumRows(void) { return Vid_NumRows; }

int _fast VidNumCols(void) { return Vid_NumCols; }

int _fast VidWhereX(void) { return Vid_Col + 1; }

int _fast VidWhereY(void) { return Vid_Row + 1; }

char _fast VidGetPage(void) { return Vid_Page; }

