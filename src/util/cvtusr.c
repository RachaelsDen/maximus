// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: cvtusr.c,v 1.1.1.1 2002/10/01 17:57:17 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_INCL_VER

#include "cvtusr.h"
#include "max.h"
#include "max_oldu.h"
#include "prog.h"
#include "userapi.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

char user_name[] = "user";
char user_bbs[] = "user.bbs";
char user_idx[] = "user.idx";
char user_bak[] = "user.bak";
char user_102[] = "user.102";
char user_200[] = "user.200";
char user_dol[] = "user$$$";
char user_poo[] = "user$$$.bbs";
char user_poo2[] = "user$$$.idx";
char user_dat[] = "user.dat";
char users_bbs[] = "users.bbs";
char rec_num[] = "Record %04d\r";

void _fast Adjust_User_Record(struct _usr *user);

int _stdc c_main(int argc, char *argv[])
{
    int x;

    Hello("CVTUSR", "Maximus User File Conversion Utility", VERSION, "1989, " THIS_YEAR);

    if (argc < 2)
        Format();

    for (x = 1; x < argc; x++)
    {
        if (*argv[x] == '-' || *argv[x] == '/')
        {
            switch (tolower(argv[x][1]))
            {
            case 'd':
                Dump(argv[x] + 2);
                break;

            case '3':

        Get_Dos_Date(&usr.date_newfile);
        Get_Dos_Date(&usr.date_pwd_chg);

        if ((++num % 32) == 0)
        {
            printf(rec_num, num);
            fflush(stdout);
        }


        memset(&usr, 0, sizeof usr);
        memmove(&usr, &usr200, sizeof usr200);


        usr.group = 0;
        usr.dob_year = 0;
        memset(usr.dataphone, 0, sizeof usr.dataphone);
        usr.msgs_posted = usr.msgs_read = 0;
        usr.sex = SEX_UNKNOWN;
        memset(usr.rsvd45, 0, sizeof usr.rsvd45);

        memset(&usr.date_1stcall, 0, sizeof usr.date_1stcall);


        strcpy(usr.msg, usr200.msg);
        strcpy(usr.files, usr200.files);


        while ((p = strchr(usr.files, '.')) != NULL)
            *p = '_';


        if ((++num % 32) == 0)
        {
            printf(rec_num, num);
            fflush(stdout);
        }

        if (!UserFileCreateRecord(huf, &usr, TRUE))
            printf("Error writing user record for %s\n", usr.name);
    }

    printf(rec_num, num);
    printf("\nDone!\n");

    close(infile);
    UserFileClose(huf);

    unlink(user_bak);
    unlink(user_idx);
    rename(user_bbs, user_bak);
    rename(user_poo, user_bbs);
    rename(user_poo2, user_idx);
}

#if 0
void Convert_RBBS(char *name)
{
  NW(name);

  struct _rbbsu ru;
  struct _usr102 usr;

  int rbbsfile;
  int maxfile;
  int nptr=0;

  if ((rbbsfile=open(name,O_RDONLY | O_BINARY))==-1)
  {
    printf("Error opening `%s' for read!\n",name);
    exit(1);
  }

  if ((maxfile=open(user_bbs,O_CREAT | O_TRUNC | O_WRONLY | O_BINARY,
                    S_IREAD | S_IWRITE))==-1)
  {
    printf("Error opening `USER.BBS' for write!\n");
    exit(1);
  }

  while (read(rbbsfile,(char *)&ru,sizeof(struct _rbbsu))==
          sizeof(struct _rbbsu))
  {
    if (*BASIC(ru.name)=='\0')
      continue;

    memset(&usr,'\0',sizeof(struct _usr102));
    usr.width=80;
    usr.len=24;
    usr.help=NOVICE;

    strcpy(usr.name,fancy_str(BASIC(ru.name)));
    strcpy(usr.pwd,fancy_str(BASIC(ru.pwd)));
    strcpy(usr.city,fancy_str(BASIC(ru.city)));
    usr.dnld=atoi(BASIC(ru.dl_total_bytes));
    usr.upld=atoi(BASIC(ru.ul_total_bytes));
    usr.lastread_ptr=nptr++;
    usr.ibmchars=1;
    usr.more=1;
    usr.formfeed=1;
    usr.tabs=1;
    usr.ansi=0;
    usr.kludge=0;
    usr.priv=newpriv(NORMAL);
    usr.struct_len=sizeof(struct _usr102)/20;

    write(maxfile, (char *)&usr, sizeof(struct _usr102));

    if ((++num % 32)==0)
    {
      printf(rec_num, num);
      fflush(stdout);
    }
  }

  printf(rec_num, num);
  printf("\nDone!\n");
  close(maxfile);
  close(rbbsfile);
}
#endif

void Check_If_Exist(void)
{
    char temp[PATHLEN];

    if (fexist(user_bbs) || fexist(user_idx))
    {
        printf("Warning!  USER.BBS already exists.  Overwrite [y,N]? ");
        fgets(temp, 80, stdin);

        printf("\n");

        if (toupper(*temp) != 'Y')
        {
            printf("Aborted!\n");
            exit(1);
        }

        if (fexist(user_bak))
            unlink(user_bak);

        rename(user_bbs, user_bak);
    }
}
