// SPDX-License-Identifier: GPL-2.0-or-later



#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdlib.h>
#include <string.h>

void ci_login(void)
{
    Get_Dos_Date(&sci.login);
    sci.logon_priv = usr.priv;
    sci.logon_xkeys = usr.xkeys;
    sci.calls = usr.times + 1;
}

void ci_init(void)
{
    if (*PRM(caller_log))
    {
        memset(&sci, 0, sizeof sci);
        strcpy(sci.name, usrname);
        sci.task = task_num;
        ci_login();
    }
}

void ci_filename(char *buf)
{
    char temp[PATHLEN];

    *buf = '\0';
    if (*PRM(caller_log))
    {
        char *p;

        strcpy(temp, PRM(caller_log));
        Convert_Star_To_Task(temp);
        Parse_Outside_Cmd(temp, buf);
        p = strrchr(buf, PATH_DELIM);
        if (p == NULL)
            p = buf;
        if (strchr(p, '.') == NULL)
            strcat(buf, dotbbs);
    }
}

void ci_save(void)
{
    char temp[PATHLEN];

    ci_filename(temp);
    if (*sci.name && *temp)
    {
        int fd;

