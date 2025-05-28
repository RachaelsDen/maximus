// SPDX-License-Identifier: GPL-2.0-or-later



#include "alc.h"
#include "dv.h"
#include "prog.h"
#include "win.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void near _WinDrawPickList(VPICK *vp);
static void near _WinFixItemTop(VPICK *vp);

VPICK *_fast WinCreatePickList(VWIN *win, int row, int col, int height, int col_item,
                               int col_select, PLIST *picklist, int it_current)
{
    VPICK *vp;
    PLIST *ip;
    int max_len, x;

    if ((vp = malloc(sizeof(VPICK))) == NULL)
        return NULL;

    vp->it_current = 0;

