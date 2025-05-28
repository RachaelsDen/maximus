// SPDX-License-Identifier: GPL-2.0-or-later



#ifdef MAX_INSTALL
#include "ar.h"
#include "install.h"
#include "prog.h"
#include "tui.h"
#include <stdarg.h>
#include <stdlib.h>
#else
#include "ar.h"
#include <stdarg.h>
#include <stdlib.h>
#endif

#define UPDATE_CRC(c) crc = crctable[(crc ^ (c)) & 0xFF] ^ (crc >> CHAR_BIT)

FILE *arcfile, *infile, *outfile;
uint crc, bitbuf;

static ushort crctable[UCHAR_MAX + 1];
static uint subbitbuf;
static int bitcount;

void _stdc error(char *fmt, ...)
{
#ifdef MAX_INSTALL
    char szError[180];
    va_list args;

    va_start(args, fmt);
    vsprintf(szError, fmt, args);
    va_end(args);

    WinErr(szError);
    WinExit(1);
#else
    va_list args;

    va_start(args, fmt);
    putc('\n', stderr);
    vfprintf(stderr, fmt, args);
    putc('\n', stderr);
    va_end(args);
    exit(EXIT_FAILURE);
#endif
}

void make_crctable(void)
{
    ushort i, j, r;

    for (i = 0; i <= UCHAR_MAX; i++)
    {
        r = i;
        for (j = 0; j < CHAR_BIT; j++)
            if (r & 1)
                r = (r >> 1) ^ CRCPOLY;
            else
                r >>= 1;
        crctable[i] = r;
    }
}

{
    if (n < bitcount)
    {
        subbitbuf |= x << (bitcount -= n);
    }
    else
    {
        if (compsize < origsize)
        {
            putc(subbitbuf | (x >> (n -= bitcount)), outfile);
            compsize++;
        }
        else
            unpackable = 1;
        if (n < CHAR_BIT)
        {
            subbitbuf = x << (bitcount = CHAR_BIT - n);
        }
        else
        {
            if (compsize < origsize)
            {
                putc(x >> (n - CHAR_BIT), outfile);
                compsize++;
            }
            else
                unpackable = 1;
            subbitbuf = x << (bitcount = 2 * CHAR_BIT - n);
        }
    }
}

int fread_crc(uchar *p, int n, FILE *f)
{
    int i;

    i = n = fread(p, 1, n, f);
    origsize += n;
    while (--i >= 0)
    {
        UPDATE_CRC(*p++);
        UPDATE_CRC(*p++);
    }
}

void init_getbits(void)
{
    bitbuf = 0;
    subbitbuf = 0;
    bitcount = 0;
    fillbuf(BITBUFSIZ);
}

void init_putbits(void)
{
    bitcount = CHAR_BIT;
    subbitbuf = 0;
}
