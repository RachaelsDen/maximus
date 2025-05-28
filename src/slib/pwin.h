// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __PWIN_H_DEFINED
#define __PWIN_H_DEFINED

#ifdef NT
#define WIN32_LEAN_AND_MEAN
#define _INC_DDEMLH

#undef pascal
#define pascal __pascal

#undef cdecl
#define cdecl __cdecl

#pragma pack()
#endif

