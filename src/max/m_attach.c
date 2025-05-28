// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: m_attach.c,v 1.2 2003/06/04 23:25:09 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_m_area
#define MAX_LANG_m_browse
#define MAX_LANG_max_chat
#define MAX_LANG_f_area

#include "m_attach.h"
#include "arcmatch.h"
#include "display.h"
#include "dr.h"
#include "l_attach.h"
#include "max_file.h"
#include "max_msg.h"
#include "mm.h"
#include "prog.h"
#include "userapi.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static char *attach_path = NULL;

static const char lfa_kludge[] = "\x01LFA: ";

static void near LFAFindClose(LFAFIND *pLfaF);

void Msg_AttachUpload(PMAH pmah, HAREA marea, XMSG *msg, UMSGID uid)
{

    FENTRY fent;

    logit(log_attach_upload);

    if ((attach_path = malloc(PATHLEN)) == NULL)
    {
        logit(mem_none);
        return;
    }

    if (Make_Attach_Directory() == -1)
    {
        free(attach_path);
        attach_path = NULL;
        return;
    }

    save_tag_list(NULL);


        WhiteN();
        iLfa_flags = 0L;
        ok = TRUE;
        *fname = '\0';

        if (local)
        {
            int fn;
            char *p = fname;

            for (fn = 0; GetFileEntry(fn, &fent); ++fn)
            {
                strcpy(p, fent.szName);
                p += strlen(p);
                *p++ = ' ';
            }
            if (p > fname)
                --p;
            *p = '\0';
        }

        if (local && GetYnAnswer(attach_ask_compr, 0) == NO)
            iLfa_flags = LFA_NODELETE | LFA_FILE_PATH;


        HMSG mh = MsgOpenMsg(marea, MOPEN_RW, MsgUidToMsgn(marea, uid, UID_EXACT));
        if (!mh)
            logit("!Can't reopen msg - msgapierr=%d", msgapierr);
        else
        {
            if (MsgReadMsg(mh, msg, 0L, 0L, NULL, 0L, NULL) == -1)
                logit("!Error reading msg - msgapierr=%d", msgapierr);
            else
            {
                msg->attr |= MSGFILE;

                if (MsgWriteMsg(mh, FALSE, msg, NULL, 0L, 0L, 0L, NULL) == -1)
                    logit("!Error writing msg - msgapierr=%d", msgapierr);
            }
            MsgCloseMsg(mh);
        }
    }

    Clean_Directory(attach_path, TRUE);
    free(attach_path);
    attach_path = NULL;

    Free_Filenames_Buffer(0);
    restore_tag_list(NULL, FALSE);
}

