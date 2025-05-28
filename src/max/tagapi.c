// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: tagapi.c,v 1.1.1.1 2002/10/01 17:53:09 sdudley Exp $";
#pragma on(unreferenced)

#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef OS_2
#define INCL_DOS
#include "pos2.h"
#endif

#include "max_msg.h"
#include "tagapip.h"

#include "ffind.h"

static char szTagSuffix[] = "\x01%s\x01";
static char szEmptyList[] = "\x01";


int TagReadTagFile(struct _mtagmem *pmtm)
{
    struct _mtagidx mti;

    memset(pmtm, 0, sizeof *pmtm);



int TagWriteTagFile(struct _mtagmem *pmtm)
{
    char fnamei[PATHLEN];
    char fnamed[PATHLEN];
    FILE *fpi, *fpd;
    struct _mtagidx mti;
    long ofs;

    sprintf(fnamei, mtag_idx, PRM(sys_path));
    sprintf(fnamed, mtag_dat, PRM(sys_path));


    if (pmtm->dwLen > mti.dwLen)
    {
        _TagReuseIdx(&mti, usr.lastread_ptr);


        if (mti.dwOffset == -1)
            mti.dwOffset = 0;
    }

    if ((fpi = fopen(fnamei, fexist(fnamei) ? fopen_readpb : fopen_writepb)) == NULL)
    {
        cant_open(fnamei);
        return FALSE;
    }

    if ((fpd = fopen(fnamed, fexist(fnamed) ? fopen_readpb : fopen_writepb)) == NULL)
    {
        cant_open(fnamed);
        fclose(fpi);
        return FALSE;
    }


    while (ftell(fpi) < ofs)
    {
        struct _mtagidx mti_new;

        memset(&mti_new, 0, sizeof mti_new);

        if (fwrite(&mti_new, sizeof mti_new, 1, fpi) != 1)
            break;
    }

    fseek(fpi, ofs, SEEK_SET);

    if (fwrite(&mti, sizeof mti, 1, fpi) != 1)
        logit(cantwrite, fnamei);

    fseek(fpd, mti.dwOffset, SEEK_SET);

    if (pmtm->pbAreas)
    {


int TagQueryTagList(struct _mtagmem *pmtm, char *pszArea)
{
    char szAreaName[PATHLEN];

    if (!pmtm->pbAreas)
        return FALSE;

    sprintf(szAreaName, szTagSuffix, pszArea);

    return stristr(pmtm->pbAreas, szAreaName) != NULL;
}


        if ((pmtm->pbAreas = (char *)malloc(MTAG_PAD_SIZE)) == NULL)
            return FALSE;

        strcpy(pmtm->pbAreas, szEmptyList);

        pmtm->dwUsed = 1;
        pmtm->dwLen = MTAG_PAD_SIZE;
    }

    sprintf(szAreaName, szTagSuffix, pszArea);


    if (pmtm->dwUsed + strlen(szAreaName) + 1 >= pmtm->dwLen)
    {
        if ((pmtm->pbAreas = (char *)realloc(pmtm->pbAreas, pmtm->dwLen + MTAG_PAD_SIZE)) == NULL)
            return FALSE;


int TagDeleteTagList(struct _mtagmem *pmtm, char *pszArea)
{
    char szAreaName[PATHLEN];
    char *p, *e;

    if (!pmtm->pbAreas)
        return FALSE;

    sprintf(szAreaName, szTagSuffix, pszArea);


    e = p + strlen(szAreaName) - 1;

    memmove(p, e, strlen(e) + 1);


static int _TagGetMtagMem(struct _mtagidx *pmti, struct _mtagmem *pmtm)
{
    char fname[PATHLEN];
    FILE *fp;

    sprintf(fname, mtag_dat, PRM(sys_path));


static void near _TagNewPmtm(struct _mtagmem *pmtm)
{
    pmtm->pbAreas = (char *)malloc(MTAG_PAD_SIZE);

    if (pmtm->pbAreas)
        strcpy(pmtm->pbAreas, szEmptyList);

    pmtm->dwLen = MTAG_PAD_SIZE;
    pmtm->dwUsed = 1;
}


static int near _TagPackMessages(FILE *in_i, FILE *in_d, FILE *out_i, FILE *out_d, int recnum)
{
  struct _mtagidx mti_in, mti_out;
  byte *pbBuf;
  int processed=0;

  logit(log_repacking_mtag);

  if ((pbBuf=(byte *)malloc(PACK_BUF_SIZE))==NULL)
  {
    logit(mem_none);
    return FALSE;
  }


    if (processed++ != recnum && mti_out.dwLen)
    {
      mti_out.dwOffset=ftell(out_d);


      fseek(in_d, mti_in.dwOffset, SEEK_SET);



static int near _TagRepackMtag(int recnum)
{
  char ifnamei[PATHLEN];
  char ifnamed[PATHLEN];
  char ofnamei[PATHLEN];
  char ofnamed[PATHLEN];

  FILE *in_i, *in_d;
  FILE *out_i, *out_d;

  int rc;

  sprintf(ifnamei, mtag_idx, PRM(sys_path));
  sprintf(ifnamed, mtag_dat, PRM(sys_path));

  sprintf(ofnamed, "%smtagdat.$$$", PRM(sys_path));
  sprintf(ofnamei, "%smtagidx.$$$", PRM(sys_path));


  if ((out_d=fopen(ofnamed, fopen_writeb))==NULL)
  {
    fclose(in_i);
    fclose(in_d);
    cant_open(ofnamed);
    return FALSE;
  }

  if ((out_i=fopen(ofnamei, fopen_writeb))==NULL)
  {
    fclose(out_d);
    fclose(in_i);
    fclose(in_d);
    cant_open(ofnamed);
    return FALSE;
  }



  unlink(ifnamed);
  rename(ofnamed, ifnamed);

  unlink(ifnamei);
  rename(ofnamei, ifnamei);

  return rc;
}
#endif


    if (!pmti->dwLen)
        return TRUE;

    sprintf(fname, mtag_fre, PRM(sys_path));

    if ((fd = shopen(fname, O_WRONLY | O_BINARY)) == -1)
        fd = sopen(fname, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_DENYNO, S_IREAD | S_IWRITE);

    if (fd == -1)
        return FALSE;

    lseek(fd, 0L, SEEK_END);


    if (len > MAX_MTAG_FRE * (long)sizeof mtf)
    {

static int near _TagReuseIdx(struct _mtagidx *pmti, int recnum)
{

static int near _TagReadIdx(struct _mtagidx *pmti)
{
    char fname[PATHLEN];
    long lOfs;
    int fd;

    sprintf(fname, mtag_idx, PRM(sys_path));

    if ((fd = shopen(fname, O_RDONLY | O_BINARY)) == -1)
        fd = sopen(fname, O_WRONLY | O_BINARY, SH_DENYNO, S_IREAD | S_IWRITE);

    if (fd == -1)
        return FALSE;


        memset(pmti, 0, sizeof *pmti);

        while (lseek(fd, 0L, SEEK_END) < lOfs)
            if (write(fd, (char *)pmti, sizeof *pmti) != sizeof *pmti)
            {
                close(fd);
                return FALSE;
            }
    }

    close(fd);

    return TRUE;
}
