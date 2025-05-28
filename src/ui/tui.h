// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __TUI_H_DEFINED
#define __TUI_H_DEFINED

#include "keys.h"
#include "prog.h"
#include "win.h"

#ifdef __FARDATA__
#define MENUFAR huge
#else
#define MENUFAR
#endif


#define MENU_PLACE                                                                                 \

#define MENU_COLS                                                                                  \
    CBLACK | _GRAY, CBLACK | _GRAY, CBLACK | _GRAY, CWHITE | _BLACK, CRED | _GRAY, CWHITE | _BLACK

#define STD_MENU(name, sx, sy, bor, type)                                                          \
    struct _vmenu MENUFAR(name)[1] = {sx, sy, MENU_COLS, bor, type, 0xffff, 0xffff, NULL, NULL,    \
                                      NULL, {

#define DEF_MENU(name, sx, sy, cw, cb, ci, cs, ch, csh, bor, type)                                 \
    struct _vmenu MENUFAR(name)[1] = {sx, sy, cw, cb, ci, cs, ch, csh, bor, type, 0xffff, 0xffff,  \
                                      NULL, NULL, NULL, {

#define MNU_ITEM(name, handler, menu) {name, handler, NULL, menu, NULL, NULL, 0xffffu, 0xffffu},
#define STD_ITEM(name, handler) {name, handler, NULL, NULL, NULL, NULL, 0xffffu, 0xffffu},
#define DAT_ITEM(name, handler, data) {name, handler, data, NULL, NULL, NULL, 0xffffu, 0xffffu},

#define END_MENU                                                                                   \
    {                                                                                              \
        NULL                                                                                       \
    }                                                                                              \
    }                                                                                              \
    }                                                                                              \
    ;

struct _vmenu;
struct _vopt;
struct _vkey;

typedef struct _vmenu *HVMENU;
typedef struct _vopt *HVOPT;
typedef struct _vkey *HVKEY;

#define VKF_MENUKEYS                                                                               \
#define VKF_AFTER                                                                                  \


struct _vkey
{










struct _vmenu
{
    word start_x, start_y;
    byte col_win, col_bor, col_item, col_sel, col_hot, col_selhot;
    sword border;
    word type;
    word sizex, sizey;

    word (*before)(HVMENU menu);
    word (*after)(HVMENU menu);

    char *title;

    struct _vopt opt[MAX_VOPT];

