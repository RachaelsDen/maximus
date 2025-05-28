// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_misc.c,v 1.3 2003/06/05 23:26:49 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_init
#define MAX_LANG_max_log
#define MAX_LANG_max_main
#define MAX_LANG_f_area
#define MAX_INCL_COMMS

#include <ctype.h>
#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <share.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef UNIX
#include <errno.h>
#endif

#ifdef OS_2
#define INCL_DOS
#include "pos2.h"
#endif

#include "alc.h"
#include "display.h"
#include "max_file.h"
#include "max_menu.h"
#include "max_msg.h"
#include "prog.h"


static int win_cols = 0;
static int win_rows = 0;
static int rip_font = 0;
int loc_cols = 0;
int loc_rows = 0;
static int rip_x = 0;
static int rip_y = 0;

int RipOriginX() { return rip_x; }

int RipOriginY() { return rip_y; }

#ifndef ORACLE
void GetLocalSize()
{
    loc_rows = WinGetNumRows(win);
    loc_cols = WinGetNumCols(win);
}
#endif


int TermWidth(void)
{
    if (local)
    {
        if (loc_cols == 0)
            GetLocalSize();
        return loc_cols;
    }
    if (win_cols)
        return win_cols;
    if (hasRIP())
    {
        switch (rip_font)
        {
        case 0:
            return 80;
        case 1:
            return 90;
        case 2:
            return 80;
        case 3:
            return 90;
        case 4:
            return 40;
        }
    }
    return usr.width;
}

