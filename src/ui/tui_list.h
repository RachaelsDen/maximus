// SPDX-License-Identifier: GPL-2.0-or-later


MenuFunction(DlgLstShow);
MenuFunction(DlgLstAct);
MenuFunction(DlgListUp);
MenuFunction(DlgListDown);
MenuFunction(DlgLstReg);

#define LISTBOX_COL (CYELLOW | _BLUE)
#define LISTBOX_SELECT_COL (CWHITE | _BLACK)
#define LISTBOX_SCROLL_COL (CLCYAN | _BLUE)
#define DLG_LST(name, x, y, dt)                                                                    \
    {name, DlgLstAct, dt, NULL, NULL, NULL, x, y, DlgLstShow, NULL, DlgLstReg},

