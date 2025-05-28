// SPDX-License-Identifier: GPL-2.0-or-later


#include "tui.h"
#include <stdlib.h>
#include <string.h>


MenuFunction(DlgLstShow)
{
    PUIHEAD puh = (PUIHEAD)opt->data;
    PUILIST pulThis = puh->top;
    VWIN *win = opt->parent->win;
    int x, y;
    byte attr;
    int cxList, cyList;

    GetListDims(opt, &cxList, &cyList);


MenuFunction(DlgLstAct)
{
    PUIHEAD puh = (PUIHEAD)opt->data;

    if (puh->pfnSelect)
        (puh->pfnSelect)(puh->uiCur, puh->cur);

    return 0;
}

MenuFunction(DlgLstUp)
{
    PUIHEAD puh = (PUIHEAD)opt->data;

    if (puh->cur->prior)
    {
        puh->cur = puh->cur->prior;
        puh->uiCur--;


        if (puh->cur == puh->top->prior)
        {
            puh->top = puh->top->prior;
            puh->uiTop--;
        }

        (*opt->display)(opt);
    }

    return 0;
}

MenuFunction(DlgLstDown)
{
    PUIHEAD puh = (PUIHEAD)opt->data;
    PUILIST pui;
    int ofs;
    int cxList, cyList;

    if (puh->cur->next)
    {
        puh->cur = puh->cur->next;
        puh->uiCur++;

        GetListDims(opt, &cxList, &cyList);


        if (ofs >= cyList)
        {
            puh->top = puh->top->next;
            puh->uiTop++;
        }

        (*opt->display)(opt);
    }

    return 0;
}

static void near DlgLstScrollUp(HVOPT opt, PUIHEAD puh)
{
    if (puh->top->prior)
    {
        puh->top = puh->top->prior;
        puh->cur = puh->top;
        puh->uiTop--;
        puh->uiCur = puh->uiTop;
        (*opt->display)(opt);
        tdelay(100);
    }
}

static void near DlgLstScrollDown(HVOPT opt, PUIHEAD puh, int cyList)
{
    if (puh->uiTop + cyList < puh->uiNumItems)
    {
        puh->top = puh->top->next;
        puh->uiTop++;

        puh->uiCur = puh->uiTop;
        puh->cur = puh->top;


    puh->uiCur = puh->uiTop;

    for (pui = puh->top; pui && lastrow--; pui = pui->next)
        puh->uiCur++;

    if (pui && puh->cur != pui)
    {
        puh->cur = pui;
        (*opt->display)(opt);
    }


        if (timeup(ulLastClick) || puh->uiCur != uiLastSel)
        {
            ulLastClick = timerset(60L);
            uiLastSel = puh->uiCur;
        }
        else
            (*opt->menufn)(opt);
    }
}

static void near DlgLstHandleScrollbar(HVOPT opt, PUIHEAD puh, int cyList, int press)
{
    extern word lastrow;

    if (press)
    {
        if (lastrow == 0)
            DlgLstScrollUp(opt, puh);
        else if (lastrow == cyList - 1)
            DlgLstScrollDown(opt, puh, cyList);

int DlgLstMouse(HVOPT opt, int press)
{
    PUIHEAD puh = (PUIHEAD)opt->data;
    int cxList, cyList;
    extern word lastcol, lastrow;

    lastcol -= opt->cx + opt->parent->win->s_col;
    lastrow -= opt->cy + opt->parent->win->s_row;

    GetListDims(opt, &cxList, &cyList);

    if (lastcol == cxList - 1)
    {
        DlgLstHandleScrollbar(opt, puh, cyList, press);
        return 0;
    }

    if ((int)lastrow == -1)
        DlgLstScrollUp(opt, puh);
    else if (lastrow == cyList)
        DlgLstScrollDown(opt, puh, cyList);
    else
        DlgLstGotoRow(opt, puh, press);


MenuFunction(DlgLstMaybeSelect)
{
    extern word last_evt_was_mouse;

    if (last_evt_was_mouse)
        DlgLstMousePrs(opt);

    return 0;
}


    opt->ubefore = DlgLstMaybeSelect;


    GetListDims(opt, &cxList, &cyList);


    pul->txt = strdup(txt);
    pul->app_inf = app_inf;
    pul->prior = puh->tail;

    if (pul->prior)
        pul->prior->next = pul;

    pul->next = NULL;

