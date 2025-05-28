// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: t_misc.c,v 1.1.1.1 2002/10/01 17:53:14 sdudley Exp $";
#pragma on(unreferenced)


static char *szTrk;

void TrackRelease(TRK t) { TrkClose(t); }

#endif


static void near GetUsList(TRK t)
{
    BTREE *pbt;
    PALIST *ppl;
    TRK_OWNER_NDX *pton;

    pbt = TrkGetOwnerBtree(t);
    ppl = PalistNew();


    while ((pton = BtLookup(pbt, NULL, ppl)) != NULL)
        if (eqstri(pton->szOwner, usr.name))
        {
            TRKLIST ptl = malloc(sizeof(*ptl));

            if (ptl)
            {
                strcpy(ptl->to, pton->to);
                ptl->next = tl;
                tl = ptl;
            }
        }

    PalistDelete(ppl);
}


int IsUserExcluded(char *szName)
{
    EXCLIST pel;

    for (pel = el; pel; pel = pel->next)
        if (eqstri(szName, pel->pszName))
            return TRUE;

    return FALSE;
}


    if ((fp = fopen(name, fopen_read)) == NULL)
        return;


        if ((pel = malloc(sizeof *pel)) != NULL)
        {
            pel->pszName = strdup(line);
            pel->next = el;
            el = pel;
        }
    }

    fclose(fp);
}


    if (*szNewTrack)
        szTrk = szNewTrack;
    else
        szTrk = "trk";

    if ((t = TrkOpen(szTrk, TRUE)) == NULL)
    {
        logit(log_cant_open_trk);
        return;
    }


void DeinitTracker(void)
{
    TRKLIST ptl, ptlnext;
    EXCLIST pel, pelnext;


    for (pel = el; pel; pelnext = pel->next, free(pel), pel = pelnext)
        if (pel->pszName)
            free(pel->pszName);

#ifdef TRACK_PERSISTENT

    if (trkPersistent)
        TrkClose(trkPersistent);

    trkPersistent = 0;
#endif
}


    p = PRM(track_privview);

    if (*p == 0 || (!tl && !PrivOK(p, FALSE)))
        return FALSE;

    if (!kludges || (p = MsgGetCtrlToken(kludges, actrack_colon)) == NULL)
        return FALSE;

    rc = TrackAreWeOwnerOfActrack(p + 9, ptmn, pupdate_status);

    MsgFreeCtrlToken(p);

    return rc;
}


int TrackAreWeOwnerOfActrack(char *actrack, TRK_MSG_NDX *ptmn, int *pupdate_status)
{
    TRK t;
    TRK_MSG_NDX tmn;
    int rc = FALSE;

    if ((t = TrackGet()) == NULL)
        return FALSE;


        if (PrivOK(PRM(track_privview), FALSE))
            rc = TRUE;
    }

    TrackRelease(t);


void TrackMakeACAUDIT(char *out, char *fmt, ...)
{
    va_list va;
    SCOMBO sc;

    Get_Dos_Date(&sc);

    strcpy(out, "ACAUDIT: [");
    sc_time(&sc, out + strlen(out));
    strcat(out, "] ");

    va_start(va, fmt);
    vsprintf(out + strlen(out), fmt, va);
    va_end(va);
}

