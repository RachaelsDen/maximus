// SPDX-License-Identifier: GPL-2.0-or-later


#include "prog.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

sword _fast uniqrename(char *from, char *toorig, char *final,
                       int(_fast *pfnMove)(char *fromfile, char *tofile))
{
    int tsize = strlen(toorig) + 30;
    char *to = (char *)malloc(tsize);
    char *bs, *dot, *add;
    sword ret;
    unsigned fex;
    word i;

    memset(to, '\0', tsize);
    strcpy(to, toorig);

    ret = 0;

    if (!fexist(from))
        ret = -1;
    else
        while ((fex = fexist(to)) != FALSE ||
               (pfnMove ? (*pfnMove)(from, to) : rename(from, to)) != 0)
        {
            if (!fex && (errno == ENOTSAM || !fexist(to)
#ifndef __TURBOC__
                         || errno == EXDEV
#endif
                         ))
            {
                ret = -1;
                break;
            }


            if (dot == NULL || dot < bs)
                strcat(to, ".000");


            for (i = 1; i <= 3; i++)
                if (dot[i] == '\0')
                    dot[i] = '0';

            add = dot + 3;

            for (add = dot + 3; add >= to; add--)
            {
                if (*add >= '0' && *add <= '9')
                {
                    if (*add == '9')
                        *add = '0';
                    else
                    {
                        (*add)++;
                        break;
                    }
                }
                else if (*add == '/' || *add == '\\' || *add == ':')
                {
                    free(to);
