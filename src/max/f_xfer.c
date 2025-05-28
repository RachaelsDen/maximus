// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_xfer.c,v 1.1.1.1 2002/10/01 17:51:12 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>
#ifdef BINK_PROTOCOLS
#include "zmodem.h"
#endif
#include "f_idx.h"
#include "fb.h"
#include "max_file.h"
#include "prog.h"

int File_Get_Protocol(sword *protocol, int chng, int need_nonexit)
{
    char temp[PATHLEN];
    struct _proto_str *ps;
    char *s;

    word max, prot;
    byte ch;

    if (!chng && usr.def_proto != PROTOCOL_NONE)
    {
        if (!need_nonexit || usr.def_proto < 0 || (prm.protoflag[usr.def_proto] & XTERNEXIT) == 0)
        {
            *protocol = usr.def_proto;
            return 0;
        }
    }

    *protocol = PROTOCOL_NONE;

    if (!*linebuf)
    {
        if (*PRM(proto_dump))
            Display_File(0, NULL, PRM(proto_dump));
        else
        {
            if (!chng)

            max = 9;

            for (prot = 0; prot < MAX_EXTERNP; prot++)
                if (!need_nonexit || (prm.protoflag[prot] & XTERNEXIT) == 0)
                {
                    if (strlen(s = Protocol_Name(prot, temp)) > max)
                        max = strlen(s);
                }


            for (ps = intern_proto; ps->name; ps++)
                if (*ps->name)
                {
                    if (no_zmodem && *ps->name == 'Z')
                        continue;

                    Printf(proto_box_mid, *ps->name, max - 1, max - 1, ps->name + 1);
                }

            for (prot = 0; prot < MAX_EXTERNP; prot++)
                if (!need_nonexit || (prm.protoflag[prot] & XTERNEXIT) == 0)
                    if (*(s = Protocol_Name(prot, temp)))
                        Printf(proto_box_mid, toupper(*s), max - 1, max - 1, s + 1);

            Printf(proto_box_mid, chng ? *proto_none : *proto_quit, max - 1, max - 1,
                   (chng ? proto_none : proto_quit) + 1);

            Printf(proto_box_bot, max + 3);
        }
    }

    ch = (byte)toupper(KeyGetRNP(select_p));

    if (ch == 'Q' || (ch == 'N' && chng) || ch == '\r' || ch == '\x00')
        return -1;

    for (ps = intern_proto; ps->name; ps++)
    {
        if (no_zmodem && *ps->name == 'Z')
            continue;

        if (*ps->name == ch)
        {
            *protocol = ps->num;
            return 0;
        }
    }

    for (prot = 0; prot < MAX_EXTERNP; prot++)
        if (!need_nonexit || (prm.protoflag[prot] & XTERNEXIT) == 0)
            if (ch == (byte)toupper(*Protocol_Name(prot, temp)))
            {
                *protocol = (int)prot;
                return 0;
            }

    *linebuf = '\0';
    Printf(dontunderstand, ch);
    return -1;
}


void Open_OpusXfer(FILE **xferinfo)
{
    char xname[PATHLEN];

    sprintf(xname, opusxfer_name, original_path, task_num);

    if ((*xferinfo = shfopen(xname, fopen_write, O_WRONLY | O_TRUNC | O_CREAT | O_NOINHERIT)) ==
        NULL)
        cant_open(xname);
}

void Close_OpusXfer(FILE **xferinfo)
{
    if (*xferinfo)
    {
        fputc('\n', *xferinfo);
        fclose(*xferinfo);
    }

    *xferinfo = NULL;
}

void Delete_OpusXfer(FILE **xferinfo)
{
    char xname[PATHLEN];

    if (*xferinfo)
        fclose(*xferinfo);

    *xferinfo = NULL;

    sprintf(xname, opusxfer_name, original_path, task_num);
    unlink(xname);
}

byte Get_Protocol_Letter(sword protocol)
{
    switch (protocol)
    {
    default:
    case PROTOCOL_XMODEM:
        return 'X';
    case PROTOCOL_XMODEM1K:
        return '1';
    case PROTOCOL_YMODEM:
        return 'Y';
    case PROTOCOL_YMODEMG:
        return 'G';
    case PROTOCOL_SEALINK:
        return 'S';
    case PROTOCOL_ZMODEM:
        return 'Z';
    }
}

#ifdef BINK_PROTOCOLS
char *zalloc(void)
{
    byte *sptr;

    if ((sptr = malloc(WAZOOMAX + 16)) == NULL)
        logit("!Z-MEMOVFL");

    return sptr;
}
#endif

                break;
                ret = FALSE;
                break;
            }
        }
    }

    Puts("\r" CLEOL);
    WhiteN();
    return ret;
}