static int near Make_Attach_Directory(void)
{

    Free_Filenames_Buffer(0);

    if (local)
    {
        char *s;

        WhiteN();
        InputGetsL(temp, 0, make_attach_local);

        for (s = strtok(temp, cmd_delim); s; s = strtok(NULL, cmd_delim))
        {
            if (AddFileEntry(s, 0, 0) == 0)
                break;
        }
    }
    else
    {
        word sf2;

        if (File_Get_Protocol(&protocol, FALSE, TRUE) == -1)
            return -1;

        ChatSaveStatus(&css);
        ChatSetStatus(FALSE, cs_file_xfer);

        if (baud < ClassGetInfo(cls, CIT_MIN_XFER_BAUD))
        {
            Display_File(0, NULL, PRM(xferbaud));
            Printf(baudtoolowforxfer, ClassGetInfo(cls, CIT_MIN_XFER_BAUD));
            Press_ENTER();
            return -1;
        }

        b_free = zfree(attach_path);

        if (prm.k_free && b_free < (long)prm.k_free * 1000L)
        {
            Display_File(0, NULL, PRM(no_space));
            return -1;
        }

        Printf(bytes_for_ul, commaize(b_free - (long)prm.k_free * 1000L, temp));

        if (!IsBatch(protocol))
            File_Get_Upload_Names();

        Add_To_Time(time(NULL) - ul_start_time);
        ChatRestoreStatus(&css);
    }

    if (FileEntries())
    {
        word fn;
        sword gotfiles;

        FENTRY fent;

        for (gotfiles = 0, fn = 0; GetFileEntry(fn, &fent); ++fn)
        {
            if (local)
                strcpy(temp, fent.szName);
            else
            {
                strcpy(temp, attach_path);
                strcat(temp, fent.szName);
            }
            if (fexist(temp))
                ++gotfiles;
            else
                logit(cantfind, temp);
        }
        else
            sprintf(files, "%s" WILDCARD_ALL, attach_path);

        for (ret = strlen(pth);; Delay(100))
        {
            sprintf(szAttachName, "%08lX.%s", (time(NULL) << 4L) | (long)task_num, pai->extension);
            strcpy(pth + ret, szAttachName);
            if (!fexist(pth))
                break;
        }

        Form_Archiver_Cmd(pth, files, cmd, pai->add);


static void near Update_Attach_Db(PMAH pmah, HAREA marea, XMSG *msg, UMSGID uid, char *szFileName,
                                  dword ulFlags)
{


        DBASE OS2FAR *pDb = LFAdbOpen(PRM(attach_base));

        if (!pDb)
            logit(log_err_open_attach_db, PRM(attach_base));
        else
        {
            int ok;
            HUF huf;
            char recipient[36];
            LFA_REC lfa;


        if (szCtrl != NULL && (p = strstr(szCtrl, lfa_kludge)) != NULL &&
            sscanf(p + 6, "%lx %s\x01", &attachId, temp) == 2)
        {

        {
            char *s, *p = plfa->szFile;
            int gotpath;

            memset(plfa, '\0', sizeof(LFA_REC));
            plfa->ulAttributes = LFA_NODELETE | LFA_FILE_PATH;
            for (s = strtok(pxmsg->subj, cmd_delim); s; s = strtok(NULL, cmd_delim))
            {
                        strcpy(p, PRM(inbound_files));
                        plfa->ulAttributes &= ~LFA_NODELETE;
                    }
            {
                --p;

            if (!ReadMsgArea(ham, plfa->szArea, &ma))
            {
                *p = '\0';
                logit(log_err_noarea, plfa->szArea);
                return FALSE;
            }
            strcpy(p, MAS(ma, attachpath));


            if (!*p)
                strcpy(p, PRM(attach_path));

            DisposeMah(&ma);
        }
        strcat(p, s);
        if (!fexist(p))
        {
            logit(cantfind, p);
            if (szMsg)
            {
                Puts(szMsg);
                Press_ENTER();
            }
            return FALSE;
        }
        p += strlen(p);
        *p++ = ' ';
    }

    if (p > szFile)
        --p;
    *p = '\0';
    return TRUE;
}

int Msg_UnreceivedAttach(XMSG *pxmsg, char *szCtrl, int isnetmsg)
{
    int rc;
    DBASE OS2FAR *pdb;
    LFA_REC lfa;

    if ((pdb = Read_Attach(&lfa, pxmsg, szCtrl, isnetmsg)) == NULL)
        rc = FALSE;
    else
    {
        LFAdbClose(pdb);
        rc = TRUE;
    }
    return rc;
}

static int near Send_Attach(int fDelok)
{
    int good = FALSE;

    FENTRY fent;

    if (local)
    {



                p = No_Path(fent.szName);


                if (fexist(temp2))
                {
                    sprintf(prompt, ok_to_overwrite, temp2);

                    if (GetyNAnswer(prompt, 0) == NO)
                        continue;

                    fDoMove = FALSE;
                }


                if (fDelok && !fDoMove)
                    unlink(fent.szName);
            }
        }
    }
    else
    {
        struct _css css;
        sword protocol;

        if (File_Get_Protocol(&protocol, FALSE, TRUE) != -1)
        {

            ChatSaveStatus(&css);
            ChatSetStatus(FALSE, cs_file_xfer);

            if (File_Send_Files(protocol, NULL, NULL, 1))
                good = TRUE;

            ChatRestoreStatus(&css);
        }
    }

    return good;
}

static int near Decompress_Attach(char *szName)
{
    struct _arcinfo *pai;
    int fd, ret;

    Load_Archivers();

    if ((fd = shopen(szName, O_RDONLY | O_BINARY | O_NOINHERIT)) == -1)
        return -1;

    for (pai = ari; pai; pai = pai->next)
        if (MatchArcType(fd, pai))
            break;

    close(fd);

    if (!pai)
        pai = ari;

    if (!pai)
    {
        Puts(unknown_compr);
        ret = -1;
    }
    else
    {
        FFIND *ff;
        char temp[PATHLEN];
        char szFullName[PATHLEN];

        strcpy(szFullName, szName);

        if (szFullName[1] != ':' && szFullName[0] != '\\' && szFullName[0] != '/')
        {
            strcpy(szFullName, PRM(sys_path));
            strcat(szFullName, szName);
        }


        FixLastread(sq, mah.ma.type, last_msg, MAS(mah, path));

        Save_Directory2(attach_path);
        ret = Outside(NULL, NULL, OUTSIDE_RUN | OUTSIDE_STAY | OUTSIDE_NOFIX, temp, FALSE, CTL_NONE,
                      0, NULL);
        Restore_Directories2();

        if (ret == 0)
        {

            sprintf(temp, "%s" WILDCARD_ALL, attach_path);
            if ((ff = FindOpen(temp, 0)) != NULL)
            {
                do
                {
                    strcpy(temp, attach_path);
                    strcat(temp, ff->szName);

                    if (AddFileEntry(temp, FFLAG_NOBYTES, -1L) == -1)
                    {
                        Free_Filenames_Buffer(0);
                        break;
                    }
                } while (FindNext(ff) == 0 && CanAddFileEntry());
                FindClose(ff);
            }
        }

        if (!FileEntries())
            Puts(no_attach_files);
    }

    return ret;
}

void Msg_AttachDownload(XMSG *pxmsg, char *szCtrl, int isnetmsg)
{
    DBASE OS2FAR *pdb;
    LFA_REC lfa;


        if (Attach_File(&lfa, temp, attach_notavail))
        {

            logit(log_attach_download);

            if ((attach_path = malloc(PATHLEN)) == NULL)
                logit(mem_none);
            else
            {


                    if (lfa.ulAttributes & LFA_FILE_PATH)
                    {
                        char *s;

                        for (s = strtok(temp, cmd_delim); s; s = strtok(NULL, cmd_delim))
                        {
                            if (AddFileEntry(s, FFLAG_NOBYTES, -1L) == -1)
                                goto Done;
                        }
                    }


                    if (FileEntries() && Send_Attach(!(lfa.ulAttributes & LFA_NODELETE)) &&
                        prm.kill_attach == 2 && !(lfa.ulAttributes & LFA_NODELETEATTACH))

                    {
                        if (!(lfa.ulAttributes & LFA_NODELETE))
                            unlink(temp);
                        if (pdb != FTSATTACHDBH)
                        {
                            void *pvLookId[] = {NULL, NULL, NULL};

                            pvLookId[0] = &lfa.ulAttachID;
                            pvLookId[1] = lfa.szTo;
                            pvLookId[2] = lfa.szArea;
                            LFAdbRemove(pdb, pvLookId);
                        }
                    }

                    Clean_Directory(attach_path, TRUE);
                }

            Done:

                free(attach_path);
                attach_path = NULL;
            }
        }

        LFAdbClose(pdb);

        Free_Filenames_Buffer(0);
        restore_tag_list(NULL, FALSE);
    }
}

