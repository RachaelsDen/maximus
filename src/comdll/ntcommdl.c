// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: ntcommdl.c,v 1.1.1.1 2002/10/01 17:49:34 sdudley Exp $";
#pragma on(unreferenced)

#include <stdio.h>
#include <windows.h>

#define NO_RUNTIME

int APIENTRY LibMain(HANDLE hdll, DWORD reason, LPVOID reserved)
{
#if 0
        switch( reason ) {
         case DLL_THREAD_ATTACH:
             break;
         case DLL_PROCESS_ATTACH:
             break;
         default:
         }
#endif
}

#ifdef NO_RUNTIME
int __DLLstart(HANDLE hdll, DWORD reason, LPVOID reserved)
{
    return LibMain(hdll, reason, reserved);
}
#endif
