// SPDX-License-Identifier: GPL-2.0-or-later




#ifndef MD5_H_DEFINED__
#define MD5_H_DEFINED__

#include "prog.h"

cpp_begin()

#define PROTOTYPES 1
#define MD 5
    typedef unsigned char *POINTER;

typedef dword UINT4;

#define PROTO_LIST(list) list

} MD5_CTX;

void MD5Init PROTO_LIST((MD5_CTX *));
void MD5Update PROTO_LIST((MD5_CTX *, unsigned char *, unsigned int));
void MD5Final PROTO_LIST((unsigned char[16], MD5_CTX *));
void string_to_MD5(char *szString, char *pbMD5);

cpp_end()

