// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mex_main.c,v 1.2 2003/06/05 23:26:50 wesgarland Exp $";
#pragma on(unreferenced)

#define MEX_INIT

#define MAX_INCL_VER

#include "max.h"
#include "mex.h"
#include "prog.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sdebug = FALSE;
int mdebug = FALSE;

static void near usage(void)
{
    static char help[] = "Usage:\n\n"

                         "mex [<args>...] <filename>\n\n"

                         "<args> can be any of the following options:\n\n"

                         "  -a       Show addresses instead of names in ASCII quad listing\n"

    for (av = argv + 1; *av; av++)
    {
        if (**av == '-' || **av == '/')
        {
            switch ((*av)[1])
            {
            case 'a':
                show_addr = TRUE;
                break;


            case 'd':
                if ((*av)[2] == 'y')
                    yydebug = TRUE;
                else if ((*av)[2] == 's')
                    sdebug = TRUE;
                else if ((*av)[2] == 'm')
                    mdebug = TRUE;
                break;

            case 'h':
                lHeapSize = atol(*av + 2);
                break;

            case 's':
                lStackSize = atol(*av + 2);
                break;

            case 'q':
                vm_output = FALSE;
                break;

            default:
            case '?':
                usage();
                break;
            }
        }
        else if (eqstri(*av, "?"))
            usage();
        else
        {

    delim = strrstr(filename, "\\/:");
    dot = strrchr(filename, '.');

    if (!dot || (delim && dot && dot < delim))
        strcat(filename, ".mex");

    if (!push_fstk(filename))
        exit(1);

    if (vm_output)
        open_vm(filename, lStackSize, lHeapSize, outfile);

    linenum = 1L;
    scope = 0;

    offset = maxoffset = 0;
    glob_offset = maxgloboffset = GLOB_CONTROL_DATA;
    n_errors = n_warnings = 0;


    ret = yyparse();

    if (vm_output)
        close_vm();

