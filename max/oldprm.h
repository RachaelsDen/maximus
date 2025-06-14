/*
 * Maximus Version 3.02
 * Copyright 1989, 2002 by Lanius Corporation.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/*# name=.PRM file structure and definitions
 */

#if !defined(__PRM_H_DEFINED) || defined(FORCE)

#if defined(FORCE)
#undef OFS
typedef char OFS[PATHLEN];
/*#elif defined (WSETUP)
    #define OFS char **/
#else
#define OFS word
#endif

#ifndef __PRM_H_DEFINED
#define MAX_DRIVES 26 /* Maximum number of drives on system      */
#define CHAR_BITS 8   /* Number of bits in a 'char'              */
#define CTL_VER 9     /* Version number of BBS.PRM               */

/* This macro is ONLY used for accessing *pointers* in the `prm' structure.
   This is required, due to the way Wynn has made OPUS_CTL write the strings
   out (which uses a lot less memory than some other ways).  If you want
   to access an INT, or a non-pointer in the structure, then you can use
   a `prm.var_name'-style reference.                                       */

#define PRM(s) (offsets + (prm.s))

#define MAX_LANG 8     /* Max. number of possible languages    */
#define MAX_YELL 10    /* Max number of yell slots             */
#define MAX_EXTERNP 16 /* max. number of external programs     */
#define MAXCLASS 12    /* number of possible priv levels       */
#define ALIAS_CNT 15   /* number of matrix addresses           */

/** Definitions for the `prm.flags' variable **/

#define FLAG_keyboard 0x0001 /* If local mode is on by default          */
#define FLAG_watchdog 0x0002 /* Use watchdog for outside commands       */
#define FLAG_snoop 0x0004    /* If snoop is on by default               */
#define FLAG_norname 0x0008  /* If we should disable ^aREALNAME kludge  */
#define FLAG_close_sf 0x0010 /* Close all standard files for O)utside   */
#define FLAG_break_clr                                                                             \
    0x0020                   /* Send a break signal to dump modem's     *                          \
                              * internal buffer                         */
#define FLAG_log_echo 0x0040 /* Log user-written echomail               */
#define FLAG_no_ulist                                                                              \
    0x0080                     /* User can't press '?' to list users in   *                        \
                                * msg.                                    */
#define FLAG_no_magnet 0x0100  /* Disable the MagnEt editor               */
#define FLAG_autodate 0x0200   /* Automatically search directory for      */
                               /* file size & date.                       */
#define FLAG_statusline 0x0400 /* If SysOp wants a status line on screen  */
#define FLAG_ask_phone 0x0800  /* If we should ask user for phone number  */
#define FLAG_noyell 0x1000     /* If yell is toggled on or off by Sysop   */
#define FLAG_lbaud96                                                                               \
    0x2000 /* If we should use 9600 baud for local    *                                            \
            * callers... (For Opus compatibility!)    */
#define FLAG_alias                                                                                 \
    0x4000 /* If we're running a system which allows  *                                            \
            * aliases or handles                      */
#define FLAG_ask_name                                                                              \
    0x8000 /* If we should ask user for their alias   *                                            \
            * name too -- Only needed if using        *                                            \
            * FLAG_alias.                             */

#define FLAG2_gate 0x0001      /* Gate netmail messages, use zonegate!    */
#define FLAG2_has_snow 0x0002  /* Video adapter is slow CGA w/snow        */
#define FLAG2_msgread 0x0004   /* If arrow keys can be used for reading   */
#define FLAG2_ltimeout 0x0008  /* Local keyboard timeout                  */
#define FLAG2_noshare 0x0010   /* SHARE not used -- don't lock files!     */
#define FLAG2_CAPTURE 0x0020   /* Sysop chat capture automatically on     */
#define FLAG2_NOCRIT 0x0040    /* Don't use internal crit.err handler     */
#define FLAG2_CHECKDUPE 0x0080 /* Check for duplicate uploads             */
#define FLAG2_CHECKEXT 0x0100  /* Compare extension for duplicate uploads */
#define FLAG2_GLOBALHB 0x0200  /* Global high bit allowed                 */
#define FLAG2_1NAME 0x0400     /* Global high bit allowed                 */

#define LOG_terse 0x02
#define LOG_verbose 0x04
#define LOG_trace 0x06

