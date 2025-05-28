// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: ued_cmds.c,v 1.1.1.1 2002/10/01 17:53:20 sdudley Exp $";
#pragma on(unreferenced)


#define MAX_LANG_max_ued
#define MAX_LANG_max_chng
#define MAX_LANG_max_init

#include "ffind.h"
#include "max_area.h"
#include "md5.h"
#include "mm.h"
#include "prog.h"
#include "ued.h"
#include "userapi.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <share.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static void near Strip_Bad_Stuff(byte *s, int m);
static int fAddUser = FALSE;


    if ((find_name = malloc(PATHLEN * sizeof(char))) == NULL)
    {
        logit(log_nomem_del);
        return -1;
    }

    if ((huf = UserFileOpen(PRM(user_file), 0)) == NULL)
    {
        cant_open(PRM(user_file));

        free(find_name);
        return -1;
    }

    DrawUserScreen();

    return 0;
}


static void near Strip_Bad_Stuff(byte *s, int m)
{
    *(s + m) = '\0';

    while (*s)
    {
        if (*s < ' ')
            *s = ' ';

        s++;
    }
}


void UedLast(void)
{
    Update_User();
    UedFindLastUser();
}


    Putc('\r');

    Update_User();

    if ((huff = UserFileFindOpen(huf, user.name, NULL)) != NULL)
    {

        tryusr = huff->usr;

        rc = UserFileFindNext(huff, NULL, NULL);

        if (rc)
            user = huff->usr;
        else
            user = tryusr;

        UserFileFindClose(huff);
    }
    else
        UedFindFirstUser();

    Read_New_User();
}


            if (strcmp(temp, " ") == 0)
                *temp = 0;

            strcpy(user.alias, temp);
        }
    }

    changes = TRUE;
}

void UedGetCity(void)
{
    char temp[PATHLEN];

    InputGetsLL(temp, 35, ued_city);

    if (*temp)
        strcpy(user.city, temp);

    changes = TRUE;
}

void UedGetName(void)
{
    char temp[PATHLEN];
    struct _usr usrtmp;

    InputGetsLL(temp, 35, ued_uname);

    if (*temp)
    {
        if (!eqstri(temp, olduser.name) && !eqstri(temp, olduser.alias) &&
            (UserFileFind(huf, temp, NULL, &usrtmp) || UserFileFind(huf, NULL, temp, &usrtmp)))
        {
            Puts(ued_nameinuse);
            Press_ENTER();
        }
        else
            strcpy(user.name, fancier_str(temp));
    }

    changes = TRUE;
}

void UedGetVoicePhone(void)
{
    char temp[PATHLEN];

    InputGetsLL(temp, 14, ued_phone);

    if (*temp)
        strcpy(user.phone, temp);

    changes = TRUE;
}

void UedGetDataPhone(void)
{
    char temp[PATHLEN];

    InputGetsLL(temp, 14, ued_phone);

    if (*temp)
        strcpy(user.dataphone, temp);

    changes = TRUE;
}

void UedGetSex(void)
{
    byte cmd;

    cmd = (byte)toupper(KeyGetRNP(ued_sex_prompt));

    if (cmd == ued_sex_keys[0])
        user.sex = SEX_MALE;
    else if (cmd == ued_sex_keys[1])
        user.sex = SEX_FEMALE;
    else if (cmd == ued_sex_keys[2])
        user.sex = SEX_UNKNOWN;

    changes = TRUE;
}


        if (yy < 100)
            yy += 1900;

        user.dob_year = yy;
        user.dob_month = mm;
        user.dob_day = dd;
    }

    changes = TRUE;
}

void UedGetGroup(void)
{
    char temp[PATHLEN];

    InputGetsLL(temp, 6, ued_group_prompt);

    if (*temp)
        user.group = atoi(temp);

    changes = TRUE;
}

void UedGetPointCredit(void)
{
    char temp[PATHLEN];

    InputGetsLL(temp, 25, ued_pcredit_prompt);

    if (*temp)
        user.point_credit = atol(temp);

    changes = TRUE;
}

