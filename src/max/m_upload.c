// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_upload.c,v 1.1.1.1 2002/10/01 17:52:51 sdudley Exp $";
#pragma on(unreferenced)


#include "arcmatch.h"
#include "max_file.h"
#include "max_msg.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


    for (ai = ari; ai; ai = ai->next)
        if (MatchArcType(fd, ai))
            return TRUE;

    return FALSE;
}

void Msg_Upload(void)
{
    FILE *inmsg;
    XMSG msg;

    char temp[PATHLEN];

    int aborted;
    sword protocol;

    FENTRY fent;

    if (local)
    {
        Puts(err999_1);
        InputGets(temp, err999_2);

        return;
    }

    aborted = isareply = isachange = FALSE;

    Blank_Msg(&msg);
    *netnode = '\0';
    *orig_msgid = '\0';


    sprintf(temp, msgtemp_name, blank_str, task_num);


        sf2 = prm.flags2;
        prm.flags2 &= ~(FLAG2_CHECKDUPE | FLAG2_CHECKEXT);

        File_Get_Files(protocol, NULL, PRM(temppath));

        prm.flags2 = sf2;
    }


    if ((inmsg = shfopen(temp, fopen_readb, O_RDONLY | O_BINARY | O_NOINHERIT)) == NULL)
    {
        cant_open(temp);
        Puts(xferaborted);
        unlink(temp);
    }
    else
    {


            for (fn = 0; GetFileEntry(fn, &fent); ++fn)
            {
                sprintf(temp, ss, PRM(temppath), No_Path(fent.szName));
                unlink(temp);
