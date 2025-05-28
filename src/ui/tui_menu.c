// SPDX-License-Identifier: GPL-2.0-or-later


HVMENU nextmen;


word last_evt_was_mouse = 0;


    save_appdata = opt->appdata;


    if (opt->uafter)
        (*opt->uafter)(opt);

    if (opt->uafter2)
        (*opt->uafter2)(opt);
}


    if (opt->ubefore)
        (*opt->ubefore)(opt);


char *_TuiMakeOptName(HVOPT opt, char *sel_char, word *sel_col, word minch)
{
    static char optname[MAX_OPTNAME_LEN];
    char *p, *o, *end;

    if (sel_char)
        *sel_char = '\0';

    if (sel_col)
        *sel_col = 0;

    for (p = opt->name, o = optname; *p; p++)
        if (*p == '~')
        {
            if (sel_char)
                *sel_char = p[1];

            if (sel_col)
                *sel_col = (word)(p - opt->name);
        }
        else
        {
            *o++ = *p;
        }


    if (opt->display)
    {
        (*opt->display)(opt);
        return 0;
    }


MenuFunction(_TuiMenuOptHighlight)
{
    return (_TuiDrawOption(opt, opt->parent->col_sel, opt->parent->col_selhot, TRUE));
}


MenuFunction(_TuiMenuOptNormal)
{
    return (_TuiDrawOption(opt, opt->parent->col_item, opt->parent->col_hot, TRUE));
}


sword _TuiMenuAddKey(HVOPT opt, word kb, MenuFunction((*menufn)), HVOPT newopt, HVMENU newmenu,
                     word hotspot, word flag)
{
    HVKEY key;


    key->key = kb;
    key->menufn = menufn;
    key->newopt = newopt;
    key->newmenu = newmenu;
    key->flag = flag;


    key->next = opt->keys;
    opt->keys = key;
    return 0;
}


    while (prior->regist == DlgRadReg && prior - 1 >= menu->opt && prior[-1].regist == DlgRadReg)
        prior--;

    return prior;
}


sword _TuiAddEnterFunc(HVMENU vmenu, HVOPT opt)
{
    sword ret;

    NW(vmenu);


    if (ret == 0 && opt->menu && (vmenu->type & MENU_HORIZ))
        ret = _TuiMenuAddKey(opt, VKEY_DOWN, opt->menufn, NULL, opt->menu, HOT_NONE, 0);

    return (ret);
}


sword _TuiMenuLinkOpt(HVMENU vmenu, HVOPT opt, HVOPT end_opt, HVOPT last_opt)
{
    word backkey;
    word forekey;
    HVOPT next, prior;

    NW(last_opt);
    NW(end_opt);


static word _TuiOptnameLen(char *name) { return (strlen(name) - (strchr(name, '~') != NULL)); }


    for (opt = 0; opt < MAX_VOPT && vmenu->opt[opt].name; opt++)
    {
        thisopt = &vmenu->opt[opt];


        thiswid = _TuiOptnameLen(thisopt->name);

        if (thiswid > *width)
            *width = thiswid;
    }

    return opt;
}


static void near _TuiPlaceOption(HVMENU menu, HVOPT opt)
{
    if (menu->type & MENU_VERT)
    {
        if (opt->cx == 0xffffu)
            opt->cx = menu->cx;

        if (opt->cy == 0xffffu)
            opt->cy = menu->cy++;
    }
    else if (menu->type & MENU_HORIZ)
    {
        if (opt->cx == 0xffffu)
        {
            opt->cx = menu->cx;
            menu->cx += strlen(_TuiMakeOptName(opt, NULL, NULL, 0)) + 2;
        }

        if (opt->cy == 0xffffu)
            opt->cy = menu->cy;
    }

    opt->hot_col = (byte)(opt->parent->start_x + opt->cx + (opt->parent->border != BORDER_NONE));

    opt->hot_row = (byte)(opt->parent->start_y + opt->cy + (opt->parent->border != BORDER_NONE));

    if (opt->parent->type & MENU_VERT)
        opt->hot_n_cols = (byte)(opt->parent->wid + 2);
    else
        opt->hot_n_cols = (byte)(strlen(_TuiMakeOptName(opt, NULL, NULL, 0)) + 2);

    opt->hot_n_rows = 1;
}


