// SPDX-License-Identifier: GPL-2.0-or-later


#define MAX_LANG_f_area
#include "ffind.h"
#include "max_file.h"
#include "mm.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>


    if (*FAS(*pfah, filesbbs))
        strcpy(temp, FAS(*pfah, filesbbs));
    else
        sprintf(temp, ss, FAS(*pfah, downpath), files_bbs);

    if ((filesbbs = shfopen(temp, fopen_readb, O_RDONLY | O_BINARY | O_NOINHERIT)) == NULL)
    {
            fseek(filesbbs, offset + 1L, SEEK_SET);

            switch (Parse_Priv(filesbbs))
            {
            case SKIP_FILE:
                breakout = TRUE;
                break;


            case SKIP_NONE:
                continue;
            }
            break;

        case '@':
                strocpy(temp, temp + 1);
            }


                if (temp[0] == '\\' || temp[1] == ':' || temp[0] == '/')
                {
                    char *sp = strchr(temp, ' ');
                    char *tb = strchr(temp, '\t');
                    char *pth;


                    if (sp)
                        *sp = '\0';

                    pth = strrstr(temp, "\\/");


                for (p = temp, next = p + strlen(p); *p; p++)
                    if (isspace(*p))
                    {
                        next = p;
                        *p = '\0';
                        break;
                    }


                    if (flag)
                    {
                        if (pfah->fa.attribs & FA_FREETIME)
                            *flag |= FFLAG_NOTIME;
                        if (pfah->fa.attribs & FA_FREESIZE)
                            *flag |= FFLAG_NOBYTES;
                    }


word File_Okay(char *filename)
{
    char path[PATHLEN];
    char filespec[PATHLEN];
    FFIND *ff;
    word okay;

    okay = TRUE;


        if (*path)
            sprintf(filespec, ss, path, filename);

        ff = FindOpen(filespec, 0);

        if (!ff)
        {
            File_IsOffline(filename);
            okay = FALSE;
        }
        else if (!eqstri(filename, ff->szName))
        {
            Puts(file_no_wc);
            okay = FALSE;
        }

        FindClose(ff);
    }
    else
    {
