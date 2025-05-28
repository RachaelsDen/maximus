// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: language.c,v 1.3 2003/06/11 14:52:19 wesgarland Exp $";
#pragma on(unreferenced)

#define MAX_LANG_max_chat
#define MAX_LANG_max_chng
#define MAX_LANG_end

#ifdef INTERNAL_LANGUAGES

#define INITIALIZE_LANGUAGE

#include "mm.h"
#include "prog.h"

void Chg_Language(void) {}


static void near UpdateStaticStrings(void)
{
    cYes = *Yes;
    cNo = *No;
    cNonStop = *M_nonstop;

    if (szHeyDude)
        free(szHeyDude);

    if (szPageMsg)
        free(szPageMsg);

    szHeyDude = strdup(ch_hey_dude_msg);
    szPageMsg = strdup(ch_page_msg);
}


void Set_Lang_Alternate(int usealt) { using_alternate = (usealt && !local) ? TRUE : FALSE; }


    ptrsize = (l->ch->ndefs + l->ch->adefs) * sizeof(HOFS);


    max_len = min(l->ch->hlen, l->max_heap);

    if (read(hfile, l->heap, max_len) != (signed)max_len)
        return FALSE;
    else
        return TRUE;
}


static int Init_Lang_Heap(struct _lang *l)
{
    if ((l->ptrs = (HOFS *)malloc(l->max_ptrs)) == NULL ||
        (l->heap = (char *)malloc(l->max_heap)) == NULL ||
        (l->heapnames = malloc(MAX_HEAPNAMES)) == NULL)
    {
        if (l->ptrs)
            free(l->ptrs);

        logit(log_mem_nolheap);
        return FALSE;
    }

    Blank_Lang(l);

    return TRUE;
}


#ifndef ORACLE
void LanguageCleanup(void)
{
    Deinit_Lang_Heap(&ush);
    Deinit_Lang_Heap(&glh);
    Deinit_Lang_Heap(&syh);
}
#endif


    strcpy(temp, PRM(lang_path));

    if (temp[1] != ':' && temp[0] != '\\' && temp[0] != '/')
    {
        strcpy(temp, PRM(sys_path));
        strcat(temp, PRM(lang_path));
    }

    strcat(temp, name);
    strcat(temp, dotltf);

#else
    sprintf(temp, psps_ltf, PRM(lang_path), name);
#endif


    if ((lf = sopen(temp, O_RDONLY | O_BINARY | O_NOINHERIT, SH_DENYWR, S_IREAD | S_IWRITE)) == -1)
    {
        return -1;
    }


    if (read(lf, l->heapnames, l->inf.hn_len) != l->inf.hn_len)
        return -1;


static void Verify_Language_Date(int fd, char *name)
{
    union stamp_combo ld;

    get_fdt(fd, &ld);

    if (GEdate(&ld, &prmdate))
    {
        if (EQdate(&ld, &prmdate))
        {

            logit("!Language %s has same date as .PRM file; recompile .PRM file with SILT!", name);
            return;
        }

        logit("!Old language %s: recompile .PRM file with SILT!", name);
        quit(ERROR_CRITICAL);
    }
}

    if (ph->inf.file_ptrs != n_lang_ptrs)
    {
        logit("!Language '%s': string count mismatch", name);
        maximus_exit(1);
    }
}


    CheckLangPtrs(&ush, PRM(lang_file[usr.lang]));
    CheckLangPtrs(&syh, PRM(lang_file[0]));

    FileDate(prmname, &prmdate);

    Verify_Language_Date(langfile, PRM(lang_file[usr.lang]));
    Verify_Language_Date(sysfile, PRM(lang_file[0]));


    glh.ch = &ush.hdat[0];
    ReadHeap(langfile, &glh);

    UpdateStaticStrings();


    memmove(&syh.hdat[1], &ush.hdat[1], sizeof(struct _heapdata));
    syh.ch = &syh.hdat[1];
    ReadHeap(langfile, &syh);


static char *HeapPtr(struct _lang *l, int sn)
{

    if (l->heap && l->ptrs)
    {
        if (sn < l->ch->ndefs)
        {


            if (using_alternate && sn < l->ch->adefs)
                sn += l->ch->ndefs;


static char *HeapOfs(struct _lang *l, int sn) { return HeapPtr(l, sn - l->ch->start_num); }

static char *heapnm(struct _lang *l, struct _heapdata *h) { return l->heapnames + h->heapname; }


        ush.ch = NULL;


                ush.ch = &ush.hdat[heap];
                ReadHeap(langfile, &ush);

#ifdef TEST_VER
                if (debug_ovl)
                    logit(">@Lang: %02x", heap);
#endif
                return HeapPtr(&ush, strn);
            }
        }

        return "";
    }
}


    if (ush.ch && InHeap(strn, ush.ch))
    {
        return HeapOfs(&ush, strn);
    }
    else if (glh.ch && InHeap(strn, glh.ch))
    {
        return HeapOfs(&glh, strn);
    }
    else if (syh.ch && InHeap(strn, syh.ch))
    {
        return HeapOfs(&syh, strn);
    }
    else
    {

        ush.ch = NULL;


                ush.ch = &ush.hdat[heap];
                ReadHeap(langfile, &ush);

#ifdef TEST_VER
                if (debug_ovl)
                    logit(">@Lang: %02x", heap);
#endif
                return HeapOfs(&ush, strn);
            }
        }

        return "";
    }
}


    glh.ch = &ush.hdat[0];
    ReadHeap(langfile, &glh);

    UpdateStaticStrings();
}


void Chg_Language(void)
{
    int lang;

    if ((lang = Get_Language()) == -1)
        return;

    usr.lang = lang;

    Switch_To_Language();

    if (*language_change)
    {
        Puts(language_change);
        Press_ENTER();
    }
}

#ifndef ORACLE

int Language_Save_Heap(void)
{
    word x;

    if (ush.ch == 0)
        return -1;

    for (x = 0; x < MAX_HEAP && x < ush.inf.n_heap; x++)
    {
        if (ush.ch == &ush.hdat[x])
            return x;
    }

    return -1;
}

