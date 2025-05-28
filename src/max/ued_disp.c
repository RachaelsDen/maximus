// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: ued_disp.c,v 1.1.1.1 2002/10/01 17:53:20 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_ued
#define MAX_INCL_COMMS

#include "ued_disp.h"
#include "mm.h"
#include "prog.h"
#include "ued.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int near MKD(void);


static char *near Expire_By(struct _usr *user)
{
    if (user->xp_flag & XFLAG_EXPDATE)
        return ued_xp_date;
    else if (user->xp_flag & XFLAG_EXPMINS)
        return ued_xp_mins;
    else
        return ued_xp_none;
}

static char *near Expire_Action(struct _usr *user, char *temp)
{
    if (user->xp_flag & XFLAG_DEMOTE)
    {
        char ptmp[16];

        sprintf(temp, ued_xp_demote, privstr(user->xp_priv, ptmp));
        return temp;
    }

    if (user->xp_flag & XFLAG_AXE)
        return ued_xp_hangup;

    return ued_xp_none;
}

static char *near Expire_At(struct _usr *user, char *temp)
{
    if (user->xp_flag & XFLAG_EXPDATE)
    {
        FileDateFormat(&user->xp_date, temp);
        return temp;
    }

    if (user->xp_flag & XFLAG_EXPMINS)
    {
        sprintf(temp, ued_xp_minutes, user->xp_mins);
        return temp;
    }

    return ued_xp_none;
}


static char *near DOB(struct _usr *pusr, char *out)
{
    switch (prm.date_style)
    {
    default:
        sprintf(out, date_str, pusr->dob_month, pusr->dob_day, pusr->dob_year % 100);
        break;

    case 1:
        sprintf(out, date_str, pusr->dob_day, pusr->dob_month, pusr->dob_year % 100);
        break;

    case 2:
    case 3:
        sprintf(out, prm.date_style == 2 ? date_str : datestr, pusr->dob_year % 100,
                pusr->dob_month, pusr->dob_day);
    }

    return out;
}


char *Show_Pwd(char *pwd, char *ret, char echo)
{
    char *s, *p;

    for (s = pwd, p = ret; *s; s++)
        if (echo)
            *p++ = echo;
        else
            *p++ = *s;

    *p = '\0';

    return ret;
}
