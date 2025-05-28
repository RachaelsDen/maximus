// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_mcmd.c,v 1.3 2003/06/06 01:10:10 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS

#include "mm.h"
#include "prog.h"
#include <string.h>
#include <time.h>

#if defined(UNIX) || defined(NT)
#include "ntcomm.h"
#else
#define COMMAPI_VER 0
#endif

#ifndef SHORT_MDM_CMD
static char *mdm_rsp[] = {"NO CARRIER", "CONNECT", "BUSY",        "VOICE",        "RING",
                          "RRING",      "RINGING", "NO DIALTONE", "NO DIAL TONE", "DIAL TONE",
                          "ERROR",      "OK",      NULL};
#endif

int _mdm_cmd(char *command)
{
#ifndef SHORT_MDM_CMD
    timer_t expire;

    unsigned int baud, y, z;

    int ch, buflen;

    char buffer[MAX_cmdlen], temp[50];

    MDM_RESPONSE retval;
#endif

    unsigned int x;
    long timedone;

                retval = MDM_nocarrier;
                break;

                retval = MDM_busy;
                break;

                retval = MDM_ring;
                break;

                retval = MDM_nodialtone;
                break;

                retval = MDM_error;
                break;

                break;
            }
        }
    }

    mdm_dump(DUMP_INPUT);
    return retval;

#endif
}

int mdm_cmd(char *cmd)
{
#if (COMMAPI_VER > 1)
    extern HCOMM hcModem;

    if (!ComIsAModem(hcModem))
