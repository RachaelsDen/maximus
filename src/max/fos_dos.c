// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: fos_dos.c,v 1.1.1.1 2002/10/01 17:50:57 sdudley Exp $";
#pragma on(unreferenced)


#include "mm.h"
#include "modem.h"
#include "prog.h"
#include <conio.h>
#include <dos.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __MSDOS__

static int fossil_installed = FALSE;

void fossil_getxy(char *row, char *col)
{
    union REGS r;

    if (fossil_installed)
    {
        r.h.ah = 0x12;
#ifdef __386__
        int386(0x14, &r, &r);
#else
        int86(0x14, &r, &r);
#endif
    }
{
    union REGS regs;
    struct SREGS sregs;
    extern int cdecl port;

    if (fossil_installed)
    {
        regs.h.ah = FOSSIL_info;

#ifdef __386__
        regs.w.cx = sizeof(*finfo);
        sregs.es = FP_SEG(finfo);
        regs.w.di = FP_OFF(finfo);
        regs.w.dx = port;
        int386x(0x14, &regs, &regs, &sregs);
#else
        regs.x.cx = sizeof(*finfo);
        sregs.es = FP_SEG(finfo);
        regs.x.di = FP_OFF(finfo);
        regs.x.dx = port;
        int86x(0x14, &regs, &regs, &sregs);
#endif
    }
    else
    {

#ifdef __386__
#endif

        finfo->size = sizeof(struct _fossil_info);
        finfo->majver = 5;
        finfo->minver = 0;
        finfo->id = (char far *)"None";

        finfo->input_size = finfo->input_free = finfo->output_size = finfo->output_free = 0x1000;


        finfo->height = (char)((*(int far *)MK_FP(0x0000, 0x044c) / finfo->width) >> 1);

{
    extern int cdecl port;

    CallFossil(FOSSIL_deinit, 0);
    fossil_installed = FALSE;
    return 0;
}



int mdm_blockwrite(int max_chars, char *offset)
{
    union REGS r;
    struct SREGS sr;
    extern int cdecl port;
    void far *fptr = offset;

    r.h.ah = FOSSIL_blockwrite;
    sr.es = FP_SEG(fptr);

#ifdef __386__
    r.w.cx = max_chars;
    r.w.di = FP_OFF(fptr);
    r.w.dx = port;

    int386(0x14, &r, &r);

    return (r.w.ax);
#else
    r.x.cx = max_chars;
    r.x.di = FP_OFF(fptr);
    r.x.dx = port;

    int86x(0x14, &r, &r, &sr);

    return (r.x.ax);
#endif
}


    case DUMP_OUTPUT:
        CallFossil(FOSSIL_dumpout, 0);

        if (prm.flags & FLAG_break_clr)
            mdm_break(10);

        Delay(10);
        break;

    default:
        return -1;
    }

    return 0;
}


sword mdm_getc(void) { return (mdm_avail() ? mdm_ggetcw() : -1); }


word mdm_ctrlc(word mask)
{
    return (!local && (CallFossil(FOSSIL_ctrlc, mask) & 0x00ff) == 0x0001);
}

word out_empty(void) { return (local ? TRUE : (mdm_status() & STATUS_OUTEMPTY)); }

word mdm_avail(void) { return (local ? FALSE : (mdm_status() & STATUS_ANYDATA)); }

word real_carrier(void) { return (mdm_status() & prm.carrier_mask); }

word carrier(void)
{
    if (no_dcd_check || local)
        return TRUE;

    return real_carrier();
}

