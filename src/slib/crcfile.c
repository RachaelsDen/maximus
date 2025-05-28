// SPDX-License-Identifier: GPL-2.0-or-later


#include "crc.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

dword *cr3tab;

#define CRCBUFSIZE 16384

main(int argc, char *argv[])
{
    int fd, got;
    char *buf;
    dword crc;
    char *p;

    cr3tab = mkcrc32tab();

    if (argc < 2 || (fd = shopen(argv[1], O_RDONLY | O_BINARY)) == NULL)
    {
        printf("Can't open `%s'\n", argv[1]);
        return 1;
    }

    if ((buf = malloc(CRCBUFSIZE)) == NULL)
    {
        printf("Out of memory!\n");
        return 1;
    }

    printf("CRCing %s...\n", argv[1]);

    for (crc = ~0; (got = read(fd, (char *)buf, CRCBUFSIZE)) > 0;)
    {
        char *e = buf + got;

        for (p = buf; p < e;)
            crc = xcrc32(*p++, crc);
    }

