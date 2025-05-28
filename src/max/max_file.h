// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef MAX_FILE_H_DEFINED__
#define MAX_FILE_H_DEFINED__


typedef struct _file_entry
{
} FENTRY;

int Alloc_Filenames_Buffer(void);
void Free_Filenames_Buffer(word usLeave);

#define autodate(f)                                                                                \
    (((prm.flags & FLAG_autodate) && !((f).fa.attribs & (FA_MANDATE | FA_LISTDATE))) ||            \
     ((f).fa.attribs & FA_AUTODATE))
#define manualdate(f)                                                                              \
    ((!(prm.flags & FLAG_autodate) && !((f).fa.attribs & (FA_AUTODATE | FA_LISTDATE))) ||          \
     ((f).fa.attribs & FA_MANDATE))
#define listdate(f) (!!((f).fa.attribs & FA_LISTDATE))

#endif
