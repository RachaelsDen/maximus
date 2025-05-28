// SPDX-License-Identifier: GPL-2.0-or-later

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int stricmp(const char *a, const char *b) { return strcasecmp(a, b); }

int strnicmp(const char *a, const char *b, size_t n) { return strncasecmp(a, b, n); }

char *strupr(char *sOrig)
{
    char *s = sOrig;

    if (s && *s)
    {
        do
        {
            *s = toupper(*s);
        } while (*s++);
    }

    return sOrig;
}

char *strlwr(char *sOrig)
{
    char *s = sOrig;

    if (s && *s)
    {
        do
        {
            *s = tolower(*s);
        } while (*s++);
    }

    return sOrig;
}

char *itoa(int value, char *buffer, int radix)
{
