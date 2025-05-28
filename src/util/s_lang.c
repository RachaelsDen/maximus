// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_lang.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define SILT
#define MAX_INCL_LANGUAGE

#include "dr.h"
#include "language.h"
#include "max.h"
#include "opusprm.h"
#include "prog.h"
#include "silt.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int Parse_Language(FILE *ctlfile)
{
    struct _gheapinf gi;
    struct _heapdata h0, h1;

    int lf;


    linenum++;

    for (;;)
    {
        if (fgets(line, MAX_LINE, ctlfile) != NULL)
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
                else if (eqstri(p, "language"))
                {
                    done_language = TRUE;

                    getword(line, p, ctl_delim, 2);

                    Make_String(prm.lang_file[prm.max_lang], p);


#ifndef UNIX
                    sprintf(temp, "%s%s.LTF", strings + prm.lang_path, p);
#else
                    sprintf(temp, "%s%s.ltf", strings + prm.lang_path, p);
#endif
                    if ((lf = shopen(temp, O_RDONLY | O_BINARY)) == -1)
                    {
                        printf("\nFatal error opening language file `%s'!\n", temp);
                        exit(1);
                    }

                    read(lf, (char *)&gi, sizeof(struct _gheapinf));

                    if (prm.max_heap < gi.max_gheap_len)
                        prm.max_heap = gi.max_gheap_len;

                    if (prm.max_ptrs < gi.max_gptrs_len)
                        prm.max_ptrs = gi.max_gptrs_len;

                    if (prm.max_lang == 0)
                    {
                        prm.max_syh_ptrs = (h1.ndefs + h1.adefs) * sizeof(HOFS);
                        prm.max_syh_len = h1.hlen;
                    }

                    prm.max_lang++;
                }
                else if (eqstri(p, "app") || eqstri(p, "application"))
                    ;
                else
                    Unknown_Ctl(linenum, p);
            }

            linenum++;
        }
        else
            break;
    }

    linenum++;

    return 0;
}