void Msg_AttachKill(XMSG *pxmsg, char *szCtrl, int isnetmsg)
{
    DBASE OS2FAR *pdb;
    LFA_REC lfa;


        if (pdb != FTSATTACHDBH && (lfa.ulAttributes & LFA_NODELETEATTACH) == 0)
        {
            void *pvLookId[] = {NULL, NULL, NULL};

            pvLookId[0] = &lfa.ulAttachID;
            pvLookId[1] = lfa.szTo;
            pvLookId[2] = lfa.szArea;
            LFAdbRemove(pdb, pvLookId);
        }
        LFAdbClose(pdb);
    }
}

            pplLook = PalistNew();
            rc = LFAdbLookup(pdb, pvLookId, pplLook, &lfa);
            PalistDelete(pplLook);

            LFAdbClose(pdb);
        }
    }

    return rc;
}

static LFAFIND *near LFAFindOpen(char *name)
{
    DBASE OS2FAR *pdb;
    LFAFIND *pLfaF;

    pLfaF = NULL;
    if (prm.attach_base)
    {
        if ((pdb = LFAdbOpen(PRM(attach_base))) == NULL)
            logit(log_err_open_attach_db, PRM(attach_base));
        else if ((pLfaF = malloc(sizeof(LFAFIND))) == NULL)
            logit(mem_none);
        else
        {
            pLfaF->pdb = pdb;
            pLfaF->pvLookId[0] = NULL;
            pLfaF->pvLookId[1] = name;
            pLfaF->pvLookId[2] = NULL;
            pLfaF->pplLook = PalistNew();
            if (!LFAdbLookup(pLfaF->pdb, pLfaF->pvLookId, pLfaF->pplLook, &pLfaF->lfa))
            {
                LFAFindClose(pLfaF);
                pLfaF = NULL;
            }
        }
    }
    return pLfaF;
}

