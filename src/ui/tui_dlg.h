// SPDX-License-Identifier: GPL-2.0-or-later


extern word dlg_ok;


word DlgBefore(HVMENU menu);
word DlgAfter(HVMENU menu);

MenuFunction(DlgButAct);
MenuFunction(DlgButOk);
MenuFunction(DlgButCan);
MenuFunction(DlgButShow);
MenuFunction(DlgButReg);

MenuFunction(DlgStrShow);
MenuFunction(DlgStrEdit);
MenuFunction(DlgStrReg);

MenuFunction(DlgIntShow);
MenuFunction(DlgIntEdit);
MenuFunction(DlgIntReg);

MenuFunction(DlgRadAct);
MenuFunction(DlgRadShow);
MenuFunction(DlgRadReg);

MenuFunction(DlgChkAct);
MenuFunction(DlgChkShow);
MenuFunction(DlgChkReg);

MenuFunction(DlgInfReg);

MenuFunction(DlgAddrShow);
MenuFunction(DlgAddrEdit);
MenuFunction(DlgAddrReg);

MenuFunction(DlgValShow);
MenuFunction(DlgValAct);
MenuFunction(DlgValReg);

#define STD_DIALOG(name, sx, sy, bor, type, xwid, ywid)                                            \
    struct _vmenu(name)[] = {sx, sy, MENU_COLS, bor,                                               \
                             (type) | MENU_DIALOG | MENU_HOT | MENU_HOT_ONLY, xwid, ywid,          \
                             DlgBefore, DlgAfter, NULL, {

#define TIT_DIALOG(name, sx, sy, bor, type, xwid, ywid, tit)                                       \
    struct _vmenu(name)[] = {sx, sy, MENU_COLS, bor,                                               \
                             (type) | MENU_DIALOG | MENU_HOT | MENU_HOT_ONLY, xwid, ywid,          \
                             DlgBefore, DlgAfter, tit, {

#define DEF_DIALOG(name, sx, sy, cw, cb, ci, cs, ch, csh, bor, type, xwid, ywid)                   \
    struct _vmenu(name)[] = {sx, sy, cw, cb, ci, cs, ch, csh, bor,                                 \
                             (type) | MENU_DIALOG | MENU_HOT | MENU_HOT_ONLY, xwid, ywid,          \
                             DlgBefore, DlgAfter, NULL, {

#define DLG_STR(name, x, y, dt)                                                                    \
    {name, NULL, dt, NULL, NULL, NULL, x, y, DlgStrShow, DlgStrEdit, DlgStrReg},
#define DLG_INT(name, x, y, dt)                                                                    \
    {name, NULL, dt, NULL, NULL, NULL, x, y, DlgIntShow, DlgIntEdit, DlgIntReg},
#define DLG_INV(name, x, y, dt, v)                                                                 \
    {name, NULL, dt, NULL, NULL, NULL, x, y, DlgIntShow, DlgIntEdit, DlgIntReg, v},
#define DLG_INV2(name, x, y, dt, v, p)                                                             \
    {name, NULL, dt, NULL, NULL, NULL, x, y, DlgIntShow, DlgIntEdit, DlgIntReg, v, 0,              \
     0,    0,    0,  0,    0,    0,    0, 0, 0,          0,          0,         p},
#define DLG_BYT(name, x, y, dt)                                                                    \
    {name, NULL, dt, NULL, NULL, NULL, x, y, DlgIntShow, DlgIntEdit, DlgIntReg,                    \
     0,    0,    0,  0,    0,    0,    0, 0, 0,          0,          AF_BYTE},
#define DLG_LNG(name, x, y, dt)                                                                    \
    {name, NULL, dt, NULL, NULL, NULL, x, y, DlgIntShow, DlgIntEdit, DlgIntReg,                    \
     0,    0,    0,  0,    0,    0,    0, 0, 0,          0,          AF_LONG},
#define DLG_LNV(name, x, y, dt, v)                                                                 \
    {name, NULL, dt, NULL, NULL, NULL, x, y, DlgIntShow, DlgIntEdit, DlgIntReg,                    \
     v,    0,    0,  0,    0,    0,    0, 0, 0,          0,          AF_LONG},
#define DLG_LNV2(name, x, y, dt, v, p)                                                             \
    {name, NULL, dt, NULL, NULL, NULL, x, y, DlgIntShow, DlgIntEdit, DlgIntReg, v, 0,              \
     0,    0,    0,  0,    0,    0,    0, 0, AF_LONG,    0,          0,         p},
#define DLG_ADDR(name, x, y, dt)                                                                   \
    {name, NULL, dt, NULL, NULL, NULL, x, y, DlgAddrShow, DlgAddrEdit, DlgAddrReg},
#define DLG_VSW(name, x, y, dt, vs)                                                                \
    {name, DlgValAct, dt, NULL, NULL, NULL, x, y, DlgValShow, NULL, DlgValReg, 0,                  \
     0,    0,         0,  0,    0,    0,    0, 0, 0,          0,    0,         vs},
#define DLG_VSB(name, x, y, dt, vs)                                                                \
    {name, DlgValAct, dt, NULL, NULL, NULL, x, y, DlgValShow, NULL,    DlgValReg, 0,               \
     0,    0,         0,  0,    0,    0,    0, 0, 0,          AF_BYTE, 0,         vs},
#define DLG_BAUD(name, x, y, dt)                                                                   \
    {name, DlgBaudAct, dt, NULL, NULL, NULL, x, y, DlgIntShow, NULL, DlgBaudReg},
#define DLG_PRIV(name, x, y, dt)                                                                   \
    {name, DlgPrivAct, dt, NULL, NULL, NULL, x, y, DlgPrivShow, NULL, DlgPrivReg},
#define DLG_STV(name, x, y, dt, v)                                                                 \
    {name, NULL, dt, NULL, NULL, NULL, x, y, DlgStrShow, DlgStrEdit, DlgStrReg, v},
#define DLG_STV2(name, x, y, dt, v, p)                                                             \
    {name, NULL, dt, NULL, NULL, NULL, x, y, DlgStrShow, DlgStrEdit, DlgStrReg, v, 0,              \
     0,    0,    0,  0,    0,    0,    0, 0, 0,          0,          0,         p},
#define DLG_VAL(name, x, y, dt)                                                                    \
    {name, DlgStrEdit, dt, NULL, NULL, NULL, x, y, DlgStrShow, DlgStrEdit, DlgStrReg},
#define DLG_BUF(name, x, y, dt, bef)                                                               \
    {name, DlgButAct, dt, NULL, bef, NULL, x, y, DlgButShow, NULL, DlgButReg},
#define DLG_BUT(name, x, y, dt)                                                                    \
    {name, DlgButAct, dt, NULL, NULL, NULL, x, y, DlgButShow, NULL, DlgButReg},
#define DLG_OK(name, x, y)                                                                         \
    {name, DlgButOk, NULL, NULL, NULL, NULL, x, y, DlgButShow, NULL, DlgButReg},
#define DLG_BUA(name, x, y, a) {name, a, NULL, NULL, NULL, NULL, x, y, DlgButShow, NULL, DlgButReg},
#define DLG_OKF(name, x, y) {name, f, NULL, NULL, NULL, NULL, x, y, DlgButShow, NULL, DlgButReg},
#define DLG_CAN(name, x, y)                                                                        \
    {name, DlgButCan, NULL, NULL, NULL, NULL, x, y, DlgButShow, NULL, DlgButReg},
#define DLG_INF(name, x, y) {name, NULL, NULL, NULL, NULL, NULL, x, y, NULL, NULL, DlgInfReg},
#define DLG_RAD(name, x, y, dt)                                                                    \
    {name, DlgRadAct, dt, NULL, NULL, NULL, x, y, DlgRadShow, NULL, DlgRadReg},
#define DLG_CHK(name, x, y, dt)                                                                    \
    {name, DlgChkAct, dt, NULL, NULL, NULL, x, y, DlgChkShow, NULL, DlgChkReg},

#define END_DIALOG                                                                                 \
    {                                                                                              \
        NULL                                                                                       \
    }                                                                                              \
    }                                                                                              \
    }                                                                                              \
    ;
