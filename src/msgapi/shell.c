// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: shell.c,v 1.1.1.1 2002/10/01 17:54:28 sdudley Exp $";
#pragma on(unreferenced)

#pragma library("../msgapi.lib");

#define TEST_VER
#define INITSQUISH
#define ERL_ERROR 1

#define MSGAPI_HANDLERS
#include "api_Sq.h"
#include "msgapi.h"
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

#define RDLEN 8192

int chase(HAREA ha, int sfd, int ifd, FOFS begin_frame, FOFS last_frame, FOFS end_frame,
          int num_msg)
{
    FOFS fo, foLast;
    SQHDR sqh;
    SQIDX sqi;
    int msgnum = 0;

    fo = begin_frame;
    foLast = NULL_FRAME;

    printf("scanning the %s list\n", ifd == -1 ? "free" : "message");

    while (fo)
    {
        lseek(sfd, fo, SEEK_SET);
        printf("frame %d:\n", msgnum + 1);

        if (fo >= end_frame)
            printf("\a%d: frame too large (%#lx >= %#lx)\n", msgnum + 1, fo, end_frame);

        if (read(sfd, &sqh, sizeof sqh) != sizeof sqh)
        {
            printf("\aread err %d\n", msgnum + 1);
            exit(1);
        }

        if (sqh.prev_frame != foLast)
        {
            printf("\aframe %d: mismatch prev_frame (struct=%#lx, real=%#lx)\n", msgnum + 1,
                   sqh.prev_frame, foLast);
        }

        lseek(ifd, (long)msgnum * (long)sizeof(SQIDX), SEEK_SET);

        if (ifd != -1)
        {
                while ((p = strpbrk(p, "\n\x8d")) != NULL)
                    memmove(p, p + 1, strlen(p + 1) + 1);

                p = rd;


        case 'w':
            num = atol(temp + 1);
            printf("\nTEXT> ");

            fgets(temp, 499, stdin);

            if ((msgh = MsgOpenMsg(sq, MOPEN_CREATE, num)) == NULL)
                printf("Can't open message!\n");
            else
            {
                if (MsgWriteMsg(msgh, FALSE, &msg, temp, strlen(temp) + 1, strlen(temp) + 1,
                                strlen(ctxt) + 1, ctxt) == -1)
                    printf("Can't write message!\n");
                else
                    printf("Wrote msg#%d\n", MsgHighMsg(sq));

                MsgCloseMsg(msgh);
            }
            break;

            *(char far *)0 = 0;
            break;

