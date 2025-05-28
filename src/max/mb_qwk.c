// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: mb_qwk.c,v 1.2 2003/06/04 23:46:22 wesgarland Exp $";
#pragma on(unreferenced)


#define MAX_LANG_m_browse
#define MAX_LANG_f_area
#define MAX_LANG_max_chat

#include "mb_qwk.h"
#include "dr.h"
#include "ffind.h"
#include "m_browse.h"
#include "max_file.h"
#include "max_msg.h"
#include "prog.h"
#include "qwk.h"
#include <fcntl.h>
#include <io.h>
#include <share.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef MAX_TRACKER
#include "trackc.h"
#include "trackm.h"
#endif
#include "l_attach.h"

static void near QWKAddToCdat(PMAH pmah);

#else
#define MAX_QWK_BUF 64
#endif


            sprintf(temp, "%s" PATH_DELIMS "filatt%02d%s", qwk_path, FileEntries(),
                    strrchr(q->fname, '.'));
            if (lcopy(q->fname, temp) == -1)
            {

static int near queue_block(char *block)
{
    int bytes;


    if (!block || mdat_nblock == MAX_QWK_BUF)
    {
        bytes = QWK_RECSIZE * mdat_nblock;


    if (*PRM(olr_dir) == '\0' || *PRM(olr_name) == '\0' || *PRM(arc_ctl) == '\0')
        return -1;

    sprintf(qwk_path, "%snode%02x", PRM(olr_dir), task_num);

    return Make_Clean_Directory(qwk_path);
}

void Clean_QWK_Directory(int rdir) { Clean_Directory(qwk_path, rdir); }

static int near Create_Control_DAT(void)
{
    char temp[PATHLEN];
    union stamp_combo sc;
    static char ps_n[] = "%s\n";

    sprintf(temp, "%scontrol.dat", qwk_path);

    if ((cdat = shfopen(temp, fopen_writep, O_RDWR | O_CREAT | O_NOINHERIT)) == NULL)
    {
        cant_open(temp);
        return -1;
    }

    Get_Dos_Date(&sc);


    fprintf(cdat, "\n");


    fprintf(cdat, "0 ,%s\n", PRM(olr_name));


    strcpy(temp, usrname);
    fprintf(cdat, "%s\n", cstrupr(temp));


    cdatpos = ftell(cdat);


    return 0;
}

static int near Create_Messages_DAT(void)
{


    sprintf(mdatname, mdat_template, qwk_path);

    if ((qwkfile = sopen(mdatname, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY | O_NOINHERIT,
                         SH_DENYNONE, S_IREAD | S_IWRITE)) == -1)
    {
        cant_open(mdatname);
        free(mdat_buf);
        return -1;
    }

    memset(block, ' ', QWK_RECSIZE);
    memmove(block, text, strlen(text));

    if (!queue_block(block))
    {
        close(qwkfile);
        return -1;
    }


    if ((*akd = malloc(sizeof(struct _akd) * MAX_QWK_AREAS)) == NULL)
        return -1;


    sprintf(temp, ps_dats, PRM(olr_dir));

    if (!direxist(temp))
        if (mkdir(temp) != 0)
        {
            free(*akd);
            return -1;
        }


    if ((kfd = shopen(temp, O_RDONLY | O_BINARY | O_NOINHERIT)) == -1 ||
        read(kfd, (char *)akh, sizeof(struct _akh)) != sizeof(struct _akh) ||
        !eqstri(akh->name, usr.name))
    {
        strcpy(akh->name, usr.name);
        akh->num_areas = 0;
        return 0;
    }


    if ((got = read(kfd, (char *)*akd, howmuch)) != (int)howmuch)
        akh->num_areas = got / sizeof(struct _akd);

    close(kfd);
    return 0;
}

int Write_Kludge_File(struct _akh *akh, struct _akd **akd)
{
    char temp[PATHLEN];
    unsigned howmuch;
    int kfd, ret;

    ret = -1;

    sprintf(temp, ps_dats, PRM(olr_dir));
    sprintf(temp + strlen(temp), o8lxdat, (long)usr.lastread_ptr);

    if ((kfd = sopen(temp, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY | O_NOINHERIT, SH_DENYNONE,
                     S_IREAD | S_IWRITE)) == -1)
    {
        return -1;
    }

    if (write(kfd, (char *)akh, sizeof(struct _akh)) == sizeof(struct _akh))
    {
        howmuch = akh->num_areas * sizeof(struct _akd);

        if (write(kfd, (char *)*akd, howmuch) == (signed)howmuch)
            ret = 0;
    }

    close(kfd);
    return ret;
}


int InsertAkh(char *aname, int tossto)
{
    int old, an;

    if (tossto != -1 && tossto <= MAX_QWK_AREAS)
        an = tossto;
    else
    {

        for (an = 0; an < akh.num_areas; an++)
            if (eqstri(aname, akd[an].name))
                break;


        if (an == akh.num_areas && akh.num_areas >= MAX_QWK_AREAS)
        {

            for (an = 0, old = -1; an < akh.num_areas; an++)
                if (old == -1 || !GEdate(&akd[an].used, &akd[old].used))
                    old = an;


            if (akd[old].used.ldate == now.ldate)
            {
                Puts(qwk_toomany);
                return 1;
            }

            an = old;
        }
    }

    strcpy(akd[an].name, aname);
    akd[an].used = now;

    if (an >= akh.num_areas)
        akh.num_areas = an + 1;

    return an;
}


    sprintf(tp, ndx_name, qwk_path, this_conf);

    if ((ndxfile = sopen(tp, O_CREAT | O_TRUNC | O_WRONLY | O_BINARY | O_NOINHERIT, SH_DENYNONE,
                         S_IREAD | S_IWRITE)) == -1)
    {
        cant_open(tp);
        return -1;
    }

    n_qidx = 0;

    if (!b->fSilent)
    {
        Rev_Up();
        Printf(srchng, (colour % 7) + 9, aname);
        vbuf_flush();
    }

    area_toyou = area_packed = 0;


    if (*PMAS(pmah, echo_tag) == 0)
    {
        strcpy(temp, *PMAS(pmah, descript) == 0 ? PMAS(pmah, name) : PMAS(pmah, descript));
    }
    else
    {
        strcpy(temp, MAS(*pmah, echo_tag));
        cfancy_str(temp);
    }


    temp[12] = '\0';
    fprintf(cdat, "%s\n", *temp ? temp : "Unknown");
}


static int near maybe_queue(char **blpos, char *block, int *n_blocks)
{

    while (*blpos >= block + QWK_RECSIZE)
    {
        if (!queue_block(block))
            return FALSE;

        *blpos -= QWK_RECSIZE;

        memmove(block, block + QWK_RECSIZE, *blpos - block);
        (*n_blocks)++;
    }

    return TRUE;
}



    qm.status = (byte)((b->msg.attr & MSGPRIVATE) ? '*' : ' ');

    if (b->msg.attr & MSGREAD)
        qm.status = (byte)(qm.status == '*' ? '+' : '-');

    bprintf(qm.msgn, "%-7ld", MsgMsgnToUid(b->sq, b->msgn));

    bprintf(qm.date, "%02d-%02d-%02d", b->msg.date_written.date.mo, b->msg.date_written.date.da,
            (b->msg.date_written.date.yr + 80) % 100);

    bprintf(qm.time, "%02d:%02d", b->msg.date_written.time.hh, b->msg.date_written.time.mm);

    bprintf(qm.from, "%-25.25s", b->msg.from);
    bprintf(qm.to, "%-25.25s", b->msg.to);
    bprintf(qm.subj, "%-25.25s", b->msg.subj);
    bprintf(qm.pwd, "            ");
    bprintf(qm.replyto, "%-8ld", b->msg.replyto);


static int near AddPersonalIndex(BROWSE *b, struct _qmndx *pqn)
{
    char fname[PATHLEN];
    int rc = TRUE;


static int near BuildIndex(BROWSE *b, long this_rec, word this_conf)
{
    long ieee;
    struct _qmndx qmndx;
    int rc = TRUE;


    if (n_qidx == MAX_QIDX)
        Flush_Qidx();


struct _qwk_callback
{
    int line_type;
    char **blpos;
    char *block;
    int *n_blocks;
};


    if (pqc->line_type & MSGLINE_SEENBY && !GEPriv(usr.priv, prm.seenby_priv))
        return 0;
    else if (pqc->line_type & MSGLINE_KLUDGE && !GEPriv(usr.priv, prm.ctla_priv))
        return 0;


    if (pqc->line_type & MSGLINE_KLUDGE)
    {
        **pqc->blpos = '@';
        (*pqc->blpos)++;
    }


    if (!maybe_queue(pqc->blpos, pqc->block, pqc->n_blocks))
        return -1;

    return 0;
}


    *pthis_rec = tell(qwkfile) / QWK_RECSIZE + mdat_nblock;


    if (!BuildIndex(b, *pthis_rec, this_conf))
        rc = -1;


static void near QWKAddHeaderText(BROWSE *b, char *block, char **pblpos, int *pn_blocks,
                                  TRK_MSG_NDX *ptmn, char *ctrl, int *pdo_we_own)
{

    *pn_blocks = 1;
    *pblpos = block;


#ifdef MAX_TRACKER
    **pblpos = 0;
    TrackAddQWKFirst(ptmn, pdo_we_own, *pblpos, ctrl);
    (*pblpos) += strlen(*pblpos);
#endif


    qc.blpos = pblpos;
    qc.block = block;
    qc.n_blocks = pn_blocks;
    qc.line_type = MSGLINE_KLUDGE;


static int QWKAddMsgBody(BROWSE *b, char *block, char **pblpos, int *pn_blocks)
{

    qc.blpos = pblpos;
    qc.block = block;
    qc.n_blocks = pn_blocks;

    if ((n_ol = Alloc_Outline(ol)) < 1)
        return -1;

    while ((got = Msg_Read_Lines(b->m, n_ol, 80 - HARD_SAFE, 80 - SOFT_SAFE, ol, lt, &last_attr,
                                 MRL_QEXP)) > 0)
    {
        for (ln = 0; ln < got; ln++)
        {
            qc.line_type = lt[ln];

            if (QWKCallBack(ol[ln], &qc, FALSE) == -1)
                break;
        }
    }

    Dealloc_Outline(ol);
    return 0;
}


    if (++total_packed >= (dword)prm.max_pack && prm.max_pack)
        return -1;

    return 0;
}



    if (((union stamp_combo *)&b->msg.date_arrived)->ldate != 0 &&
        !GEdate(&b->msg.date_arrived, &scRestrict))
    {
        return 0;
    }


    if (QWKInitializeHeaders(b, qwkfile, &this_rec) == -1)
        ret = -1;


    QWKAddHeaderText(b, block, &blpos, &n_blocks, &tmn, ctrl, &do_we_own);
    QWKAddMsgBody(b, block, &blpos, &n_blocks);


        if ((pdb = Read_Attach(&lfa, &b->msg, ctrl, !!(mah.ma.attribs & MA_NET))) != NULL)
        {
            char temp[PATHLEN * 3];


            LFAdbClose(pdb);
        }
    }

#ifdef MAX_TRACKER

        if (!maybe_queue(&blpos, block, &n_blocks))
            ret = -1;
    }
