// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: silt.c,v 1.1.1.1 2002/10/01 17:57:37 sdudley Exp $";
#pragma on(unreferenced)


#define SILT
#define SILT_INIT
#define MAX_INCL_VER

#include "silt.h"
#include "max.h"
#include "opusprm.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef __WATCOMC__
#include <malloc.h>
#endif

struct _maxcol col = {
#if 0
    '\xf0',

    '\x1f',
    '\x1e',
    '\x47',
    '\x1e',
    '\x1a',
    '\x1f',
    '\x1b',
                    break;

                case 'u':
                    do_unattended = TRUE;
                    break;

                case 'x':
                    do_prm = do_marea = do_farea = do_menus = TRUE;
                    break;

                case 'y':
                    printf("Warning!  The '-y' parameter is obsolete!\n");
                    break;

                default:
                    printf("\aInvalid command-line parameter:  `%s'!\n", argv[x]);
                    Silt_Format();
                }

                p++;
            }
        }
        else
        {
            printf("\aInvalid command-line parameter:  `%s'!\n", argv[x]);
            Silt_Format();
        }
    }


static void Adjust_Prm(void)
{
    char temp[PATHLEN];

    if (!prm.achg_keys)
        Make_String(prm.achg_keys, "[]?");

    if (!prm.high_msgarea)
        Make_String(prm.high_msgarea, "ZZZZZZZZZZ");

    if (!prm.high_filearea)
        Make_String(prm.high_filearea, "ZZZZZZZZZZ");

    if (!prm.begin_msgarea)
        Make_String(prm.begin_msgarea, "1");

    if (!prm.begin_filearea)
        Make_String(prm.begin_filearea, "1");

    if (!prm.adat_name)
    {
        strcpy(temp, strings + prm.sys_path);
        strcat(temp, "area.dat");

        Make_String(prm.adat_name, temp);
    }

    if (!prm.aidx_name)
    {
        strcpy(temp, strings + prm.sys_path);
        strcat(temp, "area.idx");

        Make_String(prm.aidx_name, temp);
    }

    if (!prm.access)
        Make_String(prm.access, "access");
}

static void near Write_Max_Prm(char *name)
{
    char temp[PATHLEN];
    int prmfile;

    printf("\nWriting Maximus Version %d PRM file...", CTL_VER);

    if (!(done_sys && done_equip && done_session && done_language && done_colours))
    {
        printf("\n\aWarning!  PRM creation specified, but all sections are "
               "not present!");
    }
    else
    {
        sprintf(temp, "%s.prm", name);

        if ((prmfile = open(temp, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, S_IREAD | S_IWRITE)) ==
            -1)
        {
            printf("\n\aError opening `%s' for write!\n", temp);
            exit(1);
        }

        write(prmfile, (char *)&prm, sizeof(struct m_pointers));
        write(prmfile, strings, offset);
        close(prmfile);
    }
}

static void near Write_Colours(void)
{
    char temp[PATHLEN];
    int fd;

    if (!do_prm)
        return;

    sprintf(temp, "%scolours.dat", strings + prm.sys_path);

    if ((fd = sopen(temp, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_DENYNO,
                    S_IREAD | S_IWRITE)) == -1)
    {
        printf("Can't open colour data file (`%s')!  Aborting...\n", temp);
        exit(1);
    }

    if (write(fd, (char *)&col, sizeof(col)) != sizeof(col))
        printf("Can't write to %s\n", temp);

    close(fd);
}

int _stdc c_main(int argc, char *argv[])
{
    char temp[PATHLEN];

    Hello("SILT", "Maximus Control File Compiler", VERSION, "1989, " THIS_YEAR);


    sprintf(temp, "%s.ctl", argv[1]);

    Initialize_Prm();
    qsort(silt_table, silt_table_size, sizeof(silt_table[0]), stcomp);
    Parse_Ctlfile(temp);

    MsgAreaClose();
    FileAreaClose();

    if (do_prm || do_2areas)
        putchar('\n');

    Adjust_Prm();

    if (do_prm)
    {
        Write_Max_Prm(argv[1]);
        Write_Access();
        Write_Colours();
    }

    if (do_2areas)
        Generate20Areas();

    printf("\n\nDone!\n");

    return 0;
}
