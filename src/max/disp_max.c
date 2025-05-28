// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: disp_max.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)


#include "display.h"
#include "max_file.h"
#include "max_menu.h"
#include "max_msg.h"
#include "prog.h"
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int near MsgAreaControl(DSTK *d);
static int near ParseTime(DSTK *d);
static word near DispCheckExpire(DSTK *d);
static word near DispHandleKeys(DSTK *d);
static word near DispHandleXtern(DSTK *d);
static word near DispLink(DSTK *d);
static word near DispCheckBaud(DSTK *d);
static word near DispDoAPB(DSTK *d);
static word near DispComment(void);
static word near DispSetPriv(DSTK *d);
static word near DispChatAvail(DSTK *d);
static word near DispCheckHelp(DSTK *d);
static void near DispDoNodeDisp(DSTK *d);
static word near DispNodeOnline(DSTK *d);
static word near DispNodeAvailable(DSTK *d);


int AllowAttribute(PMAH pmah, int i)
{


    if (i == MSGKEY_FILE && (pmah->ma.attribs & MA_ATTACH))
        i = MSGKEY_LATTACH;


    fAllowedArea = (pmah->ma.attribs & MA_NET) || i == MSGKEY_READ || i == MSGKEY_PRIVATE ||
                   ((i == MSGKEY_LATTACH) && (pmah->ma.attribs & MA_ATTACH));

    switch (i)
    {
    case MSGKEY_LATTACH:
        if (prm.attach_base && (prm.attach_path || MAS(*pmah, attachpath)))
            priv = prm.msg_localattach;
        break;

    case MSGKEY_PRIVATE:
        if ((pmah->ma.attribs & (MA_PVT | MA_PUB)) == (MA_PVT | MA_PUB))
            priv = usr.priv;
        break;

    default:
        priv = prm.msg_ask[i];
        break;
    }

    return (fAllowedArea && (GEPriv(usr.priv, priv) || mailflag(CFLAGM_ATTRANY)));
}

