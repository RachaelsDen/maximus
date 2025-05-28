// SPDX-License-Identifier: GPL-2.0-or-later



#include "exec.h"
#include "checkpat.h"
#include "compat.h"
#include <bios.h>


typedef struct
{
    char drive[MAXDRIVE], dir[MAXDIR];
    char name[MAXFILE], ext[MAXEXT];
    char cmdpath[MAXPATH];
    char cmdpars[80];
} SWBLOCK;

#define REDIRECT 0

#define SWAP_FILENAME max_swap_filename
extern char *max_swap_filename;

#define CREAT_TEMP 0x0080
#define DONT_SWAP_ENV 0x4000

#define ERR_COMSPEC -7
#define ERR_NOMEM -8

spawn_check_proc *spawn_check = NULL;

#ifdef __cplusplus
extern "C" int
#else
extern int _cdecl
#endif
         char *rstdout, char *rstderr
#endif
);

#ifdef __cplusplus
extern "C" int
#else
extern int _cdecl
#endif

#ifdef __cplusplus
extern "C" int
#else
extern int _cdecl
#endif
exists(char *fname);

#define isslash(ch) (ch == '\\' || ch == '/')


static int tryext(char *fn)
{
    char *ext;

    ext = strchr(fn, '\0');
    strcpy(ext, ".COM");
    if (exists(fn))
        return 1;
    strcpy(ext, ".EXE");
    if (exists(fn))
        return 1;
    strcpy(ext, ".BAT");
    if (exists(fn))
        return 2;
    *ext = 0;
    return 0;
}


static int findfile(char *fn, SWBLOCK *pswb)
{
    char *path, *penv;
    char *prfx;
    int found, check, hasext;

    if (!*fn)
        return (pswb->cmdpath[0]) ? 3 : ERR_COMSPEC;

    if (isslash(fn[0]) && isslash(fn[1]))
    {
    }
    check = checkpath(fn, INF_NODIR, pswb->drive, pswb->dir, pswb->name, pswb->ext, fn);
    if (check < 0)
        return check;

    if ((check & HAS_WILD) || !(check & HAS_FNAME))
        return ERR_FNAME;

    hasext = (check & HAS_EXT) ? ((!stricmp(pswb->ext, ".bat")) ? 2 : 1) : 0;

    if (hasext)
    {
        if (check & FILE_EXISTS)
            found = hasext;
        else
            found = 0;
    }
    else
        found = tryext(fn);

    if (found || (check & (HAS_PATH | HAS_DRIVE)))
        return found;

    penv = getenv("PATH");
    if (!penv)
        return 0;
    path = (char *)malloc(strlen(penv) + 1);
    if (path == NULL)
        return ERR_NOMEM;

    strcpy(path, penv);
    prfx = strtok(path, ";");

    while (!found && prfx != NULL)
    {
        while (isspace(*prfx))
            prfx++;
        if (*prfx)
        {
            strcpy(fn, prfx);
            prfx = strchr(fn, '\0');
            prfx--;
            if (*prfx != '\\' && *prfx != '/' && *prfx != ':')
            {
                *++prfx = '\\';
            }
            prfx++;
            strcpy(prfx, pswb->name);
            strcat(prfx, pswb->ext);
            check = checkpath(fn, INF_NODIR, pswb->drive, pswb->dir, pswb->name, pswb->ext, fn);
            if (check > 0 && (check & HAS_FNAME))
            {
                if (hasext)
                {
                    if (check & FILE_EXISTS)
                        found = hasext;
                }
                else
                    found = tryext(fn);
            }
        }
        prfx = strtok(NULL, ";");
    }
    free(path);
    return found;
}


static void getcmdpath(SWBLOCK *pswb)
{
    char *pcmd;
    int found = 0;

    if (pswb->cmdpath[0])
        return;
    pcmd = getenv("COMSPEC");
    if (pcmd)
    {
        strcpy(pswb->cmdpath, pcmd);
        pcmd = pswb->cmdpath;
        while (isspace(*pcmd))
            pcmd++;
        if (NULL != (pcmd = strpbrk(pcmd, ";,=+/\"[]|<> \t")))
        {
            while (isspace(*pcmd))
                *pcmd++ = 0;
            if (strlen(pcmd) >= 79)
                pcmd[79] = 0;
            strcpy(pswb->cmdpars, pcmd);
            strcat(pswb->cmdpars, " ");
        }
        found = findfile(pswb->cmdpath, pswb);
    }
    if (!found)
    {
        pswb->cmdpars[0] = 0;
        strcpy(pswb->cmdpath, "COMMAND.COM");
        found = findfile(pswb->cmdpath, pswb);
        if (!found)
            pswb->cmdpath[0] = 0;
    }
}


