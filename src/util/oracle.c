// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: oracle.c,v 1.1.1.1 2002/10/01 17:57:34 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_INITIALIZE
#define MAX_INCL_COMMS
#define MAX_INCL_VER
#define MAX_DEFINE_VERSION

#include "max_msg.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <dos.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int unum = 0;
char *filenames[30];

static void Proc_Arg(char *a);
static void Oracle_Help(void);
static void Oracle_More(void);

static char oracle_name[PATHLEN];
char waitforcaller = 0;

char privch = -1;

void GetLocalSize()
{
    extern int loc_cols, loc_rows;

    loc_cols = usr.width;
    loc_rows = usr.len;
}

void Oracle_Parse_Args(char *ctlname, int argc, char *argv[])
{
    struct _fossil_info finfo;
    char *pszPrm;
    int x;

    char env_args[PATHLEN], *s;

    NW(ctlname);

    fprintf(stderr, "\nORACLE " VERSION "  External *.BBS Display File Viewer\n");
    fprintf(stderr,
            "Copyright 1990-" THIS_YEAR " by Lanius Corporation.  All rights reserved.\n\n");

    timeon = time(NULL);
    timeoff = timeon + (60L * 60L);
    max_time = 60;

    pszPrm = GetMaximus(argc, argv, 1);
    strcpy(prmname, pszPrm);

    strcpy(firstname, "Joe");

    Blank_User(&usr);

    // Do this 'portably'

    fossil_inf((struct _fossil_info far *)&finfo);
    usr.len = finfo.height;
    usr.width = finfo.width;

    strcpy(usr.name, "Joe SysOp");
    strcpy(usrname, usr.name);

    strcpy(usr.city, "Anytown, Canada");
    strcpy(usr.alias, "John Doe");
    strcpy(usr.phone, "(123) 456-7890");
    strcpy(usr.pwd, "Mypass");

    usr.ludate.msg_st.date.yr = 11;
    usr.ludate.msg_st.date.mo = 8;
    usr.ludate.msg_st.date.da = 15;

    usr.ludate.msg_st.time.hh = 1;
    usr.ludate.msg_st.time.mm = 23;
    usr.ludate.msg_st.time.ss = 45 / 2;

    usr.priv = (word)-1;
    usr.times = 20;
    usr.up = 250;
    usr.down = 1000;
    usr.downtoday = 100;
    usr.credit = 1500;
    usr.debit = 345;
    usr.video = GRAPH_ANSI;
    bstats.num_callers = 10000;
    strcpy(bstats.lastuser, "Joe User");
    task_num = 1;

    mah.heap = "";
    mah.heap_size = 1;

    fah.heap = "";
    fah.heap_size = 1;

    *oracle_name = '\0';

    if ((s = getenv("ORACLE")) != NULL)
    {
        strcpy(env_args, s);

        for (s = strtok(env_args, " "); s && *s; s = strtok(NULL, " "))
            Proc_Arg(s);
    }

    if (argc <= 1)
        Oracle_Help();

    for (x = 1; x < argc; x++)
        Proc_Arg(argv[x]);
}

static void Proc_Arg(char *a)
{

    char *orig, *s;

    orig = a;

    if (*a == '-' || *a == '/')
    {
        a++;

        switch (tolower(*a))
        {
        case 'h':
            a++;

            switch (tolower(*a))
            {
            case 'n':
                usr.help = NOVICE;
                break;

            case 'r':
                usr.help = REGULAR;
                break;

            case 'e':
                usr.help = EXPERT;
                break;

            default:
                printf("Error!  Invalid help level specified: `%c'!\n", *a);
            }
            break;

        case 'i':
            usr.bits2 &= ~BITS2_IBMCHARS;
            break;

            break;

        case 'q':
            usr.bits |= BITS_HOTKEYS;
            break;

        case 's':
            a++;

            switch (tolower(*a))
            {
            case 'l':
                usr.len = (char)atoi(++a);
                break;

            case 'w':
                usr.width = (char)atoi(++a);
                break;

            default:
                printf("Error!  Invalid screen option specified: `%c'!\n", *a);
            }
            break;

            a++;
            if (isdigit(*a))
                usr.priv = (word)atol(a);
            else
                privch = (char)toupper(*a);
            break;

        default:
            printf("Error!  Invalid command-line argument: `%s'!\n\n", orig);

    if (usr.priv == (word)-1)
    {