#define MULTITASKER_auto -1
#define MULTITASKER_none 0
#define MULTITASKER_doubledos 1
#define MULTITASKER_desqview 2
#define MULTITASKER_topview 3
#define MULTITASKER_mlink 4
#define MULTITASKER_mswindows 5
#define MULTITASKER_os2 6
#define MULTITASKER_pcmos 7

/* Special values for the character set byte */

#define CHARSET_SWEDISH 0x01
#define CHARSET_CHINESE 0x02

#define XTERNEXIT 0x40  /* If external protocl has erlvl exit */
#define XTERNBATCH 0x80 /* If protocol can do batch transfers */

#define NLVER_5 5
#define NLVER_6 6
#define NLVER_7 7
#define NLVER_FD 32

struct cl_rec
{
    sword priv;
    word max_time;      /* max cume time per day         */
    word max_call;      /* max time for one call         */
    word max_dl;        /* max dl kbytes per day         */
    word ratio;         /* ul:dl ratio                   */
    word min_baud;      /* speed needed for logon        */
    word min_file_baud; /* speed needed for file xfer    */
};
#endif /* !__PRM_H_DEFINED */

/* Note: To read in the *.PRM structure, first read in the m_pointers       *
 * structure, which is always contained at the beginning of the file.       *
 * Then, seek to the offset prm.heap_offset, and read in everything         *
 * from there to EOF into heap[].  All of the 'OFS' type variables          *
 * are simply offsets into the variable-length heap which started at        *
 * heap_offset. To obtain a string from the .PRM heap, simply               *
 * add the offset in the m_pointers structure to the address of the         *
 * heap[] variable that the heap was read into.  For example, to access     *
 * the string for 'system_name', you'd use '(heap+prm.system_name)'.        *
 * Alternatively, you can declare a macro to do this, such as the           *
 * PRM() macro shown above.  (Maximus itself uses the variable              *
 * 'strings' instead of 'heap' to hold the varible-length strings,          *
 * but the concept is the same.)  When using the PRM() macro to             *
 * access the string for 'system_name', you'd simply write:                 *
 * 'PRM(system_name)', which is a lot clearer.  Also, please note that      *
 * NON-OFS variables should be accessed normally!  That means that          *
 * 'task_num', 'auto_kill', can be access with 'prm.task_num',              *
 * 'prm.auto_kill', etc.  The special heap manipulation is only needed      *
 * for strings.                                                             */

