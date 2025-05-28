// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_ocmd.c,v 1.1.1.1 2002/10/01 17:51:55 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_INCL_COMMS

#include "dr.h"
#include "max_area.h"
#include "max_file.h"
#include "max_msg.h"
#include "mm.h"
#include "prog.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct _outstr
{
    char ch;
};

#define OUT_STR 0
#define OUT_INT 1
#define OUT_BYTE 2
#define OUT_UPSTR 3
#define OUT_NBACKS 4
#define OUT_UINT 5
#define OUT_DWORD 6

static struct _outstr outstr[] = {{'f', OUT_STR, (void *)firstname},
                                  {'a', OUT_UINT, (void *)&usr.times},
                                  {'c', OUT_STR, (void *)usr.city},
                                  {'d', OUT_STR, (void *)usr.msg},
                                  {'h', OUT_STR, (void *)usr.phone},
                                  {'i', OUT_DWORD, (void *)&usr.down},
                                  {'k', OUT_BYTE, (void *)&task_num},
                                  {'n', OUT_STR, (void *)usrname},
                                  {'H', OUT_DWORD, (void *)&usr.downtoday},
                                  {'I', OUT_DWORD, (void *)&usr.up},
                                  {'J', OUT_STR, (void *)last_readln},
                                  {'U', OUT_STR, (void *)"_"},
                                  {'X', OUT_DWORD, (void *)&last_msg},
                                  {'Y', OUT_BYTE, (void *)&usr.lang},
                                  {'%', OUT_STR, (void *)"%"},
                                  {'\0', 0, NULL}};

int Parse_Outside_Cmd(char *parm, char *outparm)
{
    int x;

    char temp[PATHLEN];
    char *in;
    char *out;
    char *p;

    struct _outstr *os;

    for (in = parm, out = outparm; *in; in++)
    {
        if (*in != '%')
            *out++ = *in;
        else
        {
                        strcpy(out, (byte *)os->p);
                        break;

                    case OUT_UINT:
                        sprintf(out, pd, (word) * (byte *)os->p);
                        break;

                        strcpy(out, (char *)os->p);

                        if ((x = strlen(out)) > 3)
                            out[x - 1] = '\0';
                    }

                    break;
                }
            }

                    p = FAS(fah, filesbbs);

                    if (*p)
                        strcpy(out, p);
                    else
                        sprintf(out, ss, FAS(fah, downpath), files_bbs);
                    break;

                    strcpy(out, linebuf);
                    *linebuf = '\0';
                    break;

                case 'S':
                    getword(PRM(sysop), temp, ctl_delim, 1);
                    strcpy(out, temp);
                    break;

                case 'T':
                    sprintf(out, pl, timeoff - time(NULL));
                    break;

                case 'V':
                    strcpy(out, FAS(fah, uppath));

                    if ((x = strlen(out)) > 3)
                        out[x - 1] = '\0';
                    break;

                case 'W':
                    sprintf(out, pl, steady_baud_l ? steady_baud_l : baud);
                    break;

                case 'Z':
                    strcpy(out, usrname);
                    cstrupr(out);
                    break;

                case '!':
                    out[0] = '\n';
                    out[1] = '\0';
                    break;

  void ParseOutsideCmd(char *txt)
  {
    char *buf;
    int maxlen=strlen(txt)+100;

    maxlen=max(maxlen, 256);

    if ((buf=malloc(maxlen))==NULL)
      logit(mem_none);
    else
    {
      Parse_Outside_Cmd(txt, buf);
      strcpy(txt, buf);
      free(buf);
    }
  }
#endif
#endif
