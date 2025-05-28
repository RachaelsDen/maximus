// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: msgapi.c,v 1.1.1.1 2002/10/01 17:54:25 sdudley Exp $";
#pragma on(unreferenced)

#define MSGAPI_INIT

#include "msgapi.h"
#include "alc.h"
#include "apidebug.h"
#include "max.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>

static byte *intl = "INTL";
static byte *fmpt = "FMPT";
static byte *topt = "TOPT";
static byte *area_colon = "AREA:";

#ifdef OS_2
#endif

#if defined(__MSDOS__)
#endif

unsigned _SquishCloseOpenAreas(void);

    (void)usTermCode;

    _SquishCloseOpenAreas();


    DosExitList(EXLST_EXIT, 0);
}

int __dll_initialize(void)
{
    extern char startup_txt[];
    grow_handles(40);


    DosExitList(EXLST_ADD, __DLLend);
    return 1;
}

#endif
#endif


    if (mi.req_version >= 1)
    {
        if (mi.palloc)
            palloc = mi.palloc;

        if (mi.pfree)
            pfree = mi.pfree;

        if (mi.repalloc)
            repalloc = mi.repalloc;

        if (mi.farpalloc)
            farpalloc = mi.farpalloc;

        if (mi.farpfree)
            farpfree = mi.farpfree;

        if (mi.farrepalloc)
            farrepalloc = mi.farrepalloc;
    }

    return 0;
}

sword MAPIENTRY MsgCloseApi(void) { return _SquishCloseOpenAreas() ? 0 : -1; }

HAREA MAPIENTRY MsgOpenArea(byte OS2FAR *name, word mode, word type)
{
    if (type & MSGTYPE_SQUISH)
        return (SquishOpenArea(name, mode, type));
    else
        return (SdmOpenArea(name, mode, type));
}

sword MAPIENTRY MsgValidate(word type, byte OS2FAR *name)
{
    if (type & MSGTYPE_SQUISH)
        return (SquishValidate(name));
}


sword MAPIENTRY InvalidMsgh(HMSG msgh)
{
    if (msgh == NULL || msgh->id != MSGH_ID || MsgInvalidHarea(msgh->ha))
    {
        msgapierr = MERR_BADH;
        return TRUE;
    }

    return FALSE;
}


static word near _CopyToBuf(byte *p, byte *out, byte **end, unsigned remaining)
{
    word len = 0;

    if (out)
        *out++ = '\x01';

    len++;

    for (; remaining > 0 && (*p == '\x0d' || *p == '\x0a' || *p == (byte)0x8d);)
    {
        p++;
        remaining--;
    }

    while (remaining > 0 && *p == '\x01' || strncmp(p, area_colon, 5) == 0)
    {

    if (out)
        *out = '\0';

    len++;


    if (end)
        *end = p;

    return len;
}


void MAPIENTRY MsgFreeCtrlToken(char *cbuf) { pfree(cbuf); }

byte OS2FAR *MAPIENTRY CopyToControlBuf(byte OS2FAR *txt, byte OS2FAR *OS2FAR *newtext,
                                        unsigned OS2FAR *length)
{
    byte *cbuf, *end;

    word clen;


#define SAFE_CLEN 20

    if ((cbuf = palloc(clen + SAFE_CLEN)) == NULL)
        return NULL;

    (void)memset(cbuf, '\0', clen + SAFE_CLEN);


        norig = *orig;
        ndest = *dest;


        if (ndest.net == dest->net && ndest.node == dest->node && norig.net == orig->net &&
            norig.node == orig->node)
        {
            *dest = ndest;
            *orig = norig;


            RemoveFromCtrl(ctrl, intl);
        }
    }


    if ((s = GetCtrlToken(ctrl, topt)) != NULL)
    {
        dest->point = (word)atoi(s + 5);
        pfree(s);

        RemoveFromCtrl(ctrl, topt);
    }
}

byte OS2FAR *MAPIENTRY CvtCtrlToKludge(byte OS2FAR *ctrl)
{
    byte *from;
    byte *buf;
    byte *to;
    size_t clen;

    clen = strlen(ctrl) + NumKludges(ctrl) + 20;

    if ((buf = palloc(clen)) == NULL)
        return NULL;

    to = buf;


        if (!eqstrn(from + 1, area_colon, 5))
            *to++ = *from;

        from++;

        while (*from && *from != '\x01')
            *to++ = *from++;

        *to++ = '\r';
    }

    *to = '\0';

    return buf;
}

void MAPIENTRY RemoveFromCtrl(byte OS2FAR *ctrl, byte OS2FAR *what)
{
    byte *search;
    byte *p, *s;

    if ((search = palloc(strlen(what) + 2)) == NULL)
        return;

    (void)strcpy(search, "\x01");
    (void)strcat(search, what);

