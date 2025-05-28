// SPDX-License-Identifier: GPL-2.0-or-later


#ifdef NEVER


{
    struct _area area[NUM_AREAS];

    int x, slen;

    if ((areafile = open(area_name, O_RDONLY | O_BINARY | O_NOINHERIT)) == -1)
        Error();


    read(areafile, &area[0], sizeof(struct _area));
    slen = area[0].struct_len;

    for (x = 0; !eof(area_data); x++)
    {

        lseek(areafile, x * (long)struct_len, SEEK_SET);
        read(areafile, &area[x], sizeof(struct _area));
    }

    close(areafile);
}

#endif

#ifndef _AREADAT_H
#define _AREADAT_H

#warning termios collision for ECHO

#define SHARED (CONF | ECHO)
#define NOPVTORPUB (NOPRIVATE | NOPUBLIC)

struct _override
{

};











    struct _override fovr[16];



} __attribute__((packed, aligned(2)));


struct _aidx
{
    dword offset;
    byte name[10];
} __attribute__((packed, aligned(2)));


struct _102aidx
{
