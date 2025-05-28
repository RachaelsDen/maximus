// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_locate.c,v 1.1.1.1 2002/10/01 17:51:06 sdudley Exp $";
#pragma on(unreferenced)


#include "alc.h"
#include "display.h"
#include "fb.h"
#include "max_file.h"
#include "max_menu.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <share.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static sword near LocateDisplayJunk(byte *fnam, byte *desc, word *attr, char *nonstop, PFAH pfah,
                                    FDAT *dp)
{
    byte *descwork;
    char junk[10];
    sword ret;

    if ((descwork = malloc(MAX_FBBS_ENTRY + 1)) == NULL)
        return DRET_NOMEM;

        sprintf(junk, fbbs_counter, dp->times_dl);


    after = found + strlen(searchfor);

    p = file_desc_col;
    l = strlen(p);
    strocpy(after + l, after);
    memmove(after, file_desc_col, l);


    p = file_found_col;
    l = strlen(p);
    strocpy(found + l, found);
    memmove(found, p, l);

    return TRUE;
}

static byte *near LocateSeekDesc(FDAT *dp, int dmp, byte *curdmp, dword *dmploc, word *dmpb)
{
    byte *desc;


    if (dp->desc < *dmploc || dp->desc >= *dmploc + DMP_BUF_SIZE - 2 ||
        dp->desc + *(word *)(curdmp + (size_t)(dp->desc - *dmploc)) >= *dmploc + DMP_BUF_SIZE - 2)
    {
        *dmploc = lseek(dmp, dp->desc, SEEK_SET);
        *dmpb = read(dmp, (char *)curdmp, DMP_BUF_SIZE);
    }


    desc = curdmp + (size_t)(dp->desc - *dmploc) + sizeof(word);


    if ((desc = malloc(MAX_FBBS_ENTRY + 10)) == NULL)
        return DRET_NOMEM;

    if ((fnam = malloc(MAX_FBBS_ENTRY + 10)) == NULL)
    {
        free(desc);
        return DRET_NOMEM;
    }


    strcpy(fnam, dp->name);


    *s = '\0';


static word near LocateSearchString(FDAT *dp, int dmp, byte *curdmp, dword *dmploc, word *dmpb)
{
    char *desc;

    desc = LocateSeekDesc(dp, dmp, curdmp, dmploc, dmpb);

    return (desc && (stristr_nochin(dp->name, searchfor) || stristr_nochin(desc, searchfor)));
}

static sword near LocateReadFdat(FDAT *da, int dat, int dmp, word attr, char *nstop, PFAH pfah)
{
    FDAT *dp, *dend;

    sword got;
    word doit;
    sword ret = 0;

    byte *curdmp;
    dword dmploc;
    word dmpbytes;


static sword near LocateSearchArea(word attr, char *nstop, PFAH pfah, byte colour)
{
    byte fbbs[PATHLEN];
    byte fdmp[PATHLEN];
    byte fdat[PATHLEN];
    byte *delim, *dot;


    strcpy(usr.files, PFAS(pfah, name));


    Printf(srchng, (char)((colour % 7) + 9), PFAS(pfah, name));
    vbuf_flush();


    if (*FAS(*pfah, filesbbs))
        strcpy(fbbs, FAS(*pfah, filesbbs));
    else
        sprintf(fbbs, ss, FAS(*pfah, downpath), sfiles);


    delim = strrstr(fdat, pdel_only);


    if (dot && (!delim || dot > delim))
        *dot = '\0';


void File_Locate(void)
{
    FAH fa;
    BARINFO bi, biSave;
    HAFF haff;

    byte savearea[MAX_ALEN];
    byte *s;

    byte colour;
    char nonstop;

    int ret;

    memset(&fa, 0, sizeof fa);


        Get_Dos_Date(&usr.date_newfile);
    }
    else
    {
        display_line = display_col = 1;
        Printf(searchingfor, searchfor, '\0');
        logit(log_searchingfor, searchfor);
    }

    first_search = TRUE;

    if ((haff = AreaFileFindOpen(haf, NULL, 0)) == NULL)
        return;

    colour = 0;
    ret = 0;

    biSave.priv = usr.priv;
    biSave.keys = usr.xkeys;
    strcpy(savearea, usr.files);

    for (colour = ret = 0; !halt() && AreaFileFindNext(haff, &fa, FALSE) == 0 &&
                           ret != DRET_BREAK && ret != DRET_NOMEM;
         colour++)
    {


    strcpy(usr.files, savearea);
    usr.priv = biSave.priv;
    usr.xkeys = biSave.keys;
}
