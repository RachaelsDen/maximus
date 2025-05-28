// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_bar.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_m_area

#include "alc.h"
#include "max_area.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>
#ifdef UNIX
#include <errno.h>
#endif


static int near ParseBarPriv(char *szPriv, BARINFO *pbi)
{
    word priv;

    if (!*szPriv)
    {
        pbi->priv = usr.priv;
        pbi->keys = usr.xkeys;
        pbi->use_barpriv = FALSE;
        return TRUE;
    }

    if (eqstri(szPriv, "NoAccess"))
        priv = (word)-1;
    else
        priv = ClassAbbrevLevel(szPriv);

    pbi->priv = priv;


static int near ProcessExtBar(char *line, BARINFO *pbi)
{
    char szPriv[PATHLEN];
    char name[PATHLEN];

    getword(line, name, ctl_delim, 1);

    if (eqstri(Strip_Underscore(name), usr.name) || eqstri(name, usr.alias))
    {
        getword(line, szPriv, ctl_delim, 2);
        ParseBarPriv(szPriv, pbi);
        return TRUE;
    }

    if (eqstri(name, all))
    {
        getword(line, szPriv, ctl_delim, 2);

        if (*szPriv)
            ParseBarPriv(szPriv, pbi);

        return TRUE;
    }

    return FALSE;
}


static void near GetBarPwd(char *pwd)
{
    if (!*linebuf)
        Display_File(0, NULL, PRM(barricade));

    InputGetse(pwd, '.', bar_access);
    display_line = display_col = 1;
    cfancy_str(pwd);
}


static void near BadBarPwd(char *pwd, char *name, int tries)
{
    logit(log_bad_bar_pwd, name, pwd);

    Printf(wrong_pwd, tries);
    Putc('\n');

    if (tries == 3)
    {
        logit(l_invalid_pwd);
        Puts(invalid_pwd);
        ci_barricade();
        mdm_hangup();
    }
}


static int near ProcessBarFile(FILE *fp, BARINFO *pbi, char *name, int ext_only)
{
    char line[PATHLEN];
    char pwd[PATHLEN];
    int asked_pwd;
    int tries = 0;

    do
    {
        fseek(fp, 0L, SEEK_SET);
        asked_pwd = FALSE;

        while (fgets(line, PATHLEN, fp) != NULL)
        {
            Strip_Trailing(line, '\n');

            if (*line == '!')
            {
                if (ProcessExtBar(line + 1, pbi))
                    return (pbi->priv != (word)-1);
            }

    return FALSE;
}


int GetBarPriv(char *barfile, int is_msg, PMAH pmah, PFAH pfah, BARINFO *pbi, int ext_only)
{
    FILE *fp;
    int rc;