static int tempdir(char *outfn, SWBLOCK *pswb)
{
    int i, res;
    char *stmp[4];

    stmp[0] = getenv("TMP");
    stmp[1] = getenv("TEMP");
    stmp[2] = ".\\";
    stmp[3] = "\\";

    for (i = 0; i < 4; i++)
        if (stmp[i])
        {
            strcpy(outfn, stmp[i]);
            res = checkpath(outfn, 0, pswb->drive, pswb->dir, pswb->name, pswb->ext, outfn);
            if (res > 0 && (res & IS_DIR) && !(res & IS_READ_ONLY))
                return 1;
        }
    return 0;
}

#if (REDIRECT)

static int redirect(char *par, char **rstdin, char **rstdout, char **rstderr, SWBLOCK *pswb)
{
    char ch, sav;
    char *fn, *fnp, *beg;
    int app;

    do
    {
        app = 0;
        beg = par;
        ch = *par++;
        if (ch != '<')
        {
            if (*par == '&')
            {
                ch = '&';
                par++;
            }
            if (*par == '>')
            {
                app = 1;
                par++;
            }
        }

        while (isspace(*par))
            par++;
        fn = par;
        if ((fnp = strpbrk(par, ";,=+/\"[]|<> \t")) != NULL)
            par = fnp;
        else
            par = strchr(par, '\0');
        sav = *par;
        *par = 0;

        if (!strlen(fn))
            return 0;
        fnp = (char *)malloc(strlen(fn) + app + 1);
        if (fnp == NULL)
            return 0;
        if (app)
        {
            strcpy(fnp, ">");
            strcat(fnp, fn);
        }
        else
            strcpy(fnp, fn);

        switch (ch)
        {
        case '<':
            if (*rstdin != NULL)
                return 0;
            *rstdin = fnp;
            break;
        case '>':
            if (*rstdout != NULL)
                return 0;
            *rstdout = fnp;
            break;
        case '&':
            if (*rstderr != NULL)
                return 0;
            *rstderr = fnp;
            break;
        }

        *par = sav;
        strcpy(beg, par);
        par = strpbrk(beg, "<>");
    } while (par);

    return 1;
}

#endif

int cdecl do_exec(char *exfn, char *epars, int spwn, unsigned needed, char **envp)
{

    if ((ffrc = findfile(execfn, &swb)) <= 0)
        return RC_NOFILE | -ffrc;


    if (envp != NULL)
        for (env = envp; *env != NULL; env++)
            envlen += strlen(*env) + 1;

    if (envlen)
    {
        envptr = envbuf;
        if (FP_OFF(envptr) & 0x0f)
            envptr += 16 - (FP_OFF(envptr) & 0x0f);
        ep = envptr;

        for (env = envp; *env != NULL; env++)
        {
            ep = stpcpy(ep, *env) + 1;
        }
        *ep = 0;
    }

    if (!spwn)
        swapping = -1;
    else
    {

        if (needed < avail)
            swapping = 0;
        else
        {

            swapping = spwn;
            if (spwn & USE_FILE)
            {
                if (!tempdir(swapfn, &swb))
                {
                    spwn &= ~USE_FILE;
                    swapping = spwn;
                }
                else if (OS_MAJOR >= 3)
                    swapping |= CREAT_TEMP;
                else
                {
                    strcat(swapfn, SWAP_FILENAME);
                    idx = strlen(swapfn) - 1;
                    while (exists(swapfn))
                    {
                        if (swapfn[idx] == 'Z')
                            idx--;
                        if (swapfn[idx] == '.')
                            idx--;
                        swapfn[idx]++;
                    }
                }
            }
        }
    }


exit:
    free(progpars);
#if (REDIRECT)
    if (rstdin)
        free(rstdin);
    if (rstdout)
        free(rstdout);
    if (rstderr)
        free(rstderr);
#endif
    if (envlen)
        free(envbuf);

    return rc;
}
