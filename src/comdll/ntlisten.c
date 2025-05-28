// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: ntlisten.c,v 1.1.1.1 2002/10/01 17:49:35 sdudley Exp $";
#pragma on(unreferenced)

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char *argv[])
{
    HANDLE hp;
    char buf[2];
    DWORD got;
    FILE *fp;

    if ((fp = fopen("listen.log", "a")) == NULL)
    {
        printf("Can't open listen.log\n");
        return 1;
    }

    if ((hp = CreateNamedPipe(argv[1], PIPE_ACCESS_INBOUND,
                              PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, 0, 0, 2000,
                              NULL)) == INVALID_HANDLE_VALUE)
    {
        printf("Error opening named pipe %s\n", argv[1]);
        exit(1);
    }

    for (;;)
    {
        printf("Waiting to connect to client.\n");

        if (!ConnectNamedPipe(hp, NULL))
        {
            printf("ConnectNamedPipe returned error %d\n", GetLastError());
            exit(1);
        }

        printf("Connected to client.\n");

        while (ReadFile(hp, buf, 1, &got, NULL))
        {
            fwrite(buf, 1, 1, fp);
            printf("%c", buf[0]);
            fflush(stdout);
        }

        printf("Disconnecting from pipe\n");

        DisconnectNamedPipe(hp);
    }

    fclose(fp);
    CloseHandle(hp);
}
