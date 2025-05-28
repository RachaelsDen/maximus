// SPDX-License-Identifier: GPL-2.0-or-later


#include "max_msg.h"
#include "mm.h"
#include <string.h>


        if (prm.flags2 & FLAG2_UMSGID)
            *pmsgnum = MsgUidToMsgn(sq, *pmsgnum, UID_EXACT);
    }

    return !!*pmsgnum;
}
