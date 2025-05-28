// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __MAXV_H_DEFINED_
#define __MAXV_H_DEFINED_


unsigned char nohibit[256] = {
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  15,  16,  17,  18,
    19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,
    38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,
    57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,
    76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,
    95,  96,  97,  98,  99,  100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113,
    114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, '^', 'C', 'u', 'e', 'a', 'a',
    'a', 'a', 'c', 'e', 'e', 'e', 'i', 'i', 'i', 'A', 'A', 'E', 'a', 'A', 'o', 'o', 'o', 'u', 'u',
    'y', 'O', 'U', 'c', 'L', 'Y', 'P', 'f', 'a', 'i', 'o', 'u', 'n', 'N', 'a', 'o', '?', '+', '+',
    '2', '4', '!', '<', '>', 'X', 'X', 'X', '|', '+', '+', '+', '+', '+', '+', '|', '+', '+', '+',
    '+', '+', '+', '+', '+', '+', '-', '+', '+', '+', '+', '+', '+', '+', '+', '-', '+', '+', '+',
    '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', 'X', 'X', 'X', 'X', 'X', 'a', 'b', 'g', 'p',
    'E', 'o', 'u', 'T', 'O', 'O', 'O', 'q', 'o', 'o', 'e', 'U', '=', '+', '>', '<', '(', ')', '%',
    '=', 'o', '.', '.', '/', 'n', '2', 'X', ' '};

struct _proto_str intern_proto[] = {{PROTOCOL_NONE, ""},
                                    {PROTOCOL_XMODEM, "Xmodem"},
                                    {PROTOCOL_XMODEM1K, "1K-Xmodem"},
                                    {PROTOCOL_ZMODEM, "Zmodem"},
                                    {PROTOCOL_SEALINK, "SEAlink"},
                                    {PROTOCOL_YMODEM, "Ymodem"},
                                    {PROTOCOL_YMODEMG, "GYmodem-G"},
                                    {-9999, NULL}};

#else

extern unsigned char nohibit[];
extern struct _proto_str intern_proto[];

#endif

#ifdef BINK_PROTOCOLS
#endif

extern unsigned cdecl _stklen;

typedef void(_stdc *std_arg_int)(int);
typedef void(_stdc *std_arg_charstar)(char *);

extrn void(_stdc *local_putc)(int ch) IS((std_arg_int)fputchar);
extrn void(_stdc *local_puts)(char *s) IS((std_arg_charstar)putss);


#ifndef BINK_PROTOCOLS
#endif

extrn FILE *chatlog;

extrn char activexx_bbs[] IS("%sactive%02x.bbs");
extrn char active_star[] IS("%sactive*.bbs");

extrn char logformat[] IS("%c %02d %s %02d:%02d:%02d %s %s\n");
extrn char nameabbr[] IS("MAX ");
extrn char ps_lastread[] IS("%slastread.bbs");
extrn char ps_lastread_single[] IS("%slastread");
extrn char sq_lastread[] IS("%s.sql");
extrn char ss[] IS("%s%s");
extrn char goto_str[] IS("\x16\x08%c%c");
extrn char bbs_stats[] IS("%sbbstat%02x.bbs");
extrn char sp_bs[] IS(" \x08");
extrn char clear_string[] IS("\x16\x08%c%c\x19 %c");
extrn char fill_string[] IS("\x16\x08%c%c\x19%c%c");
extrn char attr_string[] IS("\x16\x01%c");
extrn char pd[] IS("%d");
extrn char pu[] IS("%u");
extrn char pl[] IS("%ld");
extrn char plu[] IS("%lu");
extrn char dotbbs[] IS(".bbs");
extrn char dotidx[] IS(".idx");
extrn char dotgbs[] IS(".gbs");
extrn char dotrbs[] IS(".rbs");
extrn char dotdat[] IS(".dat");
extrn char opusxfer_name[] IS("%smaxxfer.%03x");
#ifndef UNIX
extrn char ipcxx_bbs[] IS("%sIPC%02x.BBS");
extrn char ipc_star[] IS("%sIPC*.BBS");
extrn char ipc_x[] IS("IPC%x.BBS");
#else
extrn char ipcxx_bbs[] IS("%sipc%02x.bbs");
extrn char ipc_star[] IS("%sipc*.bbs");
extrn char ipc_x[] IS("ipc%x.bbs");
#endif
extrn char xctl_keyboard[] IS("Keyboard\n");
extrn char xctl_port_baud[] IS("Port %u\nBaud %ld\n");
extrn char xctl_modem[] IS("Modem %x %lx %x %x %lx\n");
extrn char xctl_time[] IS("Time %u\n");
extrn char xctl_log[] IS("Log %s\n");
extrn char xctl_msgs[] IS("Messages %s\n");
extrn char xctl_uploads[] IS("Uploads %s\n");
extrn char xctl_downloads[] IS("Downloads %s\n");
extrn char xctl_help[] IS("Help %sHlp\n");
extrn char xctl_filesbbs[] IS("FilesBbs %s\n");
extrn char files_bbs[13] IS("files.bbs");
extrn char sfiles[13] IS("files");
extrn char last_onexit[LEN(PATHLEN)] IS("");
#else

#ifdef MCP
extrn char last_readln[MAXLEN + 1];
#ifdef BINK_PROTOCOLS






#ifndef OS_2

extern char comp_date[];
extern char comp_time[];