static sword _TuiCreateMenuKeyList(HVMENU menu, HVKEY otherkeys)
{
    HVKEY keys;
    HVOPT opt, end;
    HVOPT dummyopt;
    char sel_char;
    word did_hot;

    if ((dummyopt = malloc(sizeof(*dummyopt))) == NULL)
        return -1;


    keys = otherkeys;


    for (opt = menu->opt, end = opt + menu->num_opt; opt < end; opt++)
    {

        _TuiPlaceOption(menu, opt);


        *dummyopt = *opt;
        dummyopt->keys = keys;


            did_hot = FALSE;


            if (sel_char && (menu->type & MENU_HOT))
            {
                word mkey;

                if ((mkey = AsciiToScanCode(sel_char)) != 0)
                {
                    if (opt->regist == DlgRadReg || opt->regist == DlgButReg ||
                                       HOT_PRESS1, VKF_AFTER);

                        _TuiMenuAddKey(dummyopt, (menu->type & MENU_HOT_ONLY) ? 0xffff : sel_char,
                                       opt->menufn, opt, opt->menu, HOT_RELEASE1, VKF_AFTER);
                    }

                    did_hot = TRUE;
                }
            }

            if (!did_hot)
            {
                _TuiMenuAddKey(dummyopt, sel_char, opt->menufn, opt, opt->menu,
                               did_hot ? HOT_NONE : HOT_RELEASE1, VKF_AFTER);


static HVKEY _TuiGetSubKeys(HVMENU oldmenu, HVOPT opt)
{
    HVKEY new = NULL, key, add;
    int ky;


    for (key = opt->keys; key; key = key->next)
    {

        ky = key->key;

        if (((oldmenu->type & MENU_HORIZ) && (ky == VKEY_LEFT || ky == VKEY_RIGHT)) ||
            ((oldmenu->type & MENU_VERT) && (ky == VKEY_UP || ky == VKEY_DOWN)) || (ky & 0xff) == 0)
        {
            if ((add = malloc(sizeof(*add))) == NULL)
                return NULL;

            *add = *key;

            add->newmenu = key->newopt->menu;


    if (new)
        new->flag |= VKF_MENUKEYS;

    return new;
}


HVKEY _TuiAddEscKey(HVOPT opt)
{
    HVKEY key;

    if ((key = malloc(sizeof(*key))) == NULL)
        return NULL;

    memset(key, '\0', sizeof(*key));

    key->key = K_ESC;
    key->menufn = NULL;
    key->newopt = opt;
    key->newmenu = NULL;


sword _TuiRegisterSubordinate(HVMENU oldmenu, HVOPT opt)
{
    HVKEY key, esc;


    if (opt->menu->type & MENU_PLACE)
    {
            opt->menu->start_y = oldmenu->start_y + opt->cy + 1;
        }
    }


static void near _TuiGetWindowDim(HVMENU menu, word *cols, word *rows)
{
    if (menu->type & MENU_VERT)
    {
        *rows = menu->num_opt + (menu->border == BORDER_NONE ? 0 : 2);
        *cols = menu->wid + 2 + (menu->border == BORDER_NONE ? 0 : 2);
    }
    else if (menu->type & MENU_DIALOG)
    {
        *cols = menu->sizex;
        *rows = menu->sizey;
    }

void _TuiFindMenuStartLoc(HVMENU menu)
{
    word rows, cols;

    if (menu->start_x == 0xffffu)
        menu->start_x = ((VidNumCols() - menu->sizex) >> 1);

    if (menu->start_y == 0xffffu)
        menu->start_y = ((VidNumRows() - menu->sizey) >> 1);

    _TuiGetWindowDim(menu, &cols, &rows);

    if ((sword)(menu->start_y + rows) >= VidNumRows())
        menu->start_y = VidNumRows() - rows;

    if ((sword)(menu->start_x + cols) >= VidNumCols())
        menu->start_x = VidNumCols() - cols;

    if ((sword)menu->start_y < 0)
        menu->start_y = 0;

    if ((sword)menu->start_x < 0)
        menu->start_x = 0;
}


HVMENU _TuiRegisterMenu1(HVMENU vmenu, HVKEY keylist)
{
    HVOPT opt, last_opt, end_opt;

    if ((vmenu->num_opt = _TuiMenuCountOpts(vmenu, &vmenu->wid)) == 0)
        return NULL;

    if (vmenu->sizey == 0xffff)
        vmenu->sizey = ((vmenu->type & MENU_HORIZ) ? 1 : vmenu->num_opt) +
                       (vmenu->border != BORDER_NONE ? 2 : 0);

    if (vmenu->sizex == 0xffff)
        vmenu->sizex = ((vmenu->type & MENU_HORIZ) ? VidNumCols() : vmenu->wid) +
                       (vmenu->border != BORDER_NONE ? 2 : 0);


    vmenu->cx = 0;
    vmenu->cy = 0;


    if (_TuiCreateMenuKeyList(vmenu, keylist) == -1)
        return NULL;


        if (_TuiMenuLinkOpt(vmenu, opt, end_opt, last_opt) == -1 ||
            (opt->menu && _TuiRegisterSubordinate(vmenu, opt) == -1) ||
            _TuiAddEnterFunc(vmenu, opt) == -1)
        {
            TuiDestroyMenu(vmenu);
            return NULL;
        }


HVMENU _fast TuiRegisterMenu(HVMENU vmenu)
{
    vmenu->parent = NULL;
    vmenu->type |= def_menu_attr;

    return (_TuiRegisterMenu1(vmenu, NULL));
}


static sword near _TuiDrawMenu(HVMENU menu)
{
    HVOPT opt, end;




    if (m->curopt != m->lastopt)
        _TuiOptAfter(m->lastopt);

    if (m->after)
        (*m->after)(m);

    if (m->win)
        WinClose(m->win);
}


    if ((compar = _TuiCommonParent(oldmenu, newmenu)) != NULL)
    {
        for (m = oldmenu; m && m != compar; m = m->parent)
            m->type |= MENU__DROP;

        compar->lastopt = lastopt = compar->curopt;
        compar->curopt = curopt = (newopt ? newopt : compar->curopt);


static sword near _TuiExecOption(HVMENU menu, HVKEY key, HVMENU *nxtmen)
{
    sword ret = 0;
    HVMENU newmenu, oldnm;

    NW(menu);


            _TuiOptAfter(menu->curopt);

            return ret;
        }
    }


    newmenu = NULL;

    if (key->newopt)
    {

        if (_TuiOnThisMenu(menu, key->newopt) && !key->newmenu)
        {
            menu->lastopt = menu->curopt;
            menu->curopt = key->newopt;
        }
        else if ((newmenu = key->newopt->parent) != NULL && !key->newmenu)
        {

        }
    }


static HVKEY near _TuiGetKeyboardOption(HVMENU menu)
{
    HVKEY key;
    word ch;

    if (!khit())
        return NULL;

    ch = kgetch();


    ch = ((ch & 0xff00u) | (toupper(ch & 0xff)));


    if (menu->curopt->unknown)
        (*menu->curopt->unknown)(menu->curopt);

    return NULL;
}


static HVKEY near _TuiMouseAction(HVMENU menu, word col, word row, word mask)
{
    HVKEY key;

    for (key = menu->curopt->keys; key; key = key->next)
        if (key->hot_flag & mask)
        {
#ifdef DEBUG_PD
            WinPrintf(wscrn, "Check %s %s at %d %d %d %d\r\n", key->newopt->name,
                      key->newmenu->parent->curopt->name, key->hot_col, key->hot_n_cols,
                      key->hot_row, key->hot_n_rows);

            WinSync(wscrn, FALSE);
#endif

            if ((key->hot_flag & HOT_ANYWHERE) ||
                ((col >= key->newopt->hot_col &&
                  col < key->newopt->hot_col + key->newopt->hot_n_cols) &&
                 (row >= key->newopt->hot_row &&
                  row < key->newopt->hot_row + key->newopt->hot_n_rows)))
            {
#ifdef DEBUG_PD
                WinPrintf(wscrn, "Got %s %s (%d)\r\n", key->newopt->name,
                          key->newmenu->parent->curopt->name, mask);
                WinSync(wscrn, FALSE);
#endif

                return key;
            }
        }

    return NULL;
}


static HVKEY near _TuiGetMouseOption(HVMENU menu)
{
    word button, col, row;
    HVKEY key;

    if (!has_mouse)
        return NULL;

    MouseStatus(&button, &col, &row);


    key = NULL;


        if ((button & BUT_RIGHT) && (lastbut & BUT_RIGHT) == 0)
            key = _TuiMouseAction(menu, col, row, HOT_PRESS2);


        if (button & BUT_LEFT)
            key = _TuiMouseAction(menu, col, row, HOT_PRESS1);
    }


static sword near _TuiGetOption(HVMENU menu, HVMENU *nextmen)
{
    HVKEY key;

    WinSync(menu->win, FALSE);


    return (_TuiExecOption(menu, key, nextmen));
}


    for (m = menustk; m; m = m->next)
        _TuiCloseMenu(m);

    menustk = NULL;
}


        while (nextmen->curopt->regist == DlgInfReg)
            nextmen->curopt++;


        for (m = menustk, last = NULL; m; m = m->next)
            if (m->type & MENU__DROP)
            {
                _TuiCloseMenu(m);

                if (last)
                {
                    last->next = m->next;
                    last = m;
                }
                else
                    menustk = m->next;
            }
            else
                last = m;


        if (!_TuiMenuOnStack(nextmen, menustk))
        {
            word rows, cols;


            if (menustk)
                WinSync(menustk->win, FALSE);


            _TuiGetWindowDim(nextmen, &cols, &rows);


        if (curopt != lastopt)
        {
            _TuiOptAfter(lastopt);
            _TuiOptBefore(curopt);
        }

        nextmen->lastopt = lastopt = curopt;
    } while ((ret = _TuiGetOption(nextmen, &nextmen)) == 0);

    _TuiCloseMenuStack(menustk);

    NW(ret);

    return (dlg_ok == 1);
#endif
}

void _fast TuiSetMenuType(word attr) { def_menu_attr = attr; }

sword _fast TuiDestroyMenu(HVMENU vmenu)
{
    NW(vmenu);

    return 0;
}