static int near LFAFindNext(LFAFIND *pLfaF)
{
    if (pLfaF != NULL)
        return LFAdbLookup(pLfaF->pdb, pLfaF->pvLookId, pLfaF->pplLook, &pLfaF->lfa);
    return 0;
}

static void near LFAFindClose(LFAFIND *pLfaF)
{
    if (pLfaF != NULL)
    {
        PalistDelete(pLfaF->pplLook);
        LFAdbClose(pLfaF->pdb);
        free(pLfaF);
    }
}

static int near Attach_List(void);
static void near Download_Attaches(void);

void Msg_Attach_Download(void)
{
    int n;

    n = Attach_List();

    WhiteN();

    if (n == 0)
    {
        Puts(no_files_attached);
        Press_ENTER();
    }
    else
    {
        char *p = malloc(strlen(n_files_attached) + 12);
        sprintf(p, n_files_attached, n);

        if (n == 1 || GetYnAnswer(p, 0) != NO)
            Download_Attaches();

        free(p);
    }
}

static int near Attach_List(void)
{
    int n;
    LFAFIND *pLfaF;

    n = 0;
    if ((pLfaF = LFAFindOpen(usr.name)) != NULL)
    {
        byte nonstop;

        nonstop = FALSE;
        display_line = display_col = 1;

        Printf(attach_hdr0, usr.name);
        WhiteN();
        Puts(attach_hdr0_5);
        Puts(attach_hdr1);
        Puts(attach_hdr2);

        do
        {
            char temp[PATHLEN];
            char szSize[20];
            long lSize = 0;
            char *s;

            if (halt() || MoreYnBreak(&nonstop, NULL))
                break;
            ++n;


            lSize /= 1000;

            if (lSize >= 1000)
                sprintf(szSize, "%d.%dM", lSize / 1000, (lSize / 100) % 10);
            else
                sprintf(szSize, "%dK", lSize);

            Printf(attach_fmt, FileDateFormat(&pLfaF->lfa.scDateAttached, temp),
                   pLfaF->lfa.scDateAttached.msg_st.time.hh,
                   pLfaF->lfa.scDateAttached.msg_st.time.mm, pLfaF->lfa.szFrom, szSize,
                   pLfaF->lfa.szArea);
        } while (LFAFindNext(pLfaF));
        LFAFindClose(pLfaF);

        Puts(attach_hdr2);
    }
    return n;
}

static void near Download_Attaches(void)
{
    LFAFIND *pLfaF;

    if ((pLfaF = LFAFindOpen(usr.name)) != NULL)
    {
        char temp[PATHLEN];

        save_tag_list(NULL);

        do
        {

            Printf(attach_fmt2, FileDateFormat(&pLfaF->lfa.scDateAttached, temp),
                   pLfaF->lfa.scDateAttached.msg_st.time.hh,
                   pLfaF->lfa.scDateAttached.msg_st.time.mm, pLfaF->lfa.szFrom, pLfaF->lfa.szArea);

            if (Attach_File(&pLfaF->lfa, temp, attach_notavail) &&
                GetYnAnswer(attach_dload, 0) != NO)
            {

                logit(log_attach_download);

                if ((attach_path = malloc(PATHLEN)) == NULL)
                    logit(mem_none);
                else
                {


                        if (pLfaF->lfa.ulAttributes & LFA_FILE_PATH)
                        {
                            if (AddFileEntry(temp, FFLAG_NOBYTES, -1L) == -1)
                                goto Done;
                        }


                        if (FileEntries() && Send_Attach(!(pLfaF->lfa.ulAttributes & LFA_NODELETE)))
                        {
                            if ((prm.kill_attach == 2 &&
                                 !(pLfaF->lfa.ulAttributes & LFA_NODELETEATTACH)) ||
                                Ask_KillAttach())
                            {
                                void *pvLookId[] = {NULL, NULL, NULL};

                                pvLookId[0] = &pLfaF->lfa.ulAttachID;
                                pvLookId[1] = pLfaF->lfa.szTo;
                                pvLookId[2] = pLfaF->lfa.szArea;
                                if (!(pLfaF->lfa.ulAttributes & LFA_NODELETE))
                                    unlink(temp);
                                LFAdbRemove(pLfaF->pdb, pvLookId);
                            }
                        }
                        else
                            break;

                        Clean_Directory(attach_path, TRUE);
                    }

                Done:

                    free(attach_path);
                    attach_path = NULL;
                }
            }
        } while (LFAFindNext(pLfaF));
        LFAFindClose(pLfaF);

        restore_tag_list(NULL, FALSE);
    }
}
