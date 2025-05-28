// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef MEX_H_DEFINED__
#define MEX_H_DEFINED__

#ifndef __TYPEDEFS_H_DEFINED
#include "typedefs.h"
#endif

#ifdef OS_2
#define INCL_NOPM
#include <pos2.h>
#endif


#ifdef MEX_INIT
#define mex_extern
#define equ(s) = s
#else
#define mex_extern extern
#define equ(s)
#endif

#define bcopy(f, t, size) memmove(t, f, size)
#define isidchar(c) (isalpha(c) || isdigit(c) || (c) == '_')


#define MAX_GLOB_LEN                                                                               \




typedef char *string;


struct _typedesc;
typedef struct _typedesc TYPEDESC;

struct _attributes;
typedef struct _attributes ATTRIBUTES;

struct _address;
typedef struct _address ADDRESS;

struct _dataobj;
typedef struct _dataobj DATAOBJ;

struct _funcargs;
typedef struct _funcargs FUNCARGS;

struct _goto;
typedef struct _goto GOTO;

struct _tlist;
struct _tlistlist;

typedef struct _tlist TLIST;
typedef struct _tlistlist TLLIST;

struct _patch;
typedef struct _patch PATCH;



typedef struct _iaddr
{

struct _funcargs
{

struct _conval
{
    struct _conval *next;
    VMADDR offset;
    VMADDR len;
    byte *buf;
};


struct _rcheck
{
    VMADDR lo, hi;

    DATAOBJ *obj;
};


struct _ipat
{

struct _imp
{
};


struct _implist
{
};


struct _tlistlist
{
    word size;
    TLIST *tlist;
    TLLIST *next;
};


typedef struct
{
    ATTRIBUTES *func;
    ATTRIBUTES *arg;
} FUNCCALL;


typedef struct _tokentype
{
    word operator;
} TOKEN;


struct _dataobj
{


    union
    {
        VALTYPE val;
        ADDRESS addr;
    } form;
};

struct _patch
{
    VMADDR quad;
    PATCH *next;
};

typedef struct _whiletype
{
    PATCH jump;
    VMADDR top_quad;
} WHILETYPE;

typedef struct _fortype
{
    VMADDR vmTest;
    VMADDR vmPost;
    VMADDR vmBody;
    PATCH paJzDone;
    PATCH paJmpBody;
    PATCH paJmpTest;
    PATCH paJmpPost;
} FORTYPE;

typedef struct
{
    PATCH *patchout;
    VMADDR else_label;
} ELSETYPE;


struct _typedesc
{
        {
            RANGE bounds;
            TYPEDESC *el_type;
        } array;


typedef struct _funcattr
{
} FUNCATTR;

struct _attributes
{
    char *name;



    union
    {
    } c;
};

#ifndef MEX_PARSER
