// SPDX-License-Identifier: GPL-2.0-or-later


#include "max_file.h"
#include "max_menu.h"
#include "max_msg.h"
#include "mm.h"
#include <ctype.h>


int CanAccessMsgCommand(PMAH pmah, option opt, char letter)
{
    char *menuname = PMAS(pmah, menuname);
    struct _opt *popt, *eopt;
    struct _amenu am;

    if (!*menuname)
        menuname = mnu_msg;

    Initialize_Menu(&am);

    if (Read_Menu(&am, menuname))
    {
        logit(cantread, menuname);
        return FALSE;
    }

    letter = toupper(letter);


    for (popt = am.opt, eopt = popt + am.m.num_options; popt < eopt; popt++)
    {
        if (popt->type == opt && (!letter || toupper(am.menuheap[popt->name]) == letter))
        {
            if (OptionOkay(&am, popt, FALSE, PMAS(pmah, barricade), pmah, &fah, menuname))
                break;
        }
    }

    Free_Menu(&am);


    for (popt = am.opt, eopt = popt + am.m.num_options; popt < eopt; popt++)
    {
        if (popt->type == opt && (!letter || toupper(am.menuheap[popt->name]) == letter))
        {
            if (OptionOkay(&am, popt, FALSE, PFAS(pfah, barricade), &mah, pfah, menuname))
                break;
        }
    }

    if (pbi && pbi->use_barpriv)
    {
        usr.priv = biSave.priv;
        usr.xkeys = biSave.keys;
    }

    Free_Menu(&am);