int TermLength(void)
{
    if (local)
    {
        if (loc_rows == 0)
            GetLocalSize();
        return loc_rows;
    }
    if (win_rows)
        return win_rows;
    if (hasRIP())
    {
        switch (rip_font)
        {
        case 0:
        case 2:

void SetTermSize(int icols, int irows)
{
    win_cols = (icols < 20 || icols > 132) ? 0 : icols;
    win_rows = (irows < 1 || irows > 200) ? 0 : irows;
}

void SetRipFont(int ifontno) { rip_font = ifontno; }

void SetRipOrigin(int ix, int iy)
{
    rip_x = ix;
    rip_y = iy;
}


void Delay(unsigned int duration)
{
    long tim;

    vbuf_flush();

    tim = timerset(duration);

    while (!timeup(tim))
        Giveaway_Slice();
}

void Giveaway_Slice(void)
{
#ifndef ORACLE
    static long cd_loss = -1L;
    static int pvar = -1;
    static long last_check = -1L;


#if defined(OS_2)
    DosSleep(1L);
#elif defined(NT)
    Sleep(1L);
#elif defined(__MSDOS__)
    if (sleeper)
        (*sleeper)();
#elif defined(UNIX)
#ifdef _REENTRANT
    sched_yield();
#else
    sleep(0);
#endif
#else
#error Unknown OS!
#endif
}

#ifndef ORACLE

static VWIN *swin = NULL;

void Draw_StatusLine(int clearit)
{

    if (!(displaymode == VIDEO_IBM && (prm.flags & FLAG_statusline)))
        return;

        WinToBottom(swin);

        if (!swin)
            return;
    }

    secs_left = ((signed long)timeoff - (signed long)time(NULL));

    if (secs_left < 0L)
        secs_left = 0L;


    if ((clearit != STATUS_FORCE && (inchat || secs_left == last)) || (bufr = malloc(81)) == NULL)
        return;

    last = secs_left;

    WinGotoXY(swin, 0, 0, FALSE);

#ifdef KEY

char *Strip_Ansi(char *s, char *area, long msgnum)
{
    extern void(pascal far * pstrip_ansi)(int len, char far *ptr, char far *far *ret, int far *got);
    char *rc = (char *)0x1296;
    int got = TRUE;

    (*pstrip_ansi)(strlen(s), s, &rc, &got);

    if (got && area && msgnum != 0)
        logit(log_got_ansi, area, msgnum);

    return rc;
}

#else

char *Strip_Ansi(char *s, char *area, long msgnum)
{
    char *orig_s;

    orig_s = s;

    while (*s)
    {
        if (*s == '\x1b')
        {
            if (area && msgnum != 0)
                logit(log_got_ansi, area, msgnum);

            *s = '<';
        }

        s++;
    }

    return orig_s;
}

char *Timestamp_Format(char *format, union stamp_combo *sstamp, char *out)
{
    struct tm localt;

    char *sfmt;
    char *p;

    if (sstamp->ldate == 0L)
    {
        *out = '\0';
        return out;
    }

    if ((sfmt = malloc(255)) == NULL)
    {
        *out = '\0';
        return out;
    }

    strcpy(p = sfmt, format);

    while (*p)
    {
        if (*p == '%')
        {
            switch (*++p)
            {

    if (localt.tm_year > 99)
        localt.tm_year %= 100;
#endif

    strftime(out, BUFLEN, sfmt, &localt);

    free(sfmt);

    return out;
}


long Add_To_Time(long seconds)
{
    unsigned long save_toff;
    long added;

    save_toff = min(timeoff, getoff);

    timeoff = min(getoff, timeoff + (unsigned long)seconds);


char *Keys(long key)
{
    static char keys[MAX_KEYS + 1];
    char *s;
    int x;

    s = keys;

    for (x = 0; x < MAX_KEYS; x++)
        if (key & (1L << x))
        {
            if (x <= 7)
                *s++ = (char)('1' + x);
            else
                *s++ = (char)('A' + (x - 8));
        }

    *s = '\0';

    return keys;
}


void _stdc FinishUp(void) { FinishUp2(TRUE); }

#ifdef __MSDOS__

void Sys_Rst(void)
{
    char restart_name[PATHLEN];

    current_line = 24;

    if (System_Restart(restart_name) == 0)
        Display_Options(restart_name, NULL);
    else
    {
        Display_File(!usr.times ? DISPLAY_PCALL : 0, NULL, restart_name);


    if (in_msghibit || in_mcheck)
        return (mah.ma.attribs & MA_HIBIT) && (usr.bits2 & BITS2_IBMCHARS);


    if (in_node_chat && (usr.bits2 & BITS2_IBMCHARS))
        return TRUE;

    return FALSE;
}

char *fancier_str(char *str)
{
    byte *s;
    byte cset[80];
    word lower = FALSE;

    s = str;

    strcpy(cset, "abcdefghijklmnopqrstuvwxyz");

    if (prm.charset == CHARSET_SWEDISH)
        strcat(cset, "}{|");


char *No_Path(char *orig)
{
    char *s;

    if ((s = strrstr(orig, pdel_only)) != NULL)
        return (s + 1);
    else
        return orig;
}


struct _arcinfo *UserAri(byte num)
{
    struct _arcinfo *ar;

    for (ar = ari; ar && --num > 0; ar = ar->next)
        ;

    return ar;
}

word CharsetChinese(byte *str, byte *ch)
{
    NW(str);
    NW(ch);


int BrowseWCMatch(char *wc, char *name)
{
    char *pwc, *pn;

    for (pwc = wc, pn = name; *pwc; pwc++)
    {
        if (tolower(*pwc) == tolower(*pn))
            pn++;
        else if (*pwc == '*')
        {
            if (*pn != pwc[1])
            {
                while (*pn && *++pn != pwc[1])
                    ;
            }
        }
        else
            break;
    }


char *Strip_Underscore(char *s)
{
    char *orig;

    orig = s;

    while (*s)
    {
        if (*s == '_')
            *s++ = ' ';
        else
            s++;
    }

    return orig;
}

void Blank_User(struct _usr *user)
{
    memset(user, '\0', sizeof(struct _usr));

    user->help = NOVICE;

    user->video = GRAPH_TTY;

    user->bits = BITS_TABS | BITS_FSR;
    user->bits2 = BITS2_IBMCHARS | BITS2_BORED | BITS2_CLS | BITS2_MORE;

    if (prm.logon_priv == PREREGISTERED)
        user->priv = 0;
    else
        user->priv = prm.logon_priv;

    user->width = 80;
    user->len = 24;

    if (offsets)
    {
        char temp[PATHLEN];

        Parse_Outside_Cmd(PRM(begin_msgarea), temp);
        SetAreaName(user->msg, temp);

        Parse_Outside_Cmd(PRM(begin_filearea), temp);
        SetAreaName(user->files, temp);
    }

    user->struct_len = sizeof(struct _usr) / 20;
    user->def_proto = PROTOCOL_NONE;
}


    memset(usr, 0, MAX_ALEN);
    strncpy(usr, newarea, MAX_ALEN - 1);
    usr[MAX_ALEN - 1] = '\0';

    return (strupr(usr));
}

char *FileDateFormat(union stamp_combo *stamp, char *temp)
{
    int mo, da, yr;

    mo = stamp->msg_st.date.mo;
    da = stamp->msg_st.date.da;
    yr = (stamp->msg_st.date.yr + 80) % 100;

    *temp = '\0';

    switch (prm.date_style)
    {
    case 0:
        sprintf(temp, date_str, mo, da, yr);
        break;

    case 1:
        sprintf(temp, date_str, da, mo, yr);
        break;

    case 2:
        sprintf(temp, date_str, yr, mo, da);
        break;

    case 3:
        sprintf(temp, datestr, yr, mo, da);
        break;
    }

    return temp;
}

word halt(void)
{
    if (brk_trapped || mdm_halt())
    {
        brk_trapped = 0;
        mdm_dump(DUMP_ALL);
        ResetAttr();


word CharsetSwedish(byte *str, byte *ch)
{
    NW(str);

    return (prm.charset == CHARSET_SWEDISH &&
            (*ch == '{' || *ch == '}' || *ch == '[' || *ch == ']' || *ch == '|' || *ch == '\\'));
}

char *MsgDte(union stamp_combo *st, char *datebuf)
{
#ifdef ORACLE
    NW(st);
    NW(datebuf);
    strcpy(datebuf, "");
#else
    char temp[BUFLEN + 1];
    strcpy(datebuf, Timestamp_Format(PRM(dateformat), st, temp));
    strcat(datebuf, " ");
    strcat(datebuf, Timestamp_Format(PRM(timeformat), st, temp));
#endif

    return datebuf;
}

void Check_Time_Limit(unsigned long *input_timeout, int *timer2)
{
    long left;

    if (finished)
        return;

    if (!local && !carrier())
        Lost_Carrier();

    if (do_timecheck && !in_file_xfer && !in_wfc && !(fLoggedOn && acsflag(CFLAGA_NOTIME)))
    {
        if ((left = timeleft()) <= 0)
            TimeLimit();
        else if (left == 2 && !sent_time_almostup)
            TimeAlmostUp();
        else if (left == 5 && !sent_time_5left && fLoggedOn)
            Time5Left();
    }

            mdm_hangup();
        }
        else
        {

#if 0
word AreaTagged(char *name)
{
  byte temp[PATHLEN];
  byte *p;
  byte ch;
  
  temp[0]='\x01';
  strcpy(temp+1, name);
  
  for (p=tma.areas; (p=strstr(p, temp)) != NULL; p++)
    if ((ch=p[strlen(temp)]) < ' ' || ch=='\x00')
      return TRUE;
  
  return FALSE;
}
#endif

#ifdef ORACLE
int CanAccessFileCommand(PFAH pfah, option opt, char letter, BARINFO *pbi)
{
    NW(pfah);
    NW(opt);
    NW(letter);
    NW(pbi);
    return FALSE;
}
#endif

void cant_open(char *fname) { logit(cantopen, fname, errno); }


    if ((p = strchr(pszKeys, '/')) != NULL)
    {

char *commaize(long ulNum, char *szBuf)
{
    char *p;
    char cSep = *thousand_sep;

    sprintf(szBuf, "%ld", ulNum);
    p = szBuf + strlen(szBuf);

    if (cSep)
    {
        while (p >= szBuf + 4)
        {
            p -= 3;
            strocpy(p + 1, p);
            *p = cSep;
        }
    }

    return szBuf;
}

char *_fast stristr_nochin(char *string, char *search)
{
    word last_found = 0;
    word strlen_search = strlen(search);

    if (string)
    {
        while (*string)
        {
            if ((tolower(*string)) == (tolower(search[last_found])))
                last_found++;
            else
            {
                if (last_found != 0)
                {
                    string -= last_found - 1;
                    last_found = 0;
                    continue;
                }
            }

            string++;

            if (last_found == strlen_search)
                return (string - last_found);
        }
    }

    return (NULL);
}
