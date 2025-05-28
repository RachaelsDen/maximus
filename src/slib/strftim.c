// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include "unistr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef NO_STRFTIME

                sprintf(out, "%02d", (current_time->tm_yday) / 7);
                break;

            case 'w':
                sprintf(out, "%d", current_time->tm_wday);
                break;


                if ((scrptr = getenv("TZ")) != 0)
                {
                    scrptr[3] = 0;
                    strcpy(out, strupr(scrptr));
                }
                else
                    strcpy(string, "??T");
                break;

            case '%':
                strcpy(out, "%");
                break;
            }

            out += strlen(out);
        }
        else
            *out++ = *in;
    }

    *out = '\0';

    strcpy(string, temp);

    return (strlen(string));
}

