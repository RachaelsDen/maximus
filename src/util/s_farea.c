// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: s_farea.c,v 1.1.1.1 2002/10/01 17:57:41 sdudley Exp $";
#pragma on(unreferenced)


#define SILT
#define NOVARS
#define NOINIT
#define NO_MSGH_DEF

#include "s_farea.h"
#include "max.h"
#include "prog.h"
#include "s_heap.h"
#include "silt.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static unsigned cbLast = 0;
static word division = 0;
static char prefix[PATHLEN] = "";

static void near FiltBarricade(void *v, char *words[], char *line)
{
    NW(line);

    if (!*words[1] || !*words[2])
    {
        printf("\n\aError!  Two args needed for Barricade keyword on line %d!\n", linenum);
        Compiling(-1, NULL, NULL);
    }

    HeapAdd(&PFI(v)->h, &PFI(v)->fa.barricademenu, words[1]);
    HeapAdd(&PFI(v)->h, &PFI(v)->fa.barricade, words[2]);
}

static void near FileAreaWrite(FAINFO *pfi, int closeit)
{
    static int fa_fd = -1;
    static int fai_fd = -1;
    unsigned size;
    OVRLIST ol;
    struct _mfidx mfi;

    if (!do_farea)
        return;

    if (!pfi && fa_fd != -1 && closeit)
    {
        FAREA fa;
        long pos = lseek(fa_fd, 0L, SEEK_END);


        pos -= cbLast + ADATA_START;

        lseek(fa_fd, ADATA_START, SEEK_SET);

        if (read(fa_fd, (char *)&fa, sizeof fa) != sizeof fa)
        {
            printf("Error reading final file area data!\n");
            exit(1);
        }

        lseek(fa_fd, ADATA_START, SEEK_SET);

        fa.cbPrior = -pos;

        if (write(fa_fd, (char *)&fa, sizeof fa) != sizeof fa)
        {
            printf("Error writing final file area data!\n");
            exit(1);
        }

        close(fa_fd);
        close(fai_fd);
        fa_fd = -1;
        return;
    }

    if (fa_fd == -1 && !closeit)
    {
        char fname[PATHLEN];
        dword dwId = FAREA_ID;

        if (strings[prm.farea_name] == 0)
        {
            printf("Error!  FILEAREA.CTL cannot be SILTed separately.  Use\n"
                   "\"SILT MAX\" and ensure that you have a \"Files farea\"\n"
                   "keyword in the Session Section.\n");
            exit(1);
        }

        strcpy(fname, strings + prm.farea_name);
        strcat(fname, ".dat");

        if ((fa_fd = sopen(fname, O_CREAT | O_TRUNC | O_RDWR | O_BINARY, SH_DENYNO,
                           S_IREAD | S_IWRITE)) == -1)
        {
            printf("Can't open file area data file %s!\n", fname);
            exit(1);
        }

        strcpy(fname, strings + prm.farea_name);
        strcat(fname, ".idx");

        if (write(fa_fd, (char *)&dwId, sizeof dwId) != sizeof dwId)
        {
            printf("\aError writing key to file data file %s\n", fname);
            exit(1);
        }

        if ((fai_fd = sopen(fname, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, SH_DENYNO,
                            S_IREAD | S_IWRITE)) == -1)
        {
            printf("Can't open file area index file %s!\n", fname);
            exit(1);
        }
    }

    if (pfi)
    {

        if ((pfi->fa.attribs & (FA_DIVBEGIN | FA_DIVEND)) == 0)
            if (pfi->fa.downpath && (pfi->fa.attribs & FA_SLOW) == 0)
                assert_dir(pfi->h.heap + pfi->fa.downpath);

        strnncpy(mfi.name, pfi->h.heap + pfi->fa.name, sizeof(mfi.name));
        mfi.name_hash = SquishHash(pfi->h.heap + pfi->fa.name);
        mfi.ofs = tell(fa_fd);

        if (write(fai_fd, (char *)&mfi, sizeof mfi) != sizeof mfi)
            ErrWrite();


        for (ol = pfi->ol; ol; ol = ol->next)
            if (write(fa_fd, (char *)&ol->or, sizeof ol->or) != sizeof ol->or)
                ErrWrite();


static void near FiltType(void *v, char *words[], char *line)
{

    for (w = 1; w < MAX_PARSE_WORDS && *words[w]; w++)
    {
        for (pst = style_tab; pst->name; pst++)
            if (eqstri(words[w], pst->name))
            {
                PFI(v)->fa.attribs |= pst->mask;
                break;
            }

        if (!pst->name)
            Unknown_Ctl(linenum, words[w]);
    }
}

void FileAreaClose(void) { FileAreaWrite(NULL, TRUE); }

int ParseFileArea(FILE *ctlfile, char *name)
{
    char line[PATHLEN];
    char fullname[PATHLEN];
    static FAINFO fi;
    OVRLIST ol;

    struct _vbtab verbs[] = {{0, "acs", &fi.fa.acs},
                             {FiltPath, "download", &fi.fa.downpath},
                             {FiltPath, "upload", &fi.fa.uppath},
                             {FiltBarricade, "barricade", NULL},
                             {0, "filelist", &fi.fa.filesbbs},
                             {0, "desc", &fi.fa.descript},
                             {0, "description", &fi.fa.descript},
                             {FiltType, "type", NULL},
                             {FiltMenuname, "menuname", NULL},
                             {FiltOverride, "override", NULL},
                             {0, "app", NULL},
                             {0, "application", NULL},
                             {0, NULL, NULL}};

    if (strchr(name, '.'))
        BadDivisionName();


    prefix[strlen(prefix) - 1] = 0;

