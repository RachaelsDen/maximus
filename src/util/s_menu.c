// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_menu.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
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
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int tsearch(char *key, struct _st base[], unsigned int num);
static word near InsertMenuHeap(char *s);
static void near Init_Opt(struct _opt *opt);
static int near Parse_Option(option opt, char *line, struct _opt *thisopt, int menufile);
static void near Init_Menu(void);
static void near Free_Menu(void);
static option near IsOpt(char *token);

#define MENUHEAPLEN 4096

static char *menuheap;
static int menuofs;

int Parse_Menu(FILE *ctlfile, char *name)
{
    struct _opt thisopt;

        write(menufile, (char *)&menu, sizeof(struct _menu));
    }

    while (fgets(line, MAX_LINE, ctlfile) != NULL)
    {
        Strip_Comment(line);

        if (!*line)
        {
            linenum++;
            continue;
        }

        priv_word = 2;

        getword(line, keyword, ctl_delim, 1);

    TryAgain:

        if (!*keyword)
            ;
        else if (eqstri(keyword, "end"))
            break;
        else if (!do_menus)
            ;
        else if ((opt = IsOpt(keyword)) != 0)
        {
            Parse_Option(opt, line, &thisopt, menufile);
            menu.num_options++;
            Init_Opt(&thisopt);
        }
        else if (eqstri(keyword, "menuheader") || eqstri(keyword, "silentmenuheader"))
        {
            if (eqstri(keyword, "silentmenuheader"))
                menu.flag |= MFLAG_SILENT;

            getword(line, keyword, ctl_delim, 2);

            if (eqstri(keyword, "none"))
                menu.header = HEADER_NONE;
            else if (eqstri(keyword, "message"))
                menu.header = HEADER_MESSAGE;
            else if (eqstri(keyword, "file"))
                menu.header = HEADER_FILE;
            else if (eqstri(keyword, "change"))
                menu.header = HEADER_CHANGE;
            else if (eqstri(keyword, "chat"))
                menu.header = HEADER_CHAT;
            else
                Unknown_Ctl(linenum, keyword);
        }
        else if (eqstri(keyword, "title"))
            menu.title = InsertMenuHeap(fchar(line, ctl_delim, 2));
        else if (eqstri(keyword, "menufile"))
        {
            getword(line, temp, ctl_delim, 2);
            Add_Filename(temp);

            menu.dspfile = InsertMenuHeap(temp);

            x = 3;

            do
            {
                getword(line, temp, ctl_delim, x++);

                if (*temp)
                {
                    if (eqstri(temp, "novice"))
                        menu.flag |= MFLAG_MF_NOVICE;
                    else if (eqstri(temp, "regular"))
                        menu.flag |= MFLAG_MF_REGULAR;
                    else if (eqstri(temp, "expert"))
                        menu.flag |= MFLAG_MF_EXPERT;
                    else if (eqstri(temp, "rip"))
                        menu.flag |= MFLAG_MF_RIP;
                    else
                        Unknown_Ctl(linenum, temp);
                }
            } while (*temp);

#ifdef UNIX
            fixPathMove(temp);
#endif
            menu.headfile = InsertMenuHeap(temp);

            x = 3;

            do
            {
                getword(line, temp, ctl_delim, x++);

                if (*temp)
                {
                    if (eqstri(temp, "novice"))
                        menu.flag |= MFLAG_HF_NOVICE;
                    else if (eqstri(temp, "regular"))
                        menu.flag |= MFLAG_HF_REGULAR;
                    else if (eqstri(temp, "expert"))
                        menu.flag |= MFLAG_HF_EXPERT;
                    else if (eqstri(temp, "rip"))
                        menu.flag |= MFLAG_HF_RIP;
                    else
                        Unknown_Ctl(linenum, keyword);
                }
            } while (*temp);


            Unknown_Ctl(linenum, keyword);
        }

        linenum++;
    }

    linenum++;

    if (do_menus)
    {
        char *s;

        lseek(menufile, 0L, SEEK_SET);

        write(menufile, (char *)&menu, sizeof(struct _menu));
        lseek(menufile, 0L, SEEK_END);
        write(menufile, menuheap, menuofs);
        close(menufile);


int tsearch(char *key, struct _st base[], unsigned int num)
{
    int x, lastx = -1, lasthi, lastlo;

    char *s, *t;

    lasthi = num;
    lastlo = 0;

    for (;;)
    {
        x = ((lasthi - lastlo) >> 1) + lastlo;

        if (lastx == x)
            return -1;

        lastx = x;

        for (s = key, t = base[x].token; tolower(*s) == tolower(*t); s++, t++)
            if (!*s)

    thisopt->priv = InsertMenuHeap(temp);


    thisopt->name = InsertMenuHeap(temp);


    if (do_menus)
        write(menufile, (char *)thisopt, sizeof(struct _opt));

    return 0;
}

static void near Init_Opt(struct _opt *opt)
{
    memset(opt, '\0', sizeof(struct _opt));

    opt->type = nothing;
    opt->areatype = AREATYPE_ALL;
    opt->priv = 0;
}

static word near InsertMenuHeap(char *s)
{
    int len = strlen(s);
    word oldofs;

    if (menuofs + len >= MENUHEAPLEN)
    {
        printf("Error!  Menu file too big (option '%s')\n", s);
        exit(1);
    }

    strcpy(menuheap + menuofs, s);
    oldofs = menuofs;
    menuofs += strlen(s) + 1;
    return oldofs;
}

static option near IsOpt(char *token)
{
    int x;

    if ((x = tsearch(token, silt_table, silt_table_size)) != -1)
        return silt_table[x].opt;
    else
        return 0;
}
