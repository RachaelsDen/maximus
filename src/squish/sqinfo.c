// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: sqinfo.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#define NOVARS
#define NOVER
#define MSGAPI_HANDLERS

#include "api_sq.h"
#include "msgapi.h"
#include "prog.h"
#include "sqver.h"
#include <conio.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int quiet = 0;
static int findbug = 0;
static int batch = 0;

void divider(void)
{
    if (!quiet)
        printf("\n=======================================\n");
}

char *frtype(int type)
{
    switch (type)
    {
    case FRAME_NORMAL:
        return "Stored msg";

    case FRAME_FREE:
        return "Free";

    default:
        return "\aUnknown!  (Should be `Stored msg' or `Free'!)";
    }
}

int debug_chain(char *name, FILE *sfd, FILE *ifd, struct _sqbase *sqbase, FOFS new_frame,
                FOFS last_frame, char *type, struct _sqbase *sqb, int num_msg, int fFreeFrame)
{
    SQIDX idx;
    SQHDR lframe;
    SQHDR frame;
    FOFS lframeofs;
    long filesize;
    int goterr = FALSE;
    int haderr = FALSE;
    int msgnum = 0;
    word count;

    NW(ifd);

    if (new_frame == NULL_FRAME)
    {
        if (!quiet)
            printf("The %s list is empty.\n", type);
    }
    else
    {
        lframe.next_frame = new_frame;
        lframeofs = NULL_FRAME;

        fseek(sfd, 0L, SEEK_END);
        filesize = ftell(sfd);

        count = 0;

        for (;;)
        {
            if (!quiet)
                printf("\n");

            if (!findbug)
                printf("%s frame at %#010lx: (#%u)\n", type, new_frame, count + 1);

            msgnum++;

            if (!quiet)
                printf("\n");

            if (new_frame == NULL_FRAME)
            {
                printf("\aerror! cannot read the NULL frame\n");
                goterr = TRUE;
            }

            if (new_frame > filesize)
            {
                printf("\aframe offset too large (file size is %#010lx)!\n", filesize);
                goterr = TRUE;
            }

            fseek(sfd, new_frame, SEEK_SET);

            if (ftell(sfd) != lframe.next_frame)
            {
                printf("\aerror: incorrect forward link for prior msg, #%d\n", count - 1);
                goterr = TRUE;
            }

            if (fread((char *)&frame, 1, sizeof(SQHDR), sfd) != sizeof(SQHDR))
            {
                printf("\aerror reading frame at %#010lx\n", new_frame);
                goterr = TRUE;
            }
            else
            {

                if (!quiet)
                    printf("id=           %#010lx", frame.id);

                if (frame.id == SQHDRID)
                {
                    if (!quiet)
                        printf(" (OK)\n");
                }
                else
                {
                    printf("\a (Should be %#010lx!)\n", SQHDRID);
                    goterr = TRUE;
                }

                if (!quiet)
                    printf("prev_frame=   %#010lx", frame.prev_frame);

                if (frame.prev_frame == lframeofs)
                {
                    if (!quiet)
                        printf(" (OK)\n");
                }
                else
                {
                    printf("\a (Should be %#010lx.)\n", lframeofs);
                    goterr = TRUE;
                }

                if (!quiet)
                    printf("next_frame=   %#010lx", frame.next_frame);

                if (new_frame >= sqbase->end_frame)
                {
                    printf("\a (Should be less than end_frame [%#010lx]!)\n", sqbase->end_frame);
                    goterr = TRUE;
                }
                else if (new_frame == frame.next_frame)
                {
                    printf("\a (Circular frame reference!)\n");
                    goterr = TRUE;
                }
                else if (new_frame == last_frame && frame.next_frame != NULL_FRAME)
                {
                    printf("\a Last should be NULL_FRAME (0x00000000).\n");
                    goterr = TRUE;
                }
                else if (frame.next_frame == NULL_FRAME && new_frame != last_frame)
                {
                    printf("\a Premature link end. Chain should end at %#010lx.\n", last_frame);
                    goterr = TRUE;
                }
                else if (sqb && frame.next_frame == NULL_FRAME &&
                         (unsigned long)(count + 1) != sqb->num_msg)
                {
                    printf("\a\nErr!  Last msg is #%ld, but got chain end after %ld msgs!\n",
                           sqb->num_msg, (long)(count + 1));
                    goterr = TRUE;
                }
                else if (!quiet)
                    printf(" (OK)\n");

                if (!quiet)
                    printf("frame_length= %ld", frame.frame_length);

                if (new_frame + sizeof(SQHDR) + frame.frame_length > sqbase->end_frame ||
                    (frame.next_frame > new_frame &&
                     new_frame + sizeof(SQHDR) + frame.frame_length > frame.next_frame))
                {
                    printf("\a Too long!\n");
                    goterr = TRUE;
                }
                else if (!quiet)
                    printf(" (OK)\n");

                if (!quiet)
                    printf("msg_length=   %ld", frame.msg_length);

                if ((long)frame.msg_length < (long)sizeof(XMSG) + (long)frame.clen && !fFreeFrame)
                {
                    printf("\a  (Control info is too long for frame!)\n");
                    goterr = TRUE;
                }
                else if (frame.msg_length > frame.frame_length)
                {
                    printf("\a  (Should be <= %ld!)\n", frame.frame_length);
                    goterr = TRUE;
                }
                else if (!quiet)
                    printf(" (OK)\n");

                if (!quiet)
                {
                    printf("clen=         %ld\n", frame.clen);
                    printf("type=         %s\n", frtype(frame.frame_type));
                }
            }

            if (goterr)
            {
                printf("Problem in %s.\n"
                       "Press <esc> to abort, or any other key to continue: ",
                       name);

                if (batch)
                    exit(1);

                fflush(stdout);

                if (kgetch() == '\x1b')
                    exit(1);

                printf("\n");
                goterr = FALSE;
                haderr = TRUE;
            }

            divider();

            if (new_frame == NULL_FRAME || frame.next_frame == NULL_FRAME)
                break;

            lframeofs = new_frame;
            new_frame = frame.next_frame;
            lframe = frame;
            count++;
        }
    }

    if (num_msg != -1 && msgnum != num_msg)
    {
        printf("\aError!  Expected %d msgs in chain, but only found %d\n", num_msg, msgnum);
        haderr = TRUE;
    }

    return (haderr ? -1 : 0);
}

