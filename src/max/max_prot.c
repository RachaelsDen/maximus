// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: max_prot.c,v 1.1.1.1 2002/10/01 17:52:00 sdudley Exp $";
#pragma on(unreferenced)

#include "max_file.h"
#include "mm.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


    p = PRM(protocol_max);

    if (*p)
        strcpy(fname, p);
    else
        sprintf(fname, "%sprotocol.max", PRM(sys_path));

    if ((fd = shopen(fname, O_RDONLY | O_BINARY | O_NOINHERIT)) == -1)
    {
        cant_open(fname);
        return FALSE;
    }

    seekit = sizeof(struct _proto) * protocol;

    if (lseek(fd, seekit, SEEK_SET) == seekit &&
        read(fd, (char *)pro, sizeof(struct _proto)) == sizeof(struct _proto))
    {
        ret = TRUE;
    }

    close(fd);

    return ret;
}


    Parse_Outside_Cmd(pro->log, fname);
    unlink(fname);


    if (pro->flag & P_OPUS)
    {
        if (local)
            fprintf(ctl, xctl_keyboard);
        else
            fprintf(ctl, xctl_port_baud, port + 1, bd);

        if (!local)

    for (n = 0; GetFileEntry(n, &fent); n++)
    {
        fprintf(ctl, ul ? pro->ulstr : pro->dlstr, fent.szName);
        fputc('\n', ctl);
    }


    Parse_Outside_Cmd(pro->log, fname);

    if ((log = fopen(fname, fopen_read)) == NULL)
    {
        cant_open(fname);
        return FALSE;
    }

    while (fgets(line, LOGLEN, log))
    {
        char *ulstr, *dlstr, *got, *desc;
        word ul;
        word fn;


            ul = (ulstr && (dlstr == NULL || ulstr < dlstr));
            got = (ul ? ulstr : dlstr);
        }
        else
        {

        getword(got, fname, ctl_delim, pro->fnamword + 1);


        for (fn = 0; GetFileEntry(fn, &fent); fn++)
            if (eqstri(No_Path(fent.szName), No_Path(fname)))
                break;

        if (fn == FileEntries())
            memset(&fent, 0, sizeof fent);


        if (ul)
        {
            strcpy(tempname, No_Path(fname));
            fent.szName = tempname;


            sprintf(fname, ss, FAS(fah, uppath), fent.szName);
        }
        else
        {
            fent.szName = fname;
        }


    if (gotfile)
    {
        Parse_Outside_Cmd(pro->log, fname);
        unlink(fname);

        Parse_Outside_Cmd(pro->ctl, fname);
        unlink(fname);
    }

    return gotfile;
}
