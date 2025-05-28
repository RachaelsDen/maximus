// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef LEXP_H_DEFINED__
#define LEXP_H_DEFINED__



typedef struct _macro
{
    int fInMacro;
    int iPos;
    MACDEF md;
} MACRO;


typedef struct _xlt
{
    char from;
    char to;
} XLTABLE;

