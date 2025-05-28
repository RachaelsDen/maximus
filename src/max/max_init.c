// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_init.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_init
#define MAX_LANG_max_chat
#define MAX_INCL_COMMS

#include "dr.h"
#include "emsi.h"
#include "max_edit.h"
#include "max_file.h"
#include "max_msg.h"
#include "mm.h"
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

#ifdef KEY
#include "makekey.h"
#endif

static void near OpenAreas(void);
static void near install_handlers(void);
static void near StartUpVideo(void);
static void near Initialize_Colours(void);

void Init_Variables(void)
{
    int x;
    char *s;


    multitasker = -2;
    strcpy(log_name, c123);

    local_putc = (void(_stdc *)(int))fputchar;
    local_puts = (void(_stdc *)(char *))putss;

#ifndef ORACLE
    Lprintf(slogan, "\n", version, test);
    Lputs(copyright);
#endif

    *firstname = *linebuf = *searchfor = *fix_menupath = *last_readln = *arq_info = '\0';

    display_line = display_col = current_line = current_col = 1;

    isareply = isachange = FALSE;

    port = -1;
    cls = -1;
    orig_disk2 = orig_disk3 = -1;
    local = -2;
    task_num = 255;
    fSetTask = FALSE;
    event_num = (byte)-2;

    baud = 0;
    current_baud = 0;
    steady_baud = 0;
    steady_baud_l = 0;
    ultoday = 0;
    brk_trapped = 0;
    erl = 0;

#ifndef ORACLE
    max_lines = 0;
#endif

    num_yells = 0;
    rst_offset = -1L;
    getoff = 0x7fffffffL;

    fFlow = FALSE;

    menu_lines = 1;

    if ((s = getenv("PROMPT")) != NULL)
    {
#endif

    nowrite_lastuser = in_file_xfer = written_local = mn_dirty = no_zmodem = in_mcheck = no_shell =
        dsp_set = in_node_chat = chkmail_reply = waitforcaller = in_wfc = log_wfc = in_msghibit =
            FALSE;

    direction = DIRECTION_NEXT;

    offsets = NULL;

    chatlog = NULL;
#ifndef ORACLE
    sq = NULL;
#endif
    dspwin = NULL;
    dspwin_time = 0L;

#ifndef ORACLE
    Init_File_Buffer();
#endif

    max_time = 0xffffL;
    last_bps = 0;


    prm.logon_priv = 0;
    Blank_User(&usr);


#ifdef MCP
    *szMcpPipe = 0;
#endif

#ifdef EMSI
    EmsiInitHandshake();
#endif
}

static void near quitfile()
{
    vbuf_flush();
    Local_Beep(3);
    Delay(300);
    quit(ERROR_FILE);
}

char *Startup(void)
{
#ifdef KEY
    int key_fd, key_ok = TRUE;
    char *key_buf, *key_outbuf;
    int key_size, key_strip_ofs;
#endif

    union stamp_combo now;
    char temp[PATHLEN];

#ifndef ORACLE
    struct _usr user;
    struct _minf mi;
    int fd;
#endif

    if (getcwd(original_path, PATHLEN) == NULL)
    {
        Lputs(err_startup_tlong);
        Local_Beep(3);
        maximus_exit(ERROR_FILE);
    }
    else if (strlen(cfancy_fn(original_path)) > 3)
        strcat(cfancy_fn(original_path), PATH_DELIMS);


    Get_Dos_Date(&now);
    MsgDte(&now, temp);
    datelen = strlen(temp);

    if (!dsp_set)
        displaymode = prm.video;


    if (!do_useredit)
        OpenAreas();

    Load_Archivers();

#ifdef KEY
    if ((key_fd = key_open("MAXIMUS.KEY")) == -1)
        key_ok = FALSE;
#endif


    if (local && !restart_system)
        prm.flags &= ~FLAG_statusline;


      local_putc=(void (_stdc *)(int))fossil_putc;
      local_puts=(void (_stdc *)(char *))fossil_puts;
      break;
#endif

    case VIDEO_DOS:
      local_putc=(void (_stdc *)(int))fputchar;
      local_puts=(void (_stdc *)(char *))putss;
      break;

    case VIDEO_FAST:
#ifdef __MSDOS__
      local_putc=(void (_stdc *)(int))xputch;
      local_puts=(void (_stdc *)(char *))xputs;
      break;

    default:
        displaymode = VIDEO_IBM;

    case VIDEO_IBM:
    case VIDEO_BIOS:
        StartUpVideo();

#ifndef ORACLE

    if (!fSetTask)
        task_num = prm.task_num;


#ifdef KEY
    if (key_ok)
        key_close(key_fd);
#endif


#ifndef ORACLE

    if (do_useredit)
    {
        strcpy(usr.name, "\xff ");
        Config_Multitasker(FALSE);

        usr.video = GRAPH_ANSI;
        usr.bits |= BITS_TABS;
        usr.bits2 |= BITS2_CLS | BITS2_IBMCHARS;
        usr.width = 80;
        usr.len = 25;

        timeoff = timeon + (1440 * 60L);

        local = TRUE;

        OpenAreas();

        *log_name = '\0';

        Fossil_Install(TRUE);
        User_Edit(NULL);

        AreaFileClose(ham);
        AreaFileClose(haf);

        ShutDownVideo();

        quit(0);
    }


    do_timecheck = TRUE;

#ifndef ORACLE
    Blank_User(&usr);

    {
        if (!LogOpen())
            quit(ERROR_CRITICAL);
        else
        {
            if (!restart_system)
                LogWrite("\n");
        }
    }

#ifdef KEY
    if (key_ok && (key_outbuf = malloc(key_size)) == NULL)
        key_ok = FALSE;
#endif

    if (!restart_system)
    {
        extern int _stdc main();

        if (task_num)
            logit(log_begin_mt, version, task_num);
        else
            logit(log_begin_1t, version);
    }

#ifdef KEY
    if (key_ok)
    {
        key_strip_ofs = key_unpack1(key_buf, key_outbuf, key_size);
        key_free(key_buf);
    }
#endif


#ifdef MCP
    ChatOpenMCP();
#endif


#if defined(KEY) && !defined(ORACLE)
    return key_outbuf + CODE_1_SIZE;
#else
    return NULL;
#endif
}


    end = lseek(prmfile, 0L, SEEK_END);


    if (*PRM(first_menu))
        strnncpy(main_menu, PRM(first_menu), MAX_MENUNAME - 1);



    if (timeout_tics < 6000)
        timeout_tics = 4 * 60 * 100;
}

void Read_Access()
{
    char temp[PATHLEN];
#ifndef ORACLE
    int plevels;
    extern PLIST *pl_privs;
#endif

    sprintf(temp, ss, PRM(access), dotdat);
    if (!ClassReadFile(temp))
    {
        char temp2[PATHLEN];
        strcpy(temp2, PRM(sys_path));
        strcat(temp2, temp);

        if (!ClassReadFile(temp2))
        {
            Lprintf(cant_find_file, access_txt, temp);
            quitfile();
        }
    }

#ifndef ORACLE
    return BAUD38400;
}


    nullptr();
}

static void near StartUpVideo(void)
{
    VidOpen(prm.flags2 & FLAG2_has_snow, multitasker == MULTITASKER_desqview, FALSE);

    if (!no_video)
        VidCls(CGREY);

        fflush(stdout);
#endif
    }
}
