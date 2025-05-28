// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_rmen.c,v 1.1.1.1 2002/10/01 17:52:02 sdudley Exp $";
#pragma on(unreferenced)


#include "max_menu.h"
#include "max_msg.h"
#include "mm.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


    if (*MNU(*pam, m.dspfile) && DoDspFile(menuhelp, pam->m.flag))
        menu_lines = pam->m.menu_length;
    else
    {
            int opts_per_line = (TermWidth() + 1) / pam->m.opt_width;
            if (opts_per_line <= 0)
                opts_per_line = 1;
            menu_lines = 3 + (num_opt / opts_per_line) + !!(num_opt % opts_per_line);
        }
        else
            menu_lines = 2;
    }
}

sword Read_Menu(struct _amenu *menu, char *mname)
{
    long where, end;

    int menufile;
    word menu_items;
    size_t size, hlen;

    char mpath[PATHLEN];

    menu_items = 1;

    sprintf(mpath, "%s%s.mnu", menupath, mname);

    if ((menufile = shopen(mpath, O_RDONLY | O_BINARY)) == -1)
        return -2;

    if (read(menufile, (char *)&menu->m, sizeof(menu->m)) != sizeof(menu->m))
    {
        logit(cantread, mpath);
        close(menufile);
        quit(2);
    }

    size = sizeof(struct _opt) * menu->m.num_options;

    if ((menu->opt = malloc(size)) == NULL)
    {
        logit(mem_none);
        close(menufile);
        return -1;
    }

    if (read(menufile, (char *)menu->opt, size) != (signed)size)
    {
        logit(cantread, mpath);
        close(menufile);
        return -1;
    }

