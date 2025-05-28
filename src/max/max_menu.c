// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_menu.c,v 1.1.1.1 2002/10/01 17:51:51 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_main
#define MAX_INCL_COMMS

#include "max_menu.h"
#include "display.h"
#include "max_file.h"
#include "max_msg.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *pszMenuName = NULL;

char *CurrentMenuName(void) { return pszMenuName ? pszMenuName : blank_str; }

static void near ProcessMenuName(char *name, char *menu_name)
{
    pszMenuName = menu_name;

    if (strchr(name, '%'))
        Parse_Outside_Cmd(name, menu_name);
    else
        strcpy(menu_name, name);

    Convert_Star_To_Task(menu_name);
    menu_name[MAX_MENUNAME - 1] = 0;
}

int DoDspFile(byte help, word flag)
{
    return ((help == NOVICE && (flag & MFLAG_MF_NOVICE)) ||
            (help == REGULAR && (flag & MFLAG_MF_REGULAR)) ||
            (help == EXPERT && (flag & MFLAG_MF_EXPERT)) || (hasRIP() && (flag & MFLAG_MF_RIP)));
}

static int near DoHdrFile(byte help, word flag)
{
    return ((help == NOVICE && (flag & MFLAG_HF_NOVICE)) ||
            (help == REGULAR && (flag & MFLAG_HF_REGULAR)) ||
            (help == EXPERT && (flag & MFLAG_HF_EXPERT)) || (hasRIP() && (flag & MFLAG_HF_RIP)));
}


static void near ShowMenuHeader(PAMENU pam, byte help, int first_time)
{
    char *filename;

    filename = MNU(*pam, m.headfile);

    if (!*filename || !DoHdrFile(help, pam->m.flag))
    {
        if (hasRIP())
            Putc('\n');
        else
            Puts("\n\n");
    }
    else
    {

            sprintf(temp, "%s %d", filename + 1, first_time);

            Mex(temp);
        }
        else if (Display_File(DISPLAY_HOTMENU | DISPLAY_MENUHELP, NULL, filename) == -1)
        {
            logit(cantfind, filename);
        }
    }
}

static void near ShowMenuFile(PAMENU pam, char *filename)
{
    if (!*linebuf &&
        Display_File(hasRIP() ? DISPLAY_MENUHELP : (DISPLAY_HOTMENU | DISPLAY_MENUHELP), NULL,
                     filename) == -1)
    {
        logit(cantfind, filename);
    }

    if (pam->m.hot_colour != -1)
    {
        Printf(attr_string, pam->m.hot_colour & 0x7f);
        Puts(pam->m.hot_colour > 0x7f ? BLINK : blank_str);
    }
}


