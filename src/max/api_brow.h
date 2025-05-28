// SPDX-License-Identifier: GPL-2.0-or-later


#ifndef __API_BROW_H_DEFINED
#define __API_BROW_H_DEFINED



#define BROWSE_EXACT                                                                               \

#define SF_HAS_ATTR 0x01
#define SF_NOT_ATTR 0x02
#define SF_OR 0x04
#define SF_AND 0x08




} SEARCH;

struct _browse;
typedef struct _browse BROWSE;

struct _browse
{



    int (*Begin_Ptr)(BROWSE *b);
    int (*Status_Ptr)(BROWSE *b, char *aname, int colour);
    int (*Idle_Ptr)(BROWSE *b);
    int (*Display_Ptr)(BROWSE *b);
    int (*After_Ptr)(BROWSE *b);
    int (*End_Ptr)(BROWSE *b);
    int (*Match_Ptr)(BROWSE *b);