int sqvalidate(char *name, FILE *sfd, FILE *ifd)
{
    struct _sqbase sqbase;
    int x, y;

    if (fread((char *)&sqbase, 1, sizeof(struct _sqbase), sfd) != sizeof(struct _sqbase))
    {
        printf("\asqvalidate: unable to read sqbase header\n");
        return -1;
    }

    divider();

    printf("\nGlobal data for %s:\n\n", name);

    if (!quiet)
    {
        printf("len=         %d\n", sqbase.len);
        printf("num_msg=     %ld\n", sqbase.num_msg);
        printf("high_msg=    %ld", sqbase.high_msg);
    }

    if (sqbase.high_msg != sqbase.num_msg)
        printf("\a (should be %ld!)", sqbase.num_msg);

    if (!quiet)
    {
        printf("\n");

        printf("uid=         %ld\n", sqbase.uid);
        printf("base=        %s\n", sqbase.base);
        printf("begin_frame= %#010lx\n", sqbase.begin_frame);
        printf("last_frame=  %#010lx\n", sqbase.last_frame);
        printf("last_free_fr=%#010lx\n", sqbase.last_free_frame);
        printf("free_frame=  %#010lx\n", sqbase.free_frame);
        printf("end_frame=   %#010lx\n", sqbase.end_frame);
        printf("sz_sqhdr=    %d\n", sqbase.sz_sqhdr);
