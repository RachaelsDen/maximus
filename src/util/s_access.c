// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_access.c,v 1.2 2003/06/05 03:18:58 wesgarland Exp $";
#pragma on(unreferenced)


#define SILT
#define NOVARS
#define NOINIT

#include "dr.h"
#include "max.h"
#include "opusprm.h"
#include "prog.h"
#include "silt.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define ACSHEAPLEN 2048
#define ACSNO 32

void Add_Access(struct _clsrec *cls);

static char *acsheap;
static int acsofs;
static int clalloc;

CLH clh;
PCLH pclh = &clh;

static void near Init_Access(void);
static void near Init_Class(struct _clsrec *cls, char *name);
static word near InsertClassHeap(char *s);

int ParseAccess(FILE *ctlfile, char *name)
{
    int x;
    struct _clsrec thiscls;

    return 0;
}

static void near Init_Access(void)
{
    if (!acsheap)
    {
        if ((acsheap = malloc(ACSHEAPLEN)) == NULL)
            NoMem();

        clh.usn = 0;
        clh.ussize = sizeof(struct _clsrec);
        if ((clh.pcInfo = malloc(clh.ussize * ACSNO)) == NULL)
            NoMem();
        clalloc = ACSNO;
        clh.pHeap = acsheap;
        pclh = &clh;

        acsheap[0] = '\0';
        acsofs = 1;
    }
}

static void near Init_Class(struct _clsrec *cls, char *name)
{
    memset(cls, '\0', sizeof(struct _clsrec));


void Add_Access(struct _clsrec *cls)
{

    for (i = 0; i < clh.usn; ++i)
    {
        char *p = acsheap + clh.pcInfo[i].zAbbrev;

        if (eqstri(nm, p))
        {
            printf("\nError! Class `%s' has already been defined\n", nm);
            Compiling(-1, NULL, NULL);
            return;
        }

        if (cls->usLevel == clh.pcInfo[i].usLevel)
        {
            printf("\nWarning! Class `%s' has the same priv level as `%s' (%d)\n", nm, p,
                   cls->usLevel);
            Compiling(-1, NULL, NULL);
        }

        if (cls->usKey && cls->usKey == clh.pcInfo[i].usKey)
        {
            printf("\nWarning! Class `%s' has the same priv key as `%s' (%c)\n", nm, p, cls->usKey);
            Compiling(-1, NULL, NULL);
        }
    }


    if (clh.usn > 1)
        qsort(clh.pcInfo, clh.usn, sizeof(*cls), cmpclass);


    if (prm_class < MAXCLASS && cls->usOldPriv != 11 && cls->usOldPriv != (word)-1)
    {
        prm.cls[prm_class].priv = cls->usOldPriv;
        prm.cls[prm_class].max_time = cls->usTimeDay;
        prm.cls[prm_class].max_call = cls->usTimeCall;
        prm.cls[prm_class].max_dl = cls->ulFileLimit;
        prm.cls[prm_class].ratio = cls->usFileRatio;
        prm.cls[prm_class].min_baud = cls->usMinBaud * 100;
        prm.cls[prm_class].min_file_baud = cls->usFileBaud * 100;
        prm_class++;
    }
}


    if (isdigit(*p) || *p == '-')
        return (word)atol(p);

    n = strcspn(p, " \t/,-=+<>()&|");
    for (i = 0; i < clh.usn; ++i)
    {
        CLSREC *pcr = ClassRec(i);
        char *cName = clh.pHeap + pcr->zAbbrev;
        char *cAlias = clh.pHeap + pcr->zAlias;

        if ((strnicmp(cName, p, n) == 0 && cName[n] == '\0') ||
            (strnicmp(cAlias, p, n) == 0 && cAlias[n] == '\0'))
        {
            return pcr->usLevel;
        }
    }

    if (stricmp(p, "noaccess") == 0)
        return (int)(unsigned int)(word)-1;

    printf("\a\nInvalid priv `%s' on line %d of CTL file!\n", p, linenum);
    exit(1);
}

int ClassLevelIndex(word usLevel) { return Deduce_Class((int)usLevel); }
