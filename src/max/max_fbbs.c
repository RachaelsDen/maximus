// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_fbbs.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)


#include "display.h"
#include "ffind.h"
#include "max_file.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

        psz++;

    *plSize = lsize;
    return psz;
}


                    year += 100;
                else if (year > 1900)
            }
        }
    }


    filename = malloc(MAX_FBBS_ENTRY + 1);
    line = malloc(MAX_FBBS_ENTRY + 1);
    string = malloc(MAX_FBBS_ENTRY + 1);
    filespec = malloc(MAX_FBBS_ENTRY + 1);

    if (filename == NULL || line == NULL || string == NULL || filespec == NULL)
    {
        if (string)
            free(string);

        if (line)
            free(line);

        if (filename)
            free(filename);

        return DRET_NOMEM;
    }


    if (strlen(orig_entry) >= MAX_FBBS_ENTRY - 13)
        orig_entry[MAX_FBBS_ENTRY - 13] = '\0';


    strcpy(line, orig_entry);
    getword(line, filename, " \t\n", 1);


    if (strchr(filename, PATH_DELIM))
        strcpy(filespec, filename);
    else
        sprintf(filespec, ss, FAS(fah, downpath), filename);

    wild = (strpbrk(filespec, "*?") != NULL);


    if ((d->type & DISPLAY_SEARCH) && !wild && d->beginline)
    {
        strcpy(string, line);
        cstrlwr(string);

        fSkipDisp = (stristr_nochin(string, searchfor) == NULL);
    }


    if (!fSkipDisp)
    {
        if ((d->type & DISPLAY_NEWFILES) || autodate(fah))
        {
            ff = wild ? FindOpen(filespec, 0) : FindInfo(filespec);

            isoffline = (ff == NULL);
        }
        else
        {
            isoffline = FALSE;
            ff = NULL;
        }


                    strcpy(line, orig_entry);

                    scFile = ff->scWdate;
                    scUl = ff->scCdate;
                }
            }


            for (s = filename + strlen(filename), p = filename + MAX_FN_LEN; s < p; s++)
                *s = ' ';

            filename[MAX_FN_LEN] = '\0';
            upper_fn(filename);

            if (d->type & DISPLAY_NEWFILES)
            {
                if (!d->beginline || isoffline)
                    doit = FALSE;
                else if ((doit = GEdate(&scUl, &new_date)) != FALSE)
                    matches++;
            }
            else if (d->type & DISPLAY_SEARCH)
            {
                if (!d->beginline)
                    doit = FALSE;
                else
                {

                        l = strlen(file_desc_col);
                        strocpy(p + slsf + l, p + slsf);
                        memcpy(p + slsf, file_desc_col, l);

                        if ((prm.charset & CHARSET_CHINESE) == 0)
                            for (y = 0; y < slsf; y++)
                                p[y] = (byte)toupper(p[y]);


                        l = strlen(file_found_col);
                        strocpy(p + l, p);
                        memcpy(p, file_found_col, l);

                        l = strlen(file_desc_col);
                        strocpy(filename + l, filename);
                        memcpy(filename, file_desc_col, l);


                p = firstchar(line, " \t\n", 2);


                if (!listdate(fah) && p > line + 14 && isspace(*(line + 14)))
                    p = line + 14;

                if (!p)
                    p = blank_str;


                ret = ShowFileEntry(&d->type, d->nonstop, isoffline, &scFile, &scUl, filename,
                                    ulSize, d->ck_abort, p, thisdesc, &fah);

                free(thisdesc);

                if (ret != DRET_OK)
                    break;
            }


            if (isoffline || !wild || (!autodate(fah) && (d->type & DISPLAY_NEWFILES) == 0) ||
                FindNext(ff) != 0)
            {
                break;
            }
        }

        if ((d->type & DISPLAY_NEWFILES) || autodate(fah))
            FindClose(ff);
    }


        *type &= ~DISPLAY_AREANAME;
    }

    if (DispMoreYnBreak(nstop, NULL, *type))
        return DRET_BREAK;

    Printf("%s%-*s ", ((*type & DISPLAY_SEARCH) ? file_desc_col : file_name_col), MAX_FN_LEN,
           filename);


    if (!fullformat && listdate(*pfah))
    {
        if ((*type & DISPLAY_SEARCH) && (size > 0))
            fullformat = TRUE;
        else if (isdigit(*desc))
        {
            char *p = desc + strspn(desc, "0123456789");

            {
                desc = descsize(desc, &size);
                desc = descdate(desc, pscFile);
                *pscUl = *pscFile;
                if (pscFile->ldate)
                    fullformat = TRUE;
            }

                {
                    fullformat = TRUE;
                    desc = descsize(desc, &size);
                }
            }
        }
    }

    if (!fullformat)
        Printf(file_desc_col);
    else
    {
        if (isoffline)
        {
            Printf(file_offline, file_offline_col, prm.date_style == 3 ? '\x07' : '\x09');
        }
        else
        {
            Printf("%s%7ld %s", file_size_col, size, file_date_col);

            Puts(FileDateFormat(pscFile, tmpdate));
        }

        if (ck_abort && halt())
            return DRET_BREAK;


    while (*desc)
    {
        dw = descwork;

        while (*desc && *desc != ' ' && *desc != '-')
            *dw++ = *desc++;


        if ((word)(current_col + stravtlen(descwork)) > (word)TermWidth())
        {

            while (*dw == ' ')
                dw++;


        Puts(dw);
    }

{
    int ch;

    switch (ch = fgetc(bbsfile))
    {

    default:
        if (Priv_Code(ch, 'L') == SKIP_LINE)
            return SKIP_FILE;
        else
            return SKIP_NONE;
    }
}
