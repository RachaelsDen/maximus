// SPDX-License-Identifier: GPL-2.0-or-later


#define INCL_PM
#include <pos2.h>

extern HAB hab;
extern HWND hwndFrame, hwndClient;

void TuiPmInit(void);
void TuiPmTerm(void);
int TuiPmEvent(HVMENU vmenu);

#define ID_RESOURCE 1


typedef struct _menuitem
{
    USHORT afStyle;
    USHORT afAttribute;
    USHORT idItem;
} MTI;

