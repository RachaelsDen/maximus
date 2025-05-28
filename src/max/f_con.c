// SPDX-License-Identifier: GPL-2.0-or-later


#pragma off(unreferenced)
static char rcs_id[] = "$Id: f_con.c,v 1.2 2003/06/04 23:46:21 wesgarland Exp $";
#pragma on(unreferenced)


#include "f_con.h"
#include "alc.h"
#include "arc.h"
#include "ffind.h"
#include "max_file.h"
#include "prog.h"
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <mem.h>
#include <share.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static sword near Display_Contents(char *filename);
static sword near Read_Zip(int zipfile);
static sword near Zip_Scan_For_Header(char *buffer);
static sword near Zip_Read_Directory(int zipfile, long zip_pos, int offset);
static sword near Read_LzhArc(int type, int lzhfile);
static sword near do_ext_hdr(int lzhfile, byte **fname, byte *buf, word hdrlen);


    Strip_Path(filename);

    if (!*filename)
        return;

    display_line = display_col = 1;

        return -1;

    if (Zip_Read_Directory(zipfile, zip_pos, found_header) == -1)
        return -1;

    return 0;
}

static sword near Zip_Scan_For_Header(char *buffer)
{
    byte *x;

    if ((x = memstr(buffer, END_STRSIG, SEEK_SIZE, strlen(END_STRSIG))) != NULL)
        return (sword)((char *)x - buffer);
    else
        return 0;
}

static sword near Zip_Read_Directory(int zipfile, long zip_pos, int offset)
{
    byte temp[5];
    byte method[8];
    byte attributes[5];
    byte *filename;
    byte *file_comment = NULL;
    byte nonstop;
    int ratio_percent;
    int ratio_decimal;

    dword total_uncompressed;
    dword total_compressed;

    word num_files;

    struct _dir_end dir_end;
    struct _dir_header dir_head;

    union stamp_combo stamp;


    lseek(zipfile, (long)((long)zip_pos + (long)offset + 4L), SEEK_SET);
    read(zipfile, (char *)&dir_end.info, sizeof(dir_end.info));


    for (;;)
    {
        if (read(zipfile, temp, 4) != 4)
            return -1;


            if (read(zipfile, (char *)&dir_head.info, sizeof(dir_head.info)) !=
                sizeof(dir_head.info))
                return -1;


                    dir_head.info.file_comment_length = 0;
                }
            }


            lseek(zipfile, (long)dir_head.info.xtra_field_length, SEEK_CUR);


            Strip_Ansi(filename, 0, 0);


            stamp.dos_st.date = dir_head.info.last_mod_date;
            stamp.dos_st.time = dir_head.info.last_mod_time;


            if ((dir_head.info.ver_made_by >> 8) == 0)
            {
                if (dir_head.info.file_attr_ext & MSDOS_HIDDEN)
                    attributes[0] = 'h';

                if (dir_head.info.file_attr_ext & MSDOS_SYSTEM)
                    attributes[1] = 's';

                if (dir_head.info.file_attr_ext & MSDOS_READONLY)
                    attributes[2] = 'r';
                else
                    attributes[2] = 'w';
            }

            if (!dir_head.info.uncompressed_size)
                dir_head.info.uncompressed_size = 1L;

            ratio_percent = (int)(100 - ((dir_head.info.compressed_size * 100) /
                                         dir_head.info.uncompressed_size));

            if (ratio_percent == 100)
                ratio_percent = 99;

            ratio_decimal = (int)(1000 - ((dir_head.info.compressed_size * 1000) /
                                          dir_head.info.uncompressed_size)) %
                            10;

            Printf(zip_format, dir_head.info.uncompressed_size, method,
                   dir_head.info.compressed_size, ratio_percent, ratio_decimal,
                   stamp.msg_st.date.mo, stamp.msg_st.date.da, (stamp.msg_st.date.yr + 80) % 100,
                   stamp.msg_st.time.hh, stamp.msg_st.time.mm, dir_head.info.crc, attributes,
                   (dir_head.info.bits & 0x01) ? '*' : ' ', filename);


            if (dir_head.info.bits & 0x01)
                Printf(zip_encrypt, filename);


            free(filename);

            if (dir_head.info.file_comment_length)
                free(file_comment);
        }
        else if (memcmp(temp, END_STRSIG, 4) == 0)
        {
            display_line += 2;

            if (MoreYnBreak(&nonstop, NULL))
                break;


            Puts(zip_trail1);

            if (total_uncompressed)
                Printf(zip_trail2, total_uncompressed, total_compressed,
                       (int)(100 - ((total_compressed * 100) / total_uncompressed)),
                       (int)(1000 - ((total_compressed * 1000) / total_uncompressed)) % 10,
                       num_files);

            return 0;
        }
        else
    return 0;
}

