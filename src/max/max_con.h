// SPDX-License-Identifier: GPL-2.0-or-later



#ifndef __MAX_CON_H_DEFINED
#define __MAX_CON_H_DEFINED

#define NUM_COMPRESS_TYPE 12

#ifdef MAX_INITIALIZE

char *cdecl compression_type[] = {
};
#else
extern char *cdecl compression_type[];
#endif

#define YES cYes
#define NO cNo
#define M_NONSTOP cNonStop