void UedGetPointDebit(void)
{
    char temp[PATHLEN];

    InputGetsLL(temp, 25, ued_pdebit_prompt);

    if (*temp)
        user.point_debit = atol(temp);

    changes = TRUE;
}

void UedGetHotkeys(void)
{
    user.bits ^= BITS_HOTKEYS;
    changes = TRUE;
}

void UedGetNerd(void)
{
    user.bits ^= BITS_NERD;
    changes = TRUE;
}

void UedGetTabs(void)
{
    user.bits ^= BITS_TABS;
    changes = TRUE;
}

void UedGetRIP(void)
{
    user.bits ^= BITS_RIP;
    changes = TRUE;
}

void UedGetIBMChars(void)
{
    user.bits2 ^= BITS2_IBMCHARS;
    changes = TRUE;
}

void UedGetPause(void)
{
    user.bits2 ^= BITS2_MORE;
    changes = TRUE;
}

void UedGetCalledBefore(void)
{
    user.bits2 ^= BITS2_CONFIGURED;
    changes = TRUE;
}

void UedGetScrnClr(void)
{
    user.bits2 ^= BITS2_CLS;
    changes = TRUE;
}

void UedGetAvailChat(void)
{
    user.bits ^= BITS_NOTAVAIL;
    changes = TRUE;
}

void UedGetFSR(void)
{
    user.bits ^= BITS_FSR;
    changes = TRUE;
}

void UedGetMaxed(void)
{
    user.bits2 ^= BITS2_BORED;
    changes = TRUE;
}

void UedGetWidth(void)
{
    char temp[PATHLEN];

    InputGets(temp, ued_width);

    if (*temp)
        user.width = (char)atoi(temp);

    changes = TRUE;
}

void UedGetLength(void)
{
    char temp[PATHLEN];

    InputGets(temp, ued_length);

    if (*temp)
        user.len = (char)atoi(temp);

    changes = TRUE;
}

void UedGetNulls(void)
{
    char temp[PATHLEN];

    InputGets(temp, ued_nulls);

    if (*temp)
        user.nulls = (byte)atoi(temp);

    changes = TRUE;
}

void UedGetMsgArea(void)
{
    char temp[PATHLEN];

    InputGets(temp, ued_lastmsg);

    if (*temp)
        SetAreaName(user.msg, temp);

    changes = TRUE;
}

void UedGetFileArea(void)
{
    char temp[PATHLEN];

    InputGets(temp, ued_lastfile);

    if (*temp)
        SetAreaName(user.files, temp);

    changes = TRUE;
}


void UedGetProtocol(void)
{
    sword proto;

    Puts(CLS);
    Puts(chose_default_proto);

    if (File_Get_Protocol(&proto, TRUE, FALSE) != -1)
        user.def_proto = proto;

    DrawUserScreen();
    changes = TRUE;
}


    Inputf(temp, INPUT_WORD | INPUT_NOLF, 0, 0, ued_dlall);
    Puts(CLEOL);

    if (*temp)
        user.down = atol(temp);


void UedGetHelp(void)
{
    byte cmd;

    cmd = (byte)toupper(KeyGetRNP(ued_gethelp));

    if (cmd == ued_help_keys[0])
        user.help = NOVICE;
    else if (cmd == ued_help_keys[1])
        user.help = REGULAR;
    else if (cmd == ued_help_keys[2])
        user.help = EXPERT;

    changes = TRUE;
}


void UedGetVideo(void)
{
    byte cmd;

    changes = TRUE;

    cmd = (byte)toupper(KeyGetRNP(ued_vidmode));

    if (cmd == ued_vid_keys[0])
        user.video = GRAPH_TTY;
    else if (cmd == ued_vid_keys[1])
        user.video = GRAPH_ANSI;
    else if (cmd == ued_vid_keys[2])
        user.video = GRAPH_AVATAR;
}


    if (!*temp)
    {
        memset(user.pwd, 0, sizeof user.pwd);
#ifdef CANENCRYPT
        user.bits &= ~BITS_ENCRYPT;
#endif
        return;
    }

