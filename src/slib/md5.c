// SPDX-License-Identifier: GPL-2.0-or-later




#include "md5.h"
#include "prog.h"
#include <string.h>

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

static void MD5Transform PROTO_LIST((UINT4[4], unsigned char[64]));
static void Encode PROTO_LIST((unsigned char *, UINT4 *, unsigned int));
static void Decode PROTO_LIST((UINT4 *, unsigned char *, unsigned int));
static void MD5_memcpy PROTO_LIST((POINTER, POINTER, unsigned int));
static void MD5_memset PROTO_LIST((POINTER, int, unsigned int));

static unsigned char PADDING[64] = {0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define FF(a, b, c, d, x, s, ac)                                                                   \
    {                                                                                              \
        (a) += F((b), (c), (d)) + (x) + (UINT4)(ac);                                               \
        (a) = ROTATE_LEFT((a), (s));                                                               \
        (a) += (b);                                                                                \
    }
#define GG(a, b, c, d, x, s, ac)                                                                   \
    {                                                                                              \
        (a) += G((b), (c), (d)) + (x) + (UINT4)(ac);                                               \
        (a) = ROTATE_LEFT((a), (s));                                                               \
        (a) += (b);                                                                                \
    }
#define HH(a, b, c, d, x, s, ac)                                                                   \
    {                                                                                              \
        (a) += H((b), (c), (d)) + (x) + (UINT4)(ac);                                               \
        (a) = ROTATE_LEFT((a), (s));                                                               \
        (a) += (b);                                                                                \
    }
#define II(a, b, c, d, x, s, ac)                                                                   \
    {                                                                                              \
        (a) += I((b), (c), (d)) + (x) + (UINT4)(ac);                                               \
        (a) = ROTATE_LEFT((a), (s));                                                               \
        (a) += (b);                                                                                \
    }

    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
}

    index = (unsigned int)((context->count[0] >> 3) & 0x3F);

    if (inputLen >= partLen)
    {
        MD5_memcpy((POINTER)&context->buffer[index], (POINTER)input, partLen);
        MD5Transform(context->state, context->buffer);

        for (i = partLen; i + 63 < inputLen; i += 64)
            MD5Transform(context->state, &input[i]);

        index = 0;
    }
    else
        i = 0;

{
    unsigned char bits[8];
    unsigned int index, padLen;

    index = (unsigned int)((context->count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    MD5Update(context, PADDING, padLen);

    Encode(digest, context->state, 16);

    MD5_memset((POINTER)context, 0, sizeof(*context));
}

static void MD5Transform(state, block) UINT4 state[4];
unsigned char block[64];
{
    UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

    Decode(x, block, 64);



    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;

    MD5_memset((POINTER)x, 0, sizeof(x));
}

static void Encode(output, input, len) unsigned char *output;
UINT4 *input;
unsigned int len;
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
    {
        output[j] = (unsigned char)(input[i] & 0xff);
        output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}

static void Decode(output, input, len) UINT4 *output;
unsigned char *input;
unsigned int len;
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((UINT4)input[j]) | (((UINT4)input[j + 1]) << 8) |
                    (((UINT4)input[j + 2]) << 16) | (((UINT4)input[j + 3]) << 24);
}


static void MD5_memcpy(output, input, len) POINTER output;
POINTER input;
unsigned int len;
{
    memcpy(output, input, len);
}

static void MD5_memset(output, value, len) POINTER output;
int value;
unsigned int len;
{
    memset(output, value, len);
}


void string_to_MD5(char *szString, char *pbMD5)
{
    MD5_CTX ctx;

    MD5Init(&ctx);
    MD5Update(&ctx, szString, strlen(szString));
    MD5Final(pbMD5, &ctx);
}
