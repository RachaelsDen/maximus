// SPDX-License-Identifier: GPL-2.0-or-later



typedef enum
{
    CS_TOP,
    CS_SYSTEM,
    CS_MATRIX,
    CS_MENU,
    CS_AREA,
    CS_COLOUR,
    CS_SESSION,
    CS_EVENT,
    CS_LANGUAGE,
    CS_END_
} CVTSTATE;

#define MAX_TRANSLATE_TABLES CS_END_


typedef struct
{
    char *szLine;
    char *szStrippedLine;
    char *szKeyword;
    char *szWords[MAX_LINE_WORDS];
} CVTPARM;


typedef struct
{
    char *szKeyword;
    KWHANDLER kwh;
} TRANSLATOR;

typedef struct
{

struct _tagdata
{
    word struct_len;
    char name[36];
    char areas[348];
};

char *fchar(char *str, char *delim, int wordno);
void Unknown(char *szWhat, char *szValue);
