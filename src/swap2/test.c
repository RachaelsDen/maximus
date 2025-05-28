// SPDX-License-Identifier: GPL-2.0-or-later


#include "exec.h"
#include <stdio.h>

int cdecl do_spawn(int swapping, char *execfname, char *cmdtail, unsigned envlen, char *envp);

char *max_swap_filename = "test.swp";

int main()
{
    int rc;

    printf("ready to swap\n");

    rc = do_exec("command.com", "", USE_EMS | USE_XMS | USE_FILE, 0xffff, NULL);

    printf("rc = %d\n", rc);
    printf("done swap\n");
    return 0;
}
