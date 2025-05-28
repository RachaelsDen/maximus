// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_equip.c,v 1.1.1.1 2002/10/01 17:57:40 sdudley Exp $";
#pragma on(unreferenced)


#define SILT
#define NOVARS
#define NOINIT
#define MAX_INCL_COMMS

#include "dr.h"
#include "max.h"
#include "opusprm.h"
#include "prog.h"
#include "silt.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int Parse_Equipment(FILE *ctlfile)
{

        *s2;

    linenum++;

    while (fgets(line, MAX_LINE, ctlfile))
    {
        Strip_Comment(line);

        if (*line)
        {
            strcpy(temp, line);

            getword(line, p, ctl_delim, 1);

            if (!*p)
                ;
            else if (eqstri(p, "end"))
                break;
            else if (eqstri(p, "output"))
            {
                getword(line, p, ctl_delim, 2);

                if (strnicmp(p, "com", 3) == 0)
                {
                    if ((prm.com_port = atoi(p + 3) - 1) == -1 || prm.com_port > 15)
                    {
                        printf("\n\aInvalid COM port on line %d of CTL file!\n", linenum);
                        Compiling(-1, NULL, NULL);
                        prm.com_port = 0;
                    }
                }
                else if (eqstri(p, "local"))
                    prm.flags |= FLAG_keyboard;
                else
                    Unknown_Ctl(linenum, p);
            }
            else if (eqstri(p, "baud"))
            {
                getword(line, p, ctl_delim, 2);

                if (eqstri(p, "maximum"))
                {
                    if ((prm.max_baud = atoi(fchar(line, ctl_delim, 3))) == 0)
                    {
                        prm.max_baud = 1200;
                        printf("\n\aInvalid baud rate on line %d of CTL file!\n", linenum);
                        Compiling(-1, NULL, NULL);
                    }
                }
                else
                    Unknown_Ctl(linenum, p);
            }
            else if (eqstri(p, "busy"))
            {
                s2 = fchar(line, ctl_delim, 2);
                Make_String(prm.m_busy, s2);
            }
            else if (eqstri(p, "init"))
            {
                s2 = fchar(line, ctl_delim, 2);
                Make_String(prm.m_init, s2);
            }
            else if (eqstri(p, "ring"))
            {
                s2 = fchar(line, ctl_delim, 2);
                Make_String(prm.m_ring, s2);
            }
            else if (eqstri(p, "answer"))
            {
                s2 = fchar(line, ctl_delim, 2);
                Make_String(prm.m_answer, s2);
            }
            else if (eqstri(p, "connect"))
            {
                s2 = fchar(line, ctl_delim, 2);
                Make_String(prm.m_connect, s2);
            }
            else if (eqstri(p, "mask"))
            {
                getword(line, p, ctl_delim, 2);

                if (eqstri(p, "carrier"))
                {
                    if ((prm.carrier_mask = atoi(fchar(line, ctl_delim, 3))) == 0)
                    {
                        printf("\aInvalid carrier mask on line %d of CTL file!\n", linenum);
                        prm.carrier_mask = 128;
                    }
                }
                else if (eqstri(p, "handshaking"))
                {
                    getword(line, p, ctl_delim, 3);

                    if (eqstri(p, "xon"))
                        prm.handshake_mask |= FLOW_TXOFF;
                    else if (eqstri(p, "cts"))
                        prm.handshake_mask |= FLOW_CTS;
                    else if (eqstri(p, "dsr"))
                        prm.handshake_mask |= FLOW_DSR;
                    else
                        Unknown_Ctl(linenum, p);
                }
                else
                    Unknown_Ctl(linenum, p);
            }
            else if (eqstri(p, "send"))
            {
                getword(line, p, ctl_delim, 2);

                if (eqstri(p, "break"))
                    prm.flags |= FLAG_break_clr;
                else
                    Unknown_Ctl(linenum, p);
            }
            else if (eqstri(p, "no"))
            {
                getword(line, p, ctl_delim, 2);

                if (eqstr(p, "critical"))
                    prm.flags2 |= FLAG2_NOCRIT;
            }
            else if (eqstri(p, "app") || eqstri(p, "application"))
                ;
            else
                Unknown_Ctl(linenum, p);
        }

        linenum++;
    }

    linenum++;

    return 0;
}
