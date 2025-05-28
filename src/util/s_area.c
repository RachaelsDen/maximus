// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_area.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)

#define SILT
#define NOVARS
#define NOINIT
#define NO_MSGH_DEF

#include "areaapi.h"
#include "areadat.h"
#include "bfile.h"
#include "max.h"
#include "newarea.h"
#include "prog.h"
#include "s_heap.h"
#include "s_marea.h"
#include "silt.h"
#include "skiplist.h"
#include <ctype.h>
#include <string.h>

#define HIDDEN 0x000b

typedef struct
{
    dword offset;
    char name[1];
} A2DATA;

void canonslash(char *orig, char *dest, int max)
{
    char buf[PATHLEN];

    strnncpy(buf, orig, min(max, PATHLEN));

    if (strlen(buf) != 3 || buf[1] != ':')
        Strip_Trailing(buf, PATH_DELIM);

    strcpy(dest, *buf ? make_fullfname(buf) : "");
}

int _stdc mystrcmp(void *v1, void *v2)
{
    A2DATA *a1 = v1;
    A2DATA *a2 = v2;

    return strcmp(a1->name, a2->name);
}


static void near ACSToPriv(char *aname, char *acs, sword *piPriv, dword *pdKeys)
{
    NW(aname);

static void near AddAttrib(struct _area *pa, int attrib)
{
    int i;

    for (i = 0; i < 12; i++)
        pa->attrib[i] |= attrib;
}


    if (do_ul2areas)
    {
        char *p;


        if (p)
            strocpy(name, p + 1);
    }


    if ((pa2Found = SkipSearchList(sl, pa2)) != NULL)
    {
        Bseek(bDat, pa2Found->offset, BSEEK_SET);
        fUpdate = TRUE;

        if (Bread(bDat, &a, sizeof a) != sizeof a)
        {
            printf("Error reading existing file area from offset %" INT32_FORMAT " (area %s)\n",
                   pa2Found->offset, name);
            exit(1);
        }

        Bseek(bDat, pa2Found->offset, BSEEK_SET);
    }
    else
    {
        memset(&a, 0, sizeof a);
        a.id = AREA_ID;
        a.struct_len = sizeof a;
        a.type = MSGTYPE_SDM;
        a.msgpriv = a.filepriv = HIDDEN;
        a.origin_aka = -1;
    }

    free(pa2);
    pa2 = NULL;

    strncpy((char *)&a.areano, name, 2);
    strnncpy(a.name, name, 39);
    strupr2((char *)&a.areano);
    a.type = pmah->ma.type;

    canonslash(PMAS(pmah, path), a.msgpath, 80);

    if (a.type & MSGTYPE_SDM)
        Add_Trailing(a.msgpath, PATH_DELIM);

    strnncpy(a.msgname, PMAS(pmah, echo_tag), 40);
    strnncpy(a.msginfo, PMAS(pmah, descript), 80);
    canonslash(PMAS(pmah, barricade), a.msgbar, 80);
    strnncpy(a.origin, PMAS(pmah, origin), 62);
    ACSToPriv(name, PMAS(pmah, acs), &a.msgpriv, &a.msglock);
    a.origin_aka = 0;


    if (pmah->ma.attribs & MA_READONLY)
        AddAttrib(&a, NOPUBLIC | NOPRIVATE);
    else if ((pmah->ma.attribs & (MA_PVT | MA_PUB)) == (MA_PVT | MA_PUB))
        ;
    else if (pmah->ma.attribs & MA_PVT)
        AddAttrib(&a, NOPUBLIC);
    else if (pmah->ma.attribs & MA_PUB)
        AddAttrib(&a, NOPRIVATE);

    if (pmah->ma.attribs & MA_NET)
        AddAttrib(&a, SYSMAIL);

    if (pmah->ma.attribs & MA_ECHO)
        AddAttrib(&a, ECHO);

    if (pmah->ma.attribs & MA_CONF)
        AddAttrib(&a, CONF);

    if (pmah->ma.attribs & MA_ANON)
        AddAttrib(&a, ANON_OK);

    if (pmah->ma.attribs & MA_NORNK)
        AddAttrib(&a, NREALNAME);

    if (pmah->ma.attribs & MA_REAL)
        AddAttrib(&a, UREALNAME);

    if (pmah->ma.attribs & MA_ALIAS)
        AddAttrib(&a, UALIAS);


    memset(&aidx, 0, sizeof aidx);
    aidx.offset = Btell(bDat);
    strncpy(aidx.name, name, sizeof aidx.name);


void AddFileArea(BFILE bDat, BFILE bNdx, BFILE bIdx, PFAH pfah, SLIST *sl)
{
    struct _area a;
    struct _aidx aidx;
    struct _102aidx aidx102;
    word wExists;
    A2DATA *pa2;
    char *name;

    if ((name = strdup(PFAS(pfah, name))) == NULL)
        NoMem();

        char *p;
        while ((p = strchr(name, '.')))
            *p = '_';
    }
    else if (do_short2areas)
    {

    if (pfah->fa.attribs & (FA_DIVBEGIN | FA_DIVBEGIN))
        a.filepriv = HIDDEN;

    memset(&aidx, 0, sizeof aidx);
    aidx.offset = Btell(bDat);
    strncpy(aidx.name, name, sizeof aidx.name);


void Generate20Areas(void)
{
    static char szErrOpen[] = "\nError opening '%s' for write!\n";
    char *pszDat;
    char *pszIdx;
    char pszNdx[PATHLEN];
    SLIST *sl;
    BFILE bDat, bNdx, bIdx;
    MAH mah = {0};
    FAH fah = {0};
    HAF haf;
    HAFF haff;
    char *p;

    printf("\nWriting Max 2.x-compatible AREA.DAT/NDX/IDX files...");

    if ((sl = SkipCreateList(16, 8, mystrcmp)) == NULL)
    {
        printf("Can't allocate memory for skip list!\n");
        exit(1);
    }

    pszDat = strings + prm.adat_name;
    pszIdx = strings + prm.aidx_name;
    strcpy(pszNdx, pszIdx);

    if ((p = stristr(pszNdx, ".idx")) == NULL)
        strcat(pszNdx, ".ndx");
    else
        strcpy(p, ".ndx");


    if ((haf = AreaFileOpen(strings + prm.farea_name, FALSE)) == NULL)
    {
        printf("Error opening file data file %s for read!\n", strings + prm.marea_name);
        exit(1);
    }

    if ((haff = AreaFileFindOpen(haf, NULL, AFFO_DIV)) != NULL)
    {
        while (AreaFileFindNext(haff, &fah, FALSE) == 0)
            AddFileArea(bDat, bNdx, bIdx, &fah, sl);

        AreaFileFindClose(haff);
    }

    AreaFileClose(haf);
    DisposeFah(&fah);

