// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <dos.h>

#if defined(__MSDOS__)

#define INT_CRITERR 0x24

#ifdef __FLAT__
#include <conio.h>
#pragma aux newint24h parm[];

void __interrupt newint24h(dword rgs, dword rfs, dword res, dword rds, dword redi, dword resi,
                           dword rebp, dword resp, dword rebx, dword redx, dword recx,
                           dword volatile reax)
{
    NW(redi);
    NW(redx);
    NW(recx);
    NW(rebx);
    NW(rebp);
    NW(resi);
    NW(resp);
    NW(rds);
    NW(res);
    NW(rfs);
    NW(rgs);

    if (reax & 0x8000)
    {
        cputs("Critical error ");

        cputs((reax & 0x0100) ? "writing " : "reading ");
        cputs("drive ");
        putch('A' + (char)(reax & 0xff));
        cputs(":\r\n");
    }
    else
    {
        cputs("Critical error accessing device\r\n");
    }


#ifdef TEST_HARNESS

#include <dos.h>
#include <fcntl.h>
#include <io.h>
#include <stdlib.h>

main()
{
    int fd;

    install_24();
    printf("hoop-la!\n");

    if ((fd = open("a:asdf", O_RDONLY | O_BINARY)) != -1)
    {
        printf("\nopen successful.\n");
        close(fd);
    }
    else
        printf("\nopen failed.\n");

    if ((fd = open("com3", O_CREAT | O_TRUNC | O_WRONLY | O_BINARY)) != -1)
    {
        printf("\nopen successful.\n");

        if (write(fd, 0, 5) != 5)
            printf("Write unsuccessful!\n");

        close(fd);
    }
    else
        printf("\nopen failed.\n");

    if ((fd = open("b:gronk", O_CREAT | O_TRUNC | O_WRONLY | O_BINARY)) != -1)
    {
        printf("\nopen successful.\n");

        if (write(fd, 0, 5) != 5)
            printf("Write unsuccessful!\n");

        close(fd);
    }
    else
        printf("\nopen failed.\n");

    printf("done!\n");
    uninstall_24();
    return 0;
}

#endif
