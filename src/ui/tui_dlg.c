// SPDX-License-Identifier: GPL-2.0-or-later


#include "tui.h"
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static char *near DlgButName(HVOPT opt, char *sel_ch, word *sel_ofs);
static char *near DlgStrName(HVOPT opt, char *buf, char *sel_ch, word *sel_ofs);
static void near DlgStrGetLen(HVOPT opt, word *field_len, word *max_len);
static void near DlgRedrawStr(HVOPT opt, word *offset);
static char *near DlgStrIsValue(struct _vopt *opt);
static MenuFunction(DlgRadValue);





            if (DlgStrIsValue(menu->opt + n))
                menu->dlgsave[n] = (void *)*(char *)menu->opt[n].data;
            else
            {
                DlgStrGetLen(&menu->opt[n], NULL, &max_len);


                menu->dlgsave[n] = malloc(max_len);


word DlgAfter(HVMENU menu)
{
    word n;

    if (!menu->dlgsave)
        return 0;

    for (n = 0; n < menu->num_opt; n++)
    {
        if (dlg_ok != 1)
        {
            if (menu->opt[n].display == DlgButShow)
            {
                if (menu->opt[n].data)
                    *(void **)menu->opt[n].data = menu->dlgsave[n];
            }
            else if (menu->opt[n].display == DlgRadShow)
            {
                if (menu->opt[n].data)
                    *(void **)menu->opt[n].data = menu->dlgsave[n];
            }
            else if (menu->opt[n].display == DlgStrShow)
            {
                if (DlgStrIsValue(menu->opt + n))
                    *(char *)menu->opt[n].data = (char)menu->dlgsave[n];
                else if (menu->dlgsave[n])
                    strcpy((char *)menu->opt[n].data, (char *)menu->dlgsave[n]);
            }
        }

        if (menu->opt[n].display == DlgStrShow && menu->dlgsave[n] && !DlgStrIsValue(menu->opt + n))
        {
            free(menu->dlgsave[n]);
        }
    }

    return 0;
}


MenuFunction(DlgButShow)
{
    VWIN *win = opt->parent->win;

    char *butname;
    char sel_ch;
    byte attr, sel_attr;

    word sel_ofs, high, butlen;

    high = (opt->parent->curopt == opt);
    attr = col((byte)(high ? BUTTON_HIGH : BUTTON_STD));
    sel_attr = col((byte)(high ? BUTTON_HIGH : BUTTON_SEL));

    butname = DlgButName(opt, &sel_ch, &sel_ofs);
    butlen = strlen(butname);

    WinBox(win, opt->cy, opt->cx, opt->cy + 2, opt->cx + butlen + 3,
           high ? BORDER_DOUBLE : BORDER_SINGLE, attr);

    WinPutch(win, opt->cy + 1, opt->cx + 1, ' ', col(attr));
    WinPutstra(win, opt->cy + 1, opt->cx + 2, col(attr), butname);

    if (sel_ch)
        WinPutch(win, opt->cy + 1, opt->cx + 2 + sel_ofs, sel_ch, col(sel_attr));

    WinPutch(win, opt->cy + 1, opt->cx + 2 + butlen, ' ', col(attr));

    return 0;
}


MenuFunction(DlgButAct)
{
    char valbuf[MAX_OPTNAME_LEN];
    word val, len;
    char *s;

    for (s = opt->name; *s != ';'; s++)
        ;

    len = (word)(s - opt->name);

    memmove(valbuf, opt->name, len);
    valbuf[len] = '\0';

    val = atoi(valbuf);

    if (opt->data)
    {
        if (s[-1] == 'b')
            *(byte *)opt->data = (byte)val;
        else
            *(word *)opt->data = val;
    }

    if (dlg_ok != 0)
    {
        if (opt->parent->parent)
            _TuiCloseOldMenu(opt->parent, opt->parent->parent, opt->parent->parent->curopt);

        nextmen = opt->parent->parent;


    if (nextmen == NULL)
        return 1;

    return 0;
}

MenuFunction(DlgButCan)
{
    dlg_ok = -1;

    if (opt->parent->parent)
        _TuiCloseOldMenu(opt->parent, opt->parent->parent, opt->parent->parent->curopt);

    nextmen = opt->parent->parent;


MenuFunction(DlgButReg)
{
    HVOPT prior, next;

    prior = _TuiGetPriorOpt(opt->parent, opt);
    next = _TuiGetNextOpt(opt->parent, opt);

    _TuiMenuAddKey(opt, VKEY_UP, NULL, prior, NULL, 0, 0);
    _TuiMenuAddKey(opt, VKEY_DOWN, NULL, next, NULL, 0, 0);

    opt->hot_n_rows = 3;
    opt->hot_n_cols = (byte)(4 + strlen(DlgButName(opt, NULL, NULL)));
    return 0;
}


static char *near DlgButName(HVOPT opt, char *sel_ch, word *sel_ofs)
{
    static char butname[MAX_OPTNAME_LEN];
    char *s, *namestart, *o;

    if (sel_ch)
        *sel_ch = '\0';

    if (sel_ofs)
        *sel_ofs = 0;

    for (s = opt->name; *s != ';'; s++)
        ;

    namestart = ++s;

    for (o = butname; *s; s++)
    {
        if (*s == '~')
        {
            if (sel_ch)
                *sel_ch = s[1];

            if (sel_ofs)
                *sel_ofs = (word)(s - namestart);

            s++;
        }

        *o++ = *s;
    }

    *o = '\0';
    return butname;
}


static char *near DlgStrIsValue(struct _vopt *opt)
{
    char *p;

    if ((p = strchr(opt->name, '`')) != NULL)
        return p + 1;
    else
        return NULL;
}


static void near DlgStrRotateValue(struct _vopt *opt)
{
    char temp[20];
    char *p, *s;

    sprintf(temp, val_str, *(char *)opt->data);

    if ((p = strstr(opt->name, temp)) != NULL)
        p++;
    else
        p = strchr(opt->name, '`');

    if ((s = strchr(p, ',')) == NULL)
        s = strchr(opt->name, ',');

    if (s)
    {
        *(char *)opt->data = (char)atoi(s + 1);
        DlgStrShow(opt);
        WinSync(opt->parent->win, TRUE);
    }
}

            WinPutch(win, opt->cy, opt->cx + strlen(str) + field_len - 1, '\xaf',

    switch (key = opt->parent->laststroke)
    {
    case VKEY_LEFT:
        if (offset)
            offset--;
        break;

    case VKEY_RIGHT:
        if (offset < strlen(str))
            offset++;
        break;

    case VKEY_DEL:
        if (offset < strlen(str))
            strocpy(str + offset, str + offset + 1);
        break;

    case VKEY_HOME:
        offset = 0;
        break;

    case VKEY_END:
        offset = strlen(str);
        break;

    case K_CTRLY:
        str[offset = 0] = '\0';
        break;

    case K_BS:
        if (offset)
        {
            strocpy(str + offset - 1, str + offset);
            offset--;
        }
        break;


static void near DlgRedrawStr(HVOPT opt, word *offset)
{
    VWIN *win = opt->parent->win;

    char name[MAX_OPTNAME_LEN];
    char *str = opt->data;

    word cx = opt->cx;
    word cy = opt->cy;
    word field_len, max_len;
    word start_pos;


    DlgStrGetLen(opt, &field_len, &max_len);


    if (*offset >= field_len - 3)
        start_pos = *offset - (field_len - 3);
    else
        start_pos = 0;


MenuFunction(DlgStrAfter)
{
    WinCursorHide(opt->parent->win);
    return 0;
}


static char *near DlgStrName(HVOPT opt, char *buf, char *sel_ch, word *sel_ofs)
{
    char *start = strchr(opt->name, ';');
    char *s;
    char *out;

    *buf = '\0';

    if (sel_ofs)
        *sel_ofs = 0;

    if (sel_ch)
        *sel_ch = '\0';

    if (start == NULL)
        return buf;

    for (s = ++start, out = buf; *s; s++)
    {
        if (*s == '~')
        {
            if (sel_ofs)
                *sel_ofs = (word)(s - start);

            if (sel_ch)
                *sel_ch = s[1];
        }
        else
            *out++ = *s;
    }

    *out = '\0';

    return buf;
}



MenuFunction(DlgRadShow)
{
    VWIN *win = opt->parent->win;
    char but_txt[10];

    char *butname;
    char sel_ch;
    byte attr, sel_attr;

    word sel_ofs, high;

    high = (opt->parent->curopt == opt);
    attr = col((byte)(high ? RAD_HIGH : RAD_STD));
    sel_attr = col((byte)(high ? RAD_HIGH : RAD_SEL));

    butname = DlgButName(opt, &sel_ch, &sel_ofs);

static MenuFunction(DlgRadValue)
{
    char valbuf[MAX_OPTNAME_LEN];
    word len;
    char *s;

    for (s = opt->name; *s != ';'; s++)
        ;

    len = (word)(s - opt->name);

    memmove(valbuf, opt->name, len);
    valbuf[len] = '\0';

    return (atoi(valbuf));
}


    if (opt->data)
        *(word *)opt->data = val;


    for (par = opt->parent, o = par->opt, oend = o + par->num_opt; o < oend; o++)
        if (o->data == opt->data && o->display)
            (*o->display)(o);

    return 0;
}


    for (first = opt; first[-1].data == opt->data; first--)
        ;

    for (last = opt; last[1].data == opt->data; last++)
        ;


    for (after = opt; after[1].regist == DlgRadReg && after[1].data == opt->data; after++)
        ;

    after = _TuiGetNextOpt(opt->parent, after);

    next = (opt + 1 <= last ? opt + 1 : first);
    prior = (opt - 1 >= first ? opt - 1 : last);

                   last + 1, NULL, 0, 0);
    _TuiMenuAddKey(opt, K_TAB, NULL, after, NULL, 0, 0);
    _TuiMenuAddKey(opt, VKEY_STAB, NULL, before, NULL, 0, 0);
    return 0;
}


static unsigned near _DlgGetChkSetting(struct _vopt *opt)
{
    char *s;
    unsigned ret;

    for (s = opt->name; *s != ';'; s++)
        ;

    if (isdigit(s[-1]) || (s[-1] >= 'a' && s[-1] <= 'f'))
    {
        unsigned ofs, mask;

        sscanf(s - 1, "%x", &ofs);
        mask = 1 << (ofs - 1);

        ret = !!(*(word *)opt->data & mask);
    }
    else if (s[-1] == 'B')
        ret = !!*(byte *)opt->data;
    else
        ret = !!*(word *)opt->data;

    return ret;
}


    sprintf(but_txt, "[%c]", _DlgGetChkSetting(opt) ? 'X' : ' ');

    WinPutstra(win, opt->cy, opt->cx, col(attr), but_txt);
    WinPutstra(win, opt->cy, opt->cx + 3, col(attr), butname);

    if (sel_ch)
        WinPutch(win, opt->cy, opt->cx + 3 + sel_ofs, sel_ch, col(sel_attr));

    return 0;
}


    if (opt->data)
        _DlgSetChkSetting(opt, !_DlgGetChkSetting(opt));


MenuFunction(DlgChkReg)
{
    HVOPT prior, next;

    opt->hot_n_rows = 1;
    opt->hot_n_cols = (byte)(3 + strlen(DlgButName(opt, NULL, NULL)));

    prior = _TuiGetPriorOpt(opt->parent, opt);
    next = _TuiGetNextOpt(opt->parent, opt);

    _TuiMenuAddKey(opt, VKEY_UP, NULL, prior, NULL, 0, 0);
    _TuiMenuAddKey(opt, VKEY_DOWN, NULL, next, NULL, 0, 0);

                   _TuiGetNextOpt(opt->parent, opt), NULL, 0, 0);
    return 0;
}


MenuFunction(DlgInfReg)
{
    opt->hot_n_rows = 0;
    opt->hot_n_cols = 0;
    return 0;
}


    return ret;
}

MenuFunction(DlgIntShow)
{
    sword ret;



static MenuFunction(TuiValKeyRet1)
{
    NW(opt);
    dlg_ok = -1;
    return 1;
}


MenuFunction(TuiValHandlerWord)
{
    dlg_ok = 1;
    *(word *)opt->data = ((struct _val_list *)opt->appdatap)->value;
    return 1;
}

MenuFunction(TuiValHandlerByte)
{
    dlg_ok = 1;
    *(byte *)opt->data = (byte)((struct _val_list *)opt->appdatap)->value;
    return 1;
}


static HVMENU near _TuiValCreateMenu(struct _val_list *val_list, void *data, unsigned do_byte)
{
    HVMENU v;
    HVOPT opt;
    struct _val_list *l;

    if ((v = malloc(sizeof(struct _vmenu))) == NULL)
        return NULL;

    (void)memset(v, '\0', sizeof(struct _vmenu));
    v->start_x = -1;
    v->start_y = -1;
    v->col_win = CWHITE | _BLUE;
    v->col_bor = CYELLOW | _BLUE;
    v->col_item = CWHITE | _BLUE;
    v->col_sel = CBLACK | _WHITE;
    v->col_hot = CYELLOW | _BLUE;
    v->col_selhot = CBLACK | _WHITE;
    v->border = BORDER_DOUBLE;
    v->type = MENU_HOT | MENU_VERT | MENU_SHADOW;
    v->sizex = 0xffffu;
    v->sizey = 0xffffu;


        if (do_byte)
        {
            if (*(byte *)opt->data == (byte)l->value)
                v->def_opt = opt - v->opt;
        }
        else
        {
            if (*(word *)opt->data == l->value)
                v->def_opt = opt - v->opt;
        }
    }

    return v;
}


static void near DlgValWrap1(HVOPT opt)
{
    struct _val_list *l;


        opt->appdatap = (void *)opt->data;
        opt->data = szValTemp;


        for (l = opt->valdatap; l->name; l++)
            if (((opt->appflag & AF_BYTE) && (byte)l->value == *(byte *)opt->appdatap) ||
                ((opt->appflag & AF_BYTE) == 0 && l->value == *(word *)opt->appdatap))
            {
                strcpy(szValTemp, _TuiValName(l));
            }
    }
}


static void near DlgValWrap2(HVOPT opt)
{
    if (opt->appdatap)
    {
        opt->data = opt->appdatap;
        opt->appdatap = NULL;
    }
}


    _TuiMenuAddKey(opt, ' ', DlgValAct, NULL, NULL, 0, 0);


    h = _TuiValCreateMenu(opt->valdatap, opt->data, !!(opt->appflag & AF_BYTE));


    DlgStrName(opt, temp, NULL, NULL);


    h->start_x =
        opt->cx + opt->parent->start_x + (opt->parent->border != BORDER_NONE) + strlen(temp) + 1;


    if ((sword)h->start_y < 0)
        h->start_y = 0;


    h->parent = NULL;
    key = _TuiAddEscKey(NULL);
    key->menufn = TuiValKeyRet1;
    _TuiRegisterMenu1(h, key);

    okay = TuiExecMenu(h);
    TuiDestroyMenu(h);
    free(h);

    if (okay)

