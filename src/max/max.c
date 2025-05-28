// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max.c,v 1.1.1.1 2002/10/01 17:51:17 sdudley Exp $";
#pragma on(unreferenced)

#include "alc.h"
#include "mm.h"
#include "prog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __TURBOC__
extern unsigned cdecl _stklen = 16656;
#endif

#if defined(OS_2) && defined(__FLAT__)
#define INCL_DOS
#include "pos2.h"
#endif

int _stdc c_main(int argc, char *argv[])
{
    char *ctlname;
    char *key_info;


    _heapgrow();


    Init_Variables();

    if ((ctlname = (char *)malloc(PATHLEN)) == NULL)
        maximus_exit(2);

#ifdef ORACLE
    Oracle_Parse_Args(ctlname, argc, argv);
#else
    Parse_Args(ctlname, argc, argv);
#endif

    Read_Prm(ctlname);


    key_info = Startup();

#ifdef ORACLE
    Oracle();
