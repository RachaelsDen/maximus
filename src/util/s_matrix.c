// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_matrix.c,v 1.1.1.1 2002/10/01 17:57:46 sdudley Exp $";
#pragma on(unreferenced)


#define SILT
#define NOVARS
#define NOINIT

#include "dr.h"
#include "max.h"
#include "opusprm.h"
#include "prog.h"
#include "silt.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static int alias_count = 0;

int Parse_Matrix(FILE *ctlfile)
{
    int x, y;

                        {
                            x = Deduce_Attribute(p);
                            getword(line, p, ctl_delim, 5);
                            if (x == -20 && (!p || !*p))
                                prm.msg_localattach = 0;
                            else
                            {
                                y = Deduce_Priv(p);

                        {
                            x = Deduce_Attribute(p);

                            getword(line, p, ctl_delim, 5);
                            if (x == -20 && (!p || !*p))
                                prm.msg_localattach = 0;
                            else
                            {
                                y = Deduce_Priv(p);

