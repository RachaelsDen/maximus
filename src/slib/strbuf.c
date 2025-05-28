// SPDX-License-Identifier: GPL-2.0-or-later



#include "strbuf.h"
#include "prog.h"
#include <stdlib.h>
#include <string.h>

#define sbofs2ptr(sb, ofs) (char *)(((char *)(sb)) + (ofs))

#if defined(UNIX)
strbuf *sb_new(int sz)
#else
strbuf *sb_new(word sz)
#endif
{
    strbuf *sb;

    if (sz <= sizeof(strbuf))
        sz = STRBUFSZ;
    sb = (strbuf *)malloc(sz);
    if (sb != NULL)
    {
        char *p;

        sb->usSize = (word)sz;
        sb->usOffset = sizeof(strbuf);
        p = sbofs2ptr(sb, sb->usOffset);
        *p = '\0';
        sb->usOffset++;
    }
    return sb;
}

char *sb_alloc(strbuf *sb, char *s)
{
    if (s)
    {
        word len = (word)strlen(s);
            if (((long)sb->usOffset + (long)len) >= (long)sb->usSize)

        *s = STRDELMK;


        for (at = sizeof(strbuf) + 1; at < sb->usOffset; at += len)
        {
            char *p = sbofs2ptr(sb, at);
            len = (word)strlen(p) + 1;
            if (*p != STRDELMK)
                used = p;
        }

