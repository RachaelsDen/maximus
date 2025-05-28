// SPDX-License-Identifier: GPL-2.0-or-later



extern int cdecl do_exec(char *xfn, char *pars, int spawn, unsigned needed, char **envp);



#define USE_EMS 0x01
#define USE_XMS 0x02
#define USE_FILE 0x04
#define EMS_FIRST 0x00
#define XMS_FIRST 0x10
#define HIDE_FILE 0x40
#define NO_PREALLOC 0x100
#define CHECK_NET 0x200

#define USE_ALL (USE_EMS | USE_XMS | USE_FILE)


typedef int(spawn_check_proc)(int cmdbat, int swapping, char *execfn, char *progpars);
extern spawn_check_proc *spawn_check;


typedef struct
{
} prep_block;

extern prep_block swap_prep;