#if defined(MUSTENCRYPT) || defined(CHANGEENCRYPT)
    if (!(prm.flags2 & FLAG2_NOENCRYPT))
    {
        byte abMd5[MD5_SIZE];

        string_to_MD5(strlwr(temp), abMd5);

        memcpy(user.pwd, abMd5, sizeof user.pwd);
        user.bits |= BITS_ENCRYPT;
    }
    else
#endif
    {
        strcpy(user.pwd, cfancy_str(temp));
        user.bits &= ~BITS_ENCRYPT;
    }
}


void UedShowHelp(void)
{
    Display_File(0, NULL, "%suedhelp", PRM(misc_path));
    DrawUserScreen();
}


void UedFindLastUser(void)
{
    if (!UserFileSeek(huf, -1L, &user, sizeof usr))
        UedFindFirstUser();
    Read_New_User();
}


static void near PurgeLastreads(int *piOffset, int num_offset)
{
    char temp[PATHLEN];
    MAH ma;
    HAFF haff;
    long where, pos;
    int lrfile, i;
    dword zeroes;

    memset(&ma, 0, sizeof ma);
    Puts(ued_cleansing_lastreads);
    vbuf_flush();

    zeroes = 0;

    if ((haff = AreaFileFindOpen(ham, NULL, 0)) == NULL)
        return;

    while (AreaFileFindNext(haff, &ma, 0) == 0)
    {
        if (!*MAS(ma, path))
            continue;

        Printf(CLEOL " %s\r", cfancy_str(MAS(ma, path)));
        vbuf_flush();

        sprintf(temp, (ma.ma.type & MSGTYPE_SDM) ? ps_lastread : sq_lastread, MAS(ma, path));

        if ((lrfile = shopen(temp, O_RDWR | O_BINARY | O_NOINHERIT)) == -1)
            continue;


        for (i = 0; i < num_offset; i++)
        {
            int size;

            if (ma.ma.type & MSGTYPE_SDM)
                size = sizeof(word);
            else
                size = sizeof(UMSGID);

            where = (long)piOffset[i] * (long)size;

            if (where <= pos)
            {
                lseek(lrfile, where, SEEK_SET);
                write(lrfile, (char *)&zeroes, size);
            }
        }

        close(lrfile);
    }

    DisposeMah(&ma);
}


        user.delflag ^= UFLAG_DEL;
        changes = TRUE;
    }
}


        if (!fAddUser)
        {
            if (UserFileUpdate(huf, olduser.name, olduser.alias, &user))
                changes = FALSE;
            else
                logit(cantwrite, PRM(user_file));
        }
        else
        {

    if (eqstri(usr.name, user.name))
    {
        byte old_video = usr.video;

        if (usr.priv != user.priv)
        {
            usr = user;
            Find_Class_Number();
        }
        else
        {
            usr = user;
        }


int Add_User(void)
{
    Update_User();

    Blank_User(&user);

    user.lastread_ptr = Find_Next_Lastread(huf);
    user.struct_len = sizeof(struct _usr) / 20;
    changes = TRUE;

    DrawUserScreen();
    fAddUser = TRUE;
    return 0;
}

static int near try_match(struct _usr *pu, int exact)
{
    if ((exact && (eqstri(pu->name, find_name) || eqstri(pu->alias, find_name))) ||
        (!exact && stristr(pu->name, find_name)) || (!exact && stristr(pu->alias, find_name)) ||
        (!exact && stristr(pu->phone, find_name)))
    {
        return TRUE;
    }

    return FALSE;
}


                    if (first && !begin)
                        first = FALSE;
                    else if (try_match(&huff->usr, exact))
                    {
                        u = huff->usr;
                        found = TRUE;
                        break;
                    }
                } while (UserFileFindNext(huff, NULL, NULL));

                UserFileFindClose(huff);
            }
        }

        if (found)
        {
            user = u;
            Read_New_User();
        }
        else
        {
            Goto(PROMPT_LINE, 1);
            Puts(ued_not_found);
            Press_ENTER();
        }
    }
}