static void near ShowMenuCommand(PAMENU pam, struct _opt *popt, int eol, int first_opt, byte help)
{
    char *optname = pam->menuheap + popt->name;
    int nontty;

    switch (help)
    {

static void near ShowMenuCanned(PAMENU pam, byte help, char *title, char *menuname)
{
    struct _opt *popt, *eopt;
    int opts_per_line, num_opts, num_shown;
    int first_opt = TRUE;


static void near ShowMenuBody(PAMENU pam, byte help, char *title, char *menuname)
{
    char *filename = MNU(*pam, m.dspfile);


static void near ShowOption(int ch, byte help, word flag)
{
    if ((usr.bits & BITS_HOTKEYS) && *linebuf == 0)
    {
        if (!hasRIP() || !DoDspFile(help, flag))
            Putc(ch == '|' ? ' ' : ch);
        Putc('\n');
    }
}


        if (ch > 255 && pam->menuheap[popt->name] == '`')
            scan = atoi(pam->menuheap + popt->name + 1) << 8;

        if ((upper_ch == toupper(pam->menuheap[popt->name]) || ch == scan) && upper_ch != '`' &&
            OptionOkay(pam, popt, FALSE, NULL, &mah, &fah, menuname))
        {

            if (popt->type != read_individual && !shown)
            {
                shown = TRUE;
                ShowOption(ch, *pbHelp, pam->m.flag);
            }

            if (pam->m.flag & MFLAG_RESET)
                RipReset();

            *pbHelp = usr.help;
            *piRanOpt = TRUE;

            next_menu_char = -1;

            p = RunOption(pam, popt, upper_ch, msg, &flag, menuname);

            if (flag & RO_NEWMENU)
            {
                *piSameMenu = FALSE;
                strcpy(name, p);
            }

            if (flag & RO_QUIT)
                return -1;

            if (flag & RO_SAVE)
                return 1;
        }
    }

    if (!*piRanOpt && ch != '|' && ch != 0x7f && ch <= 255)
    {
        ShowOption(ch, *pbHelp, pam->m.flag);
        Printf(dontunderstand, upper_ch);
        mdm_dump(DUMP_INPUT);
        ResetAttr();
        Clear_KBuffer();
        vbuf_flush();

        switch (*pbHelp)
        {
        case REGULAR:
            *pbHelp = NOVICE;
            break;
        case EXPERT:
            *pbHelp = REGULAR;
            break;
        }
    }

    return 0;
}


    if (*old_name)
    {
        if (eqstri(old_name, menu_name))
        {
            if (fah.heap && !eqstri(FAS(fah, menuname), menu_name) &&
                !eqstri(MAS(mah, menuname), menu_name))
            {
                strcpy(menu_name, old_replace);
                strcpy(name, menu_name);
                *old_name = *old_replace = 0;
                rc = TRUE;
            }
        }
        else
        {

            *old_name = *old_replace = 0;
        }
    }


    if (fah.heap && eqstri(menu_name, FAS(fah, menureplace)) &&
        !eqstri(menu_name, FAS(fah, menuname)))
    {
        strcpy(old_name, FAS(fah, menuname));

        if (!*old_replace)
            strcpy(old_replace, FAS(fah, menureplace));

        strcpy(name, FAS(fah, menuname));
        ProcessMenuName(name, menu_name);
        rc = TRUE;
    }


    if (lam && mah.bi.use_barpriv)
        if (lam->biOldPriv.use_barpriv)
        {
            if (!eqstri(CurrentMenuName(), MAS(mah, barricademenu)))
                ExitMsgAreaBarricade();
        }
        else
            EnterMsgAreaBarricade();

    if (laf && fah.bi.use_barpriv)
        if (laf->biOldPriv.use_barpriv && fah.heap)
        {
            if (!eqstri(CurrentMenuName(), FAS(fah, barricademenu)))
                ExitFileAreaBarricade();
        }
        else
            EnterFileAreaBarricade();

    return rc;
}

static int near RiteArea(int areatype, int attrib)
{
    if ((attrib & MA_NET) && (areatype & AREATYPE_MATRIX) == 0)
        return FALSE;

    if ((attrib & MA_ECHO) && (areatype & AREATYPE_ECHO) == 0)
        return FALSE;

    if ((attrib & MA_CONF) && (areatype & AREATYPE_CONF) == 0)
        return FALSE;

    if ((attrib & (MA_SHARED | MA_NET)) == 0 && (areatype & AREATYPE_LOCAL) == 0)
        return FALSE;

    return TRUE;
}

static int near MagnEtOkay(struct _opt *opt)
{
    if (inmagnet)
    {
        switch (opt->type)
        {
        case edit_save:
        case edit_abort:
        case edit_list:
        case edit_edit:
        case edit_insert:
        case edit_delete:
        case edit_quote:
        case display_file:
            return FALSE;
        }
    }

    return TRUE;
}


static int near OverridePrivOkay(struct _amenu *menu, struct _opt *popt, PMAH pmah, PFAH pfah,
                                 char *menuname)
{
    int i;
    char name = toupper(menu->menuheap[popt->name]);
    char szNewName[PATHLEN];

    if (pmah)
    {
        for (i = 0; i < pmah->ma.num_override; i++)
        {
            Parse_Outside_Cmd(pmah->heap + pmah->pov[i].menuname, szNewName);

            if (pmah->pov[i].opt == popt->type && eqstri(szNewName, menuname) &&
                (!pmah->pov[i].name || toupper(pmah->pov[i].name) == name))
            {
                return PrivOK(pmah->heap + pmah->pov[i].acs, FALSE);
            }
        }
    }

    if (pfah)
    {
        for (i = 0; i < pfah->fa.num_override; i++)
        {
            Parse_Outside_Cmd(pfah->heap + pfah->pov[i].menuname, szNewName);

            if (pfah->pov[i].opt == popt->type && eqstri(szNewName, menuname) &&
                (!pfah->pov[i].name || toupper(pfah->pov[i].name) == name))
            {
                return PrivOK(pfah->heap + pfah->pov[i].acs, FALSE);
            }
        }
    }

    return PrivOK(menu->menuheap + popt->priv, FALSE);
}

int OptionOkay(struct _amenu *menu, struct _opt *popt, int displaying, char *barricade, PMAH pmah,
               PFAH pfah, char *menuname)
{
    BARINFO biSave;
    BARINFO bi;
    int rc;

    bi.use_barpriv = FALSE;


    if (barricade && *barricade && GetBarPriv(barricade, FALSE, pmah, pfah, &bi, TRUE) &&
        bi.use_barpriv)
    {

        usr.priv = bi.priv;
        usr.xkeys = bi.keys;
    }

    rc = (OverridePrivOkay(menu, popt, pmah, pfah, menuname) &&
          RiteArea(popt->areatype, pmah->ma.attribs) && MagnEtOkay(popt) &&
          (local ? (popt->flag & OFLAG_UREMOTE) == 0 : (popt->flag & OFLAG_ULOCAL) == 0) &&
          (!displaying || (popt->flag & OFLAG_NODSP) == 0) &&
          (hasRIP() ? (popt->flag & OFLAG_NORIP) == 0 : (popt->flag & OFLAG_RIP) == 0));


int Display_Options(char *first_name, XMSG *msg)
{

    next_menu_char = -1;


    do
    {

        if (Read_Menu(&menu, menu_name) != 0)
        {
            cant_open(menu_name);
            quit(2);
        }

        same_menu = first_time = TRUE;
        help = usr.help;

        do
        {
            int ran_opt;
            unsigned ch;


                if (next_menu_char == -1)
                    ch = GetMenuResponse(title);
                else
                {
                    ch = next_menu_char;
                    next_menu_char = -1;
                }


                if (usr.help != orig_help)
                    help = usr.help;


                ProcessMenuName(name, menu_name);

                if (EnterMenu(name, menu_name))
                {
                    ran_opt = TRUE;
                    same_menu = FALSE;
                }

            } while (!ran_opt && ch > 255 && opt_rc == 0);

            first_time = FALSE;
        } while (same_menu && opt_rc == 0);
    } while (opt_rc == 0);

    Free_Menu(&menu);

    return opt_rc == -1 ? ABORT : SAVE;
}
