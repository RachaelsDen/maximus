// SPDX-License-Identifier: GPL-2.0-or-later


#if defined(OS_2)

#define INCL_SUB

#include "pos2.h"
#include "prog.h"

static int last_scan;

int pascal kgetch(void)
{
    int ret;
    KBDKEYINFO kki;

    if (last_scan)
    {
        ret = last_scan;
        last_scan = 0;
        return ret;
    }

    KbdCharIn(&kki, IO_WAIT, 0);


static int BadKeyRec(PINPUT_RECORD pir)
{
    if (pir->EventType != KEY_EVENT || !pir->Event.KeyEvent.bKeyDown)
        return TRUE;

    switch (pir->Event.KeyEvent.wVirtualScanCode)
    case 0x2a:
    case 0x1d:
    case 0x38:
    case 0x3a:
    case 0x36:
    case 0x46:
    case 0x45:
        return TRUE;

    return FALSE;
}

int pascal kpeek(void)
{
    INPUT_RECORD ir;
    DWORD dwGot;

    if (last_scan)
        return last_scan;

    if (!console_inited)
        _console_init();

    do
    {
        if (!PeekConsoleInput(hIn, &ir, 1, &dwGot) || dwGot == 0)
            return -1;

        if (BadKeyRec(&ir))
            ReadConsoleInput(hIn, &ir, 1, &dwGot);
    } while (BadKeyRec(&ir));

    return InputRecToKey(&ir, TRUE);
}

int pascal kgetch()
{
    INPUT_RECORD ir;
    DWORD dwGot;

    if (last_scan)
    {
        int rc;
        rc = last_scan;
        last_scan = 0;
        return rc;
    }

    if (!console_inited)
        _console_init();

    do
    {
        if (!ReadConsoleInput(hIn, &ir, 1, &dwGot) || dwGot == 0)
            return -1;
    } while (BadKeyRec(&ir));

    return InputRecToKey(&ir, FALSE);
}

int pascal khit(void) { return (kpeek() != -1); }

#elif defined(UNIX)

#include <curses.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

        int ch = getch();

        if (ch == ERR)
            ch = -1;

        return ch;
    }
    else
    {

        if (select(fileno(stdin) + 1, &rfds, NULL, NULL, &tv) <= 0)
        if (ch >= 0)
            ungetch(ch);
    }
    else
    {