void UedGetExpireAction(void)
{
    byte cmd;

    changes = TRUE;

    cmd = (byte)toupper(KeyGetRNP(ued_get_action));

    if (cmd == ued_get_actionk[0])
    {
        user.xp_flag &= ~XFLAG_DEMOTE;
        user.xp_flag |= XFLAG_AXE;
    }
    else if (cmd == ued_get_actionk[1])
    {
        char temp[PATHLEN];

        user.xp_flag &= ~XFLAG_AXE;
        user.xp_flag |= XFLAG_DEMOTE;

        Goto(PROMPT_LINE, 1);
        Puts(CLEOL);

        InputGets(temp, ued_getpriv);
        if (*temp)
        {
            word lvl;

            if (isdigit(*temp))
                lvl = (word)atol(temp);
            else
                lvl = ClassKeyLevel(toupper(*temp));

            if (lvl == (word)-1)
            {
                Puts(ued_invalidpriv);
                Press_ENTER();
            }
            else
            {
                user.xp_priv = lvl;
                changes = TRUE;
            }
        }
    }
    else if (cmd == ued_get_actionk[2])
        user.xp_flag &= ~(XFLAG_AXE | XFLAG_DEMOTE);
}


void UedUndoChanges(void)
{
    user = olduser;
    changes = TRUE;
}


int UedPurgeUsers(void)
{
    char fname[PATHLEN];
    char fnameidx[PATHLEN];
    int purgelr[MAX_PLR];
    HUF hufnew;
    HUFF huff;
    int pn = 0;

    Update_User();

    if (UFileBusy())
        return 0;

    Puts(ued_purging);
    vbuf_flush();

    if ((hufnew = UserFileOpen(user_poo, O_CREAT | O_TRUNC)) == NULL)
    {
        cant_open(user_poo);
        return 0;
    }


    strcpy(fnameidx, PRM(user_file));
    strcat(fnameidx, dotidx);

    unlink(fnameidx);

    strcpy(fname, PRM(user_file));
    strcat(fname, dotbbs);

    if (!move_file(fname, user_bak) == 0)
        logit(cantmove, fname, user_bak);
    else if (!move_file(user_poo_bbs, fname) == 0)
        logit(cantmove, user_poo_bbs, fname);
    else if (!move_file(user_poo_idx, fnameidx) == 0)
        logit(cantmove, user_poo_idx, fnameidx);
    else
    {
        if ((huf = UserFileOpen(PRM(user_file), 0)) == NULL)
            logit(cantopen, PRM(user_file));
        else
        {
            PurgeLastreads(purgelr, pn);

            Puts("\r" CLEOL);
            Puts(done_ex);
            Press_ENTER();

            DrawUserScreen();
            vbuf_flush();

            return 0;
        }
    }

    quit(ERROR_CRITICAL);
    return 0;
}

static char *lastread_used;

static int num_ptr, byt, usize;

void FindLR_Start(long usr_rec)
{
    usize = (int)usr_rec;

    num_ptr = usize + 1;
    byt = max(1, num_ptr / CHAR_BITS);
    num_ptr = num_ptr - CHAR_BITS;

    if ((lastread_used = (char *)malloc(byt)) == NULL)
    {
        logit(nomls);
        quit(ERROR_CRITICAL);
    }



        o_byt = byt;

        usize = lr_ptr + 50;
        num_ptr = usize + 1;
        byt = max(1, num_ptr / CHAR_BITS);
        num_ptr = num_ptr - CHAR_BITS;

        if ((lastread_used = realloc(lastread_used, byt)) == NULL)
        {
            logit(nomls);
            quit(ERROR_CRITICAL);
        }

        memset(lastread_used + o_byt, '\0', byt - o_byt);
    }

