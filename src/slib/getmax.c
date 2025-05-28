// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <stdio.h>
#include <stdlib.h>


char *GetMaximus(int argc, char **argv, int iBadErrorlevel)
{
    char *pszMaximus = NULL;

    (void)argc;


            if (**argv == '-' && (*argv)[1] == 'p')
            {
                pszMaximus = *argv + 2;
                break;
            }

            argv++;
        }
    }

