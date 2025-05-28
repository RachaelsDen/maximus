// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: piper.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)

#error Obsolete.  This program is no longer in the distribution


#define MAX_INCL_VER

#include "ffind.h"
#include "max.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _sys110
{




static int _stdc stcomp(const void *arg1, const void *arg2)
{
    static char a1[10], a2[10];

    if (strlen((char *)arg1) <= 1)
    {
        a1[0] = '0';
        a1[1] = *(char *)arg1;
        a1[2] = '\0';
    }
    else
        strcpy(a1, (char *)arg1);

    if (strlen((char *)arg2) <= 1)
    {
        a2[0] = '0';
        a2[1] = *(char *)arg2;
        a2[2] = '\0';
    }
    else
        strcpy(a2, (char *)arg2);

    return (strcmp(a1, a2));
}

int OpusToMaxPriv(byte opriv);

int _stdc main(int argc, char *argv[])
{
    FILE *areasfile, *dirbbs, *areasbbs;

    FFIND *ff, *ffo;

    struct _sys sys;
    struct _sys110 sys110;
    static struct _ab abbs[NUM_ABBS];

    char temp[80], *p;

    int x, y, ret, sysfile, maxsys, abbs_num, dat, sn;

    char sysname[255][3];

    NW(argc);
    NW(argv);

    abbs_num = 0;

    Hello("PIPER", "Maximus Control File Converter", VERSION, "1990, " THIS_YEAR_LAST);

#warning hard-coded filenames inappropriate for unix

    if (fexist("AREAS.CTL"))
    {
        printf("`AREAS.CTL' already exists;  Overwrite [y,N]? ");
        fgets(temp, 80, stdin);

        printf("\n");

        if (toupper(*temp) != 'Y')
        {
            printf("Aborted!\n");
            return -1;
        }

        if (fexist("AREAS.BAK"))
            unlink("AREAS.BAK");

        rename("AREAS.CTL", "AREAS.BAK");
    }

#ifndef UNIX
    if ((areasbbs = fopen("AREAS.BBS", "r")) != NULL || (areasbbs = fopen("ECHO.CTL", "r")) != NULL)
#else
    if ((areasbbs = fopen("etc/areas.bbs", "r")) != NULL ||
        (areasbbs = fopen("etc/echo.ctl", "r")) != NULL)
#endif
    {
        while (fgets(temp, 80, areasbbs) != NULL)
        {
            if (abbs_num >= NUM_ABBS - 1)
            {
                printf("Too many areas in echomail control file -- continuing...\n");
                break;
            }

            if (strchr(temp, ';'))
                *strchr(temp, ';') = '\0';

            if (*temp)
            {
                p = temp;

            {
                sysname[maxsys][0] = '0';
                sysname[maxsys][1] = '\0';
            }
            else
            {
                sysname[maxsys][0] = ff->szName[6];

                if (ff->szName[7] == '.')
                    sysname[maxsys][1] = '\0';
                else
                {
                    sysname[maxsys][1] = ff->szName[7];
                    sysname[maxsys][2] = '\0';
                }
            }

            ret = FindNext(ff);
        }

        FindClose(ff);
    }

    qsort(sysname, maxsys, sizeof(sysname[0]), stcomp);

    for (sn = 0; sn < maxsys; sn++)
    {
        printf("\rProcessing area %s...  ", sysname[sn]);

        if (dat)
        {
            sscanf(sysname[sn], "%x", &x);

            if (x < 100)
                fprintf(areasfile, "Area %d\n", x);
            else
            {
                y = 'A';

                while (x >= 100 + 26)
                {
                    y++;
                    x -= 26;
                }

                x -= 100;

                fprintf(areasfile, "Area %c%c\n", y, 'A' + x);
            }

            sprintf(temp, "SYSTEM%s.DAT", sysname[sn]);

            if ((sysfile = open(temp, O_RDONLY | O_BINARY)) == -1)
                printf("Can't open `%s' -- Continuing...\n", temp);
            else
            {
                read(sysfile, (char *)&sys110, sizeof(struct _sys110));
                close(sysfile);

                if (*sys110.msgpath)
                    fprintf(areasfile, "        MsgAccess       %s\n",
                            Priv_Level(OpusToMaxPriv(sys110.MsgPriv)));

                if (*sys110.filepath)
                {
                    fprintf(areasfile, "        FileAccess      %s\n\n",
                            Priv_Level(OpusToMaxPriv(sys110.FilePriv)));
                    fprintf(areasfile, "        FileInfo        %s\n", sys110.filtitle);
                    fprintf(areasfile, "        Download        %s\n", sys110.filepath);
                }

                if (*sys110.uppath)
                    fprintf(areasfile, "        Upload          %s\n", sys110.uppath);

                if (*sys110.listpath)
                    fprintf(areasfile, "        FileList        %s\n", sys110.listpath);

                if (*sys110.msgpath)
                {
                    fprintf(areasfile, "\n        MsgInfo         %s\n", sys110.msgtitle);

                    sprintf(temp, "%sORIGIN.*", sys110.msgpath);

                    ffo = FindOpen(temp, 0);

                    if (ffo && (sys110.attrib & ECHO))
                    {
                        sprintf(temp, "%s%s", sys110.msgpath, ffo->szName);

                        if ((dirbbs = fopen(temp, "r")) != NULL)
                        {
                            fgets(temp, 80, dirbbs);
                            fclose(dirbbs);

                            if (temp[x = strlen(temp) - 1] == '\n')
                                temp[x] = '\0';

                            if (strlen(ffo->szName) <= 7)
                                x = 0;
                            else if (sscanf(ffo->szName, "ORIGIN.%x", &x) != 1)
                                x = 0;

                            fprintf(areasfile, "        Origin          %d %s\n", x, temp);
                        }
                    }

                    FindClose(ffo);

                    if ((sys110.attrib & ECHO) && *sys110.EchoName)
                        fprintf(areasfile, "        MsgName         %s\n", sys110.EchoName);

                    if (*sys110.barrpath)
                        fprintf(areasfile, "        Barricade       %s\n", sys110.barrpath);

                    if (sys110.attrib & ECHO)
                        strcpy(temp, "EchoMail");
                    else if (sys110.attrib & SYSMAIL)
                        strcpy(temp, "Matrix  ");
                    else
                        strcpy(temp, "Local   ");

                    fprintf(areasfile, "        %s        %s\n\n", temp, sys110.msgpath);

                    if ((sys110.attrib & NOPRIVATE) && (sys110.attrib & NOPUBLIC))
                        fprintf(areasfile, "        Read-Only\n");
                    else if (sys110.attrib & NOPRIVATE)
                        fprintf(areasfile, "        Public Only\n");
                    else if (sys110.attrib & NOPUBLIC)
                        fprintf(areasfile, "        Private Only\n");
                    else
                        fprintf(areasfile, "        Public and Private\n");

                    if (sys110.attrib & ANON_OK)
                        fprintf(areasfile, "        Anonymous OK\n");
                }
            }
        }
        else
        {
            fprintf(areasfile, "Area %s\n", sysname[sn]);

            if (eqstri(sysname[sn], "0"))
                strcpy(temp, "SYSTEM.BBS");
            else
                sprintf(temp, "SYSTEM%s.BBS", sysname[sn]);

            if ((sysfile = open(temp, O_RDONLY | O_BINARY)) == -1)
                printf("Can't open `%s' -- Continuing...\n", temp);
            else
            {
                read(sysfile, (char *)&sys, sizeof(struct _sys));
                close(sysfile);

                if (*sys.msgpath)
                    fprintf(areasfile, "        MsgAccess       %s\n", Priv_Level(sys.priv));

                if (*sys.filepath)
                    fprintf(areasfile, "        FileAccess      %s\n", Priv_Level(sys.priv));

                if (*sys.filepath)
                {
                    fprintf(areasfile, "\n");

                    sprintf(temp, "%sDIR.BBS", sys.filepath);

                    if ((dirbbs = fopen(temp, "r")) != NULL)
                    {
                        fgets(temp, 80, dirbbs);
                        fclose(dirbbs);

                        if (temp[x = strlen(temp) - 1] == '\n')
                            temp[x] = '\0';

                        fprintf(areasfile, "        FileInfo        %s\n", temp);
                    }

                    fprintf(areasfile, "        Download        %s\n", sys.filepath);
                }

                if (*sys.uppath)
                    fprintf(areasfile, "        Upload          %s\n", sys.uppath);

                if (*sys.msgpath)
                {
                    sprintf(temp, "%sDIR.BBS", sys.msgpath);

                    fprintf(areasfile, "\n");

                    if ((dirbbs = fopen(temp, "r")) != NULL)
                    {
                        fgets(temp, 80, dirbbs);
                        fclose(dirbbs);

                        if (temp[x = strlen(temp) - 1] == '\n')
                            temp[x] = '\0';

                        fprintf(areasfile, "        MsgInfo         %s\n", temp);
                    }

                    sprintf(temp, "%sORIGIN.*", sys.msgpath);

                    ffo = FindOpen(temp, 0);

                    if (ffo && (sys.attrib & ECHO))
                    {
                        sprintf(temp, "%s%s", sys.msgpath, ffo->szName);

                        if ((dirbbs = fopen(temp, "r")) != NULL)
                        {
                            fgets(temp, 80, dirbbs);
                            fclose(dirbbs);

                            if (temp[x = strlen(temp) - 1] == '\n')
                                temp[x] = '\0';

                            if (strlen(ffo->szName) <= 7)
                                x = 0;
                            else if (sscanf(ffo->szName, "ORIGIN.%x", &x) != 1)
                                x = 0;

                            fprintf(areasfile, "        Origin          %d %s\n", x, temp);
                        }
                    }

                    FindClose(ffo);

                    if (sys.attrib & ECHO)
                    {
                        for (x = 0; x < abbs_num; x++)
                            if (eqstri(sys.msgpath, abbs[x].path))
                            {
                                fprintf(areasfile, "        MsgName         %s\n", abbs[x].tag);
                                break;
                            }

                        if (x == abbs_num)
                            fprintf(areasfile, "        MsgName         ?\n");
                    }


                    if (fexist(sys.bbspath))
                        fprintf(areasfile, "        Barricade       %s\n", sys.bbspath);

                    if (sys.attrib & ECHO)
                        strcpy(temp, "EchoMail");
                    else if (sys.attrib & SYSMAIL)
                        strcpy(temp, "Matrix  ");
                    else
                        strcpy(temp, "Local   ");

                    fprintf(areasfile, "        %s        %s\n\n", temp, sys.msgpath);

                    if ((sys.attrib & NOPRIVATE) && (sys.attrib & NOPUBLIC))
                        fprintf(areasfile, "        Read-Only\n");
                    else if (sys.attrib & NOPRIVATE)
                        fprintf(areasfile, "        Public Only\n");
                    else if (sys.attrib & NOPUBLIC)
                        fprintf(areasfile, "        Private Only\n");
                    else
                        fprintf(areasfile, "        Public and Private\n");

                    if (sys.attrib & ANON_OK)
                        fprintf(areasfile, "        Anonymous OK\n");
                }
            }
        }

        fprintf(areasfile, "End Area\n\n");
    }

    fclose(areasfile);

    printf("\r                     \rAll done!\n");

    return 0;
}

int OpusToMaxPriv(byte opriv)
{
    switch (opriv)
    {
    case _SYSOP:
        return SYSOP;

    case _ASSTSYSOP:
        return ASSTSYSOP;

    case _CLERK:
        return CLERK;

    case _EXTRA:
        return EXTRA;

    case _FAVORED:
        return FAVORED;

    case _PRIVEL:
        return PRIVIL;

    case _WORTHY:
        return WORTHY;

    case _NORMAL:
        return NORMAL;

    case _LIMITED:
        return LIMITED;

    case _DISGRACE:
        return DISGRACE;

    case _TWIT:
        return TWIT;

    default:
        return HIDDEN;
    }
}
