// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_args.c,v 1.3 2003/06/05 23:37:19 wesgarland Exp $";
#pragma on(unreferenced)


#include "caller.h"
#include "mm.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef UNIX
#include "prm.h"
#include <errno.h>
#endif

#ifndef ORACLE

static void near Unknown_CmdParam(char *param);
static void near ReadCallerInfo(char *path);
static void near Parse_Single_Arg(char *arg);

#if defined(OS_2) && !defined(__FLAT__)
#define INCL_DOS
#include <os2.h>

#include "semtrig.h"

unsigned trigger_wait = FALSE;
HSYSSEM hssmBBS;
SEL selBBS;

void pascal far MaxSemTriggerClose(USHORT usTermCode)
{
    NW(usTermCode);

    DosSemClear(hssmBBS);


    DosSleep(1000);
    DosSemRequest(hssmBBS, SEM_INDEFINITE_WAIT);


    local = FALSE;
    baud = pst->ulRateDCE;
    steady_baud_l = pst->ulRateDTE;
    port = pst->hfPort - 1;
    task_num = pst->usTask;
    fSetTask = TRUE;
    strcpy(arq_info, pst->szARQinfo);

    current_baud = Decimal_Baud_To_Mask((unsigned int)baud);
    steady_baud = Decimal_Baud_To_Mask((unsigned int)steady_baud_l);

    max_time = pst->ulMaxTime;
    getoff = timestart + (max_time * 60L);

                *p1 = '\0';
        }
        else

void Recurse(void)
{
  Recurse();
}

#pragma off(check_stack);

#endif

#ifdef UNIX
byte getDynamicTaskNumber(int cleanup)
{
    char *path;
    int i, fd;
    static char filename[FILENAME_MAX];

    if (cleanup)
    {
        if (filename[0])
            unlink(filename);
    }

    if (offsets && PRM(ipc_path))
        path = PRM(ipc_path);
    else
        path = "/tmp";

        fd = open(filename, O_RDWR | O_CREAT, 0644);
        if (fd >= 0)
        {
            if (flock(fd, LOCK_EX | LOCK_NB) == 0)
            {
                char buf[32];

                snprintf(buf, sizeof(buf), "%i\n", (int)getpid());
                write(fd, buf, strlen(buf));
                logit("# PID %i running as task %i", (int)getpid(), i);
                return i;
            }
            else
                close(fd);
        }
    }

    filename[0] = (char)0;
    return 0;
}

void dtnCleanUp() { getDynamicTaskNumber(1); }
#endif

static void near Parse_Single_Arg(char *arg)
{
    if (*arg == '-' || *arg == '/')
    {
        cstrlwr(arg);

        switch (arg[1])
        {
#ifdef MCP
            if ((baud = atol(arg + 2)) != 0L)
            {
                local = FALSE;
                current_baud = Decimal_Baud_To_Mask((unsigned int)baud);
            }
            break;

                debug_ovl = TRUE;
                break;
#endif

#ifdef DMALLOC
            strcpy(linebuf, arg + 2);
            break;

        case 'i':
            ReadCallerInfo(arg + 2);
            break;

            strcpy(log_name, arg + 2);
            break;

            if (arg[2] != 'd')
                port = atoi(arg + 2) - 1;
            else
            {
                port_is_device = TRUE;
                port = atoi(arg + 3) - 1;
            }
            break;

            max_time = atol(arg + 2);
            getoff = timestart + (max_time * 60L);
            break;

           case 'd':
            displaymode=VIDEO_DOS;
            break;
            
          case 'f':
            displaymode=VIDEO_FAST;
            break;
            
          case 'o':
            displaymode=VIDEO_FOSSIL;
            break;
#endif
            default:
                Unknown_CmdParam(arg);
            }
            break;

        case 'w':
            waitforcaller = TRUE;
            port_is_device = TRUE;
            local = FALSE;
            break;

        case 'x':
            switch (arg[2])
            {
            case 'c':
                no_dcd_check = TRUE;
                break;

            case 'd':
                no_dtr_drop = TRUE;
                break;

            case 'j':
                no_shell = TRUE;
                break;

#ifdef OS_2
            case 't':
                no_traptrap = TRUE;
                break;
#endif

            case 'z':
                no_zmodem = TRUE;
                break;

            default:
                Unknown_CmdParam(arg);
            }
            break;

        case 'y':
            strcpy(arq_info, arg + 2);
            break;

#ifdef MAXSNOOP
        case 'z':
            SnSetPipeName(arg + 2);
            break;
#endif

        default:
            Unknown_CmdParam(arg);
            break;
        }
    }
    else if (eqstri(arg, qmark))
        Unknown_CmdParam(NULL);
    else
        strcpy(prmname, arg);
}

static void near Unknown_CmdParam(char *param)
{
    if (param)
        Lprintf(huh, param);

    Lprintf("Usage:\n\n");

    Lprintf("  max"
#ifdef OS_2
            "p"
#endif
            " [prm_name] [[args]...]\n\n");

#ifdef OS_2
    Lprintf("  -a<pipename> Name of MCP pipe           -s<speed>   Lock baud rate (bps)\n");
#else
    Lprintf("                                          -s<speed>   Lock baud rate (bps)\n");
#endif
    Lprintf("  -b<speed>    Connection speed (bps)     -t<minutes> Maximum time limit\n");
    Lprintf("  -c           Create 'user.bbs'          -u{q}       User edit (-uq=hotkeys)\n");
#ifdef OS_2
    Lprintf("  -dl          Debug logging              -vi         Select Video IBM\n");
#else
    Lprintf("  -dl          Debug logging              -v{bi}      Select Video BIOS/IBM\n");
#endif
    Lprintf("  -e<num>      Event file number          -w          Wait for caller\n");
    Lprintf("  -j<strokes>  Jam keystrokes into buffer -xc         No DCD checking\n");
    Lprintf("  -i<filename> Read FD caller info        -xd         Don't drop DTR\n");
    Lprintf("  -k           Local mode                 -xj         Don't allow <Alt-J>\n");
    Lprintf("  -m{dqplwman} Multitasker selection\n");
    Lprintf("  -n           Task number                -xz         No internal Zmodem\n");
#ifdef OS_2
    Lprintf("  -p<handle>   Com handle                 -y<info>    Extra modem connect info\n");
    Lprintf("  -pd<port>    Com port number\n");
#else
    Lprintf("  -p<port_num> Com port number            -y<info>    Extra modem connect info\n");
#ifdef __MSDOS__
    Lprintf("  -r           Restart from Xtern_Erlvl\n");
#endif
#endif

    quit(ERROR_PARAM);
}

