// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_sflo.c,v 1.2 2003/06/05 03:13:40 wesgarland Exp $";
#pragma on(unreferenced)

#include "prog.h"
#include "squish.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0

#define MAX_SFLO 255

#define BSTAT_NONE 'N'
#define BSTAT_BUSY 'B'


short OutToSflo(void)
{
  MATCHOUT *moOut;
  NETADDR naFind={ZONE_ALL, NET_ALL, NODE_ALL, POINT_ALL};
  FILE *fpSflo;
  byte flav;
  char szHeader[MAX_SFLO];
  char *szDomain="fidonet.org";
  char *szType;

#ifndef UNIX
  if ((fpSflo=shfopen("SUPERFLO.DAT", "w+b",
#else
  if ((fpSflo=shfopen("superflo.dat", "w+b",
#endif
                      O_CREAT | O_TRUNC | O_WRONLY | O_BINARY))==NULL)
  {
    (void)printf("Error creating SuperFLO!\n");
    return -1;
  }
  
  if ((moOut=MatchOutOpen(&config, &naFind, MATCH_ALL, 0))==NULL)
  {
    (void)fclose(fpSflo);
    return -1;
  }
  
  do
  {
