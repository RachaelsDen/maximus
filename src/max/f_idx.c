// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_idx.c,v 1.1.1.1 2002/10/01 17:51:04 sdudley Exp $";
#pragma on(unreferenced)


#include "f_idx.h"
#include "fb.h"
#include "max_file.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static void near fext(char *name, PFAH pfah, char *ext)
{
    char *dot;

    if (*FAS(*pfah, filesbbs))
        strcpy(name, FAS(*pfah, filesbbs));
    else
    {
        strcpy(name, FAS(*pfah, downpath));
        strcat(name, filesdat_name);
    }

    if ((dot = strrchr(name, '.')) != NULL)
        *dot = '\0';

    strcat(name, ext);
}

IDXF *IndexOpen(char *pat)
{
    IDXF *ix;
    char idxname[PATHLEN];
    char *star, *quest;

    if ((ix = malloc(sizeof(IDXF))) == NULL)
        return NULL;

    memset(ix, '\0', sizeof(IDXF));

    strcpy(idxname, PRM(sys_path));
    strcat(idxname, master_idx);

    if ((ix->ifd = shopen(idxname, O_RDONLY | O_BINARY | O_NOINHERIT)) == -1)
    {
        free(ix);
        return NULL;
    }

    ix->hi = lseek(ix->ifd, 0L, SEEK_END);

    if (ix->hi == -1 || (ix->hi /= sizeof(FIDX)) <= 0)
    {
        close(ix->ifd);
        free(ix);
        return NULL;
    }

    ix->lo = 0L;
    ix->last = -1L;
    ix->next_found_ofs = -1L;


        if (star && (quest == NULL || quest > star))
            ix->pat_len = (star - pat);
        else
            ix->pat_len = (quest - pat);
    }
    else
    {

    while (!ix->found)
    {

        if (ix->last == tryit)
            break;

        ix->last = tryit;


        result = strncmp(ix->pat, ix->fidx.name, ix->pat_len);


            if (!eqstrin(ix->fidx.name, ix->pat, MAX_FN_LEN))
            {
                if (tell(ix->ifd) - (long)(sizeof(FIDX) * 2) >= 0L)
                {
                    lseek(ix->ifd, -(long)(sizeof(FIDX) * 2), SEEK_CUR);

                    while (tell(ix->ifd) > 0L)
                    {
                        if (read(ix->ifd, (char *)&ix->fidx, sizeof(FIDX)) != sizeof(FIDX))
                        {
                            break;
                        }


                        if (!eqstrin(ix->fidx.name, ix->pat, ix->pat_len))
                        {

                        if (tell(ix->ifd) - (long)(sizeof(FIDX) * 2) < 0L)
                            break;

                        lseek(ix->ifd, -(long)(sizeof(FIDX) * 2), SEEK_CUR);
                    }
                }
            }


            ix->found = TRUE;
            ix->next_found_ofs = tell(ix->ifd) - (long)sizeof(FIDX);

            if (ix->next_found_ofs < 0L)
                ix->next_found_ofs = 0L;
        }
        else if (result < 0)
            ix->hi = tryit;
        else
            ix->lo = tryit;
    }

    if (ix->found && ix->next_found_ofs != -1L)
    {

        while (read(ix->ifd, (char *)&ix->fidx, sizeof(FIDX)) == sizeof(FIDX) &&
               (!ix->pat_len || strnicmp(ix->pat, ix->fidx.name, ix->pat_len) == 0))
        {

    ix->next_found_ofs = -1L;
    ix->found = TRUE;
    return -1;
}

void IndexClose(IDXF *ix)
{
    if (ix)
    {
        close(ix->ifd);

        if (ix->pat)
        {
            free(ix->pat);
            ix->pat = NULL;
        }

        free(ix);
    }
}


word FidxIsOkay(FIDX *fidx, FDAT *fdat, char *name, char *path, word check_cur, word check_priv,
                PFAH pfahIn)
{
    BARINFO bi;
    FAH fa;
    HAFF haff;
    PFAH pfah;
    char temp[PATHLEN];
    int ret, dfd;
    long ofs;

    memset(&fa, 0, sizeof fa);
    pfah = pfahIn ? pfahIn : &fa;


    if (!ValidFileArea(NULL, pfah, VA_VAL | VA_PWD | VA_EXTONLY, &bi) ||
        (eqstri(FAS(fah, name), PFAS(pfah, name)) && !check_cur) ||
        !CanAccessFileCommand(pfah, file_tag, 0, &bi))
    {

    fext(temp, pfah, dot_dat);


    if (fdat->flag & (FF_DELETED | FF_COMMENT))
        ret = FALSE;

    close(dfd);


        fext(temp, pfah, dot_dmp);

        if ((dfd = shopen(temp, O_RDONLY | O_BINARY | O_NOINHERIT)) == -1)
            ret = FALSE;
        else
        {

                lseek(dfd, fdat->acs, SEEK_SET);

                if (read(dfd, (char *)&len, sizeof(word)) != sizeof(word))
                    ret = FALSE;

                if ((acs = malloc(len)) == NULL)
                {
                    logit(mem_none);
                    ret = FALSE;
                }
                else
                {

                if (read(dfd, (char *)&len, sizeof(word)) != sizeof(word))
                    ret = FALSE;


            close(dfd);
        }
    }

    if (!pfahIn)
        DisposeFah(&fa);

    return ret;
}


    while (!out && (got = read(fd, (char *)fdbuf, sizeof(FDAT) * NUM_FDAT)) > 0)
    {

                *fdat->name = '\0';
                fdat->flag |= FF_DELETED;

                lseek(fd, -(long)(fdend - fdat) * sizeof(FDAT), SEEK_CUR);
                write(fd, (char *)fdat, sizeof(FDAT));
                out = TRUE;
                break;
            }
    }

    free(fdbuf);
    close(fd);
}
