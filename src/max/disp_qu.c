// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: disp_qu.c,v 1.1.1.1 2002/10/01 17:50:52 sdudley Exp $";
#pragma on(unreferenced)


#include "display.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void near DisplayQuestIgnore(DSTK *d, sword until)
{
    sword ch;

    for (;;)
    {

word DisplayQuestionnaire(DSTK *d)
{
    time_t longtime;
    byte *p = NULL;
    long offset;
    sword ch, rr;

    static char was_no_local_output;

    switch (ch = DispSlowGetChar(d))
    {
        if (hasRIP())
        {
            was_no_local_output = no_local_output;
            no_local_output = 1;
        }
        if (hasRIP())
            no_local_output = was_no_local_output;
        break;

        if ((ch == 'E' && usr.video == GRAPH_TTY) || (ch == '^' && usr.video != GRAPH_TTY))
            DisplayQuestIgnore(d, 'e');
        break;

        DispGetToBlank(d, d->scratch);

        do
        {
            Input(d->temp, INPUT_LB_LINE, 0, MAXLEN, NULL);

            if (d->allanswers)
            {
                for (p = d->temp; *p; p++)
                    if (isalnum(*p) || *p >= 0x7f)
                        break;

                if (*p == '\0')
                {
                    Puts(tryagain);
                    Clear_KBuffer();
                }
            }
        } while (d->allanswers && *p == '\0');

        strcpy(last_readln, d->temp);

        display_line = 1;

        if (d->questfile && *d->temp)
            fprintf(d->questfile, "%s: %s\n", cstrupr(d->scratch), d->temp);
        break;

    case 'o':
        if (d->questfile)
        {
            fprintf(d->questfile, "* %s\t%s\t", usrname, usr.city);


            fputs(d->scratch, d->questfile);
        }
        break;

        DispGetToBlank(d, d->scratch);
        Save_Directory2(d->scratch);
        break;

        return SKIP_FILE;


            if (lastmenu)
            {
                Puts(tryagain);
                Clear_KBuffer();
            }

            Input_Char(CINPUT_DISPLAY | CINPUT_ACCEPTABLE | CINPUT_LASTMENU |
                           (d->allanswers ? CINPUT_ALLANSWERS : 0) | CINPUT_DUMP,
                       d->scratch);
        } while (d->allanswers && (lastmenu == '\0' || lastmenu == ' ' || lastmenu == '|') &&
                 !strchr(d->scratch, '|'));
        break;

        d->skipcr = FALSE;

        lseek(d->bbsfile, 0L, SEEK_SET);
        d->bufp = d->highp = d->filebufr;
        break;

        d->skipcr = FALSE;

        DispGetToBlank(d, d->scratch);

        sscanf(d->scratch, "%5ld", &offset);

        lseek(d->bbsfile, offset, SEEK_SET);
        d->bufp = d->highp = d->filebufr;
        break;
    }

    return SKIP_NONE;
}