#ifdef FORCE
struct mfpointers
#else
struct m_pointers
#endif
{

    /*-----------------------------------------------------------*/
    /* DATA                                                      */
    /*-----------------------------------------------------------*/

    byte id;          /* Always equal to 'M'               STABLE  */
    byte version;     /* for safety                        STABLE  */
    word heap_offset; /* OFFSET OF BEGINNING OF HEAP!      STABLE  */
    byte task_num;    /* for multi-tasking systems         STABLE  */
    sword com_port;   /* Com1=0, Com2=1, etc               STABLE  */
    byte noise_ok;    /* If yell noise is currently on     STABLE  */

    /* Miscellanious system information */

    byte video;        /* Mode for local video display              */
    byte log_mode;     /* What style of logging to use              */
    word max_baud;     /* fastest speed we can use                  */
    sbyte multitasker; /* flag for DoubleDos (see below)            */
    byte nlver;        /* Which nodelist version we use (NLVER_XXX) */
    word min_ulist;    /* Min and max privs for the U)serlist cmd   */
    word max_ulist;    /*    "                                      */

    /* Information about errorlevels */

    byte exit_val;   /* Erl to use after caller if none of below  */
    byte edit_exit;  /* erl to use after matrix mail written      */
    byte echo_exit;  /* ERRORLEVEL for after inbound echomail     */
    byte local_exit; /* Errorlevel after entering local msgs      */

    /* Modem information */

    sword carrier_mask;
    sword handshake_mask;

    /* Log-on information */

    sword logon_priv;    /* Access level for new users                */
    word logon_time;     /* time to give for logons                   */
    word min_baud;       /* minimum baud to get on-line               */
    word speed_graphics; /* min baud for graphics                  */

    /* Information about message areas */

    byte auto_kill; /* RECD PVT msgs. 0=no 1=ask 2=yes            */

    sword ctla_priv;   /* Priv to see CONTROL-A lines in messages    */
    sword seenby_priv; /* Min priv to see SEEN-BY line               */
    sword pvt_priv;    /* Min priv to read pvt msgs                  */

    sword msg_ask[16];    /* Array of privs. for message attr ask's     */
    sword msg_assume[16]; /* Array of privs. for message attr assume's  */
    sword msg_fromfile;   /* Priv. for doing message from file          */
    byte rsvd1[4];        /* used to be high_msgarea, begin_msgarea     */
    sword unlisted_priv;  /* Priv needed to send to unlisted node       */
    sword unlisted_cost;  /* Charge to send to unlisted node            */

    sword mc_reply_priv; /* Priv to reply to msg with mailchecker     */
    sword mc_kill_priv;  /* Priv to kill msg with mailchecker         */

    /* Information about file areas */

    sword date_style;     /* Used for FILES.BBS display                */
    sword dlall_priv;     /* Priv. needed to DL file not in FILES.BBS  */
    sword ulbbs_priv;     /* Priv. needed to UL *.BBS files            */
    dword k_free;         /* The number of disk space (in K) which     *
                           * must be available before we let a user    *
                           * upload.                                   */
    word ul_reward;       /* Percentage reward for uploads             */
    word ratio_threshold; /* K which can DL before harass about ratio  */

    byte rsvd2[4]; /* used to be high_filearea, begin_filearea  */

    /* Our matrix address(es) */

    NETADDR address[ALIAS_CNT];

    /*  struct _yell yell[MAX_YELL]; */ /* Yell info moved to event file */
    byte rsvd3[60];                     /* Reserved by Maximus for future use */

    /* About the users */

    struct cl_rec class[MAXCLASS];

    /* Flags for external protocols */

    sword protoexit; /* Errorlevel for protocol exit      */
    char protoflag[MAX_EXTERNP];

    /* General-purpose bit-flags  (See FLAGx_xxx definitions above.) */

    word flags;
    word flags2;
    word flags3;
    word flags4;

    /* Bit field containing drive letters to save when going outside */
    char drives_to_save[(MAX_DRIVES / CHAR_BITS) + 1];

    byte fbbs_margin; /* Margin to use for wrapping FILES.BBS comments */

    byte rsvd999;

    word max_ptrs; /* Maximum size of pointers of ALL *.LTFs */
    word max_heap; /* Maximus heap size of all *.LTFs */
    byte max_lang; /* Current number of languages */
    byte rsvd_lang;

    word max_glh_ptrs;
    word max_glh_len;

    word max_syh_ptrs;
    word max_syh_len;

    byte input_timeout; /* # of mins until Max hangs up due to no input    */

    byte charset;  /* Character set support - see CHARSET_XXXX, above */
    word max_pack; /* Maximum # of msgs to pack into a .QWK packet    */

    byte rsvd65[12]; /* Reserved by Maximus for future use              */

    /* --------------------------------------------------------------- */
    /* -------------------------- OFFSETS ---------------------------- */
    /* --------------------------------------------------------------- */

    /* About your system */

#define PRM_HEAP_START sysop

    OFS sysop;       /* sysop's name. MUST be first offset in prm file */
    OFS system_name; /* board's name                              */

    /* Modem commands */

    OFS m_busy; /* mdm cmd to take modem off hook            */

    /* Paths to various places */

    OFS sys_path;  /* path to SYSTEM?.BBS files                 */
    OFS misc_path; /* path to `F-key files'                     */
    OFS net_info;  /* path to NODELIST files                    */
    OFS temppath;  /* place to put temporary files              */
    OFS ipc_path;  /* path for inter-process communications     */

    /* General files needed by the system */

    OFS user_file;    /* path/filename of User.Bbs                 */
    OFS log_name;     /* name of the log file                      */
    OFS chat_prog;    /* External chat program, if any             */
    OFS chat_fbegin;  /* File to display instead of "CHAT: begin"  */
    OFS chat_fend;    /* File to display instead of "END CHAT"     */
    OFS local_editor; /* Command for local editor, if any          */
    OFS notfound;     /* User name not found in user file          */
    OFS junk;         /* Don't use this for anything!              */

    /* General *.?BS files needed everywhere */

    OFS logo;         /* first file shown to a caller              */
    OFS bad_logon;    /* if user's last logon attempt was bad      */
    OFS welcome;      /* shown after logon                         */
    OFS quote;        /* For displaying "random" quotes from       */
    OFS newuser1;     /* Asks user to type in password             */
    OFS newuser2;     /* Replaces `welcome' for a new user         */
    OFS rookie;       /* Replaces `welcome' for rookies            */
    OFS application;  /* new user questionnaire                    */
    OFS byebye;       /* file displayed at logoff                  */
    OFS out_leaving;  /* Bon Voyage                                */
    OFS out_return;   /* Welcome back from O)utside                */
    OFS daylimit;     /* Sorry, you've been on too long...         */
    OFS timewarn;     /* warning about forced hangup               */
    OFS tooslow;      /* explains minimum logon baud rate          */
    OFS barricade;    /* Displayed before prompt for access code   */
    OFS shelltodos;   /* Displayed when Sysop hits Alt-J           */
    OFS backfromdos;  /* Displayed when Sysop returns from Alt-J   */
    OFS areanotexist; /* File to display instead of "That area     *
                       * doesn't exist!"                           */

    /* File-area items */

    OFS rsvd6;          /* Reserved by Maximus for future use        */
    OFS xferbaud;       /* explains minimum file transfer baud rate  */
    OFS file_area_list; /* dump file... used instead of Dir.Bbs      */
    OFS no_space;       /* File to display if trying to UL with      *
                         * less than k_free space left on drive.     */
    OFS fname_format;   /* Essay on MS-DOS filenames for U)ploads    */
    OFS ul_log;         /* Log file for uploads                      */

    OFS file_header; /* Format for file area's A)rea command      */
    OFS file_format; /* Format for A)rea command entries          */
    OFS file_footer; /* Format for footer for file.area menu      */

    OFS proto_dump; /* Dump file for protocol screen            */

    /* Message-area items */

    OFS msgarea_list;  /* dump file... used instead of Dir.Bbs      */
    OFS echotoss_name; /* Name of your echomail tosslog             */
    OFS nomail;        /* Display by mailchecker if no mail wtng.   */

    OFS msg_header; /* Format for msg.area's A)rea command       */
    OFS msg_format; /* Format for A)reas command entries         */
    OFS msg_footer; /* Format for footer for msg.area menu       */

    /* Help files:  Used to explain various things */

    OFS hlp_editor;   /* intro to msg editor for novices.          */
    OFS hlp_replace;  /* Explain the Msg.Editor E)dit command      */
    OFS msg_inquire;  /* Explain the Msg. I)nquire command         */
    OFS hlp_locate;   /* Explain the Files L)ocate command         */
    OFS hlp_contents; /* Explain the Files C)ontents command       */
    OFS oped_help;    /* help file for the full-screen editor      */
    OFS hlp_scan;     /* help file for S)can                       */
    OFS hlp_list;     /* help file for L)ist                       */

    /* External protocols */

    OFS protocols[MAX_EXTERNP]; /* external file protocol programs   */
    OFS protoname[MAX_EXTERNP]; /* name of protocol, on menu         */

    /* Date/Time format strings */

    OFS timeformat;
    OFS dateformat;

    /* Paths/filenames of the AREAS.DAT and AREAS.IDX files */

    OFS adat_name;
    OFS aidx_name;

    /* Menu paths/names */

    OFS menupath;   /* The default place to look for the menus */
    OFS first_menu; /* The name of the first menu to display */
    OFS edit_menu;  /* Name of the EDIT menu */

    /* Miscellaneous */

    OFS achg_keys; /* Characters used to change area -/+ */
    OFS tune_file; /* Path to TUNES.MAX */
    OFS lang_path; /* Path to *.LTF files */

    OFS lang_file[MAX_LANG]; /* Array of all *.LTF names */

    OFS m_init;    /* Modem initialization string */
    OFS m_ring;    /* Command modem sends when phone ringing */
    OFS m_answer;  /* Cmd to send to modem when ring detect */
    OFS m_connect; /* Connect string, as returned by modem */

    OFS high_msgarea;
    OFS begin_msgarea; /* Msg area to put new users in              */

    OFS high_filearea;
    OFS begin_filearea; /* File area to put new users in             */

    OFS fidouser; /* Name of FIDOUSER.LST file to use          */
    OFS cmtarea;  /* Message area to put comments in           */

    OFS arc_ctl;  /* Control file for archiving programs       */
    OFS olr_name; /* OLR: Filename to use for DL packets       */
    OFS olr_dir;  /* OLR: Directory for off-line stuff         */
    OFS phone_num;
    OFS viruschk;     /* Name of batch file to call for virus check*/
    OFS protocol_max; /* Name of compiled protocol data file       */

#define PRM_HEAP_END protocol_max
};

#define __PRM_H_DEFINED
#endif
