// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: joho.c,v 1.2 2003/06/04 23:23:43 wesgarland Exp $";
#pragma on(unreferenced)

#include "fdnode.h"
#include "msgapi.h"
#include "prog.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


    lseek(fd, 0L, SEEK_SET);

    if (read(fd, (char *)&c, sizeof(c)) != sizeof(c))
        return FALSE;


    lastrec = -1;
    rec = c.hdr.master_idx;
    max = (word)(lseek(fd, 0L, SEEK_END) / lbsize);
    gotit = FALSE;


        for (i = 0; i < inf->nodes; i++)
        {
            g = (struct _gdx *)(fdb + sizeof(struct _inf) + rec_size * i);

            if ((diff = (*compare)(find, g)) <= 0)
            {
                    gotit = TRUE;

                break;
            }

            last = g->block_num;
        }


        if (!gotit)
            rec = last;
    }

    free(fdb);


int JoHoFetch(void *f, struct _johofile *jf, struct _johonode *jn)
{
    struct _gdx *g = (struct _gdx *)f;
    char *buf;
    char comma[] = ",";
    char *p;
    long ofs;
    int pvt, point, fd;

    pvt = !!(g->nlofs & PVT_NODELIST);
    point = !!(g->nlofs & POINT_NODELIST);

    fd = pvt ? jf->pfd : point ? jf->ppfd : jf->nfd;
    ofs = g->nlofs & ~(PVT_NODELIST | POINT_NODELIST);

    if (lseek(fd, ofs, SEEK_SET) != ofs)
        return FALSE;

    if ((buf = malloc(MAX_NL_SIZE)) == NULL)
        return FALSE;

    buf[MAX_NL_SIZE - 1] = '\0';

    if (read(fd, buf, MAX_NL_SIZE - 1) != MAX_NL_SIZE && !strchr(buf, '\r'))
    {
        free(buf);
        return FALSE;
    }

    if ((p = strchr(buf, '\r')) != NULL)
        *p = '\0';

    for (p = buf; (p = strchr(p, '_')) != NULL; p++)
        *p = ' ';

    p = strtok(buf, comma);
    strncpy(jn->system, p, 79);
    jn->system[79] = '\0';
    p = strtok(NULL, comma);
    strncpy(jn->city, p, 29);
    jn->city[29] = '\0';
    p = strtok(NULL, comma);
    strncpy(jn->sysop, p, 35);
    jn->sysop[35] = '\0';
    p = strtok(NULL, comma);
    strncpy(jn->phone, p, 39);
    jn->phone[39] = '\0';
    p = strtok(NULL, comma);
    jn->baud = atol(p);
    p += strlen(p) + 1;
    strncpy(jn->flags, p, 79);
    jn->flags[79] = '\0';

    free(buf);

    return TRUE;
}


#ifndef UNIX
    sprintf(name, "%sNODELIST.FDX", path);
#else
    sprintf(name, "%nodelist.fdx", path);
#endif

    if ((jf->fdfd = shopen(name, O_RDONLY | O_BINARY | O_NOINHERIT)) == -1)
        return FALSE;


    strncpy(ext, c.nl_ext, 3);
    ext[3] = '\0';

#ifndef UNIX
    sprintf(name, "%sNODELIST.%3s", path, ext);
#else
    ext[0] = tolower((int)ext[0]);
    ext[1] = tolower((int)ext[1]);
    ext[2] = tolower((int)ext[2]);
    sprintf(name, "%snodelist.%3s", path, ext);
#endif

    if ((jf->nfd = shopen(name, O_RDONLY | O_BINARY | O_NOINHERIT)) == -1)
    {
        close(jf->fdfd);
        return FALSE;
    }


#ifndef UNIX
    sprintf(name, "%sFDNET.PVT", path);
#else
    sprintf(name, "%sfdnet.pvt", path);
#endif

    jf->pfd = shopen(name, O_RDONLY | O_BINARY | O_NOINHERIT);


#ifndef UNIX
    sprintf(name, "%sFDPOINT.PVT", path);
#else
    sprintf(name, "%sfdpoint.pvt", path);
#endif

    jf->ppfd = shopen(name, O_RDONLY | O_BINARY | O_NOINHERIT);

    return TRUE;
}

int JoHoClose(struct _johofile *jf)
{
    if (jf->fdfd != -1)
        close(jf->fdfd);

    if (jf->nfd != -1)
        close(jf->nfd);

    if (jf->pfd != -1)
        close(jf->pfd);

    if (jf->ppfd != -1)
        close(jf->ppfd);

    if (jf->ufd != -1)
        close(jf->ufd);

    jf->fdfd = -1;
    jf->nfd = -1;
    jf->pfd = -1;
    jf->ppfd = -1;
    jf->ufd = -1;
    return 0;
}
