// SPDX-License-Identifier: GPL-2.0-or-later


#include "arc_def.h"
#include <fcntl.h>
#include <io.h>
#include <string.h>

int _fast MatchArcType(int fd, struct _arcinfo *ai)
{
    char temp[50];
    int id_len;

    if (ai == NULL || ai->id == NULL)
        return 0;

    id_len = strlen(ai->id);

    if (ai->id_ofs < 0L)
        lseek(fd, -(long)id_len + ai->id_ofs + 1, SEEK_END);
    else
        lseek(fd, ai->id_ofs, SEEK_SET);

    read(fd, (char *)temp, id_len);

    return (strncmp(ai->id, temp, id_len) == 0);
}
