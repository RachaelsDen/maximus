// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_tag.c,v 1.1.1.1 2002/10/01 17:51:10 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_main

#include "alc.h"
#include "max_file.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static void near File_Tag_Delete(void);
static void near File_Tag_List(void);

void File_Tag(int dl_cmd)
{
    byte ch;

    if (local)
        baud = 38400L;

    if (!*linebuf)
        File_Tag_List();

    for (;;)
    {
        WhiteN();

        ch = (byte)toupper(KeyGetRNP(dl_cmd ? file_edit_menu : tag_menu));

        WhiteN();

        if (ch == tag_keys[0] && !dl_cmd)
        {
            File_Get_Download_Names(TAG_VERBOSE, PROTOCOL_ZMODEM);

        while (*p && isdigit(*p))
            ++p;

        if (*p && (++p, isdigit(*p)))
        {
            ft = (word)atoi(p);
            if (ft <= fn)
                ft = fn;
        }

        if (ft > FileEntries())
            ft = FileEntries();

        --fn;
        --ft;


                strcpy(fname, No_Path(fent.szName));
                RemoveFileEntry(fn);


#ifndef ORACLE

static char *last_tag_name = NULL;

static void near make_tag_save_name(char *buf, char *pszFname)
{
    if (!pszFname || !*pszFname)
        pszFname = default_tag_save;

    if (strchr(pszFname, '%'))
        Parse_Outside_Cmd(pszFname, buf);
    else
        strcpy(buf, pszFname);

    Convert_Star_To_Task(buf);
}

int save_tag_list(char *pszFname)
{
    FILE *fp;
    char temp[PATHLEN];

    if (last_tag_name)
    {
        free(last_tag_name);
        last_tag_name = NULL;
    }
    make_tag_save_name(temp, pszFname);
    if ((fp = shfopen(temp, fopen_write, O_CREAT | O_TRUNC | O_WRONLY)) != NULL)
    {
        FENTRY fent;
        int n;

        for (n = 0; GetFileEntry(n, &fent); ++n)
            fprintf(fp, "%s %ld %04x\n", fent.szName, fent.ulSize, fent.fFlags);

        fclose(fp);
        last_tag_name = strdup(temp);
        return TRUE;
    }
    return FALSE;
}

int restore_tag_list(char *pszFname, int fNoDelete)
{
    FILE *fp;
    char temp[PATHLEN];

    Free_Filenames_Buffer(0);

    if (pszFname == NULL && last_tag_name)
        strcpy(temp, last_tag_name);
    else
        make_tag_save_name(temp, pszFname);

    if ((fp = shfopen(temp, fopen_read, O_RDONLY)) != NULL)
    {
        char buf[PATHLEN];

        while (fgets(buf, PATHLEN - 1, fp) != NULL)
        {
            char fname[PATHLEN];
            long size;
            int flag = 0;

            flag = 0;

            if (sscanf(buf, "%s %ld %x", fname, &size, &flag) >= 2)
                AddFileEntry(fname, flag, size);
        }

        fclose(fp);

        if (!fNoDelete)
            unlink(temp);

        return TRUE;
    }

    return FALSE;
}

