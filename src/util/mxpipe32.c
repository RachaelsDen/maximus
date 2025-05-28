// SPDX-License-Identifier: GPL-2.0-or-later




static int CreatePipes(PIPES *pp)
{
    ULONG rc;

#ifdef MXP_DEBUG
    printf("create pipes\n");
#endif

    rc = DosCreatePipe(&pp->rpStdin.hpRead, &pp->rpStdin.hpWrite, PIPE_SIZE_STDIN);

    if (rc)
        return FALSE;

    rc = DosCreatePipe(&pp->rpStdout.hpRead, &pp->rpStdout.hpWrite, PIPE_SIZE_STDOUT);

    if (rc)
        return FALSE;

    return TRUE;
}


static int FiddleOutput(PIPES *pp)
{
    ULONG rc;
    HFILE hfDup;

#ifdef MXP_DEBUG
    printf("fiddle output\n");
#endif


    hfDup = HANDLE_STDIN;
    rc = DosDupHandle(pp->rpStdin.hpRead, &hfDup);

    if (rc)
        return FALSE;

    hfDup = HANDLE_STDOUT;
    rc = DosDupHandle(pp->rpStdout.hpWrite, &hfDup);

    if (rc)
        return FALSE;

    hfDup = HANDLE_STDERR;
    rc = DosDupHandle(pp->rpStdout.hpWrite, &hfDup);

    if (rc)
        return FALSE;

    return TRUE;
}


    psz = pp->szArgString;

    strcpy(psz, *++argv);

    if (!stristr(psz, ".exe"))
        strcat(psz, ".exe");

    psz += strlen(psz) + 1;

    while (*++argv)
    {
        strcat(psz, *argv);

        if (argv[1])
            strcat(psz, " ");
    }

    psz[strlen(psz) + 1] = 0;

    return TRUE;
}

static void ThreadStdin(void *pv)
{
    PIPES *pp = pv;
    KBDKEYINFO kki;

#ifdef MXP_DEBUG
    dprintf(pp, "ThreadStdin starting\r\n");
#endif


    for (;;)
    {
        int ch;
        ULONG rc;
        ULONG ulRead;
        ULONG ulWritten;

        rc = DosRead(pp->rpStdout.hpRead, &ch, 1, &ulRead);

#ifdef MXP_DEBUG
        dprintf(pp, "ThreadStdout got '%c'\r\n", ch);
#endif

        if (rc)
        {
            dprintf(pp, "ThreadStdout rc=%d\r\n", rc);
            exit(rc);
        }

        rc = DosWrite(pp->hfStdout, &ch, 1, &ulWritten);

        if (rc)
            exit(rc);

        if (pp->hfModem)
        {
            rc = DosWrite(pp->hfModem, &ch, 1, &ulWritten);

            if (rc)
            {
                dprintf(pp, "DosWrite rc=%d\r\n", rc);
                exit(rc);
            }
        }
    }
}

