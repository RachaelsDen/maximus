// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_runo.c,v 1.2 2003/06/04 23:46:22 wesgarland Exp $";
#pragma on(unreferenced)

#define MAX_LANG_max_main

#include "exec.h"
#include "max_menu.h"
#include "mm.h"
#include "prog.h"
#include <stdlib.h>
#include <string.h>

static int near Exec_Misc(PAMENU pam, struct _opt *thisopt, char *arg, char **result,
                          unsigned *puiFlag);

static option no_ed_ops[] = {display_file, xtern_dos,     xtern_run,     xtern_erlvl,   xtern_chain,
                             xtern_concur, statistics,    o_yell,        o_cls,         userlist,
                             o_version,    edit_save,     edit_abort,    edit_list,     edit_edit,
                             edit_insert,  edit_delete,   edit_continue, edit_to,       edit_from,
                             edit_subj,    edit_handling, edit_quote,    read_diskfile, nothing};


char *RunOption(struct _amenu *menu, struct _opt *thisopt, int ch, XMSG *msg, unsigned *puiFlag,
                char *menuname)
{
    char *kp, *arg, *result;
    option *op;
    int type;

    *puiFlag = 0;


        for (op = no_ed_ops; *op != nothing; op++)
            if (thisopt->type == *op)
                break;

        if (*op == nothing)
        {
            Puts(you_dont_have_access);
            return NULL;
        }
    }


    if (type >= MISC_BLOCK && type < XTERN_BLOCK)
        Exec_Misc(menu, thisopt, arg, &result, puiFlag);
    else if (type >= XTERN_BLOCK && type < MAIN_BLOCK)
        Exec_Xtern(type, thisopt, arg, &result, menuname);
    else if (type >= MAIN_BLOCK && type < MSG_BLOCK)
        Exec_Main(type, &result);
    else if (type >= MSG_BLOCK && type < FILE_BLOCK)
        Exec_Msg(type, &result, ch, arg, menuname);
    else if (type >= FILE_BLOCK && type < CHANGE_BLOCK)
        Exec_File(type, &result, menuname);
    else if (type >= CHANGE_BLOCK && type < EDIT_BLOCK)
        Exec_Change(type, &result);
    else if (type >= EDIT_BLOCK && type < CHAT_BLOCK)
        Exec_Edit(type, &result, msg, puiFlag);
    else if (type >= CHAT_BLOCK && type < END_BLOCK)
        Exec_Chat(type, &result);
    else
        logit(bad_menu_opt, type);

    return result;
}

static int near Exec_Misc(PAMENU pam, struct _opt *thisopt, char *arg, char **result,
                          unsigned *puiFlag)
{
    NW(pam);

    *result = NULL;

    switch (thisopt->type)
    {
    case display_menu:
        if (!(thisopt->flag & OFLAG_NOCLS))
        {
            if (hasRIP())
                Puts(end_rip);
            Puts(CLS);
        }

        *puiFlag |= RO_NEWMENU;
        *result = arg;
        return 0;


    case o_return:
        *puiFlag |= RO_QUIT;
        *result = "";
        return 0;

    case display_file:
        return (Display_File(0, NULL, arg));

#ifdef MEX
