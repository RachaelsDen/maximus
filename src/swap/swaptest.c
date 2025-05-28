// SPDX-License-Identifier: GPL-2.0-or-later


#include <dos.h>
#include <errno.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "swap.h"


int swap_return;
unsigned char exec_return;
unsigned char *comspec;
unsigned int dos_ptr;

main(int argc, char *argv[])
{

    printf("Hello--we are now in SWAPTEST.  We are about to execute a DOS shell.\n\n");

    if (!xms_installed())
        printf("No ");
    printf("XMS driver detected.\n");

    if (!ems4_installed())
        printf("No ");
    printf("EMS 4.0 driver detected.\n");


#if 1
    {
        char *p1;
        char *p2;
        char *p3;

        p1 = malloc(50000);
        p2 = malloc(50000);
        p3 = malloc(50000);

        printf("p1=%x\n", p1);
        printf("p2=%x\n", p2);
        printf("p3=%x\n", p3);
    }
#else

#ifdef __TURBOC__
    allocmem(512u, &dos_ptr);
#else
    _dos_allocmem(1024, (unsigned short *)&dos_ptr);
#endif
#endif

    printf("\n**test without swapping!\n");

    {
        char *args[2] = {"c:\\os2\\mdos\\command.com", NULL};
        int rc;

        rc = spawnvp(P_WAIT, args[0], args);

        printf("rc=%d, errno=%d, args='%s'\n", rc, errno, args[0]);
    }

    printf("\n** Type EXIT to return to SWAPTEST **\n");

    comspec = getenv("COMSPEC");

    swap_return = swap(comspec, "", &exec_return, "swaptest.fil");

    printf("\n\nBack in SWAPTEST now.\n\n");

    switch (swap_return)
    {
    case SWAP_OK:
        printf("Successful, executed program returned %d.\n", (int)exec_return);
        break;

    case SWAP_NO_SHRINK:
        printf("Unable to shrink DOS memory block.\n");
        break;

    case SWAP_NO_SAVE:
        printf("Unable to save program to memory or disk.\n");
        break;

    case SWAP_NO_EXEC:
        printf("DOS EXEC call failed.  Error is %d: ", (int)exec_return);
        switch (exec_return)
        {
        case BAD_FUNC:
            printf("Bad function.\n");
            break;
        case FILE_NOT_FOUND:
            printf("Program file not found.\n");
            break;
        case ACCESS_DENIED:
            printf("Access to program file denied.\n");
            break;
        case NO_MEMORY:
            printf("Insufficient memory to run program.\n");
            break;
        case BAD_ENVIRON:
            printf("Bad environment.\n");
            break;
        case BAD_FORMAT:
            printf("Bad format.\n");
            break;
        default:
            printf("Unexpected error code #%d (decimal).\n", (int)exec_return);
            printf("Consult DOS technical reference manual.\n");
            break;
        }
    }

    return (0);
}
