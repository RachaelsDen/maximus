// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_parse.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define SILT
#define NOVARS
#define NOINIT

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

void Initialize_Prm(void)
{
    int x;


    memset(&prm, '\0', sizeof(struct m_pointers));

    prm.id = 'M';
    prm.version = CTL_VER;
    prm.heap_offset = sizeof(struct m_pointers);
    prm.log_mode = LOG_terse;
    prm.max_baud = 1200;
    prm.multitasker = MULTITASKER_auto;
    prm.nlver = 6;

    prm.exit_val = 5;
    prm.edit_exit = 0;
    prm.echo_exit = 0;
    prm.protoexit = 9;

    prm.flags = FLAG_autodate;
    prm.fbbs_margin = 0;

    prm.carrier_mask = 128;
    prm.handshake_mask = 0;

    prm.logon_priv = 0;
    prm.logon_time = 10;
    prm.noise_ok = TRUE;

    prm.ctla_priv = prm.seenby_priv = (word)-1;


    prm.mc_reply_priv = 0;
    prm.mc_kill_priv = 0;

    prm.pvt_priv = (word)-1;

    for (x = 0; x < 16; x++)
    {
        prm.msg_ask[x] = (word)-1;
        prm.msg_assume[x] = (word)-1;
    }

    prm.unlisted_priv = (word)-1;
    prm.unlisted_cost = 50;

    prm.msg_fromfile = (word)-1;
    prm.input_timeout = 4;

    prm.msg_localattach = (word)-1;
    prm.kill_attach_priv = (word)-1;
    prm.kill_attach = 1;
    prm.mcp_sessions = 1;
    prm.max_msgsize = UL_TRUNC;
    prm.speed_rip = (word)-1;

    prm.video = VIDEO_IBM;

    *strings = '\0';

    char temp[MAX_LINE];
    char *bufr;

    int x;

    linenum = 1;

    strcpy(ctl_name, fancy_fn(ctlname));
    fixPathMove(ctl_name);

    printf("\nParsing `%s':", ctl_name);

    if ((ctlfile = fopen(ctlname, "r")) == NULL)
    {
        printf("  \aFatal error opening `%s' for read!\n", ctlname);
        exit(1);
    }

    if ((bufr = malloc(MAX_BUFR)) != NULL)
        setvbuf(ctlfile, bufr, _IOFBF, MAX_BUFR);

    while (fgets(line, MAX_LINE, ctlfile))
    {
        Strip_Comment(line);

        if (*line)
        {
            getword(line, p, ctl_delim, 1);

            if (!*p)
                linenum++;
            else if (eqstri(p, "system"))
            {
                Compiling(LAST_SECTION, cc_section, "System");
                Parse_System(ctlfile);
                done_sys = TRUE;
            }
            else if (eqstri(p, "access"))
            {
                strcpy(p, fchar(line, ctl_delim, 2));

                Compiling(LAST_ACCESS, cc_accs, p);
                ParseAccess(ctlfile, p);
                done_access = TRUE;
            }
            else if (eqstri(p, "equipment"))
            {
                Compiling(LAST_SECTION, cc_section, "Equipment");
                Parse_Equipment(ctlfile);
                done_equip = TRUE;
            }
            else if (eqstri(p, "matrix"))
            {
                Compiling(LAST_SECTION, cc_section, "Matrix");
                Parse_Matrix(ctlfile);
                done_matrix = TRUE;
            }
            else if (eqstri(p, "colour") || eqstri(p, "color") || eqstri(p, "colours") ||
                     eqstri(p, "colors"))
            {
                Compiling(LAST_SECTION, cc_section, "Colors");
                Parse_Colours(ctlfile);
                done_colours = TRUE;
            }
            else if (eqstri(p, "session"))
            {
                Compiling(LAST_SECTION, cc_section, "Session");
                Parse_Session(ctlfile);
                done_session = TRUE;
            }
            else if (eqstri(p, "language"))
            {
                Compiling(LAST_SECTION, cc_section, "Language");
                Parse_Language(ctlfile);
                done_language = TRUE;
            }
            else if (eqstri(p, "reader"))
            {
                Compiling(LAST_SECTION, cc_section, "Reader");
                Parse_Reader(ctlfile);
            }
            else if (eqstri(p, "msgdivisionbegin"))
            {
                char acs[PATHLEN];
                char displayfile[PATHLEN];

                linenum++;


                getword(line, p, ctl_delim, 2);
                getword(line, acs, ctl_delim, 3);
                getword(line, displayfile, ctl_delim, 4);

                ParseMsgDivisionBegin(p, acs, displayfile, fchar(line, ctl_delim, 5));
            }
            else if (eqstri(p, "filedivisionbegin"))
            {
                char acs[PATHLEN];
                char displayfile[PATHLEN];

                linenum++;


                getword(line, p, ctl_delim, 2);
                getword(line, acs, ctl_delim, 3);
                getword(line, displayfile, ctl_delim, 4);

                ParseFileDivisionBegin(p, acs, displayfile, fchar(line, ctl_delim, 5));
            }
            else if (eqstri(p, "msgdivisionend"))
            {
                linenum++;
                ParseMsgDivisionEnd();
            }
            else if (eqstri(p, "filedivisionend"))
            {
                linenum++;
                ParseFileDivisionEnd();
            }
            else if (eqstri(p, "msgarea"))
            {
                linenum++;
                getword(line, p, ctl_delim, 2);
                Compiling(LAST_AREA, cc_area, p);
                ParseMsgArea(ctlfile, p);
            }
            else if (eqstri(p, "filearea"))
            {
                linenum++;
                getword(line, p, ctl_delim, 2);
                Compiling(LAST_AREA, cc_area, p);
                ParseFileArea(ctlfile, p);
            }
            else if (eqstri(p, "protocol"))
            {
                strcpy(p, fchar(line, ctl_delim, 2));
                Compiling(LAST_SECTION, cc_section, p);
                Parse_Protocol(ctlfile, p);
            }
            else if (eqstri(p, "menu"))
            {
                strcpy(p, fchar(line, ctl_delim, 2));

                Compiling(LAST_MENU, cc_menu, p);
                Parse_Menu(ctlfile, p);
            }
            else if (eqstri(p, "section"))
            {
                linenum++;

                while (fgets(line, MAX_LINE, ctlfile) != NULL)
                {
                    linenum++;

                    getword(line, p, " \t\n", 1);

                    if (eqstri(p, "end"))
                        break;
                }
            }
            else if (eqstri(p, "include"))
            {
                getword(line, p, ctl_delim, 2);
                linenum++;

                x = linenum;
                last = LAST_NONE;

                Parse_Ctlfile(p);
                strcpy(ctl_name, ctlname);

                linenum = x;
            }
            else if (eqstri(p, "max20area"))
            {
                getword(line, p, ctl_delim, 2);

                if (p[1] != ':' && p[0] != '\\' && p[0] != '/')
                {
                    strcpy(temp, strings + prm.sys_path);
                    strcat(temp, p);
                    strcpy(p, temp);
                }

                strcpy(max20area, p);

                strcpy(temp, p);
                strcat(temp, ".dat");
                Make_String(prm.adat_name, temp);

                strcpy(temp, p);
                strcat(temp, ".idx");
                Make_String(prm.aidx_name, temp);
            }
            else if (eqstri(p, "version14"))
                ;
            else if (eqstri(p, "version17"))
                ;
            else if (eqstri(p, "app") || eqstri(p, "application"))
                ;
            else
                Unknown_Ctl(linenum++, p);
        }
        else
            linenum++;
    }

    fclose(ctlfile);

    if (bufr)
        free(bufr);

    return 0;
}
