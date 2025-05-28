// SPDX-License-Identifier: GPL-2.0-or-later



static char *usage = "ar -- compression archiver -- written by Haruhiko Okumura\n"
                     "  PC-VAN:SCIENCE        CompuServe:74050,1022\n"
                     "  NIFTY-Serve:PAF01022  INTERNET:74050.1022@compuserve.com\n"
                     "Usage: ar command archive [file ...]\n"
                     "Commands:\n"
                     "   a: Add files to archive (replace if present)\n"
                     "   x: Extract files from archive\n"
                     "   r: Replace files in archive\n"
                     "   d: Delete files from archive\n"
                     "   p: Print files on standard output\n"
                     "   l: List contents of archive\n"
                     "If no files are named, all files in archive are processed,\n"
                     "   except for commands 'a' and 'd'.\n"
                     "You may copy, distribute, and rewrite this program freely.\n";


#include "ar.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

{
    int i;

    for (i = 0; i < 3; i++)
        if (a <= ULONG_MAX / 10)
            a *= 10;
        else
            b /= 10;
    if ((ulong)(a + (b >> 1)) < a)
    {
        a >>= 1;
        b >>= 1;
    }
    if (b == 0)
        return 0;
    return (uint)((a + (b >> 1)) / b);
}

static void put_to_header(int i, int n, ulong x)
{
    while (--n >= 0)
    {
        header[i++] = (uchar)((uint)x & 0xFF);
        x >>= 8;
    }
}

static ulong get_from_header(int i, int n)
{
    ulong s;

    s = 0;
    while (--n >= 0)
    headersum = (uchar)fgetc(arcfile);
}

static void write_header(void)
{
    fputc(headersize, outfile);
}

static void skip(void) { fseek(arcfile, compsize, SEEK_CUR); }

static void copy(void)
{
    uint n;

    write_header();
    while (compsize != 0)
    {
        n = (uint)((compsize > DICSIZ) ? DICSIZ : compsize);
        if (fread((char *)buffer, 1, n, arcfile) != n)
            error("Can't read");
        if (fwrite((char *)buffer, 1, n, outfile) != n)
            error("Can't write");
        compsize -= n;
    }
}

static void store(void)
{
    uint n;

    origsize = 0;
    crc = INIT_CRC;
    while ((n = fread((char *)buffer, 1, DICSIZ, infile)) != 0)
    {
        fwrite_crc(buffer, n, outfile);
        origsize += n;
    }
    compsize = origsize;
}

static int add(int replace_flag)
{
    long headerpos, arcpos;
    uint r;

    if ((infile = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", filename);

    if (replace_flag)
    {
        printf("Replacing %s ", filename);
        skip();
    }
    else
        printf("Adding %s ", filename);
    headerpos = ftell(outfile);
    namelen = strlen(filename);
    headersize = 25 + namelen;
    arcpos = ftell(outfile);
    origsize = compsize = 0;
    unpackable = 0;
    crc = INIT_CRC;
    encode();
    if (unpackable)
    {
    fseek(outfile, 0L, SEEK_END);
    r = ratio(compsize, origsize);
    printf(" %d.%d%%\n", r / 10, r % 10);
        printf("Extracting %s ", filename);
    }
    else
    {
        outfile = stdout;
        printf("===== %s =====\n", filename);
    }
    crc = INIT_CRC;
    method = header[3];
    header[3] = ' ';
    if (!strchr("045", method) || memcmp("-lh -", header, 5))
    {
        fprintf(stderr, "Unknown method: %u\n", method);
        skip();
    }
    else
    {
        ext_headersize = (uint)get_from_header(headersize - 2, 2);
        while (ext_headersize != 0)
        {
            fprintf(stderr, "There's an extended header of size %u.\n", ext_headersize);
            compsize -= ext_headersize;
            if (fseek(arcfile, ext_headersize - 2, SEEK_CUR))
                error("Can't read");
            ext_headersize = fgetc(arcfile);
            ext_headersize += (uint)fgetc(arcfile) << 8;
        }
        crc = INIT_CRC;
        if (method != '0')
            decode_start();
        while (origsize != 0)
        {
            n = (uint)((origsize > DICSIZ) ? DICSIZ : origsize);
            if (method != '0')
                decode(n, buffer);
            else if (fread((char *)buffer, 1, n, arcfile) != n)
                error("Can't read");
            fwrite_crc(buffer, n, outfile);
            if (outfile != stdout)
                fputc('.', stdout);
            origsize -= n;
        }
    }
    if (to_file)
        fclose(outfile);
    else
        outfile = NULL;
    printf("\n");
    if ((crc ^ INIT_CRC) != file_crc)
        fprintf(stderr, "CRC error\n");
}

static void list_start(void) { printf("Filename         Original Compressed Ratio CRC Method\n"); }

static void list(void)
{
    uint r;

    printf("%-14s", filename);
    if (namelen > 14)
        printf("\n              ");
    r = ratio(compsize, origsize);
    printf(" %10lu %10lu %u.%03u %04X %5.5s\n", origsize, compsize, r / 1000, r % 1000, file_crc,
           header);
}

static int match(char *s1, char *s2)
{
    for (;;)
    {
        while (*s2 == '*' || *s2 == '?')
        {
            if (*s2++ == '*')
                while (*s1 && *s1 != *s2)
                    s1++;
            else if (*s1 == 0)
                return 0;
            else
                s1++;
        }
        if (*s1 != *s2)
            return 0;
        if (*s1 == 0)
            return 1;
        s1++;
        s2++;
    }
}

static int search(int argc, char *argv[])
{
    int i;

    if (argc == 3)
        return 1;
    for (i = 3; i < argc; i++)
        if (match(filename, argv[i]))
            return 1;
    return 0;
}

static void exitfunc(void)
{
    fclose(outfile);
    remove(temp_name);
}

int main(int argc, char *argv[])
{
    int i, j, cmd, count, nfiles, found, done;

    for (i = 3; i < argc; i++)
        if (strpbrk(argv[i], "*?"))
            break;
    if (cmd == 'A' && i < argc)
        error("Filenames may not contain '*' and '?'");
    if (i < argc)


        atexit(exitfunc);
    }
    else
        temp_name = NULL;

    make_crctable();
    count = done = 0;

    if (cmd == 'A')
    {
        for (i = 3; i < argc; i++)
        {
            for (j = 3; j < i; j++)
                if (strcmp(argv[j], argv[i]) == 0)
                    break;
            if (j == i)
            {
                strcpy(filename, argv[i]);
                if (add(0))
                    count++;
                else
                    argv[i][0] = 0;
            }
            else
                nfiles--;
        }
        if (count == 0 || arcfile == NULL)
            done = 1;
    }

    while (!done && read_header())
    {
        found = search(argc, argv);
        switch (cmd)
        {
        case 'R':
            if (found)
            {
                if (add(1))
                    count++;
                else
                    copy();
            }
            else
                copy();
            break;
        case 'A':
        case 'D':
            if (found)
            {
                count += (cmd == 'D');
                skip();
            }
            else
                copy();
            break;
        case 'X':
        case 'P':
            if (found)
            {
                extract(cmd == 'X');
                if (++count == nfiles)
                    done = 1;
            }
            else
                skip();
            break;
        case 'L':
            if (found)
            {
                if (count == 0)
                    list_start();
                list();
                if (++count == nfiles)
                    done = 1;
            }
            skip();
            break;
        }
    }

    if (temp_name != NULL && count != 0)
    {
