// SPDX-License-Identifier: GPL-2.0-or-later

#pragma off(unreferenced)
static char rcs_id[]="$Id: cppmain.cc,v 1.1.1.1 2002/10/01 17:49:25 sdudley Exp $";
#pragma on(unreferenced)

extern "C" c_main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  return c_main(argc, argv);
}