#endif


    Recd_Msg(b->m, &b->msg, TRUE);
    Update_Length(this_rec, n_blocks);

    usr.msgs_read++;


int QWK_After(BROWSE *b)
{
    char temp[PATHLEN];
    dword num_msg;

    NW(b);

    Flush_Qidx();
    close(ndxfile);

    close(qwkfile);

    FinishControlDAT();

    if (!b->fSilent)
        Printf(qwk_pack_end, total_msgs, total_toyou, total_packed);

    if (total_packed >= (dword)prm.max_pack && prm.max_pack)
        Printf(qwk_too_many, (long)prm.max_pack);


        if (!b->fSilent)
            TrackReportOurMessages(qwk_path);
#endif

        Write_Kludge_File(&akh, &akd);
        ret = QWK_Compress_Mail(b);




    fprintf(cdat, cdat_hello);
    fprintf(cdat, cdat_news);
    fprintf(cdat, cdat_goodbye);
    fprintf(cdat, "0\n");


    if (total_packed == 0 || GetYnAnswer(download_msgs, 0) == NO)
        return -1;

    Puts(wait_doing_compr);

    GenerateStupidFiles();

    sprintf(qwkname, "%s%s.qw%c", qwk_path, PRM(olr_name), qwk_ctr);
    unlink(qwkname);

    sprintf(files, "%s*.*", qwk_path);

    Load_Archivers();

    while (usr.compress == 0 || usr.compress > MAX_ARI || (pai = UserAri(usr.compress)) == NULL)
    {
        usr.compress = Get_Archiver();
    }

    if (!pai)
    {
        Puts(unknown_compr);
        ret = -1;
    }
    else
    {
        char tmp[PATHLEN * 2];

        Form_Archiver_Cmd(qwkname, files, cmd, pai->add);


        ChatSaveStatus(&css);
        ChatSetStatus(FALSE, cs_file_xfer);


        if (File_Send_Files(protocol, menuname, NULL, 1))
            good = TRUE;


        ChatRestoreStatus(&css);

        Free_Filenames_Buffer(0);
        restore_tag_list(NULL, FALSE);
    }

    if (good)
    {
        extern struct _lrptr *lrptr;

        if (qwk_ctr == 'k')
            qwk_ctr = '0';

        qwk_ctr++;

        if (qwk_ctr == '9' + 1)
            qwk_ctr = '0';

        if (lrptr)
        {
            Puts(qwk_update_lr);
            vbuf_flush();
            Lmsg_Update(b);
            Putc('\n');
        }
    }


#ifdef NEVER
static void near MakeBlank(char *s)
{
    char fname[PATHLEN];
    int fd;

    strcpy(fname, qwk_path);
    strcat(fname, s);

    if ((fd = open(fname, O_CREAT | O_WRONLY | O_BINARY, S_IREAD | S_IWRITE)) != -1)
        close(fd);
}
#endif

static void near CopyOLRdir(char *fspec)
{
    char fname[PATHLEN];
    char toname[PATHLEN];
    FFIND *ff;

    strcpy(fname, PRM(olr_dir));
    strcat(fname, fspec);

    if ((ff = FindOpen(fname, 0)) == NULL)
        return;

    do
    {

    sprintf(fname, "%sDOOR.ID", qwk_path);

    if ((fp = fopen(fname, "w")) != NULL)
    {
        fprintf(fp, door_id_name, us_short);
        fprintf(fp, door_id_ver, version);
        fprintf(fp, door_id_sys, xfer_id);
        fprintf(fp, door_id_cname, cprog_name);
        fprintf(fp, door_id_ctype_add);
        fprintf(fp, door_id_ctype_drop);
        fclose(fp);
    }



static void _stdc bprintf(char *dest, char *format, ...)
{
    char string[120];
    va_list var_args;

    va_start(var_args, format);
    vsprintf(string, format, var_args);
    va_end(var_args);

    memmove(dest, string, strlen(string));
}

static void near Flush_Qidx(void)
{
    if (n_qidx)
    {
        write(ndxfile, (char *)qidxs, sizeof(struct _qmndx) * n_qidx);
        n_qidx = 0;
    }
}


static void near Update_Length(long rec, int blocks)
{
    if (n_len == MAX_LEN_CHAIN)
        Flush_Len_Chain();

    len_chain[n_len].rec = rec;
    len_chain[n_len++].blocks = blocks;
}


static void near Flush_Len_Chain(void)
{
    struct _len_ch *lc, *end;
    char b_len[12];

