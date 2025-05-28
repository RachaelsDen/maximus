// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: maxpipe.c,v 1.1.1.1 2002/10/01 17:57:27 sdudley Exp $";
#pragma on(unreferenced)

#include <conio.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INCL_NOPM
#define INCL_DOS
#define INCL_VIO
#define INCL_DOSDEVICES
#define INCL_DOSDEVIOCTL
#include "pos2.h"

#include "comm.h"

#ifdef __FLAT__
#define DosMakePipe DosCreatePipe
#define DosBufReset DosResetBuffer
#define DosSendSignal(p, s) DosSendSignalException(p, 4)

#ifdef _loadds
#undef _loadds
#endif

#ifdef FAR
#undef FAR
#endif

#ifdef far
#undef far
#endif

#ifdef VOID
#undef VOID
#endif

#define VOID void
#define far
#define FAR
#define _loadds
#endif

extern int DupHandles(void);
extern int StartThreads(void);
extern void CloseHandles(void);
static void far _loadds WatchDogThread(void *pv);
static int CHAR_AVAIL(void);
static BYTE GET_CHAR(void);
static void far _loadds StdinThread(void *pv);
static void far _loadds StdoutThread(void *pv);

#define STACK1 16384
#define STACK2 16384
#define STACK3 16384

    return TRUE;
}

void *zalloc(size_t bytes)
{
    void *ret = malloc(bytes);

    if (!ret)
    {
        fprintf(stderr, "MAXPIPE: Couldn't allocate %u bytes\n", bytes);
        exit(3);
    }

    return ret;
}

int StartThreads(void)
{
#ifdef __FLAT__
    static char stack1[STACK1];
    static char stack2[STACK2];
    static char stack3[STACK3];
#else
    BYTE *stack1, *stack2, *stack3;

    stack1 = zalloc(STACK1);
    stack2 = zalloc(STACK2);
#endif

#ifdef __FLAT__
    if (_beginthread(StdinThread, stack1, STACK1, NULL) == -1 ||
        _beginthread(StdoutThread, stack2, STACK2, NULL) == -1)
    {
        fprintf(stderr, "MAXPIPE: Couldn't create threads\n");
        return FALSE;
    }
#else
    if (DosCreateThread((PFNTHREAD)StdinThread, &tid1, stack1 + STACK1) ||
        DosCreateThread((PFNTHREAD)StdoutThread, &tid2, stack2 + STACK2))
    {
        fprintf(stderr, "MAXPIPE: Couldn't create threads\n");
        return FALSE;
    }
#endif

    }

    return TRUE;
}

void CloseHandles(void)
{
    HFILE sin = fileno(stdin);
    HFILE sout = fileno(stdout);
    HFILE serr = fileno(stderr);

    DosClose(hfStdoutR);
    DosClose(hfStdoutW);
    DosClose(hfStdinR);
    DosClose(hfStdinW);
    DosDupHandle(oldStderr, &serr);
    DosDupHandle(oldStdout, &sout);
    DosDupHandle(oldStdin, &sin);
    DosClose(oldStderr);
    DosClose(oldStdout);
    DosClose(oldStdin);
}

#pragma check_stack(off)

                {
                    if (bytes > 0)
                    {
                        bytes--;
                        DosWrite(hfStdoutW, "\x8 \x8", 3, &bo);
                    }
                }
                else
                {
                    linebuf[bytes++] = (char)c;
                    DosWrite(hfStdoutW, &c, 1, &bo);
                }
            }

            if (c == '\n')
            {
                DosWrite(hfStdinW, linebuf, bytes, &bo);
                bytes = 0;
            }
        }
    }

    DosExit(EXIT_THREAD, 0);
}

static VOID FAR _loadds StdoutThread(void *pv)
{
    static char bufout[200];
    static char buf[150];
    OS2UINT bytes, i, j;

    (void)pv;

    while (alive)
    {
        DosRead(hfStdoutR, buf, sizeof(buf), &bytes);

        for (i = j = 0; i < bytes; i++)
        {
            if (buf[i] == '\n')
                bufout[j++] = '\r';

            bufout[j++] = buf[i];
        }

        if (hfCom)
            ComWrite(hfCom, bufout, j);

        VioWrtTTY(bufout, j, 0);
    }

    DosExit(EXIT_THREAD, 0);
}
