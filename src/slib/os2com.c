// SPDX-License-Identifier: GPL-2.0-or-later


#ifdef OS_2

#include "modem.h"
#include "prog.h"

void IoPause(void) { ComPause(hcModem); }

void IoResume(void) { ComResume(hcModem); }

#endif