word DisplayMaxCode(DSTK *d)
{
    char *p;
    union stamp_combo st;
    sword ch;

    switch (DispSlowGetChar(d))
    {
    case '\x01':
        Puts(sc_time(&usr.ludate, d->scratch));
        break;

    case '\x02':
        return DispCheckBaud(d);

    case '\x03':
        Puts(PRM(system_name));
        break;

    case '\x04':
        Puts(PRM(sysop));
        break;

    case '\x05':
        Puts(last_readln);
        break;

    case '\x06':
        ch = DispSlowGetChar(d);
        switch (ch)
        {

            if ((p = strrchr(usr.files, '.')) != NULL)
                Printf("%0.*s", p - (char *)usr.files, usr.files);
            break;

        return MsgAreaControl(d);

    case '\x0e':
        if ((ch = DispSlowGetChar(d)) == 'C')
            Printf(pu, usr.credit);
        else if (ch == 'D')
            Printf(pu, usr.debit);
        else if (ch == 'B')
            Printf(pl, (long)usr.credit - (long)usr.debit);
        break;

    case '\x10':
        Puts(usr.phone);
        break;

    case '\x12':
        Puts(usr.name);
        break;

        return DispDoAPB(d);

    case '^':
#ifdef ORACLE
        return SKIP_LINE;
#else
    {
        int fn, i = FALSE;

        FENTRY fent;

        for (fn = 0; !i && GetFileEntry(fn, &fent); ++fn)
            i = !!(fent.fFlags & FFLAG_TAG);
        return i ? SKIP_NONE : SKIP_LINE;
    }
#endif

        DispGetToBlank(d, d->scratch);

        if (task_num != (byte)atoi(d->scratch))
            return SKIP_LINE;
        break;

    {
        byte was_no_output = no_local_output;
        if (d->type & DISPLAY_NOLOCAL)
            no_local_output = FALSE;
        Msg_Checkmail(NULL);
        no_local_output = was_no_output;
    }
    break;

        DispGetToBlank(d, d->scratch);

        Convert_Star_To_Task(d->scratch);
        Parse_Outside_Cmd(d->scratch, d->temp);

        if (fexist(d->temp))
            unlink(d->temp);
        break;

    case 'e':
        DispGetToBlank(d, d->scratch);

        if (!eqstri(d->scratch, last_readln))
            return SKIP_LINE;
        break;

        strcpy(linebuf, "*");
        {
            byte was_no_output = no_local_output;
            if (d->type & DISPLAY_NOLOCAL)
                no_local_output = FALSE;
            File_Locate();
            no_local_output = was_no_output;
        }
        break;

        if (Mdm_keyp())
            return SKIP_LINE;
        break;

        DispGetToBlank(d, d->scratch);

        Convert_Star_To_Task(d->scratch);
        Parse_Outside_Cmd(d->scratch, d->temp);

        if (!fexist(d->temp))
            return SKIP_LINE;
        break;

    case 'I':
        if (((ch = DispSlowGetChar(d)) == 'L' && !local) || (ch == 'R' && local))
        {
            return SKIP_LINE;
        }
        break;


    case 'J':
        DispGetToBlank(d, d->temp);

#ifndef ORACLE
        {
            word flags = FFLAG_OK | FFLAG_THIS1 | FFLAG_TAG;
            char *p;

            if (strchr(d->temp, '%'))
                Parse_Outside_Cmd(d->temp, p = d->scratch);
            else
                p = d->temp;

            while (*p == '!' || *p == '@')
            {
                if (*p == '!')
                    flags |= FFLAG_NOBYTES;
                else
                    flags |= FFLAG_NOTIME;

                p++;
            }

            if (fexist(p))
            {
                upper_fn(p);
                AddFileEntry(p, flags, -1L);
            }
        }
#endif
        break;

        return DispLink(d);

    case 'm':
        if (!inmagnet)
            return SKIP_LINE;
        break;

    {
        byte was_no_output = no_local_output;
#ifndef ORACLE
        char *pszArgs;
#endif

        if (d->type & DISPLAY_NOLOCAL)
            no_local_output = FALSE;


        if ((pszArgs = firstchar(d->temp, " ", 2)) == NULL)
            pszArgs = "";
        else
        {
            pszArgs[-1] = 0;
        }

        if (usr.time)
            return SKIP_LINE;
        break;

    case 'r':
        return DispSetPriv(d);

    case 'S':
        if (*linebuf)
            return SKIP_LINE;
        break;

        ch = DispSlowGetChar(d) - '1';

        if (ch >= 0 && ch <= 7)
            if (UserHasKey(ch))
                UserKeyOff(ch);
            else
                UserKeyOn(ch);
        break;

        DispGetString(d, d->scratch, MAX_FBBS_ENTRY);
#ifndef ORACLE
        if (hasRIP())
            RIP_SendFile(d->scratch, FALSE);
#endif
        break;

        Parse_Outside_Cmd(DispGetString(d, d->scratch, PATHLEN), d->temp);

        if (d->questfile)
            fprintf(d->questfile, "%s\n", d->temp);
        break;

    case 'x':
        return DispCheckExpire(d);

    case 'X':
        return DispHandleXtern(d);

    case 'y':
        switch (DispSlowGetChar(d))
        {
        case 'D':
            if (usr.xp_flag & XFLAG_EXPDATE)
                FileDateFormat(&usr.xp_date, d->scratch);
            else
                strcpy(d->scratch, gen_none);

            Puts(d->scratch);
            break;

        case 'T':
            if (usr.xp_flag & XFLAG_EXPMINS)
                sprintf(d->scratch, xp_minutes, usr.xp_mins);
            else
                strcpy(d->scratch, gen_none);

            Puts(d->scratch);
            break;
        }
        break;

            if (p != NULL)
            {
                *p++ = '\0';
                filesize = atol(p);
            }
            if (RIP_HasFile(d->scratch, &filesize) == TRUE)
                return SKIP_NONE;
        }
#endif
        return SKIP_LINE;

        DispGetToBlank(d, d->scratch);
#ifndef ORACLE
        restore_tag_list(*d->scratch ? d->scratch : NULL, FALSE);
#endif
        break;
    }

    return SKIP_NONE;
}

static int near MsgAreaControl(DSTK *d)
{
    int ch = DispSlowGetChar(d);
    char *p;

    switch (ch)
    {
    case '#':
#ifdef ORACLE
        Puts("1");
#else
        Printf(pl, MsgNumMsg(sq));
#endif
        break;

    case 'd':
        if ((p = strrchr(usr.msg, '.')) != NULL)
        {
            Printf(p2s, ++p);
            break;

        char *p = strchr(msgattr_keys, DispSlowGetChar(d));
        int i = (!p) ? -1 : (p - msgattr_keys);


        if (i == MSGKEY_FILE && (mah.ma.attribs & MA_ATTACH) != 0 && (mah.ma.attribs & MA_NET) == 0)
            i = MSGKEY_LATTACH;

        return AllowAttribute(&mah, i) ? SKIP_NONE : SKIP_LINE;
    }

    case 'n':
#ifndef ORACLE
        if (((ch = DispSlowGetChar(d)) == 'N' && last_msg >= MsgHighMsg(sq)) ||
            (ch == 'R' && last_msg == 0L) || (ch == 'M' && MsgNumMsg(sq) == 0L))
            return SKIP_NONE;
        else
#endif
            return SKIP_LINE;

    case 'i':
        if (((ch = DispSlowGetChar(d)) == 'N' && ch == 'N' && direction == DIRECTION_NEXT) ||
            (ch == 'P' && direction == DIRECTION_PREVIOUS))
            return SKIP_NONE;
        else
            return SKIP_LINE;

    case 'a':
        if ((ch = DispSlowGetChar(d)) == 'L')
        {
            if ((mah.ma.attribs & (MA_NET | MA_SHARED)) == 0)
                return SKIP_NONE;
        }
        else if (ch == 'E')
        {
            if (mah.ma.attribs & MA_ECHO)
                return SKIP_NONE;
        }
        else if (ch == 'M')
        {
            if (mah.ma.attribs & MA_NET)
                return SKIP_NONE;
        }
        else if (ch == 'C')
        {
            if (mah.ma.attribs & MA_CONF)
                return SKIP_NONE;
        }
        return SKIP_LINE;

    case 'F':
#ifndef ORACLE
        if (!Msg_AttachedFiles())
#endif
            return SKIP_LINE;
    }

    return SKIP_NONE;
}

static int near ParseTime(DSTK *d)
{
    time_t longtime;
    struct tm *lt;

    int operation;
    int hh, h, mm, m;
    int cond = FALSE;

    operation = DispSlowGetChar(d);
    hh = DispSlowGetChar(d) - 1;
    mm = DispSlowGetChar(d) - 1;

    longtime = time(NULL);
    lt = localtime(&longtime);

    h = lt->tm_hour;
    m = lt->tm_min;

    switch (operation)
    {
        if ((h == hh && m < mm) || h < hh)
            cond = TRUE;
        else
            cond = FALSE;
        break;

        if (h == hh && m == mm)
            cond = FALSE;
        else
            cond = TRUE;
        break;

        if ((h == hh && m <= mm) || h < hh)
            cond = TRUE;
        else
            cond = FALSE;
        break;
    }

    return cond ? SKIP_NONE : SKIP_LINE;
}

static word near DispCheckExpire(DSTK *d)
{
    union stamp_combo sc;
    word days;
    time_t now;
    struct tm *tms;

    DispGetToBlank(d, d->scratch);
    days = atoi(d->scratch);

    if (usr.xp_flag & XFLAG_EXPDATE)
    {
        now = time(NULL);


        return ((sword)usr.xp_mins - timeonline() <= (sword)days ? SKIP_NONE : SKIP_LINE);
    }
}

static word near DispHandleKeys(DSTK *d)
{
    int type = DispSlowGetChar(d);
    sword keyn;

    char *p;

            if ((usr.xkeys & (1L << keyn)) == 0)
                return SKIP_LINE;
            break;

            usr.xkeys |= 1L << keyn;
            break;


    tlong = DispGetPos();

    free(d->filebufr);


    if ((d->filebufr = (char *)malloc(FILEBUFSIZ)) == NULL)
    {
        d->ret = DRET_NOMEM;
        return SKIP_FILE;
    }

    lseek(d->bbsfile, tlong, SEEK_SET);
    d->bufp = d->highp = d->filebufr;


static void near DispDoNodeDisp(DSTK *d)
{
    byte tid;
    char *p;

    DispGetString(d, d->scratch, MAXLEN);
    Parse_Outside_Cmd(d->scratch, d->temp);
    getword(d->temp, d->scratch, ctl_delim, 1);


    if ((p = firstchar(d->temp, ctl_delim, 2)) == NULL)
        return;

        return SKIP_NONE;
    }

    if (((ch = DispSlowGetChar(d)) == 'A' && !avail) || (ch == 'N' && avail))
        return SKIP_LINE;

    return SKIP_NONE;
}

static word near DispCheckHelp(DSTK *d)
{
    sword hlp, ch;

    hlp = (d->type & DISPLAY_MENUHELP) ? menuhelp : usr.help;

    if (((ch = DispSlowGetChar(d)) == 'N' && hlp != NOVICE) || (ch == 'R' && hlp != REGULAR) ||
        (ch == 'E' && hlp != EXPERT) || (ch == 'H'))
    {
        return SKIP_LINE;
    }

    return SKIP_NONE;
}

