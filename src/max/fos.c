// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: fos.c,v 1.3 2003/06/06 01:13:59 wesgarland Exp $";
#pragma on(unreferenced)


#include "keys.h"
#include "mm.h"
#include "modem.h"
#include "prog.h"
#include <conio.h>
#include <dos.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int waslocal = 0;
static int waskeyboard = 0;

int Mdm_WasLocalKey(void) { return waslocal; }

    signed int x;
    unsigned int y;
    int timer2;

#ifdef DEBUG_OUT
    int c;
#endif

    timer2 = FALSE;
    input_timeout = timerset(timeout_tics);

    for (;;)
    {

        if (waskeyboard)
        {
            waslocal = 1;
            --waskeyboard;
            return 0;
        }

                }
                else
                {
                    x &= (Highbit_Allowed() ? 0xff : 0x7f);

                    if (x == 3)
                        brk_trapped = TRUE;

                    waslocal = 1;
#ifdef DEBUG_OUT
                    c = (x & (Highbit_Allowed() ? 0xff : 0x7f));
                    break;
#else
                    return (x);
#endif
                }
            }
            else
            {
                Parse_Local(loc_getch());

                timer2 = FALSE;
                input_timeout = timerset(timeout_tics);
            }
        }
        else
        {
            y = mdm_ggetcw();

            if (y == 241 && !fLoggedOn && !fthru_yuhu)
            {
                fthru_yuhu = TRUE;
                logit(log_ft_yuhu);
            }

            waslocal = 0;
#ifdef DEBUG_OUT
            c = (y & (Highbit_Allowed() ? 0xff : 0x7f));
            break;
#else
            return (y & (Highbit_Allowed() ? 0xff : 0x7f));
#endif
        }
    }

#ifdef DEBUG_OUT
    if (dout_log)
        DebOutGotChar(c);

    return c;
#endif
}


int Mdm_kpeek_tic(word tics)
{
    static int x;
    long end;

    end = tics ? timerset(tics) : tics;

    do
    {
        if (loc_kbhit())
        {
            if (local || keyboard)
            {
                    Keyboard_Off();
                    waskeyboard = 2;
                    return 0;
                }
                else
#endif
                {
                    if (x == K_CTRLC)
                    {
{
    Check_Time_Limit(NULL, NULL);

    if (loc_kbhit())
    {
        if (local || keyboard)
        {
                Keyboard_Off();
                waskeyboard = 2;
            }
#else
            ;
#endif
        }
        else
            Parse_Local(loc_getch());
    }

    Check_For_Message(NULL, NULL);
}


word Mdm_flush_ck_tic(word tics, word checkcc, word checkcar)
{
    long end;

    end = timerset(tics);

    vbuf_flush();

    if (!local)
    {
        while (!out_empty() && (tics == 0 || !timeup(end)))
        {
            if (checkcc && halt())
            {
                mdm_dump(DUMP_ALL);
                return TRUE;
            }

            if (!in_wfc && checkcar)
                Mdm_check();

            Giveaway_Slice();
        }
    }

    return FALSE;
}


        (void)mdm_ctrlc(0);
#if defined(OS_2) || defined(NT) || defined(UNIX)
        com_XON_disable();
#elif defined(__MSDOS__)
        mdm_flow(prm.handshake_mask & ~(FLOW_TXOFF | FLOW_RXOFF));
#else
#error Unknown OS!
#endif

#if defined(NT) || defined(UNIX)
        com_HHS_enable(prm.handshake_mask);
#endif
    }
    else if (state == FLOW_OFF)
    {
        (void)mdm_ctrlc(0);
#if defined(OS_2) || defined(NT) || defined(UNIX)
        com_XON_disable();
#elif defined(__MSDOS__)
        mdm_flow(0);
#else
#error Unknown OS!
#endif

#if defined(NT) || defined(UNIX)
        com_HHS_disable(prm.handshake_mask);
#endif
    }
}
