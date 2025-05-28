// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: fixlr.c,v 1.1.1.1 2002/10/01 17:57:23 sdudley Exp $";
#pragma on(unreferenced)

#include "bfile.h"
#include "max.h"
#include <fcntl.h>
#include <io.h>

void FixUser(BFILE b, char *arg, int *piMaxRead)
{
    struct _usr usr;
    int iUserNum = atoi(arg);
    long lSeek = (long)iUserNum * sizeof usr;

    Bseek(b, lSeek, SEEK_SET);

    if (Bread(b, &usr, sizeof usr) != 0)
        puts("Can't read user file");

    printf("User #%d - old lastread %5d - ", iUserNum, usr.lastread_ptr);

    usr.lastread_ptr = ++(*piMaxRead);

    printf("new lastread %5d\n", usr.lastread_ptr);

    Bseek(b, lSeek, SEEK_SET);

    if (Bwrite(b, &usr, sizeof usr) != 0)
        puts("Can't write user file!");
}

int main(int argc, char *argv[])
{
    int iMaxRead = 0;
    struct _usr usr;
    BFILE b;

    if (argc < 3)
    {
        puts("Usage:\n  fixlr <userbbs_path> <user#> [<user#> ...]");
        return 1;
    }

    if ((b = Bopen(argv[1], BO_RDWR | BO_BINARY, BSH_DENYNO, 8192)) == NULL)
    {
        puts("Error opening user file!");
        return 1;
    }

