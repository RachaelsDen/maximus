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

/*# name=Direct-video routines for Maximus
 */

#include "dv.h"
#include "prog.h"

#ifdef __MSDOS__

int _fast VidGotoXY(int Col, int Row, int do_sync)
{
    Col--;
    Row--;

    if (!do_sync || (Col >= 0 && Col < Vid_NumCols && Row >= 0 && Row < Vid_NumRows))
    {
        Vid_Col = Col;
        Vid_Row = Row;

        if (do_sync)
            VidSyncCur();

        return 0;
    }
    else
        return -1;
}

#endif /* __MSDOS__ */
