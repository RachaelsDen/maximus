// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_sessio.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define SILT
#define NOVARS
#define NOINIT

#include "dr.h"
#include "l_attach.h"
#include "max.h"
#include "opusprm.h"
#include "prog.h"
#include "silt.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void Init_Attach_Db(char *szAttDbName);

int Parse_Session(FILE *ctlfile)
{

                ;
#if 0
      else if (eqstri(p,"filesbbs"))
      {
        getword(line,p,ctl_delim,3);

        if (eqstri(p,"download"))
        {
          getword(line,p,ctl_delim,4);
          prm.dlall_priv=Deduce_Priv(p);
        }
        else Unknown_Ctl(linenum,p);
      }
#endif
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "ask"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "phone"))
                prm.flags |= FLAG_ask_phone;
            else if (eqstri(p, "alias") || eqstri(p, "real"))
                prm.flags |= FLAG_ask_name;
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "alias"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "system"))
                prm.flags |= FLAG_alias;
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "chat"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "external"))
                Make_String(prm.chat_prog, fchar(line, ctl_delim, 3)) else if (eqstri(p, "capture"))
                    prm.flags2 |= FLAG2_CAPTURE;
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "external"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "protocol") || eqstri(p, "batchprotocol") ||
                eqstri(p, "batchexitprotocol") || eqstri(p, "exitprotocol"))
            {
                getword(line, p, ctl_delim, 3);

                if (eqstri(p, "errorlevel"))
                {
                    getword(line, p, ctl_delim, 4);
                    prm.protoexit = atoi(p);
                }
#ifdef NEVER
                else
                {
                    if (protocol_num == MAX_EXTERNP)
                    {
                        printf("\n\aError!  Too many external protocols, "
                               "line %d.\n",
                               linenum);
                        exit(1);
                    }

                    getword(line, p, ctl_delim, 2);

                    if (eqstri(p, "batchprotocol"))
                        prm.protoflag[protocol_num] |= XTERNBATCH;
                    else if (eqstri(p, "batchexitprotocol"))
                        prm.protoflag[protocol_num] |= (XTERNBATCH | XTERNEXIT);
                    else if (eqstri(p, "exitprotocol"))
                        prm.protoflag[protocol_num] |= XTERNEXIT;

                    getword(line, p, ctl_delim, 3);
                    s2 = fchar(line, ctl_delim, 4);

                    Make_Filename(prm.protocols[protocol_num], p);

                    if (s2 && *s2)
                        Make_String(prm.protoname[protocol_num],
                                    s2) else prm.protoname[protocol_num] =
                            prm.protocols[protocol_num];

                    protocol_num++;
                }
#endif
                else Unknown_Ctl(linenum, p);
            }
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "yell"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "off"))
                prm.noise_ok = FALSE;
            else
            {
                printf("\n\aWarning!  Yell events have been moved from MAX.CTL to\n"
                       "EVENTSxx.BBS.\n");
            }
        }
        else if (eqstri(p, "highest"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "msgarea"))
            {
                getword(line, p, ctl_delim, 3);
                Make_String(prm.high_msgarea, p);
            }
            else if (eqstri(p, "filearea"))
            {
                getword(line, p, ctl_delim, 3);
                Make_String(prm.high_filearea, p);
            }
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "single"))
            prm.flags2 |= FLAG2_1NAME;
        else if (eqstri(p, "protocolctl"))
        {
            getword(line, p, ctl_delim, 2);
            Make_Filename(prm.protocol_max, p);
        }
        else if (eqstri(p, "messagedata"))
        {
            getword(line, p, ctl_delim, 2);
            Make_Filename(prm.marea_name, p);
        }
        else if (eqstri(p, "filedata"))
        {
            getword(line, p, ctl_delim, 2);
            Make_Filename(prm.farea_name, p);
        }
        else if (eqstri(p, "area"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "change"))
            {
                getword(line, p, ctl_delim, 4);
                Make_String(prm.achg_keys, strupr(p));
            }
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "global"))
            prm.flags2 |= FLAG2_GLOBALHB;
        else if (eqstri(p, "rip"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "path"))
            {
                s2 = fchar(line, ctl_delim, 3);
                Make_Path(prm.rippath, s2);

                if (!direxist(strings + prm.rippath))
                    makedir(strings + prm.rippath);
            }
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "menu"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "path"))
            {
                s2 = fchar(line, ctl_delim, 3);
                Make_Path(prm.menupath, s2);

                if (!direxist(strings + prm.menupath))
                    makedir(strings + prm.menupath);
            }
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "first"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "menu"))
            {
                getword(line, p, ctl_delim, 3);
                Make_String(prm.first_menu, p);
            }
            else if (eqstri(p, "file"))
            {
                getword(line, p, ctl_delim, 4);
                Make_String(prm.begin_filearea, p);
            }
            else if (eqstri(p, "message"))
            {
                getword(line, p, ctl_delim, 4);
                Make_String(prm.begin_msgarea, p);
            }
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "compatible"))
            prm.flags |= FLAG_lbaud96;
        else if (eqstri(p, "statusline"))
            prm.flags |= FLAG_statusline;
        else if (eqstri(p, "charset"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "chinese"))
            {
                prm.charset = CHARSET_CHINESE;
                prm.flags2 |= FLAG2_GLOBALHB;
            }
            else if (eqstri(p, "swedish"))
                prm.charset = CHARSET_SWEDISH;
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "input"))
            prm.input_timeout = (byte)atoi(fchar(line, ctl_delim, 3));
        else if (eqstri(p, "save"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "directories"))
            {
                getword(line, p, ctl_delim, 3);

                for (sp = p; *sp; sp++)
                {
                    if ((*sp = (char)toupper(*sp)) >= 'A' && *sp <= 'Z')
                        BitOn(prm.drives_to_save, *sp - 'A');
                    else
                    {
                        printf("\n\aInvalid drive `%c' specified on line %d of "
                               "CTL file!\n",
                               *p, linenum);
                        Compiling(-1, NULL, NULL);
                    }
                }
            }
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "arrow"))
            ;
        else if (eqstri(p, "strict"))
            prm.flags2 |= FLAG2_STRICTXFER;
        else if (eqstri(p, "stage"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "path"))
            {
                s2 = fchar(line, ctl_delim, 3);
                Make_Path(prm.stagepath, s2);

                if (!direxist(strings + prm.stagepath))
                    makedir(strings + prm.stagepath);
            }
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "maxmsgsize"))
        {
            getword(line, p, ctl_delim, 2);

            prm.max_msgsize = atol(p);


            if (eqstri(p, "umsgids"))
                prm.flags2 |= FLAG2_UMSGID;
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "check"))
        {
            getword(line, p, ctl_delim, 2);

            if (eqstri(p, "ansi"))
                prm.flags2 |= FLAG2_CHKANSI;
            else if (eqstri(p, "rip"))
                prm.flags2 |= FLAG2_CHKRIP;
            else
                Unknown_Ctl(linenum, p);
        }
        else if (eqstri(p, "app") || eqstri(p, "application"))
            ;
        else
            Unknown_Ctl(linenum, p);

        linenum++;
    }

    linenum++;

    return 0;
}

static void Init_Attach_Db(char *szAttDbName)
{
    char temp[PATHLEN];

    strcpy(temp, szAttDbName);
    strcat(temp, ".db");
    if (!fexist(temp))
        LFAdbClose(LFAdbCreate(szAttDbName));
}
