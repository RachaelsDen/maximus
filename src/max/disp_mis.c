// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: disp_mis.c,v 1.1.1.1 2002/10/01 17:50:51 sdudley Exp $";
#pragma on(unreferenced)


#include "display.h"
#include "max_area.h"
#include "max_menu.h"
#include "mm.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *Ordinal(long number)
{
    number %= 100L;

    if (number > 10L && number < 20L)
        return ordinal_th;

    switch (number % 10L)
    {
    case 1L:
        return ordinal_st;

    case 2L:
        return ordinal_nd;

    case 3L:
        return ordinal_rd;

    default:
        return ordinal_th;
    }
}


void Get_To_Blank(char *s, FILE *f)
{
    char *orig;
    int c, s1, s2;

    orig = s;

    while (((c = fgetc(f)) > 32) || c == 25)
    {
                *s++ = (char)s1;

    if (c == 13)
        fgetc(f);

    *s = '\0';

        {
            s1 = *++s;

            if (s1)
            {
                s2 = *++s;

                if (s2)
                {
char *Get_BBS_String(char *string, FILE *bbsfile, int max)
{
    fgets(string, max, bbsfile);
    Fix_RLE(string);
    Trim_Line(string);

    return string;
}
#endif

void Add_Full_Path(char *src, char *dest)
{
    char *temp;

    if ((temp = malloc(PATHLEN)) == NULL)
        return;

    if (src[1] == ':' || *src == '\\' || *src == '/' || *src == '.')
        strcpy(dest, src);
    else
        sprintf(dest, ss, original_path, src);

    if (dest[1] != ':')
    {
        temp[0] = *original_path;
        temp[1] = ':';
        temp[2] = '\0';
        strcat(temp, dest);
        strcpy(dest, temp);
    }

    free(temp);
}

word Priv_Code(int ch, int action)
{
    word priv;

    if (ch >= '1' && ch <= '8')
    {
        if (action == 'Q')
        {
            if (!UserHasKey(ch - '1'))
                return SKIP_LINE;
            else
                return SKIP_NONE;
        }
        else if (action == 'X')
        {
            if (UserHasKey(ch - '1'))
                return SKIP_LINE;
            else
                return SKIP_NONE;
        }
        else
            return SKIP_LINE;
    }

    priv = ClassKeyLevel(toupper(ch));

    switch (action)
    {
        return (usr.priv != priv) ? SKIP_NONE : SKIP_LINE;

        return (GEPriv(usr.priv, priv)) ? SKIP_NONE : SKIP_LINE;
    }


int BbsRunOpt(option opt_type, char *arg)
{
    struct _amenu *menu;
    struct _opt *opt;
    unsigned uiFlag;
    char *p;


    if ((opt = menu->opt = malloc(sizeof(struct _opt))) == NULL)
    {
        free(menu);
        return -1;
    }


    memset(opt, '\0', sizeof(struct _opt));


    p = menu->menuheap;
    *p++ = '\0';


    strcpy(p, ClassDesc(cls));

    opt->type = opt_type;
    opt->priv = p - menu->menuheap;
    opt->areatype = AREATYPE_ALL;

    RunOption(menu, opt, 0, NULL, &uiFlag, "");

    free(menu->menuheap);
    free(menu->opt);
    free(menu);

    return 0;
}

#endif
