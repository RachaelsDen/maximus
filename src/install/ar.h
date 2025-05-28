// SPDX-License-Identifier: GPL-2.0-or-later



#ifdef NT
typedef unsigned short ushort;
#endif

#include "compiler.h"
#include "typedefs.h"
#include <limits.h>
#include <stdio.h>

#ifdef MAX_INSTALL
#endif


void putbits(int n, uint x);
int fread_crc(uchar *p, int n, FILE *f);
void fwrite_crc(uchar *p, int n, FILE *f);
void init_getbits(void);
void init_putbits(void);

#define DICSIZ (1U << DICBIT)

#define NC (UCHAR_MAX + MAXMATCH + 2 - THRESHOLD)

void make_table(int nchar, uchar bitlen[], int tablebits, ushort table[]);

