// SPDX-License-Identifier: GPL-2.0-or-later



#include "prog.h"
#include <stdio.h>

int _fast isleap(int year) { return (divby(year, 400) || (!divby(year, 100) && divby(year, 4))); }
