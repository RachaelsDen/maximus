// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __ETL_H_DEFINED
#define __ETL_H_DEFINED


mex_extern struct _id
{
    char *name;
    word value;
} idlist[]
#ifdef MEX_INIT
    = {{"char", T_BYTE},
       {"int", T_WORD},
       {"long", T_DWORD},
       {"void", T_VOID},
       {"string", T_STRING},
       {"if", T_IF},
       {"then", T_THEN},
       {"else", T_ELSE},
       {"goto", T_GOTO},
       {"array", T_ARRAY},
       {"of", T_OF},
       {"while", T_WHILE},
       {"do", T_DO},
       {"for", T_FOR},
       {"ref", T_REF},
       {"return", T_RETURN},
       {"shl", T_SHL},
       {"shr", T_SHR},
       {"and", T_LAND},
       {"or", T_LOR},
       {"struct", T_STRUCT},
       {"unsigned", T_UNSIGNED},
       {"signed", T_SIGNED},
       {"sizeof", T_SIZEOF},
       {NULL, 0}}
#endif
;