static sword near Read_LzhArc(int type, int lzhfile)
{
    struct _lhpre pre;
    struct _lh0 *lh0 = NULL;
    struct _lh2 *lh2;
    byte *lhtemp = NULL, *cur;

    struct _archead archead;
    struct tm *filed;

    struct _arj_id aid;
    struct _arj_hdr *arj = NULL;

    byte *fname, *p;
    byte attr[6];
    byte method[10];
    byte nonstop;

    word tempword, crc;
    word num_files, percent, first;

    sword hsize;

    dword total_compressed, total_uncompressed;
    dword compressed_size = 0L, uncompressed_size = 0L;
    dword dwcrc;

    union stamp_combo file_date;

    first = TRUE;

    num_files = 0;
    total_compressed = total_uncompressed = 0L;
    nonstop = FALSE;

    Puts(arc_h1);
    Puts(arc_h2);

#ifndef UNIX
    while (!eof(lzhfile))
#else
    while (1)
#endif
    {
        Mdm_check();

        if (halt() || MoreYnBreak(&nonstop, NULL))
            return 0;

        strcpy(attr, four_blanks);

        if (type == ARCHIVE_LZH)
        {

            if (read(lzhfile, (char *)&pre, sizeof(struct _lhpre)) != sizeof(struct _lhpre))
            {
                break;
            }

            if (pre.hdrsize == 0 || (lhtemp = malloc(pre.hdrsize)) == NULL)
                break;


            if (pre.hdrsize == 0)
                break;

            lh0 = (struct _lh0 *)lhtemp;
            fname = NULL;

            if (lh0->hdr_ver == 0 || lh0->hdr_ver == 1)
            {
                file_date.ldate = ((file_date.ldate >> 16) | (file_date.ldate << 16));

#endif


                if ((fname = malloc(lh0->namelen + 1)) == NULL)
                    break;

                memmove(fname, cur, lh0->namelen);
                fname[lh0->namelen] = '\0';

                cur += lh0->namelen;


                cur++;

                crc = lh2->crc;


            if (read(lzhfile, (char *)&aid, sizeof(struct _arj_id)) != sizeof(struct _arj_id) ||
                aid.id != ARJ_ID)
            {
                break;
            }


            if ((lhtemp = malloc(aid.hdr_size)) == NULL)
                break;


            if (read(lzhfile, (char *)&dwcrc, sizeof(dword)) != sizeof(dword))
                break;

            arj = (struct _arj_hdr *)lhtemp;
            cur = lhtemp + arj->hdr_size;


            cur += strlen(cur) + 1;


            while (read(lzhfile, (char *)&tempword, sizeof(word)) && tempword)
                lseek(lzhfile, (long)tempword + 4L, SEEK_CUR);

            if (arj->method == 0)
                strcpy(method, zip_store);
            else
            {
                strcpy(method, zip_reduce);
                method[6] = (char)('0' + arj->method);
            }

            file_date = arj->mod_date;


            file_date.ldate = ((file_date.ldate >> 16) | (file_date.ldate << 16));

#endif

            if (!first)
            {
                compressed_size = arj->comp_size;
                uncompressed_size = arj->orig_size;
            }

            crc = (word)arj->file_crc;
        }
        else
            break;


        if (type == ARCHIVE_LZH)
        {

            lseek(lzhfile, lh0->compressed_size - (lh0->hdr_ver == 2 ? 2 : 0), SEEK_CUR);

            free(lhtemp);
            free(fname);
        }
        else if (type == ARCHIVE_ARC)
            lseek(lzhfile, archead.compressed_size, SEEK_CUR);
        else if (type == ARCHIVE_ARJ)
        {

            if (!first)
                lseek(lzhfile, arj->comp_size, SEEK_CUR);

            free(lhtemp);
        }

        first = FALSE;

        num_files++;
    }

    Puts(arc_t1);

    if (total_uncompressed)
        Printf(arc_t2, num_files, total_uncompressed, total_compressed,
               (int)(100 - ((total_compressed * 100) / total_uncompressed)),
               (int)(1000 - ((total_compressed * 1000) / total_uncompressed)) % 10);

    return 0;
}

static sword near do_ext_hdr(int lzhfile, byte **fname, byte *buf, word hdrlen)
{
    byte *ext, *p;
    word extsize = 0;

    p = buf;

    while (hdrlen)
    {

        if (buf)
        {
            ext = p;
            p += hdrlen;
        }
        else
        {
            if ((ext = malloc(hdrlen)) == NULL)
                break;

            ;

        extsize += hdrlen;
        hdrlen = *(word *)((byte *)ext + hdrlen - 2);

        if (!buf)
            free(ext);
    }

    return extsize;
}
