// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mex.c,v 1.1.1.1 2002/10/01 17:52:23 sdudley Exp $";
#pragma on(unreferenced)

#define MEX_VM

#include "mex.h"
#include "max_file.h"
#include "max_msg.h"
#include "md5.h"
#include "mm.h"
#include "modem.h"
#include "prog.h"
#include "userapi.h"
#include <io.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef MEX

#include "mex_max.h"
#include "mexint.h"
#include "mexp.h"
#include "vm.h"

struct _mex_instance_stack *pmisThis = 0;


static VMADDR EnterSymtabBlank(char *szName, int iSize)
{
    VMADDR vma;

    vma = MexEnterSymtab(szName, iSize);

    if (vma)
        memset(MexDSEG(vma), 0, iSize);

    return vma;
}


int EXPENTRY intrin_setup(void)
{
    int i;
    struct _mex_instance_stack *pmis;


    pmis->vmaLinebuf = MexStoreString("input", linebuf);

    pmis->vmaID = EnterSymtabBlank("id", sizeof(struct mex_instancedata));
    pmis->vmaUser = EnterSymtabBlank("usr", sizeof(struct mex_usr));
    pmis->vmaMarea = EnterSymtabBlank("marea", sizeof(struct mex_marea));
    pmis->vmaFarea = EnterSymtabBlank("farea", sizeof(struct mex_farea));
    pmis->vmaMsg = EnterSymtabBlank("msg", sizeof(struct mex_msg));
    pmis->vmaSys = EnterSymtabBlank("sys", sizeof(struct mex_sys));


    pmis->pmid = MexDSEG(pmis->vmaID);
    pmis->pmid->instant_video = 1;
    pmis->pmid->task_num = task_num;
    pmis->pmid->local = local;

#if defined(NT)
    pmis->pmid->port = local ? 0 : (word)ComGetHandle(hcModem);
#elif defined(OS_2)
    pmis->pmid->port = ComGetFH(hcModem);
#else
    pmis->pmid->port = port + 1;
#endif

    pmis->pmid->speed = baud;
    pmis->pmid->alias_system = !!(prm.flags & FLAG_alias);
    pmis->pmid->ask_name = !!(prm.flags & FLAG_ask_name);
    pmis->pmid->use_umsgid = !!(prm.flags2 & FLAG2_UMSGID);


    MexStoreMarea(MexDSEG(pmis->vmaMarea), &mah);


    pmis->pmm = MexDSEG(pmis->vmaMsg);

    if (!sq)
        memset(pmis->pmm, 0, sizeof *pmis->pmm);
    else
    {
        pmis->set_current = pmis->pmm->current = UIDnum(last_msg);
        pmis->pmm->num = MsgGetNumMsg(sq);
        pmis->pmm->high = UIDnum(MsgGetHighMsg(sq));
    }
    pmis->pmm->direction = (direction == DIRECTION_NEXT);


    pmis->hafFile = 0;
    pmis->hafMsg = 0;

    pmis->fhCallers = (word)-1;
    pmis->huf = NULL;
    pmis->huff = NULL;


void MexImportData(struct _mex_instance_stack *pmis)
{
    MexImportUser(pmis->pmu, &usr);
    SetUserName(&usr, usrname);
    Set_Lang_Alternate(hasRIP());
    Find_Class_Number();
    MexImportString(linebuf, pmis->vmaLinebuf, BUFLEN);
}


void MexExportData(struct _mex_instance_stack *pmis)
{
    MexExportString(pmis->vmaLinebuf, linebuf);
    MexExportUser(pmis->pmu, &usr);
}


    sprintf(szBirthDate, "%04u.%02u.%02u", user->dob_year, user->dob_month, user->dob_day);

    MexKillStructString(mex_usr, pusr, dob);
    StoreStringUser(dob, szBirthDate);

    StampToMexStamp(&user->date_1stcall, &pusr->date_1stcall);
    StampToMexStamp(&user->date_pwd_chg, &pusr->date_pwd_chg);
    pusr->nup = user->nup;
    pusr->ndown = user->ndown;
    pusr->ndowntoday = user->ndowntoday;
    pusr->time_added = user->time_added;
    pusr->point_credit = user->point_credit;
    pusr->point_debit = user->point_debit;
    StampToMexStamp(&user->date_newfile, &pusr->date_newfile);
}


    MexStringCopy(szBirthDate, &pusr->dob, sizeof(szBirthDate));

    if (sscanf(szBirthDate, "%u.%u.%u", &yy, &mm, &dd) == 3)
    {
        user->dob_year = yy;
        user->dob_month = mm;
        user->dob_day = dd;
    }

    MexStampToStamp(&pusr->date_1stcall, &user->date_1stcall);
    MexStampToStamp(&pusr->date_pwd_chg, &user->date_pwd_chg);
    user->nup = pusr->nup;
    user->ndown = pusr->ndown;
    user->ndowntoday = pusr->ndowntoday;
    user->time_added = pusr->time_added;
    user->point_credit = pusr->point_credit;
    user->point_debit = pusr->point_debit;
    MexStampToStamp(&pusr->date_newfile, &user->date_newfile);

    GetStringUser(user->msg, msg);
    GetStringUser(user->files, files);
}


void EXPENTRY intrin_term(short *psRet)
{
    int i;
    struct _mex_instance_stack *pmis;
    char szOldMsg[MAX_ALEN];
    char szOldFile[MAX_ALEN];

    NW(psRet);


    if (pmis->hafFile)
        AreaFileFindClose(pmis->hafFile);
    if (pmis->hafMsg)
        AreaFileFindClose(pmis->hafMsg);


    MexStringCopy(linebuf, MexDSEG(pmis->vmaLinebuf), BUFLEN);


    MexImportUser(pmis->pmu, &usr);


    if (!eqstri(szOldMsg, usr.msg))
    {
        BARINFO bi;

        memset(&bi, 0, sizeof bi);

        if (!PopPushMsgArea(usr.msg, &bi))
            strcpy(usr.msg, szOldMsg);
    }


    free(pmis);
}


int MexStartupIntrin(char *pszFile, char *pszArgs, dword fFlag)
{

    vbuf_flush();


int Mex(char *file)
{
    char *dup;
    char *p;
    char *pszArgs;
    int rc;

    if ((dup = strdup(file)) == NULL)
    {
        logit(mem_none);
        return -1;
    }


    if ((p = firstchar(dup, " ", 2)) == NULL)
        pszArgs = "";
    else
    {
        p[-1] = 0;
        pszArgs = p;
    }

