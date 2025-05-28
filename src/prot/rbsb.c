// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: rbsb.c,v 1.1.1.1 2002/10/01 17:54:40 sdudley Exp $";
#pragma on(unreferenced)

#include "pdata.h"
#include "zsjd.h"


int mode(int m)
{
    dlogit(("@Zmodem mode %d", m));

    switch (m)
    {
    case 3:
        Mdm_Flow(FLOW_PARTIAL_OFF);
        break;

    case 2:
        Mdm_Flow(FLOW_NO_CCK);
        break;

    case 1:
        Mdm_Flow(FLOW_OFF);
        break;

    case 0:
        Mdm_Flow(FLOW_ON);
        break;

    default:
        return ERROR;
    }

    return OK;
}

void sendbrk(void)
{
    Delay(100);
    mdm_break(100);
}
