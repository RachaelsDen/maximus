// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_misc.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
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

void Strip_Comment(char *l)
{
    char *sp = l;
    int x;

    while (*sp)
    {
        if (isalpha(*sp))
            break;
        else if (ispunct(*sp))
        {
            *sp = '\0';
            break;
        }

        sp++;
    }

    if (l[x = strlen(l) - 1] == '\n')
        l[x] = '\0';
}

void Add_Path(char *s, int warn)
{
    int x = 0;

    char temp[MAX_LINE];
#if 0
       temp2[MAX_LINE];
#endif
    if (!s)
        return;

    while (*s && (s[x = strlen(s) - 1] == ' ' || s[x] == '\t'))
        s[x] = '\0';

    if (*s && s[x] != PATH_DELIM)
    {
        s[++x] = PATH_DELIM;
        s[++x] = '\0';
    }

#if 0
  if (prm.sys_path)
  {
    if (! (s[1]==':' || *s=='\\' || *s=='/'))
    {
      strcpy(temp,strings+prm.sys_path);
      strcat(temp,s);
    }
    else strcpy(temp,s);

    if (temp[1] != ':')
    {
      temp2[0]=*(strings+prm.sys_path);
      temp2[1]=':';
      temp2[2]='\0';
      strcat(temp2,temp);
      strcpy(temp,temp2);
    }
  }
  else
#endif
    strcpy(temp, s);


char *fchar(char *str, char *delim, int wordno)
{
    char *s;

    if ((s = firstchar(str, delim, wordno)) == NULL)
        return str + strlen(str);
    else
        return s;
}

#if 0
byte MaxPrivToOpus(int maxpriv)
{
  switch(maxpriv)
  {
    case SYSOP:
      return _SYSOP;

    case ASSTSYSOP:
      return _ASSTSYSOP;

    case CLERK:
      return _CLERK;

    case EXTRA:
      return _EXTRA;

    case FAVORED:
      return _FAVORED;

    case PRIVIL:
      return _PRIVEL;

    case WORTHY:
      return _WORTHY;

    case NORMAL:
      return _NORMAL;

    case LIMITED:
      return _LIMITED;

    case DISGRACE:
      return _DISGRACE;

    case TWIT:
      return _TWIT;
  }

  return _HIDDEN;
}
#endif

void assert_dir(char *path)
{
    if (!direxist(path))
        makedir(path);
}

int makedir(char *d)
{
    char temp[PATHLEN];
    int x;

    for (*temp = '\0';;)
    {
        if (!do_unattended)
        {
            printf("\rCreate dir `%s' [Y,n]? ", d);

            fgets(temp, PATHLEN, stdin);

            Strip_Trailing(temp, '\n');

            *temp = (char)toupper(*temp);

            Compiling(-1, NULL, NULL);
        }

        if (do_unattended || *temp == 'Y' || *temp == '\n' || *temp == '\0')
        {
            char *fn;

            printf("\rCreating directory `%s'\n", d);
            Compiling(-1, NULL, NULL);

            fn = sstrdup(d);

            Strip_Trailing(fn, PATH_DELIM);

            x = make_dir(fn);
            free(fn);
            return x;
        }
        else if (*temp == 'N')
            return 0;
    }
}

#if 0
int Deduce_Priv(char *p)
{
  if (strnicmp(p,"hidden",6)==0)
    return HIDDEN;
  else if (strnicmp(p,"sysop",5)==0)
    return SYSOP;
  else if (strnicmp(p,"asstsysop",9)==0)
    return ASSTSYSOP;
  else if (strnicmp(p,"clerk",5)==0)
    return CLERK;
  else if (strnicmp(p,"extra",5)==0)
    return EXTRA;
  else if (strnicmp(p,"favored",5)==0)
    return FAVORED;
  else if (strnicmp(p,"privel",6)==0 || strnicmp(p,"privil",6)==0)
    return PRIVIL;
  else if (strnicmp(p,"worthy",6)==0)
    return WORTHY;
  else if (strnicmp(p,"normal",6)==0)
    return NORMAL;
  else if (strnicmp(p,"limited",7)==0)
    return LIMITED;
  else if (strnicmp(p,"disgrace",8)==0)
    return DISGRACE;
  else if (strnicmp(p,"twit",4)==0)
    return TWIT;
  else
  {
    printf("\a\nInvalid priv level `%s' on line %d of CTL file!\n",p,linenum);
    exit(1);
  }
  return 0;
}
#endif

int Deduce_Attribute(char *a)
{
    if (eqstri(a, "private"))
        return 0;
    else if (eqstri(a, "crash"))
        return 1;
    else if (eqstri(a, "fileattach"))
        return 4;
    else if (eqstri(a, "killsent"))
        return 7;
    else if (eqstri(a, "hold"))
        return 9;
    else if (eqstri(a, "filerequest"))
        return 11;
    else if (eqstri(a, "updaterequest"))
        return 15;
    else if (eqstri(a, "fromfile"))
        return -22;
    else if (eqstri(a, "localattach"))
        return -20;
    else
    {
        printf("\a\nInvalid attribute `%s' on line %d of CTL file!\n", a, linenum);
        exit(1);
    }
    return 0;
}

#if 0
int Deduce_Class(int priv)
{
  int x;

  for (x=0;x < num_class;x++)
    if (prm.cls[x].priv==priv)
      break;

  prm.cls[x].priv=priv;

  if (x >= num_class)
    num_class++;

  return x;
}
#endif

void Unknown_Ctl(int linenum, char *p)
{
    printf("\n\aUnknown statement in line %d of `%s':  `%s'?\n", linenum, ctl_name, p);
    Compiling(-1, NULL, NULL);
}

int Compiling(char type, char *string, char *name)
{
    static char last_string[80], last_name[80];

    static int last_length = 0;
    int x;

    if (type == -1)
        printf(last_string, last_name);
    else
    {

    p = strchr(p, '/');

        if (!(s[x] == ':' || s[x - 1] == '\\' || s[x - 1] == '/'))
        {
            if (x == 2)
                strcpy(temp, ":");
            else
                *temp = '\0';
            strcat(temp, strings + prm.sys_path);
            strcat(temp, s + x - 1);
        }
        else
            strcpy(temp, s);
    }
    else
        strcpy(temp, s);

    return (Add_To_Heap(temp, FALSE));
}

int Make_Pth(char *value)
{
    int x = 0;

    char temp[MAX_LINE], *s;

    if (value == NULL)
        s = "";
    else
        s = value;

    while (*s && (s[x = strlen(s) - 1] == ' ' || s[x] == '\t'))
        s[x] = '\0';

    if (*s && s[x] != PATH_DELIM)
    {
        s[++x] = PATH_DELIM;
        s[++x] = '\0';
    }

    strcpy(temp, s);
    Add_Path(temp, 1);

    return (Add_To_Heap(temp, TRUE));
}

int Add_To_Heap(char *s, int fancy)
{
    int old_ofs;
    char *o;


void Attrib_Or(int clnum,int attr,struct _area *area)
{
  int x;

  if (clnum==-1)
  {
    for (x=0;x < MAXCLASS;x++)
      area->attrib[x] |= attr;
  }
  else area->attrib[clnum] |= attr;
}

void Attrib_And(int clnum,int attr,struct _area *area)
{
  int x;

  if (clnum==-1)
  {
    for (x=0;x < MAXCLASS;x++)
      area->attrib[x] &= attr;
  }
  else area->attrib[clnum] &= attr;
}


int Blank_Sys(struct _sys *sys,int mode)
{
  if (mode==0)
  {
    sys->ls_caller=0;
    sys->quote_pos=0L;
  }

  sys->priv=HIDDEN;
  sys->attrib=0;
  sys->lock=0;

  memset(sys->msgpath, '\0', sizeof(sys->msgpath));
  memset(sys->uppath, '\0', sizeof(sys->uppath));
  memset(sys->filepath, '\0', sizeof(sys->filepath));
  memset(sys->bbspath, '\0', sizeof(sys->bbspath));
  memset(sys->hlppath, '\0', sizeof(sys->hlppath));

  strcpy(sys->bbspath, strings+prm.menupath);
  strcpy(sys->hlppath, strings+prm.sys_path);
  strcat(sys->hlppath, "Hlp" PATH_DELIMS);

  return 0;
}


void Blank_Area(struct _area *area)
{
  memset(area,'\0',sizeof(struct _area));

  area->id=AREA_id;
  area->struct_len=sizeof(struct _area);
  area->type=MSGTYPE_SDM;


    if (!verbs)
    {
        words[0] = szFirstWord;
        getword(line, words[0], ctl_delim, 1);
    }
    else
    {
        for (w = 0; w < MAX_PARSE_WORDS; w++)
        {
            if ((words[w] = malloc(PATHLEN)) == NULL)
                NoMem();

            if (w == 0 || *words[w - 1])
                getword(line, words[w], ctl_delim, w + 1);
            else
                *words[w] = 0;
        }
    }


    if (!verbs || !pvt->verb)
    {
        if (eqstri(words[0], "end"))
            rc = TRUE;
        else if (*words[0] && verbs)
            Unknown_Ctl(linenum, words[0]);
    }
    else
    {

        if (pvt->pzstr)
            HeapAdd(&PFI(pfi)->h, pvt->pzstr, fchar(line, ctl_delim, 2));
    }


void near FiltPath(void *v, char *words[], char *line)
{
    int len = strlen(line);

    NW(words);
    NW(v);

    while (len && line[len - 1] == ' ')
        --len;

    line[len] = 0;


void near FiltOverride(void *v, char *words[], char *line)
{
    OVRLIST ol = malloc(sizeof(*ol));
    int idx;

    NW(line);

    if (!ol)
        NoMem();


    if (!*words[1])
    {
        printf("Error!  No menu name specified for override on line %d!\n", linenum);
        return;
    }

    if (!*words[3])
    {
        printf("Error!  No access control string specified for override on line %d!\n", linenum);
        return;
    }

    if ((idx = tsearch(words[2], silt_table, silt_table_size)) != -1)
        ol->or.opt = silt_table[idx].opt;
    else
        Unknown_Ctl(linenum, words[2]);

    if (*words[4])
        ol->or.name = *words[4];
    else
        ol->or.name = 0;

    if (PFI(v)->marea)
    {
        HeapAdd(&PMI(v)->h, &ol->or.menuname, words[1]);
        HeapAdd(&PMI(v)->h, &ol->or.acs, words[3]);


        ol->next = PFI(v)->ol;
        PFI(v)->ol = ol;

        PFI(v)->fa.num_override++;
    }
}

void near FiltMenuname(void *v, char *words[], char *line)
{
    NW(line);

    if (!*words[1] || !*words[2])
        printf("\n\aError!  Two arguments must be specified for the MenuName keyword!\n");

    if (PFI(v)->marea)
    {
        HeapAdd(&PMI(v)->h, &PMI(v)->ma.menureplace, words[1]);
        HeapAdd(&PMI(v)->h, &PMI(v)->ma.menuname, words[2]);
    }
    else
    {
        HeapAdd(&PFI(v)->h, &PFI(v)->fa.menureplace, words[1]);
        HeapAdd(&PFI(v)->h, &PFI(v)->fa.menuname, words[2]);
    }
}

void BadDivisionName(void)
{
    printf("\n\aError!  Invalid character ('.') in area/division name on line %d!\n", linenum);
    Compiling(-1, NULL, NULL);
}
